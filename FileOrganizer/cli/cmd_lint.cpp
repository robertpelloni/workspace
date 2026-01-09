#include "fo/core/registry.hpp"
#include "fo/core/lint_interface.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

void lint_command(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Usage: fo_cli lint <path> [options]\n";
        return;
    }

    auto linter = fo::core::Registry<fo::core::ILinter>::instance().create("std");
    if (!linter) {
        std::cerr << "Error: Standard linter not found.\n";
        return;
    }

    std::vector<std::filesystem::path> paths;
    for (const auto& arg : args) {
        if (arg.rfind("--", 0) != 0) {
             paths.push_back(arg);
        }
    }

    auto results = linter->lint(paths);

    std::cout << "Lint Results:\n";
    for (const auto& res : results) {
        std::cout << "[" << (res.type == fo::core::LintType::EmptyFile ? "EMPTY FILE" :
                             res.type == fo::core::LintType::EmptyDirectory ? "EMPTY DIR" :
                             res.type == fo::core::LintType::BrokenSymlink ? "BROKEN LINK" : "TEMP FILE") 
                  << "] " << res.path.string() << " (" << res.details << ")\n";
    }
}
