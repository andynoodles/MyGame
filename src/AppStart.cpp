#include "App.hpp"
#include "Level.hpp"

unsigned long App::Start(unsigned long InitTime) {
    // init setting
    m_BGM.PlayStart(); 
    m_ReadyText->SetVisible(true);
	for(auto lifeIcon : m_LifeIcons){
		lifeIcon->SetVisible(true);
	}

    LevelInit(InitTime);
    // Reset Values
    m_Score->SetFoodScore(0);
    m_Score->SetVisibleScore(0);
    m_Pacman->SetHp(PACMAN_LIFE);

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
	
	return MyElapsedTime();
}

