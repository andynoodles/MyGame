#include "App.hpp"
#include "Util/Input.hpp"

float SpeedX, SpeedY, SpeedMultiplier = 1;

void App::Update() {
    
    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        SpeedX = 0;
        SpeedY = 5;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        SpeedX = -5;
        SpeedY = 0;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        SpeedX = 0;
        SpeedY = -5;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        SpeedX = 5;
        SpeedY = 0;
    }
    m_Pacman->Move({SpeedX, SpeedY}, SpeedMultiplier);

	m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}