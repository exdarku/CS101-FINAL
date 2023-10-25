#include "include/rang.hpp"
#include <iostream>
#include <string>
#include <map>
#include "include/tsl/ordered_map.h" // For ordered list
#include <cstdlib>


const std::string appName = "Study Buddy"; // App Name


void cpsleep(int time) { 
    #ifdef WINDOWS
    sleep(time);
    #else
    // Assume POSIX
    sleep(time);
    #endif
};


void clear()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
}

class User { // User object | Setter/Getter
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
private:
    std::string taskName;
    int taskDuration;
    tsl::ordered_map<std::string, int> todo;
public:
    void header() { 
        clear();
        std::cout << "=========================================================================" << std::endl;
        std::cout << rang::fg::cyan << rang::style::bold << appName << rang::fg::reset << rang::style::reset << std::endl;
        std::cout << "=========================================================================" << std::endl;
    };

    void registerScreen() {
        header();
        std::string username;
        std::cout << "Howdy there! Register with your name or nickname to continue!\nNickname: ";
        std::getline(std::cin, username);
        loggedInUser.setUsername(username);
    }

    void appMenu() {
        while(true){
            header();
            std::cout << "Welcome to " << appName << ", " << rang::style::bold << rang::fg::green << loggedInUser.getUsername() << rang::style::reset << rang::fg::reset <<"!" << std::endl;
            std::cout << "Enter the tasks you want to do for this session" << std::endl;
            std::cout << "Don't forget to type 'done' in the task name to proceed!" << std::endl;
            std::cout << "=========================================================================" << std::endl;
            std::cout << "Current Task List: \n" << std::endl;
            int count = 0;
            for ( const auto &p : todo){
                count = count + 1;
                std::cout << "[" << count << "] " << p.first << "   -   " << p.second << " minutes"  << std::endl;
            };

            std::cout << "\n[" << count + 1 << "] " << "Task name: "; 
            std::getline(std::cin, taskName); // We use getline para mu take ug input with space.
            if (taskName == "done") {
                break;
            } else { // This will loop until the user types 'done'
                std::cout << "[" << count + 1 << "] " << "How long should this task take? (in minutes): ";
                std::cin >> taskDuration; 
                std::cin.ignore();
                todo[taskName] = taskDuration;
                currentTask = currentTask + 1;
            };  
        };
    };

    void appCountdownScreen() {
        header();
        int pause = 0;
        int count = 0;
        std::cout << "Yipee! All tasks are now in queue! type 'go' and press enter to start with your tasks!\n" << std::endl;
        for(const auto &p : todo){
            count = count + 1;
            std::cout << "[" << count << "] " << p.first << "   -   " << p.second << " minutes"  << std::endl;
        };
        std::cout << "=========================================================================" << std::endl;
        std::cin >> pause;
        // Start the queue
        int loopcount = 0;
        for(const auto &p : todo){
            loopcount = loopcount + 1;
            int currentTaskDuration = p.second * 60;
            while(true){
                header();
                std::cout << "[" << loopcount << "] " << p.first << "   -   " << currentTaskDuration << " seconds \n";
                cpsleep(1);
                currentTaskDuration = currentTaskDuration - 1;
                if(currentTaskDuration == 0) {
                    break;
                };
            };
        };
    };
};
App AppInstance; // Initializes the App class

int main() {
    AppInstance.registerScreen();
    AppInstance.appMenu();
    AppInstance.appCountdownScreen();
    return 0;
};

