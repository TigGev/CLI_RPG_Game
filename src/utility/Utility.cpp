#include "../../headers/utility/Utility.h"


void Utility::printRed(const std::string& msg) {std::cout << "\033[31m" << msg << "\033[0m";}
void Utility::printGreen(const std::string& msg) {std::cout << "\033[32m" << msg << "\033[0m";}
void Utility::printYell(const std::string& msg) {std::cout << "\033[33m" << msg << "\033[0m";}
void Utility::printBlue(const std::string& msg) {std::cout << "\033[34m" << msg << "\033[0m";}
void Utility::printPurple(const std::string& msg) {std::cout << "\033[35m" << msg << "\033[0m";}

void Utility::printHealt(int healt) {
    if (healt > 100) printPurple(std::to_string(healt));
    else if (healt > 70) printBlue(std::to_string(healt));
    else if (healt > 30) printYell(std::to_string(healt));
    else printRed(std::to_string(healt));
}

void Utility::printAttack(int attack) {
    if (attack > 150) printPurple(std::to_string(attack));
    else if (attack > 80) printBlue(std::to_string(attack));
    else if (attack > 15) printYell(std::to_string(attack));
    else printRed(std::to_string(attack));
}

void Utility::printDefence(int defence) {
    if (defence > 80) printPurple(std::to_string(defence));
    else if (defence > 40) printBlue(std::to_string(defence));
    else if (defence > 10) printYell(std::to_string(defence));
    else printRed(std::to_string(defence));
}

int Utility::getValidatedInput(int min, int max) {
    int choice;
    std::cout << "Select option: ";
    while (true) {
        if (std::cin >> choice) {
            if (choice < min || choice > max) {
                std::cout << "Invalid input: Please enter a number between " << min << " and " << max << ": ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else break;;
        }
        else {
            std::cout << "Invalid input: Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return choice;
}
