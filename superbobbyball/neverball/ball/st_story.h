#ifndef ST_STORY_H
#define ST_STORY_H

#include "state.h"

extern struct state st_story;

void story_set(const char *image, const char *text, struct state *next);

#endif
