#include "App.hpp"

void App::Start() {
	m_BGM.PlayStart();
	m_BackgroundImage->Draw();
	m_ReadyText->Draw();
	if(m_Time.GetElapsedTimeMs() > GAME_OPENING_TIME_Ms/2.5){
		m_Red->Draw();
		m_Pink->Draw();
		m_Orange->Draw();
		m_Cyan->Draw();
		m_Pacman->Draw();
	}
	if(m_Time.GetElapsedTimeMs() > GAME_OPENING_TIME_Ms){
		m_ReadyText->SetVisible(false);
		m_ReadyText->Draw();

		m_CurrentState = State::UPDATE;
	}
}

