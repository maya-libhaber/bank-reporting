#ifndef SPECIFICILY_REPORT__
#define SPECIFICILY_REPORT__

#include <iostream>
#include "iReportVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {

class SpecificCustomerVisitor : public IReportVisitor{
public:
    ~SpecificCustomerVisitor() { }
    void Visit(CustomerMap& a_customerMap);
    
private:
    void printSpecificCustomer(TransactionRepository::TotalPerCustomerPerDate totalPerCustomerPerDate);

};    

}//reportApp

#endif//SPECIFICILY_REPORT__
