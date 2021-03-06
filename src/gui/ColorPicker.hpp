#pragma once

#include "Container.hpp"
#include "Slider.hpp"

namespace GUI {

class ColorPickerDisplay : public Widget {
public:
    explicit ColorPickerDisplay(Container& c)
        : Widget(c) { }

    void set_color(sf::Color color) { m_color = color; }

private:
    sf::Color m_color;

    virtual void draw(sf::RenderWindow& window) const override;
};

class ColorPicker : public Container {
public:
    explicit ColorPicker(Container& c);

    sf::Color value() const;

    std::function<void(sf::Color)> on_change;

private:
    std::shared_ptr<Slider> m_r_slider;
    std::shared_ptr<Slider> m_g_slider;
    std::shared_ptr<Slider> m_b_slider;
    std::shared_ptr<ColorPickerDisplay> m_color_picker_display;
};

}
