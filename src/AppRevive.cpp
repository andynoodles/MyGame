#include "App.hpp"

unsigned long App::Revive(unsigned long ReviveTime) { 
	m_BGM.PlayStart();
	m_ReadyText->SetVisible(true);
    m_PacmanDead->SetVisible(false);

    // Ready Time + Dead animation time
	if(m_Time.GetElapsedTimeMs() - ReviveTime > 3000 + 2500){
        // Stop Display state on some obj
        m_ReadyText->SetVisible(false);

        // Start Display state on some obj
        m_Cyan->SetVisible(true);
        m_Red->SetVisible(true);
        m_Orange->SetVisible(true);
        m_Pink->SetVisible(true);
        for (auto& Food : m_SmallFood) {
            Food->SetVisible(true); 
        }
        for (auto& Food : m_LargeFood) {
            Food->SetVisible(true); 
        }

        // Reset FoodScore to 0
        m_Score->SetFoodScore(0);
        // Reset Pacman Postion
        m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X,PACMAN_STARTTILE_Y));
        m_Pacman->SetVisible(true);

        // Stop animation for dead pacman
        m_PacmanDead->SetLooping(false);
        m_PacmanDead->SetVisible(false);

        // Reset Ghosts Position
        m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, NUMBEROFTILESY - 2));
        m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, NUMBEROFTILESY - 2));
        m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, 1));
        m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, 1));

        m_CurrentState = State::UPDATE;
	}

    m_Root.Update();
    return m_Time.GetElapsedTimeMs();
}
