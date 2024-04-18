#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <vector>
#include <string>
#include "config.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Pacman : public Util::GameObject {

public:
    explicit Pacman(const std::vector<std::string>& AnimationPaths);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

	//Setter
    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }
    void SetPlaying(bool play) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if(play) temp->Play();
    }
	void SetPosition(const glm::vec2& Position);
    void SetDirection(std::string Direction);
	void HpMinusOne(){hp--;}

	//Getter
	std::string GetDirection(){return MoveDirection;}
    glm::vec2 GetPosition(){return m_Transform.translation;}
	int GetHp(){return hp;}

    [[nodiscard]] bool IfAnimationEnds() const;
    
    void FaceNorth();
    void FaceSouth();
    void FaceWest();
    void FaceEast();
	void Move(const std::string Direction, float SpeedMultiplier);
   	void MoveBack(const std::string Direction, float SpeedMultiplier);
	void Stop();

private:
    std::string MoveDirection = "East";
    glm::vec2 Speed;
	int hp = 3;
};

#endif //ANIMATED_CHARACTER_HPP
