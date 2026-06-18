YNN_ELEMENTWISE_KERNEL(arch_flag::avx, multiply_fp32_fp32_fp32_1x16_x86_avx, multiply, nullptr, float32x1_t, float32x1_t, float32x1_t, float32x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx, multiply_add_fp32_fp32_fp32_1x16_x86_avx, multiply_add, nullptr, float32x1_t, float32x1_t, float32x1_t, float32x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx, clamp_fp32_fp32_fp32_1x16_x86_avx, clamp, nullptr, float32x1_t, float32x1_t, float32x1_t, float32x1_t)
