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

// admin class 
class Admin {
public:
    void removePlayer(string players[], int& numPlayers);
    void viewGames(Game games[], int numGames);
    void changeDrawMoney(double& drawMoney);
};

void Admin::removePlayer(string players[], int& numPlayers) {
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

void Admin::viewGames(Game games[], int numGames) {
    cout << "Past games:\n";
    for (int i = 0; i < numGames; i++) {
        cout << "Player: " << games[i].playerName << ", Secret number: " << games[i].secretNumber
             << ", Tries: " << games[i].tries << endl;
    }
}

void Admin::changeDrawMoney(double& drawMoney) {
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

// player class
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
};

class Score {
public:
    void updateScoreboard(int scores[], string players[], string playerName, int tries) {
    for (int i = 0; i < 10; i++) {
        if (playerName == players[i]) {
            if (tries < scores[i] || scores[i] == 0) {
                scores[i] = tries;
                cout << "New high score for " << playerName << ": " << tries << " tries!\n";
            } else {
                cout << "You did not beat your high score for " << playerName << ".\n";
            }
            return;
        }
    }
    // If the player is not found in the scoreboard, add them to the bottom
    for (int i = 0; i < 10; i++) {
        if (players[i] == "") {
            players[i] = playerName;
            scores[i] = tries;
            cout << "Added " << playerName << " to the scoreboard with " << tries << " tries.\n";
            return;
        }
    }
}

void viewScoreboard(int scores[], string players[]) {
    cout << "High Scores:\n";
    for (int i = 0; i < 10; i++) {
        if (players[i] != "") {
            cout << i + 1 << ". " << players[i] << ": " << scores[i] << " tries\n";
        }
    }
}
};

int main() {
    return 0;
}

