#pragma once
#include <mutex>
#include <sstream>

class Printer :
        public std::ostringstream
{
public:
    Printer() = default;
    ~Printer() override;
private:
    static std::mutex cout_mtx;
};