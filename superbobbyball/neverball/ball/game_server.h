#ifndef GAME_SERVER_H
#define GAME_SERVER_H

/*---------------------------------------------------------------------------*/

#define RESPONSE    0.05f              /* Input smoothing time               */
#define ANGLE_BOUND 20.0f              /* Angle limit of floor tilting       */
#define VIEWR_BOUND 10.0f              /* Maximum rate of view rotation      */

/*---------------------------------------------------------------------------*/

struct target_zone {
    float radius;
    int score;
    float color[4]; /* RGBA */
};

/*---------------------------------------------------------------------------*/

int   game_server_init(const char *, int, int, int);
void  game_server_free(const char *);
void  game_server_step(float);
float game_server_blend(void);

void  game_set_goal(int);
void  game_respawn(int);

void  game_set_ang(float, float, int);
void  game_set_pos(int, int, int);
void  game_set_x  (float, int);
void  game_set_z  (float, int);
void  game_set_cam(int, int);
void  game_set_rot(float, int);
void  game_set_action(int, int);

float curr_time_elapsed(int p);
float curr_speed(int p);
float curr_altitude(int p);
int   curr_warp_id(int p);

int game_get_zone_count(void);
const struct target_zone *game_get_zones(void);

/*---------------------------------------------------------------------------*/

#endif
