#include "App.hpp"

unsigned long App::Dead(unsigned long InitTime) { // NOLINT(this method will mutate members in the future)
    if (m_PacmanDead->IfAnimationEnds()) {
        m_PacmanDead->SetLooping(false);
    }
    
    if (m_Time.GetElapsedTimeMs() - InitTime > 2500){
        // Exit Dead state
        if(m_Pacman->IsDead())
            m_CurrentState = State::START;
        else
            m_CurrentState = State::REVIVE;
    }
    
    m_Root.Update();

    return m_Time.GetElapsedTimeMs();
}
