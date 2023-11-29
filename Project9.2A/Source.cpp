#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define SEARCH

const int MAX_NAME_LENGTH = 20; 

// Перерахування для представлення спеціальностей
enum Specialty {
    MATH_ECONOMICS,
    PHYSICS_CS,
    COMPUTER_SCIENCE
};

// Структура, що представляє інформацію про студента
struct Student {
    int studentNumber;
    char lastName[MAX_NAME_LENGTH];
    int course;
    Specialty specialty;
    double physics;
    double math;
    double it;
};

// Функція для перетворення зчислення Specialty в рядок
const char* specialtiesToString(Specialty specialty) {
    switch (specialty) {
    case MATH_ECONOMICS:
        return "Mathematics and economics";
    case PHYSICS_CS:
        return "Physics and computer science";
    case COMPUTER_SCIENCE:
        return "Computer science";
    default:
        return "Unknown Specialty";
    }
}

// Функція порівняння для qsort на основі курсу
int compareStudentsByCourse(const void* a, const void* b) {
    const Student* studentA = static_cast<const Student*>(a);
    const Student* studentB = static_cast<const Student*>(b);

    // Порівняйте за курсом
    return studentA->course - studentB->course;
}

// Функція порівняння для qsort на основі спеціальності
int compareStudentsBySpecialty(const void* a, const void* b) {
    const Student* studentA = static_cast<const Student*>(a);
    const Student* studentB = static_cast<const Student*>(b);

    // Порівняти за спеціальністю
    return studentA->specialty - studentB->specialty;
}

// Функція порівняння для qsort на основі прізвища в порядку спадання
int compareStudentsByLastName(const void* a, const void* b) {
    const Student* studentA = static_cast<const Student*>(a);
    const Student* studentB = static_cast<const Student*>(b);

    // Порівняти за прізвищем у порядку спадання
    return -strcmp(studentA->lastName, studentB->lastName);
}

// Функція для введення даних про студента
void inputStudents(Student* students, int numberOfStudents) {
    // Перерахувати значення для спеціальностей
    const Specialty specialties[] = { MATH_ECONOMICS, PHYSICS_CS, COMPUTER_SCIENCE };

    // Прізвища
    const char* lastNames[] = { "Vovk", "Mazurok", "Ushakov", "Kojushko", "Zarubich", "Simonenko", "Barchuk", "Osadchyi", "Kalyna" };

    for (int i = 0; i < numberOfStudents; ++i) {
        // Скопіювати прізвище
        strncpy(students[i].lastName, lastNames[i % (sizeof(lastNames) / sizeof(lastNames[0]))], MAX_NAME_LENGTH - 1);
        students[i].lastName[MAX_NAME_LENGTH - 1] = '\0';

        // Встановити спеціальність з допомогою enum
        students[i].specialty = specialties[i % (sizeof(specialties) / sizeof(specialties[0]))];

        // Згенерувати випадковий курс (від 1 до 5)
        students[i].course = rand() % 5 + 1;

        // Згенерувати випадкові оцінки (від 3 до 5)
        students[i].physics = rand() % 3 + 3;
        students[i].math = rand() % 3 + 3;
        students[i].it = rand() % 3 + 3;

        students[i].studentNumber = i + 1;
    }
}

// Функція для виведення таблиці студентів та обчислення кількості та відсотку студентів
void displayTable(const Student* students, int numberOfStudents) {
    int countWithoutThrees = 0;
    int countBelowFour = 0;

    // Відображення заголовка
    std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << "| No |  Surname   |Course|            Speciality          |  P |  M | I  |" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    // Відобразити дані про студентів та виконати обчислення
    for (int i = 0; i < numberOfStudents; ++i) {
        std::cout << "| " << std::setw(2) << students[i].studentNumber << " | " << std::setw(10) << students[i].lastName << " | "
            << std::setw(4) << students[i].course << " | " << std::setw(30) << specialtiesToString(students[i].specialty) << " | "
            << std::setw(2) << students[i].physics << " | " << std::setw(2) << students[i].math << " | "
            << std::setw(2) << students[i].it << " |" << std::endl;

        // Обчислення
        if (students[i].physics >= 4 && students[i].math >= 4 && students[i].it >= 4) {
            countWithoutThrees++;
        }

        double averageGrade = (students[i].physics + students[i].math + students[i].it) / 3.0;
        if (averageGrade < 4.0) {
            countBelowFour++;
        }
    }

    std::cout << "--------------------------------------------------------------------------" << std::endl;

    // Вивести результати обчислень
    std::cout << "1. Number of students without threes: " << countWithoutThrees << std::endl;
    std::cout << "2. Percentage of students with an average grade below 4: " << std::fixed << std::setprecision(2)
        << (static_cast<double>(countBelowFour) / numberOfStudents) * 100 << "%" << std::endl;
}
// Функція бінарного пошуку для пошуку студента із заданим прізвищем, курсом та спеціальністю
int binarySearch(const Student* students, int numberOfStudents, const char* lastName, int course, Specialty specialty) {
    for (int i = 0; i < numberOfStudents; ++i) {
        const Student& student = students[i];

        if (strcmp(student.lastName, lastName) == 0 && student.course == course && student.specialty == specialty) {
            // Студента знайдено
            return i;
        }
    }

    // Студента не знайдено
    return -1;
}




int main() {
    // Ініціалізувати генератор випадкових чисел
    std::srand(static_cast<unsigned>(std::time(0)));

    int numberOfStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numberOfStudents;

    // Створити динамічний масив студентів
    Student* students = new Student[numberOfStudents];

    // Ввести дані про студента
    inputStudents(students, numberOfStudents);
#ifdef SEARCH
    // Вивести невідсортовану таблицю та обчислення
    std::cout << "Unsorted Table:" << std::endl;
    displayTable(students, numberOfStudents);

    qsort(students, numberOfStudents, sizeof(Student), compareStudentsByLastName);

    // Критерії пошуку вхідних даних
    char searchLastName[MAX_NAME_LENGTH];
    int searchCourse;
    int searchSpecialty;

    std::cout << "\nEnter last name to search: ";
    std::cin >> searchLastName;
    std::cout << "Enter course to search: ";
    std::cin >> searchCourse;
    std::cout << "Enter specialty to search (0 for MATH_ECONOMICS, 1 for PHYSICS_CS, 2 for COMPUTER_SCIENCE): ";
    std::cin >> searchSpecialty;

    // Перетворити searchSpecialty у значення переліку
    Specialty searchEnumSpecialty = static_cast<Specialty>(searchSpecialty);

    // Виконати бінарний пошук
    int foundIndex = binarySearch(students, numberOfStudents, searchLastName, searchCourse, searchEnumSpecialty);

    if (foundIndex != -1) {
        std::cout << "Student found" << std::endl;
        std::cout << "Details of the found student:" << std::endl;
        std::cout << "Last name: " << students[foundIndex].lastName << std::endl;
        std::cout << "Course: " << students[foundIndex].course << std::endl;
        std::cout << "Specialty: " << specialtiesToString(students[foundIndex].specialty) << std::endl;
    }
    else {
        std::cout << "Student not found." << std::endl;
    }

    return foundIndex;
}
#endif

#ifdef SORT
char continueSorting;
do {

    // Вивести невідсортовану таблицю та обчислення
    std::cout << "Unsorted Table:" << std::endl;
    displayTable(students, numberOfStudents);
    std::cout << "\nDo you want to continue with the next sorting step? (y/n): ";
    std::cin >> continueSorting;
    if (continueSorting != 'y') {
        break;
    }
    // Сортування за курсом
    qsort(students, numberOfStudents, sizeof(Student), compareStudentsByCourse);
    std::cout << "\nSorted by Course:" << std::endl;
    displayTable(students, numberOfStudents);

    std::cout << "\nDo you want to continue with the next sorting step? (y/n): ";
    std::cin >> continueSorting;
    if (continueSorting != 'y') {
        break;
    }

    // Сортування за спеціальністю
    qsort(students, numberOfStudents, sizeof(Student), compareStudentsBySpecialty);
    std::cout << "\nSorted by Specialty:" << std::endl;
    displayTable(students, numberOfStudents);

    std::cout << "\nDo you want to continue with the next sorting step? (y/n): ";
    std::cin >> continueSorting;
    if (continueSorting != 'y') {
        break;
    }

    // Сортування за прізвищем у порядку спадання
    qsort(students, numberOfStudents, sizeof(Student), compareStudentsByLastName);
    std::cout << "\nSorted by Last Name in Descending Order:" << std::endl;
    displayTable(students, numberOfStudents);

    std::cout << "\nDo you want to continue with the next sorting step? (y/n): ";
    std::cin >> continueSorting;
} while (continueSorting == 'y');
// Вільна пам'ять
delete[] students;

return 0;
}
#endif

