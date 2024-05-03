#include "App.hpp"

unsigned long App::Start(unsigned long InitTime) {
    // init setting
    m_BGM.PlayStart(); 
    m_ReadyText->SetVisible(true);

    // Stop animation for dead pacman
    m_PacmanDead->SetLooping(false);
    m_PacmanDead->SetVisible(false);
    m_PacmanDead->SetPlaying(false);

    m_Red->SetLooping(false);
    m_Red->SetFrame(1);

    m_Pink->SetLooping(false);
    m_Pink->SetFrame(1);

    m_Orange->SetLooping(false);
    m_Orange->SetFrame(1);

    m_Cyan->SetLooping(false);
    m_Cyan->SetFrame(1);

    m_Pacman->SetLooping(false);


	if(m_Time.GetElapsedTimeMs() - InitTime > GAME_OPENING_TIME_DURATION/2.5){
        m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, 1));
		m_Red->SetVisible(true);

        m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, 1));
        m_Pink->SetVisible(true);
		
        m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, NUMBEROFTILESY - 2));
        m_Orange->SetVisible(true);
        
        m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, NUMBEROFTILESY - 2));
        m_Cyan->SetVisible(true);
		
        m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X, PACMAN_STARTTILE_Y));
        m_Pacman->SetVisible(true);
	}
	if(m_Time.GetElapsedTimeMs() - InitTime > GAME_OPENING_TIME_DURATION){
        m_ReadyText->SetVisible(false);
        
        m_Red->SetPlaying(true);        
        m_Pink->SetPlaying(true);	   
        m_Orange->SetPlaying(true);    
		m_Cyan->SetPlaying(true);

        m_Red->SetLooping(true);        
        m_Pink->SetLooping(true);	   
        m_Orange->SetLooping(true);    
		m_Cyan->SetLooping(true);

        m_Pacman->SetPlaying(true);
        m_Pacman->SetLooping(true);
        for (auto& Food : m_SmallFood) {
            Food->SetVisible(true);
        }
        for (auto& Food : m_LargeFood) {
            Food->SetVisible(true);
        }

        // Reset scores
        m_Score->SetFoodScore(0);
        m_Score->SetVisibleScore(0);
        
		m_CurrentState = State::UPDATE;
	}

	m_Renderer.Update();
	
	return m_Time.GetElapsedTimeMs();
}

