#pragma once
#include "TestCollector.h"
#include "DataBinding/ViewModelBase.h"

class ViewModelBaseTests
    : public QObject
{
    Q_OBJECT

    public:
        ViewModelBaseTests();
        virtual ~ViewModelBaseTests();

    private slots:
        void IsValidWhenThereAreNoMembers();
        void IsValidWhenAllMembersValid();
        void IsInvalidWhenAtLeastOneMemberIsInvalid();

};
ADD_TEST(ViewModelBaseTests)
