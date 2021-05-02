#ifndef DATA_LOADER__
#define DATA_LOADER__

#include <vector>
#include "reader.hpp"

namespace reportApp {

class DataLoader {
public:
    typedef std::unordered_map<int, Customer> CustomerMap;
    typedef std::unordered_map<int, double> TotalPerYear;//year : totalAmount
    typedef std::unordered_map<int, TotalPerYear> CustomersTotalMap;// id: <year:totalAmount>

    typedef std::unordered_map<int, double> TotalPerMonth;//month : totalAmount
    typedef std::unordered_map<int, TotalPerMonth> TotalMonthlyMapPerID;// year: <month:totalAmount>
    typedef std::unordered_map<int, TotalPerMonth> TotalMonthlyBank;// year: <month:totalAmount>

    typedef std::unordered_map<std::string, double> TotalPerDate;//date : totalAmount
    typedef std::unordered_map<int, TotalPerDate> TotalPerCustomerPerDate;// id: <date:totalAmount>

    DataLoader(const std::string& a_sourceFile);
    ~DataLoader();
    
    void Load();
    
private:
    Reader* m_reader;

};

}//reportApp

#endif//DATA_LOADER__
