#include <iostream>
#include <limits>
#include <string>
#include <vector>

const int SERVICE_BROKERAGE = 1;
const int SERVICE_RETIREMENT = 2;

const std::string STORED_USERNAME = "admin";
const std::string STORED_PASSWORD = "123";

class Client {
public:
    Client(std::string name, int service) : name(std::move(name)), service(service) {}

    const std::string& getName() const { return name; }
    int getService() const { return service; }
    void setService(int newService) { service = newService; }

private:
    std::string name;
    int service;
};

std::string serviceLabel(int service) {
    if (service == SERVICE_BROKERAGE) {
        return "Brokerage";
    }
    if (service == SERVICE_RETIREMENT) {
        return "Retirement";
    }
    return "Unknown";
}

// keeps asking until we get a real number in range, cin.fail() catches
// letters/garbage input
int readValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That doesn't look like a number. Please try again.\n";
            continue;
        }

        if (value < min || value > max) {
            std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        return value;
    }
}

bool checkUserPermissionAccess() {
    std::string enteredUsername;
    std::string enteredPassword;

    std::cout << "Enter your username: \n";
    std::cin >> enteredUsername;

    std::cout << "Enter your password: \n";
    std::cin >> enteredPassword;

    return enteredUsername == STORED_USERNAME && enteredPassword == STORED_PASSWORD;
}

void displayInfo(const std::vector<Client>& clients) {
    std::cout << "  #  Client's Name        Service Selected\n";

    for (std::size_t i = 0; i < clients.size(); ++i) {
        std::cout << "  " << (i + 1) << ". "
                   << clients[i].getName() << "  -  "
                   << serviceLabel(clients[i].getService()) << "\n";
    }
}

void changeCustomerChoice(std::vector<Client>& clients) {
    int clientNumber = readValidatedInt(
        "Enter the number of the client that you wish to change (1-" +
            std::to_string(clients.size()) + "): ",
        1, static_cast<int>(clients.size()));

    // index is clientNumber - 1 since the menu is 1-based but vector isn't
    int newService = readValidatedInt(
        "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement): ",
        SERVICE_BROKERAGE, SERVICE_RETIREMENT);

    clients[clientNumber - 1].setService(newService);

    std::cout << "Updated " << clients[clientNumber - 1].getName()
               << " to " << serviceLabel(newService) << ".\n";
}

int main() {
    std::cout << "Created by Levi Winters" << std::endl;
    std::cout << "Hello! Welcome to our Investment Company\n";

    if (!checkUserPermissionAccess()) {
        std::cout << "Invalid username or password. Exiting program.\n";
        return 1;
    }

    std::vector<Client> clients = {
        Client("Bob Jones", SERVICE_BROKERAGE),
        Client("Sarah Davis", SERVICE_RETIREMENT),
        Client("Amy Friendly", SERVICE_BROKERAGE),
        Client("Johnny Smith", SERVICE_BROKERAGE),
        Client("Carol Spears", SERVICE_RETIREMENT)
    };

    while (true) {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "DISPLAY the client list (enter 1)\n";
        std::cout << "CHANGE a client's choice (enter 2)\n";
        std::cout << "Exit the program.. (enter 3)\n";

        int choice = readValidatedInt("You chose: ", 1, 3);

        if (choice == 1) {
            displayInfo(clients);
        } else if (choice == 2) {
            changeCustomerChoice(clients);
        } else if (choice == 3) {
            break;
        }
    }

    return 0;
}
