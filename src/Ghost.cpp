#include "Ghost.hpp"
#include "Util/Logger.hpp"

Ghost::Ghost(const std::vector<std::string>& AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 125, false, 0);
    m_Transform.scale = {2,2};
}

bool Ghost::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() -1;
}

void Ghost::SetPosition(const glm::vec2& Position){ 
    m_Transform.translation = Position; 
}


glm::vec2 Ghost::GetPosition(){
    return m_Transform.translation;
}

void Ghost::GhostMoveNormal(){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 0;
    if(Direction == "East") {
        Speed = {GHOST_SPEED, 0};
        StartIndex = 0;
    }
    else if(Direction == "West") {
        Speed = {-GHOST_SPEED, 0};
        StartIndex = 2;
    }
    else if(Direction == "North") {
        Speed = {0, GHOST_SPEED};
        StartIndex = 4;
    }
    else if(Direction == "South") {
        Speed = {0, -GHOST_SPEED};
        StartIndex = 6;
    }

    if(temp->GetCurrentFrameIndex() > StartIndex + 1 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 2){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

void Ghost::GhostMoveScared(){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 8;
    if(Direction == "East") {
        Speed = {GHOST_SPEED, 0};
    }
    else if(Direction == "West") {
        Speed = {-GHOST_SPEED, 0};
    }
    else if(Direction == "North") {
        Speed = {0, GHOST_SPEED};
    }
    else if(Direction == "South") {
        Speed = {0, -GHOST_SPEED};
    }
    if(temp->GetCurrentFrameIndex() > StartIndex + 1 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 2){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

void Ghost::GhostMoveFlash(){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 8;
    if(Direction == "East") {
        Speed = {GHOST_SPEED, 0};
    }
    else if(Direction == "West") {
        Speed = {-GHOST_SPEED, 0};
    }
    else if(Direction == "North") {
        Speed = {0, GHOST_SPEED};
    }
    else if(Direction == "South") {
        Speed = {0, -GHOST_SPEED};
    }
    if(temp->GetCurrentFrameIndex() > StartIndex + 4 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 5){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

void Ghost::GhostMoveEye() {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 0;
    if (Direction == "East") {
        Speed = { GHOST_SPEED, 0 };
        StartIndex = 15;
    }
    else if (Direction == "West") {
        Speed = { -GHOST_SPEED, 0 };
        StartIndex = 14;
    }
    else if (Direction == "North") {
        Speed = { 0, GHOST_SPEED };
        StartIndex = 16;
    }
    else if (Direction == "South") {
        Speed = { 0, -GHOST_SPEED };
        StartIndex = 13;
    }
    if (temp->GetCurrentFrameIndex() < StartIndex || temp->GetCurrentFrameIndex() > StartIndex) {
        temp->SetCurrentFrame(StartIndex);
    }

    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier);
}

void Ghost::GhostMove(){
    switch (State)
    {
    case Ghost::GhostState::NORMAL:
        GhostMoveNormal();
        break;
    case Ghost::GhostState::SCARED:
        GhostMoveScared();
        break;
    case Ghost::GhostState::FLASHING:
        GhostMoveFlash();
        break;
    case Ghost::GhostState::DEAD:
        GhostMoveEye();
        break;
    default:
        GhostMoveNormal();
        break;
    }
}

std::pair<int, int> Ghost::GetTileOfPosition(glm::vec2 position) {
    int newX = position.x + 224, newY = 248 - position.y;
    return { newX / PIXELPERTILE ,newY / PIXELPERTILE };
}

glm::vec2 Ghost::GetCenterPositionOfTile(int x, int y) {
    glm::vec2 center = { -216 + PIXELPERTILE * x , 240 - PIXELPERTILE * y };
    return center;
}

glm::vec2 Ghost::GetTargetPixel(std::pair<int, int> EndPosition) {
    std::vector<std::vector<int>> grid = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    std::pair<int, int> StartPosition = GetTileOfPosition(this->GetPosition());
    LOG_DEBUG("x:{}, y:{}", StartPosition.first, StartPosition.second);
    std::pair<int, int > NextTile = FindNextTile(grid, StartPosition, EndPosition);
    return GetCenterPositionOfTile(NextTile.second, NextTile.first); 
}

void Ghost::MoveToTile(std::pair<int, int> EndPosition) {
    EndPosition = {EndPosition.second, EndPosition.first};
    glm::vec2 Target = GetTargetPixel(EndPosition);

    if (GetPosition().x < Target.x && fabs(GetPosition().y - Target.y) < 10) {
        SetDirection("East");
        SetPosition({GetPosition().x, Target.y});
    }
    else if (GetPosition().x > Target.x && fabs(GetPosition().y - Target.y) < 10) {
        SetDirection("West");
        SetPosition({GetPosition().x, Target.y});
    }
    else if (fabs(GetPosition().x - Target.x) < 10 && GetPosition().y > Target.y) {
        SetDirection("South");
        SetPosition({Target.x, GetPosition().y});
    }
    else if (fabs(GetPosition().x - Target.x) < 10 && GetPosition().y < Target.y) {
        SetDirection("North");
        SetPosition({Target.x, GetPosition().y});
    }

    GhostMove();
}

double distance(const std::pair<int, int>& vec1, const std::pair<int, int>& vec2) {
    double dx = vec1.first - vec2.first;
    double dy = vec1.second - vec2.second;
    return std::sqrt(dx * dx + dy * dy);
}

// Function to find the vector from a given set of vectors that has the shortest distance to a given vector
std::pair<int, int> findClosestVector(const std::vector<std::pair<int, int>>& vectors, const std::pair<int, int>& target) {
    double minDistance = std::numeric_limits<double>::max();
    std::pair<double, double> closestVector = vectors[0]; // Initialize with the first vector

    for (const auto& vec : vectors) {
        double dist = distance(vec, target);
        if (dist < minDistance) {
            minDistance = dist;
            closestVector = vec;
        }
    }

    return closestVector;
}

std::pair<int, int> Ghost::FindNextTile(std::vector<std::vector<int>>& grid, std::pair<int, int> CurrentTile, std::pair<int, int> TargetTile){
    std::vector<std::pair<int, int >> Roads;
    if(grid[CurrentTile.second + 1][CurrentTile.first] == 0){
		// Check North Tile
		Roads.push_back({CurrentTile.second + 1, CurrentTile.first});
	}
	if(grid[CurrentTile.second - 1][CurrentTile.first] == 0){
		// Check South Tile
		Roads.push_back({CurrentTile.second - 1, CurrentTile.first});
	}	
	if(grid[CurrentTile.second][CurrentTile.first + 1] == 0){
		// Check East Tile
		Roads.push_back({CurrentTile.second, CurrentTile.first + 1});
	}
	if(grid[CurrentTile.second][CurrentTile.first - 1] == 0){
		// Check West Tile
		Roads.push_back({CurrentTile.second, CurrentTile.first - 1});
	}
    
    return findClosestVector(Roads, TargetTile);
}
