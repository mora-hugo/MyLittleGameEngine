#pragma once
#include <fstream>
#include <cstdint>

namespace HC {
    class File {
    public:
        File(const std::string& path);
        ~File() = default;
        virtual bool IsOpen() = 0;

        size_t GetFileContentSize() const;

        virtual bool CloseFile() = 0;
        inline std::string GetFilePath() const {return filepath;}
    protected:
        virtual bool OpenFile() = 0;
    protected:
        std::string filepath;

    };

    class FileReader : public File {
    public:
        FileReader(const std::string& path, bool isBinaryFile = false);
        bool OpenFile() override;
        bool CloseFile() override;
        void Read(uint8_t *data, size_t size);
        bool IsOpen() override;

    private:
        std::ifstream file;
        bool bIsBinaryFile = false;

    };

    class FileWriter : public File {
    public:
        FileWriter(const std::string& path);

        bool OpenFile() override;
        bool CloseFile() override;
        void Write(const uint8_t* data, size_t size);
        bool IsOpen() override;
    private:
        std::ofstream file;
    };
}



