#pragma once

#include <variant>
#include "File.h"
#include "Directory.h"

namespace HC::FileSystem {

    class FileDirectoryVariant {
    public:
        explicit FileDirectoryVariant(std::unique_ptr<File> file);
        explicit FileDirectoryVariant(std::unique_ptr<Directory> directory);

        [[nodiscard]] bool IsFile() const;
        [[nodiscard]] bool IsDirectory() const;

        [[nodiscard]] File& GetFile() const;
        [[nodiscard]] Directory& GetDirectory() const;

    private:
        std::variant<std::unique_ptr<File>, std::unique_ptr<Directory>> variant;
    };
}
