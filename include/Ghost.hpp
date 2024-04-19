#ifndef GHOST_HPP
#define GHOST_HPP

#include <vector>
#include <string>
#include <queue>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"

class Ghost : public Util::GameObject {
public:
    enum class GhostState {
        CHASE,
        SCARED,
        SCATTER,
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
    void UpdateTargetTile(std::pair<int, int> EndPosition);
    void MoveToTile(std::pair<int, int> EndPosition);
    std::pair<int, int> FindNextTile(std::pair<int, int> CurrentTile, std::pair<int, int> TargetTile);

    void SetState(GhostState state) { State = state; }
    GhostState GetState() { return State; }

    void SetDirection(std::string direction) { Direction = direction; }
    void SetSpeedMultiplier(float mul) { SpeedMultiplier = mul; }
    void SetMarker(unsigned long time) { marker = time; }
    unsigned long GetMarker() { return marker; }
private:
    glm::vec2 Speed;
    std::string Direction = "West";
    std::pair<int, int> CurrentTile;
    std::pair<int, int> TargetTile;
    std::queue<std::pair<int, int>> HistoryTile;
    float SpeedMultiplier = 1;
    unsigned long marker = 0;
    GhostState State = GhostState::SCATTER;
};

#endif //ANIMATED_CHARACTER_HPP
