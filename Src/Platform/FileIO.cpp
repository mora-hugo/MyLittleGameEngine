
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <FileIO.h>

HC::File::File(const std::string &path) : filepath(path)
{
}

size_t HC::File::GetFileContentSize() const {
    if(!std::filesystem::exists(filepath)) {
        //std::cerr << "File " << filepath <<" does not exist" << std::endl;
        return 0;
    }
    return std::filesystem::file_size(filepath);

}

HC::FileReader::FileReader(const std::string& path, bool isBinaryFile) : File(path), bIsBinaryFile(isBinaryFile) {

}

void HC::FileReader::Read(uint8_t *data, size_t size) {
    file.read(reinterpret_cast<char*>(data), size);
}

bool HC::FileReader::OpenFile() {
    try {
        file = bIsBinaryFile ?
            std::ifstream(filepath, std::ios::binary)
        :
            std::ifstream(filepath);
    }
    catch (std::ifstream::failure& e) {
    }

    return IsOpen();

}

bool HC::FileReader::CloseFile() {
    if(IsOpen())
        file.close();

    return true;
}

bool HC::FileReader::IsOpen() {
    return file.is_open();
}

HC::FileWriter::FileWriter(const std::string& filepath)  : File(filepath) {

}

bool HC::FileWriter::OpenFile() {
    file = std::ofstream(filepath);
    return IsOpen();
}

bool HC::FileWriter::CloseFile() {
    if(IsOpen())
        file.close();

    return true;
}


void HC::FileWriter::Write(const uint8_t *data, size_t size) {
    file.write(reinterpret_cast<const char*>(data), size);
}

bool HC::FileWriter::IsOpen() {
    return file.is_open();
}
