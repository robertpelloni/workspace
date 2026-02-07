#ifndef _ULTRA64_H_
#define _ULTRA64_H_

#include <PR/ultratypes.h>
#include <PR/os.h>
#include <PR/libaudio.h>

// Controller Button Constants
#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_Z      0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

// Controller Structure
typedef struct {
    u16 button;
    s8  stick_x;
    s8  stick_y;
    u8  errno;
} OSContPad;

#endif
