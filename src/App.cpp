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

void App::PacmanMoveProcess(){
	ChangeDirectionIfPossible();
	m_Pacman->Move(m_Pacman->GetDirection() ,1);
	if(IfPacmanCollidesWall()){
		m_Pacman->MoveBack(m_Pacman->GetDirection() ,1);
	}
}

void App::ChangeDirectionIfPossible(){
		std::string oldDirection = m_Pacman->GetDirection() ,newDirection  = InputManager();

	if(newDirection == oldDirection) return;
	m_Pacman->SetDirection(newDirection);
    m_Pacman->Move(m_Pacman->GetDirection(), 1);
	if(IfPacmanCollidesWall()){
		m_Pacman->MoveBack(m_Pacman->GetDirection() ,1);
		m_Pacman->SetDirection(oldDirection);
	}
	else{
		m_Pacman->MoveBack(m_Pacman->GetDirection(),1);
	}

}

std::string App::InputManager(){
	std::string s;
    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        s =  "North";
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
       s =  "West";
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        s =  "South";
    } 
    else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        s =  "East";
    }
	else s = m_Pacman->GetDirection();
	return s;
}

bool App::IfPacmanCollidesWall(){
	int size = PIXELPERTILE/2 - 2.5; //need fine-tune
	glm::vec2 currentPosition = m_Pacman->GetPosition();
	int upperLeft =  m_BackgroundImage->typeOfPixel(currentPosition.x - size ,currentPosition.y + size);
	int upperRight =  m_BackgroundImage->typeOfPixel(currentPosition.x + size ,currentPosition.y + size);
	int lowerLeft =  m_BackgroundImage->typeOfPixel(currentPosition.x - size ,currentPosition.y - size);
	int lowerRight =  m_BackgroundImage->typeOfPixel(currentPosition.x + size ,currentPosition.y - size);
	if(upperLeft == 1 || upperRight == 1 || lowerLeft == 1 || lowerRight ==1)
		return true;
	return false;
}


