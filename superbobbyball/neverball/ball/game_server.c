/*
 * Copyright (C) 2003 Robert Kooima
 *
 * NEVERBALL is  free software; you can redistribute  it and/or modify
 * it under the  terms of the GNU General  Public License as published
 * by the Free  Software Foundation; either version 2  of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
 * General Public License for more details.
 */

#include <SDL.h>
#include <math.h>
#include <assert.h>

#include "vec3.h"
#include "geom.h"
#include "config.h"
#include "binary.h"
#include "common.h"
#include "ease.h"

#include "solid_sim.h"
#include "solid_all.h"

#include "game_common.h"
#include "game_server.h"
#include "game_proxy.h"

#include "cmd.h"
#include "progress.h"

/*---------------------------------------------------------------------------*/

static int server_state = 0;
static int game_mode = MODE_NORMAL;

struct server_player
{
    struct s_vary vary;
    struct s_vary *sim_state;
    int ball_index;
    int sim_owner;

    struct game_tilt tilt;
    struct game_view view;

    float view_k;
    float view_time;
    float view_fade;

    float view_zoom_curr;
    float view_zoom_start;
    float view_zoom_end;
    float view_zoom_time;

    float time_limit;
    float time_elapsed;
    float timer;
    int   status;
    int   coins;

    int   goal_e;
    int   jump_e;
    int   jump_b;
    float jump_dt;
    float jump_p[3];
    float start_p[3];

    /* Flight Physics State */
    int   fly_active;
    int   fly_done;
    float fly_pitch;

    /* Fight Physics State */
    int   punch_state; /* 0=None, 1=Extending, 2=Retracting */
    float punch_timer;

    /* Billiards/Bowling State */
    float shot_power;
    int   bowling_frame;
    int   bowling_throw;
    int   bowling_pins[10];
    float bowling_pin_start[10][3];
    int   shot_state; /* 0=Aim, 1=Power, 2=Rolling */

    /* Hub State */
    int   warp_id;

    int   action_prev;
};

static struct server_player players[MAX_PLAYERS];
static int player_count = 1;

#define VIEW_FADE_MIN 0.2f
#define VIEW_FADE_MAX 1.0f

#define ZOOM_DELAY (GROW_TIME * 0.5f)
#define ZOOM_TIME (ZOOM_DELAY + GROW_TIME)
#define ZOOM_MIN 0.75f
#define ZOOM_MAX 1.25f

/*---------------------------------------------------------------------------*/

struct input
{
    float s;
    float x;
    float z;
    float r;
    int   c;
    int   action;
};

static struct input input_players[MAX_PLAYERS];

static float get_angle_bound(void)
{
    return config_get_d(CONFIG_PHYSICS) ? 60.0f : ANGLE_BOUND;
}

static void input_init(void)
{
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        input_players[i].s = RESPONSE;
        input_players[i].x = 0;
        input_players[i].z = 0;
        input_players[i].r = 0;
        input_players[i].c = 0;
        input_players[i].action = 0;
    }
}

static void input_set_s(int p, float s)
{
    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].s = s;
}

static void input_set_x(int p, float x)
{
    float bound = get_angle_bound();
    if (x < -bound) x = -bound;
    if (x >  bound) x =  bound;

    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].x = x;
}

static void input_set_z(int p, float z)
{
    float bound = get_angle_bound();
    if (z < -bound) z = -bound;
    if (z >  bound) z =  bound;

    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].z = z;
}

static void input_set_r(int p, float r)
{
    if (r < -VIEWR_BOUND) r = -VIEWR_BOUND;
    if (r >  VIEWR_BOUND) r =  VIEWR_BOUND;

    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].r = r;
}

static void input_set_c(int p, int c)
{
    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].c = c;
}

static void input_set_action(int p, int a)
{
    if (p >= 0 && p < MAX_PLAYERS)
        input_players[p].action = a;
}

static float input_get_s(int p)
{
    float s = (p >= 0 && p < MAX_PLAYERS) ? input_players[p].s : RESPONSE;
    if (config_get_d(CONFIG_PHYSICS)) return s * 0.2f; /* Faster response */
    return s;
}

static float input_get_x(int p)
{
    return (p >= 0 && p < MAX_PLAYERS) ? input_players[p].x : 0.0f;
}

static float input_get_z(int p)
{
    return (p >= 0 && p < MAX_PLAYERS) ? input_players[p].z : 0.0f;
}

static float input_get_r(int p)
{
    return (p >= 0 && p < MAX_PLAYERS) ? input_players[p].r : 0.0f;
}

static int input_get_c(int p)
{
    return (p >= 0 && p < MAX_PLAYERS) ? input_players[p].c : 0;
}

static int input_get_action(int p)
{
    return (p >= 0 && p < MAX_PLAYERS) ? input_players[p].action : 0;
}

/*---------------------------------------------------------------------------*/

/* Target Zones Configuration */
static const struct target_zone zones[] = {
    {  2.0f, 500, { 1.0f, 0.0f, 0.0f, 0.5f } }, /* Red Bullseye */
    {  5.0f, 300, { 1.0f, 1.0f, 0.0f, 0.5f } }, /* Yellow Inner */
    { 10.0f, 100, { 0.0f, 0.0f, 1.0f, 0.5f } }, /* Blue Outer */
    { 15.0f,  50, { 1.0f, 1.0f, 1.0f, 0.5f } }  /* White Edge */
};

int game_get_zone_count(void)
{
    return sizeof(zones) / sizeof(zones[0]);
}

const struct target_zone *game_get_zones(void)
{
    return zones;
}

/*---------------------------------------------------------------------------*/

static union cmd cmd;

static void game_cmd_map(const char *name, int ver_x, int ver_y)
{
    cmd.type          = CMD_MAP;
    cmd.map.name      = strdup(name);
    cmd.map.version.x = ver_x;
    cmd.map.version.y = ver_y;
    game_proxy_enq(&cmd);
}

static void game_cmd_eou(void)
{
    cmd.type = CMD_END_OF_UPDATE;
    game_proxy_enq(&cmd);
}

static void game_cmd_ups(void)
{
    cmd.type  = CMD_UPDATES_PER_SECOND;
    cmd.ups.n = UPS;
    game_proxy_enq(&cmd);
}

static void game_cmd_sound(const char *filename, float a)
{
    cmd.type = CMD_SOUND;

    cmd.sound.n = strdup(filename);
    cmd.sound.a = a;

    game_proxy_enq(&cmd);
}

#define audio_play(s, f) game_cmd_sound((s), (f))

static void game_cmd_set_player(int p)
{
    cmd.type = CMD_SET_PLAYER;
    cmd.setplayer.player_index = p;
    game_proxy_enq(&cmd);
}

static void game_cmd_goalopen(int p)
{
    game_cmd_set_player(p);
    cmd.type = CMD_GOAL_OPEN;
    game_proxy_enq(&cmd);
}

static void game_cmd_updball(int p)
{
    struct server_player *pl = &players[p];
    struct v_ball *b = &pl->sim_state->uv[pl->ball_index];

    game_cmd_set_player(p);

    cmd.type = CMD_CURRENT_BALL;
    cmd.currball.ui = pl->ball_index;
    game_proxy_enq(&cmd);

    cmd.type = CMD_BALL_POSITION;
    v_cpy(cmd.ballpos.p, b->p);
    game_proxy_enq(&cmd);

    cmd.type = CMD_BALL_BASIS;
    v_cpy(cmd.ballbasis.e[0], b->e[0]);
    v_cpy(cmd.ballbasis.e[1], b->e[1]);
    game_proxy_enq(&cmd);

    cmd.type = CMD_BALL_PEND_BASIS;
    v_cpy(cmd.ballpendbasis.E[0], b->E[0]);
    v_cpy(cmd.ballpendbasis.E[1], b->E[1]);
    game_proxy_enq(&cmd);
}

/* Update ALL balls for the given player's view */
static void game_cmd_upd_all_balls(int p)
{
    struct server_player *pl = &players[p];
    int i;

    for (i = 0; i < pl->sim_state->uc; i++)
    {
        struct v_ball *b = &pl->sim_state->uv[i];

        game_cmd_set_player(p);

        cmd.type = CMD_CURRENT_BALL;
        cmd.currball.ui = i;
        game_proxy_enq(&cmd);

        cmd.type = CMD_BALL_POSITION;
        v_cpy(cmd.ballpos.p, b->p);
        game_proxy_enq(&cmd);

        cmd.type = CMD_BALL_BASIS;
        v_cpy(cmd.ballbasis.e[0], b->e[0]);
        v_cpy(cmd.ballbasis.e[1], b->e[1]);
        game_proxy_enq(&cmd);

        cmd.type = CMD_BALL_PEND_BASIS;
        v_cpy(cmd.ballpendbasis.E[0], b->E[0]);
        v_cpy(cmd.ballpendbasis.E[1], b->E[1]);
        game_proxy_enq(&cmd);
    }
}

static void game_cmd_updview(int p)
{
    game_cmd_set_player(p);

    cmd.type = CMD_VIEW_POSITION;
    v_cpy(cmd.viewpos.p, players[p].view.p);
    game_proxy_enq(&cmd);

    cmd.type = CMD_VIEW_CENTER;
    v_cpy(cmd.viewcenter.c, players[p].view.c);
    game_proxy_enq(&cmd);

    cmd.type = CMD_VIEW_BASIS;
    v_cpy(cmd.viewbasis.e[0], players[p].view.e[0]);
    v_cpy(cmd.viewbasis.e[1], players[p].view.e[1]);
    game_proxy_enq(&cmd);
}

static void game_cmd_ballradius(int p)
{
    struct server_player *pl = &players[p];

    /* Sync ALL ball radii */
    int i;
    for (i = 0; i < pl->sim_state->uc; i++) {
        game_cmd_set_player(p);
        cmd.type = CMD_CURRENT_BALL;
        cmd.currball.ui = i;
        game_proxy_enq(&cmd);

        cmd.type = CMD_BALL_RADIUS;
        cmd.ballradius.r = pl->sim_state->uv[i].r;
        game_proxy_enq(&cmd);
    }
}

static void game_cmd_init_balls(int p, int count)
{
    int i;
    game_cmd_set_player(p);
    cmd.type = CMD_CLEAR_BALLS;
    game_proxy_enq(&cmd);

    for (i = 0; i < count; i++) {
        cmd.type = CMD_MAKE_BALL;
        game_proxy_enq(&cmd);
    }

    game_cmd_upd_all_balls(p);
    game_cmd_ballradius(p);
}

static void game_cmd_pkitem(int p, int hi)
{
    game_cmd_set_player(p);
    cmd.type      = CMD_PICK_ITEM;
    cmd.pkitem.hi = hi;
    game_proxy_enq(&cmd);
}

static void game_cmd_jump(int p, int e)
{
    game_cmd_set_player(p);
    cmd.type = e ? CMD_JUMP_ENTER : CMD_JUMP_EXIT;
    game_proxy_enq(&cmd);
}

static void game_cmd_punch(int p, int e)
{
    game_cmd_set_player(p);
    cmd.type = CMD_PUNCH;
    cmd.punch.active = e;
    game_proxy_enq(&cmd);
}

static void game_cmd_tiltangles(int p)
{
    game_cmd_set_player(p);
    cmd.type = CMD_TILT_ANGLES;

    cmd.tiltangles.x = players[p].tilt.rx;
    cmd.tiltangles.z = players[p].tilt.rz;

    game_proxy_enq(&cmd);
}

static void game_cmd_tiltaxes(int p)
{
    game_cmd_set_player(p);
    cmd.type = CMD_TILT_AXES;

    v_cpy(cmd.tiltaxes.x, players[p].tilt.x);
    v_cpy(cmd.tiltaxes.z, players[p].tilt.z);

    game_proxy_enq(&cmd);
}

static void game_cmd_timer(int p)
{
    game_cmd_set_player(p);
    cmd.type    = CMD_TIMER;
    cmd.timer.t = players[p].timer;
    game_proxy_enq(&cmd);
}

static void game_cmd_coins(int p)
{
    game_cmd_set_player(p);
    cmd.type    = CMD_COINS;
    cmd.coins.n = players[p].coins;
    game_proxy_enq(&cmd);
}

static void game_cmd_status(int p)
{
    game_cmd_set_player(p);
    cmd.type     = CMD_STATUS;
    cmd.status.t = players[p].status;
    game_proxy_enq(&cmd);
}

/*---------------------------------------------------------------------------*/

static int grow_init(int p, int type)
{
    struct server_player *pl = &players[p];
    struct v_ball *up = &pl->sim_state->uv[pl->ball_index];

    int size = up->size;

    if (type == ITEM_SHRINK)
        size--;
    else if (type == ITEM_GROW)
        size++;

    size = CLAMP(0, size, 2);

    if (size != up->size)
    {
        const int old_size = up->size;

        up->r_vel = (up->sizes[size] - up->r) / GROW_TIME;
        up->size = size;

        if (size < old_size)
            return -1;

        if (size > old_size)
            return +1;
    }

    return 0;
}

static void grow_step(int p, float dt)
{
    struct server_player *pl = &players[p];
    struct v_ball *up = &pl->sim_state->uv[pl->ball_index];

    if (up->r_vel != 0.0f)
    {
        float r, dr;

        r = up->r + up->r_vel * dt;

        if ((up->r < up->sizes[up->size] && r >= up->sizes[up->size]) ||
            (up->r > up->sizes[up->size] && r <= up->sizes[up->size]))
        {
            r = up->sizes[up->size];
            up->r_vel = 0.0f;
        }

        dr = r - up->r;

        up->p[1] += dr;
        up->r     = r;

        game_cmd_ballradius(p);
    }
}

/*---------------------------------------------------------------------------*/

static struct lockstep server_step;

static void game_player_init(int p, int t, int e, int mode)
{
    struct server_player *pl = &players[p];
    int i;
    int ball_count = 1;

    pl->time_limit = (float) t / 100.0f;
    pl->time_elapsed = 0.0f;
    pl->timer = 0.0f;
    pl->status = GAME_NONE;
    pl->coins = 0;

    pl->fly_active = 0;
    pl->fly_done = 0;
    pl->fly_pitch = 0.0f;

    pl->punch_state = 0;
    pl->punch_timer = 0.0f;

    pl->shot_power = 0.0f;

    pl->action_prev = 0;

    pl->bowling_frame = 1;
    pl->bowling_throw = 1;
    for(i=0; i<10; i++) pl->bowling_pins[i] = 0;
    pl->shot_state = 0;

    pl->warp_id = -1;

    if (mode == MODE_BATTLE || mode == MODE_TARGET || mode == MODE_FIGHT)
    {
        ball_count = player_count;
        if (p == 0)
        {
            /* Master simulation */
            sol_load_vary(&pl->vary, &game_base);
            pl->sim_state = &pl->vary;
            pl->sim_owner = 1;

            /* Resize balls */
            if (ball_count > 1)
            {
                 struct v_ball *new_uv = realloc(pl->vary.uv, sizeof(struct v_ball) * ball_count);
                 if (new_uv)
                 {
                     pl->vary.uv = new_uv;
                     for (i = 1; i < ball_count; i++)
                     {
                         pl->vary.uv[i] = pl->vary.uv[0];
                         pl->vary.uv[i].p[0] += (float)i * 1.5f;
                         pl->vary.uv[i].p[2] += (float)i * 1.5f;
                     }
                     pl->vary.uc = ball_count;
                 }
            }
        }
        else
        {
            /* Slave */
            pl->sim_state = &players[0].vary;
            pl->sim_owner = 0;
        }
        pl->ball_index = p;
    }
    else if (mode == MODE_BILLIARDS)
    {
        ball_count = 16;
        if (p == 0)
        {
            sol_load_vary(&pl->vary, &game_base);
            pl->sim_state = &pl->vary;
            pl->sim_owner = 1;

            /* Resize balls */
            struct v_ball *new_uv = realloc(pl->vary.uv, sizeof(struct v_ball) * ball_count);
            if (new_uv)
            {
                pl->vary.uv = new_uv;
                pl->vary.uc = ball_count;

                /* Init Billiard Positions (Triangle) */
                float x = pl->vary.uv[0].p[0];
                float z = pl->vary.uv[0].p[2] + 5.0f; /* Start further down */
                float r = pl->vary.uv[0].r;
                float d = r * 2.05f; /* Diameter + padding */

                int b = 1;
                int row, col;
                for (row = 0; row < 5; row++) {
                    float z_row = z + row * d * 0.866f; /* sin(60) */
                    float x_start = x - (row * d) * 0.5f;
                    for (col = 0; col <= row; col++) {
                        if (b < ball_count) {
                            pl->vary.uv[b] = pl->vary.uv[0];
                            pl->vary.uv[b].p[0] = x_start + col * d;
                            pl->vary.uv[b].p[2] = z_row;
                            b++;
                        }
                    }
                }
            }
        }
        else
        {
            pl->sim_state = &players[0].vary;
            pl->sim_owner = 0;
        }
        pl->ball_index = 0;
    }
    else if (mode == MODE_BOWLING)
    {
        ball_count = 11; /* 1 Player + 10 Pins */
        if (p == 0)
        {
            sol_load_vary(&pl->vary, &game_base);
            pl->sim_state = &pl->vary;
            pl->sim_owner = 1;

            struct v_ball *new_uv = realloc(pl->vary.uv, sizeof(struct v_ball) * ball_count);
            if (new_uv)
            {
                pl->vary.uv = new_uv;
                pl->vary.uc = ball_count;

                /* Setup Pins (Triangle) at end of lane */
                /* Assuming standard lane length, e.g. 20m? */
                /* Base position for pins */
                float x = pl->vary.uv[0].p[0];
                float z = pl->vary.uv[0].p[2] + 20.0f;
                float r = pl->vary.uv[0].r;
                float d = r * 2.5f; /* Pins spaced out a bit */

                int b = 1;
                int row, col;
                for (row = 0; row < 4; row++) { /* 4 rows for 10 pins */
                    float z_row = z + row * d * 0.866f;
                    float x_start = x - (row * d) * 0.5f;
                    for (col = 0; col <= row; col++) {
                         if (b < ball_count) {
                            pl->vary.uv[b] = pl->vary.uv[0];
                            pl->vary.uv[b].p[0] = x_start + col * d;
                            pl->vary.uv[b].p[2] = z_row;

                            /* Store start pos */
                            v_cpy(pl->bowling_pin_start[b-1], pl->vary.uv[b].p);
                            b++;
                         }
                    }
                }
            }
        }
        else
        {
            pl->sim_state = &players[0].vary;
            pl->sim_owner = 0;
        }
        pl->ball_index = 0;
    }
    else
    {
        /* Race / Independent */
        ball_count = 1;
        sol_load_vary(&pl->vary, &game_base);
        pl->sim_state = &pl->vary;
        pl->sim_owner = 1;
        pl->ball_index = 0;

        if (p > 0)
        {
            pl->vary.uv[0].p[0] += (float)p * 1.5f;
            pl->vary.uv[0].p[2] += (float)p * 1.5f;
        }
    }

    game_tilt_init(&pl->tilt);

    pl->jump_e = 1;
    pl->jump_b = 0;
    pl->goal_e = e ? 1 : 0;

    game_view_fly(&pl->view, pl->sim_state, 0.0f);

    v_cpy(pl->start_p, pl->sim_state->uv[pl->ball_index].p);

    pl->view_k = 1.0f;
    pl->view_time = 0.0f;
    pl->view_fade = 0.0f;
    pl->view_zoom_curr = 1.0f;
    pl->view_zoom_time = ZOOM_TIME;

    if (pl->sim_owner)
        sol_init_sim(pl->sim_state);

    game_cmd_timer(p);
    if (pl->goal_e) game_cmd_goalopen(p);
    game_cmd_init_balls(p, ball_count);
    game_cmd_updview(p);
}

int game_server_init(const char *file_name, int t, int e, int mode)
{
    struct { int x, y; } version;
    int i, p;

    game_server_free(file_name);

    if (!game_base_load(file_name))
        return (server_state = 0);

    player_count = config_get_d(CONFIG_MULTIBALL);
    if (player_count < 1) player_count = 1;
    if (player_count > MAX_PLAYERS) player_count = MAX_PLAYERS;

    server_state = 1;
    game_mode = mode;

    version.x = 0;
    version.y = 0;

    for (i = 0; i < game_base.dc; i++)
    {
        char *k = game_base.av + game_base.dv[i].ai;
        char *v = game_base.av + game_base.dv[i].aj;

        if (strcmp(k, "version") == 0)
            sscanf(v, "%d.%d", &version.x, &version.y);
    }

    input_init();

    game_cmd_map(file_name, version.x, version.y);
    game_cmd_ups();

    for (p = 0; p < player_count; p++)
    {
        game_player_init(p, t, e, mode);
    }

    game_cmd_eou();

    lockstep_clr(&server_step);

    return server_state;
}

void game_server_free(const char *next)
{
    int p;
    if (server_state)
    {
        sol_quit_sim();

        for (p = 0; p < player_count; p++)
        {
            if (players[p].sim_owner)
                sol_free_vary(&players[p].vary);
        }

        game_base_free(next);

        server_state = 0;
    }
}

/*---------------------------------------------------------------------------*/

static void game_update_view(int p, float dt)
{
    struct server_player *pl = &players[p];
    struct v_ball *b = &pl->sim_state->uv[pl->ball_index];

    /* Current view scale. */

    if (pl->view_zoom_time < ZOOM_TIME)
    {
        pl->view_zoom_time += dt;

        if (pl->view_zoom_time >= ZOOM_TIME)
        {
            pl->view_zoom_time = ZOOM_TIME;
            pl->view_zoom_curr = pl->view_zoom_end;
            pl->view_zoom_end = 0.0f;
        }
        else if (pl->view_zoom_time >= ZOOM_DELAY)
        {
            float a = (pl->view_zoom_time - ZOOM_DELAY) / (ZOOM_TIME - ZOOM_DELAY);

            a = easeInOutBack(a);

            pl->view_zoom_curr = pl->view_zoom_start + (pl->view_zoom_end - pl->view_zoom_start) * a;
        }
    }

    float SCL = pl->view_zoom_curr;

    float dc = pl->view.dc * (pl->jump_b > 0 ? 2.0f * fabsf(pl->jump_dt - 0.5f) : 1.0f);
    float da = 90.0f * input_get_r(p) * dt;
    float k;

    float M[16], v[3], Y[3] = { 0.0f, 1.0f, 0.0f };
    float view_v[3];

    float spd = (float) cam_speed(input_get_c(p)) / 1000.0f;

    /* Track manual rotation time. */

    if (da == 0.0f)
    {
        if (pl->view_time < 0.0f)
        {
            pl->view_fade = CLAMP(VIEW_FADE_MIN, -pl->view_time, VIEW_FADE_MAX);
            pl->view_time = 0.0f;
        }
        pl->view_time += dt;
    }
    else
    {
        if (pl->view_time > 0.0f)
        {
            pl->view_fade = 0.0f;
            pl->view_time = 0.0f;
        }
        pl->view_time -= dt;
    }

    /* Center the view about the ball. */

    v_cpy(pl->view.c, b->p);

    view_v[0] = -b->v[0];
    view_v[1] =  0.0f;
    view_v[2] = -b->v[2];

    /* Compute view vector. */

    if (spd >= 0.0f)
    {
        if (da == 0.0f)
        {
            float s;

            v_sub(pl->view.e[2], pl->view.p, pl->view.c);
            v_nrm(pl->view.e[2], pl->view.e[2]);

            s = fpowf(pl->view_time, 3.0f) / fpowf(pl->view_fade, 3.0f);
            s = CLAMP(0.0f, s, 1.0f);

            v_mad(pl->view.e[2], pl->view.e[2], view_v, v_len(view_v) * spd * s * dt);
        }
    }
    else
    {
        pl->view.e[2][0] = fsinf(V_RAD(pl->view.a));
        pl->view.e[2][1] = 0.0;
        pl->view.e[2][2] = fcosf(V_RAD(pl->view.a));
    }

    if (da != 0.0f)
    {
        m_rot(M, Y, V_RAD(da));
        m_vxfm(v, M, pl->view.e[2]);
        v_cpy(pl->view.e[2], v);
    }

    /* Arcade Camera Snap */
    if (config_get_d(CONFIG_PHYSICS))
    {
        float speed = v_len(b->v);
        if (speed > 5.0f)
        {
            float vel_n[3];
            v_cpy(vel_n, b->v);
            v_nrm(vel_n, vel_n);

            float target_n[3];
            v_scl(target_n, vel_n, -1.0f);

            v_lerp(pl->view.e[2], pl->view.e[2], target_n, 5.0f * dt);
            v_nrm(pl->view.e[2], pl->view.e[2]);
        }
    }

    v_crs(pl->view.e[0], pl->view.e[1], pl->view.e[2]);
    v_crs(pl->view.e[2], pl->view.e[0], pl->view.e[1]);
    v_nrm(pl->view.e[0], pl->view.e[0]);
    v_nrm(pl->view.e[2], pl->view.e[2]);

    k = 1.0f + v_dot(pl->view.e[2], view_v) / 10.0f;

    pl->view_k = pl->view_k + (k - pl->view_k) * dt;

    if (pl->view_k < 0.5f) pl->view_k = 0.5;

    v_scl(v,    pl->view.e[1], SCL * pl->view.dp * pl->view_k);
    v_mad(v, v, pl->view.e[2], SCL * pl->view.dz * pl->view_k);
    v_add(pl->view.p, v, b->p);

    v_cpy(pl->view.c, b->p);
    v_mad(pl->view.c, pl->view.c, pl->view.e[1], SCL * dc);

    pl->view.a = V_DEG(fatan2f(pl->view.e[2][0], pl->view.e[2][2]));

    game_cmd_updview(p);
}

static void game_update_time(int p, float dt, int b)
{
    struct server_player *pl = &players[p];
    if (b)
    {
        pl->time_elapsed += dt;

        if (pl->time_limit > 0.0f && pl->time_elapsed > pl->time_limit)
            pl->time_elapsed = pl->time_limit;

        pl->timer = fabsf(pl->time_limit - pl->time_elapsed);

        game_cmd_timer(p);
    }
}

static void zoom_init(int p, float target)
{
    struct server_player *pl = &players[p];
    pl->view_zoom_time = 0.0f;
    pl->view_zoom_start = pl->view_zoom_curr;
    pl->view_zoom_end = CLAMP(ZOOM_MIN, target, ZOOM_MAX);
}

static int game_update_state(int p, int bt)
{
    struct server_player *pl = &players[p];
    struct b_goal *zp;
    int hi;

    /* Test for an item. */

    if (bt && (hi = sol_item_test(pl->sim_state, NULL, ITEM_RADIUS)) != -1)
    {
        struct v_item *hp = pl->sim_state->hv + hi;

        game_cmd_pkitem(p, hi);

        if (hp->t == ITEM_COIN)
        {
            pl->coins += hp->n;
            game_cmd_coins(p);
        }
        else if (hp->t == ITEM_CLOCK)
        {
            const float value = (float) hp->n;

            audio_play(AUD_CLOCK, 1.f);

            if (pl->time_limit > 0.0f)
                pl->time_limit = pl->time_limit + value;
            else
                pl->time_elapsed = MAX(0.0f, pl->time_elapsed - value);

            game_update_time(p, 0.0f, bt);
        }
        else if (hp->t == ITEM_GROW || hp->t == ITEM_SHRINK)
        {
            switch (grow_init(p, hp->t))
            {
                case -1:
                    audio_play(AUD_SHRINK, 1.0f);
                    zoom_init(p, pl->sim_state->uv->sizes[pl->sim_state->uv->size] / pl->sim_state->uv->sizes[1]);
                    break;

                case +1:
                    audio_play(AUD_GROW, 1.0f);
                    zoom_init(p, pl->sim_state->uv->sizes[pl->sim_state->uv->size] / pl->sim_state->uv->sizes[1]);
                    break;

                case 0:
                    break;
            }
        }
        else if (hp->t == ITEM_SPEED)
        {
            /* Speed Boost */
            struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
            float fwd[3];
            if (v_len(b->v) > 0.1f) {
                v_cpy(fwd, b->v);
                v_nrm(fwd, fwd);
                v_mad(b->v, b->v, fwd, 15.0f);
            }
            audio_play(AUD_JUMP, 1.0f);
        }
        else if (hp->t == ITEM_MISSILE)
        {
            audio_play(AUD_COIN, 1.f);
        }
        else if (hp->t == ITEM_BANANA)
        {
            audio_play(AUD_FALL, 1.f);
        }

        audio_play(AUD_COIN, 1.f);

        hp->t = ITEM_NONE;
    }

    /* Test for a switch. */

    if (sol_swch_test(pl->sim_state, game_proxy_enq, 0) == SWCH_INSIDE)
        audio_play(AUD_SWITCH, 1.f);

    /* Test for a jump. */

    if (pl->jump_e == 1 && pl->jump_b == 0 && (sol_jump_test(pl->sim_state, pl->jump_p, 0) ==
                                       JUMP_INSIDE))
    {
        pl->jump_b  = 1;
        pl->jump_e  = 0;
        pl->jump_dt = 0.f;

        audio_play(AUD_JUMP, 1.f);

        game_cmd_jump(p, 1);
    }
    if (pl->jump_e == 0 && pl->jump_b == 0 && (sol_jump_test(pl->sim_state, pl->jump_p, 0) ==
                                       JUMP_OUTSIDE))
    {
        pl->jump_e = 1;
        game_cmd_jump(p, 0);
    }

    /* Test for a goal. */

    if (bt && pl->goal_e && (zp = sol_goal_test(pl->sim_state, NULL, 0)))
    {
        audio_play(AUD_GOAL, 1.0f);
        return GAME_GOAL;
    }

    /* Test for time-out. */

    if (bt && pl->time_limit > 0.0f && pl->time_elapsed >= pl->time_limit)
    {
        audio_play(AUD_TIME, 1.0f);
        return GAME_TIME;
    }

    /* Test for fall-out. */

    if (bt && (pl->sim_state->base->vc == 0 || pl->sim_state->uv[pl->ball_index].p[1] < pl->sim_state->base->vv[0].p[1]))
    {
        audio_play(AUD_FALL, 1.0f);
        return GAME_FALL;
    }

    return GAME_NONE;
}

static void game_fly_step(int p, float dt)
{
    struct server_player *pl = &players[p];
    struct v_ball *b = &pl->sim_state->uv[pl->ball_index];

    /* Control Pitch */
    float z_input = input_get_z(p) / ANGLE_BOUND; /* Normalize to -1..1 range approximately */
    /* If Stick Up (Forward), Pitch Down. If Stick Down (Back), Pitch Up. */

    pl->fly_pitch += z_input * 2.0f * dt; /* 2 degrees per second? */
    pl->fly_pitch = CLAMP(-45.0f, pl->fly_pitch, 45.0f);

    /* Physics */
    float speed = v_len(b->v);

    if (speed > 1.0f)
    {
        float lift_dir[3] = { 0.0f, 1.0f, 0.0f }; /* Up for now. */

        float lift_force = speed * speed * 0.05f * (pl->fly_pitch + 10.0f); /* Bias +10 deg */
        float drag_force = speed * speed * 0.01f;

        float drag_vec[3];
        v_cpy(drag_vec, b->v);
        v_nrm(drag_vec, drag_vec);
        v_scl(drag_vec, drag_vec, -drag_force);

        float lift_vec[3];
        v_scl(lift_vec, lift_dir, lift_force);

        /* Apply forces directly to velocity */
        v_mad(b->v, b->v, drag_vec, dt);
        v_mad(b->v, b->v, lift_vec, dt);
    }
}

static void game_fight_step(int p, float dt)
{
    struct server_player *pl = &players[p];

    if (input_get_action(p) && !pl->action_prev && pl->punch_state == 0) {
        pl->punch_state = 1;
        pl->punch_timer = 0.0f;
        game_cmd_punch(p, 1);
        audio_play(AUD_JUMP, 1.0f); /* Sound */
    }

    if (pl->punch_state == 1) {
        pl->punch_timer += dt;
        if (pl->punch_timer > 0.2f) { /* Extension time */
            pl->punch_state = 2;
        }

        /* Hit detection */
        int i;
        struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
        float punch_range = b->r * 2.0f;
        float punch_vec[3];

        v_cpy(punch_vec, pl->view.e[2]);
        v_scl(punch_vec, punch_vec, -1.0f);

        for (i = 0; i < pl->sim_state->uc; i++) {
            if (i == pl->ball_index) continue;

            struct v_ball *other = &pl->sim_state->uv[i];
            float dist_vec[3];
            v_sub(dist_vec, other->p, b->p);
            float dist = v_len(dist_vec);

            if (dist < (b->r + other->r + punch_range)) {
                float d = v_dot(punch_vec, dist_vec);
                if (d > 0) {
                    /* HIT */
                    float force[3];
                    v_cpy(force, punch_vec);
                    v_scl(force, force, 20.0f * dt);
                    v_add(other->v, other->v, force);

                    audio_play(AUD_BUMPL, 1.0f);
                }
            }
        }

    }
    else if (pl->punch_state == 2) {
        pl->punch_timer -= dt;
        if (pl->punch_timer <= 0.0f) {
            pl->punch_state = 0;
            game_cmd_punch(p, 0);
        }
    }
}

static void game_billiards_step(int p, float dt)
{
    struct server_player *pl = &players[p];
    int i;

    /* Billiards Logic */

    int action = input_get_action(p);

    if (action) {
        /* Charging */
        pl->shot_power += dt * 2.0f;
        if (pl->shot_power > 1.0f) pl->shot_power = 1.0f;
    } else {
        if (pl->shot_power > 0.0f) {
            /* Release - Shoot */
            struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
            float fwd[3];
            /* View Forward = -e[2] */
            v_cpy(fwd, pl->view.e[2]);
            v_scl(fwd, fwd, -1.0f);

            float force = pl->shot_power * 30.0f; /* Max speed */
            v_mad(b->v, b->v, fwd, force);

            audio_play(AUD_BUMPL, pl->shot_power);

            pl->shot_power = 0.0f;
        }
    }

    /* Friction */
    for (i = 0; i < pl->sim_state->uc; i++) {
        struct v_ball *b = &pl->sim_state->uv[i];
        if (v_len(b->v) > 0.0f) {
             v_scl(b->v, b->v, 0.99f);
             if (v_len(b->v) < 0.05f) v_zero(b->v);
        }
    }

    /* Pocket Detection */
    struct s_vary *vary = pl->sim_state;
    if (vary->base->zc > 0) {
        for (i = 0; i < vary->uc; i++) {
            struct v_ball *b = &vary->uv[i];
            struct b_goal *goal = &vary->base->zv[0];

            float d[3];
            v_sub(d, b->p, goal->p);
            if (v_len(d) < (b->r + goal->r)) {
                if (i == 0) {
                    /* Scratch */
                    audio_play(AUD_FALL, 1.0f);
                    v_cpy(b->p, pl->start_p);
                    v_zero(b->v);
                } else {
                    /* Scored */
                    b->p[1] = -1000.0f; /* Remove */
                    v_zero(b->v);

                    pl->coins += 100;
                    game_cmd_coins(p);
                    audio_play(AUD_GOAL, 1.0f);
                }
            }
        }
    }
}

static void game_bowling_step(int p, float dt)
{
    struct server_player *pl = &players[p];

    if (pl->shot_state == 0)
    {
        float dx = input_get_x(p);
        struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
        b->p[0] += dx * 5.0f * dt;

        if (b->p[0] < -5.0f) b->p[0] = -5.0f;
        if (b->p[0] >  5.0f) b->p[0] =  5.0f;

        if (input_get_action(p)) {
             pl->shot_state = 1;
             pl->shot_power = 0.0f;
        }
    }
    else if (pl->shot_state == 1)
    {
        pl->shot_power += dt * 2.0f;
        if (pl->shot_power > 1.0f) pl->shot_power = 1.0f;

        if (!input_get_action(p)) {
            pl->shot_state = 2;
            struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
            float fwd[3] = {0,0,1};

            float force = pl->shot_power * 40.0f;
            v_mad(b->v, b->v, fwd, force);
            audio_play(AUD_BUMPL, pl->shot_power);
        }
    }
    else if (pl->shot_state == 2)
    {
        int moving = 0;
        int i;
        for (i = 0; i < pl->sim_state->uc; i++) {
            struct v_ball *b = &pl->sim_state->uv[i];

             v_scl(b->v, b->v, 0.99f);
             if (v_len(b->v) < 0.05f) v_zero(b->v);
             else moving = 1;
        }

        if (!moving) {
             int pins_down = 0;
             for (i = 1; i < pl->sim_state->uc; i++) {
                 struct v_ball *b = &pl->sim_state->uv[i];
                 float d[3];
                 v_sub(d, b->p, pl->bowling_pin_start[i-1]);
                 if (v_len(d) > 0.5f) {
                     pins_down++;
                     b->p[1] = -1000.0f;
                 }
             }

             int new_points = pins_down;
             pl->coins = new_points * 100;
             game_cmd_coins(p);

             if (pins_down == 10 || pl->bowling_throw == 2) {
                 pl->bowling_frame++;
                 pl->bowling_throw = 1;
                 game_respawn(p);
                 for (i = 1; i < pl->sim_state->uc; i++) {
                     v_cpy(pl->sim_state->uv[i].p, pl->bowling_pin_start[i-1]);
                     v_zero(pl->sim_state->uv[i].v);
                 }
             } else {
                 pl->bowling_throw++;
                 v_cpy(pl->sim_state->uv[0].p, pl->start_p);
                 v_zero(pl->sim_state->uv[0].v);
             }

             pl->shot_state = 0;
        }
    }
}

static void game_hub_step(int p, float dt)
{
    struct server_player *pl = &players[p];
    struct s_vary *vary = pl->sim_state;
    int i;

    /* Check Switches for Warp */
    for (i = 0; i < vary->xc; i++) {
        struct v_swch *xp = vary->xv + i;
        struct v_ball *b = &vary->uv[pl->ball_index];
        float d[3];
        v_sub(d, b->p, xp->base->p);

        /* Simple check radius */
        if (v_len(d) < (b->r + xp->base->r)) {
             pl->status = GAME_WARP;
             pl->warp_id = i;
             game_cmd_status(p);
             return;
        }
    }
}

static int game_step(int p, const float g[3], float dt, int bt)
{
    struct server_player *pl = &players[p];
    if (server_state)
    {
        float h[3];
        int i;

        /* Toggle Flight */
        int action = input_get_action(p);
        if (action && !pl->action_prev)
        {
            if (game_mode == MODE_TARGET)
            {
                if (!pl->fly_active && !pl->fly_done)
                {
                    pl->fly_active = 1;
                    pl->fly_pitch = 0.0f;
                    audio_play(AUD_JUMP, 1.0f); /* Feedback */
                }
                else if (pl->fly_active)
                {
                    pl->fly_active = 0;
                    pl->fly_done = 1; /* Locked */
                }
            }
        }

        if (game_mode == MODE_FIGHT)
        {
            game_fight_step(p, dt);
        }
        else if (game_mode == MODE_BILLIARDS)
        {
            game_billiards_step(p, dt);
        }
        else if (game_mode == MODE_BOWLING)
        {
            game_bowling_step(p, dt);
        }
        else if (game_mode == MODE_HUB)
        {
            game_hub_step(p, dt);
        }

        pl->action_prev = action;

        if (pl->fly_active)
        {
            /* Flight Mode */
            game_fly_step(p, dt);

            /* Disable board tilt input, dampen existing tilt */
            pl->tilt.rx *= 0.9f;
            pl->tilt.rz *= 0.9f;
        }
        else if (game_mode == MODE_BILLIARDS || game_mode == MODE_BOWLING)
        {
            /* No board tilt */
            pl->tilt.rx = 0.0f;
            pl->tilt.rz = 0.0f;
        }
        else
        {
            /* Normal Tilt */
            pl->tilt.rx += (input_get_x(p) - pl->tilt.rx) * dt / MAX(dt, input_get_s(p));
            pl->tilt.rz += (input_get_z(p) - pl->tilt.rz) * dt / MAX(dt, input_get_s(p));
        }

        /* Monkey Target Landing Logic */
        if (game_mode == MODE_TARGET && !pl->fly_active)
        {
             if (pl->fly_done || pl->time_elapsed > 3.0f)
             {
                 struct v_ball *b = &pl->sim_state->uv[pl->ball_index];
                 float speed = v_len(b->v);

                 /* If speed is very low and we are not falling */
                 if (speed < 0.05f)
                 {
                     /* Landed */
                     float dist = sqrtf(b->p[0] * b->p[0] + b->p[2] * b->p[2]);
                     int points = 0;
                     int j;
                     int count = game_get_zone_count();
                     const struct target_zone *z = game_get_zones();

                     for (j = 0; j < count; j++) {
                         if (dist <= z[j].radius) {
                             points = z[j].score;
                             break;
                         }
                     }

                     if (pl->status == GAME_NONE)
                     {
                         pl->coins += points;
                         game_cmd_coins(p);
                         return GAME_GOAL;
                     }
                 }
             }
        }

        game_tilt_axes(&pl->tilt, pl->view.e);

        game_cmd_tiltaxes(p);
        game_cmd_tiltangles(p);

        grow_step(p, dt);

        game_tilt_grav(h, g, &pl->tilt);

        if (pl->jump_b > 0)
        {
            pl->jump_dt += dt;

            if (pl->jump_dt >= 0.5f)
            {
                if (pl->jump_b == 1)
                {
                    float dp[3];

                    v_sub(dp, pl->jump_p, pl->sim_state->uv[pl->ball_index].p);
                    v_add(pl->view.p, pl->view.p, dp);

                    pl->jump_b = 2;
                }

                v_cpy(pl->sim_state->uv[pl->ball_index].p, pl->jump_p);
            }

            if (pl->jump_dt >= 1.0f)
                pl->jump_b = 0;
        }
        else
        {
            /* Run the sim */
            if (pl->sim_owner)
            {
                /* Sync ALL balls position to clients */
                if (pl->sim_owner) {
                    game_cmd_upd_all_balls(p);
                }

                for (i = 0; i < pl->sim_state->uc; i++)
                {
                    float b = sol_step(pl->sim_state, game_proxy_enq, h, dt, i, NULL);

                    if (b > 0.5f)
                    {
                        float k = (b - 0.5f) * 2.0f;
                        if      (pl->sim_state->uv[i].r > pl->sim_state->uv[i].sizes[1]) audio_play(AUD_BUMPL, k);
                        else if (pl->sim_state->uv[i].r < pl->sim_state->uv[i].sizes[1]) audio_play(AUD_BUMPS, k);
                        else                                                             audio_play(AUD_BUMPM, k);
                    }
                }
            }
        }

        /* We already called game_cmd_upd_all_balls if owner */
        game_cmd_updball(p);

        game_update_view(p, dt);
        game_update_time(p, dt, bt);

        return game_update_state(p, bt);
    }
    return GAME_NONE;
}

static void game_server_iter(float dt)
{
    int p;
    for (p = 0; p < player_count; p++)
    {
        switch (players[p].status)
        {
        case GAME_GOAL: game_step(p, GRAVITY_UP, dt, 0); break;
        case GAME_FALL: game_step(p, GRAVITY_DN, dt, 0); break;

        case GAME_WARP:
            /* Halt processing for this player, waiting for client transition */
            break;

        case GAME_NONE:
            if ((players[p].status = game_step(p, GRAVITY_DN, dt, 1)) != GAME_NONE)
                game_cmd_status(p);
            break;
        }
    }

    game_cmd_eou();
}

static struct lockstep server_step = { game_server_iter, DT };

void game_server_step(float dt)
{
    lockstep_run(&server_step, dt);
}

float game_server_blend(void)
{
    return lockstep_blend(&server_step);
}

/*---------------------------------------------------------------------------*/

void game_set_goal(int p)
{
    audio_play(AUD_SWITCH, 1.0f);
    if (p >= 0 && p < MAX_PLAYERS)
    {
        players[p].goal_e = 1;
        game_cmd_goalopen(p);
    }
}

void game_respawn(int p)
{
    struct server_player *pl = &players[p];
    if (p >= 0 && p < MAX_PLAYERS)
    {
        v_cpy(pl->sim_state->uv[pl->ball_index].p, pl->start_p);
        v_scl(pl->sim_state->uv[pl->ball_index].v, pl->sim_state->uv[pl->ball_index].v, 0.0f);
        v_scl(pl->sim_state->uv[pl->ball_index].w, pl->sim_state->uv[pl->ball_index].w, 0.0f);

        pl->status = GAME_NONE;

        /* Reset flight state */
        pl->fly_active = 0;
        pl->fly_done = 0;
        pl->fly_pitch = 0.0f;

        pl->punch_state = 0;
        pl->punch_timer = 0.0f;

        pl->shot_power = 0.0f;

        game_view_fly(&pl->view, pl->sim_state, 0.0f);

        game_cmd_status(p);
        game_cmd_updball(p);
        game_cmd_updview(p);
    }
}

/*---------------------------------------------------------------------------*/

void game_set_x(float k, int p)
{
    input_set_x(p, -get_angle_bound() * k);
    input_set_s(p, config_get_d(CONFIG_JOYSTICK_RESPONSE) * 0.001f);
}

void game_set_z(float k, int p)
{
    input_set_z(p, +get_angle_bound() * k);
    input_set_s(p, config_get_d(CONFIG_JOYSTICK_RESPONSE) * 0.001f);
}

void game_set_ang(float x, float z, int p)
{
    input_set_x(p, x);
    input_set_z(p, z);
}

void game_set_pos(int x, int y, int p)
{
    const float range = ANGLE_BOUND * 2;

    input_set_x(p, input_get_x(p) + range * y / config_get_d(CONFIG_MOUSE_SENSE));
    input_set_z(p, input_get_z(p) + range * x / config_get_d(CONFIG_MOUSE_SENSE));

    input_set_s(p, config_get_d(CONFIG_MOUSE_RESPONSE) * 0.001f);
}

void game_set_cam(int c, int p)
{
    input_set_c(p, c);
}

void game_set_rot(float r, int p)
{
    input_set_r(p, r);
}

void game_set_action(int a, int p)
{
    input_set_action(p, a);
}

/*---------------------------------------------------------------------------*/

float curr_time_elapsed(int p)
{
    if (p >= 0 && p < MAX_PLAYERS)
        return players[p].time_elapsed;
    return 0.0f;
}

float curr_speed(int p)
{
    if (p >= 0 && p < MAX_PLAYERS)
    {
        struct v_ball *b = &players[p].sim_state->uv[players[p].ball_index];
        return v_len(b->v);
    }
    return 0.0f;
}

float curr_altitude(int p)
{
    if (p >= 0 && p < MAX_PLAYERS)
    {
        struct v_ball *b = &players[p].sim_state->uv[players[p].ball_index];
        return b->p[1];
    }
    return 0.0f;
}

/*---------------------------------------------------------------------------*/

int curr_warp_id(int p)
{
    if (p >= 0 && p < MAX_PLAYERS)
        return players[p].warp_id;
    return -1;
}

/*---------------------------------------------------------------------------*/
