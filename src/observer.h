#ifndef IOBSERVER_H
#define IOBSERVER_H

class Observer
{
public:
    virtual ~Observer() {};
    virtual void update() = 0;

protected:
    Observer();
};

#endif // IOBSERVER_H
