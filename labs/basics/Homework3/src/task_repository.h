#pragma once
#include <vector>
#include <QString>
#include <QStringList>

enum class Difficulty { Easy, Medium, Hard };
enum class TaskType { Translation, Grammar };

struct TaskData {
    Difficulty diff;
    TaskType type;
    QString question;
    QString answer;
    QStringList options;
};

class TaskRepository {
public:
    static std::vector<TaskData> getAllTasks() {
        return {
            // EASY (A1-A2)
            {Difficulty::Easy, TaskType::Translation, "Sun", "Солнце"},
            {Difficulty::Easy, TaskType::Translation, "Dog", "Собака"},
            {Difficulty::Easy, TaskType::Translation, "Green", "Зеленый"},
            {Difficulty::Easy, TaskType::Translation, "Milk", "Молоко"},
            {Difficulty::Easy, TaskType::Translation, "School", "Школа"},
            {Difficulty::Easy, TaskType::Translation, "Friend", "Друг"},
            {Difficulty::Easy, TaskType::Translation, "Family", "Семья"},
            {Difficulty::Easy, TaskType::Translation, "Winter", "Зима"},
            {Difficulty::Easy, TaskType::Grammar, "I ___ happy.", "0", {"am", "is", "are"}},
            {Difficulty::Easy, TaskType::Grammar, "She ___ a cat.", "1", {"have", "has", "having"}},
            {Difficulty::Easy, TaskType::Grammar, "Look at ___!", "2", {"they", "their", "them"}},

            // MEDIUM (B1-B2)
            {Difficulty::Medium, TaskType::Translation, "Knowledge", "Знания"},
            {Difficulty::Medium, TaskType::Translation, "Experience", "Опыт"},
            {Difficulty::Medium, TaskType::Translation, "Beautiful", "Красивый"},
            {Difficulty::Medium, TaskType::Translation, "Decision", "Решение"},
            {Difficulty::Medium, TaskType::Translation, "Together", "Вместе"},
            {Difficulty::Medium, TaskType::Translation, "Mountain", "Гора"},
            {Difficulty::Medium, TaskType::Translation, "Science", "Наука"},
            {Difficulty::Medium, TaskType::Translation, "Journey", "Путешествие"},
            {Difficulty::Medium, TaskType::Grammar, "We ___ to the cinema last night.", "2", {"go", "goes", "went"}},
            {Difficulty::Medium, TaskType::Grammar, "If it rains, we ___ stay home.", "1", {"would", "will", "are"}},
            {Difficulty::Medium, TaskType::Grammar, "He is ___ than me.", "0", {"taller", "tall", "tallest"}},

            // HARD (C1)
            {Difficulty::Hard, TaskType::Translation, "Consequence", "Последствие"},
            {Difficulty::Hard, TaskType::Translation, "Ambiguous", "Двусмысленный"},
            {Difficulty::Hard, TaskType::Translation, "Sustainability", "Устойчивость"},
            {Difficulty::Hard, TaskType::Translation, "Prejudice", "Предрассудок"},
            {Difficulty::Hard, TaskType::Translation, "Sophisticated", "Сложный"},
            {Difficulty::Hard, TaskType::Translation, "Inevitable", "Неизбежный"},
            {Difficulty::Hard, TaskType::Grammar, "By 2025, I ___ my project.", "2", {"finish", "finished", "will have finished"}},
            {Difficulty::Hard, TaskType::Grammar, "Stop ___ so much noise!", "1", {"to make", "making", "make"}},
            {Difficulty::Hard, TaskType::Grammar, "I wish I ___ harder at school.", "0", {"had studied", "study", "will study"}}
        };
    }
};
