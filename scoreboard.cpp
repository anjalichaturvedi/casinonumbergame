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
