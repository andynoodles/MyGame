#include "App.hpp"

unsigned long App::Update() {
    ScoreUpdate();
    PacmanMoveProcess();
    GhostMoveProcess();
    FoodCollision();
	GhostCollision();
    GhostStateProcess(); //must be execute after ghost collsion
	BGMCtrl();
	BonusCtrl();
    TimeOutFlashText();

    if(m_Score->IsFoodAllEaten() || Util::Input::IsKeyUp(Util::Keycode::J) ) {
        m_CurrentState = State::LEVEL_CHANGE;
        LOG_DEBUG("Win:)");
    }
    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    return MyElapsedTime();
}

