#include "FileSystem/FileDirectoryVariant.h"
#include "Logger.h"

namespace HC::FileSystem {

    FileDirectoryVariant::FileDirectoryVariant(std::unique_ptr<File> file) : variant(std::move(file)) {}

    FileDirectoryVariant::FileDirectoryVariant(std::unique_ptr<Directory> directory) : variant(std::move(directory)) {}

    bool FileDirectoryVariant::IsFile() const {
        return std::holds_alternative<std::unique_ptr<File>>(variant);
    }

    bool FileDirectoryVariant::IsDirectory() const {
        return std::holds_alternative<std::unique_ptr<Directory>>(variant);
    }

    File& FileDirectoryVariant::GetFile() const {
        if (!IsFile()) {
            Logger::LogError("Variant is not a file");
            static File emptyFile("");
            return emptyFile;
        }
        return *std::get<std::unique_ptr<File>>(variant);
    }

    Directory& FileDirectoryVariant::GetDirectory() const {
        if (!IsDirectory()) {
            Logger::LogError("Variant is not a directory");
            static Directory emptyDirectory("");
            return emptyDirectory;
        }
        return *std::get<std::unique_ptr<Directory>>(variant);
    }
}
