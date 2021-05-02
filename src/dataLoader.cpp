#include <iostream>     // std::cerr
#include <fstream>
#include <string.h>
#include "dataLoader.hpp"
#include "iReportVisitor.hpp"
#include "customerYearlyVisitor.hpp"
#include "totalCustomerYearlyVisitor.hpp"
#include "specificCustomerVisitor.hpp"

namespace reportApp {

DataLoader::DataLoader(const std::string& a_sourceFile)
{ 
    m_reader = new Reader(a_sourceFile); 
}

DataLoader::~DataLoader() 
{
    delete m_reader;
}

void DataLoader::Load() 
{
    std::pair<Reader::LinesIterator, Reader::LinesIterator> rangeIterator = m_reader->Read();
    TransactionRepositoryBuilder builder;
    TransactionRepository tr = builder.Build(rangeIterator);
    
    CustomerYearlyVisitor customerYearlyVisitor;
    std::cout << "Customer yearly financial data: \n";
    std::cout << "ID    year    sum\n";
    tr.Accept(customerYearlyVisitor);
    std::cout << "\n";

    TotalCustomerYearlyVisitor totalCustomerYearlyVisitor;
    std::cout << "Total yearly financial data: \n";
    std::cout << "year  month  sum\n";
    tr.Accept(totalCustomerYearlyVisitor);
    std::cout << "\n";

    SpecificCustomerVisitor specificCustomerVisitor;
    std::cout << "Specific customer on a specific date: \n";
    std::cout << "id  date  sum\n";
    tr.Accept(specificCustomerVisitor);

}

}//reportApp
