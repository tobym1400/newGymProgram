#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

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
        return name + " (Muscle Group: " + muscleGroup + ") ";
    }

    std::string toFileString() const
    {
        return name + "," + muscleGroup;
    }
};

class Exercises
{
private:
    std::vector<Exercise> exercises;

public:
    Exercises()
    {
        std::ifstream exercisesFile;
        std::string name;
        std::string muscleGroup;
        exercisesFile.open("exercises.txt");
        while (getline(exercisesFile, name, ','))
        {
            getline(exercisesFile, muscleGroup);
            Exercise exercise(name, muscleGroup);
            exercises.push_back(exercise);
        }
        exercisesFile.close();
    }

    void addExercise(const Exercise &exercise)
    {
        exercises.push_back(exercise);

        std::ofstream exercisesFile;
        exercisesFile.open("exercises.txt", std::ofstream::app);
        exercisesFile << exercise.toFileString() << std::endl;
        exercisesFile.close();
    }

    void displayExercises()
    {
        int i = 1;
        for (Exercise exercise : exercises)
        {
            std::cout << i << ": " << exercise.toString() << std::endl;
            i++;
        }
    }

    Exercise getExercise(int i)
    {
        return exercises[i - 1];
    }
};

class ExerciseEntry
{
private:
    Exercise exercise;
    int reps;
    int sets;

public:
    ExerciseEntry(const Exercise &exercise, int reps, int sets) : exercise(exercise), sets(sets), reps(reps) {}

    std::string toString() const
    {
        return exercise.toString() + std::to_string(sets) + " x " + std::to_string(reps);
    }

    std::string getMuscleGroup() const
    {
        return exercise.getMuscleGroup();
    }

    int getSets()
    {
        return sets;
    }

    int getReps()
    {
        return reps;
    }
};

class Routine
{
private:
    std::vector<std::vector<ExerciseEntry>> routines;

public:
    Routine(int days)
    {
        routines.resize(days);
    }

    void addExercise(int day, const ExerciseEntry &exerciseEntry)
    {
        if (day >= 0 && day < routines.size())
        {
            routines[day].push_back(exerciseEntry);
        }
        else
        {
            std::cout << "Invalid day selected!" << std::endl;
        }
    }

    void displayRoutine() const
    {
        for (int i = 0; i < routines.size(); i++)
        {
            std::cout << "Day " << (i + 1) << ":" << std::endl;
            for (const auto &exerciseEntry : routines[i])
            {
                std::cout << exerciseEntry.toString() << std::endl;
            }
            std::cout << std::endl;
        }
    }

    std::unordered_map<std::string, int> calculateSetsPerMuscleGroup() const
    {
        std::unordered_map<std::string, int> muscleGroupSets;
        for (const auto &day : routines)
        {
            for (ExerciseEntry exerciseEntry : day)
            {
                muscleGroupSets[exerciseEntry.getMuscleGroup()] += exerciseEntry.getSets();
            }
        }
        return muscleGroupSets;
    }
};

int addExercises(Exercises& exercises)
{
    while (true) {
        std::string name;
        std::cout << "Enter exercise name: (or 'done' to finish for the day):" << std::endl;
        std::getline(std::cin, name);
        if (name == "done")
        {
            return 0;
        }
        std::string muscleGroup;
        std::cout << "Enter muscle group:" << std::endl;
        std::getline(std::cin, muscleGroup);

        Exercise exercise(name, muscleGroup);
        exercises.addExercise(exercise);
    }

}

int createRoutine(Exercises& exercises)
{
    int days;
    std::cout << "Enter the number of days for your workout routine (1-6): ";
    bool daysNum = false;
    while (!daysNum)
    {
        try
        {
            std::cin >> days;
            if (days >= 1 && days <= 6)
            {
                daysNum = true;
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            std::cout << "Please enter valid number" << std::endl;
        }
    }
    std::cin.ignore(); // Consume newline

    Routine routine(days);

    for (int i = 0; i < days; i++)
    {
        std::cout << "Select exercises for day " << (i + 1) << ":" << std::endl;

        while (true)
        {
            int exerciseIndex;
            std::cout << "Enter exercise index (or '0' to finish for the day): " << std::endl;
            exercises.displayExercises();
            std::cin >> exerciseIndex;
            if (0 == exerciseIndex)
            {
                break;
            }

            int sets, reps;
            std::cout << "Enter number of sets: ";
            std::cin >> sets;
            std::cout << "Enter number of reps: ";
            std::cin >> reps;
            std::cin.ignore(); // Consume newline

            Exercise exercise = exercises.getExercise(exerciseIndex);
            ExerciseEntry exerciseEntry(exercise, sets, reps);
            routine.addExercise(i, exerciseEntry);
        }
    }

    std::cout << "Your workout routine:" << std::endl;
    routine.displayRoutine();

    std::cout << "Total sets per muscle group per week:" << std::endl;
    auto setsPerMuscleGroup = routine.calculateSetsPerMuscleGroup();
    for (const auto &entry : setsPerMuscleGroup)
    {
        std::cout << entry.first << ": " << entry.second << " sets" << std::endl;
    }
    return 0;
}

int main()
{
    Exercises exercises;

    int option;

    while (true)
    {
        std::cout << "Please select option:" << std::endl;
        std::cout << "0 - Quit" << std::endl;
        std::cout << "1 - List Exercises" << std::endl;
        std::cout << "2 - Add Exercises" << std::endl;
        std::cout << "3 - Create Routine:" << std::endl;

        std::cin >> option;
        std::cin.ignore();

        switch (option)
        {
        case 0:
            return 0;
        case 1:
            exercises.displayExercises();
            break;
        case 2:
            addExercises(exercises);
            break;
        case 3:
            createRoutine(exercises);
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            break;
        }
    }
    return 0;
}
