#include "App.hpp"

unsigned long App::Dead() { // NOLINT(this method will mutate members in the future)
    // Full Dead
    if(m_Pacman->IsDead()){
        // Play end animation

        // Reset life, level, score
        
        // Restart Game
        m_CurrentState = State::UPDATE;
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


        // Go back AppUpdate
        m_CurrentState = State::REVIVE;    
    }
    return m_Time.GetElapsedTimeMs();
}
