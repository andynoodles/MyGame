#include "KeyBoard.hpp"

void KeyBorad::ReadKeyBorad(){
    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        resultStr += "A";
	} else if (Util::Input::IsKeyDown(Util::Keycode::B)) {
        resultStr += "B";
    } else if (Util::Input::IsKeyDown(Util::Keycode::C)) {
        resultStr += "C";
    } else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        resultStr += "D";
    } else if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        resultStr += "E";
    } else if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        resultStr += "F";
    } else if (Util::Input::IsKeyDown(Util::Keycode::G)) {
        resultStr += "G";
    } else if (Util::Input::IsKeyDown(Util::Keycode::H)) {
        resultStr += "H";
    } else if (Util::Input::IsKeyDown(Util::Keycode::I)) {
        resultStr += "I";
    } else if (Util::Input::IsKeyDown(Util::Keycode::J)) {
        resultStr += "J";
    } else if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        resultStr += "K";
    } else if (Util::Input::IsKeyDown(Util::Keycode::L)) {
        resultStr += "L";
    } else if (Util::Input::IsKeyDown(Util::Keycode::M)) {
        resultStr += "M";
    } else if (Util::Input::IsKeyDown(Util::Keycode::N)) {
        resultStr += "N";
    } else if (Util::Input::IsKeyDown(Util::Keycode::O)) {
        resultStr += "O";
    } else if (Util::Input::IsKeyDown(Util::Keycode::P)) {
        resultStr += "P";
    } else if (Util::Input::IsKeyDown(Util::Keycode::Q)) {
        resultStr += "Q";
    } else if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        resultStr += "R";
    } else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        resultStr += "S";
    } else if (Util::Input::IsKeyDown(Util::Keycode::T)) {
        resultStr += "T";
    } else if (Util::Input::IsKeyDown(Util::Keycode::U)) {
        resultStr += "U";
    } else if (Util::Input::IsKeyDown(Util::Keycode::V)) {
        resultStr += "V";
    } else if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        resultStr += "W";
    } else if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        resultStr += "X";
    } else if (Util::Input::IsKeyDown(Util::Keycode::Y)) {
        resultStr += "Y";
    } else if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        resultStr += "Z";
    } else if (Util::Input::IsKeyDown(Util::Keycode::BACKSPACE)) {
        if (resultStr.size() == 1) 
            resultStr = " ";
        else
            resultStr.erase(resultStr.size() - 1);
    }
}

std::string KeyBorad::GetResult(){
    return resultStr;
}

void KeyBorad::Clear(){
    resultStr = "";
}