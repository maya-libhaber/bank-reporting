#ifndef TRANSACTION__
#define TRANSACTION__

#include <string>
#include <time.h>

namespace reportApp {

class Transaction {
public:
    Transaction(double a_amount, struct tm a_tm);

    int GetYear();
    int GetMonth();
    std::string GetDate();
    int GetDay();
    double GetAmount();

private:
    mutable double m_amount;
    struct tm m_tm;
};

}//reportApp

#endif//TRANSACTION__
