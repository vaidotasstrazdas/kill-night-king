#pragma once
#include "ViewModelBase.h"
#include "ViewModelObject.h"

class QLineEdit;
class QObject;
class QSpinBox;

namespace DataBinder
{
    void BindControlToData(QSpinBox& control, ViewModelIntObject& value, ViewModelBase* context);

    void BindControlToData(QLineEdit& control, ViewModelIntObject& value, ViewModelBase* context);
}
