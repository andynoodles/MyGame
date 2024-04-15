#include "Food.hpp"

Food::Food(const std::string& ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

void Food::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
