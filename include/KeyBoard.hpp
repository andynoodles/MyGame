#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "Util/Input.hpp"
#include <string>

class KeyBorad : Util::Input{
private:
    std::string resultStr;
public:
    void ReadKeyBorad(); // read all 26 letters
    std::string GetResult();
    void Clear();
};

#endif