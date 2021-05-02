#include "customerYearlyVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {

void CustomerYearlyVisitor::Visit(CustomerMap& a_customerMap) 
{
   TransactionRepository::CustomersTotalMap customersTotalMap;

    for(auto& ent : a_customerMap) {
        int currCustomerID = ent.first;
        TransactionRepository::TotalPerYear totalPerYear;
        totalPerYear = ent.second.GetTotalTransactionsPerYear();
        customersTotalMap.insert(std::pair<int, TransactionRepository::TotalPerYear> (currCustomerID, totalPerYear));
    }

    printCustomerYearly (customersTotalMap);
}

void CustomerYearlyVisitor::printCustomerYearly(TransactionRepository::CustomersTotalMap customersTotalMap)
{
    TransactionRepository::TotalPerYear totalPerYear;

    for(auto it = std::begin(customersTotalMap); it != std::end(customersTotalMap); ++it) {
        std::cout << it->first << "\t";
        totalPerYear = it->second;
        for(auto it1 = std::begin(totalPerYear); it1 != std::end(totalPerYear); ++it1) {
            std::cout << it1->first << "\t"<< it1->second;
        }
        std::cout << std::endl;
    }
}

}
