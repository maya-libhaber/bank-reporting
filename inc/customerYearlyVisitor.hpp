#ifndef CUSTOMER_YEARLY_REPORT__
#define CUSTOMER_YEARLY_REPORT__

#include <iostream>
#include "iReportVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {

class CustomerYearlyVisitor : public IReportVisitor {

public:
    ~CustomerYearlyVisitor() { }
    void Visit(CustomerMap& a_customerMap);
    
private:
    void printCustomerYearly(TransactionRepository::CustomersTotalMap customersTotalMap);

};    

}//reportApp

#endif//CUSTOMER_YEARLY_REPORT__
