#include "include/rang.hpp"
#include <iostream>
#include <string>
#include <map>
#include "include/tsl/ordered_map.h" // For ordered list
#include <cstdlib>



std::string appName = "Study Buddy"; // App Name

void clear()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

class User { // User object
private:
    std::string username;
public:
    User(std::string name) { // Constructor
        username = name;
    };
    std::string getUsername() {
        return username;
    }
    void setUsername(std::string name){
        username = name;

    };
};
User loggedInUser = User("None");

class App { // Main App Class
public:
    void header() {
    clear();
    std::cout << "=========================================================================" << std::endl;
    std::cout << rang::fg::cyan << appName << rang::fg::gray << std::endl;
    std::cout << "=========================================================================" << std::endl;
    };

    void registerScreen() {
        header();
        std::string pause;
        std::string username;
        std::cout << "Howdy there! Register with your name or nickname to continue!\nNickname: ";
        std::getline(std::cin, username);
        loggedInUser.setUsername(username);
    }

    void appMenu() {
        int currentTask = 1;
        std::string taskName;
        int taskDuration;
        tsl::ordered_map<std::string, int> todo;
        while(true){
            header();
            std::cout << "Welcome to " << appName << ", " << loggedInUser.getUsername() << "!" << std::endl;
            std::cout << "Enter the tasks you want to do for this session" << std::endl;
            std::cout << "Don't forget to type 'done' in the task name to proceed!" << std::endl;
            std::cout << "=========================================================================" << std::endl;
            std::cout << "Current Task List: " << std::endl;
            int count = 0;
            for ( const auto &p : todo){
                count = count + 1;
                std::cout << "[" << count << "] " << p.first << "   -   " << p.second << " minutes"  << std::endl;
            } 
            std::cout << "=========================================================================" << std::endl;
            std::cout << "[" << currentTask << "] " << "Task name: "; 
            std::getline(std::cin, taskName); // We use getline para mu take ug input with space.
            if (taskName == "done") {
                break;
            } else { // This will loop until the user types 'done'
                std::cout << "[" << currentTask << "] " << "How long should this task take? (in minutes): ";
                std::cin >> taskDuration; 
                std::cin.ignore();
                todo[taskName] = taskDuration;
                currentTask = currentTask + 1;
            };
        };
    };
};
App AppInstance; // Initializes the App class



int main() {
    AppInstance.registerScreen();
    AppInstance.appMenu();
    return 0;
};

