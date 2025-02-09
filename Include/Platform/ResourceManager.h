#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>
#include <FileIO.h>
#include <Singleton.h>

#include <Assertion.h>
#include <format>
#include <stb_image/stb_image.h>

namespace HC {
    class IResource {
    public:
        explicit IResource(const std::string& filepath) : filepath(filepath) { }
        virtual ~IResource() = default;
        virtual bool Load() = 0;
        virtual bool Save() = 0;

        std::string GetFilePath() const {
            return filepath;
        }

    protected:
        std::string filepath;
    };

    template<typename T>
    class Resource : public IResource {
    public:
        explicit Resource(const std::string& filepath) : IResource(filepath) { }
        bool Load() override = 0;
        bool Save() override = 0;
    };

    class FileResource : public Resource<FileResource> {
    public:
        explicit FileResource(const std::string& filepath, bool bIsBinaryFile = false) : Resource(filepath), reader(filepath, bIsBinaryFile), writer(filepath) {

        }


        bool Load() override {
            if(!reader.OpenFile()) {
                return false;
            }
            bytes.resize(reader.GetFileContentSize());
            reader.Read(bytes.data(), reader.GetFileContentSize());
            return reader.CloseFile();

        }

        bool Save() override {
            writer.OpenFile();
            writer.Write(bytes.data(), bytes.size());
            return writer.CloseFile();

        }
    public:
        std::vector<uint8_t> bytes;
    private:
        FileWriter writer;
        FileReader reader;


    };

    class ConfigResource : public FileResource {
    public:
        explicit ConfigResource(const std::string& filepath) : FileResource(filepath) {

        }

        bool Load() override {
            bool bSuccess = FileResource::Load();
            if (!bSuccess) {
                return false;
            }

            size_t i = 0;
            // if the line starts with #, it is a comment
            while (i < bytes.size()) {
                if(bytes[i] == '#') {
                    while (bytes[i] != '\n') {
                        i++;
                    }
                    continue;
                }
                // if the line is not a comment, we parse it
                std::vector<char> line;
                while (i < bytes.size() && bytes[i] != '\n') {
                    line.push_back(bytes[i]);
                    i++;
                }
                auto pair = ParseLine(std::string(line.begin(), line.end()));
                Trim(pair.first);
                Trim(pair.second);
                i++;
                if(pair.first.empty() || pair.second.empty()) {
                    continue;
                }
                config.insert(pair);
            }
            bytes.clear();
            return true;
        }

        std::pair<std::string, std::string> ParseLine(const std::string& line) {
            // Get a representation of a line using a pair of key and value
            std::vector<char> key;
            std::vector<char> value;
            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] == '=') {
                    i++;
                    while (i < line.size()) {
                        value.push_back(line[i]);
                        i++;
                    }
                    break;
                }
                key.push_back(line[i]);
            }
        return {std::string(key.begin(), key.end()), std::string(value.begin(), value.end())};
    }


        template <typename T, typename L>
        bool AreSame() { return std::is_same<T, L>::value; }

    bool GetValue(const std::string& key, std::string & outValue) {
        auto it = config.find(key);
        if (it != config.end()) {
            outValue = it->second;
        }
        return it != config.end();
    }

    template<typename T>
    bool GetValue(const std::string& key, T& outValue) {
        std::string value;
        if (!GetValue(key, value)) {
            return false;
        }
        if (AreSame<T,float>()) {
            outValue = std::stof(value);
        }
        else if (AreSame<T, double>()) {
            outValue = std::stod(value);
        }
        else if (AreSame<T, int>()) {
            outValue = std::stoi(value);
        }
        else if (AreSame<T, bool>()) {
            outValue = (value == "true" ||  value == "1");
        }
        else {
            return false;
        }
        return true;
    }

    private:
        static std::string Trim(std::string& str)
        {
            str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
            str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
            return str;
        }

    private:
    std::map<std::string, std::string> config;
};


    class ResourceManager : public Singleton<ResourceManager> {
    public:
        template<typename T, typename... Args>
        std::shared_ptr<T> Load(const std::string& filepath, Args... args) {
            std::shared_ptr<T> resource;
            auto it = resources.find(filepath);
            if (it != resources.end()) {
                resource = std::dynamic_pointer_cast<T>(it->second);
            }

            if (!resource) {
                resource = std::make_shared<T>(filepath, args...);
                // if the loading is not successful, we reset the newly created ptr
                if (!resource->Load()) {
                    resource.reset();
                    return nullptr;
                }
                resources[filepath] = std::static_pointer_cast<IResource>(resource);
            }
            return resource;
        }


        bool Unload(const std::string& filepath) {
            auto it = resources.find(filepath);
            if (it != resources.end()) {
                it->second.reset();
                resources.erase(it);
                return true;
            }
            return false;
        }

    private:
        std::map<std::string, std::shared_ptr<IResource>> resources;
    };

}