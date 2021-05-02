#include "mu_test.h"
#include "dataLoader.hpp"
#include "reader.hpp"
#include "transaction.hpp"
#include "transactionRepositoryBuilder.hpp"
#include "transactionRepository.hpp"
#include "customer.hpp"
#include "totalCustomerYearlyVisitor.hpp"
#include "specificCustomerVisitor.hpp"
#include "customerYearlyVisitor.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <time.h>

using namespace reportApp;

typedef std::vector<reportApp::Transaction> TransactionVector;
typedef std::unordered_map<int,std::vector<reportApp::Transaction> > SecondMap;
typedef std::unordered_map<int,SecondMap > FirstMap;
typedef std::unordered_map<int, std::unordered_map<int, TransactionVector > > RepoMap;

typedef std::vector<std::string> VectorLines;
typedef VectorLines::iterator VectorIterator;
typedef std::vector<VectorLines> VectorVectors;
typedef VectorVectors::iterator VectorVectorsIt;


UNIT(dataLoader_Test)
    reportApp::DataLoader dataLoader("info.txt");
    dataLoader.Load();
    ASSERT_EQUAL(1,1);

END_UNIT


UNIT(dataLoader_largeInfo_Test)
    reportApp::DataLoader dataLoader("largeInfo.csv");
    dataLoader.Load();
    ASSERT_EQUAL(1,1);

END_UNIT

UNIT(reader_Test)
    Reader reader("info.txt");
    std::pair<Reader::LinesIterator, Reader::LinesIterator> it = reader.Read();
    double res = atof(it.first[0][1].c_str());
    ASSERT_EQUAL(res, 3);

END_UNIT

UNIT(builder_Test)
    Reader reader("info.txt");
    std::pair<Reader::LinesIterator, Reader::LinesIterator> it = reader.Read();
  
    TransactionRepositoryBuilder builder;
    TransactionRepository transactionRepository = builder.Build(it);

    typedef std::unordered_map<int, Customer> CustomerMap;
    CustomerMap customerMap = transactionRepository.GetCustomerMap();
    int res = customerMap.size();
    ASSERT_EQUAL(res, 3);

END_UNIT

struct tm calculateTimestamp(std::string& a_dateAndtime)
{
    const char *time_details = a_dateAndtime.c_str();
    struct tm tm = {};
    strptime(time_details, "%Y-%m-%d %H:%M:%S", &tm);

    return tm;
}

UNIT(transaction_Test)
    std::vector<std::string> tranVec{"50", "2016-10-01 09:55:00"};

    const char *time_details = tranVec[1].c_str();
    struct tm tm = {};
    strptime(time_details, "%Y-%m-%d %H:%M:%S", &tm);

    Transaction transaction1(atof(tranVec[0].c_str()), tm);

    int res = transaction1.GetMonth();

    ASSERT_EQUAL(res, 10);
    tranVec.clear();
END_UNIT

UNIT(customer_Test)
    std::vector <std::vector <std::string> > tranVec{ {"50", "2016-10-01 09:55:00"}, {"100", "2017-10-01 09:59:30"}, {"130", "2017-01-01 09:59:30"}};

    struct tm tm1 = calculateTimestamp(tranVec[0][1]);
    struct tm tm2 = calculateTimestamp(tranVec[1][1]);
    struct tm tm3 = calculateTimestamp(tranVec[1][1]);

    Transaction transaction1(atof(tranVec[0][0].c_str()), tm1);
    Transaction transaction2(atof(tranVec[1][0].c_str()), tm2);
    Transaction transaction3(atof(tranVec[2][0].c_str()), tm3);

    Customer customer(1);
    typedef std::unordered_map<int, Customer> CustomerMap;
    CustomerMap customerMap;
    customerMap.insert(std::pair<int, Customer>(1, customer));
    customer.AddTransaction(transaction1);
    customer.AddTransaction(transaction2);
    customer.AddTransaction(transaction3);

    std::unordered_map<int, double> totalPerYear = customer.GetTotalTransactionsPerYear();

    double res = totalPerYear.at(2017);
    ASSERT_EQUAL(res, 230);
END_UNIT

UNIT(customer1_Test)
    std::vector <std::vector <std::string> > tranVec{ {"50", "2016-10-01 09:55:00"}, {"100", "2017-10-01 09:59:30"}, {"130", "2017-01-01 09:59:30"}};

    struct tm tm1 = calculateTimestamp(tranVec[0][1]);
    struct tm tm2 = calculateTimestamp(tranVec[1][1]);
    struct tm tm3 = calculateTimestamp(tranVec[1][1]);

    Transaction transaction1(atof(tranVec[0][0].c_str()), tm1);
    Transaction transaction2(atof(tranVec[1][0].c_str()), tm2);
    Transaction transaction3(atof(tranVec[2][0].c_str()), tm3);

    Customer customer(1);
    typedef std::unordered_map<int, Customer> CustomerMap;
    CustomerMap customerMap;
    customerMap.insert(std::pair<int, Customer>(1, customer));
    customer.AddTransaction(transaction1);
    customer.AddTransaction(transaction2);
    customer.AddTransaction(transaction3);

    Customer::TotalMonthly totalMonthly = customer.GetTotalTransactionsPerYearAndMonth();

    double res = totalMonthly[2017][10];
    ASSERT_EQUAL(res, 230);
END_UNIT

UNIT(customer2_Test)
    std::vector <std::vector <std::string> > tranVec{ {"50", "2016-10-01 09:55:00"}, {"100", "2017-10-01 09:59:30"}, {"130", "2017-01-01 09:59:30"}};

    struct tm tm1 = calculateTimestamp(tranVec[0][1]);
    struct tm tm2 = calculateTimestamp(tranVec[1][1]);
    struct tm tm3 = calculateTimestamp(tranVec[2][1]);

    Transaction transaction1(atof(tranVec[0][0].c_str()), tm1);
    Transaction transaction2(atof(tranVec[1][0].c_str()), tm2);
    Transaction transaction3(atof(tranVec[2][0].c_str()), tm3);

    Customer customer(1);
    typedef std::unordered_map<int, Customer> CustomerMap;
    CustomerMap customerMap;
    customerMap.insert(std::pair<int, Customer>(1, customer));
    customer.AddTransaction(transaction1);
    customer.AddTransaction(transaction2);
    customer.AddTransaction(transaction3);

    Customer::TotalPerDate totalPerDate = customer.GetTotalTransactionsPerDate();

    double res = totalPerDate["2016-10-1"];
    ASSERT_EQUAL(res, 50);
END_UNIT


UNIT(transactionRepo_Test)
    std::string date1 = "2016-10-01 09:55:00";
    std::string date2 = "2017-10-01 09:59:30";
    std::string date3 = "2017-01-01 09:59:30";

    std::vector <std::vector <std::string> > tranVec{ {"50", date1}, {"100", date2}, {"130", date3}};

    struct tm tm1 = calculateTimestamp(tranVec[0][1]);
    struct tm tm2 = calculateTimestamp(tranVec[1][1]);
    struct tm tm3 = calculateTimestamp(tranVec[1][1]);

    Transaction transaction1(atof(tranVec[0][0].c_str()), tm1);
    Transaction transaction2(atof(tranVec[1][0].c_str()), tm2);
    Transaction transaction3(atof(tranVec[2][0].c_str()), tm3);

    Customer customer(1);
    typedef std::unordered_map<int, Customer> CustomerMap;
    CustomerMap customerMap;
    customerMap.insert(std::pair<int, Customer>(1, customer));
    customer.AddTransaction(transaction1);
    customer.AddTransaction(transaction2);
    customer.AddTransaction(transaction3);

    std::unordered_map<int, double> totalPerYear = customer.GetTotalTransactionsPerYear();

    TransactionRepository transactionRepository(customerMap);
    CustomerYearlyVisitor customerYearlyVisitor;
    transactionRepository.Accept(customerYearlyVisitor);
    customerYearlyVisitor.Visit(customerMap);

    ASSERT_PASS();
    
END_UNIT

TEST_SUITE(BankReporting_Test)
    TEST(dataLoader_Test)
    TEST(dataLoader_largeInfo_Test)
    TEST(reader_Test)
    TEST(builder_Test)
    TEST(transaction_Test)
    TEST(customer_Test)
    TEST(customer1_Test)
    TEST(customer2_Test)
    TEST(transactionRepo_Test)
END_SUITE


