YNN_DOT_KERNEL(arch_flag::avx512vnni, dot_uint8_int8_int32_4x8x16_1x4x16_avx512vnni, 4, 8, 16, 1, 4, 16, /*flags=*/dot_flag::consistent_arithmetic, uint8_t, int8_t, int32_t)
YNN_DOT_KERNEL(arch_flag::avx512vnni, dot_uint8_int8_int32_8x8x16_1x4x16_avx512vnni, 8, 8, 16, 1, 4, 16, /*flags=*/dot_flag::consistent_arithmetic, uint8_t, int8_t, int32_t)
YNN_DOT_KERNEL(arch_flag::avx512vnni, dot_uint8_int8_int32_4x4x16_1x4x16_avx512vnni, 4, 4, 16, 1, 4, 16, /*flags=*/dot_flag::consistent_arithmetic, uint8_t, int8_t, int32_t)
YNN_DOT_KERNEL(arch_flag::avx512vnni, dot_uint8_int8_int32_8x4x16_1x4x16_avx512vnni, 8, 4, 16, 1, 4, 16, /*flags=*/dot_flag::consistent_arithmetic, uint8_t, int8_t, int32_t)
