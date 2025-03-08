#pragma once

#include "File.h"
#include <vector>
#include <functional>
namespace HC::FileSystem {
    class Directory {
    public:
        explicit Directory(const std::string& dirPath);

        [[nodiscard]] bool Exists() const;
        void Create() const;
        void Remove(bool recursive = false) const;
        [[nodiscard]] std::vector<std::unique_ptr<File>> GetFiles() const;
        [[nodiscard]] std::vector<std::unique_ptr<Directory>> GetSubDirectories() const;

        [[nodiscard]] std::vector<std::unique_ptr<class FileDirectoryVariant>> GetContents() const;


        std::string path, name;


    };
}
