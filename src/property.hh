#pragma once
#include "component.hh"

class Property : public Component {
public:

    virtual ~Property() {}
    virtual void progress() = 0;

private:

};