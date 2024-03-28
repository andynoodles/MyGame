#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

#define PACMAN_SPEED 15

class Pacman : public Util::GameObject {

public:
    explicit Pacman(const std::vector<std::string>& AnimationPaths);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void SetPlaying(bool play) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if(play) temp->Play();
    }
    [[nodiscard]] bool IfAnimationEnds() const;
    
    void FaceNorth();
    void FaceSouth();
    void FaceWest();
    void FaceEast();
    void SetPosition(const glm::vec2& Position);
    void SetDirection(std::string Direction);
    std::string GetDirection();
    glm::vec2 GetPosition();
    void Move(const std::string Direction, float SpeedMultiplier);

private:
    std::string MoveDirection;
    glm::vec2 Speed;

};

#endif //ANIMATED_CHARACTER_HPP
