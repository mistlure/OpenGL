#pragma once
#include "EnumObservableSubjects.h"

class Observer {
public:
    virtual void onNotify(ObservableSubjects source) = 0;
    virtual ~Observer() = default;
};