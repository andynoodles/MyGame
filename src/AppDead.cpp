#include "App.hpp"
#include "Util/Logger.hpp"

unsigned long App::Dead(unsigned long InitTime) { // NOLINT(this method will mutate members in the future)
//	m_BGM.PlayDeath();
    if (m_PacmanDead->IfAnimationEnds()) {
        LOG_DEBUG("end time:{}", m_Time.GetElapsedTimeMs());
        m_PacmanDead->SetLooping(false);
    }
    
    if (m_Pacman->IsDead()) {
        m_GameOverText->SetVisible(true);
    }

    if (m_Time.GetElapsedTimeMs() - InitTime > 2500){
        // Exit Dead state
        if (m_Pacman->IsDead()) {
            m_GameOverText->SetVisible(false);
            m_CurrentState = State::START;
        }           
        else
            m_CurrentState = State::REVIVE;
    }
    
    m_Root.Update();

    return m_Time.GetElapsedTimeMs();
}
