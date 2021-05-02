#include "specificCustomerVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {
    
void SpecificCustomerVisitor::Visit(CustomerMap& a_customerMap)
{
    TransactionRepository::TotalPerCustomerPerDate totalPerCustomerPerDate;
    TransactionRepository::TotalPerDate totalPerDate; 

    for(auto& ent : a_customerMap) {
        int currCustomerID = ent.first;
        totalPerDate = ent.second.GetTotalTransactionsPerDate();// <string, double>  date : sum
        totalPerCustomerPerDate.insert(std::pair<int, TransactionRepository::TotalPerDate> (currCustomerID, totalPerDate));
    }

    printSpecificCustomer (totalPerCustomerPerDate);

}

void SpecificCustomerVisitor::printSpecificCustomer(TransactionRepository::TotalPerCustomerPerDate totalPerCustomerPerDate)
{
    TransactionRepository::TotalPerDate totalPerDate;

    for(auto it = std::begin(totalPerCustomerPerDate); it != std::end(totalPerCustomerPerDate); ++it) {
    std::cout << it->first << "\t";
    totalPerDate = it->second;
    for(auto it1 = std::begin(totalPerDate); it1 != std::end(totalPerDate); ++it1) {
        std::cout << it1->first << "\t"<< it1->second;
    }
    std::cout << std::endl;
    }
}

}
