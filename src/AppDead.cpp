#include "App.hpp"

void App::Dead() { // NOLINT(this method will mutate members in the future)
    
        

    // Full Dead
    if(m_Pacman->IsDead()){
        // Play end animation
        // Restart Game
        m_CurrentState = State::INIT;
    }
    // Half Dead
    else{
        // Set Display false on some obj
        m_Cyan->SetVisible(false);
        m_Red->SetVisible(false);
        m_Orange->SetVisible(false);
        m_Pink->SetVisible(false);
        for (auto& Food : m_SmallFood) {
			Food->SetVisible(false); 
		}
        for (auto& Food : m_LargeFood) {
            Food->SetVisible(false); 
        }
        // Play Pacman dead animation

        // Reset Pacman Postion
        m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X,PACMAN_STARTTILE_Y));
        // Go back AppUpdate
        m_CurrentState = State::UPDATE;    
    }
}
