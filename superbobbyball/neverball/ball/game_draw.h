#ifndef GAME_DRAW_H
#define GAME_DRAW_H

#include "solid_draw.h"
#include "game_common.h"

/*---------------------------------------------------------------------------*/

struct game_draw
{
    int state;

    struct s_vary vary;
    struct s_draw draw;

    struct s_full back;

    struct game_tilt tilt;              /* Floor rotation                    */
    struct game_view view;              /* Current view                      */

    int   goal_e;                       /* Goal enabled flag                 */
    float goal_k;                       /* Goal animation                    */

    int   jump_e;                       /* Jumping enabled flag              */
    int   jump_b;                       /* Jump-in-progress flag             */
    float jump_dt;                      /* Jump duration                     */

    float fade_k;                       /* Fade in/out level                 */
    float fade_d;                       /* Fade in/out direction             */

    int   punch_active;                 /* Fight punch state                 */
};

/* FIXME: this is just for POSE_* constants. */
#include "game_client.h"

void game_draw(struct game_draw *gds, int p_idx, int p_count, int pose, float t, int x, int y, int w, int h);

/*---------------------------------------------------------------------------*/

struct game_lerp
{
    float alpha;                        /* Interpolation factor              */

    struct s_lerp lerp;

    struct game_tilt tilt[2];
    struct game_view view[2];

    float goal_k[2];
    float jump_dt[2];

    int   punch_active[2];              /* Interpolation state (discrete)    */
};

void game_lerp_init(struct game_lerp *, struct game_draw *);
void game_lerp_free(struct game_lerp *);
void game_lerp_copy(struct game_lerp *);
void game_lerp_apply(struct game_lerp *, struct game_draw *);

/*---------------------------------------------------------------------------*/

#endif
