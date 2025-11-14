#pragma once
#include <vector>
#include "Observer.h"

class Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notify(ObservableSubjects source) {
        for (auto observer : observers) {
            if (observer) observer->onNotify(source);
        }
    }

private:
    std::vector<Observer*> observers;
};
