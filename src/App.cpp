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
        int size = PIXELPERTILE/2;
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
        int size = PIXELPERTILE/2;
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

void App::FoodCollision(){
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
}

void App::FoodEffect(){
    if(GetElapsedTime() - GetMarker() < PILL_DURATION && onPill){
        if(!(GetElapsedTime() - GetMarker() < FLASH_DURATION))
            m_Cyan->GhostMoveScaredFlash("East", 0);
        else
            m_Cyan->GhostMoveScared("East", 0);

        m_Text->SetText("I'm high");
    }
    else{
        onPill = false;
        m_Cyan->GhostMove("East", 0);
        m_Text->SetText("I'm trash");
    }
}
