#include "Ghost.hpp"
#define PI 3.14159265358979323846

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

void Ghost::GhostMove(const glm::vec2 &Speed, float SpeedMultiplier){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 0;
    //East
    if(Speed.x > 0 && Speed.y == 0) StartIndex = 0;
    //West
    else if(Speed.x < 0 && Speed.y == 0) StartIndex = 2;
    //North
    else if(Speed.x == 0 && Speed.y > 0) StartIndex = 4;
    //South
    else if(Speed.x == 0 && Speed.y < 0) StartIndex = 6;
    if(temp->GetCurrentFrameIndex() > StartIndex + 1 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 2){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

void Ghost::GhostMoveScared(const glm::vec2 &Speed, float SpeedMultiplier){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 8;
    if(temp->GetCurrentFrameIndex() > StartIndex + 1 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 2){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

void Ghost::GhostMoveScaredFlash(const glm::vec2 &Speed, float SpeedMultiplier){
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    size_t StartIndex = 8;
    if(temp->GetCurrentFrameIndex() > StartIndex + 4 || temp->GetCurrentFrameIndex() < StartIndex){
        temp->SetCurrentFrame(StartIndex);
    }
    if(temp->GetCurrentFrameIndex() == StartIndex + 5){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}