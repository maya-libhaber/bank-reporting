#include "transaction.hpp"

namespace reportApp {

Transaction::Transaction(double a_amount, struct tm a_tm)
:   m_amount(a_amount)
,   m_tm(a_tm)
{ }

int Transaction::GetYear()
{
    return m_tm.tm_year + 1900;
}

int Transaction::GetMonth()
{
    return m_tm.tm_mon + 1;
}

std::string Transaction::GetDate()
{
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();

    std::string date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day); 
    return date;
}

int Transaction::GetDay()
{
    return m_tm.tm_mday;
}

double Transaction::GetAmount()
{
    return m_amount;
}

} //reportApp