#ifndef EMBED_GPU_SPECS_H_
#define EMBED_GPU_SPECS_H_
#include <string>

namespace xla::gpu { 
const std::string& get_a100_pcie_80();
const std::string& get_a100_sxm_40();
const std::string& get_a100_sxm_80();
const std::string& get_a6000();
const std::string& get_b200();
const std::string& get_b300();
const std::string& get_h100_pcie();
const std::string& get_h100_sxm();
const std::string& get_mi200();
const std::string& get_p100();
const std::string& get_v100();
}  // namespace xla::gpu

#endif  // EMBED_GPU_SPECS_H_
