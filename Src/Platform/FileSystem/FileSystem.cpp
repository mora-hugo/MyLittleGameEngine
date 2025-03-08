#include "FileSystem/FileSystem.h"
#include "Logger.h"

namespace HC::FileSystem {
    void FileSystem::Mount(const std::string& virtualPath, const std::string& realPath) {
        if (!fs::exists(realPath)) {
            Logger::LogError("Real path \"{0}\" does not exist", realPath);
            return;
        }
        virtualMounts[virtualPath] = realPath;
    }

    std::string FileSystem::ResolvePath(const std::string& virtualPath) const {
        for (const auto& entry : virtualMounts) {
            if (virtualPath.find(entry.first) == 0)
                return entry.second + virtualPath.substr(entry.first.length());
        }
        Logger::LogError("Virtual path \"{0}\" not found", virtualPath);
        return "";
    }

    std::unique_ptr<File> FileSystem::GetFile(const std::string& virtualPath) const {
        std::string realPath = ResolvePath(virtualPath);
        if (realPath.empty()) return nullptr;
        return std::make_unique<File>(realPath);
    }

    std::unique_ptr<Directory> FileSystem::GetDirectory(const std::string& virtualPath) const {
        std::string realPath = ResolvePath(virtualPath);
        if (realPath.empty()) return nullptr;
        return std::make_unique<Directory>(realPath);
    }

    void FileSystem::ExecuteOnAllFilesRecursive(const FileFunction &func) const {
        for (const auto& entry : virtualMounts) {
            auto dir = GetDirectory(entry.first);
            if (dir) {
                ExecuteAllFilesRecursiveWorker(*dir, func, 0);
            }
        }
    }

    void FileSystem::ExecuteAllFilesRecursiveWorker(Directory &directory, const FileFunction &func, int depth) {
        auto files = directory.GetFiles();
        for (const auto& file : files) {
            func(*file, depth);
        }

        auto subDirs = directory.GetSubDirectories();
        for (const auto& subDir : subDirs) {
            ExecuteAllFilesRecursiveWorker(*subDir, func, depth + 1);
        }
    }


}
