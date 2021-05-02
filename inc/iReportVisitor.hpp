#ifndef IREPORT_VISITOR__
#define IREPORT_VISITOR__

#include <unordered_map>

namespace reportApp {

class TotalCustomerYearlyVisitor;
class SpecificCustomerVisitor;
class CustomerYearlyVisitor;
class Customer;

class IReportVisitor {
public:
    typedef std::unordered_map<int, Customer> CustomerMap;

    virtual ~IReportVisitor() = 0;
    virtual void Visit(CustomerMap& customerMap) = 0;
    
};    

inline IReportVisitor::~IReportVisitor() { }


}//reportApp

#endif//IREPORT_VISITOR__
