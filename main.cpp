/*
StudyBuddy
Developed by Code Buddy
Frances Jennifer Piccio
Jhouvann Morden
Laurence Lesmoras

For CS101 Final Assessment
*/

#include "include/rang.hpp" // Header for colors
#include <iostream>
#include <string>
#include "include/tsl/ordered_map.h" // Header for ordered map
#include <cstdlib>
#include <array>
#include <random>
#include <iterator>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string appName = "Study Buddy"; // App Name

void cpsleep(int time) { // Cross platform sleep function
#ifdef _WIN32
    Sleep(time * 1000);
#else
    // Assume UNIX/LINUX
    sleep(time);
#endif
}

void clear() { // Cross platform clear screen function
#ifdef _WIN32
    std::system("cls");
#else
    // Assume UNIX/LINUX
    std::system("clear");
#endif
}

class User { // User object
private:
    std::string username;

public:
    User(std::string name) { // Constructor
        username = name;
    }

    std::string getUsername() {
        return username;
    }

    void setUsername(std::string name) {
        username = name;
    }
};

User loggedInUser = User("None"); // Initializes the User instance

class App { // Main App Class
private:
    std::string taskName;
    int taskDuration;
    tsl::ordered_map<std::string, int> todo;

public:

    void clearList(){
        todo.clear();
    }

    void header() { // Header Function
        clear();
        std::cout << "=========================================================================" << std::endl;
        std::cout << rang::fg::cyan << rang::style::bold << appName << rang::fg::reset << rang::style::reset << std::endl;
        std::cout << "=========================================================================" << std::endl;
    }

    void registerScreen() { // Register Screen Function
        header();
        std::string username;
        std::cout << "Hey friend! Register with your nickname to continue!\nNickname: ";
        std::getline(std::cin, username);
        loggedInUser.setUsername(username);
    }

    void appMenu() { // App Menu Screen Function
        int currentTask = 1;
        while (true) {
            header();
            std::cout << "Welcome to " << appName << ", " << rang::style::bold << rang::fg::green << loggedInUser.getUsername() << rang::style::reset << rang::fg::reset << "!" << std::endl;
            std::cout << "Input the tasks you want to work on for this session" << std::endl;
            std::cout << "Don't forget to type 'done' in the task name to proceed!" << std::endl;
            std::cout << "=========================================================================" << std::endl;
            std::cout << "Current Task List: \n" << std::endl;
            int count = 0;
            for (const auto &p : todo) {
                count = count + 1;
                std::cout << "[" << count << "] " << p.first << "   -   " << p.second << " minutes" << std::endl;
            }
            std::cout << "\n[" << currentTask << "] " << "Task name: ";
            std::getline(std::cin, taskName); // We use getline to take input with spaces.
            if (taskName == "done") {
                break;
            } else { // This will loop until the user types 'done'
                std::cout << "[" << count + 1 << "] " << "How long should this task take? (in minutes): ";
               while (true) {
                    try {
                        std::string input;
                        std::cin >> input;
                        taskDuration = std::stoi(input); 
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw std::runtime_error("");
                        }

                        std::cin.ignore(); // Clear the newline character from the input buffer
                        if (taskDuration <= 0) {
                            throw std::runtime_error("");
                        }
                        // If everything is valid, add the task to the todo list
                        todo[taskName] = taskDuration;
                        currentTask = currentTask + 1;
                        break; 

                    } catch (const std::exception& e) {
                        std::cerr << "Invalid Input. Please enter proper duration in minutes. (Number only) " << std::endl;
                        std::cout << "[" << count + 1 << "] " << "How long should this task take? (in minutes): ";
                    }
                }
            }
        }
    }

    void appCountdownScreen() { // App Countdown Screen Function
        header();
        std::string pause;
        int count = 0;
        std::cout << "Yay! All tasks are now in queue! Type 'go' and press enter to start the fun!\n" << std::endl;
        for (const auto &p : todo) {
            count = count + 1;
            std::cout << "[" << count << "] " << p.first << "   -   " << p.second << " minutes" << std::endl;
        }
        std::cout << "=========================================================================" << std::endl;
        std::cin >> pause;

        // When the user presses enter, the queue will start
        int loopcount = 0;
        for (const auto &p : todo) {
            loopcount = loopcount + 1;
            int currentTaskDuration = p.second * 60;
            while (true) {
                header();
                std::cout << "[" << loopcount << "] " << p.first << "   -   " << currentTaskDuration << " seconds \n";
                cpsleep(1);
                currentTaskDuration = currentTaskDuration - 1;
                if (currentTaskDuration == 0) {

                    std::string messages[4] {
                    "Hey, vibe check! here's a star for completing your to-do's!\n" ,
                    "You're a star! don't forget to take breaks in between tasks!\n" ,
                    "Hooray! here's a little treat for a job well done!\n",
                    "Let's go, friend! a productive day is a wonderful day!\n"
                    };

                    int ranIndex = rand() % 4;
                
                    std:: cout << messages[ranIndex];

                    Sleep(5000);  // time_period in seconds

                    break;
                }
            }
        }
        
    };
};

App AppInstance; // Initializes the App class

int main() {
    AppInstance.registerScreen();
    AppInstance.appMenu();
    AppInstance.appCountdownScreen();

    std::string moreTasks;
    bool validInput = false;

    while (!validInput) {
        try {
            std::cout << "All tasks are completed. Do you want to add more tasks? [yes/no]: ";
            std::cin >> moreTasks;
            std::cin.ignore(); 

            if (moreTasks == "yes") {
                AppInstance.clearList();
                AppInstance.appMenu();
                AppInstance.appCountdownScreen();
            } else if (moreTasks == "no") {
                AppInstance.header();
                std::cout << "Thank you for using " << appName << ", Goodbye!" << std::endl;
                validInput = true; 
                cpsleep(3);
                exit(0);
            } else {
                throw std::runtime_error("Invalid input. Please enter 'yes' or 'no'.");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
