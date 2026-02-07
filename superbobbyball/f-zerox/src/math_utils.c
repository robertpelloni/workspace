#include "common.h"

/**
 * @brief Initialize the game system and all subsystems
 *
 * Called during startup to initialize the entire game state including
 * audio system, graphics system, input system, and core game systems.
 * Uses state check to avoid re-initialization on soft resets.
 */
void System_Init(void) {
    D_800DCE44 = -1;
    D_800DCE48 = 0x8000;

    // Check if already initialized using magic number
    if (D_800DCE60 != 0x20DE1529) {
        func_8008DB98(); // Audio system init (cold boot)
        D_800DCE60 = 0x20DE1529; // Set initialized flag
        func_800A4BAC(); // Additional audio init
    } else {
        func_8008DA68(); // Audio system re-init (warm boot)
        func_800A4B54(); // Audio shutdown/restart
    }

    func_80085510(); // Machine system init
    func_800FC730(); // Graphics system init
    func_8007F500(); // Memory system init
    func_80076848(); // Input system init
    func_8007D9D0(); // Timing system init

    D_800CD16C = 1; // Mark system as fully initialized
}

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80068BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80068DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80068F04.s")

/**
 * @brief Execute the current game state function from the state machine
 *
 * Routes to the appropriate state handler based on the current state index.
 * Uses a jump table with bounds checking to select the correct function.
 *
 * @return The result code from the state handler (0 for success, non-zero for errors)
 */
s32 StateMachine_ExecuteCurrentState(void) {
    s32 result = 0; // Default return value

    if (D_800CD044 != 3) { // If not in debug/demo mode
        if (D_80106DA0 != 0) { // If state machine is active
            typedef s32 (*StateHandler)(void);
            // Calculate index with modulo from state value
            StateHandler handler = (StateHandler)D_800CD0FC[D_800DCE44 & 0x1F];
            result = handler();
        }
    }

    func_800FD184(result); // Process state result
    return result;
}

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80069700.s")

/**
 * @brief Initialize or reset the machine state array
 *
 * Scans through an array of machine state structures (each 0x94 bytes)
 * and resets all fields for inactive machines. Active machines are skipped.
 * Also resets a special machine at a fixed memory offset.
 */
void Controller_ResetMachineStates(void) {
    u8* end = D_800DCE98 + (0x94 * 4); // End of machine array (4 machines * 0x94 bytes)
    u8* curr = end;
    u8* start = D_800DCE98;

    // Iterate backwards through machine states
    while (1) {
        u8 isActive = *(curr + 0x6B);
        if (isActive != 0) {
            // Skip active machine, continue to previous
            curr -= 0x94;
            if (curr < start) break;
            continue;
        }

        // Clear all fields for inactive machine
        curr -= 0x94;
        *(s16*)(curr + 0x80) = 0; // Unknown field A
        *(s16*)(curr + 0x7E) = 0; // Unknown field B
        *(s16*)(curr + 0x7C) = 0; // Unknown field C
        *(s16*)(curr + 0x7A) = 0; // Unknown field D
        *(s16*)(curr + 0x82) = 0; // Unknown field E
        *(u8*)(curr + 0x71) = 0;  // Flag A
        *(u8*)(curr + 0x70) = 0;  // Flag B
        *(u8*)(curr + 0x6F) = 0;  // Flag C
        *(u8*)(curr + 0x6E) = 0;  // Flag D
        *(u8*)(curr + 0x6D) = 0;  // Flag E
        *(u8*)(curr + 0x6C) = 0;  // Flag F
        *(s32*)(curr + 0x84) = 0; // Unknown pointer/value

        if (curr < start) break;
    }

    // Reset special machine at fixed offset
    u8* specialMachine = D_800DD180;
    *(u8*)(specialMachine + 0x6D) = 0;
    u8 temp = *(u8*)(specialMachine + 0x6D); // 0
    *(s16*)(specialMachine + 0x7E) = 0;
    *(s16*)(specialMachine + 0x7C) = 0;
    *(s16*)(specialMachine + 0x7A) = 0;
    *(s16*)(specialMachine + 0x82) = 0;
    *(u8*)(specialMachine + 0x70) = 0;
    *(u8*)(specialMachine + 0x6F) = 0;
    *(u8*)(specialMachine + 0x6E) = 0;
    *(u8*)(specialMachine + 0x6C) = temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80069820.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80069D44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80069ED0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_80069F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006A00C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006A3AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006A6E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/osSetTime.s")

/**
 * @brief Set the time-related global variables
 *
 * @param timeValue1 First timing value (likely milliseconds or ticks)
 * @param timeValue2 Second timing value (likely seconds or frame count)
 */
void System_SetTime(s32 timeValue1, s32 timeValue2) {
    D_800CD178 = timeValue1;
    D_800CD17C = timeValue2;
}

/**
 * @brief XOR Shift Random Number Generator
 *
 * Implementation of a custom pseudorandom number generator using XOR shift
 * with two state variables. This is likely the game's main RNG used for
 * AI behavior, particle effects, and random game events.
 *
 * The algorithm:
 * - Uses two 32-bit state values (D_800CD170 and D_800CD174)
 * - Updates state1 using linear congruential generation
 * - Conditionally updates state2 based on its LSB
 * - Returns XOR of the two states
 *
 * @return 32-bit pseudo-random value
 */
s32 Math_Rand(void) {
    s32 state1 = D_800CD170;
    u32 next_state1 = (u32)state1 * 0x41C64E6D + 0x3039;

    s32 state2 = D_800CD174;
    if (state2 & 1) {
        D_800CD170 = next_state1;
        state2 ^= 0x11020;
        D_800CD174 = state2;
    }

    state1 = D_800CD170;
    s32 final_state2 = (u32)state2 >> 1;
    D_800CD174 = final_state2;

    return state1 ^ final_state2;
}

/**
 * @brief Round a floating point number to the nearest integer
 *
 * Uses standard rounding where values at exactly 0.5 round to the nearest
 * integer with ties rounding away from zero.
 *
 * Examples:
 * - Math_RoundF(3.4f) → 3
 * - Math_RoundF(3.6f) → 4
 * - Math_RoundF(-2.4f) → -2
 * - Math_RoundF(-2.6f) → -3
 *
 * @param value Input float value to round
 * @return Rounded integer value
 */
s32 Math_RoundF(f32 value) {
    if (value < 0.0f) {
        return (s32)(value - 0.5f);
    }
    return (s32)(value + 0.5f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006AA38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006ADE4.s")

/**
 * @brief Set a dual-vector structure (both vectors to same values)
 *
 * Sets two 3-component vectors (likely RGB colors or XYZ positions) in the
 * structure to identical values. This is commonly used for color gradients
 * or symmetric positioning.
 *
 * @param vecStruct Pointer to the UnkStruct_10 containing two vectors
 * @param compX Value for X/Red component in both vectors
 * @param compY Value for Y/Green component in both vectors
 * @param compZ Value for Z/Blue component in both vectors
 */
void Vector_SetDual(struct UnkStruct_10* vecStruct, s32 compX, s32 compY, s32 compZ) {
    vecStruct->unk0 = vecStruct->unk4 = compX;
    vecStruct->unk1 = vecStruct->unk5 = compY;
    vecStruct->unk2 = vecStruct->unk6 = compZ;
}

/**
 * @brief Set a dual-vector structure (alias of Vector_SetDual)
 *
 * Identical functionality to Vector_SetDual. Likely created by compiler
 * inlining or function duplication for optimization purposes.
 *
 * @param vecStruct Pointer to the UnkStruct_10 containing two vectors
 * @param compX Value for X/Red component in both vectors
 * @param compY Value for Y/Green component in both vectors
 * @param compZ Value for Z/Blue component in both vectors
 */
void Vector_SetDual_Alias(struct UnkStruct_10* vecStruct, s32 compX, s32 compY, s32 compZ) {
    vecStruct->unk0 = vecStruct->unk4 = compX;
    vecStruct->unk1 = vecStruct->unk5 = compY;
    vecStruct->unk2 = vecStruct->unk6 = compZ;
}

/**
 * @brief Set the tail 3-component vector in UnkStruct_8
 *
 * Sets the vector components at offsets 0x8, 0x9, 0xA which appear to be
 * the last three bytes of the structure. Likely used for XYZ positions,
 * RGB colors, or velocity vectors.
 *
 * @param vecStruct Pointer to the UnkStruct_8
 * @param compX Value for component at offset 0x8
 * @param compY Value for component at offset 0x9
 * @param compZ Value for component at offset 0xA
 */
void Vector_SetTriple(struct UnkStruct_8* vecStruct, s32 compX, s32 compY, s32 compZ) {
    vecStruct->unk8 = compX;
    vecStruct->unk9 = compY;
    vecStruct->unkA = compZ;
}

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006B010.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006B07C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006B18C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006B33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006B908.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006BB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006BBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006BC84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006BFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006C278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006C378.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006C520.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006CB0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006CC98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006D03C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/math_utils/func_8006D2E0.s")
