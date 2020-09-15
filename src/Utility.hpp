#pragma once

#if __GNUC__ < 8 || __clang__ == 1 && __clang__major__ < 6
    // Includes filesystem from experimental
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    // Includes filesystem from stable
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

#include "fmt/format.h"
#include <string_view>
#include <utility>
#include <QString>
#include <cstdlib>
#include <memory>

namespace Utility {
    template<typename... Args> 
    inline QString QFormat(std::string_view format, Args&&... args) noexcept {
        return QString().fromStdString(fmt::format(format, std::forward<Args>(args)...));
    }

    namespace File {
        inline QString ReadFile(std::string_view name) {
            static auto const s_closer = [](FILE* file) { std::fclose(file); };
            std::unique_ptr<FILE, decltype(s_closer)> file{ std::fopen(name.data(), "r"), s_closer };

            // Opened successfully
            if (file.get()) {
                // Gets the file length
                std::fseek(file.get(), 0l, SEEK_END);
                size_t const len = std::ftell(file.get());
                std::fseek(file.get(), 0l, SEEK_SET);

                QString out{};
                out.reserve(len + 1);

                char key;
                while ((key = std::fgetc(file.get())) != EOF)
                    out += key;

                return out;
            }

            return "";
        }

        inline void WriteFile(std::string_view name, std::string_view data) {
            static auto const s_closer = [](FILE* file) { std::fclose(file); };
            std::unique_ptr<FILE, decltype(s_closer)> file{ std::fopen(name.data(), "w"), s_closer };

            if (file.get())
                fprintf(file.get(), "%s", data.data());
        }

        inline bool Exists(std::string_view file) {
            return fs::exists(file.data());
        }

        inline bool DirExists(std::string_view dir) {
            return fs::is_directory(dir);
        }
    }
}
