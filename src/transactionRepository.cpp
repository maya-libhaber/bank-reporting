#include <string>
#include <time.h>       /* time_t, struct tm, time, mktime */
#include <stdlib.h>     /* atof */
#include "transactionRepository.hpp"
#include "iReportVisitor.hpp"

namespace reportApp {

TransactionRepository::TransactionRepository(CustomerMap a_customerMap)
:   m_customerMap(a_customerMap)
{ }

TransactionRepository::CustomerMap& TransactionRepository::GetCustomerMap()
{
    return m_customerMap;
}

void TransactionRepository::Accept(IReportVisitor& visitor)
{
    visitor.Visit(m_customerMap);
}

}//reportApp
