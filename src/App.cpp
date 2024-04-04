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
        glm::vec2 OtherPosition = other->GetPosition();
        glm::vec2 ThisPosition = m_Pacman->GetPosition();
		if(m_BackgroundImage->GetTileOfPosition(ThisPosition) == m_BackgroundImage->GetTileOfPosition(OtherPosition))
			return true;
        return false;
}

bool App::IfCollides(const std::shared_ptr<Ghost>& other){
        glm::vec2 OtherPosition = other->GetPosition();
        glm::vec2 ThisPosition = m_Pacman->GetPosition();
		if(m_BackgroundImage->GetTileOfPosition(ThisPosition) == m_BackgroundImage->GetTileOfPosition(OtherPosition))
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
            SetTimeMarker();
            onPill = true;
            m_Score->AddVisibleScore(SCORE_FOOD);
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
	else{
		m_Pacman->Move(m_Pacman->GetDirection() ,1);
	}
}

std::pair<int ,int> App::GetTileIntented(std::string newDirection){
	std::pair<int ,int> tileintented;
	std::pair<int ,int> currentTile = m_BackgroundImage->GetTileOfPosition(m_Pacman->GetPosition());

	if(newDirection =="North") tileintented = {currentTile.first ,currentTile.second-1};
	else if(newDirection =="South") tileintented = {currentTile.first ,currentTile.second+1};
	else if(newDirection =="West") tileintented = {currentTile.first-1 ,currentTile.second};
	else if(newDirection =="East") tileintented = {currentTile.first+1 ,currentTile.second};
	
	return tileintented;
}

void App::ChangeDirectionIfPossible(){
	std::string oldDirection = m_Pacman->GetDirection() ,newDirection  = InputManager();
	if(newDirection == oldDirection) return;

	std::pair<int ,int> tileintented = GetTileIntented(newDirection);
	if(m_BackgroundImage->GetLayout(tileintented.second ,tileintented.first) == 1){
		return;
	}
	else{
		glm::vec2 centerOfTileIntented = m_BackgroundImage->GetCenterPositionOfTile(tileintented.first ,tileintented.second);
		glm::vec2 currentPosition = m_Pacman->GetPosition();
		float disToMidX = currentPosition.x - centerOfTileIntented.x ,disToMidY = currentPosition.y - centerOfTileIntented.y;

		if(newDirection == "North"){
			m_Pacman->SetPosition({currentPosition.x - disToMidX ,currentPosition.y + std::fabs(disToMidX)});
		}
		else if(newDirection == "South"){
			m_Pacman->SetPosition({currentPosition.x - disToMidX ,currentPosition.y - std::fabs(disToMidX)});
		}
		else if(newDirection == "West"){
			m_Pacman->SetPosition({currentPosition.x - std::fabs(disToMidY) ,currentPosition.y - disToMidY});
		}
		else if(newDirection == "East"){
			m_Pacman->SetPosition({currentPosition.x + std::fabs(disToMidY) ,currentPosition.y - disToMidY});
		}

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
	std::pair<int ,int> tileintented = GetTileIntented(m_Pacman->GetDirection());

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
