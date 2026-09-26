#include "frontend.h"
#include "../functional/functional.h"

namespace frontend {
    functional::TestDetail test;
    std::vector<utils::button> buttons;
    std::vector<utils::text> texts;
    std::vector<utils::text_input> text_inputs;
    std::map<int,int> answers;

    enum UI_state{MAIN,TEST,STUDENT_LOGIN,TEACHER_LOGIN};
    UI_state state = MAIN;

    int question_number = 0;
    int answer = 0;
    sf::Vector2f answer_position({400,300});

    void button_highlight(){
        buttons[buttons.size()-(2-answer)-1].button_state = utils::ACTIVED;
    }


    void run_test(){
        answers.clear();
        question_number = 0;
        test = functional::fetchTestDetails(std::stoi(text_inputs[2].data.toAnsiString()));
        if(test.questions.empty()){
            return;
        }
        for(int i = 0;i<buttons.size();i++){
            buttons[i].button_state = utils::HIDEN;
        }
        buttons[0].button_state = utils::DISABLED;
        buttons[1].button_state = utils::ENABLED;
        for(int i = 0;i<texts.size();i++){
            texts[i].text_io_state = utils::HIDEN;
        }
        for(int i = 0;i<text_inputs.size();i++){
            text_inputs[i].text_io_state = utils::HIDEN;
        }
        buttons[6].button_state = utils::ENABLED;
        buttons[7].button_state = utils::HIDEN;
        state = TEST;

        for(int i = 0;i<test.questions[question_number].options.size();i++){
            buttons.push_back({utils::ACTIVED,[i](){ answer = i; },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{answer_position.x,answer_position.y +( 50.0f*i)},{650,50},test.questions[question_number].options[i]});
        }
        texts[4].text_io_state = utils::ACTIVED;
        texts[4].data[0] = sf::String(test.questions.at(question_number).text);
        state = TEST;
    }
    void next_question(){
        answers[test.questions[question_number].id] = answer;
        
        if(question_number < (test.questions.size()-1)){
            buttons.erase(buttons.end()-test.questions[question_number].options.size(),buttons.end());

            question_number++;
            texts[4].data[0] = sf::String(test.questions.at(question_number).text);
            buttons[6].button_state = utils::ENABLED;
            buttons[7].button_state = utils::HIDEN;
            for(int i = 0;i<test.questions[question_number].options.size();i++){
                buttons.push_back({utils::ACTIVED,[i](){ answer = i; },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{answer_position.x,answer_position.y +( 50.0f*i)},{650,50},test.questions[question_number].options[i]});
            }
        }else{
            buttons[6].button_state = utils::HIDEN;
            buttons[7].button_state = utils::ENABLED;
            texts[4].data[0] = sf::String(L"No questions found");
        }
        
    }
    void submit_and_send(){
        buttons.erase(buttons.end()-test.questions[question_number].options.size(),buttons.end());
        texts[4].data[0] = functional::submitTestResults(0, test.id, answers);
        for(int i = 0;i<buttons.size();i++){
            buttons[i].button_state = utils::ENABLED;
        }
        for(int i = 0;i<texts.size();i++){
            texts[i].text_io_state = utils::ACTIVED;
        }
        for(int i = 0;i<text_inputs.size();i++){
            texts[i].text_io_state = utils::ACTIVED;
        }
        buttons[1].button_state = utils::DISABLED;
        buttons[6].button_state = utils::HIDEN;
        buttons[7].button_state = utils::HIDEN;
        state = MAIN;
    }
    

    void init(sf::RenderWindow &window){
        utils::window = &window;
        utils::font_path = "../assets/Monocraft.ttf";
        utils::init_window();
        utils::load_font();

        buttons.push_back({utils::ENABLED,[](){ run_test(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,0},{150,50},L"Run ▶"});
        buttons.push_back({utils::DISABLED,[](){ submit_and_send(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,50},{250,50},L"Terminate ▶"});
        buttons.push_back({utils::HIDEN,[](){  },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,100},{250,50},L"LOG OUT ▶"});
        buttons.push_back({utils::DISABLED,[](){ if(!functional::loginStudentSFML(text_inputs[0].data,text_inputs[1].data)){texts[0].data[0] = sf::String("INVALID!");}else{texts[0].data[0] = sf::String("VALID");} },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,100},{250,50},L"LOG IN ▶"});
        buttons.push_back({utils::ENABLED,[](){ utils::window->close(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,900},{250,50},L"EXIT ▶"});
        buttons.push_back({utils::ENABLED,[](){ texts[3].data = functional::getTestsSFML(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,600},{250,50},L"GET TESTS ▶"});
        buttons.push_back({utils::HIDEN,[](){ next_question(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,800},{300,50},L"NEXT QUESTION▶"});
        buttons.push_back({utils::HIDEN,[](){ submit_and_send(); },{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,800},{300,50},L"Send test ▶"});
        
        


        texts.push_back({utils::HIDEN,{L"Привет!"},{100,100},{0.02,0.02},sf::Color(0,255,0)});
        texts.push_back({utils::ACTIVED,{L"State:"},{800,0},{0.02,0.02},sf::Color(0,255,0)});
        texts.push_back({utils::ACTIVED,{L"Logged out"},{900,0},{0.02,0.02},sf::Color(0,255,0)});
        texts.push_back({utils::ACTIVED,{L"Test"},{300,80},{0.02,0.02},sf::Color(0,255,255)});
        texts.push_back({utils::ACTIVED,{L"Test"},{300,0},{0.02,0.02},sf::Color(0,255,255)});

        text_inputs.push_back({utils::ACTIVED,[](sf::String string){}, L"Name",{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,150},{150,50}});
        text_inputs.push_back({utils::ACTIVED,[](sf::String string){}, L"Surname",{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,200},{150,50}});
        text_inputs.push_back({utils::ACTIVED,[](sf::String string){}, L"0",{sf::Color(255,250,0),sf::Color(0,0,230),sf::Color(0,255,0),sf::Color(255,0,0),sf::Color(0,188,255)},{0,250},{150,50}});
    }
    void event_listener(std::optional<sf::Event> &event){
        if (event->is<sf::Event::Closed>()){
            utils::window->close();
        }
        if(const auto *resized_window = event->getIf<sf::Event::Resized>()){
            utils::view.setSize({(float)resized_window->size.x,(float)resized_window->size.y});
            utils::view.setCenter({resized_window->size.x / 2.f, resized_window->size.y / 2.f});
            utils::window->setSize(resized_window->size);
            utils::resize_window();

        }
        if(const auto *mouse_click = event->getIf<sf::Event::MouseButtonPressed>()){
            if(mouse_click->button == sf::Mouse::Button::Left || mouse_click->button == sf::Mouse::Button::Right){
                
                
            }
        }

        if(const auto *keyboard_pressed = event->getIf<sf::Event::TextEntered>()){
            auto unicode = keyboard_pressed->unicode;

            if (unicode == U'\b' && utils::get_text(text_inputs) != NULL && !utils::get_text(text_inputs)->isEmpty()) {
                
                utils::get_text(text_inputs)->erase(utils::get_text(text_inputs)->getSize() - 1);
            } else if (unicode >= 32 && unicode != 0x7F) { 
                sf::String buffer;
                buffer += unicode;
                utils::enter_text(text_inputs, buffer);
            }
        }
         if (event->is<sf::Event::FocusLost>()) {
        // Вариант А: Нагло возвращаем окно на место
            utils::window->requestFocus(); 
        
        // Вариант Б (Для диплома еще круче): Сразу засчитываем попытку взлома/списывания!
        // Переключаем экран на "Тест аннулирован за списывание!" и блокируем базу.
        }


        sf::Vector2i offset_mouse = sf::Mouse::getPosition(*utils::window);
        utils::is_button_pressed(offset_mouse, buttons,event);
        utils::is_text_input_active(offset_mouse,text_inputs,event);
    }

    void draw(){
        utils::render_texture.clear(utils::background_color);
        /*USER CODE BEGIN */
        switch(state){
            case TEST:button_highlight();break;
            case STUDENT_LOGIN:break;
            case TEACHER_LOGIN:break;
            case MAIN:break;
        }
        utils::draw_button(buttons);
        utils::draw_text(texts);
        utils::draw_text_input(text_inputs);
        /*USER CODE END*/
        utils::update_window();

    }
}


