#include "App.hpp"

unsigned long App::Start(unsigned long InitTime) {
	m_BGM.PlayStart();
	m_BackgroundImage->Draw();
	m_ReadyText->Draw();
	if(m_Time.GetElapsedTimeMs()- InitTime > GAME_OPENING_TIME_DURATION/2.5){
		m_Red->SetVisible(true);
		m_Pink->SetVisible(true);
		m_Orange->SetVisible(true);
		m_Cyan->SetVisible(true);
		m_Pacman->SetVisible(true);

		
	}
	if(m_Time.GetElapsedTimeMs()- InitTime > GAME_OPENING_TIME_DURATION){
		m_ReadyText->SetVisible(false);
		m_Red->SetPlaying(true);
		m_Pink->SetPlaying(true);
		m_Orange->SetPlaying(true);
		m_Cyan->SetPlaying(true);
		m_Pacman->SetPlaying(true);
		
		m_CurrentState = State::UPDATE;
	}

	return m_Time.GetElapsedTimeMs();
}

