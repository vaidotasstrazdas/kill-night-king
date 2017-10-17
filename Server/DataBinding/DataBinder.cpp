#include <QLineEdit>
#include <QSpinBox>

#include "DataBinder.h"

namespace DataBinder
{
    void BindControlToData(QSpinBox& control, ViewModelIntObject& value, ViewModelBase* context)
    {
        context->AddMember(&value);

        if (control.value())
        {
            value = control.value();
            value.SetIsValid(true);
        }

        QObject::connect(&control, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), context, [&value](int newValue)
        {
            value = newValue;
            value.SetIsValid(true);
        });
    }

    void BindControlToData(QLineEdit& control, ViewModelIntObject& value, ViewModelBase* context)
    {
        context->AddMember(&value);

        bool isValid = false;
        const auto initialValue = control.text().toUInt(&isValid);
        if (isValid)
        {
            value = initialValue;
            value.SetIsValid(true);
        }

        QObject::connect(&control, static_cast<void(QLineEdit::*)(const QString&)>(&QLineEdit::textChanged), context, [&value](const QString& text)
        {
            bool isValid = false;
            unsigned int newValue = text.toUInt(&isValid);
            value.SetIsValid(isValid);
            if (!isValid)
                return;

            value = newValue;
        });
    }
}
