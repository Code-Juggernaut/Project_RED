#include <SFML/Graphics.hpp>
//#include <SQLiteCpp/SQLiteCpp.h>
#include "libs/UI/generic.h"
#include "frontend/frontend.h"
//#include "functional/functional.h"
// #include <nlohmann/json.hpp>
/*
cmake -B build
cmake --build build



cmake -B build-win
cmake --build build-win

 */

int main(){
    sf::RenderWindow window(sf::VideoMode({1024,1024}),"CTL");
    frontend::init(window);
/*
    std::string teacherCode = "secret123"; // Тот самый код из базы (в реальности вводит в SFML-поле)
    std::string testTitle = "Основы C++ и ООП";

    // Создаем вопросы для теста
    std::vector<functional::TeacherQuestion> newQuestions = {
        {
            1, 
            "Что такое инкапсуляция?", 
            {"Скрытие данных", "Наследование методов", "Множественное наследование"}, 
            0 // Индекс правильного ответа (0 — "Скрытие данных")
        },
        {
            2, 
            "Какой ключевое слово используется для наследования в C++?", 
            {"extends", "implements", "публичное двоеточие ':'"}, 
            2 
        }
    };

    // Отправляем запрос на создание нового теста (testId = std::nullopt)
    functional::saveTestByTeacher(teacherCode, std::nullopt, testTitle, newQuestions);
*/
    /*if (loginStudentSFML("Сидоров А.А.", "CARD-777")) {
        getTestsSFML();
    }*/

    while(window.isOpen()){
        //texture.resize(window.getSize());
        while (std::optional<sf::Event> event = window.pollEvent()){
            frontend::event_listener(event);
        }
        sf::RectangleShape rect({100,100});
        rect.setFillColor(sf::Color::Green);
        rect.setPosition({0,0});
        window.clear(utils::background_color);
        window.draw(rect);
        frontend::draw();
        window.display();
    }
}