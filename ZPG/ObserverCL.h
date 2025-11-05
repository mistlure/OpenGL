#pragma once

template<typename T>
class ObserverCL {
public:
    virtual void onNotify(const T& value) = 0;
    virtual ~ObserverCL() = default;
};