#include "commandprocessor.h"
#include "printers.h"
#include <sstream>
#include <string>
#include <fstream>

size_t getSize(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    const size_t bulkSize { getSize(argc, argv) };
    CommandProcessor processor("{", "}", bulkSize);
    ConsolePrinter printer(processor);
    FilePrinter fPrinter(processor);
    processor.start();

    return 0;
}

size_t getSize(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "You did not set the bulk size explicity. It will be a 3 commands at "
            "bulk.\n";
        return 3;
    }
    istringstream ss(argv[1]);
    int num;
    if ((ss >> num).fail() || num <= 0) {
        cout << "Wrong size. Bulk size 3 will be used.\n";
        return 3;
    }
    return num;
}
