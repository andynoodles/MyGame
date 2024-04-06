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
        if(IfCollides(m_SmallFood[i]) && m_SmallFood[i]->GetVisibility()){ 
            m_SmallFood[i]->SetVisible(false); 
            m_Score->AddVisibleScore(SCORE_FOOD);
        }
    }
    for (int i = 0; i < LARGE_FOOD_NUM; i++) {
        if(IfCollides(m_LargeFood[i]) && m_LargeFood[i]->GetVisibility()){
            m_LargeFood[i]->SetVisible(false); 
			FoodEffectMarker = m_Time.GetElapsedTimeMs();
            onPill = true;
            m_Score->AddVisibleScore(SCORE_FOOD);
        }
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
	else 
        s = m_Pacman->GetDirection();
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

void App::ScoreUpdate(){
    m_Score->ScoreUpdate();
}

void App::GhostStateProcess() {
	std::vector<std::shared_ptr<Ghost>> Ghost;
	Ghost.push_back(m_Cyan);
	Ghost.push_back(m_Red);
	Ghost.push_back(m_Pink);
	Ghost.push_back(m_Orange);
	//Set State
	for (int i = 0; i < 4; i++) {
		if (GetElapsedTime() - FoodEffectMarker < PILL_DURATION &&
			onPill &&
			(Ghost[i]->GetState() != Ghost::GhostState::DEAD)) {
			if (!(GetElapsedTime() - FoodEffectMarker < DONT_FLASH_DURATION))
				Ghost[i]->SetState(Ghost::GhostState::FLASHING);
			else
				Ghost[i]->SetState(Ghost::GhostState::SCARED);
			if (IfCollides(Ghost[i])) {
				Ghost[i]->SetDeadMarker(GetElapsedTime());
				Ghost[i]->SetState(Ghost::GhostState::DEAD);
			}
		}
		else if(Ghost[i]->GetState() != Ghost::GhostState::DEAD ||
				GetElapsedTime() - Ghost[i]->GetDeadMarker() > GHOST_DEAD_DURATION) {
				Ghost[i]->SetState(Ghost::GhostState::NORMAL);
		}
			
	}
}

void App::GhostMoveProcess() {
	GhostStateProcess();

	m_Cyan->GhostMove();
	m_Red->GhostMove();
	m_Pink->GhostMove();
	m_Orange->GhostMove();
}
