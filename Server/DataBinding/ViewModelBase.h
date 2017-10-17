#pragma once
#include <QObject>

#include "ViewModelObject.h"

class ViewModelBase
    : public QObject
{
    Q_OBJECT
public:
    ViewModelBase();
    virtual ~ViewModelBase();

    bool IsValid() const;
    void AddMember(const IViewModelObject* object);

private:
    std::vector<const IViewModelObject*> m_members;
};
