#include <iostream>
#include <string>
#include <cstdlib> // for random number generation

using namespace std;

// Player class
class Player {
   public: Player(const string & n, int d): name(n),
   balance(d),
   bet(0),
   score(0) {}
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
   private: string name;
   int balance;
   int bet;
   int score;
};

// Admin class
class Admin {
   public: void removePlayer(Player & player) {
      string name = player.getName();
      player = Player("", 0);
      cout << "Player " << name << " has been removed." << endl;
   }
   void viewGames(const Player & player) {
      cout << "Scoreboard:" << endl;
      cout << player.getName() << ": " << player.getScore() << endl;
   }
   void changeDrawMoney(int & drawMoney) {
      int newAmount;
      cout << "Enter new draw money amount: ";
      cin >> newAmount;
      drawMoney = newAmount;
      cout << "Draw money has been changed to " << drawMoney << endl;
   }
};

// Main function
int main() {
   Player player("", 0);
   Admin admin;
   int drawMoney = 100;
   bool continuePlaying = true;

   while (true) {
      int choice;
      cout << "Menu:" << endl;
      cout << "1. Admin login" << endl;
      cout << "2. Player login" << endl;
      cout << "0. Quit" << endl;
      cout << "Enter choice: ";
      cin >> choice;

      if (choice == 1) {
         string password;
         cout << "Enter password: ";
         cin >> password;
         if (password == "admin") {
            int adminChoice;
            cout << "Admin menu:" << endl;
            cout << "1. Remove player" << endl;
            cout << "2. View all past games" << endl;
            cout << "3. Change draw money" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter choice: ";
            cin >> adminChoice;

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
               cout << "Invalid choice." << endl;
               break;
            }
         } else {
            cout << "Incorrect Password." << endl;
         }
      } else if (choice == 2) {
         string name;
         int deposit;
         cout << "Enter your name: ";
         cin >> name;
         cout << "Enter deposit amount: ";
         cin >> deposit;
         player = Player(name, deposit);
         cout << "Welcome, " << name << ". Your balance is " << deposit;
         int roundCount = 1;
         while (true) {
            int gameChoice;
            cout << "Game menu:" << endl;
            cout << "1. Play" << endl;
            cout << "2. View balance" << endl;
            cout << "3. Add deposit" << endl;
            cout << "4. Reset bet" << endl;
            cout << "0. Quit" << endl;
            cout << "Enter choice: ";
            cin >> gameChoice;

            if (gameChoice == 1) {
               int betAmount;
               cout << "Enter bet amount: ";
               cin >> betAmount;
               if (player.withdraw(betAmount)) {
                  player.placeBet(betAmount);
                  int randomNumber = rand() % 10 + 1; // generate random number between 1 and 10
                  int playerNumber;
                  cout << "Enter a number between 1 and 10: ";
                  cin >> playerNumber;

                  if (playerNumber == randomNumber) {
                     int winnings = betAmount * 10;
                     player.deposit(winnings);
                     player.addScore(winnings);
                     cout << "Congratulations, you guessed the correct number! You won " << winnings << "." << endl;
                  } else {
                     int losses = betAmount;
                     player.resetBet();
                     player.addScore(-losses);
                     cout << "Sorry, you guessed the wrong number. You lost " << losses << "." << endl;
                  }

                  int balance = player.getBalance();
                  if (balance < drawMoney) {
                     cout << "Insufficient balance to continue playing. Your final score is " << player.getScore() << "." << endl;
                     break;
                  }

                  cout << "Your current balance is " << balance << ". Do you want to continue playing? (y/n): ";
                  char continueChoice;
                  cin >> continueChoice;
                  if (continueChoice == 'n') {
                     cout << "Thank you for playing. Your final score is " << player.getScore() << "." << endl;
                     break;
                  }

                  roundCount++;
               } else {
                  cout << "Insufficient balance to place bet." << endl;
               }
            } else if (gameChoice == 2) {
               cout << "Your balance is " << player.getBalance() << endl;
            } else if (gameChoice == 3) {
               int depositAmount;
               cout << "Enter deposit amount: ";
               cin >> depositAmount;
               player.deposit(depositAmount);
               cout << "Deposit successful. Your new balance is " << player.getBalance() << endl;
            } else if (gameChoice == 4) {
               player.resetBet();
               cout << "Bet reset." << endl;
            } else if (gameChoice == 0) {
               break;
            } else {
               cout << "Invalid choice." << endl;
            }
         }
      } else if (choice == 0) {
         break;
      } else {
         cout << "Invalid choice." << endl;
      }
   }
   return 0;
}
