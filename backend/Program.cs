using System.Text.Json;
using System.Text.Json.Serialization;
using Microsoft.EntityFrameworkCore;
using DTO;
var builder = WebApplication.CreateBuilder(args);

// Подключаем SQLite
builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseSqlite("Data Source=app.db"));

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.PropertyNamingPolicy = JsonNamingPolicy.SnakeCaseLower;
});

var app = builder.Build();

// Авто-создание БД при старте
using (var scope = app.Services.CreateScope())
{
    var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    db.Database.EnsureCreated();

    // Добавим тестового учителя, если база пустая (AccessCode = "secret123")
    if (!db.Teachers.Any())
    {
        db.Teachers.Add(new Teacher { FullName = "Иванов И.И.", AccessCode = "secret123" });
        db.SaveChanges();
    }
}
app.MapPost("/api/student/login", async (StudentLoginReq req, AppDbContext db) =>
{
    var student = await db.Students.FirstOrDefaultAsync(s => s.StudentCardId == req.StudentCardId);
    if (student == null)
    {
        student = new Student { FullName = req.FullName, StudentCardId = req.StudentCardId };
        db.Students.Add(student);
        await db.SaveChangesAsync();
    }
    return Results.Ok(new { student.Id, student.FullName, student.StudentCardId });
});

// 2. Получить список всех доступных тестов (без вопросов)
app.MapGet("/api/tests", async (AppDbContext db) =>
{
    var tests = await db.Tests.Select(t => new { t.Id, t.Title }).ToListAsync();
    return Results.Ok(tests);
});

// 3. Студент получает тест для прохождения (БЕЗ ПРАВИЛЬНЫХ ОТВЕТОВ!)
app.MapGet("/api/tests/{id:int}", async (int id, AppDbContext db) =>
{
    var test = await db.Tests.FindAsync(id);
    if (test == null) return Results.NotFound(new { error = "Тест не найден" });

    // Десериализуем и удаляем правильные ответы перед отправкой
    var questions = JsonSerializer.Deserialize<List<Question>>(test.QuestionsJson) ?? new();
    var studentQuestions = questions.Select(q => new 
    {
        q.Id,
        q.Text,
        q.Options // Варианты ответов оставляем, а CorrectOptionIndex убираем!
    });

    return Results.Ok(new { test.Id, test.Title, questions = studentQuestions });
});


// --- ДЛЯ ПРЕПОДАВАТЕЛЕЙ (Полный доступ по AccessCode) ---

// 4. Проверка кода доступа учителя
app.MapPost("/api/teacher/verify", async (TeacherAuthReq req, AppDbContext db) =>
{
    var teacher = await db.Teachers.FirstOrDefaultAsync(t => t.AccessCode == req.AccessCode);
    if (teacher == null) return Results.Unauthorized();

    return Results.Ok(new { teacher.Id, teacher.FullName });
});

// 5. Создание или обновление теста учителем
app.MapPost("/api/teacher/tests", async (CreateTestReq req, AppDbContext db) =>
{
    // Проверяем авторизацию учителя
    var teacher = await db.Teachers.FirstOrDefaultAsync(t => t.AccessCode == req.AccessCode);
    if (teacher == null) return Results.Unauthorized();

    var jsonQuestions = JsonSerializer.Serialize(req.Questions);

    if (req.TestId.HasValue) // Редактирование существующего
    {
        var existingTest = await db.Tests.FindAsync(req.TestId.Value);
        if (existingTest == null) return Results.NotFound();
        
        existingTest.Title = req.Title;
        existingTest.QuestionsJson = jsonQuestions;
    }
    else // Создание нового
    {
        var newTest = new Test { Title = req.Title, QuestionsJson = jsonQuestions };
        db.Tests.Add(newTest);
    }

    await db.SaveChangesAsync();
    return Results.Ok(new { success = true, message = "Тест успешно сохранен" });
});


app.MapPost("/api/tests/{id:int}/submit", async (int id, SubmitTestReq req, AppDbContext db) =>
{
    var test = await db.Tests.FindAsync(id);
    if (test == null) return Results.NotFound(new { error = "Тест не найден" });

    // Десериализуем вопросы (теперь с правильными ответами!)
    var questions = JsonSerializer.Deserialize<List<Question>>(test.QuestionsJson) ?? new();
    
    int correctCount = 0;
    int totalQuestions = questions.Count;

    // Сверяем присланные ответы с правильными
    foreach (var studentAnswer in req.Answers)
    {
        var question = questions.FirstOrDefault(q => q.Id == studentAnswer.QuestionId);
        if (question != null)
        {
            // Если индекс выбранного ответа совпадает с CorrectOptionIndex
            if (question.CorrectOptionIndex == studentAnswer.SelectedOptionIndex)
            {
                correctCount++;
            }
        }
    }

    double percentage = totalQuestions > 0 ? (double)correctCount / totalQuestions * 100 : 0;

    return Results.Ok(new 
    {
        success = true,
        total = totalQuestions,
        correct = correctCount,
        score_percentage = Math.Round(percentage, 1)
    });
});




app.Run("http://localhost:5000");


// ==========================================
// МОДЕЛИ БАЗЫ ДАННЫХ И DTO
// ==========================================
app.MapPost("/api/student/login", async (StudentLoginReq req, AppDbContext db) =>
{
    var student = await db.Students.FirstOrDefaultAsync(s => s.StudentCardId == req.StudentCardId);
    if (student == null)
    {
        student = new Student { FullName = req.FullName, StudentCardId = req.StudentCardId };
        db.Students.Add(student);
        await db.SaveChangesAsync();
    }
    return Results.Ok(new { student.Id, student.FullName, student.StudentCardId });
});

app.MapGet("/api/tests", async (AppDbContext db) =>
{
    var tests = await db.Tests.Select(t => new { t.Id, t.Title }).ToListAsync();
    return Results.Ok(tests);
});

// 3. Студент получает тест для прохождения (БЕЗ ПРАВИЛЬНЫХ ОТВЕТОВ!)
app.MapGet("/api/tests/{id:int}", async (int id, AppDbContext db) =>
{
    var test = await db.Tests.FindAsync(id);
    if (test == null) return Results.NotFound(new { error = "Тест не найден" });

    // Десериализуем и удаляем правильные ответы перед отправкой
    var questions = JsonSerializer.Deserialize<List<Question>>(test.QuestionsJson) ?? new();
    var studentQuestions = questions.Select(q => new 
    {
        q.Id,
        q.Text,
        q.Options // Варианты ответов оставляем, а CorrectOptionIndex убираем!
    });

    return Results.Ok(new { test.Id, test.Title, questions = studentQuestions });
});


app.MapPost("/api/teacher/verify", async (TeacherAuthReq req, AppDbContext db) =>
{
    var teacher = await db.Teachers.FirstOrDefaultAsync(t => t.AccessCode == req.AccessCode);
    if (teacher == null) return Results.Unauthorized();

    return Results.Ok(new { teacher.Id, teacher.FullName });
});

// 5. Создание или обновление теста учителем
app.MapPost("/api/teacher/tests", async (CreateTestReq req, AppDbContext db) =>
{
    // Проверяем авторизацию учителя
    var teacher = await db.Teachers.FirstOrDefaultAsync(t => t.AccessCode == req.AccessCode);
    if (teacher == null) return Results.Unauthorized();

    var jsonQuestions = JsonSerializer.Serialize(req.Questions);

    if (req.TestId.HasValue) // Редактирование существующего
    {
        var existingTest = await db.Tests.FindAsync(req.TestId.Value);
        if (existingTest == null) return Results.NotFound();
        
        existingTest.Title = req.Title;
        existingTest.QuestionsJson = jsonQuestions;
    }
    else // Создание нового
    {
        var newTest = new Test { Title = req.Title, QuestionsJson = jsonQuestions };
        db.Tests.Add(newTest);
    }

    await db.SaveChangesAsync();
    return Results.Ok(new { success = true, message = "Тест успешно сохранен" });
});





// Модель вопроса внутри JSON
public class Question
{
    [JsonPropertyName("id")] public int Id { get; set; }
    [JsonPropertyName("text")] public string Text { get; set; } = "";
    [JsonPropertyName("options")] public List<string> Options { get; set; } = new();
    [JsonPropertyName("correct_option_index")] public int CorrectOptionIndex { get; set; }
}

// DTO Запросы
public record StudentLoginReq(
    [property: JsonPropertyName("full_name")] string FullName,
    [property: JsonPropertyName("student_card_id")] string StudentCardId
);

public record TeacherAuthReq([property: JsonPropertyName("access_code")] string AccessCode);

public record CreateTestReq(
    [property: JsonPropertyName("access_code")] string AccessCode,
    [property: JsonPropertyName("test_id")] int? TestId,
    [property: JsonPropertyName("title")] string Title,
    [property: JsonPropertyName("questions")] List<Question> Questions
);

// Дополнительные структуры (DTO) для приема ответов
public record StudentAnswer(
    [property: JsonPropertyName("question_id")] int QuestionId,
    [property: JsonPropertyName("selected_option_index")] int SelectedOptionIndex
);

public record SubmitTestReq(
    [property: JsonPropertyName("student_id")] int StudentId,
    [property: JsonPropertyName("answers")] List<StudentAnswer> Answers
);