#include "ViewModelBaseTests.h"

ViewModelBaseTests::ViewModelBaseTests()
{
}

ViewModelBaseTests::~ViewModelBaseTests()
{
}

void ViewModelBaseTests::IsValidWhenThereAreNoMembers()
{
    // Arrange
    ViewModelBase vm;

    // Assert
    QVERIFY(vm.IsValid());
}

void ViewModelBaseTests::IsValidWhenAllMembersValid()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject objOne(0);
    ViewModelIntObject objTwo(1);
    objOne.SetIsValid(true);
    objTwo.SetIsValid(true);

    // Act
    vm.AddMember(&objOne);
    vm.AddMember(&objTwo);

    // Assert
    QVERIFY(vm.IsValid());
}

void ViewModelBaseTests::IsInvalidWhenAtLeastOneMemberIsInvalid()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject objOne(0);
    ViewModelIntObject objTwo(1);
    objOne.SetIsValid(true);
    objTwo.SetIsValid(false);

    // Act
    vm.AddMember(&objOne);
    vm.AddMember(&objTwo);

    // Assert
    QVERIFY(!vm.IsValid());
}
