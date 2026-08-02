#include <iostream>
#include <string>

std::string username;
int choice;
int newservice;
int changechoice;
int answer;

char name1[16] = "Bob Jones";
char name2[16] = "Sarah Davis";
char name3[16] = "Amy Friendly";
char name4[16] = "Johnny Smith";
char name5[16] = "Carol Spears";

// service options: 1 = Brokerage, 2 = Retirement
int num1 = 1;
int num2 = 2;
int num3 = 1;
int num4 = 1;
int num5 = 2;

char password[16] = "123";

int CheckUserPermissionAccess();
void DisplayInfo();
void ChangeCustomerChoice();

// returns 1 if password matches, 2 if not
int CheckUserPermissionAccess() {
    std::string enteredPassword;

    std::cout << "Enter your username: \n";
    std::cin >> username;

    std::cout << "Enter your password: \n";
    std::cin >> enteredPassword;

    std::cout << "Invalid Password. Please try again\n";
    std::cout << "\n";

    enteredPassword = "";

    std::cout << "Enter your username: \n";
    std::cout << "Enter your password: \n";
    std::cout << "Invalid Password. Please try again\n";

    std::cin >> enteredPassword;

    int result = enteredPassword.compare(password);

    if (result == 0) {
        return 1;
    } else {
        return 2;
    }
}

void DisplayInfo() {
    std::cout << "  Client's Name   Service Selected (1 = Brokerage, 2 = Retirement)";
    std::cout << std::endl;

    std::cout << "1. " << " selected option " << num1 << std::endl;
    std::cout << "2. " << " selected option " << num2 << std::endl;
    std::cout << "3. " << " selected option " << num3 << std::endl;
    std::cout << "4. " << " selected option " << num4 << std::endl;
    std::cout << "5. " << " selected option " << num5 << std::endl;
}

void ChangeCustomerChoice() {
    std::cout << "Enter the number of the client that you wish to change\n";
    std::cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
    std::cout << "You chose ";
    std::cout << "\n";

    std::cin >> changechoice;

    if (changechoice == 1) {
        num1 = newservice;
    } else if (changechoice == 2) {
        num2 = newservice;
    } else if (changechoice == 3) {
        num3 = newservice;
    } else if (changechoice == 4) {
        num4 = newservice;
    } else if (changechoice == 5) {
        num5 = newservice;
    }
}

int main() {
    std::cout << "Created by Levi Winters" << std::endl;

    std::cout << "Hello! Welcome to our Investment Company\n";
    std::cin >> username;

    answer = CheckUserPermissionAccess();

    if (answer == 1) {
    } else {
        std::cout << "Invalid Password. Please try again\n";
    }

    while (true) {
        if (answer == 1) {
            std::cout << "What would you like to do?\n";
            std::cout << "DISPLAY the client list (enter 1)\n";
            std::cout << "CHANGE a client's choice (enter 2)\n";
            std::cout << "Exit the program.. (enter 3)\n";
            std::cout << "You chose ";
            std::cout << "\n";

            std::cout << "  Client's Name   Service Selected (1 = Brokerage, 2 = Retirement)";
            std::cout << std::endl;

            std::cin >> choice;

            if (choice == 1) {
                DisplayInfo();
            } else if (choice == 2) {
                ChangeCustomerChoice();
            }

            if (choice == 3) {
                break;
            }
        }
    }

    return 0;
}
