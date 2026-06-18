YNN_ELEMENTWISE_KERNEL(arch_flag::avx2, quantize_fp32_to_int8_1x32_x86_avx2, quantize_int8, nullptr, float32x1_t, float32x1_t, int32x1_t, int8x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx2, quantize_fp32_to_uint8_1x32_x86_avx2, quantize_uint8, nullptr, float32x1_t, float32x1_t, int32x1_t, uint8x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx2, multiply_int32_fp32_fp32_1x16_x86_avx2, multiply, nullptr, int32x1_t, float32x1_t, float32x1_t, float32x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx2, subtract_multiply_int32_int32_int32_1x16_x86_avx2, subtract_multiply, nullptr, int32x1_t, int32x1_t, int32x1_t, int32x1_t)
