#ifndef GHOST_HPP
#define GHOST_HPP

#include <vector>
#include <string>


#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "config.hpp"
#include "Astar.hpp"

class Ghost : public Util::GameObject {
public:
    enum class GhostState {
        NORMAL,
        SCARED,
        FLASHING,
        DEAD
    };
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

    void GhostMove();
    void GhostMoveNormal();
    void GhostMoveScared();
    void GhostMoveFlash();
    void GhostMoveEye();
    
    //Path finding and moving
    std::pair<int, int> GetTileOfPosition(glm::vec2 position);
    glm::vec2 GetCenterPositionOfTile(int x, int y);
    glm::vec2 GetTargetPixel(std::pair<int, int> EndPosition);
    void MoveToTile(std::pair<int, int> EndPosition);

    void SetState(GhostState state) { State = state; }
    GhostState GetState() { return State; }

    void SetDirection(std::string direction) { Direction = direction; }
    void SetSpeedMultiplier(float mul) { SpeedMultiplier = mul; }
    void SetDeadMarker(unsigned long time) { DeadMarker = time; }
    unsigned long GetDeadMarker() { return DeadMarker; }
private:
    glm::vec2 Speed;
    std::string Direction = "West";
    float SpeedMultiplier = 1;
    unsigned long DeadMarker = 0;
    GhostState State = GhostState::NORMAL;
};

#endif //ANIMATED_CHARACTER_HPP
