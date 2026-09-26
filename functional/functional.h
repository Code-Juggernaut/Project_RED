#include <SFML/Network.hpp>
#include <nlohmann/json.hpp> // Только для комфортного парсинга JSON
#include <vector>
#include <string>
#pragma once
using json = nlohmann::json;
namespace functional{
    enum backend_state{LOGGED_IN,LOGGED_OUT,RUNNING_TEST};

    typedef struct{
        int id;
        std::wstring text;
        std::vector<std::wstring> options;
    }Question;

    typedef struct{
        int id;
        std::wstring title;
        std::vector<Question> questions;
    }TestDetail;

    typedef struct{
    int id;
    std::wstring text;
    std::vector<std::wstring> options;
    int correctOptionIndex;
    }TeacherQuestion;
    
    
    bool loginStudentSFML(const sf::String &fullName, const sf::String& studentCardId);
    std::vector<sf::String> getTestsSFML();
    TestDetail fetchTestDetails(int testId);
    sf::String submitTestResults(int studentId, int testId, const std::map<int, int>& userAnswers);
    bool saveTestByTeacher(const std::wstring& accessCode, std::optional<int> testId, const std::wstring& title, const std::vector<TeacherQuestion>& questions);


}