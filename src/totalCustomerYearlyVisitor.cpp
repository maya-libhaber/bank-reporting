#include "totalCustomerYearlyVisitor.hpp"
#include "transactionRepository.hpp"

namespace reportApp {

void TotalCustomerYearlyVisitor::Visit(CustomerMap& a_customerMap)
{
    TransactionRepository::TotalMonthlyBank totalMonthlyBank;
    TransactionRepository::TotalMonthlyMapPerID resultMap;
    
    for(auto& ent : a_customerMap) {
        TransactionRepository::TotalMonthlyMapPerID totalMonthlyMapPerID;// year: <month:totalAmount>
        TransactionRepository::TotalPerMonth totalPerMonth;//month:totalAmount
        totalMonthlyMapPerID = ent.second.GetTotalTransactionsPerYearAndMonth();

        for(auto& ent1 : totalMonthlyMapPerID) {
            int year = ent1.first; //year
            totalPerMonth = ent1.second;//month:totalAmount

            if(resultMap.find(year) != resultMap.end()) {
                for(auto& ent2 : totalPerMonth) {
                    int month = ent2.first;
                    double sum = ent2.second;

                    if(totalPerMonth.find(month) != totalPerMonth.end()) {
                        resultMap[year][month] += sum;
                    }else {
                        resultMap[year][month] = sum;
                    }
                }
            } else {
                resultMap[year] = totalPerMonth;
            }
        }
        
    }
    printTotalYearly(resultMap);
}

void TotalCustomerYearlyVisitor::printTotalYearly(TransactionRepository::TotalMonthlyBank totalMonthlyBank)// year:month:sum
{
    TransactionRepository::TotalPerMonth totalPerMonth;
    for(auto it = std::begin(totalMonthlyBank); it != std::end(totalMonthlyBank); ++it) {
        std::cout << it->first << "\t";
        totalPerMonth = it->second;
        for(auto it1 = std::begin(totalPerMonth); it1 != std::end(totalPerMonth); ++it1) {
            std::cout << it1->first << "\t"<< it1->second;
        }
        std::cout << std::endl;
    }
}

}
