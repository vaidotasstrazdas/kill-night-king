#pragma once
#include "TestCollector.h"
#include "DataBinding/DataBinder.h"
#include "DataBinding/ViewModelBase.h"

class QApplication;

class DataBinderTests
    : public QObject
{
    Q_OBJECT

    public:
        DataBinderTests();
        virtual ~DataBinderTests();

    private slots:
        void SpinBoxValueChangesAreReflectedToViewModelObject();
        void SpinBoxInitialValueIsSetIfItExists();
        void LineEditValueChangesAreReflectedToViewModelObject();
        void LineEditInitialValueIsSetIfItExists();
        void LineEditIsMadeInvalidForInvalidValue();

    private:
        std::unique_ptr<QApplication> m_app;

};
ADD_TEST(DataBinderTests)
