#include "printers.h"

template<typename T>
void fillBuffer(ostream &buffer, const T &data)
{
    buffer << "bulk: ";
    for (const auto &x : data) {
        buffer << x << ",";
    }
    buffer.seekp(-1, ios_base::end);
    buffer << '\n';
}

string fileName(time_point t)
{
    using namespace chrono;

    const auto ms = duration_cast<milliseconds>(t.time_since_epoch()) % 1000;
    const time_t tt = system_clock::to_time_t(t);
    const tm lt = *localtime(&tt);

    ostringstream oss;

    oss << "bulk" << put_time(&lt, "%H%M%S");
    oss << setfill('0') << setw(3) << ms.count();
    oss << ".log";

    return oss.str();
}

ConsolePrinter::ConsolePrinter(CommandProcessor &processor)
{
    m_processor = &processor;
    m_processor->attach(this);
}

ConsolePrinter::~ConsolePrinter()
{
    if (m_processor) {
        m_processor->observerDead(this);
        m_processor->detach(this);
    }
}

void ConsolePrinter::update()
{
    if (m_processor) {
        ostringstream out;
        fillBuffer(out, *m_processor->data());
        cout << out.str();
    }
}

FilePrinter::FilePrinter(CommandProcessor &processor)
{
    m_processor = &processor;
    m_processor->attach(this);
}

FilePrinter::~FilePrinter()
{
    if (m_processor) {
        m_processor->observerDead(this);
        m_processor->detach(this);
    }
}

void FilePrinter::update()
{
    if (m_processor) {
        ofstream out;
        out.open(fileName(m_processor->time()));
        if (out.is_open()) {
            fillBuffer(out, *m_processor->data());
            out.close();
        }
    }
}
