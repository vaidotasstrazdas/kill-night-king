#pragma once
#include "IViewModelObject.h"

template<typename TValue>
class ViewModelObject
    : public IViewModelObject
{
public:
    ViewModelObject(const TValue& value)
        : m_value(value)
        , m_isValid(false)
    {
    }

    virtual ~ViewModelObject()
    {
    }

    virtual bool IsValid() const override
    {
        return m_isValid;
    }

    virtual void SetIsValid(bool isValid) override
    {
        m_isValid = isValid;
    }

    void operator=(const TValue& other)
    {
        m_value = other;
    }

    TValue GetValue()
    {
        return m_value;
    }

private:
    TValue m_value;
    bool m_isValid;
};

using ViewModelIntObject = ViewModelObject<unsigned int>;
