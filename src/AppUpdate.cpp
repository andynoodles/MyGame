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
	AddLifeDetect();

    // Press C to turn on cheat
    if(Util::Input::IsKeyUp(Util::Keycode::C) ) {
        if (cheatMode){
            cheatMode = false;
        }
        else{
            cheatMode = true;
        }
    }

    // skip level cheat(Press J to skip)
    if(m_Score->IsFoodAllEaten() || Util::Input::IsKeyUp(Util::Keycode::J) ) {
        currentLevel.AddLevel(1);
        if(currentLevel.GetCurrentLevel() == TOTAL_LEVEL){
            m_ScoreBoard->addScore("", m_Score->GetVisibleScore());
            m_ScoreBoard->saveScores();
            m_CurrentState = State::SCORE_BOARD;    
        }
        else{
            m_BGM.PlayStart(); 
            m_CurrentState = State::LEVEL_CHANGE;    
        }
        
        LOG_DEBUG("Win:)");
    }
    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    return MyElapsedTime();
}

