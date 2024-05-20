#include "App.hpp"

unsigned long App::LevelUp(unsigned int InitTime) {
	if(MyElapsedTime() - InitTime > 1000){
		m_CurrentState = State::UPDATE;
	}

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
	
	return MyElapsedTime();
}

