#include "App.hpp"

unsigned long App::Dead(unsigned long InitTime) { // NOLINT(this method will mutate members in the future)
//	m_BGM.PlayDeath();
    if (m_PacmanDead->IfAnimationEnds()) {
        m_PacmanDead->SetLooping(false);
    }
    
    if (m_Pacman->IsDead()) {
        m_GameOverText->SetVisible(true);
    }

    if (MyElapsedTime() - InitTime > 2500){
        // Exit Dead state
        if (m_Pacman->IsDead()) {
            m_GameOverText->SetVisible(false);
            m_CurrentState = State::START;
        }           
        else
            m_CurrentState = State::REVIVE;
    }
    
    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    return MyElapsedTime();
}
