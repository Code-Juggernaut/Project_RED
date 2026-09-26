#include "functional.h"
#include <iostream>
using json = nlohmann::json;

namespace functional{


// 1. Функция входа студента через sf::Http
bool loginStudentSFML(const sf::String &fullName, const sf::String& studentCardId) {
    // Настраиваем хост и порт бэкенда
    sf::Http http;
    http.setHost("localhost", 5000);

    // Создаем POST запрос к /api/student/login
    sf::Http::Request request("/api/student/login", sf::Http::Request::Method::Post);
    
    // Задаем заголовки
    request.setField("Content-Type", "application/json");

    // Формируем JSON тело запроса
    json bodyData = {
        {"full_name", fullName},
        {"student_card_id", studentCardId}
    };
    request.setBody(bodyData.dump());

    // Отправляем запрос и "ловим" ответ!
    sf::Http::Response response = http.sendRequest(request);

    // Проверяем HTTP статус
    if (response.getStatus() == sf::Http::Response::Status::Ok) {
        //std::cout << "[SFML Network] Успех! Ответ бэкенда:\n" << response.getBody() << std::endl;
        return true;
    } else {
        //std::cout << "[SFML Network Error] Ошибка кода: " << static_cast<int>(response.getStatus()) << std::endl;
        return false;
    }
}

// 2. Функция получения тестов через sf::Http
std::vector<sf::String> getTestsSFML() {
    sf::Http http("localhost", 5000);

    // Создаем GET запрос к /api/tests
    sf::Http::Request request("/api/tests", sf::Http::Request::Method::Get);

    sf::Http::Response response = http.sendRequest(request);

    std::wstring string;
    std::vector<sf::String> data;

    if (response.getStatus() == sf::Http::Response::Status::Ok) {
        // Парсим тело ответа
        json testsJson = json::parse(response.getBody());
        
        //std::cout << "\n--- Список тестов из C# бэкенда ---" << std::endl;
        for (const auto& test : testsJson) {
            //std::cout << "ID: " << test["id"] << " | Название: " << test["title"] << std::endl;
            string += L"ID";
            string += std::to_wstring(test["id"].get<int>());
            string += L" title:";
            std::string temp = test["title"];
            sf::String sfTitle = sf::String::fromUtf8(temp.begin(), temp.end());
            string += sfTitle.toWideString();
            
            data.push_back(sf::String(string));
            string.clear();
        }
    }
    return data;
}


// Структура для загруженного теста

// 1. Получить тест по ID (без правильных ответов!)
TestDetail fetchTestDetails(int testId) {
    TestDetail testDetail;
    sf::Http http("127.0.0.1", 5000);

    sf::Http::Request request("/api/tests/" + std::to_string(testId), sf::Http::Request::Method::Get);
    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Status::Ok) {
        //std::cout<<response.getBody();
        json j = json::parse(response.getBody());
        testDetail.id = j["id"];
        std::string temp = j["title"];
        sf::String title = sf::String::fromUtf8(temp.begin(),temp.end());
        
        testDetail.title = title.toWideString();

        for (const auto& q : j["questions"]) {
            Question question;
            question.id = q["id"];
            temp = q["text"];
            sf::String text = sf::String::fromUtf8(temp.begin(),temp.end());
            question.text = text.toWideString();
            
                for (const auto& opt : q["options"]) {
                    std::string question_option = opt;
                    sf::String option = sf::String::fromUtf8(question_option.begin(), question_option.end());

                    question.options.push_back(option.toWideString());
                }
            
            testDetail.questions.push_back(question);
        }
    }
    return testDetail;
}

// 2. Отправить ответы студента на бэкенд
sf::String submitTestResults(int studentId, int testId, const std::map<int, int>& userAnswers) {
    sf::Http http("127.0.0.1", 5000);
    sf::Http::Request request("/api/tests/" + std::to_string(testId) + "/submit", sf::Http::Request::Method::Post);
    request.setField("Content-Type", "application/json");

    // Формируем JSON с ответами
    json answersArray = json::array();
    for (const auto& [qId, optIdx] : userAnswers) {
        answersArray.push_back({
            {"question_id", qId},
            {"selected_option_index", optIdx}
        });
    }

    json body = {
        {"student_id", studentId},
        {"answers", answersArray}
    };

    request.setBody(body.dump());
    sf::Http::Response response = http.sendRequest(request);
    std::wstring string;
    if (response.getStatus() == sf::Http::Response::Status::Ok) {
        json result = json::parse(response.getBody());
        string += L"Right answers: ";
        string += std::to_wstring(result["correct"].get<int>());
        string += L"/";
        string += std::to_wstring(result["total"].get<int>());
        //std::cout << "Процент успеха: " << result["score_percentage"] << "%" << std::endl;
    } else {
        //std::cout << "[Error] Не удалось отправить результаты теста." << std::endl;
        string += L"error 404 not found";
    }
    return sf::String(string);
}




// Функция создания или редактирования теста
bool saveTestByTeacher(const std::string& accessCode, std::optional<int> testId, const std::string& title, const std::vector<TeacherQuestion>& questions) {
    sf::Http http("127.0.0.1", 5000);

    // Эндпоинт один и тот же для создания и редактирования
    sf::Http::Request request("/api/teacher/tests", sf::Http::Request::Method::Post);
    request.setField("Content-Type", "application/json");

    // Формируем JSON-массив вопросов со всеми полями (включая правильные ответы)
    json questionsArray = json::array();
    for (const auto& q : questions) {
        questionsArray.push_back({
            {"id", q.id},
            {"text", q.text},
            {"options", q.options},
            {"correct_option_index", q.correctOptionIndex}
        });
    }

    // Собираем общий запрос
    json body = {
        {"access_code", accessCode},
        {"title", title},
        {"questions", questionsArray}
    };

    // Если это редактирование, добавляем test_id, иначе передаем null/пускай бэкенд поймет
    if (testId.has_value()) {
        body["test_id"] = testId.value();
    } else {
        body["test_id"] = nullptr;
    }

    request.setBody(body.dump());
    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Status::Ok) {
        //std::cout << "[Teacher Panel] Тест успешно сохранен в базе данных!" << std::endl;
        return true;
    } else {
        //std::cout << "[Teacher Error] Ошибка сохранения (возможно, неверный код доступа): " 
        //          << static_cast<int>(response.getStatus()) << std::endl;
        return false;
    }
}

/***std::string teacherCode = "secret123"; // Тот самый код из базы (в реальности вводит в SFML-поле)
    std::string testTitle = "Основы C++ и ООП";

    // Создаем вопросы для теста
    std::vector<TeacherQuestion> newQuestions = {
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
    saveTestByTeacher(teacherCode, std::nullopt, testTitle, newQuestions);

    // Пример редактирования существующего теста с ID = 1:
    // saveTestByTeacher(teacherCode, 1, "Основы C++ (Обновленный)", newQuestions); */
}