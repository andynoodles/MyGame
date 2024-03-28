#include "App.hpp"

void App::TimeUpdate(){
    m_Time.Update();
}

unsigned long App::GetElapsedTime(){
    return m_Time.GetElapsedTimeMs();
}

unsigned long App::GetDeltaTime(){
    return m_Time.GetDeltaTime();
}

void App::SetTimeMarker(){
    Marker = m_Time.GetElapsedTimeMs();
}

unsigned long App::GetMarker(){
    return Marker;
}

bool App::IfCollides(const std::shared_ptr<Food>& other){
        (void) other;
        int size = 8;
        glm::vec2 OtherPostion = other->GetPosition();
        glm::vec2 ThisPostiom = m_Pacman->GetPosition();
        if( ThisPostiom.x > OtherPostion.x - size &&
            ThisPostiom.x < OtherPostion.x + size &&
            ThisPostiom.y > OtherPostion.y - size &&
            ThisPostiom.y < OtherPostion.y + size){ return true;}
        return false;
}

bool App::IfCollides(const std::shared_ptr<Ghost>& other){
        (void) other;
        int size = 8;
        glm::vec2 OtherPostion = other->GetPosition();
        glm::vec2 ThisPostiom = m_Pacman->GetPosition();
        if( ThisPostiom.x > OtherPostion.x - size &&
            ThisPostiom.x < OtherPostion.x + size &&
            ThisPostiom.y > OtherPostion.y - size &&
            ThisPostiom.y < OtherPostion.y + size){ return true;}
        return false;
}

void App::InputManager(){
    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        m_Pacman->SetDirection("North");
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        m_Pacman->SetDirection("West");
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        m_Pacman->SetDirection("South");
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        m_Pacman->SetDirection("East");
    }
}