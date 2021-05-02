#ifndef YEARLY_REPORT__
#define YEARLY_REPORT__

#include <iostream>
#include "iReportVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {

class TotalCustomerYearlyVisitor : public IReportVisitor {

public:
    ~TotalCustomerYearlyVisitor() { }
    void Visit(CustomerMap& a_customerMap);
    
private:
    void printTotalYearly(TransactionRepository::TotalMonthlyBank totalMonthlyBank);
};    

}//reportApp

#endif//YEARLY_REPORT__
