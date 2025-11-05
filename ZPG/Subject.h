#pragma once
#include <vector>
#include "ObserverCL.h"

template<typename T>
class Subject {
public:
    void attach(ObserverCL<T>* observer) {
        observers.push_back(observer);
    }

    void notify(const T& value) {
        for (auto* observer : observers) {
            if (observer) observer->onNotify(value);
        }
    }

private:
    std::vector<ObserverCL<T>*> observers;
};
