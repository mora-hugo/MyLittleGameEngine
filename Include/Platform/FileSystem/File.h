#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace HC::FileSystem {

    class File {
    public:
        explicit File(const std::string& filePath);


        bool Exists() const;
        [[nodiscard]] std::vector<uint8_t> ReadBytes() const;
        void WriteBytes(const std::vector<uint8_t>& bytes) const;
        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] std::string GetExtension() const;
        void Remove() const;
        [[nodiscard]] std::ifstream GetStream() const { return std::ifstream(path, std::ios::binary); }


        std::string path, name, extension;
    };
}
