#pragma once
class IViewModelObject
{
public:
    virtual ~IViewModelObject() {}

    virtual bool IsValid() const = 0;
    virtual void SetIsValid(bool isValid) = 0;
};
