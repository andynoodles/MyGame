#include "Pacman.hpp"

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

void Pacman::FaceCheat(float x){
    m_Transform.rotation = x;
}

void Pacman::SetPosition(const glm::vec2& Position){ 
    m_Transform.translation = Position; 
}

void Pacman::SetDirection(std::string Direction){
    MoveDirection = Direction;
}

void Pacman::Move(const std::string Direction){ 
    if(Direction == "East") {
        FaceEast();
        Speed = {PACMAN_SPEED, 0};
    }
    else if(Direction == "West") {
        FaceWest();
        Speed = {-PACMAN_SPEED, 0};
    }
    else if(Direction == "North") {
        FaceNorth();
        Speed = {0, PACMAN_SPEED};
    }
    else if(Direction == "South") {
        FaceSouth();
        Speed = {0, -PACMAN_SPEED};
    }
	SetPosition(m_Transform.translation + (Speed * this->SpeedMultiplier)); 
	checkTp();
}

void Pacman::CheatMove(const std::string Direction, float x){ 
    if(Direction == "East") {
        FaceCheat(-x);
        Speed = {PACMAN_SPEED, 0};
    }
    else if(Direction == "West") {
        FaceCheat(x);
        Speed = {-PACMAN_SPEED, 0};
    }
    else if(Direction == "North") {
        FaceCheat(-x);
        Speed = {0, PACMAN_SPEED};
    }
    else if(Direction == "South") {
        FaceCheat(x);
        Speed = {0, -PACMAN_SPEED};
    }
	SetPosition(m_Transform.translation + (Speed * this->SpeedMultiplier)); 
	checkTp();
}

void Pacman::Stop(){
	SetPosition(GetPosition()); 
}

void Pacman::SetSpeedMul(float mul){
	SpeedMultiplier = mul;
}

void Pacman::checkTp(){
	if(GetPosition().x > TP_X1)	SetPosition({TP_X2 ,GetPosition().y});
	else if(GetPosition().x < TP_X2) SetPosition({TP_X1 ,GetPosition().y});
}
