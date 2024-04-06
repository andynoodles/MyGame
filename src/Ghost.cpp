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

void Ghost::GhostMove(std::string Direction, float SpeedMultiplier){
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

void Ghost::GhostMoveScared(std::string Direction, float SpeedMultiplier){
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

void Ghost::GhostMoveFlash(std::string Direction, float SpeedMultiplier){
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

void Ghost::GhostMoveEye(std::string Direction, float SpeedMultiplier) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 8;
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