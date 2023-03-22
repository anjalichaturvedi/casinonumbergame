#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Game {
    int secretNumber;
    int tries;
    string playerName;
};

void removePlayer(string players[], int& numPlayers) {
    string playerToRemove;
    cout << "Enter the name of the player to remove: ";
    cin >> playerToRemove;

    // Find and remove the player from the array
    for (int i = 0; i < numPlayers; i++) {
        if (players[i] == playerToRemove) {
            for (int j = i; j < numPlayers - 1; j++) {
                players[j] = players[j + 1];
            }
            numPlayers--;
            cout << playerToRemove << " has been removed from the list of players.\n";
            return;
        }
    }

    cout << playerToRemove << " was not found in the list of players.\n";
}

void viewGames(Game games[], int numGames) {
    cout << "Past games:\n";
    for (int i = 0; i < numGames; i++) {
        cout << "Player: " << games[i].playerName << ", Secret number: " << games[i].secretNumber
             << ", Tries: " << games[i].tries << endl;
    }
}

void changeDrawMoney(double& drawMoney) {
    double newDrawMoney;
    cout << "Enter the new draw money amount: $";
    cin >> newDrawMoney;

    if (newDrawMoney < 0) {
        cout << "Error: Draw money cannot be negative.\n";
    } else {
        drawMoney = newDrawMoney;
        cout << "Draw money has been changed to: $" << drawMoney << endl;
    }
}

int main() {
    srand(time(0));  // Seed the random number generator with current time
    int secretNumber = rand() % 100 + 1;  // Generate a random number between 1 and 100
    int guess;
    int tries = 0;
    string adminUsername = "admin";
    string adminPassword = "password";
    string username, password;
    string players[100];
    int numPlayers = 0;
    Game games[100];
    int numGames = 0;
    double drawMoney = 1000.0;

    cout << "Welcome to the number guessing game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";

    while (true) {
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;

        if (username == adminUsername && password == adminPassword) {
            cout << "Login successful. You are now logged in as admin.\n";

            while (true) {
                cout << "What would you like to do?\n";
                cout << "1. Remove a player\n";
                cout << "2. View all past games\n";
                cout << "3. Change the draw money\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        removePlayer(players, numPlayers);
                        break;
                    case 2:
                        viewGames(games, numGames);
                        break;
                    case 3:
                        changeDrawMoney(drawMoney);
                        break;
                    case 4:
                        cout << "Logging out of admin account.\n";
                        break;
                    default:
                        cout << "Invalid choice";
                }
            }
        }
    }
}

