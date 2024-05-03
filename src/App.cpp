#include "App.hpp"

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
			m_Score->AddVisibleScore(FOOD_SCORE);
			m_Score->AddFoodScore(FOOD_SCORE);
			m_SFX.PlayMunch();
		}
	}
	for (int i = 0; i < LARGE_FOOD_NUM; i++) {
		if(IfCollides(m_LargeFood[i]) && m_LargeFood[i]->GetVisibility()){
			m_LargeFood[i]->SetVisible(false); 
			FoodEffectMarker = m_Time.GetElapsedTimeMs();
			m_Score->AddVisibleScore(FOOD_SCORE);
			m_Score->AddFoodScore(FOOD_SCORE);
			m_SFX.PlayMunch();
			m_FlashText->ResetScoreMultiplier();
		}
	}
}

void App::GhostCollision(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Pink ,m_Cyan ,m_Orange};
	for(auto g : vec){
		bool collided = IfCollides(g);
		if( collided && (g->GetState() == Ghost::GhostState::SCATTER || 
						g->GetState() == Ghost::GhostState::CHASE)){
			PacmanDead();
			break;
		}
		else if (collided && (g->GetState() == Ghost::GhostState::FLASHING ||
								g->GetState() == Ghost::GhostState::SCARED)){
			//show socre on screen
			LOG_DEBUG("GHOST EATEN");
			m_Score->AddVisibleScore(400 * m_FlashText->GetScoreMultiplier());
			m_FlashText->SetText(std::to_string(400 * m_FlashText->GetScoreMultiplier()));
			m_FlashText->SetPosition(m_Pacman->GetPosition());
			m_FlashText->SetVisible(true);
			m_FlashText->SetMarker(m_Time.GetElapsedTimeMs());
			m_FlashText->IncreaseScoreMultiplier(1);
			m_SFX.PlayEatGhost();
		}
	}

	if(m_Time.GetElapsedTimeMs() - m_FlashText->GetMarker() > 2000){
		m_FlashText->SetVisible(false);
	}
}

void App::PacmanMoveProcess(){
	ChangeDirectionIfPossible();
	if(IfPacmanCollidesWall()){
		Stop();
	}
	else{
		SetPacmanSpeedMul();
		m_Pacman->Move(m_Pacman->GetDirection());
	}
}

void App::SetPacmanSpeedMul(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Pink ,m_Cyan ,m_Orange};
	for(int i=0 ; i < vec.size() ;i++){
		if(vec[i]->IsBeenChasing()){
			m_Pacman->SetSpeedMul(currentLevel.GetPacmanFrightSpeedMul());
			break;
		}
		else if(i == vec.size()-1){
			m_Pacman->SetSpeedMul(currentLevel.GetPacmanSpeedMul());
		}
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
	if((tileintented.first >=0 && tileintented.first <= NUMBEROFTILESX -1) && m_BackgroundImage->GetLayout(tileintented.second,tileintented.first) ==1) return true;
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
	std::vector<std::shared_ptr<Ghost>> Ghosts;
	Ghosts.push_back(m_Cyan);
	Ghosts.push_back(m_Red);
	Ghosts.push_back(m_Pink);
	Ghosts.push_back(m_Orange);\
	//Time 
	unsigned long scatter = 5000, chase = 20000;
	//Set State
	for (auto Ghost : Ghosts) {
		if(Ghost->GetState() == Ghost::GhostState::SCATTER && 
		   m_Time.GetElapsedTimeMs() - Ghost->GetMarker() > scatter){
			Ghost->SetState(Ghost::GhostState::CHASE);
			Ghost->SetMarker(m_Time.GetElapsedTimeMs());
		}
		if(Ghost->GetState() == Ghost::GhostState::CHASE && 
		   m_Time.GetElapsedTimeMs() - Ghost->GetMarker() > chase){
			Ghost->SetState(Ghost::GhostState::SCATTER);
			Ghost->SetMarker(m_Time.GetElapsedTimeMs());
		}
		// onPill and flashing
		if(Ghost->GetState() == Ghost::GhostState::SCARED &&
		   m_Time.GetElapsedTimeMs() - FoodEffectMarker < PILL_DURATION &&
		   m_Time.GetElapsedTimeMs() - FoodEffectMarker > DONT_FLASH_DURATION){
			Ghost->SetState(Ghost::GhostState::FLASHING);
		}
		// onPill and not flashing
		if((Ghost->GetState() == Ghost::GhostState::SCATTER ||
		    Ghost->GetState() == Ghost::GhostState::CHASE) &&
		   m_Time.GetElapsedTimeMs() - FoodEffectMarker < PILL_DURATION &&
		   m_Time.GetElapsedTimeMs() - FoodEffectMarker < DONT_FLASH_DURATION){
			Ghost->SetState(Ghost::GhostState::SCARED);
		}
		// after pill
		if(Ghost->GetState() == Ghost::GhostState::FLASHING &&
		   m_Time.GetElapsedTimeMs() - FoodEffectMarker > PILL_DURATION){
			Ghost->SetState(Ghost::GhostState::SCATTER);
			Ghost->SetMarker(m_Time.GetElapsedTimeMs());
		}
		if( (Ghost->GetState() == Ghost::GhostState::SCARED || 
			Ghost->GetState() == Ghost::GhostState::FLASHING) &&
			IfCollides(Ghost)) {
			Ghost->SetState(Ghost::GhostState::DEAD);
		}	
		//if DEAD and back home
		if( Ghost->GetState() == Ghost::GhostState::DEAD &&
			m_BackgroundImage->GetTileOfPosition(Ghost->GetPosition()) == std::pair{14, 11}){
			Ghost->SetState(Ghost::GhostState::SCATTER);
			Ghost->SetMarker(m_Time.GetElapsedTimeMs());
		}
		
	}
	
}

void App::GhostMoveProcess() {
	m_Red->MoveToTile(GetGhostTargetTile(m_Red));
	m_Orange->MoveToTile(GetGhostTargetTile(m_Orange));
	m_Cyan->MoveToTile(GetGhostTargetTile(m_Cyan));
	m_Pink->MoveToTile(GetGhostTargetTile(m_Pink));
}

std::pair<int, int> App::GetGhostTargetTile(std::shared_ptr<Ghost> ghost){
	Ghost::GhostState ghostState = ghost->GetState();
	std::pair<int ,int> ghostTargetTile;
	std::pair<int ,int> pacmanTile = m_BackgroundImage->GetTileOfPosition(m_Pacman->GetPosition());
	std::string pacmanDir = m_Pacman->GetDirection();

	if(ghostState == Ghost::GhostState::DEAD){
		return {14 ,11}; //Target is located directly above the left side of the “door” to the ghost house.
	}
	if(ghost == m_Red){
		if(ghostState == Ghost::GhostState::CHASE){	
			ghostTargetTile = pacmanTile;
		}
		else if(ghostState == Ghost::GhostState::SCARED || ghostState == Ghost::GhostState::FLASHING){	
			ghostTargetTile = {NUMBEROFTILESX-2 ,1}; //upper right at map
		}
	}
	else if(ghost == m_Pink){
		if(ghostState == Ghost::GhostState::CHASE){
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
		if(ghostState == Ghost::GhostState::CHASE){	
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
		if(ghostState == Ghost::GhostState::CHASE && distance >= 8){
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

void App::SetGhostSpeedMul(std::shared_ptr<Ghost> g){
	if(g->IsBeenChasing()){
		g->SetSpeedMul(currentLevel.GetGhostFrightSpeedMul());
	}
	else{
		g->SetSpeedMul(currentLevel.GetGhostSpeedMul());
	}
}

void App::BGMCtrl(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Cyan ,m_Pink ,m_Orange};
	for(auto g : vec){
		if(g->GetState() == Ghost::GhostState::DEAD){
			m_BGM.PlayRetreat(); //Ghost is going home.
			return;	
		}
	}
	for(auto g:vec){
		if(g->GetState() == Ghost::GhostState::SCARED || g->GetState() == Ghost::GhostState::FLASHING){
			m_BGM.PlayPower();	//Pacman chase ghost.
			return;
		}
	}
	m_BGM.PlayNormal();
}

void App::PacmanDead() {
	m_SFX.PlayPacmanDeath();
	LOG_DEBUG("PACMAN EATEN");
	m_Pacman->HpMinusOne();
	// Undisplay some objs
	m_Pacman->SetVisible(false);
	m_Cyan->SetVisible(false);
	m_Red->SetVisible(false);
	m_Orange->SetVisible(false);
	m_Pink->SetVisible(false);
	for (auto& Food : m_SmallFood) {
		Food->SetVisible(false);
	}
	for (auto& Food : m_LargeFood) {
		Food->SetVisible(false);
	}
	// Start dead animation
	m_PacmanDead->SetPosition(m_Pacman->GetPosition());
	m_PacmanDead->SetVisible(true);
	m_PacmanDead->SetLooping(true);
	m_PacmanDead->SetPlaying(true);
	m_PacmanDead->SetFrame(0);
	m_CurrentState = State::DEAD;
}
