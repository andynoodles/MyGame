#include "App.hpp"

void App::Update() {
    TimeUpdate();
    ScoreUpdate();
	PacmanMoveProcess();
    GhostMoveProcess();
    FoodCollision();


    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

