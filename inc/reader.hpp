#ifndef READER__
#define READER__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "transactionRepositoryBuilder.hpp"

namespace reportApp {

class Reader {
public:
    typedef std::vector<std::string> Line;
    typedef std::vector<Line> Lines;
    typedef Lines::iterator LinesIterator;
    
    Reader(const std::string& a_sourceFile);

    std::pair<LinesIterator,LinesIterator> Read();

private:
    Line Proccess(std::string& a_lineContent);
    const int LINE_BUFFER_SIZE = 256;
    const std::string& m_filePath;
    Lines m_lines;

};    

}//reportApp

#endif//READER__
