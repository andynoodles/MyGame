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
        glm::vec2 OtherPosition = other->GetPosition();
        glm::vec2 ThisPosition = m_Pacman->GetPosition();
        if( ThisPosition.x > OtherPosition.x - size &&
            ThisPosition.x < OtherPosition.x + size &&
            ThisPosition.y > OtherPosition.y - size &&
            ThisPosition.y < OtherPosition.y + size){ return true;}
        return false;
}

bool App::IfCollides(const std::shared_ptr<Ghost>& other){
        (void) other;
        glm::vec2 OtherPosition = other->GetPosition();
        glm::vec2 ThisPosition = m_Pacman->GetPosition();
		int pacmanTileX = ThisPosition.x/PIXELPERTILE ,pacmanTileY = ThisPosition.y/PIXELPERTILE;
		int ghostTileX = OtherPosition.x/PIXELPERTILE ,ghostTileY = OtherPosition.y/PIXELPERTILE;
		if(pacmanTileX == ghostTileX && pacmanTileY == ghostTileY)
			return true;
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
	if(IfPacmanCollidesWall()){
		Stop();
	}
	else 
	m_Pacman->Move(m_Pacman->GetDirection() ,1);
}

void App::ChangeDirectionIfPossible(){
	std::string oldDirection = m_Pacman->GetDirection() ,newDirection  = InputManager();
	
	glm::vec2 currentPosition = m_Pacman->GetPosition();
	std::pair<int ,int> currentTile = m_BackgroundImage->GetTileOfPosition(currentPosition);
	std::pair<int ,int> upTile = {currentTile.first ,currentTile.second-1} ,downTile = {currentTile.first ,currentTile.second+1} ,leftTile = {currentTile.first-1 ,currentTile.second} ,rightTile = {currentTile.first+1 ,currentTile.second};
	LOG_DEBUG("CURRENT_TILES:{} ,{}" ,currentTile.first ,currentTile.second);
	LOG_DEBUG("U:{}" ,m_BackgroundImage->GetLayout(upTile.second ,upTile.first));
	LOG_DEBUG("D:{}" ,m_BackgroundImage->GetLayout(downTile.second ,downTile.first));
	LOG_DEBUG("L:{}" ,m_BackgroundImage->GetLayout(leftTile.second ,leftTile.first));
	LOG_DEBUG("R:{}" ,m_BackgroundImage->GetLayout(rightTile.second ,rightTile.first));

	std::pair<int ,int> tileintented;
	if(newDirection == oldDirection) return;
	else{
		if(newDirection =="North") tileintented = upTile;
		else if(newDirection =="South") tileintented = downTile;
		else if(newDirection =="West") tileintented = leftTile;
		else if(newDirection =="East") tileintented = rightTile;
	}
	if(m_BackgroundImage->GetLayout(tileintented.second ,tileintented.first) == 1){
		return;
	}
	else{
		m_Pacman->SetDirection(newDirection);
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
	glm::vec2 currentPosition = m_Pacman->GetPosition();
	std::pair<int ,int> currentTile = m_BackgroundImage->GetTileOfPosition(currentPosition);
	std::pair<int ,int> upTile = {currentTile.first ,currentTile.second-1} ,downTile = {currentTile.first ,currentTile.second+1} ,leftTile = {currentTile.first-1 ,currentTile.second} ,rightTile = {currentTile.first+1 ,currentTile.second};
	std::pair<int ,int> tileintented;
	std::string dirIntented = m_Pacman->GetDirection();	
	if(dirIntented =="North") tileintented = upTile;
	else if(dirIntented =="South") tileintented = downTile;
	else if(dirIntented =="West") tileintented = leftTile;
	else if(dirIntented =="East") tileintented = rightTile;

	if(m_BackgroundImage->GetLayout(tileintented.second,tileintented.first) ==1) return true;
	return false;
}

void App::Stop(){
	glm::vec2 currentPosition = m_Pacman->GetPosition();
	std::pair<int ,int> currentTile = m_BackgroundImage->GetTileOfPosition(currentPosition);
	glm::vec2 currentTileCenter = m_BackgroundImage->GetCenterPositionOfTile(currentTile.first ,currentTile.second);	
	
	m_Pacman->SetPosition(currentTileCenter);
}
