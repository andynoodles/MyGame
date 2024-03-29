#include "App.hpp"

void App::Update() {
    TimeUpdate();
    InputManager();

    for (int i = 0; i < 240; i++) {
        if(IfCollides(m_SmallFood[i])){ 
            m_SmallFood[i]->SetVisible(false); 
        }
    }

    for (int i = 0; i < 4; i++) {
        if(IfCollides(m_LargeFood[i])){
            m_LargeFood[i]->SetVisible(false); 
            SetTimeMarker();
            onPill = true;
        }
    }
    
    if(GetElapsedTime() - GetMarker() < PILL_DURATION && onPill){
        m_Pacman->Move(m_Pacman->GetDirection(), 1);
        m_Cyan->GhostMoveScared({0, 0}, 1);
        m_Text->SetText("I'm high");
    }
    else{
        onPill = false;
        m_Cyan->GhostMove({0,0}, 1);
        m_Pacman->Move(m_Pacman->GetDirection(), 1);
        m_Text->SetText("I'm trash");
    }



    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
