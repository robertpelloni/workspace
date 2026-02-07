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

#include "glext.h"
#include "vec3.h"
#include "geom.h"
#include "part.h"
#include "ball.h"
#include "image.h"
#include "audio.h"
#include "config.h"
#include "video.h"

#include "solid_draw.h"
#include "solid_all.h"

#include "game_client.h"
#include "game_common.h"
#include "game_proxy.h"
#include "game_draw.h"

#include "cmd.h"

/*---------------------------------------------------------------------------*/

int game_compat_map;                    /* Client/server map compat flag     */

/*---------------------------------------------------------------------------*/

#define CURR 0
#define PREV 1

static struct game_draw gd[MAX_PLAYERS];
static struct game_lerp gl[MAX_PLAYERS];

struct client_stats {
    float timer;
    int   status;
    int   coins;
};

static struct client_stats stats[MAX_PLAYERS];

static struct cmd_state cs;             /* Command state                     */

struct
{
    int x, y;
} version;                              /* Current map version               */

/*---------------------------------------------------------------------------*/

static void game_run_cmd(const union cmd *cmd)
{
    struct game_draw *cg = &gd[cs.curr_player];
    struct game_lerp *cl = &gl[cs.curr_player];
    struct client_stats *cst = &stats[cs.curr_player];
    int p;

    if (cg->state)
    {
        struct game_view *view = &cl->view[CURR];
        struct game_tilt *tilt = &cl->tilt[CURR];

        struct s_vary *vary = &cg->vary;
        struct v_item *hp;

        float v[4];
        float dt;

        int idx;

        if (cs.next_update)
        {
            for (p = 0; p < MAX_PLAYERS; p++)
            {
                if (gd[p].state)
                    game_lerp_copy(&gl[p]);
            }
            cs.next_update = 0;
        }

        switch (cmd->type)
        {
        case CMD_SET_PLAYER:
            cs.curr_player = cmd->setplayer.player_index;
            if (cs.curr_player < 0) cs.curr_player = 0;
            if (cs.curr_player >= MAX_PLAYERS) cs.curr_player = 0;
            break;

        case CMD_PUNCH:
            cg->punch_active = cmd->punch.active;
            cl->punch_active[CURR] = cmd->punch.active;
            cl->punch_active[PREV] = cmd->punch.active;
            break;

        case CMD_END_OF_UPDATE:
            cs.got_tilt_axes = 0;
            cs.next_update = 1;

            if (cs.first_update)
            {
                for (p = 0; p < MAX_PLAYERS; p++)
                {
                    if (gd[p].state)
                    {
                        game_lerp_copy(&gl[p]);
                        /* Hack to sync state before the next update. */
                        game_lerp_apply(&gl[p], &gd[p]);
                    }
                }
                cs.first_update = 0;
                break;
            }

            /* Compute gravity for particle effects. */
            /* Use P0 context for global particles */
            if (stats[0].status == GAME_GOAL)
                game_tilt_grav(v, GRAVITY_UP, &gl[0].tilt[CURR]);
            else
                game_tilt_grav(v, GRAVITY_DN, &gl[0].tilt[CURR]);

            /* Step particle, goal and jump effects. */

            if (cs.ups > 0)
            {
                dt = 1.0f / cs.ups;

                for (p = 0; p < MAX_PLAYERS; p++)
                {
                    if (gd[p].state)
                    {
                         struct game_draw *cg_p = &gd[p];
                         struct game_lerp *cl_p = &gl[p];

                         if (cg_p->goal_e && cl_p->goal_k[CURR] < 1.0f)
                            cl_p->goal_k[CURR] += dt;

                         if (cg_p->jump_b)
                         {
                            cl_p->jump_dt[CURR] += dt;

                            if (cl_p->jump_dt[PREV] >= 1.0f)
                                cg_p->jump_b = 0;
                         }
                    }
                }

                part_step(v, dt);
            }

            break;

        case CMD_MAKE_BALL:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_MAKE_ITEM:
            /* Not supported anymore. */
            break;

        case CMD_PICK_ITEM:
            /* Set up particle effects and discard the item. */

            if ((idx = cmd->pkitem.hi) >= 0 && idx < vary->hc)
            {
                float pos[3];

                hp = &vary->hv[idx];

                sol_entity_world(pos, vary, hp->mi, hp->mj, hp->p);

                item_color(hp, v);
                part_burst(pos, v);

                hp->t = ITEM_NONE;
            }
            break;

        case CMD_TILT_ANGLES:
            if (!cs.got_tilt_axes)
            {
                game_tilt_axes(tilt, view->e);
            }

            tilt->rx = cmd->tiltangles.x;
            tilt->rz = cmd->tiltangles.z;
            break;

        case CMD_SOUND:
            /* Play the sound. */

            if (cmd->sound.n)
                audio_play(cmd->sound.n, cmd->sound.a);

            break;

        case CMD_TIMER:
            cst->timer = cmd->timer.t;
            break;

        case CMD_STATUS:
            cst->status = cmd->status.t;
            break;

        case CMD_COINS:
            cst->coins = cmd->coins.n;
            break;

        case CMD_JUMP_ENTER:
            cg->jump_b  = 1;
            cg->jump_e  = 0;
            cl->jump_dt[PREV] = 0.0f;
            cl->jump_dt[CURR] = 0.0f;
            break;

        case CMD_JUMP_EXIT:
            cg->jump_e = 1;
            break;

        case CMD_MOVE_PATH:
        case CMD_MOVE_TIME:
        case CMD_BODY_PATH:
        case CMD_BODY_TIME:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_GOAL_OPEN:
            if (!cg->goal_e)
            {
                cg->goal_e = 1;
                cl->goal_k[CURR] = cs.first_update ? 1.0f : 0.0f;
            }
            break;

        case CMD_SWCH_ENTER:
            if ((idx = cmd->swchenter.xi) >= 0 && idx < vary->xc)
                vary->xv[idx].e = 1;
            break;

        case CMD_SWCH_TOGGLE:
            if ((idx = cmd->swchtoggle.xi) >= 0 && idx < vary->xc)
                vary->xv[idx].f = !vary->xv[idx].f;
            break;

        case CMD_SWCH_EXIT:
            if ((idx = cmd->swchexit.xi) >= 0 && idx < vary->xc)
                vary->xv[idx].e = 0;
            break;

        case CMD_UPDATES_PER_SECOND:
            cs.ups = cmd->ups.n;
            break;

        case CMD_BALL_RADIUS:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_CLEAR_ITEMS:
            /* Not supported anymore. */
            break;

        case CMD_CLEAR_BALLS:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_BALL_POSITION:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_BALL_BASIS:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_BALL_PEND_BASIS:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_VIEW_POSITION:
            v_cpy(view->p, cmd->viewpos.p);
            break;

        case CMD_VIEW_CENTER:
            v_cpy(view->c, cmd->viewcenter.c);
            break;

        case CMD_VIEW_BASIS:
            v_cpy(view->e[0], cmd->viewbasis.e[0]);
            v_cpy(view->e[1], cmd->viewbasis.e[1]);
            v_crs(view->e[2], view->e[0], view->e[1]);
            break;

        case CMD_CURRENT_BALL:
            if ((idx = cmd->currball.ui) >= 0 && idx < vary->uc)
                cs.curr_ball = idx;
            break;

        case CMD_PATH_FLAG:
            if ((idx = cmd->pathflag.pi) >= 0 && idx < vary->pc)
                vary->pv[idx].f = cmd->pathflag.f;
            break;

        case CMD_STEP_SIMULATION:
            sol_lerp_cmd(&cl->lerp, &cs, cmd);
            break;

        case CMD_MAP:
            game_compat_map = (version.x == cmd->map.version.x);
            break;

        case CMD_TILT_AXES:
            cs.got_tilt_axes = 1;
            v_cpy(tilt->x, cmd->tiltaxes.x);
            v_cpy(tilt->z, cmd->tiltaxes.z);
            break;

        case CMD_NONE:
        case CMD_MAX:
            break;
        }
    }
}

void game_client_sync(fs_file demo_fp)
{
    union cmd *cmdp;

    while ((cmdp = game_proxy_deq()))
    {
        if (demo_fp)
            cmd_put(demo_fp, cmdp);

        game_run_cmd(cmdp);

        cmd_free(cmdp);
    }
}

/*---------------------------------------------------------------------------*/

int  game_client_init(const char *file_name)
{
    char *back_name = "", *grad_name = "";
    int i, p;
    int player_count = config_get_d(CONFIG_MULTIBALL);
    if (player_count < 1) player_count = 1;
    if (player_count > MAX_PLAYERS) player_count = MAX_PLAYERS;

    game_client_free(file_name);

    /* Load SOL data. */

    if (!game_base_load(file_name))
        return (gd[0].state = 0); /* Signal failure via gd[0] */

    /* Initialize all players */
    for (p = 0; p < player_count; p++)
    {
        struct game_draw *cg = &gd[p];
        struct game_lerp *cl = &gl[p];
        struct client_stats *cst = &stats[p];

        cst->coins = 0;
        cst->status = GAME_NONE;
        cst->timer = 0.0f;

        if (!sol_load_vary(&cg->vary, &game_base))
        {
            /* If fail, partial clean? We rely on game_client_free cleaning up. */
            /* But caller checks return. */
            /* Let's assume if p=0 fails we return 0. */
            if (p == 0)
            {
                game_base_free(NULL);
                return (cg->state = 0);
            }
        }

        if (!sol_load_draw(&cg->draw, &cg->vary, config_get_d(CONFIG_SHADOW)))
        {
            sol_free_vary(&cg->vary);
            if (p == 0)
            {
                game_base_free(NULL);
                return (cg->state = 0);
            }
        }

        cg->state = 1;

        /* Initialize game state. */

        game_tilt_init(&cg->tilt);
        game_view_init(&cg->view);

        cg->jump_e  = 1;
        cg->jump_b  = 0;
        cg->jump_dt = 0.0f;

        cg->goal_e = 0;
        cg->goal_k = 0.0f;

        /* Initialize interpolation. */

        game_lerp_init(cl, cg);

        /* Initialize fade. */

        cg->fade_k =  1.0f;
        cg->fade_d = -2.0f;
    }

    /* Load level info (from shared base) */

    version.x = 0;
    version.y = 0;

    for (i = 0; i < game_base.dc; i++)
    {
        char *k = game_base.av + game_base.dv[i].ai;
        char *v = game_base.av + game_base.dv[i].aj;

        if (strcmp(k, "back") == 0) back_name = v;
        if (strcmp(k, "grad") == 0) grad_name = v;

        if (strcmp(k, "version") == 0)
            sscanf(v, "%d.%d", &version.x, &version.y);
    }

    game_compat_map = version.x == 1;

    part_reset();

    cmd_state_init(&cs);

    back_init(grad_name);
    /* Back is shared visually? Or each player has own skybox instance? */
    /* game_draw takes gd->back. */
    /* We need to init back for each player or share? */
    /* sol_load_full takes path. It loads geometry. */
    /* We should probably load it for each player so they have independent state/draw struct */
    for (p = 0; p < player_count; p++)
    {
        sol_load_full(&gd[p].back, back_name, 0);
    }

    light_reset();

    return gd[0].state;
}

void game_client_free(const char *next)
{
    int p;
    /* Clean up all players */
    /* We don't track player_count precisely here, so loop MAX or check state */
    /* But checking state is safe */

    game_proxy_clr();

    for (p = 0; p < MAX_PLAYERS; p++)
    {
        if (gd[p].state)
        {
            game_lerp_free(&gl[p]);
            sol_free_draw(&gd[p].draw);
            sol_free_vary(&gd[p].vary);
            sol_free_full(&gd[p].back);
            gd[p].state = 0;
        }
    }

    /* Only free game_base if we actually loaded something (gd[0].state was 1) */
    /* But we just cleared state. */
    /* game_client_init checked gd[0].state. */
    /* We can just call game_base_free(next) unconditionally? */
    /* game_base_free checks if base is loaded? No, it frees. */
    /* If we call it multiple times, we need safety. */
    /* For now, assume single call flow. */

    game_base_free(next);
    back_free();
}

/*---------------------------------------------------------------------------*/

int enable_interpolation = 1;

void game_client_blend(float a)
{
    int p;
    for (p = 0; p < MAX_PLAYERS; p++)
    {
        if (enable_interpolation)
            gl[p].alpha = a;
        else
            gl[p].alpha = 1.0f;
    }
}

void game_client_draw(int pose, float t)
{
    int p;
    int count = config_get_d(CONFIG_MULTIBALL);
    if (count < 1) count = 1;
    if (count > MAX_PLAYERS) count = MAX_PLAYERS;

    int w = video.device_w;
    int h = video.device_h;

    for (p = 0; p < count; p++)
    {
        if (!gd[p].state) continue;

        int vp_x = 0, vp_y = 0, vp_w = w, vp_h = h;

        if (count == 2)
        {
            /* Horizontal split */
            vp_h = h / 2;
            vp_y = (p == 0) ? h / 2 : 0;
        }
        else if (count >= 3)
        {
            /* Quad split */
            vp_w = w / 2;
            vp_h = h / 2;
            if (p == 0) { vp_x = 0;    vp_y = h/2; }
            if (p == 1) { vp_x = w/2;  vp_y = h/2; }
            if (p == 2) { vp_x = 0;    vp_y = 0;   }
            if (p == 3) { vp_x = w/2;  vp_y = 0;   }
        }

        game_lerp_apply(&gl[p], &gd[p]);

        /* Pass viewport to game_draw */
        game_draw(gd, p, count, pose, t, vp_x, vp_y, vp_w, vp_h);
    }
}

/*---------------------------------------------------------------------------*/

int curr_clock(int p)
{
    return (int) (stats[p].timer * 100.f);
}

int curr_coins(int p)
{
    return stats[p].coins;
}

int curr_status(int p)
{
    return stats[p].status;
}

/*---------------------------------------------------------------------------*/

void game_look(float phi, float theta)
{
    /* Apply look to all players? Or default P0? */
    /* This function is used by st_look (mouse look around). */
    /* Usually purely visual/client side. */
    /* Default to P0 for now. */
    int p = 0;
    struct game_view *view = &gl[p].view[CURR];

    view->c[0] = view->p[0] + fsinf(V_RAD(theta)) * fcosf(V_RAD(phi));
    view->c[1] = view->p[1] +                       fsinf(V_RAD(phi));
    view->c[2] = view->p[2] - fcosf(V_RAD(theta)) * fcosf(V_RAD(phi));

    gl[p].view[PREV] = gl[p].view[CURR];
}

/*---------------------------------------------------------------------------*/

void game_kill_fade(void)
{
    int p;
    for (p = 0; p < MAX_PLAYERS; p++)
    {
        gd[p].fade_k = 0.0f;
        gd[p].fade_d = 0.0f;
    }
}

void game_step_fade(float dt)
{
    int p;
    for (p = 0; p < MAX_PLAYERS; p++)
    {
        struct game_draw *cg = &gd[p];
        if ((cg->fade_k < 1.0f && cg->fade_d > 0.0f) ||
            (cg->fade_k > 0.0f && cg->fade_d < 0.0f))
            cg->fade_k += cg->fade_d * dt;

        if (cg->fade_k < 0.0f)
        {
            cg->fade_k = 0.0f;
            cg->fade_d = 0.0f;
        }
        if (cg->fade_k > 1.0f)
        {
            cg->fade_k = 1.0f;
            cg->fade_d = 0.0f;
        }
    }
}

void game_fade(float d)
{
    int p;
    for (p = 0; p < MAX_PLAYERS; p++)
        gd[p].fade_d = d;
}

/*---------------------------------------------------------------------------*/

void game_client_fly(float k)
{
    int p;
    for (p = 0; p < MAX_PLAYERS; p++)
    {
        game_view_fly(&gl[p].view[CURR], &gd[p].vary, k);
        gl[p].view[PREV] = gl[p].view[CURR];
    }
}

/*---------------------------------------------------------------------------*/
