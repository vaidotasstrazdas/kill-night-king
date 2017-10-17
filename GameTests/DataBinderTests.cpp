#include <QApplication>
#include <QSpinBox>
#include <QLineEdit>

#include "DataBinderTests.h"

static int argc = 0;

DataBinderTests::DataBinderTests()
    : m_app(new QApplication(argc, nullptr))
{
}

DataBinderTests::~DataBinderTests()
{
}

void DataBinderTests::SpinBoxValueChangesAreReflectedToViewModelObject()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject obj(0);
    QSpinBox spinBox;

    // Act & Assert
    DataBinder::BindControlToData(spinBox, obj, &vm);

    spinBox.setValue(20);
    QVERIFY(20 == obj.GetValue());

    spinBox.setValue(30);
    QVERIFY(30 == obj.GetValue());
}

void DataBinderTests::SpinBoxInitialValueIsSetIfItExists()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject obj(0);
    QSpinBox spinBox;
    spinBox.setValue(30);

    // Act
    DataBinder::BindControlToData(spinBox, obj, &vm);

    // Assert
    QVERIFY(30 == obj.GetValue());
}

void DataBinderTests::LineEditValueChangesAreReflectedToViewModelObject()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject obj(0);
    QLineEdit lineEdit;

    // Act & Assert
    DataBinder::BindControlToData(lineEdit, obj, &vm);

    lineEdit.setText("100");
    QVERIFY(100 == obj.GetValue());

    lineEdit.setText("1000");
    QVERIFY(1000 == obj.GetValue());
}

void DataBinderTests::LineEditInitialValueIsSetIfItExists()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject obj(0);
    QLineEdit lineEdit;
    lineEdit.setText("100");

    // Act
    DataBinder::BindControlToData(lineEdit, obj, &vm);

    // Assert
    QVERIFY(100 == obj.GetValue());
}

void DataBinderTests::LineEditIsMadeInvalidForInvalidValue()
{
    // Arrange
    ViewModelBase vm;
    ViewModelIntObject obj(0);
    QLineEdit lineEdit;

    // Act & Assert
    DataBinder::BindControlToData(lineEdit, obj, &vm);

    lineEdit.setText("abc");
    QVERIFY(!obj.IsValid());
}
