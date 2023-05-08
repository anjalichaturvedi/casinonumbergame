#include <iostream>
#include <fstream> // for file handling
#include <string>
#include <cstdlib> // for random number generation

using namespace std;

class Player {
public:
    Player(const string& n, int d) :
        name(n), balance(d), bet(0), score(0) {}

    const string& getName() const {
        return name;
    }

    int getBalance() const {
        return balance;
    }

    int getBet() const {
        return bet;
    }

    int getScore() const {
        return score;
    }

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else {
            return false;
        }
    }

    void placeBet(int amount) {
        bet = amount;
    }

    void resetBet() {
        bet = 0;
    }

    void addScore(int points) {
        score += points;
    }

    void resetScore() {
        score = 0;
    }

    Player operator+(const Player& other) const {
        Player result(name, balance + other.balance);
        result.bet = bet + other.bet;
        result.score = score + other.score;
        return result;
    }

    Player operator-(const Player& other) const {
        Player result(name, balance - other.balance);
        result.bet = bet - other.bet;
        result.score = score - other.score;
        return result;
    }

private:
    string name;
    int balance;
    int bet;
    int score;
};

// Base class for Admin
class BaseAdmin {
protected:
    int drawMoney;
public:
    virtual void removePlayer(Player& player) = 0;
    virtual void viewGames(const Player& player) = 0;
    virtual void changeDrawMoney() = 0;
    virtual void viewScoreboard() = 0;
};

// Derived class for Admin
class Admin : public BaseAdmin {
public:
    Admin() {
        drawMoney = 100;
    }

    void removePlayer(Player& player) {
        string name = player.getName();
        player = Player("", 0);
        cout << "\n\t\t\t\t" << "PLAYER " << name << " HAS BEEN REMOVED" << endl;
    }

   void viewGames(const Player& player) {
    viewScoreboard();
    cout << "\n\t\t\t\t" << player.getName() << ": " << player.getScore() << endl;
}


    void changeDrawMoney() {
        int newAmount;
        cout << "\n\t\t\t\t" << "ENTER NEW DRAW AMOUNT: ";
        cin >> newAmount;
        drawMoney = newAmount;
        cout << "\n\t\t\t\t" << "DRAW MONEY HAS BEEN CHANGED TO " << drawMoney << endl;
    }




    void viewScoreboard() {
    ifstream file("scoreboard.txt");
    if (file.is_open()) {
        cout << "\n\t\t\t\t" << "SCOREBOARD:" << endl;
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(",");
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string scoreStr = line.substr(pos + 1);
                int score = stoi(scoreStr);
                cout << "\n\t\t\t\t" << name << ": " << score << endl;
            }
        }


        file.close();
    }
    else {
        cout << "\n\t\t\t\t" << "UNABLE TO LOAD SCOREBOARD DATA" << endl;
    }
}

};

// Function to save player data to a file
void savePlayerData(const Player& player) {
    ofstream file("player_data.txt", ios::trunc); // open the file in truncation mode
    if (file.is_open()) {
        file << player.getName() << " " << player.getBalance() << " " << player.getScore() << endl;
        file.close();
    }
    else {
        cout << "\n\t\t\t\t" << "UNABLE TO SAVE PLAYER DATA." << endl;
    }
}


// Function to load player data from a file
Player loadPlayerData() {
    ifstream file("player_data.txt");
    string name;

    int balance, score;
    if (file.is_open()) {
        // Read the player data from the file
        file >> name >> balance >> score;
        file.close();
        // Create and return a Player object with the loaded data
        return Player(name, balance);
    }
    else {
        cout << "\n\t\t\t\t" << "UNABLE TO LOAD PLAYER DATA. STARTING WITH DEFAULT VALUES." << endl;
        // Return a default Player object if the file cannot be opened
        return Player("", 10);
    }
}
void printColoredText(const string& text, int colorCode) {
    cout << "\033[" << colorCode << "m" << text << "\033[0m";
}

// Function to print menu options with color
void printMenuOption(const string& option, int optionNumber) {
    printColoredText("\n\t\t\t\t", 0);
    printColoredText(to_string(optionNumber), 33);  // Yellow color for option number
    printColoredText(". ", 0);
    printColoredText(option, 36);  // Cyan color for option text
    cout << endl;
}



// Main function
int main() {



  cout << "\n\t\t\t" << "\033[1;34m***************************************************\n\n";
cout << "\t\t\t\t\t" << "\033[1;34mWELCOME TO CASINO\n";

cout << "\t\t\t\t" << "\033[1;34m    _______   _______   _______\n";
cout << "\t\t\t\t" << "\033[1;34m   |       | |       | |       |\n";
cout << "\t\t\t\t" << "\033[1;34m   |   7   | |   7   | |   7   |\n";
cout << "\t\t\t\t" << "\033[1;34m   |_______| |_______| |_______|\n";
cout << "\t\t\t\t" << "\033[1;34m    _______   _______   _______\n";
cout << "\t\t\t\t" << "\033[1;34m   |       | |       | |       |\n";
cout << "\t\t\t\t" << "\033[1;34m   |   7   | |   7   | |   7   |\n";
cout << "\t\t\t\t" << "\033[1;34m   |_______| |_______| |_______|\n";
cout << "\t\t\t\t" << "\033[1;34m    _______   _______   _______\n";
cout << "\t\t\t\t" << "\033[1;34m   |       | |       | |       |\n";
cout << "\t\t\t\t" << "\033[1;34m   |   7   | |   7   | |   7   |\n";
cout << "\t\t\t\t" << "\033[1;34m   |_______| |_______| |_______|\n";
cout << "\n\n\t\t\t Enter any key to continue.....\n\n";
cout << "\t\t\t" << "\033[1;34m***************************************************\n";



    getchar();

    Player player = loadPlayerData(); // Load player data from file
    Admin admin;
    int drawMoney = 100;
    bool continuePlaying = true;

    while (true) {
        int choice;
        cout << "\n\t\t\t" << "=======================================================" << endl;
        cout << "\n\t\t\t\t" << "MENU" << endl;
        printMenuOption("ADMIN LOGIN", 1);
        printMenuOption("PLAYER LOGIN", 2);
        printMenuOption("CREATE NEW PLAYER ACCOUNT", 3);
        printMenuOption("QUIT", 0);

        cin >> choice;
        cout << "\n\t\t\t" << "=======================================================" << endl;
        if (choice == 1) {
            string password;
            cout << "\n\t\t\t\t" << "ENTER PASSWORD: ";
            cin >> password;
            if (password == "admin") {
                int adminChoice;
                cout << "\n\t\t\t" << "\033[1;33m=======================================================\n";
                cout << "\n\t\t\t\t" << "\033[1;33mADMIN MENU" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m1. REMOVE PLAYER" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m2. VIEW ALL GAMES" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m3. CHANGE DRAW MONEY" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m0. EXIT" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33mENTER CHOICE: ";
                cin >> adminChoice;
                cout << "\n\t\t\t" << "\033[1;33m=======================================================\n";

                switch (adminChoice) {
                case 1:

                    admin.removePlayer(player);
                    break;
                case 2:
                 admin.viewGames(player);
    break;
                    break;
                case 3:
                    admin.changeDrawMoney();
                    break;
                case 0:
                    break;
                default:
                    cout << "\n\t\t\t\t" << "\033[1;33mINVALID CHOICE" << endl;
                    break;
                }
            }
            else {
                cout << "\n\t\t\t\t" << "\033[1;33mINCORRECT PASSWORD" << endl;
            }
        }
        else if (choice == 2) {
            if (player.getName() == "") {
                string name;
                int deposit;
                cout << "\n\t\t\t\t" << "\033[1;33mENTER YOUR NAME: ";
                cin >> name;
                cout << "\n\t\t\t\t" << "\033[1;33mENTER DEPOSIT MONEY: ";
                cin >> deposit;
                player = Player(name, deposit);
                cout << "\n\t\t\t\t" << "\033[1;33mWELCOME, " << name << "\033[1;33m. YOUR BALANCE IS " << deposit << endl;
            }
            else {
                cout << "\n\t\t\t\t" << "\033[1;33mWELCOME BACK, " << player.getName() << "\033[1;33m. YOUR BALANCE IS " << player.getBalance() << endl;
            }

            int roundCount = 1;
            while (true) {
                int gameChoice;

                cout << "\n\t\t\t" << "\033[1;34m=======================================================\n";
                cout << "\n\t\t\t" << "\033[1;34m*                    SLOT MACHINE                        *\n";
                cout << "\n\t\t\t" << "\033[1;34m*                                                        *\n";
                cout << "\n\t\t\t" << "\033[1;34m*     +-----+   +-----+   +-----+   +-----+   +-----+     *\n";
                cout << "\n\t\t\t" << "\033[1;34m*     |     |   |     |   |     |   |     |   |     |     *\n";
                cout << "\n\t\t\t" << "\033[1;34m*     |  1  |   |  2  |   |  3  |   |  4  |   |  5  |     *\n";
                cout << "\n\t\t\t" << "\033[1;34m*     |     |   |     |   |     |   |     |   |     |     *\n";
                cout << "\n\t\t\t" << "\033[1;34m*     +-----+   +-----+   +-----+   +-----+   +-----+     *\n";
                cout << "\n\t\t\t" << "\033[1;34m*                                                        *\n";
                cout << "\n\t\t\t" << "\033[1;34m==========================================================\n";
                cout << endl;

                cout << "\n\t\t\t" << "\033[1;33m=======================================================\n";
                cout << "\n\t\t\t\t" << "\033[1;33mGAME MENU" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m1. PLAY" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m2. VIEW BALANCE" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m3. ADD DEPOSIT" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m4. RESET BET" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33m0. QUIT" << endl;
                cout << "\n\t\t\t\t" << "\033[1;33mENTER CHOICE: ";
                cin >> gameChoice;
                cout << "\n\t\t\t" << "\033[1;33m=======================================================" << endl;
                if (gameChoice == 1) {
                    int betAmount;
                    cout << "\n\t\t\t\t" << "\033[1;33mENTER BET AMOUNT: ";
                    cin >> betAmount;
                    if (player.withdraw(betAmount)) {
                        player.placeBet(betAmount);
                        int randomNumber = rand() % 10 + 1; // generate random number between 1 and 10
                        int playerNumber;
                        cout << "\n\t\t\t\t" << "\033[1;33mENTER A NUMBER BETWEEN 1 AND 10: ";
                        cin >> playerNumber;

                        if (playerNumber == randomNumber) {
                            int winnings = betAmount * 10;
                            player.deposit(winnings);
                            player.addScore(winnings);
                            cout << "\n\t\t\t\t" << "\033[1;33mCONGRATULATIONS, YOU GUESSED THE CORRECT NUMBER! YOU WON " << winnings << "." << endl;
                        }
                        else {
                            int losses = betAmount;
                            player.resetBet();
                            player.addScore(-losses);
                            cout << "\n\t\t\t\t" << "\033[1;33mSORRY, YOU GUESSED THE WRONG NUMBER. YOU LOST " << losses << "." << endl;
                        }

                        int balance = player.getBalance();
                        if (balance < drawMoney) {
                            cout << "\n\t\t\t\t" << "\033[1;33mINSUFFICIENT BALANCE TO CONTINUE PLAYING. YOUR FINAL SCORE IS " << player.getScore() << "." << endl;
                            break;
                        }


                        // Save player data to file
                        ofstream file("scoreboard.txt", ios::app);
                        if (file.is_open()) {
                            file << player.getName() << "," << player.getScore() << endl;
                            file.close();
                        } else {
                            cout << "\n\t\t\t\t" << "\033[1;33mUNABLE TO SAVE SCOREBOARD DATA" << endl;
                        }

                        cout << "\n\t\t\t\t" << "\033[1;33mYOUR CURRENT BALANCE IS " << balance << "\033[1;33m. DO YOU WANT TO CONTINUE PLAYING? (y/n): ";
                        char continueChoice;
                        cin >> continueChoice;
                        if (continueChoice == 'n') {
                            cout << "\n\t\t\t\t" << "\033[1;33mTHANK YOU FOR PLAYING. YOUR FINAL SCORE IS " << player.getScore() << "." << endl;
                            break;
                        }

                        roundCount++;
                    }
                    else {
                        cout << "\n\t\t\t\t" << "\033[1;33mINSUFFICIENT BALANCE TO PLACE BET." << endl;
                    }
                }
                else if (gameChoice == 2) {
                    cout << "\n\t\t\t\t" << "\033[1;33mYOUR BALANCE IS " << player.getBalance() << endl;
                }
                else if (gameChoice == 3) {
                    int depositAmount;
                    cout << "\n\t\t\t\t" << "\033[1;33mENTER DEPOSIT AMOUNT: ";
                    cin >> depositAmount;
                    player.deposit(depositAmount);
                    cout << "\n\t\t\t\t" << "\033[1;33mDEPOSIT SUCCESSFUL. YOUR NEW BALANCE IS " << player.getBalance() << endl;
                }
                else if (gameChoice == 4) {
                    player.resetBet();
                    cout << "\n\t\t\t\t" << "\033[1;33mBET RESET." << endl;
                }
                else if (gameChoice == 0) {
                    break;
                }
                else {
                    cout << "\n\t\t\t\t" << "\033[1;33mINVALID CHOICE." << endl;
                }
            }
        }
        else if (choice == 3) {
        // Create new player account
        string name;
        int balance;
        cout << "\n\t\t\t\t" << "ENTER YOUR NAME: ";
        cin >> name;
        cout << "\n\t\t\t\t" << "ENTER STARTING BALANCE: ";
        cin >> balance;
        Player newPlayer(name, balance);
        savePlayerData(newPlayer);
        player = newPlayer;
    }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "\n\t\t\t\t" << "INVALID CHOICE." << endl;
        }
    }

   ifstream file("scoreboard.txt");
if (file.is_open()) {
    cout << "\n\t\t\t\t" << "\033[1;33mSCOREBOARD:" << endl;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string scoreStr = line.substr(pos + 1);
            int score = stoi(scoreStr);
            cout << "\n\t\t\t\t" << name << ": \033[1;33m" << score << endl;
        }
    }
    file.close();
}

    else {
        cout << "\n\t\t\t\t" << "UNABLE TO LOAD SCOREBOARD DATA" << endl;
    }
    return 0;
}
