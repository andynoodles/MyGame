#include "App.hpp"

unsigned long App::Update() {
    TimeUpdate();
    ScoreUpdate();
    PacmanMoveProcess();
    GhostMoveProcess();
    FoodCollision();
	GhostCollision();
    GhostStateProcess(); //must be execute after ghost collsion
	BGMCtrl();


    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    return m_Time.GetElapsedTimeMs();
}

