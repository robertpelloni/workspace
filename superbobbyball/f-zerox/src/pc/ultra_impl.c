#include "pc/ultra64.h"
#include "pc/hal.h"
#include <stdio.h>

// Mock Global Variables (usually defined in ld script or asm)
s32 D_800E4348 = 0; // gCurrentFramebuffer
s32 D_800D46C0 = 0; // gDebugPrintFormat?
s32 D_800D46C8 = 0;
s32 D_800D46D8 = 0;
s32 D_800D46FC = 0;
s32 D_800D471C = 0;
s32 D_800D473C = 0;
s32 D_800D474C = 0;
s32 D_800D476C = 0;
s32 D_800D478C = 0;
s32 D_800D479C = 0;
s32 D_800D47B4 = 0;
s32 D_800D47D0 = 0;
s32 D_800D47EC = 0;
s32 D_800D480C = 0;
s32 D_800D481C = 0;
s32 D_800D4834 = 0;
s32 D_800D4854 = 0;
s32 D_800D4870 = 0;
s32 D_800D488C = 0;
s32 D_800CD520 = 0;
s32 D_80400008 = 0;
s32 D_800E4350 = 0;
s32 D_800E44D0 = 0;
s32 D_800E4650 = 0;
s32 D_800CD170 = 0;
s32 D_800CD174 = 0;
s32 D_800CD178 = 0;
s32 D_800CD17C = 0;
s32 D_800DCE44 = 0;
s32 D_800DCE48 = 0;
s32 D_800DCE60 = 0;
s16 D_800CD16C = 0;
s16 D_800CD044 = 0;
s16 D_80106DA0 = 0;
s32 D_800CD0FC[32]; // Jumptable mock
s16 D_800CD168 = 0;
u8 D_800DCE98[592]; // 4 * 0x94
u8 D_800DD180[256]; // Unknown struct size

// Stubs for functions called by func_80068B20
void func_8008DB98(void) {}
void func_800A4BAC(void) {}
void func_8008DA68(void) {}
void func_800A4B54(void) {}
void func_80085510(void) {}
void func_800FC730(void) {}
void func_8007F500(void) {}
void func_80076848(void) {}
void func_8007D9D0(void) {}
void func_800FD184(s32 arg0) { (void)arg0; }
void func_80069820(void) {}
s32 __osMotorAccess(void* pfs, s32 flag) { (void)pfs; (void)flag; return 0; }

OSTime osGetTime(void) {
    return (OSTime)HAL_GetTimeMillis();
}

void* osViGetCurrentFramebuffer(void) {
    return NULL; // Stub
}

// Stubs for functions called by game_197D0.c
void func_8007F86C(void* a, void* b, void* c, void* d, void* e) { (void)a; }
void func_8007F970(void) {}
void func_8007F9E0(void) {}
void func_8007FA64(void) {}
void func_8007FB80(s32 x, s32 y, void* str) {
    printf("DEBUG PRINT at (%d, %d)\n", x, y);
}
