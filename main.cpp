#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class Exercise
{
private:
    std::string name;
    std::string muscleGroup;

public:
    Exercise(std::string name, std::string muscleGroup)
        : name(name), muscleGroup(muscleGroup) {}

    std::string getMuscleGroup() const
    {
        return muscleGroup;
    }

    std::string toString() const
    {
        return name + " (Muscle Group: " + muscleGroup + ")";
    }
};

class Exercises
{
private:
    std::vector<Exercise> exercises;

public:
    void addExercise(const Exercise &exercise)
    {
        exercises.push_back(exercise);
    }

    void displayExercises()
    {
        for (Exercise exercise : exercises)
        {
            std::cout << exercise.toString() << std::endl;
        }
    }
};

// class Routine
// {
// private:
//     std::vector<std::vector<Exercise>> routines;

// public:
//     Routine(int days)
//     {
//         routines.resize(days);
//     }

//     void addExercise(int day, const Exercise &exercise)
//     {
//         if (day >= 0 && day < routines.size())
//         {
//             routines[day].push_back(exercise);
//         }
//         else
//         {
//             std::cout << "Invalid day selected!" << std::endl;
//         }
//     }

//     void displayRoutine() const
//     {
//         for (int i = 0; i < routines.size(); i++)
//         {
//             std::cout << "Day " << (i + 1) << ":" << std::endl;
//             for (const auto &exercise : routines[i])
//             {
//                 std::cout << exercise.toString() << std::endl;
//             }
//             std::cout << std::endl;
//         }
//     }

//     std::unordered_map<std::string, int> calculateSetsPerMuscleGroup() const
//     {
//         std::unordered_map<std::string, int> muscleGroupSets;
//         for (const auto &day : routines)
//         {
//             for (const auto &exercise : day)
//             {
//                 muscleGroupSets[exercise.getMuscleGroup()] += exercise.getSets();
//             }
//         }
//         return muscleGroupSets;
//     }
// };

int main()
{
    Exercises exercises;
    for (int i = 1; i <= 4; i++)
    {
        std::string name;
        std::cout << "Enter exercise name: ";// (or 'done' to finish for the day): ";
        std::getline(std::cin, name);
        // if (name == "done")
        // {
        //     break;
        // }

        // int sets, reps;
        // std::cout << "Enter number of sets: ";
        // std::cin >> sets;
        // std::cout << "Enter number of reps: ";
        // std::cin >> reps;
        // std::cin.ignore(); // Consume newline

        std::string muscleGroup;
        std::cout << "Enter muscle group: ";
        std::getline(std::cin, muscleGroup);

        Exercise exercise(name, muscleGroup);
        exercises.addExercise(exercise);
    }
    exercises.displayExercises();

    /* int days;
    std::cout << "Enter the number of days for your workout routine (1-6): ";
    bool daysNum = false;
    while (!daysNum) {
        try {
            std::cin >> days;
            if (days >= 1 && days <= 6) {
                daysNum = true;
            }
            else {
                throw 505;
            }

        }
        catch (...) {
            std::cout << "Please enter valid number" << std::endl;
        }
    }
    std::cin.ignore(); // Consume newline

    Routine routine(days);

    for (int i = 0; i < days; i++) {
        std::cout << "Enter exercises for day " << (i + 1) << ":" << std::endl;

        while (true) {
            std::string name;
            std::cout << "Enter exercise name (or 'done' to finish for the day): ";
            std::getline(std::cin, name);
            if (name == "done") {
                break;
            }

            int sets, reps;
            std::cout << "Enter number of sets: ";
            std::cin >> sets;
            std::cout << "Enter number of reps: ";
            std::cin >> reps;
            std::cin.ignore(); // Consume newline

            std::string muscleGroup;
            std::cout << "Enter muscle group: ";
            std::getline(std::cin, muscleGroup);

            Exercise exercise(name, sets, reps, muscleGroup);
            routine.addExercise(i, exercise);
        }
    }

    std::cout << "Your workout routine:" << std::endl;
    routine.displayRoutine();

    std::cout << "Total sets per muscle group per week:" << std::endl;
    auto setsPerMuscleGroup = routine.calculateSetsPerMuscleGroup();
    for (const auto& entry : setsPerMuscleGroup) {
        std::cout << entry.first << ": " << entry.second << " sets" << std::endl;
    }
    */
    return 0;
}
