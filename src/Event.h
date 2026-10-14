#pragma once

#include <vector>
#include <functional>

#include "Log.h"


class Log;

template <typename T> //call data / callback input type
class Event
{
private:
    std::vector<std::function<void(T)>> subscribers;

public:
    Event();

    void Subscribe(std::function<void(T)> callbackFn);
    void Unsubscribe(std::function<void(T)> callbackFn);
    void Call(T);
};

//============================ due to some bs with generics needs to be also defined in header. see https://stackoverflow.com/questions/22055591/undefined-reference-to-a-generic-object-in-c

template <typename T>
Event<T>::Event()
{
    this->subscribers = std::vector<std::function<void(T)>>();
}

template <typename T>
void Event<T>::Subscribe(std::function<void(T)> callbackFn)
{
    this->subscribers.push_back(callbackFn);
}

template <typename T>
void Event<T>::Unsubscribe(std::function<void(T)> callbackFn)
{
    
    for(auto it = subscribers.begin(); it != subscribers.end(); it++)
    {
        if(*it = callbackFn)
        { 
            this->subscribers.erase(it); 
                
            return;
        }
    }
    Log.FatalError("Event cannot unsubscribe (subscriber not found)");
}

template<typename T>
void Event<T>::Call(T data)
{
    for(auto it = subscribers.begin(); it != subscribers.end(); it++)
    {
        (*it)(data);
    }
}
