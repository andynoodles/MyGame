#include "App.hpp"

unsigned long App::LevelChange(unsigned long InitTime) {

	m_Renderer_LevelUp.Update();

	if(MyElapsedTime() - InitTime > 2000){
		m_CurrentState = State::NEXT_LEVEL_INIT;
	}

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
	
	return MyElapsedTime();
}

