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
	glm::vec2 OtherPosition = other->GetPosition();
	glm::vec2 ThisPosition = m_Pacman->GetPosition();
	if(m_BackgroundImage->GetTileOfPosition(ThisPosition) == m_BackgroundImage->GetTileOfPosition(OtherPosition)) //Pacman and Ghost is on same tile.
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
			FoodEffectMarker = m_Time.GetElapsedTimeMs();
			onPill = true;
			m_Score->AddVisibleScore(SCORE_FOOD);
		}
	}
}

void App::GhostCollision(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Pink ,m_Cyan ,m_Orange};
	for(auto g : vec){
		if(IfCollides(g) && g->GetState() != Ghost::GhostState::DEAD){
			m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X,PACMAN_STARTTILE_Y));
			m_Pacman->HpMinusOne();	
		}
	}
}

bool App::IsFoodAllEaten(){
	for(auto f : m_SmallFood)
		if(f->GetVisibility()) return false;
	for(auto f : m_LargeFood)
		if(f->GetVisibility()) return false;
	return true;
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
	//std::pair<int ,int> t = m_BackgroundImage->GetTileOfPosition(m_Pacman->GetPosition());
	m_Red->MoveToTile(GetGhostTargetTile(m_Red));
	m_Orange->MoveToTile(GetGhostTargetTile(m_Orange));
	m_Cyan->MoveToTile(GetGhostTargetTile(m_Cyan));
	m_Pink->MoveToTile(GetGhostTargetTile(m_Pink));
//	m_Red->MoveToTile({28 ,0});
//	m_Cyan->MoveToTile({0 ,0});
//	m_Pink->MoveToTile({28, 31});
//	m_Orange->MoveToTile({0 , 31});
}



std::pair<int, int> App::GetGhostTargetTile(std::shared_ptr<Ghost> ghost){
	Ghost::GhostState ghostState = ghost->GetState();
	if(ghostState == Ghost::GhostState::DEAD){
		return {14 ,11}; //Target is located directly above the left side of the “door” to the ghost house.
	}
	std::pair<int ,int> ghostTargetTile;
	std::pair<int ,int> pacmanTile = m_BackgroundImage->GetTileOfPosition(m_Pacman->GetPosition());
	std::string pacmanDir = m_Pacman->GetDirection();

	if(ghost == m_Red){
		if(ghostState == Ghost::GhostState::NORMAL){	
			ghostTargetTile = pacmanTile;
		}
		else if(ghostState == Ghost::GhostState::SCARED || ghostState == Ghost::GhostState::FLASHING){	
			ghostTargetTile = {NUMBEROFTILESX-2 ,1}; //upper right at map
		}
	}
	else if(ghost == m_Pink){
		if(ghostState == Ghost::GhostState::NORMAL){
			if(pacmanDir == "North"){
				ghostTargetTile = {pacmanTile.first-4 ,pacmanTile.second-4};//It's not bug,it's feature.
			}
			else if(pacmanDir == "West"){
				ghostTargetTile = {pacmanTile.first-4 ,pacmanTile.second};
			}
			else if(pacmanDir == "East"){
				ghostTargetTile = {pacmanTile.first+4 ,pacmanTile.second};
			}
			else if(pacmanDir == "South"){
				ghostTargetTile = {pacmanTile.first ,pacmanTile.second+4};
			}
		}
		else if(ghostState == Ghost::GhostState::SCARED || ghostState == Ghost::GhostState::FLASHING){	
			ghostTargetTile = {1 ,1}; //upper left at map
		}

	}
	else if(ghost == m_Cyan){
		if(ghostState == Ghost::GhostState::NORMAL){	
			std::pair<int ,int> offsetTile;
			if(pacmanDir == "North"){
				offsetTile = {pacmanTile.first-2 ,pacmanTile.second-2};//It's not bug,it's feature.
			}
			else if(pacmanDir == "West"){
				offsetTile = {pacmanTile.first-2 ,pacmanTile.second};
			}
			else if(pacmanDir == "East"){
				offsetTile = {pacmanTile.first+2 ,pacmanTile.second};
			}
			else if(pacmanDir == "South"){
				offsetTile = {pacmanTile.first ,pacmanTile.second+2};
			}

			std::pair<int ,int> redGhostTile = m_BackgroundImage->GetTileOfPosition(m_Red->GetPosition());
			glm::vec2 redGhostTileCenter = m_BackgroundImage->GetCenterPositionOfTile(redGhostTile.first ,redGhostTile.second);
			glm::vec2 offsetTileCenter = m_BackgroundImage->GetCenterPositionOfTile(offsetTile.first ,offsetTile.second);

			ghostTargetTile = m_BackgroundImage->GetTileOfPosition({offsetTileCenter.x+(offsetTileCenter.x-redGhostTileCenter.x) ,offsetTileCenter.y+(offsetTileCenter.y-redGhostTileCenter.y)});
		}
		else if(ghostState == Ghost::GhostState::SCARED || ghostState == Ghost::GhostState::FLASHING){
			ghostTargetTile = {NUMBEROFTILESX-2 ,NUMBEROFTILESY-2}; //lower right at map
		}
	}
	else if(ghost == m_Orange){
		std::pair<int ,int> orangeGhostTile = m_BackgroundImage->GetTileOfPosition(m_Orange->GetPosition());
		//Get Euclidean distance between orange's tile and Pacman's tile.
		float distance = std::sqrt(std::pow(orangeGhostTile.first-pacmanTile.first ,2) + std::pow(orangeGhostTile.second-pacmanTile.second ,2));					
		if(ghostState == Ghost::GhostState::NORMAL && distance >= 8){
			ghostTargetTile = pacmanTile;
		}
		else if(ghostState == Ghost::GhostState::SCARED || distance < 8 ||ghostState == Ghost::GhostState::FLASHING){
			ghostTargetTile = {1,NUMBEROFTILESY-2}; //lower left at map
		}
	}

	if(ghostTargetTile.first < 1) ghostTargetTile.first = 1;
	else if(ghostTargetTile.first > NUMBEROFTILESX-2) ghostTargetTile.first = NUMBEROFTILESX-2;
	if(ghostTargetTile.second < 1) ghostTargetTile.second = 1;
	else if(ghostTargetTile.second > NUMBEROFTILESY-2) ghostTargetTile.second = NUMBEROFTILESY-2;
	return ghostTargetTile;
}
