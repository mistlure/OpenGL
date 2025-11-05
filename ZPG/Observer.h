#pragma once
#include "EnumObservableSubjects.h"

class Observer {
public:
    virtual void onNotify(ObservableSubjects source, const void* subject) = 0;
    virtual ~Observer() = default;
};