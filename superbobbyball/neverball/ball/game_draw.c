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

#include "vec3.h"
#include "glext.h"
#include "ball.h"
#include "part.h"
#include "geom.h"
#include "config.h"
#include "video.h"

#include "solid_all.h"
#include "solid_draw.h"

#include "game_draw.h"
#include "game_server.h"
#include "progress.h"

/*---------------------------------------------------------------------------*/

static const float player_colors[4][4] = {
    { 1.0f, 0.3f, 0.3f, 1.0f }, /* Red */
    { 0.3f, 1.0f, 0.3f, 1.0f }, /* Green */
    { 0.4f, 0.4f, 1.0f, 1.0f }, /* Blue */
    { 1.0f, 1.0f, 0.0f, 1.0f }  /* Yellow */
};

/* Billiard Colors (Standard Pool) */
static const float billiard_colors[16][4] = {
    { 1.0f, 1.0f, 1.0f, 1.0f }, /* 0: Cue (White) */
    { 1.0f, 1.0f, 0.0f, 1.0f }, /* 1: Yellow */
    { 0.0f, 0.0f, 1.0f, 1.0f }, /* 2: Blue */
    { 1.0f, 0.0f, 0.0f, 1.0f }, /* 3: Red */
    { 0.5f, 0.0f, 0.5f, 1.0f }, /* 4: Purple */
    { 1.0f, 0.5f, 0.0f, 1.0f }, /* 5: Orange */
    { 0.0f, 0.5f, 0.0f, 1.0f }, /* 6: Green */
    { 0.5f, 0.0f, 0.0f, 1.0f }, /* 7: Maroon */
    { 0.1f, 0.1f, 0.1f, 1.0f }, /* 8: Black */
    { 1.0f, 1.0f, 0.0f, 1.0f }, /* 9: Yellow */
    { 0.0f, 0.0f, 1.0f, 1.0f }, /* 10: Blue */
    { 1.0f, 0.0f, 0.0f, 1.0f }, /* 11: Red */
    { 0.5f, 0.0f, 0.5f, 1.0f }, /* 12: Purple */
    { 1.0f, 0.5f, 0.0f, 1.0f }, /* 13: Orange */
    { 0.0f, 0.5f, 0.0f, 1.0f }, /* 14: Green */
    { 0.5f, 0.0f, 0.0f, 1.0f }  /* 15: Maroon */
};

static void game_draw_target(void)
{
    const struct target_zone *zones = game_get_zones();
    int count = game_get_zone_count();
    int i;

    float y = 0.05f;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (i = count - 1; i >= 0; i--)
    {
        float r = zones[i].radius;
        const float *c = zones[i].color;
        int segments = 64;
        int j;

        glColor4fv(c);

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, y, 0.0f);
        for (j = 0; j <= segments; j++)
        {
            float theta = 2.0f * 3.14159f * (float)j / (float)segments;
            glVertex3f(r * cosf(theta), y, r * sinf(theta));
        }
        glEnd();

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (j = 0; j <= segments; j++)
        {
            float theta = 2.0f * 3.14159f * (float)j / (float)segments;
            glVertex3f(r * cosf(theta), y + 0.01f, r * sinf(theta));
        }
        glEnd();
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

static void game_draw_balls(struct s_rend *rend,
                            struct game_draw *gds,
                            int p_idx, int p_count,
                            const float *bill_M, float t)
{
    int i;

    int mode = curr_mode();

    if (mode == MODE_BATTLE || mode == MODE_TARGET || mode == MODE_FIGHT || mode == MODE_BILLIARDS || mode == MODE_BOWLING)
    {
        struct s_vary *vary = &gds[p_idx].vary;
        int b;

        for (b = 0; b < vary->uc; b++)
        {
            float ball_M[16];
            float pend_M[16];

            m_basis(ball_M, vary->uv[b].e[0], vary->uv[b].e[1], vary->uv[b].e[2]);
            m_basis(pend_M, vary->uv[b].E[0], vary->uv[b].E[1], vary->uv[b].E[2]);

            glPushMatrix();
            {
                glTranslatef(vary->uv[b].p[0],
                             vary->uv[b].p[1] + BALL_FUDGE,
                             vary->uv[b].p[2]);

                if (mode == MODE_FIGHT && b < MAX_PLAYERS && gds[b].punch_active)
                {
                    glPushMatrix();
                    {
                        float vec[3];
                        v_cpy(vec, gds[b].view.e[2]);
                        v_scl(vec, vec, -1.0f);

                        float offset = vary->uv[b].r * 1.5f;
                        glTranslatef(vec[0]*offset, vec[1]*offset, vec[2]*offset);

                        float s = vary->uv[b].r * 0.5f;
                        glScalef(s, s, s);

                        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

                        float ident[16];
                        m_ident(ident);
                        ball_draw(rend, ident, ident, bill_M, t);
                    }
                    glPopMatrix();
                }

                if ((mode == MODE_BILLIARDS || mode == MODE_BOWLING) && b == 0)
                {
                    /* Draw Aim Line */
                    glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glDisable(GL_TEXTURE_2D);
                    glLineWidth(2.0f);
                    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

                    float start[3] = {0,0,0}; /* Local origin */
                    float end[3];
                    float dir[3];

                    v_cpy(dir, gds[0].view.e[2]);
                    v_scl(dir, dir, -1.0f);
                    v_scl(end, dir, 10.0f);

                    glBegin(GL_LINES);
                    glVertex3fv(start);
                    glVertex3fv(end);
                    glEnd();

                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_LIGHTING);
                    glPopMatrix();
                }

                if (mode == MODE_BOWLING && b > 0)
                {
                    /* Render Pin */
                    /* Elongate vertically */
                    glScalef(1.0f, 2.5f, 1.0f);
                }

                glScalef(vary->uv[b].r,
                         vary->uv[b].r,
                         vary->uv[b].r);

                if (mode == MODE_BILLIARDS)
                {
                    int c_idx = b % 16;
                    glColor4fv(billiard_colors[c_idx]);
                }
                else if (mode == MODE_BOWLING)
                {
                    if (b == 0) {
                        /* Player */
                        int c_idx = b % 4;
                        glColor4fv(player_colors[c_idx]);
                    } else {
                        /* Pin: White */
                        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                    }
                }
                else
                {
                    int c_idx = b % 4;
                    float r = player_colors[c_idx][0];
                    float g = player_colors[c_idx][1];
                    float b = player_colors[c_idx][2];
                    float a = (b == p_idx) ? 1.0f : 0.5f;

                    glColor4f(r, g, b, a);
                }

                if (mode != MODE_BILLIARDS && mode != MODE_BOWLING && b != p_idx)
                {
                    glDepthMask(GL_FALSE);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                ball_draw(rend, ball_M, pend_M, bill_M, t);

                if (mode != MODE_BILLIARDS && mode != MODE_BOWLING && b != p_idx)
                {
                    glDisable(GL_BLEND);
                    glDepthMask(GL_TRUE);
                }
            }
            glPopMatrix();
        }
    }
    else
    {
        for (i = 0; i < p_count; i++)
        {
            if (!gds[i].state) continue;

            struct s_vary *vary = &gds[i].vary;
            int b_idx = 0;
            if (vary->uc <= 0) continue;

            float ball_M[16];
            float pend_M[16];

            m_basis(ball_M, vary->uv[b_idx].e[0], vary->uv[b_idx].e[1], vary->uv[b_idx].e[2]);
            m_basis(pend_M, vary->uv[b_idx].E[0], vary->uv[b_idx].E[1], vary->uv[b_idx].E[2]);

            glPushMatrix();
            {
                glTranslatef(vary->uv[b_idx].p[0],
                             vary->uv[b_idx].p[1] + BALL_FUDGE,
                             vary->uv[b_idx].p[2]);

                glScalef(vary->uv[b_idx].r,
                         vary->uv[b_idx].r,
                         vary->uv[b_idx].r);

                float r = player_colors[i%4][0];
                float g = player_colors[i%4][1];
                float b = player_colors[i%4][2];
                float a = (i == p_idx) ? 1.0f : 0.5f;

                glColor4f(r, g, b, a);

                if (i != p_idx)
                {
                    glDepthMask(GL_FALSE);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                ball_draw(rend, ball_M, pend_M, bill_M, t);

                if (i != p_idx)
                {
                    glDisable(GL_BLEND);
                    glDepthMask(GL_TRUE);
                }
            }
            glPopMatrix();
        }
    }
}

static void game_draw_items(struct s_rend *rend,
                            const struct s_vary *vary,
                            const float *bill_M, float t)
{
    int hi;

    for (hi = 0; hi < vary->hc; hi++)
    {
        struct v_item *hp = &vary->hv[hi];

        float item_p[3], item_e[4], u[3], a;

        if (hp->t == ITEM_NONE)
            continue;

        sol_entity_p(item_p, vary, hp->mi, hp->mj);
        sol_entity_e(item_e, vary, hp->mi, hp->mj);

        q_as_axisangle(item_e, u, &a);

        glPushMatrix();
        {
            glTranslatef(item_p[0], item_p[1], item_p[2]);
            glRotatef(V_DEG(a), u[0], u[1], u[2]);
            glTranslatef(hp->p[0], hp->p[1], hp->p[2]);
            item_draw(rend, hp, bill_M, t);
        }
        glPopMatrix();
    }
}

static void game_draw_beams(struct s_rend *rend, const struct game_draw *gd)
{
    static const GLfloat goal_c[4]       =   { 1.0f, 1.0f, 0.0f, 0.5f };
    static const GLfloat jump_c[2][4]    =  {{ 0.7f, 0.5f, 1.0f, 0.5f },
                                             { 0.7f, 0.5f, 1.0f, 0.8f }};
    static const GLfloat swch_c[2][2][4] = {{{ 1.0f, 0.0f, 0.0f, 0.5f },
                                             { 1.0f, 0.0f, 0.0f, 0.8f }},
                                            {{ 0.0f, 1.0f, 0.0f, 0.5f },
                                             { 0.0f, 1.0f, 0.0f, 0.8f }}};

    const struct s_base *base =  gd->vary.base;
    const struct s_vary *vary = &gd->vary;

    float beam_p[3], beam_e[4], u[3], a;
    int i;

    if (gd->goal_e)
        for (i = 0; i < base->zc; i++)
        {
            sol_entity_p(beam_p, vary, vary->zv[i].mi, vary->zv[i].mj);
            sol_entity_e(beam_e, vary, vary->zv[i].mi, vary->zv[i].mj);

            q_as_axisangle(beam_e, u, &a);

            glPushMatrix();
            {
                glTranslatef(beam_p[0], beam_p[1], beam_p[2]);
                glRotatef(V_DEG(a), u[0], u[1], u[2]);
                beam_draw(rend, base->zv[i].p, goal_c, base->zv[i].r, gd->goal_k * 3.0f);
            }
            glPopMatrix();
        }

    for (i = 0; i < base->jc; i++)
    {
        sol_entity_p(beam_p, vary, vary->jv[i].mi, vary->jv[i].mj);
        sol_entity_e(beam_e, vary, vary->jv[i].mi, vary->jv[i].mj);

        q_as_axisangle(beam_e, u, &a);

        glPushMatrix();
        {
            glTranslatef(beam_p[0], beam_p[1], beam_p[2]);
            glRotatef(V_DEG(a), u[0], u[1], u[2]);
            beam_draw(rend, base->jv[i].p, jump_c[gd->jump_e ? 0 : 1], base->jv[i].r, 2.0f);
        }
        glPopMatrix();
    }

    for (i = 0; i < base->xc; i++)
        if (!vary->xv[i].base->i)
        {
            sol_entity_p(beam_p, vary, vary->xv[i].mi, vary->xv[i].mj);
            sol_entity_e(beam_e, vary, vary->xv[i].mi, vary->xv[i].mj);

            q_as_axisangle(beam_e, u, &a);

            glPushMatrix();
            {
                glTranslatef(beam_p[0], beam_p[1], beam_p[2]);
                glRotatef(V_DEG(a), u[0], u[1], u[2]);
                beam_draw(rend, base->xv[i].p, swch_c[vary->xv[i].f][vary->xv[i].e], base->xv[i].r, 2.0f);
            }
            glPopMatrix();
        }
}

static void game_draw_goals(struct s_rend *rend,
                            const struct game_draw *gd, float t)
{
    const struct s_base *base =  gd->vary.base;
    const struct s_vary *vary = &gd->vary;

    float goal_p[3], goal_e[4], u[3], a;
    int i;

    if (gd->goal_e)
        for (i = 0; i < base->zc; i++)
        {
            sol_entity_p(goal_p, vary, vary->zv[i].mi, vary->zv[i].mj);
            sol_entity_e(goal_e, vary, vary->zv[i].mi, vary->zv[i].mj);

            q_as_axisangle(goal_e, u, &a);

            glPushMatrix();
            {
                glTranslatef(goal_p[0], goal_p[1], goal_p[2]);
                glRotatef(V_DEG(a), u[0], u[1], u[2]);
                goal_draw(rend, base->zv[i].p, base->zv[i].r, gd->goal_k, t);
            }
            glPopMatrix();
        }
}

static void game_draw_jumps(struct s_rend *rend,
                            const struct game_draw *gd, float t)
{
    const struct s_base *base =  gd->vary.base;
    const struct s_vary *vary = &gd->vary;

    float jump_p[3], jump_e[4], u[3], a;
    int i;

    for (i = 0; i < base->jc; i++)
    {
        sol_entity_p(jump_p, vary, vary->jv[i].mi, vary->jv[i].mj);
        sol_entity_e(jump_e, vary, vary->jv[i].mi, vary->jv[i].mj);

        q_as_axisangle(jump_e, u, &a);

        glPushMatrix();
        {
            glTranslatef(jump_p[0], jump_p[1], jump_p[2]);
            glRotatef(V_DEG(a), u[0], u[1], u[2]);
            jump_draw(rend, base->jv[i].p, base->jv[i].r, 1.0f);
        }
        glPopMatrix();
    }
}

/*---------------------------------------------------------------------------*/

static void game_draw_tilt(const struct game_draw *gd, int d)
{
    const struct game_tilt *tilt = &gd->tilt;
    const float *ball_p = gd->vary.uv[0].p;

    glTranslatef(+ball_p[0], +ball_p[1] * d, +ball_p[2]);
    glRotatef(-tilt->rz * d, tilt->z[0], tilt->z[1], tilt->z[2]);
    glRotatef(-tilt->rx * d, tilt->x[0], tilt->x[1], tilt->x[2]);
    glTranslatef(-ball_p[0], -ball_p[1] * d, -ball_p[2]);
}

static void game_refl_all(struct s_rend *rend, const struct game_draw *gd)
{
    glPushMatrix();
    {
        game_draw_tilt(gd, 1);
        sol_refl(&gd->draw, rend);
    }
    glPopMatrix();
}

/*---------------------------------------------------------------------------*/

static void game_draw_light(const struct game_draw *gd, int d, float t)
{
    GLfloat p[4];

    light_conf();

    p[0] = cosf(t);
    p[1] = 0.0f;
    p[2] = sinf(t);
    p[3] = 0.0f;

    glLightfv(GL_LIGHT2, GL_POSITION, p);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

static void game_draw_back(struct s_rend *rend,
                           const struct game_draw *gd,
                           int pose, int d, float t)
{
    if (pose == POSE_BALL)
        return;

    glPushMatrix();
    {
        const struct game_view *view = &gd->view;

        if (d < 0)
        {
            const struct game_tilt *tilt = &gd->tilt;

            glRotatef(tilt->rz * 2, tilt->z[0], tilt->z[1], tilt->z[2]);
            glRotatef(tilt->rx * 2, tilt->x[0], tilt->x[1], tilt->x[2]);
        }

        glTranslatef(view->p[0], view->p[1] * d, view->p[2]);

        if (config_get_d(CONFIG_BACKGROUND))
        {
            back_draw(rend);
            sol_back(&gd->back.draw, rend, 0, FAR_DIST, t);
        }
        else back_draw(rend);
    }
    glPopMatrix();
}

static void game_clip_refl(int d)
{
    glClipPlane4f_(GL_CLIP_PLANE0, 0, 1, 0, -0.00001);
}

static void game_clip_ball(const struct game_draw *gd, int d, const float *p)
{
    GLfloat r, c[3], pz[4], nz[4];

    c[0] = p[0];
    c[1] = p[1] * d;
    c[2] = p[2];

    pz[0] = gd->view.p[0] - c[0];
    pz[1] = gd->view.p[1] - c[1];
    pz[2] = gd->view.p[2] - c[2];

    r = sqrt(pz[0] * pz[0] + pz[1] * pz[1] + pz[2] * pz[2]);

    pz[0] /= r;
    pz[1] /= r;
    pz[2] /= r;
    pz[3] = -(pz[0] * c[0] +
              pz[1] * c[1] +
              pz[2] * c[2]);

    nz[0] = -pz[0];
    nz[1] = -pz[1];
    nz[2] = -pz[2];
    nz[3] = -pz[3];

    pz[1] *= d;
    nz[1] *= d;

    glClipPlane4f_(GL_CLIP_PLANE1, nz[0], nz[1], nz[2], nz[3]);
    glClipPlane4f_(GL_CLIP_PLANE2, pz[0], pz[1], pz[2], pz[3]);
}

static void game_draw_fore(struct s_rend *rend,
                           struct game_draw *gds,
                           int p_idx, int p_count,
                           int pose, const float *M,
                           int d, float t)
{
    struct game_draw *gd = &gds[p_idx];
    const float *ball_p = gd->vary.uv[0].p;

    struct s_draw *draw = &gd->draw;

    glPushMatrix();
    {
        game_draw_tilt(gd, d);
        game_clip_refl(d);
        game_clip_ball(gd, d, ball_p);

        if (d < 0)
            glEnable(GL_CLIP_PLANE0);

        switch (pose)
        {
        case POSE_LEVEL:
            sol_draw(draw, rend, 0, 1);
            break;

        case POSE_BALL:
            if (curr_tex_env == &tex_env_pose)
            {
                glDepthMask(GL_FALSE);
                sol_draw(draw, rend, 0, 1);
                glDepthMask(GL_TRUE);
            }
            game_draw_balls(rend, gds, p_idx, p_count, M, t);
            break;

        case POSE_NONE:
            game_draw_items(rend, &gd->vary, M, t);
            sol_draw(draw, rend, 0, 1);

            if (curr_mode() == MODE_TARGET)
                game_draw_target();

            game_draw_balls(rend, gds, p_idx, p_count, M, t);
            break;
        }


        glDepthMask(GL_FALSE);
        {
            sol_bill(draw, rend, M, t);
            game_draw_beams(rend, gd);
            part_draw_coin(draw, rend, M, t);

            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glEnable (GL_LIGHT2);
            {
                game_draw_goals(rend, gd, t);
                game_draw_jumps(rend, gd, t);
            }
            glDisable(GL_LIGHT2);
            glEnable (GL_LIGHT1);
            glEnable (GL_LIGHT0);
        }
        glDepthMask(GL_TRUE);

        if (d < 0)
            glDisable(GL_CLIP_PLANE0);
    }
    glPopMatrix();
}

/*---------------------------------------------------------------------------*/

static void game_shadow_conf(int pose, int enable)
{
    if (enable && config_get_d(CONFIG_SHADOW))
    {
        switch (pose)
        {
        case POSE_LEVEL:
            tex_env_active(&tex_env_default);
            break;

        case POSE_BALL:
            tex_env_select(&tex_env_pose,
                           &tex_env_default,
                           NULL);
            break;

        default:
            tex_env_select(&tex_env_shadow_clip,
                           &tex_env_shadow,
                           &tex_env_default,
                           NULL);
            break;
        }
    }
    else
    {
        tex_env_active(&tex_env_default);
    }
}

void game_draw(struct game_draw *gds, int p_idx, int p_count, int pose, float t, int vp_x, int vp_y, int vp_w, int vp_h)
{
    struct game_draw *gd = &gds[p_idx];

    float fov = (float) config_get_d(CONFIG_VIEW_FOV);

    if (gd->jump_b) fov *= 2.f * fabsf(gd->jump_dt - 0.5f);

    if (gd->state)
    {
        glViewport(vp_x, vp_y, vp_w, vp_h);

        const struct game_view *view = &gd->view;
        struct s_rend rend;

        gd->draw.shadow_ui = 0;

        game_shadow_conf(pose, 1);
        r_draw_enable(&rend);

        video_push_persp_ex(fov, 0.1f, FAR_DIST, vp_x, vp_y, vp_w, vp_h);
            glPushMatrix();
            {
                float T[16], U[16], M[16], v[3];

                v[0] = +view->p[0];
                v[1] = -view->p[1];
                v[2] = +view->p[2];

                video_calc_view(T, view->c, view->p, view->e[1]);
                video_calc_view(U, view->c, v,       view->e[1]);

                m_xps(M, T);

                v_sub(v, view->c, view->p);

                glTranslatef(0.f, 0.f, -v_len(v));
                glMultMatrixf(M);
                glTranslatef(-view->c[0], -view->c[1], -view->c[2]);

                game_draw_back(&rend, gd, pose, +1, t);

                if (gd->draw.reflective && config_get_d(CONFIG_REFLECTION))
                {
                    glEnable(GL_STENCIL_TEST);
                    {
                        glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
                        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
                        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                        glDepthMask(GL_FALSE);

                        game_refl_all(&rend, gd);

                        glDepthMask(GL_TRUE);
                        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                        glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);

                        glFrontFace(GL_CW);
                        glPushMatrix();
                        {
                            glScalef(+1.0f, -1.0f, +1.0f);

                            game_draw_light(gd, -1, t);

                            game_draw_back(&rend, gd, pose,    -1, t);
                            game_draw_fore(&rend, gds, p_idx, p_count, pose, U, -1, t);
                        }
                        glPopMatrix();
                        glFrontFace(GL_CCW);

                        glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFF);
                    }
                    glDisable(GL_STENCIL_TEST);
                }

                game_draw_light(gd, 1, t);

                if (gd->draw.reflective && !config_get_d(CONFIG_REFLECTION))
                {
                    r_color_mtrl(&rend, 1);
                    {
                        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                        game_refl_all(&rend, gd);
                        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                    }
                    r_color_mtrl(&rend, 0);
                }

                game_refl_all (&rend, gd);
                game_draw_fore(&rend, gds, p_idx, p_count, pose, T, +1, t);
            }
            glPopMatrix();
            video_pop_matrix();

            sol_fade(&gd->draw, &rend, gd->fade_k);

            r_draw_disable(&rend);
            game_shadow_conf(pose, 0);
    }
}

/*---------------------------------------------------------------------------*/

void game_lerp_init(struct game_lerp *l, struct game_draw *d)
{
    sol_load_lerp(&l->lerp, &d->vary);

    l->tilt[0] = l->tilt[1] = d->tilt;
    l->view[0] = l->view[1] = d->view;

    l->goal_k[0] = l->goal_k[1] = d->goal_k;
    l->jump_dt[0] = l->jump_dt[1] = d->jump_dt;

    l->punch_active[0] = l->punch_active[1] = d->punch_active;
}

void game_lerp_free(struct game_lerp *l)
{
    sol_free_lerp(&l->lerp);
}

void game_lerp_copy(struct game_lerp *l)
{
    sol_lerp_copy(&l->lerp);

    l->tilt[1] = l->tilt[0];
    l->view[1] = l->view[0];

    l->goal_k[1] = l->goal_k[0];
    l->jump_dt[1] = l->jump_dt[0];

    l->punch_active[1] = l->punch_active[0];
}

void game_lerp_apply(struct game_lerp *l, struct game_draw *d)
{
    float a = l->alpha;
    int i, j;

    sol_lerp_apply(&l->lerp, a);

    d->goal_k = l->goal_k[1] + (l->goal_k[0] - l->goal_k[1]) * a;
    d->jump_dt = l->jump_dt[1] + (l->jump_dt[0] - l->jump_dt[1]) * a;

    d->punch_active = l->punch_active[0];

    d->tilt.rx = l->tilt[1].rx + (l->tilt[0].rx - l->tilt[1].rx) * a;
    d->tilt.rz = l->tilt[1].rz + (l->tilt[0].rz - l->tilt[1].rz) * a;

    for (i=0; i<3; i++) {
        d->tilt.x[i] = l->tilt[1].x[i] + (l->tilt[0].x[i] - l->tilt[1].x[i]) * a;
        d->tilt.z[i] = l->tilt[1].z[i] + (l->tilt[0].z[i] - l->tilt[1].z[i]) * a;
    }

    for (i=0; i<3; i++) {
        d->view.p[i] = l->view[1].p[i] + (l->view[0].p[i] - l->view[1].p[i]) * a;
        d->view.c[i] = l->view[1].c[i] + (l->view[0].c[i] - l->view[1].c[i]) * a;
    }

    for (j=0; j<3; j++)
        for (i=0; i<3; i++)
            d->view.e[j][i] = l->view[1].e[j][i] + (l->view[0].e[j][i] - l->view[1].e[j][i]) * a;
}

/*---------------------------------------------------------------------------*/
