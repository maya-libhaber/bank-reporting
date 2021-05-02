#include <string>
#include <utility>      // std::pair
#include "customer.hpp"

namespace reportApp {

Customer::Customer(int a_id)
:    m_id(a_id)
{ }

void Customer::AddTransaction(Transaction a_transaction)
{
    int year = a_transaction.GetYear();
    int month = a_transaction.GetMonth();

    typedef std::vector<Transaction> TransactionVector;
    typedef std::unordered_map<int, TransactionVector> MonthToTransaction;

    if(m_indexedTransactions.find(year) == m_indexedTransactions.end()) {
        
        TransactionVector transactionVector;
        MonthToTransaction monthToTransaction; 

        transactionVector.push_back(a_transaction);
        monthToTransaction.insert(std::make_pair(month, transactionVector));
        m_indexedTransactions.insert(std::make_pair(year,monthToTransaction));

    } else if(m_indexedTransactions[year].find(month) == m_indexedTransactions[year].end()) {
            
        TransactionVector transactionVector;

        transactionVector.push_back(a_transaction);
        m_indexedTransactions[year].insert(std::make_pair(month, transactionVector));

    } else {
        m_indexedTransactions[year][month].push_back(a_transaction);
    }
}

Customer::TotalPerYear Customer::GetTotalTransactionsPerYear() 
{
    Customer::TotalPerYear totalPerYear;

    for(auto& ent1 : m_indexedTransactions) {
        auto& outer_key = ent1.first;//year
        auto& inner_map = ent1.second;//map<month:vectorTransaction>
        double totalTransactions = 0;

        for(auto& ent2 :  inner_map) {
            auto& inner_value = ent2.second;//vector<Transaction>

            for(auto& vec : inner_value) {
                totalTransactions += vec.GetAmount();
            }
        }

        totalPerYear.insert(std::pair<int, double>(outer_key, totalTransactions));//inserting when finished to iterate the all year

    }
    return totalPerYear;
}

Customer::TotalMonthly Customer::GetTotalTransactionsPerYearAndMonth()
{
    TotalMonthly totalMonthly;
    TotalPerMonth totalPerMonth;

    for(auto& ent1 : m_indexedTransactions) {
        auto& outer_key = ent1.first;//year
        auto& inner_map = ent1.second;//map<month:vectorTransaction>
   
        for(auto& ent2 :  inner_map) {
            auto& inner_key   = ent2.first;//month
            auto& inner_value = ent2.second;//vector<Transaction>
            double totalTransactions = 0;

            for(auto& vec : inner_value) {
                totalTransactions += vec.GetAmount();
            }

            totalPerMonth.insert(std::pair<int, double>(inner_key, totalTransactions));//inserting when finished to iterate the month
        }

        totalMonthly.insert(std::pair<int,TotalPerMonth >(outer_key, totalPerMonth));//inserting when finished to iterate the year
    }
    return totalMonthly;
}

Customer::TotalPerDate Customer::GetTotalTransactionsPerDate()
{
    TotalPerDate totalPerDate;//date : sum

    for(auto& ent1 : m_indexedTransactions) {
        auto& inner_map = ent1.second;//map<month:vectorTransaction>

        for(auto& ent2 :  inner_map) {
            auto& inner_value = ent2.second;//vector<Transaction>
            std::string date;//year-month-day

            for(auto& vec : inner_value) {
                double sum = 0;
                date = vec.GetDate();
                for(auto& vec1 : inner_value) {
                    if(date == vec1.GetDate()) {
                        sum += vec1.GetAmount();
                    }
                }
                totalPerDate.insert(std::pair<std::string, double> (date, sum));
            }
        }
    }
    return totalPerDate;
}

}//reportApp
