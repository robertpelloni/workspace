/*
 * Party Mode Menu State
 */

#include <stdio.h>

#include "gui.h"
#include "transition.h"
#include "audio.h"
#include "config.h"
#include "progress.h"
#include "set.h"
#include "st_party.h"
#include "st_title.h"
#include "st_play.h"
#include "st_shared.h"
#include "game_common.h"

enum {
    PARTY_MODE = GUI_LAST,
    PARTY_PLAYERS,
    PARTY_PHYSICS,
    PARTY_START
};

static int party_mode = MODE_TARGET;
static int party_players = 1;
static int party_physics = 0;

static int mode_id;
static int player_id;
static int physics_id;

static const char *get_mode_label(int m) {
    if (m == MODE_TARGET)    return "Mode: Monkey Target";
    if (m == MODE_BATTLE)    return "Mode: Battle (Shared)";
    if (m == MODE_FIGHT)     return "Mode: Monkey Fight";
    if (m == MODE_BILLIARDS) return "Mode: Monkey Billiards";
    return "Mode: Unknown";
}

static void update_labels(void) {
    char buf[32];

    gui_set_label(mode_id, get_mode_label(party_mode));

    sprintf(buf, "Players: %d", party_players);
    gui_set_label(player_id, buf);

    gui_set_label(physics_id, party_physics ? "Physics: Arcade" : "Physics: Normal");
}

static int party_action(int tok, int val) {
    switch (tok) {
        case GUI_BACK:
            return goto_state(&st_title);

        case PARTY_MODE:
            if (party_mode == MODE_TARGET)         party_mode = MODE_BATTLE;
            else if (party_mode == MODE_BATTLE)    party_mode = MODE_FIGHT;
            else if (party_mode == MODE_FIGHT)     party_mode = MODE_BILLIARDS;
            else if (party_mode == MODE_BILLIARDS) party_mode = MODE_TARGET;
            update_labels();
            break;

        case PARTY_PLAYERS:
            party_players++;
            if (party_players > 4) party_players = 1;
            update_labels();
            break;

        case PARTY_PHYSICS:
            party_physics = !party_physics;
            update_labels();
            break;

        case PARTY_START:
            config_set_d(CONFIG_MULTIBALL, party_players);
            config_set_d(CONFIG_PHYSICS, party_physics);
            progress_init(party_mode);

            /* Initialize sets if not done (st_set usually does this) */
            /* set_init returns total sets. */
            if (set_init() > 0) {
                set_goto(0); /* Easy Set */
                if (progress_play(get_level(0))) {
                    return goto_state(&st_play_ready);
                }
            }
            break;
    }
    return 1;
}

static int party_gui(void) {
    int root;
    if ((root = gui_vstack(0))) {
        gui_label(root, "Party Games", GUI_LRG, gui_yel, gui_red);
        gui_space(root);

        mode_id = gui_state(root, get_mode_label(party_mode), GUI_MED, PARTY_MODE, 0);
        player_id = gui_state(root, "Players: 1", GUI_MED, PARTY_PLAYERS, 0);
        physics_id = gui_state(root, "Physics: Normal", GUI_MED, PARTY_PHYSICS, 0);

        gui_space(root);
        gui_state(root, "Start Game", GUI_MED, PARTY_START, 0);
        gui_state(root, "Back", GUI_MED, GUI_BACK, 0);

        gui_layout(root, 0, 0);
        update_labels();
    }
    return root;
}

static int party_enter(struct state *st, struct state *prev, int intent) {
    audio_music_fade_to(0.5f, "bgm/inter.ogg");
    return transition_slide(party_gui(), 1, intent);
}

static int party_leave(struct state *st, struct state *next, int id, int intent) {
    return transition_slide(id, 0, intent);
}

static int party_click(int b, int d) {
    if (gui_click(b, d))
        return party_action(gui_token(gui_active()), gui_value(gui_active()));
    return 1;
}

static int party_buttn(int b, int d, int device_id) {
    if (d) {
        int active = gui_active();
        if (config_tst_d(CONFIG_JOYSTICK_BUTTON_A, b))
            return party_action(gui_token(active), gui_value(active));
        if (config_tst_d(CONFIG_JOYSTICK_BUTTON_B, b))
            return party_action(GUI_BACK, 0);
    }
    return 1;
}

static int party_keybd(int c, int d) {
    if (d) {
        if (c == 27) /* KEY_EXIT / ESC */
            return party_action(GUI_BACK, 0);
    }
    return 1;
}

/* Use shared handlers for paint/stick/etc */
struct state st_party = {
    party_enter,
    party_leave,
    shared_paint,
    shared_timer,
    shared_point,
    shared_stick,
    shared_angle,
    party_click,
    party_keybd,
    party_buttn
};
