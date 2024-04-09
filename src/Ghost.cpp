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
    return { newY / PIXELPERTILE ,newX / PIXELPERTILE };
}

glm::vec2 Ghost::GetCenterPositionOfTile(int x, int y) {
    glm::vec2 center = { -216 + PIXELPERTILE * x , 240 - PIXELPERTILE * y };
    return center;
}

glm::vec2 Ghost::GetTargetPixel(std::pair<int, int> EndPosition) {
    vector<vector<int>> grid = {
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

    std::vector<std::pair<int, int>> path = aStarSearch(grid, StartPosition, EndPosition);
    if(path.size() - 1 != 0)
        return GetCenterPositionOfTile(path[path.size() - 2].second, path[path.size() - 2].first);
    else
        return GetCenterPositionOfTile(path[path.size() - 1].second, path[path.size() - 1].first);
}

void Ghost::MoveToTile(std::pair<int, int> EndPosition) {
    glm::vec2 Target = GetTargetPixel(EndPosition);
    //std::cout << "Current:" << GetPosition().x << " " << GetPosition().y << endl;
    //std::cout << "Target:" << Target.x << " " << Target.y << endl;
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

    //std::cout << "Direction:" << this->Direction << endl;
    GhostMove();
}