#pragma once

#include <string_view>

namespace Build {
    constexpr std::string_view Root = ROOT_DIR;

    #ifdef DEBUG
        constexpr std::string_view Type = "Debug";
        constexpr bool IsDebug = true;
    #else
        constexpr std::string_view Type = "Release";
        constexpr bool IsDebug = false;
    #endif
}
