/*
 * Story / Cutscene State
 */

#include <stdio.h>
#include <string.h>

#include "gui.h"
#include "transition.h"
#include "image.h"
#include "config.h"
#include "common.h"
#include "video.h"
#include "st_story.h"
#include "st_title.h"

static char story_image[256];
static char story_text[1024];
static struct state *next_state = &st_title;

static int image_id;

void story_set(const char *img, const char *txt, struct state *nxt)
{
    SAFECPY(story_image, img);
    SAFECPY(story_text, txt);
    next_state = nxt;
}

static int story_action(int tok, int val)
{
    if (tok == GUI_BACK)
    {
        return goto_state(next_state);
    }
    return 1;
}

static int story_gui(void)
{
    int root;

    if ((root = gui_vstack(0)))
    {
        if (story_image[0])
        {
            int w = video.device_w * 0.8f;
            int h = video.device_h * 0.5f;
            image_id = gui_image(root, story_image, w, h);
        }

        gui_space(root);

        gui_multi(root, story_text, GUI_MED, gui_wht, gui_blk);

        gui_space(root);

        gui_state(root, "Continue", GUI_MED, GUI_BACK, 0);

        gui_layout(root, 0, 0);
    }
    return root;
}

static int story_enter(struct state *st, struct state *prev, int intent)
{
    return transition_slide(story_gui(), 1, intent);
}

static int story_leave(struct state *st, struct state *next, int id, int intent)
{
    return transition_slide(id, 0, intent);
}

static void story_paint(int id, float t)
{
    gui_paint(id);
}

static int story_click(int b, int d)
{
    if (gui_click(b, d))
        return story_action(gui_token(gui_active()), gui_value(gui_active()));
    return 1;
}

static int story_buttn(int b, int d, int device_id)
{
    if (d)
    {
        int active = gui_active();
        if (config_tst_d(CONFIG_JOYSTICK_BUTTON_A, b))
            return story_action(gui_token(active), gui_value(active));
        if (config_tst_d(CONFIG_JOYSTICK_BUTTON_B, b))
            return story_action(GUI_BACK, 0);
    }
    return 1;
}

static int story_keybd(int c, int d)
{
    if (d)
    {
        if (c == 27 || c == 13 || c == 32) /* ESC, ENTER, SPACE */
            return story_action(GUI_BACK, 0);
    }
    return 1;
}

struct state st_story = {
    story_enter,
    story_leave,
    story_paint, /* paint */
    NULL, /* timer */
    NULL, /* point */
    NULL, /* stick */
    NULL, /* angle */
    story_click,
    story_keybd,
    story_buttn
};
