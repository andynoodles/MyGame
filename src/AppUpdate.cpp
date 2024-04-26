#include "App.hpp"

void App::Update() {
    TimeUpdate();
    ScoreUpdate();
    PacmanMoveProcess();
    GhostMoveProcess();
    FoodCollision();
	GhostCollision();
    GhostStateProcess();
	BGMCtrl();


    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit() || m_Pacman->IsDead() || m_Score->IsFoodAllEaten() ) {
        m_CurrentState = State::END;
    }
}

