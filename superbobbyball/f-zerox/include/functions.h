#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

void func_800B6910(s32, u8);

/* src/math_utils.c (game_2B20.c) - Math & Vectors */
s32 func_8006A918(void); // Math_Rand
s32 func_8006A9E0(f32 arg0); // Math_RoundF
void func_8006AFC8(struct UnkStruct_10* arg0, s32 arg1, s32 arg2, s32 arg3); // SetVectors
void func_8006AFE4(struct UnkStruct_10* arg0, s32 arg1, s32 arg2, s32 arg3); // SetVectors (Alias)
void func_8006B000(struct UnkStruct_8* arg0, s32 arg1, s32 arg2, s32 arg3); // SetVector8

/* src/linked_list.c (game_446D0.c) - Linked List */
void func_800AAF9C(struct UnkStruct_1* arg0); // List_InitNode

/* src/game_73F0.c - Utils */
s32 func_8006D3F0(s32 arg0); // BoundsCheck_0_22

/* src/debug_text.c (game_197D0.c) - Debug & Framebuffer */
void func_8007F94C(void); // UpdateFramebufferPointer
void func_8007FC68(s32 arg0); // DrawDebugInt
// void func_8007FB80(...); // DrawText (Signature unknown/varargs?)

/* src/audio_state.c (game_511D0.c) - Audio State */
void func_800BA2D0(s8 arg0);
void func_800BA2E0(s8 arg0);
void func_800BAFF4(void);
void func_800BB038(void);

/* src/game_11CF0.c - Init */
void func_80079080(void); // InitLoop

/* src/game_1AE0.c - State */
void func_80067AE0(void); // RotateThreeGlobals

/* src/game_1F510.c - Machines */
void func_80088CAC(s32 arg0);
void func_8008D7E8(void); // InitAllMachines

/* src/game_194E0.c - State Setter */
void func_8007F4E0(s32 arg0, s32 arg1);

/* src/game_4FFB0.c - Low Mem */
void func_800B6A18(void);

/* src/audio_util.c (game_14440.c) - Audio Util */
void func_8007E0AC(s32 arg0);
s8 func_8007E10C(s32 arg0);

/* src/math_utils.c - Decompiled Logic */
void func_80068B20(void);
// Dependencies of func_80068B20
void func_8008DB98(void);
void func_800A4BAC(void);
void func_8008DA68(void);
void func_800A4B54(void);
void func_80085510(void);
void func_800FC730(void);
void func_8007F500(void);
void func_80076848(void);
void func_8007D9D0(void);
void func_800FD184(s32 arg0);

/* src/game_459A0.c - Variable Setters */
void func_800B0784(s32 arg0);
void func_800B0790(s32 arg0);

#endif
