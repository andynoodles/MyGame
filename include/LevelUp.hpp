#ifndef NEXT_LEVEL_HPP
#define NEXT_LEVEL_HPP

#include <vector>
#include <string>
#include "config.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class LevelUp : public Util::GameObject {

public:
    explicit LevelUp(const std::vector<std::string>& AnimationPaths);

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
    void SetFrame(unsigned int i) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetCurrentFrame(i);
    }

    [[nodiscard]] bool IfAnimationEnds() const;

private:

};

#endif //ANIMATED_CHARACTER_HPP
