#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <vector>
#include <string>
#include <queue>
#include <chrono>
#include <ctime>
#include <iostream>

#include "iprocessor.h"

using namespace std;
using time_point = chrono::system_clock::time_point;

class CommandProcessor : public iProcessor
{
public:
    CommandProcessor(const string &openSymbol, const string &closeSymbol, size_t blockSize);
    ~CommandProcessor();
    void observerDead(Observer *o) override;
    void start();

    time_point time() const;
    const vector<string> *data() const;

private:
    string m_openSymbol;
    string m_closeSymbol;
    size_t m_blockSize = 0;

    vector<string> m_model;
    time_point m_time;
    int m_counter = 0;

    void push(const string &command);
    void pop();
    bool nested(const string &command);
    bool validCommand(const string &command) const;
};

#endif // COMMANDPROCESSOR_H
