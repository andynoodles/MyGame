#include "App.hpp"

unsigned long App::LevelChange(unsigned long InitTime) {
	m_Renderer_LevelUp.Update();
	
	if(MyElapsedTime() - InitTime > LEVEL_UP_ANIMATION_DURATION){
		m_CurrentState = State::NEXT_LEVEL_INIT;
	}

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
	
	return MyElapsedTime();
}

