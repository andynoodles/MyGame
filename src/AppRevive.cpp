#include "App.hpp"

unsigned long App::Revive(unsigned long ReviveTime) { 
	m_BGM.PlayStart();
	m_ReadyText->SetVisible(true);
	if(m_Time.GetElapsedTimeMs() - ReviveTime > 3000){
        // Set Display state on some obj
        m_ReadyText->SetVisible(false);
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
		
        m_CurrentState = State::UPDATE;
	}

    m_Root.Update();
    return m_Time.GetElapsedTimeMs();
}
