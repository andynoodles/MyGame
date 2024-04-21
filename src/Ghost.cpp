#include "Ghost.hpp"

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
    case Ghost::GhostState::CHASE:
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

void Ghost::MoveToTile(std::pair<int, int> EndTile) {
    CurrentTile = GetTileOfPosition(GetPosition());
    TargetTile = FindNextTile(CurrentTile, EndTile);
    LOG_DEBUG("\nCurrent:{}, {}\nTarget: {}, {}", CurrentTile.first, CurrentTile.second, TargetTile.first, TargetTile.second);
    glm::vec2 Target = GetCenterPositionOfTile(TargetTile.first, TargetTile.second); 

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
    HistoryTile.push(CurrentTile);
    if(HistoryTile.size() > 10) HistoryTile.pop();
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

bool InQueue(std::queue<std::pair<int, int>> Queue, std::pair<int, int> Target){
    std::queue<std::pair<int, int>> myQueueCopy = Queue;

    // Iterate over the copy of the queue and print its elements
    while (!myQueueCopy.empty()) {
        if(myQueueCopy.front() == Target) return true;
        myQueueCopy.pop(); // Remove the front element
    }
    return false;
}

std::pair<int, int> Ghost::FindNextTile(std::pair<int, int> CurrentTile, 
                                        std::pair<int, int> TargetTile){
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
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
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
    std::vector<std::pair<int, int >> Roads;
    Roads.push_back({100, 100});
    Roads.push_back({100, 100});
    Roads.push_back({100, 100});
    Roads.push_back({100, 100});
    if(grid[CurrentTile.second + 1][CurrentTile.first] == 0){
		// Check North Tile
		Roads[0] = {CurrentTile.first, CurrentTile.second + 1};
	}
    if(grid[CurrentTile.second - 1][CurrentTile.first] == 0){
		// Check South Tile
		Roads[1] = {CurrentTile.first, CurrentTile.second - 1};
	}
	if(grid[CurrentTile.second][CurrentTile.first + 1] == 0){
		// Check East Tile
		Roads[2] = {CurrentTile.first + 1, CurrentTile.second};
	}
	if(grid[CurrentTile.second][CurrentTile.first - 1] == 0){
		// Check West Tile
		Roads[3] = {CurrentTile.first - 1, CurrentTile.second};
	}
    
    for (size_t i = 0; i < Roads.size(); i++) {
        if(InQueue(HistoryTile, Roads[i])) Roads[i] = {100, 100};
    }

    for (size_t i = 0; i < Roads.size(); i++) {
        LOG_DEBUG("{} {}", Roads[i].first, Roads[i].second);
    }
    return findClosestVector(Roads, TargetTile);
}
