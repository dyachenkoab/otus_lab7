#ifndef IPROCESSOR_H
#define IPROCESSOR_H
#include "observer.h"
#include <list>
using namespace std;
class iProcessor
{
public:
    virtual ~iProcessor() {};
    virtual void attach(Observer *o);
    virtual void detach(Observer *o);
    virtual void notify();
    virtual void observerDead(Observer *o) = 0;

protected:
    iProcessor();

private:
    list<Observer*> m_observers;

};

#endif // IPROCESSOR_H
