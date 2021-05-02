#include <string>
#include <time.h>       /* time_t, struct tm, time, mktime */
#include <stdlib.h>     /* atof */
#include <utility>      // std::pair
#include "transactionRepositoryBuilder.hpp"

namespace reportApp {

TransactionRepository TransactionRepositoryBuilder::Build(std::pair<Reader::LinesIterator, Reader::LinesIterator> a_rangeIterator)
{    
    while (a_rangeIterator.first != a_rangeIterator.second) { 
        
        int id = atoi((*a_rangeIterator.first)[0].c_str());
        
        struct tm brokenDownTime = calculateTimestamp((*a_rangeIterator.first)[2]);

        double amount = atof((*a_rangeIterator.first)[1].c_str());
        
        Transaction transaction (amount, brokenDownTime);

        if(m_customerMap.find(id) == m_customerMap.end()) { 
            Customer customer(id);
            customer.AddTransaction(transaction);
            m_customerMap.insert(std::pair<int, Customer> (id, customer));
        } else {
            m_customerMap.at(id).AddTransaction(transaction);
        }
    
        a_rangeIterator.first++;
    }

    TransactionRepository res(m_customerMap);
    return res;
}

struct tm TransactionRepositoryBuilder::calculateTimestamp(std::string& a_dateAndtime)
{
    const char *time_details = a_dateAndtime.c_str();
    struct tm tm;
    strptime(time_details, "%Y-%m-%d %H:%M:%S", &tm);

    return tm;
}

}//reportApp
