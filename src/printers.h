#ifndef PRINTERS_H
#define PRINTERS_H
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#include "observer.h"
#include "commandprocessor.h"

class ConsolePrinter : public Observer
{
public:
    ConsolePrinter(CommandProcessor &processor);
    ~ConsolePrinter();
    void update() override;

private:
    CommandProcessor *m_processor;

};

class FilePrinter : public Observer
{
public:
    FilePrinter(CommandProcessor &processor);
    ~FilePrinter();
    void update() override;

private:
    CommandProcessor *m_processor;

};

#endif // PRINTERS_H
