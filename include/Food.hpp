#ifndef FOOD_HPP
#define FOOD_HPP

#include <glm/fwd.hpp>
#include <string>

#include "Util/GameObject.hpp"

class Food : public Util::GameObject {
public:
    explicit Food(const std::string& ImagePath);

    Food(const Food&) = delete;

    Food(Food&&) = delete;

    Food& operator=(const Food&) = delete;

    Food& operator=(Food&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Food>& other) const {
        (void) other;
        int size = 25;
        glm::vec2 OtherPostion = other->GetPosition();
        glm::vec2 ThisPostiom = this->GetPosition();
        if( ThisPostiom.x > OtherPostion.x - size &&
            ThisPostiom.x < OtherPostion.x + size &&
            ThisPostiom.y > OtherPostion.y - size &&
            ThisPostiom.y < OtherPostion.y + size){ return true;}
        return false;
    }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};


#endif //Food_HPP
