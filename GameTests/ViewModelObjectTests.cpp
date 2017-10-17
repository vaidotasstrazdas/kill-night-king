#include "ViewModelObjectTests.h"

ViewModelObjectTests::ViewModelObjectTests()
{

}

ViewModelObjectTests::~ViewModelObjectTests()
{
}

void ViewModelObjectTests::IsInvalidInitially()
{
    // Arrange
    ViewModelIntObject obj(0);

    // Assert
    QVERIFY(!obj.IsValid());
}

void ViewModelObjectTests::CanBeMadeValid()
{
    // Arrange
    ViewModelIntObject obj(0);

    // Act
    obj.SetIsValid(true);

    // Assert
    QVERIFY(obj.IsValid());
}

void ViewModelObjectTests::CanBeMadeInvalid()
{
    // Arrange
    ViewModelIntObject obj(0);

    // Act & Assert
    obj.SetIsValid(true);
    QVERIFY(obj.IsValid());

    obj.SetIsValid(false);
    QVERIFY(!obj.IsValid());
}

void ViewModelObjectTests::AssignmentWorksAsExpectedForInteger()
{
    // Arrange
    ViewModelIntObject obj(0);

    // Act
    obj = 123;

    // Assert
    QVERIFY(123 == obj.GetValue());
}

void ViewModelObjectTests::AssignmentWorksAsExpectedForString()
{
    // Arrange
    ViewModelObject<std::string> obj("");

    // Act
    obj = "123abc";

    // Assert
    QVERIFY("123abc" == obj.GetValue());
}
