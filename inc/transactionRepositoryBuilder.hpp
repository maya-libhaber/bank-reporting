#ifndef TRB__
#define TRB__

#include <string>
#include <unordered_map>
#include <vector>
#include "transaction.hpp"
#include "customer.hpp"
#include "transactionRepository.hpp"
#include "reader.hpp"

namespace reportApp {

class TransactionRepositoryBuilder {
public:
    typedef std::unordered_map<int, Customer> CustomerMap;
    typedef std::vector<std::string> Line;
    typedef std::vector<Line> Lines;
    typedef Lines::iterator LinesIterator;

    TransactionRepository Build(std::pair<LinesIterator, LinesIterator> a_rangeIterator);

private:
    struct tm calculateTimestamp(std::string& a_dateAndtime);
    CustomerMap m_customerMap;
};

}//reportApp

#endif//TRB__
