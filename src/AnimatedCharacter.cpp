#include "AnimatedCharacter.hpp"
#define PI 3.14159265358979323846

AnimatedCharacter::AnimatedCharacter(const std::vector<std::string>& AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 125, false, 0);
    m_Transform.scale = {2,2};
}

bool AnimatedCharacter::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() -1;
}

void AnimatedCharacter::FaceNorth(){
    m_Transform.rotation = PI / 2;
}
void AnimatedCharacter::FaceSouth(){
    m_Transform.rotation = 3 * PI / 2;
}
void AnimatedCharacter::FaceWest(){
    m_Transform.rotation = PI;
}
void AnimatedCharacter::FaceEast(){
    m_Transform.rotation = 0;
}

void AnimatedCharacter::SetPosition(const glm::vec2& Position){ 
    m_Transform.translation = Position; 
}

void AnimatedCharacter::Move(const glm::vec2& Speed, float SpeedMultiplier = 1){ 
    if(Speed.x > 0 && Speed.y == 0) FaceEast();
    else if(Speed.x < 0 && Speed.y == 0) FaceWest();
    else if(Speed.x == 0 && Speed.y > 0) FaceNorth();
    else if(Speed.x == 0 && Speed.y < 0) FaceSouth();
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

glm::vec2 AnimatedCharacter::GetPosition(){
    return m_Transform.translation;
}

void AnimatedCharacter::GhostMove(const glm::vec2 &Speed, float SpeedMultiplier){
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
    if(temp->GetCurrentFrameIndex() == StartIndex + 2){
        temp->SetCurrentFrame(StartIndex);
    }
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}