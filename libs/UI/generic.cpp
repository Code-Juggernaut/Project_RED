#include"generic.h"
namespace utils{
    
    double map_range(double x, double in_min, double in_max, double out_min, double out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }




    void resize_window(){
        window_size = window->getSize();
        
        //render_texture->resize({window_size.x,window_size.y});
        aspect_ratio = (float)window_size.x/(float)window_size.y;
        
        view.zoom(1.0);
        //render_texture.setView(view);
        render_texture.setSmooth(false);
        
       // view.setViewport(sf::FloatRect({}));
        window->setView(view);
        //render_sprite.setPosition({((float)render_texture.getSize().x - window_size.x)/2.0f,0});
    }

    void init_window(){
        
        window->setVerticalSyncEnabled(true);
        //view.setViewport();
        resize_window();
    }
    


    void update_window(){
        render_texture.display();

        render_sprite.setTexture(render_texture.getTexture());
        
        window->draw(render_sprite);
    }


    void load_font(){
        if(!font.openFromFile(font_path)){
            throw std::runtime_error("Can't load font");
        }
    }

    void draw_table(){
        
    }

    void draw_button(std::vector<button> &buttons){
        sf::RectangleShape rect;
        rect.setOutlineThickness(2.f);
        sf::Text text(font);
        text.setCharacterSize(button_size);
        for(const auto &i: buttons){
            rect.setSize(i.size);
            rect.setPosition(i.position);
            text.setPosition(i.position);
            text.setString(" " + i.title + " ");
            switch (i.button_state) {
                case ACTIVED:rect.setOutlineColor(i.color.active_color);text.setFillColor(i.color.active_color);break;
                case INACTIVED:rect.setOutlineColor(i.color.inactive_color);text.setFillColor(i.color.inactive_color);break;
                case ENABLED:rect.setOutlineColor(i.color.enabled_color);text.setFillColor(i.color.enabled_color);break;
                case DISABLED:rect.setOutlineColor(i.color.disabled_color);text.setFillColor(i.color.disabled_color);break;
                case HOVERED:rect.setOutlineColor(i.color.hovered_color);text.setFillColor(i.color.hovered_color);break;
                case HIDEN:rect.setOutlineColor(sf::Color(0,0,0,0));text.setFillColor(sf::Color(0,0,0,0));break;
            }
            rect.setFillColor(background_color);
            if(i.button_state != HIDEN){
                render_texture.draw(rect);
                render_texture.draw(text);
            }
            
        }
    }

    void draw_text_input(std::vector<text_input> &text_inputs){
        sf::RectangleShape rect;
        sf::Text text(font);
        rect.setOutlineThickness(2.f);
        rect.setFillColor(background_color);
        text.setCharacterSize(console_font_size);
        for(const auto &i: text_inputs){
            rect.setSize(i.size);
            rect.setPosition(i.position);
            text.setString(i.data);
            text.setPosition(i.position);
            switch (i.text_io_state) {
                case ACTIVED:rect.setOutlineColor(i.color.active_color);text.setFillColor(i.color.active_color);break;
                case INACTIVED:rect.setOutlineColor(i.color.inactive_color);text.setFillColor(i.color.inactive_color);break;
                case ENABLED:rect.setOutlineColor(i.color.enabled_color);text.setFillColor(i.color.enabled_color);break;
                case DISABLED:rect.setOutlineColor(i.color.disabled_color);text.setFillColor(i.color.disabled_color);break;
                case HOVERED:rect.setOutlineColor(i.color.hovered_color);text.setFillColor(i.color.hovered_color);break;
                case HIDEN:rect.setOutlineColor(sf::Color(0,0,0,0));text.setFillColor(sf::Color(0,0,0,0));break;
            }

            render_texture.draw(rect);
            render_texture.draw(text);
        }
    }

    void draw_text(std::vector<text> &texts){
        sf::RectangleShape rect;
        sf::Text text(font);
        rect.setOutlineThickness(2.f);
        
        rect.setOutlineColor(context_color);
        rect.setFillColor(background_color);
        text.setCharacterSize(console_font_size);
        for(const auto &i: texts){
            text.setFillColor(i.color);
            rect.setPosition(i.position);
            rect.setSize(i.size);
            window->draw(rect);
            text.setPosition(i.position);
            int temp = 0;
            switch (i.text_io_state) {
                case ACTIVED:rect.setOutlineColor(i.color);text.setFillColor(i.color);break;
                case HIDEN:rect.setOutlineColor(sf::Color(0,0,0,0));text.setFillColor(sf::Color(0,0,0,0));break;
                default:rect.setOutlineColor(sf::Color(0,0,0,0));text.setFillColor(sf::Color(0,0,0,0));break;
            }
            for(const auto &j : i.data){
                
                text.setString(j);
                text.setPosition({i.position.x, i.position.y +console_font_size*temp+5});
                temp++;
                render_texture.draw(text);
            }
        }
    }

    void is_button_pressed(sf::Vector2i coordinates,std::vector<button> &buttons,std::optional<sf::Event> &event){
        for(int i = 0;i<buttons.size();i++){
            bool mouse_click = false;
            if(const auto *click = event->getIf<sf::Event::MouseButtonPressed>()){
                mouse_click = true;
            }
            sf::FloatRect bounds(buttons[i].position,buttons[i].size);
            if(buttons[i].button_state != DISABLED && buttons[i].function != NULL && buttons[i].button_state != HIDEN){
                if(bounds.contains({(float)coordinates.x,(float)coordinates.y})){
                //buttons[i].button_state = ACTIVED;
                    if(mouse_click == true){

                        buttons[i].button_state = ACTIVED;
                        buttons[i].function();
                    }else{
                        buttons[i].button_state = HOVERED;
                    }
                }else{
                    buttons[i].button_state = INACTIVED;
                }
            }
        }
    }

    void is_text_input_active(sf::Vector2i coordinates,std::vector<text_input> &text_inputs,std::optional<sf::Event> &event){
        for(int i = 0;i<text_inputs.size();i++){
            bool mouse_click = false;
            if(const auto *click = event->getIf<sf::Event::MouseButtonPressed>()){
                mouse_click = true;
            }
            sf::FloatRect bounds(text_inputs[i].position,text_inputs[i].size);
            
            if(mouse_click == true){
                if(bounds.contains({(float)coordinates.x,(float)coordinates.y})){
                    /*if(text_inputs[i].text_io_state == ACTIVED){
                        text_inputs[i].text_io_state = HOVERED;
                    }else{
                        text_inputs[i].text_io_state = ACTIVED;
                    }*/
                    //text_inputs[i].function();
                    text_inputs[i].text_io_state = ACTIVED;
                }else{
                    text_inputs[i].text_io_state = INACTIVED;
                }
            }
        }
    }

    void enter_text(std::vector<text_input> &text_fields, sf::String &text){
        for(int i = 0;i<text_fields.size();i++){
            if(text_fields[i].text_io_state == ACTIVED){
                text_fields[i].data += text;
            }
        }
    }

    sf::String *get_text(std::vector<text_input> &text_fields){
        
        for(int i = 0;i<text_fields.size();i++){
            if(text_fields[i].text_io_state == ACTIVED){
                return &text_fields[i].data;
            }
        }
        return NULL;
    }
}