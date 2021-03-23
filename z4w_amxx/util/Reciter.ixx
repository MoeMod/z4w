
export module Reciter;
export import <string>;
// question / answer
struct Reciter{
    std::string question;
    std::string answer;
};
export Reciter GetRandomReciter() noexcept(false);