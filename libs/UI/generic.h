#include <SFML/Graphics.hpp>
#include <math.h>
#include <functional>
//#define FONT_PATH "../UI/assets/Monocraft.ttf"
#pragma once

namespace utils{
    inline sf::Font font;
    inline sf::RenderWindow *window;
    inline sf::Color context_color(0,0,0,255);
    inline int console_font_size = 30;
    inline int button_size = 30;
    inline sf::Vector2u window_size ;
    inline std::string font_path;
    inline float aspect_ratio = 0.00;
    inline sf::View view(sf::FloatRect({0.0,0.0},{1.0,1.0}));
    inline sf::View trexture_view(sf::FloatRect({0.0,0.0},{1080,1080}));
    inline sf::RenderTexture render_texture({1024,1024});
    inline sf::Sprite render_sprite(render_texture.getTexture());
    inline sf::Color background_color(0,0,0);




    enum state{
        ACTIVED, INACTIVED, ENABLED, DISABLED, HOVERED,HIDEN
    };


    typedef struct{
        sf::Color active_color;
        sf::Color inactive_color;
        sf::Color enabled_color;
        sf::Color disabled_color;
        sf::Color hovered_color;
    }colors;


    typedef struct{
        enum state button_state;
        std::function<void()> function;
        colors color;
        sf::Vector2f position;
        sf::Vector2f size;
        sf::String title;
    }button;
    
    typedef struct{
        enum state text_io_state;
        std::function<void(sf::String)> function;
        sf::String data;
        colors color;
        sf::Vector2f position;
        sf::Vector2f size;
    }text_input;
    
    typedef struct{
        enum state text_io_state;
        std::vector<sf::String> data;
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Color color;
    }text;

    void resize_window();
    void init_window();
    void load_font();
    
    void draw_table();
    void draw_button(std::vector<button> &buttons);
    void draw_text_input(std::vector<text_input> &text_inputs);
    void draw_text(std::vector<text> &text_inputs);
    
    void is_button_pressed(sf::Vector2i coordinates,std::vector<button> &buttons,std::optional<sf::Event> &event);
    void is_text_input_active(sf::Vector2i coordinates,std::vector<text_input> &text_input,std::optional<sf::Event> &event);
    void enter_text(std::vector<text_input> &text_inputs,sf::String &text);
    sf::String *get_text(std::vector<text_input> &text_inputs);

    void update_window();

}