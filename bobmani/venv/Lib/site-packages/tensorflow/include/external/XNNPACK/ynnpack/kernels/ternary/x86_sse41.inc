YNN_ELEMENTWISE_KERNEL(arch_flag::sse41, subtract_multiply_int32_int32_int32_1x8_x86_sse41, subtract_multiply, nullptr, int32x1_t, int32x1_t, int32x1_t, int32x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::sse41, quantize_fp32_to_uint8_1x16_x86_sse41, quantize_uint8, nullptr, float32x1_t, float32x1_t, int32x1_t, uint8x1_t)
