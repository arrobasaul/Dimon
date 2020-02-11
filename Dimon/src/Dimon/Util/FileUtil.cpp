#include "dmpch.h"
#include "FileUtil.h"
namespace Dimon {
	std::string Dimon::getFileContents(const std::string& filePath)
	{
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            throw std::runtime_error("Unable to open file: " + filePath);
        }

        std::stringstream stream;

        stream << inFile.rdbuf();
        return stream.str();
	}
}
