#include "Textbox.hpp"

#include "CharacterType.hpp"
#include "Application.hpp"
#include "NotifyUser.hpp"
#include "Widget.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

namespace GUI {

void Textbox::set_display_attributes(sf::Color bg_color, sf::Color fg_color, sf::Color text_color) {
    m_bg_color = bg_color;
    m_fg_color = fg_color;
    m_text_color = text_color;
}

unsigned Textbox::m_character_pos_from_mouse(Event& event) {
    if (m_content.getSize() == 0)
        return 0;
    auto delta = sf::Vector2f(event.event().mouseButton.x, event.event().mouseButton.y) - position();

    sf::Text text = generate_sf_text();

    // We can just check the offset of 1st character because we use
    // a fixed width font. Normally we would need to iterate over characters
    // to find the nearest one.
    float character_width = text.findCharacterPos(1).x - text.getPosition().x;

    if (delta.x < 0)
        return 0;
    else if (m_cursor > m_content.getSize())
        return m_content.getSize();
    return (delta.x - m_scroll) / character_width;
}

void Textbox::set_content(sf::String content, NotifyUser notify_user) {
    m_content = std::move(content);
    m_cursor = m_content.getSize();
    m_has_decimal = false;

    if (m_content.find(".") != sf::String::InvalidPos)
        m_has_decimal = true;
    if (on_change && notify_user == NotifyUser::Yes)
        on_change(m_content);
}

void Textbox::set_cursor(unsigned cursor) {
    if (cursor > m_content.getSize())
        m_cursor = m_content.getSize();
    else
        m_cursor = cursor;

    auto new_cursor_position = calculate_cursor_position();
    if (new_cursor_position.x < 2)
        m_scroll += 2 - new_cursor_position.x;
    if (new_cursor_position.x > size().x - 4)
        m_scroll += size().x - new_cursor_position.x - 4;
}

void Textbox::handle_event(Event& event) {
    auto pos = sf::Mouse::getPosition();
    if (event.type() == sf::Event::TextEntered) {
        if (is_focused()) {
            auto codepoint = event.event().text.unicode;
            if (codepoint == '\b') {
                if (m_cursor != 0) {
                    m_content.erase(m_cursor - 1);
                    set_cursor(m_cursor - 1);
                    if (m_type == NUMBER && m_content.isEmpty())
                        m_content = "0";
                    if (on_change)
                        on_change(m_content);
                }
            }
            else if (codepoint == 0x7f) {
                if (m_cursor != m_content.getSize()) {
                    m_content.erase(m_cursor);
                    if (m_type == NUMBER && m_content.isEmpty())
                        m_content = "0";
                    if (on_change)
                        on_change(m_content);
                }
            }
            else if (can_insert_character(codepoint)) {
                if (m_type == NUMBER && m_content == "0")
                    m_content = "";
                m_content.insert(m_cursor, codepoint);
                if (on_change)
                    on_change(m_content);
                set_cursor(m_cursor + 1);
            }

            event.set_handled();
        }
    }
    else if (event.type() == sf::Event::KeyPressed) {
        if (is_focused()) {
            // FIXME: Focus check should be handled at Widget level.
            switch (event.event().key.code) {
            case sf::Keyboard::Left: {
                if (event.event().key.control)
                    move_cursor_by_word(CursorDirection::Left);
                else if (m_cursor > 0)
                    set_cursor(m_cursor - 1);

                if (!event.event().key.shift)
                    m_concurrent = m_cursor;
                event.set_handled();
            } break;
            case sf::Keyboard::Right: {
                if (event.event().key.control)
                    move_cursor_by_word(CursorDirection::Right);
                else if (m_cursor < m_content.getSize())
                    set_cursor(m_cursor + 1);

                if (!event.event().key.shift)
                    m_concurrent = m_cursor;
                event.set_handled();
            } break;
            default:
                break;
            }
        }
    }
    else if (event.type() == sf::Event::MouseButtonPressed) {
        if (is_hover()) {

            m_cursor = m_character_pos_from_mouse(event);
            m_concurrent = m_cursor;

            m_dragging = true;
        }
    }
    else if (event.type() == sf::Event::MouseButtonReleased) {
        m_dragging = false;
    }
}

void Textbox::move_cursor_by_word(CursorDirection direction) {
    // Trying to mimic vscode behavior in c++ source files.
    enum class State {
        Start,
        PendingPunctuation,
        PendingCharactersOfType,
        Done
    } state
        = State::Start;
    Util::CharacterType last_character_type = Util::CharacterType::Unknown;

    auto is_in_range = [&](int offset) {
        return (direction == CursorDirection::Left && offset > 0) || (direction == CursorDirection::Right && offset < m_content.getSize());
    };

    while (state != State::Done && is_in_range(m_cursor)) {
        auto next = m_content[direction == CursorDirection::Left ? m_cursor - 1 : m_cursor + 1];
        std::cout << "'" << (char)next << "' " << (int)state << " : " << ispunct(next) << std::endl;
        switch (state) {
        case State::Start:
            if (ispunct(next))
                state = State::PendingCharactersOfType;
            else if (!isspace(next)) {
                if (is_in_range(m_cursor - 2) && ispunct(m_content[direction == CursorDirection::Left ? m_cursor - 1 : m_cursor]))
                    state = State::PendingPunctuation;
                else
                    state = State::PendingCharactersOfType;
                m_cursor++;
            }
            break;
        case State::PendingPunctuation:
            assert(ispunct(next));
            state = State::PendingCharactersOfType;
            break;
        case State::PendingCharactersOfType: {
            auto next_type = Util::character_type(next);
            if (next_type != last_character_type && last_character_type != Util::CharacterType::Unknown) {
                state = State::Done;
                if (direction == CursorDirection::Left)
                    m_cursor++;
            }
            last_character_type = next_type;
            break;
        }
        default:
            assert(false);
            break;
        }
        if (direction == CursorDirection::Left)
            m_cursor--;
        else if (m_cursor < m_content.getSize())
            m_cursor++;
    }
    std::cout << "DONE" << std::endl;
}

sf::Text Textbox::generate_sf_text() const {
    // TODO: Cache the result
    sf::Text text(m_content, application().fixed_width_font, 16);
    text.setFillColor(m_text_color);
    text.setPosition(5, 2 + size().y / 2 - 12);
    text.move(m_scroll, 0);
    auto bounds = text.getLocalBounds();
    text.setOrigin(0, 0); // -6 because of SFML not taking descenders into account

    if (!is_focused() && m_content.getSize() == 0) {
        text.setFillColor(m_placeholder_color);
        text.setString(m_placeholder);
    }

    return text;
}

sf::Vector2f Textbox::calculate_cursor_position() const {
    return generate_sf_text().findCharacterPos(m_cursor);
}

void Textbox::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rect(size());
    rect.setOutlineColor(sf::Color(80, 80, 80));
    rect.setOutlineThickness(-2);
    rect.setFillColor(are_all_parents_enabled() ? m_bg_color : m_bg_color - sf::Color(60, 60, 60, 0));

    if (is_focused())
        rect.setOutlineColor(are_all_parents_enabled() ? m_fg_color : m_fg_color - sf::Color(39, 39, 39, 0));

    window.draw(rect);

    auto text = generate_sf_text();
    window.draw(text);

    // if(m_cursor != m_concurrent){
    //     unsigned step = text.getCharacterSize() + text.getLetterSpacing();
    //     if(text.getString() != m_placeholder){
    //         sf::RectangleShape rect;
    //         rect.setPosition(sf::Vector2f(text.getPosition().x + std::min(m_cursor, m_concurrent) * step, text.getPosition().y));
    //         rect.setSize(sf::Vector2f(std::fabs(m_cursor - m_concurrent) * step, text.getGlobalBounds().height));
    //         rect.setFillColor(m_placeholder_color);

    //         window.draw(rect);
    //     }
    // }

    if (is_focused()) {
        sf::RectangleShape cursor(sf::Vector2f(2, std::min(size().y - 6, 30.f)));
        auto position = calculate_cursor_position();
        cursor.setPosition({ position.x, size().y / 2 - cursor.getSize().y / 2 });
        cursor.setFillColor(sf::Color::Black);
        window.draw(cursor);
    }
}

bool Textbox::can_insert_character(uint32_t ch) const {
    switch (m_type) {
    case TEXT:
        return isprint(ch);
    case NUMBER:
        return isdigit(ch) || (ch == '.' && !m_has_decimal);
    }
    return false;
}
}
