#include "ViewModelBase.h"

ViewModelBase::ViewModelBase()
{
}

ViewModelBase::~ViewModelBase()
{
}

bool ViewModelBase::IsValid() const
{
    return m_members.empty() || std::all_of(m_members.begin(), m_members.end(), [](const IViewModelObject* member)
    {
        return member->IsValid();
    });
}

void ViewModelBase::AddMember(const IViewModelObject* object)
{
    m_members.push_back(object);
}
