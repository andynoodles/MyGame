#include "App.hpp"

void App::Update() {
    TimeUpdate();
    InputManager();

    for (int i = 0; i < SMALL_FOOD_NUM; i++) {
        if(IfCollides(m_SmallFood[i])){ 
            m_SmallFood[i]->SetVisible(false); 
        }
    }

    for (int i = 0; i < LARGE_FOOD_NUM; i++) {
        if(IfCollides(m_LargeFood[i])){
            m_LargeFood[i]->SetVisible(false); 
            SetTimeMarker();
            onPill = true;
        }
    }
    
    if(GetElapsedTime() - GetMarker() < PILL_DURATION && onPill){
    	glm::vec2 S;
		std::string Direction = m_Pacman->GetDirection();
	if(Direction == "East") {
		
        S = {PACMAN_SPEED, 0};
    }
    else if(Direction == "West") {
        S = {-PACMAN_SPEED, 0};
    }
    else if(Direction == "North") {
        S = {0, PACMAN_SPEED};
    }
    else if(Direction == "South") {
        S = {0, -PACMAN_SPEED};
    }
	if(Collides(m_Pacman->GetPosition()+S) == false)
        	m_Pacman->Move(m_Pacman->GetDirection(), 1);
        m_Cyan->GhostMoveScared({0, 0}, 1);
        m_Text->SetText("I'm high");
    }
    else{
	glm::vec2 S;
		std::string Direction = m_Pacman->GetDirection();
	if(Direction == "East") {
        S = {PACMAN_SPEED, 0};
    }
    else if(Direction == "West") {
        S = {-PACMAN_SPEED, 0};
    }
    else if(Direction == "North") {
        S = {0, PACMAN_SPEED};
    }
    else if(Direction == "South") {
        S = {0, -PACMAN_SPEED};
    }
	if(Collides(m_Pacman->GetPosition()+S) == false)

        m_Pacman->Move(m_Pacman->GetDirection(), 1);
        onPill = false;
        m_Cyan->GhostMove({0,0}, 1);
        m_Text->SetText("I'm trash");
    }



    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
