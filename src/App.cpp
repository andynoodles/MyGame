#include "App.hpp"

//conflict
unsigned long App::MyElapsedTime(){
	return m_Time.GetElapsedTimeMs() + 100000;
}

template<class T>
bool App::IfCollides(const std::shared_ptr<T> other){
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
			FoodEffectMarker = MyElapsedTime();
			m_Score->AddVisibleScore(FOOD_SCORE);
			m_Score->AddFoodScore(FOOD_SCORE);
			m_SFX.PlayMunch();
			m_FlashText->ResetScoreMultiplier();
			m_Red->SetState(Ghost::GhostState::SCARED);
			m_Orange->SetState(Ghost::GhostState::SCARED);
			m_Cyan->SetState(Ghost::GhostState::SCARED);
			m_Pink->SetState(Ghost::GhostState::SCARED);
		}
	}
}

int App::FoodEatenNum(){
	return m_Score->GetFoodScore()/FOOD_SCORE;
}

void App::GhostCollision(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Pink ,m_Cyan ,m_Orange};
	for(auto g : vec){
		bool collided = IfCollides(g);
		if( collided && (g->GetState() == Ghost::GhostState::SCATTER || 
						g->GetState() == Ghost::GhostState::CHASE ||
						g->GetState() == Ghost::GhostState::REVIVE)){
			if(!cheatMode){
				PacmanDead();
			}
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
			m_FlashText->SetMarker(MyElapsedTime());
			m_FlashText->IncreaseScoreMultiplier(1);
			m_SFX.PlayEatGhost();
		}
	}
}

void App::PacmanMoveProcess(){
	ChangeDirectionIfPossible();
	if(IfPacmanCollidesWall()){
		Stop();
	}
	else{
		SetPacmanSpeedMul();
		if(cheatMode){
			m_Pacman->CheatMove(m_Pacman->GetDirection(), m_Pacman->GetAngle());
			m_Pacman->SetAngle( m_Pacman->GetAngle() + 0.3);
			if (m_Pacman->GetAngle() > 2 * PI) {
				m_Pacman->SetAngle(0);
			}
		}
		else{
			m_Pacman->Move(m_Pacman->GetDirection());
		}
	}
}

void App::SetPacmanSpeedMul(){
	std::vector<std::shared_ptr<Ghost>> vec = {m_Red ,m_Pink ,m_Cyan ,m_Orange};
	for(auto& ghost : vec){
		if(ghost->IsBeingChase()){
			m_Pacman->SetSpeedMul(currentLevel.GetPacmanFrightSpeedMul());
			return;
		}
	}
	m_Pacman->SetSpeedMul(currentLevel.GetPacmanSpeedMul());
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
		    MyElapsedTime() - Ghost->GetMarker() > scatter){
			Ghost->SetState(Ghost::GhostState::CHASE);
			Ghost->SetMarker(MyElapsedTime());
		}
		if(Ghost->GetState() == Ghost::GhostState::CHASE && 
		    MyElapsedTime() - Ghost->GetMarker() > chase){
			Ghost->SetState(Ghost::GhostState::SCATTER);
			Ghost->SetMarker(MyElapsedTime());
		}
		// onPill and flashing
		if(Ghost->GetState() == Ghost::GhostState::SCARED &&
		    MyElapsedTime() - FoodEffectMarker < PILL_DURATION &&
		    MyElapsedTime() - FoodEffectMarker > DONT_FLASH_DURATION){
			Ghost->SetState(Ghost::GhostState::FLASHING);
		}
		// onPill and not flashing
		if((Ghost->GetState() == Ghost::GhostState::SCATTER ||
		    Ghost->GetState() == Ghost::GhostState::CHASE) &&
		    MyElapsedTime() - FoodEffectMarker < PILL_DURATION &&
		    MyElapsedTime() - FoodEffectMarker < DONT_FLASH_DURATION){
			Ghost->SetState(Ghost::GhostState::SCARED);
		}
		// after pill
		if(Ghost->GetState() == Ghost::GhostState::FLASHING &&
		   	MyElapsedTime() - FoodEffectMarker > PILL_DURATION){
			Ghost->SetState(Ghost::GhostState::SCATTER);
			Ghost->SetMarker(MyElapsedTime());
		}
		if( (Ghost->GetState() == Ghost::GhostState::SCARED || 
			Ghost->GetState() == Ghost::GhostState::FLASHING) &&
			IfCollides(Ghost)) {
			Ghost->SetState(Ghost::GhostState::DEAD);
		}	
		//if DEAD and back home
		if( Ghost->GetState() == Ghost::GhostState::DEAD &&
			m_BackgroundImage->GetTileOfPosition(Ghost->GetPosition()) == std::pair{14, 11}){
			Ghost->SetState(Ghost::GhostState::REVIVE);
			Ghost->SetMarker(MyElapsedTime());
		}
		
	}
	
}

void App::GhostMoveProcess() {
	SetGhostSpeedMul(m_Red);
	SetGhostSpeedMul(m_Pink);
	SetGhostSpeedMul(m_Cyan);
	SetGhostSpeedMul(m_Orange);
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
		if(ghostState == Ghost::GhostState::CHASE||
			ghostState == Ghost::GhostState::REVIVE){	
			ghostTargetTile = pacmanTile;
		}
		else if(ghostState == Ghost::GhostState::SCARED || 
				ghostState == Ghost::GhostState::FLASHING ||
				ghostState == Ghost::GhostState::SCATTER){	
			ghostTargetTile = {NUMBEROFTILESX-2 ,1}; //upper right at map
		}
	}
	else if(ghost == m_Pink){
		if(ghostState == Ghost::GhostState::CHASE||
			ghostState == Ghost::GhostState::REVIVE){
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
		else if(ghostState == Ghost::GhostState::SCARED || 
				ghostState == Ghost::GhostState::FLASHING ||
				ghostState == Ghost::GhostState::SCATTER){	
			ghostTargetTile = {1 ,1}; //upper left at map
		}

	}
	else if(ghost == m_Cyan){
		if(ghostState == Ghost::GhostState::CHASE||
			ghostState == Ghost::GhostState::REVIVE){	
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
		else if(ghostState == Ghost::GhostState::SCARED ||
				ghostState == Ghost::GhostState::FLASHING ||
				ghostState == Ghost::GhostState::SCATTER){
			ghostTargetTile = {NUMBEROFTILESX-2 ,NUMBEROFTILESY-2}; //lower right at map
		}
	}
	else if(ghost == m_Orange){
		std::pair<int ,int> orangeGhostTile = m_BackgroundImage->GetTileOfPosition(m_Orange->GetPosition());
		//Get Euclidean distance between orange's tile and Pacman's tile.
		float distance = std::sqrt(std::pow(orangeGhostTile.first-pacmanTile.first ,2) + std::pow(orangeGhostTile.second-pacmanTile.second ,2));					
		if( (ghostState == Ghost::GhostState::CHASE ||
			ghostState == Ghost::GhostState::REVIVE) && 
			distance >= 8){
			ghostTargetTile = pacmanTile;
		}
		else if(ghostState == Ghost::GhostState::SCARED ||
				ghostState == Ghost::GhostState::SCATTER ||
				ghostState == Ghost::GhostState::FLASHING ||
				distance < 8){
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
	if(g->IsBeingChase()){
		g->SetSpeedMul(currentLevel.GetGhostFrightSpeedMul());
	}
	else if(g->GetState() == Ghost::GhostState::DEAD){
		g->SetSpeedMul(1.5);
	}
	else{
		g->SetSpeedMul(currentLevel.GetGhostSpeedMul());
	}

	glm::vec2 pos = g->GetPosition();
	std::pair tile = g->GetTileOfPosition(pos);
	if(tile.second == TUNNEL_TILE_Y && (tile.first >= TUNNEL_TILE_1_X || tile.first <= TUNNEL_TILE_2_X)){ //Is in tunnel.
		g->SetSpeedMul(currentLevel.GetGhostTunnelSpeedMul());	
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
	
	m_BGM.PlayNormal(m_Score->GetFoodScore());
}

void App::PacmanDead() {
	m_SFX.PlayPacmanDeath();
	m_BGM.Pause();
	LOG_DEBUG("PACMAN EATEN");
	m_Pacman->HpMinusOne();	

	// Undisplay some objs
	m_Pacman->SetVisible(false);
	m_Cyan->SetVisible(false);
	m_Red->SetVisible(false);
	m_Orange->SetVisible(false);
	m_Pink->SetVisible(false);
	m_Bonus->SetVisible(false);
	for (auto& Food : m_SmallFood) {
		Food->SetZIndex(-2);
	}
	for (auto& Food : m_LargeFood) {
		Food->SetZIndex(-2);
	}
	// Start dead animation
	m_PacmanDead->SetPosition(m_Pacman->GetPosition());
	m_PacmanDead->SetVisible(true);
	m_PacmanDead->SetLooping(true);
	m_PacmanDead->SetPlaying(true);
	m_PacmanDead->SetFrame(0);
	m_CurrentState = State::DEAD;
	m_Renderer.Update();
}

void App::BonusCtrl(){
	//Is Pacman ate enough Food?
	if((FoodEatenNum() > BONUS_STAGE_1 && !alreadyStage1)){
		m_Bonus->SetVisible(true);
		m_Bonus->SetMarker(MyElapsedTime());
		alreadyStage1 = true;
	}
	else if(FoodEatenNum() > BONUS_STAGE_2 && !alreadyStage2){
		m_Bonus->SetVisible(true);
		m_Bonus->SetMarker(MyElapsedTime());
		alreadyStage2 = true;
	}

	if(m_Bonus->GetVisibility() && IfCollides(m_Bonus)){	
		m_Bonus->SetVisible(false);
		LOG_DEBUG("BONUS EATEN");
		m_Score->AddVisibleScore(currentLevel.GetBounsScore());
		m_FlashText->SetText(std::to_string(currentLevel.GetBounsScore()));
		m_FlashText->SetPosition(m_Pacman->GetPosition());
		m_FlashText->SetVisible(true);
		m_FlashText->SetMarker(MyElapsedTime());
		m_SFX.PlayEatBonus();
	}
	
	if(MyElapsedTime() - m_Bonus->GetMarker() > m_Bonus->GetAppearTime()){
		m_Bonus->SetVisible(false);
	}
	
	
}

void App::TimeOutFlashText(){
	if(MyElapsedTime() - m_FlashText->GetMarker() > 2000){
		m_FlashText->SetVisible(false);
	}
}

unsigned long App::NextLevelInit(unsigned long InitTime){
	LevelInit(InitTime + LEVEL_UP_ANIMATION_DURATION);

	// Reset level values
	m_Score->SetFoodScore(0);
	
	return MyElapsedTime();
}

unsigned long App::LevelInit(unsigned long InitTime){
	if(MyElapsedTime() - InitTime > GAME_OPENING_TIME_DURATION){
        m_ReadyText->SetVisible(false);
        
		m_Pacman->SetPlaying(true);
		m_Red->SetPlaying(true);
		m_Pink->SetPlaying(true);
		m_Orange->SetPlaying(true);
		m_Cyan->SetPlaying(true);

		m_Pacman->SetLooping(true);
		m_Red->SetLooping(true);
		m_Pink->SetLooping(true);
		m_Orange->SetLooping(true);
		m_Cyan->SetLooping(true);

		m_Red->SetFrame(0);
		m_Pink->SetFrame(0);
		m_Orange->SetFrame(0);
		m_Cyan->SetFrame(0);
		m_Pacman->SetFrame(0);

		m_Red->SetMarker(MyElapsedTime());
		m_Pink->SetMarker(MyElapsedTime());
		m_Cyan->SetMarker(MyElapsedTime());
		m_Orange->SetMarker(MyElapsedTime());

		m_CurrentState = State::UPDATE;
	}
	else if(MyElapsedTime() - InitTime > GAME_OPENING_TIME_DURATION/2.5){
		m_Red->SetVisible(true);
        m_Pink->SetVisible(true);
        m_Orange->SetVisible(true);        
        m_Cyan->SetVisible(true);  

		m_Red->SetFrame(0);
		m_Pink->SetFrame(0);
		m_Orange->SetFrame(0);
		m_Cyan->SetFrame(0);
		m_Pacman->SetFrame(0);
	}
	else{
		m_ReadyText->SetVisible(true);

		for (auto& Food : m_SmallFood) {
			Food->SetVisible(true);
			Food->SetZIndex(10);
		}
		for (auto& Food : m_LargeFood) {
			Food->SetVisible(true);
			Food->SetZIndex(10);
		}

		m_Pacman->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(PACMAN_STARTTILE_X, PACMAN_STARTTILE_Y));
        m_Pink->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, 1));
        m_Red->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, 1));
        m_Cyan->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(NUMBEROFTILESX - 2, NUMBEROFTILESY - 2));
		m_Orange->SetPosition(m_BackgroundImage->GetCenterPositionOfTile(1, NUMBEROFTILESY - 2));

		// Stop animation for dead pacman
		m_PacmanDead->SetLooping(false);
		m_PacmanDead->SetVisible(false);
		m_PacmanDead->SetPlaying(false);

		m_Pacman->SetPlaying(false);
		m_Red->SetPlaying(false);
		m_Pink->SetPlaying(false);
		m_Orange->SetPlaying(false);
		m_Cyan->SetPlaying(false);

		m_Pacman->SetLooping(false);
		m_Red->SetLooping(false);
		m_Pink->SetLooping(false);
		m_Orange->SetLooping(false);
		m_Cyan->SetLooping(false);

		m_Red->SetFrame(0);
		m_Pink->SetFrame(0);
		m_Orange->SetFrame(0);
		m_Cyan->SetFrame(0);
		m_Pacman->SetFrame(0);
		
		m_Red->SetState(Ghost::GhostState::SCATTER);
		m_Pink->SetState(Ghost::GhostState::SCATTER);
		m_Cyan->SetState(Ghost::GhostState::SCATTER);
		m_Orange->SetState(Ghost::GhostState::SCATTER);

		m_Pacman->SetVisible(true);
	}

	alreadyStage1 = false;
	alreadyStage2 = false;
	m_Bonus->SetVisible(false);
	m_Bonus->SetImage(currentLevel.GetBonusImgPath());
	if(currentLevel.GetCurrentLevel() < TOTAL_LEVEL-2)//The bonuses for the last three levels are same and don't need to displayed repeately.
		m_BonusIcons[currentLevel.GetCurrentLevel()]->SetVisible(true);

	m_Renderer.Update();
	return MyElapsedTime();
}

void App::AddLifeDetect(){
	if(alreadyAddIife == false && m_Score->GetVisibleScore() >= ADD_LIFE_BOUNDARY){
		m_SFX.PlayExtent();
		m_LifeIcons[m_Pacman->GetHp()-1]->SetVisible(true); 
		alreadyAddIife = true;	
		m_Pacman->HpAddOne();
	}
}

