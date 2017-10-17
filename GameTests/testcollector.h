#pragma once

#include <memory>
#include <map>
#include <string>

#include <QObject>
#include <QTest>

namespace TestCollector
{
    typedef std::map<std::string, std::shared_ptr<QObject> > TestList;

    inline TestList& GetTestList()
    {
       static TestList list;
       return list;
    }

    inline int RunAllTests(int argc, char **argv)
    {
        int result = 0;
        for (const auto& i : GetTestList())
            result += QTest::qExec(i.second.get(), argc, argv);

        return result;
    }

    template <class T>
    class UnitTestClass
    {
    public:
        UnitTestClass(const std::string& pTestName)
        {
            auto& testList = TestCollector::GetTestList();
            if (0 == testList.count(pTestName))
                testList.insert(std::make_pair(pTestName, std::make_shared<T>()));
        }
    };
}

#define ADD_TEST(className) static TestCollector::UnitTestClass<className> \
    test(#className);
