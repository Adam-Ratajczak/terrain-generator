#pragma once

#include "NotifyUser.hpp"
#include "Widget.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <functional>

namespace GUI {

class Textbox : public Widget {
    sf::String m_content, m_placeholder;
    sf::Color m_bg_color = sf::Color(220, 220, 220);
    sf::Color m_fg_color = sf::Color(120, 120, 120);
    sf::Color m_text_color = sf::Color(30, 30, 30);
    sf::Color m_placeholder_color = sf::Color(80, 80, 80);
    unsigned m_limit = 16;
    bool m_has_decimal = false, m_dragging = false;
    unsigned m_cursor = 0, m_concurrent = 0;

public:
    enum Type {
        TEXT,
        NUMBER
    };

    Type m_type = NUMBER;

    explicit Textbox(Container& c)
        : Widget(c) { }

    void set_display_attributes(sf::Color bg_color, sf::Color fg_color, sf::Color text_color);
    virtual void handle_event(Event&) override;
    virtual void draw(sf::RenderWindow& window) const override;
    void set_limit(unsigned limit) { m_limit = limit; }

    sf::String get_content() const { return m_content; }
    void set_content(sf::String content, NotifyUser = NotifyUser::Yes);
    void set_data_type(Type type) { m_type = type; }
    void set_placeholder(std::string placeholder) { m_placeholder = placeholder; }

    void set_cursor(unsigned);

    std::function<void(std::string)> on_change;

private:
    bool can_insert_character(uint32_t) const;
    unsigned m_character_pos_from_mouse(Event& event);
    sf::Vector2f calculate_cursor_position() const;
    sf::Text generate_sf_text() const;

    enum class CursorDirection {
        Left,
        Right
    };
    void move_cursor_by_word(CursorDirection);

    float m_scroll = 0;
};

}
