#include "commandprocessor.h"

CommandProcessor::CommandProcessor(const string &openSymbol, const string &closeSymbol, size_t blockSize)
    : m_openSymbol(openSymbol)
    , m_closeSymbol(closeSymbol)
    , m_blockSize(blockSize)
{
}

CommandProcessor::~CommandProcessor() { }

void CommandProcessor::observerDead(Observer *o)
{
    if (o && !m_model.empty()) {
        o->update();
    }
}

void CommandProcessor::start()
{
    string line;
    while (true) {
        std::getline(cin, line);
        if (line.empty()) {
            break;
        }
        push(line);
    }
}

time_point CommandProcessor::time() const
{
    return m_time;
}

const vector<string> *CommandProcessor::data() const
{
    return &m_model;
}

void CommandProcessor::push(const string &command)
{

    if (!nested(command)) {
        pop();
        return;
    }

    if (!validCommand(command)) {
        return;
    }

    m_model.emplace_back(move(command));

    if (m_model.size() == 1) {
        m_time = chrono::system_clock::now();
    }

    if (!m_counter && m_model.size() == m_blockSize) {
        pop();
    }
}

void CommandProcessor::pop()
{
    if (!m_model.empty()) {
        notify();
        m_model.clear();
    }
}

bool CommandProcessor::nested(const string &command)
{
    if (command == m_openSymbol) {
        if (++m_counter == 1) {
            return false;
        }
    }
    if (command == m_closeSymbol) {
        if (--m_counter == 0) {
            return false;
        }
    }
    return true;
}

bool CommandProcessor::validCommand(const string &command) const
{
    return !(command == m_openSymbol || command == m_closeSymbol);
}
