#ifndef CUSTOMER__
#define CUSTOMER__

#include <string>
#include <unordered_map>
#include <vector>
#include "transaction.hpp"

namespace reportApp {

class Customer {
public:
    typedef std::vector<Transaction> Transactions;
    typedef std::unordered_map<int, std::unordered_map<int, Transactions>> IndexedTransactions;
    typedef std::unordered_map<int, double> TotalPerYear;//year : totalAmount

    typedef std::unordered_map<int, double> TotalPerMonth;//month : totalAmount
    typedef std::unordered_map<int, TotalPerMonth> TotalMonthly;// year: <month:totalAmount>

    typedef std::unordered_map<std::string, double> TotalPerDate;//date : totalAmount

    explicit Customer(int a_id);

    void AddTransaction(Transaction a_transaction);
    int GetID();
    TotalPerYear GetTotalTransactionsPerYear(); 
    TotalMonthly GetTotalTransactionsPerYearAndMonth(); 
    TotalPerDate GetTotalTransactionsPerDate(); 

private:
    int m_id;
    IndexedTransactions m_indexedTransactions;
};

}//reportApp

#endif//CUSTOMER__
