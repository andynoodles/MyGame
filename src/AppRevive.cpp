#include "App.hpp"

unsigned long App::Revive(unsigned long ReviveTime) { 
	m_ReadyText->SetVisible(true);
    m_PacmanDead->SetVisible(false);

    // Ready Time + Dead animation time
	if(MyElapsedTime() - ReviveTime > 3000 + 2500){
        // Stop Display state on some obj
        m_ReadyText->SetVisible(false);

        // Start Playing on Ghosts
        m_Cyan->SetLooping(true);
        m_Red->SetLooping(true);
        m_Orange->SetLooping(true);
        m_Pink->SetLooping(true);

        for (auto& Food : m_SmallFood) {
            Food->SetZIndex(10);
        }
        for (auto& Food : m_LargeFood) {
            Food->SetZIndex(10);
        }

        // Reset FoodScore to 0
        m_Score->SetFoodScore(0);

        // Stop animation for dead pacman
        m_PacmanDead->SetLooping(false);
        m_PacmanDead->SetVisible(false);

        m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, 1));
        m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, 1));
        m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, NUMBEROFTILESY - 2));
		m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, NUMBEROFTILESY - 2));
        
        m_Red->SetVisible(true);
        m_Pink->SetVisible(true);
        m_Orange->SetVisible(true);        
        m_Cyan->SetVisible(true);
		
        m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X, PACMAN_STARTTILE_Y));
        m_Pacman->SetVisible(true);

        m_Red->SetMarker(MyElapsedTime());
        m_Pink->SetMarker(MyElapsedTime());
        m_Cyan->SetMarker(MyElapsedTime());
        m_Orange->SetMarker(MyElapsedTime());

        m_Red->SetState(Ghost::GhostState::SCATTER);
        m_Pink->SetState(Ghost::GhostState::SCATTER);
        m_Cyan->SetState(Ghost::GhostState::SCATTER);
        m_Orange->SetState(Ghost::GhostState::SCATTER);
        
        m_CurrentState = State::UPDATE;
		m_BGM.Resume();
	}
	
    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    
    return MyElapsedTime();
}
