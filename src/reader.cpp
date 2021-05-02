#include "reader.hpp"

namespace reportApp {

Reader::Reader(const std::string& a_sourceFile)
: m_filePath(a_sourceFile)
{ }

std::pair<Reader::LinesIterator, Reader::LinesIterator> Reader::Read()
{
    std::ifstream file(m_filePath);//TODO: THROW exception

    for (std::string inputLine; getline(file, inputLine); ) {

        if(!inputLine.empty()) {
            Line line = Proccess(inputLine);
            m_lines.push_back(line);
        }
    }

    file.close();
   
    return std::make_pair(m_lines.begin(), m_lines.end());
}

Reader::Line Reader::Proccess(std::string& a_lineContent)
{
    const char fieldDelimiter = ',';
    const char endOfLine = '\n';

    std::string tempStr(a_lineContent);
    size_t delimiterPos = 0;
    size_t start = 0;

    Line lineVector;

    while ((delimiterPos = tempStr.find(fieldDelimiter)) != std::string::npos 
                || (delimiterPos = tempStr.find(endOfLine)) != std::string::npos) {

        std::string token = tempStr.substr(0, delimiterPos);
        lineVector.push_back(token);
        start = delimiterPos + 1;
        tempStr = tempStr.substr(start, tempStr.size());
    }

    lineVector.push_back(tempStr);
    
    return lineVector;
}

}//reportApp
