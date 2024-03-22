#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <cstddef>
#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"


class AnimatedCharacter : public Util::GameObject {

public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths);

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
    glm::vec2 GetPosition();
    void Move(const glm::vec2& Speed, float SpeedMultiplier);
    void GhostMove(const glm::vec2& Speed, float SpeedMultiplier);

//variables
    float SpeedMultiplier = 1;
    glm::vec2 Speed;

};

#endif //ANIMATED_CHARACTER_HPP
