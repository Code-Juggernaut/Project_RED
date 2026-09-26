#include<SFML/Graphics.hpp>
#include "../libs/UI/generic.h"
#pragma once

namespace frontend {
    void init(sf::RenderWindow &window);
    void event_listener(std::optional<sf::Event> &event);
    void draw();
}