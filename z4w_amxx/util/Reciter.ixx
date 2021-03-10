module;

#include <string>

export module Reciter;
// question / answer
struct Reciter{
    std::string question;
    std::string answer;
};
export Reciter GetRandomReciter() noexcept(false);