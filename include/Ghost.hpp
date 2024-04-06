#ifndef GHOST_HPP
#define GHOST_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "config.hpp"

class Ghost : public Util::GameObject {
    enum class GhostState {
        NORMAL,
        SCARED,
        FLASHING,
        GOING_BACK
    };
public:
    explicit Ghost(const std::vector<std::string>& AnimationPaths);

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
    
    void SetPosition(const glm::vec2& Position);
    glm::vec2 GetPosition();
    void GhostMove(std::string Direction, float SpeedMultiplier);
    void GhostMoveScared(std::string Direction, float SpeedMultiplier);
    void GhostMoveFlash(std::string Direction, float SpeedMultiplier);
    void GhostMoveEye(std::string Direction, float SpeedMultiplier);

    void SetNormal() { State = GhostState::NORMAL; }
    void SetScared() { State = GhostState::SCARED; }
    void SetFlashing() { State = GhostState::GOING_BACK; }
    void SetGoingBack() { State = GhostState::GOING_BACK; }
private:
    glm::vec2 Speed;
    GhostState State = GhostState::NORMAL;
};

#endif //ANIMATED_CHARACTER_HPP
