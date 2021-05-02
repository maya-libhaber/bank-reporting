#ifndef TRANSACTION_REPOSITORY__
#define TRANSACTION_REPOSITORY__

#include <string>
#include <unordered_map>
#include <vector>
#include "customer.hpp" 
#include "transaction.hpp"

namespace reportApp {

class IReportVisitor;

class TransactionRepository {
public:
    typedef std::unordered_map<int, Customer> CustomerMap;
    typedef std::unordered_map<int, double> TotalPerYear;//year : totalAmount
    typedef std::unordered_map<int, TotalPerYear> CustomersTotalMap;// id: <year:totalAmount>
    typedef std::unordered_map<int, double> TotalPerMonth;//month : totalAmount
    typedef std::unordered_map<int, TotalPerMonth> TotalMonthlyMapPerID;// year: <month:totalAmount>
    typedef std::unordered_map<int, TotalPerMonth> TotalMonthlyBank;// year: <month:totalAmount>

    typedef std::unordered_map<std::string, double> TotalPerDate;//date : totalAmount
    typedef std::unordered_map<int, TotalPerDate> TotalPerCustomerPerDate;// id: <date:totalAmount>

    TransactionRepository(CustomerMap a_customerMap);

    void Accept(IReportVisitor& visitor);

    CustomerMap& GetCustomerMap();

    // CustomersTotalMap CalcSumPerYearPerCustomer();

    // TotalMonthlyBank CalcTotalTransactionsPerYearAndMonth();

    // TotalPerCustomerPerDate CalcTotalTransactionsPerDate();

private:
    CustomerMap m_customerMap; 
};

}//reportApp

#endif//TRANSACTION_REPOSITORY__
