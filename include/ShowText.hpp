#ifndef SHOWTEXT_HPP
#define SHOWTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <string>

class ShowText : public Util::GameObject {
public:
    ShowText(
    const std::string& font, 
    int size, 
    const std::string& text,
    const Util::Color& color = Util::Color(127, 127, 127))
     : GameObject(
            std::make_unique<Util::Text>(font, size, text, color), 100) {
        m_Transform.translation = {0.0F, -270.F};
    }

    void SetPosition(glm::vec2 position){
        m_Transform.translation = position;
    }

    void SetText(std::string newString){
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(newString);
    }

private:
    
};


#endif //TASKTEXT_HPP
