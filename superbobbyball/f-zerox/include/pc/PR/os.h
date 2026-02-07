#ifndef _OS_H_
#define _OS_H_

#include <PR/ultratypes.h>

typedef s32 OSTime;

OSTime osGetTime(void);
void* osViGetCurrentFramebuffer(void);

#endif
