#include "App.hpp"

void App::Start() {
	static unsigned long m = m_Time.GetElapsedTimeMs();
	m_BGM.PlayStart();
	m_BackgroundImage->Draw();
	m_ReadyText->Draw();
	if(m_Time.GetElapsedTimeMs()- m > GAME_OPENING_TIME_DURATION/2.5){
		m_Red->Draw();
		m_Pink->Draw();
		m_Orange->Draw();
		m_Cyan->Draw();
		m_Pacman->Draw();
	}
	if(m_Time.GetElapsedTimeMs()-m > GAME_OPENING_TIME_DURATION + 10){
		m_ReadyText->SetVisible(false);
		m_ReadyText->Draw();

		m_CurrentState = State::UPDATE;
	}
}

