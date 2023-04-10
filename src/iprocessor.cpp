#include "iprocessor.h"

iProcessor::iProcessor() { }

void iProcessor::attach(Observer *o)
{
    m_observers.push_back(o);
}

void iProcessor::detach(Observer *o)
{
    m_observers.remove(o);
}

void iProcessor::notify()
{
    for (const auto o : m_observers) {
        o->update();
    }
}
