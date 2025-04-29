#include "FileSystem/File.h"
#include "Logger.h"
#include <fstream>
#include <FileSystem/Directory.h>

namespace HC::FileSystem {

    File::File(const std::string& filePath)
            : path(filePath), name(fs::path(filePath).stem().string()), extension(fs::path(filePath).extension().string().substr(1)) {}

    bool File::Exists() const {
        return fs::exists(path) && fs::is_regular_file(path);
    }

    std::vector<uint8_t> File::ReadBytes() const {
        if (!Exists()) {
            Logger::LogError("File \"{0}\" not found", path);
            return {};
        }

        std::ifstream file(path, std::ios::binary);
        return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
    }

    void File::WriteBytes(const std::vector<uint8_t>& bytes) const {
        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            Logger::LogError("Failed to write to file \"{0}\"", path);
            return;
        }
        file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }

    std::string File::GetExtension() const {
        return extension;
    }

    void File::Remove() const {
        if (Exists()) {
            fs::remove(path);
        } else {
            Logger::LogError("Cannot delete \"{0}\" because it does not exist", path);
        }
    }

    std::unique_ptr<Directory> File::GetDirectory() const {
        return std::make_unique<Directory>(fs::path(path).parent_path().string());
    }

    std::string File::GetName() const {
        return name;
    }
}
