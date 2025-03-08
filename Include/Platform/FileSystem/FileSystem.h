#pragma once

#include "File.h"
#include "Directory.h"
#include "FileSystem/FileDirectoryVariant.h"
#include <unordered_map>

namespace HC::FileSystem {
    using FileFunction = std::function<void(const File&, int)>;
    class FileSystem {
    private:
        std::unordered_map<std::string, std::string> virtualMounts;

    public:
        void Mount(const std::string& virtualPath, const std::string& realPath);
        std::string ResolvePath(const std::string& virtualPath) const;
        std::unique_ptr<File> GetFile(const std::string& virtualPath) const;
        std::unique_ptr<Directory> GetDirectory(const std::string& virtualPath) const;

        void ExecuteOnAllFilesRecursive(const FileFunction& func) const;

    private:
        static void ExecuteAllFilesRecursiveWorker(Directory& directory, const FileFunction& func, int depth);
    };
}
