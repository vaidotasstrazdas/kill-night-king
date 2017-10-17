#pragma once
#include "TestCollector.h"
#include "DataBinding/ViewModelObject.h"

class ViewModelObjectTests
    : public QObject
{
    Q_OBJECT

    public:
        ViewModelObjectTests();
        virtual ~ViewModelObjectTests();

    private slots:
        void IsInvalidInitially();
        void CanBeMadeValid();
        void CanBeMadeInvalid();
        void AssignmentWorksAsExpectedForInteger();
        void AssignmentWorksAsExpectedForString();

};
ADD_TEST(ViewModelObjectTests)
