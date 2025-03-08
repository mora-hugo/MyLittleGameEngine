#include "FileSystem/Directory.h"
#include "FileSystem/FileDirectoryVariant.h"
#include "Logger.h"
#include <filesystem>

namespace HC::FileSystem {

    Directory::Directory(const std::string &dirPath)
            : path(dirPath), name(fs::path(dirPath).filename().string()) {}

    bool Directory::Exists() const {
        return fs::exists(path) && fs::is_directory(path);
    }

    void Directory::Create() const {
        if (!Exists())
            fs::create_directories(path);
        else
            Logger::LogError("Directory \"{0}\" already exists", path);
    }

    void Directory::Remove(bool recursive) const {
        if (Exists()) {
            if (recursive)
                fs::remove_all(path);
            else
                fs::remove(path);
        } else {
            Logger::LogError("Cannot delete \"{0}\" because it does not exist", path);
        }
    }

    std::vector<std::unique_ptr<File>> Directory::GetFiles() const {
        std::vector<std::unique_ptr<File>> files;
        if (!Exists()) {
            Logger::LogError("Directory \"{0}\" not found", path);
            return files;
        }

        for (const auto &entry: fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path()))
                files.emplace_back(std::make_unique<File>(entry.path().string()));
        }
        return files;
    }

    std::vector<std::unique_ptr<Directory>> Directory::GetSubDirectories() const {
        std::vector<std::unique_ptr<Directory>> dirs;
        if (!Exists()) {
            Logger::LogError("Directory \"{0}\" not found", path);
            return dirs;
        }

        for (const auto &entry: fs::directory_iterator(path)) {
            if (fs::is_directory(entry.path()))
                dirs.emplace_back(std::make_unique<Directory>(entry.path().string()));
        }
        return dirs;
    }

    std::vector<std::unique_ptr<FileDirectoryVariant>> Directory::GetContents() const {
        std::vector<std::unique_ptr<FileDirectoryVariant>> contents;
        if (!Exists()) {
            Logger::LogError("Directory \"{0}\" not found", path);
            return contents;
        }

        for (const auto &entry: fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path()))
                contents.emplace_back(
                        std::make_unique<FileDirectoryVariant>(std::make_unique<File>(entry.path().string())));
            else if (fs::is_directory(entry.path()))
                contents.emplace_back(
                        std::make_unique<FileDirectoryVariant>(std::make_unique<Directory>(entry.path().string())));
        }
        return contents;
    }


}

