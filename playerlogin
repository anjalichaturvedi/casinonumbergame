#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Game {
    public:
    int secretNumber;
    int tries;
    string playerName;
};

class Player {
private:
    string name;
    double balance;
public:
    Player() {}
    Player(string n, double b) {
        name = n;
        balance = b;
    }
    string getName() {
        return name;
    }
    double getBalance() {
        return balance;
    }
    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: $" << balance << endl;
    }
    void bet(double amount) {
        if (balance < amount) {
            cout << "Error: Insufficient balance.\n";
        } else {
            balance -= amount;
            cout << "Bet successful. New balance: $" << balance << endl;
        }
    }
};

void removePlayer(Player players[], int& numPlayers) {
    string playerToRemove;
    cout << "Enter the name of the player to remove: ";
    cin >> playerToRemove;

    // Find and remove the player from the array
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].getName() == playerToRemove) {
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

void playerLogin(Player players[], int& numPlayers) {
    string playerName;
    double balance;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Enter your starting balance: $";
    cin >> balance;
    Player p(playerName, balance);
    players[numPlayers] = p;
    numPlayers++;
    cout << "Welcome, " << playerName << "! Your starting balance is $" << balance << endl;

    while (true) {
        cout << "What would you like to do?\n";
        cout << "1. Deposit money\n";
        cout << "2. Place a bet\n";
        cout << "3. Check balance\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                double depositAmount;
                cout << "Enter the amount to deposit: $";
                cin >> depositAmount;
                p.deposit(depositAmount);
                break;
            case 2:
                double betAmount;
                cout << "Enter the amount to bet: $";
                cin >> betAmount;
                p.bet(betAmount);
                break;
            case 3:
                cout << "Available balance is: $" << p.getBalance();
            }
     }
}

int main() {
    const int MAX_PLAYERS = 10;
    Player players[MAX_PLAYERS];
    int numPlayers = 0;
    Game games[10];
    double drawMoney = 1000.0;

    srand(time(NULL));

    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Add player\n";
        cout << "2. Remove player\n";
        cout << "3. View past games\n";
        cout << "4. Change draw money\n";
        cout << "5. Player login\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (numPlayers < MAX_PLAYERS) {
                    string name;
                    double balance;
                    cout << "Enter player name: ";
                    cin >> name;
                    cout << "Enter starting balance: $";
                    cin >> balance;
                    Player p(name, balance);
                    players[numPlayers] = p;
                    numPlayers++;
                    cout << "Player added successfully.\n";
                } else {
                    cout << "Maximum number of players reached.\n";
                }
                break;
            case 2:
                removePlayer(players, numPlayers);
                break;
            case 3:
                viewGames(games, 10);
                break;
            case 4:
                changeDrawMoney(drawMoney);
                break;
            case 5:
                playerLogin(players, numPlayers);
                break;
            case 6:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

