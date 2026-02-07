#include "pc/ultra64.h"
#include <stdio.h>

void n_alSynRemovePlayer(ALSynth *s, ALPlayer *p) {
    (void)s;
    (void)p;
    // Stub
}

void n_alSynFreeFX(ALSynth *s, void *fx) {
    (void)s;
    (void)fx;
    // Stub
}

void n_alSeqpDelete(ALSeqPlayer *seqp) {
    (void)seqp;
    // Stub
}

// Functions called by game_511D0.c (Audio State)
void func_800BAFA4(s32 arg0) { (void)arg0; }
void func_800B9ED4(void) {}
void func_800B6994(void) {}
void func_800B82C8(void) {}
void func_800B7CA4(void) {}
void func_800B8598(void) {}
s32 func_800B5FB0(void) { return 0; }
void func_800B6F58(void) {}
void func_800B079C(s32 a, s32 b) { (void)a; (void)b; }
void func_800B6910(s32 a, u8 b) { (void)a; (void)b; }

// Stubs for game_14440.c
void func_800BAF30(s32 arg0) { (void)arg0; }
void func_800BB078(void) {}

// Variables used in game_511D0.c (externs)
s8 D_800D1A3C = 0;
s8 D_800D1A20 = 0;
u8 D_800D1A48 = 0;
s8 D_800D19E0 = 0;
s8 D_800D1A18 = 0;
s8 D_800D1A0C = 0;
s32 D_800D1C18 = 0;

// Variables used in game_14440.c
s8 D_800D4690 = 0;
