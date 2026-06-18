YNN_ELEMENTWISE_KERNEL(arch_flag::avx512bw, quantize_fp32_to_int8_1x64_x86_avx512bw, quantize_int8, nullptr, float32x1_t, float32x1_t, int32x1_t, int8x1_t)
YNN_ELEMENTWISE_KERNEL(arch_flag::avx512bw, quantize_fp32_to_uint8_1x64_x86_avx512bw, quantize_uint8, nullptr, float32x1_t, float32x1_t, int32x1_t, uint8x1_t)
