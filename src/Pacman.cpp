#include "Pacman.hpp"
#define PI 3.14159265358979323846

Pacman::Pacman(const std::vector<std::string>& AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 125, false, 0);
    m_Transform.scale = {2,2};
}

bool Pacman::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() -1;
}

void Pacman::FaceNorth(){
    m_Transform.rotation = PI / 2;
}
void Pacman::FaceSouth(){
    m_Transform.rotation = 3 * PI / 2;
}
void Pacman::FaceWest(){
    m_Transform.rotation = PI;
}
void Pacman::FaceEast(){
    m_Transform.rotation = 0;
}

void Pacman::SetPosition(const glm::vec2& Position){ 
    m_Transform.translation = Position; 
}

void Pacman::Move(const glm::vec2& Speed, float SpeedMultiplier = 1){ 
    if(Speed.x > 0 && Speed.y == 0) FaceEast();
    else if(Speed.x < 0 && Speed.y == 0) FaceWest();
    else if(Speed.x == 0 && Speed.y > 0) FaceNorth();
    else if(Speed.x == 0 && Speed.y < 0) FaceSouth();
    m_Transform.translation = m_Transform.translation + (Speed * SpeedMultiplier); 
}

glm::vec2 Pacman::GetPosition(){
    return m_Transform.translation;
}
