#include <iostream>
#include <string>
#include <cstdlib> // for random number generation

using namespace std;

class Player {
public:
    Player(const string & n, int d):
        name(n), balance(d), bet(0), score(0) {}
    const string & getName() const {
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
        } else {
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

// Admin class
class Admin {
   public: void removePlayer(Player & player) {
      string name = player.getName();
      player = Player("", 0);
      cout << "\n\t\t\t\t" << "Player " << name << " has been removed." << endl;
   }
   void viewGames(const Player & player) {
      cout << "\n\t\t\t\t" << "Scoreboard:" << endl;
      cout <<  "\n\t\t\t\t" << player.getName() << ": " << player.getScore() << endl;
   }
   void changeDrawMoney(int & drawMoney) {
      int newAmount;
      cout << "\n\t\t\t\t" << "Enter new draw money amount: ";
      cin >> newAmount;
      drawMoney = newAmount;
      cout << "\n\t\t\t\t" << "Draw money has been changed to " << drawMoney << endl;
   }
};

// Main function
int main() {
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t        =                                           =";
    cout << "\n\t\t\t        =                    WELCOME                =";
    cout << "\n\t\t\t        =                      TO                   =";
    cout << "\n\t\t\t        =                 CASINO GAME               =";
    cout << "\n\t\t\t        =                                           =";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\n\n\t\t\t Enter any key to continue.....";
    getchar();
   Player player("", 10);
   Admin admin;
   int drawMoney = 100;
   bool continuePlaying = true;

   while (true) {
      int choice;
      cout << "\n\t\t\t" << "=======================================================" << endl;
      cout << "\n\t\t\t\t" << "MENU" << endl;
      cout << "\n\t\t\t\t" << "1. ADMIN LOGIN" << endl;
      cout << "\n\t\t\t\t" << "2. PLAYER LOGIN" << endl;
      cout << "\n\t\t\t\t" << "0. QUIT" << endl;
      cout << "\n\t\t\t\t" << "ENTER CHOICE: ";
      cin >> choice;
      cout << "\n\t\t\t" << "=======================================================" << endl;
      if (choice == 1) {
         string password;
         cout << "\n\t\t\t\t" << "ENTER PASSWORD: ";
         cin >> password;
         if (password == "admin") {
            int adminChoice;
            cout << "\n\t\t\t" << "=======================================================" << endl;
            cout << "\n\t\t\t\t" << "ADMIN MENU" << endl;
            cout << "\n\t\t\t\t" << "1. REMOVE PLAYER" << endl;
            cout << "\n\t\t\t\t" << "2. VIEW ALL PLAYERS" << endl;
            cout << "\n\t\t\t\t" << "3. CHANGE DRAW MONEY" << endl;
            cout << "\n\t\t\t\t" << "0. EXIT" << endl;
            cout << "\n\t\t\t\t" << "ENTER CHOICE: ";
            cin >> adminChoice;
            cout << "\n\t\t\t" << "=======================================================" << endl;
            switch (adminChoice) {
            case 1:
               admin.removePlayer(player);
               break;
            case 2:
               admin.viewGames(player);
               break;
            case 3:
               admin.changeDrawMoney(drawMoney);
               break;
            case 0:
               break;
            default:
               cout << "\n\t\t\t\t" << "INVALID CHOICE" << endl;
               break;
            }
         } else {
            cout << "\n\t\t\t\t" << "INCORRECT PASSWORD" << endl;
         }
      } else if (choice == 2) {
         string name;
         int deposit;
         cout << "\n\t\t\t\t" << "ENTER YOUR NAME: ";
         cin >> name;
         cout << "\n\t\t\t\t" << "ENTER DEPOSIT MONEY: ";
         cin >> deposit;
         player = Player(name, deposit);
         cout << "\n\t\t\t\t" << "WELCOME, " << name << ". YOUR BALANCE IS " << deposit << endl;
         int roundCount = 1;
         while (true) {
            int gameChoice;
            cout << "\n\t\t\t" << "=======================================================" << endl;
            cout << "\n\t\t\t\t" << "GAME MENU" << endl;
            cout << "\n\t\t\t\t" << "1. PLAY" << endl;
            cout << "\n\t\t\t\t" << "2. VIEW BALANCE" << endl;
            cout << "\n\t\t\t\t" << "3. ADD DEPOSIT" << endl;
            cout << "\n\t\t\t\t" << "4. RESET BET" << endl;
            cout << "\n\t\t\t\t" << "0. QUIT" << endl;
            cout << "\n\t\t\t\t" << "ENTER CHOICE: ";
            cin >> gameChoice;
            cout << "\n\t\t\t" << "=======================================================" << endl;
            if (gameChoice == 1) {
               int betAmount;
               cout << "\n\t\t\t\t" << "ENTER BET AMOUNT: ";
               cin >> betAmount;
               if (player.withdraw(betAmount)) {
                  player.placeBet(betAmount);
                  int randomNumber = rand() % 10 + 1; // generate random number between 1 and 10
                  int playerNumber;
                  cout << "\n\t\t\t\t" << "ENTER A NUMBER BETWEEN 1 AND 10: ";
                  cin >> playerNumber;

                  if (playerNumber == randomNumber) {
                     int winnings = betAmount * 10;
                     player.deposit(winnings);
                     player.addScore(winnings);
                     cout << "\n\t\t\t\t" << "CONGRATULATIONS, YOU GUESSED THE CORRECT NUMBER! YOU WON " << winnings << "." << endl;
                  } else {
                     int losses = betAmount;
                     player.resetBet();
                     player.addScore(-losses);
                     cout << "\n\t\t\t\t" << "SORRY, YOU GUESSED THE WRONG NUMBER. YOU LOST " << losses << "." << endl;
                  }

                  int balance = player.getBalance();
                  if (balance < drawMoney) {
                     cout << "\n\t\t\t\t" << "INSUFFICIENT BALANCE TO CONTINUE PLAYING. YOUR FINAL SCORE IS " << player.getScore() << "." << endl;
                     break;
                  }

                  cout << "\n\t\t\t\t" << "YOUR CURRENT BALANCE IS " << balance << ". DO YOU WANT TO CONTINUE PLAYING? (y/n): ";
                  char continueChoice;
                  cin >> continueChoice;
                  if (continueChoice == 'n') {
                     cout << "\n\t\t\t\t" << "THANK YOU FOR PLAYING. YOUR FINAL SCORE IS " << player.getScore() << "." << endl;
                     break;
                  }

                  roundCount++;
               } else {
                  cout << "\n\t\t\t\t" << "INSUFFICIENT BALANCE TO PLACE BET." << endl;
               }
            } else if (gameChoice == 2) {
               cout << "\n\t\t\t\t" << "YOUR BALANCE IS " << player.getBalance() << endl;
            } else if (gameChoice == 3) {
               int depositAmount;
               cout << "\n\t\t\t\t" << "ENTER DEPOSIT AMOUNT: ";
               cin >> depositAmount;
               player.deposit(depositAmount);
               cout << "\n\t\t\t\t" << "DEPOSIT SUCCESSFUL. YOUR NEW BALANCE IS " << player.getBalance() << endl;
            } else if (gameChoice == 4) {
               player.resetBet();
               cout << "\n\t\t\t\t" << "BET RESET." << endl;
            } else if (gameChoice == 0) {
               break;
            } else {
               cout << "\n\t\t\t\t" << "INVALID CHOICE." << endl;
            }
         }
      } else if (choice == 0) {
         break;
      } else {
         cout << "\n\t\t\t\t" << "INVALID CHOICE." << endl;
      }
   }
   return 0;
}
