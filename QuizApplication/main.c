#include <stdio.h>
#include <stdlib.h> // For system function
#include <windows.h> // For Sleep function
#include <string.h>

#define MAX_QUIZZES 10
#define MAX_QUESTIONS 20
#define MAX_QUESTION_LENGTH 100
#define MAX_OPTIONS 4

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char options[MAX_OPTIONS][MAX_QUESTION_LENGTH];
    int correctOption;
} Question;

typedef struct {
    char title[MAX_QUESTION_LENGTH];
    Question questions[MAX_QUESTIONS];
    int numQuestions;
} Quiz;

Quiz quizzes[MAX_QUIZZES];
int numQuizzes = 0;

void clearBuffer() {
    while (getchar() != '\n');
}

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix-based systems
    #endif
}

void displayMenu() {
    Sleep(4000);
    clearScreen();
    printf("\nQuiz Application Menu\n");
    printf("1. Add Quiz\n");
    printf("2. Display Quizzes\n");
    printf("3. Take Quiz\n");
    printf("4. Exit\n");
}

void addQuiz() {
    printf("Enter quiz title: ");
    char title[MAX_QUESTION_LENGTH];
    scanf_s(" %[^\n]s", title, sizeof(title));

    if (numQuizzes >= MAX_QUIZZES) {
        printf("Maximum quiz limit reached. Cannot add more quizzes.\n");
        return;
    }

    strcpy_s(quizzes[numQuizzes].title, sizeof(quizzes[numQuizzes].title), title);
    quizzes[numQuizzes].numQuestions = 0;
    printf("Quiz added successfully.\n");

    int numQuestions;
    printf("Enter the number of questions you want to add: ");
    scanf_s("%d", &numQuestions);

    clearBuffer();

    if (numQuestions <= 0 || numQuestions > MAX_QUESTIONS) {
        printf("Invalid input. Please enter a positive number less than or equal to %d.\n", MAX_QUESTIONS);
        return;
    }

    for (int i = 0; i < numQuestions; i++) {
        printf("Enter question %d: ", i + 1);
        char question[MAX_QUESTION_LENGTH];
        scanf_s(" %[^\n]s", question, sizeof(question));

        clearBuffer();

        char options[MAX_OPTIONS][MAX_QUESTION_LENGTH];
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("Enter option %d: ", j + 1);
            scanf_s(" %[^\n]s", options[j], sizeof(options[j]));

            clearBuffer();
        }

        int correctOption;
        printf("Enter the index of the correct option: ");
        scanf_s("%d", &correctOption);

        clearBuffer();

        if (correctOption <= 0 || correctOption >= MAX_OPTIONS+1) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", MAX_OPTIONS);
            return;
        }

        strcpy_s(quizzes[numQuizzes].questions[i].question, sizeof(quizzes[numQuizzes].questions[i].question), question);
        for (int j = 0; j < MAX_OPTIONS; j++) {
            strcpy_s(quizzes[numQuizzes].questions[i].options[j], sizeof(quizzes[numQuizzes].questions[i].options[j]), options[j]);
        }
        quizzes[numQuizzes].questions[i].correctOption = correctOption-1;
        quizzes[numQuizzes].numQuestions++;
    }

    numQuizzes++;
}

void displayQuizzes() {
    printf("Available Quizzes:\n");
    for (int i = 0; i < numQuizzes; i++) {
        printf("%d. %s\n", i + 1, quizzes[i].title);
    }
}

void takeQuiz() {
    clearScreen();
    int quizIndex;
    printf("Enter the index of the quiz you want to take: ");
    scanf_s("%d", &quizIndex);

    clearBuffer();

    if (quizIndex < 1 || quizIndex > numQuizzes) {
        printf("Invalid input. Please enter a number between 1 and %d.\n", numQuizzes);
        return;
    }

    int score = 0;
    printf("Taking Quiz: %s\n", quizzes[quizIndex - 1].title);
    for (int i = 0; i < quizzes[quizIndex - 1].numQuestions; i++) {
        printf("Question %d: %s\n", i + 1, quizzes[quizIndex - 1].questions[i].question);
        printf("Options:\n");
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%d. %s\n", j + 1, quizzes[quizIndex - 1].questions[i].options[j]);
        }
        int answer;
        printf("Enter your answer for question %d: ", i + 1);
        scanf_s("%d", &answer);

        clearBuffer();

        if (answer < 1 || answer > MAX_OPTIONS) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", MAX_OPTIONS);
            i--;
            continue;
        }
        if (answer == quizzes[quizIndex - 1].questions[i].correctOption + 1) {
            printf("Correct!\n");
            score++;
        }
        else {
            printf("Incorrect!\n");
        }
    }
    printf("Quiz complete. Your score: %d/%d\n", score, quizzes[quizIndex - 1].numQuestions);
}

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        clearBuffer();

        switch (choice) {
        case 1:
            addQuiz();
            break;
        case 2:
            displayQuizzes();
            break;
        case 3:
            takeQuiz();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
