#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

struct BuffInfo {
    string buff;
    bool used;
};

void initializeGame(int& playerHealth, int& computerHealth, vector<bool>& bullets, vector<BuffInfo>& Buffs) {

    vector<string> allBuffs = { "Regen", "Lock", "Peek", "DoubleDamage" };

    // Seed the random number generator with the current time
    srand(time(0));

    // Use a vector to store unique indices
    vector<int> usedIndices;

    // Push the first two random buffs into Buffs
    for (int i = 0; i < 2; i++) {
        int buffindex;
        do {
            buffindex = rand() % 4; // Random index between 0 and 3
        } while (find(usedIndices.begin(), usedIndices.end(), buffindex) != usedIndices.end());

        // Add the selected index to usedIndices to avoid duplicates
        usedIndices.push_back(buffindex);

        // Push the selected buff into Buffs
        Buffs.push_back({ allBuffs[buffindex], false });
    }
    // Initialize player and computer health
    playerHealth = 3;
    computerHealth = 3;

    // Initialize bullets
    bullets = { true, true, true, true, true, true, false, false, false, false };

    // Shuffle bullets
    random_shuffle(bullets.begin(), bullets.end());
}


bool shootBullet(vector<bool>& bullets) {

    if (bullets.empty()) {
        cout << "No more bullets left!" << endl;
        return false;
    }

    bool bullet = bullets.back();
    bullets.pop_back();
    return bullet;
}

void applyBuff(string Player, string buff, int& playerHealth, int& computerHealth, bool& turn, bool& isLive, int& damage) {

    if (buff == "Regen")
    {
        playerHealth++;
        cout << Player << "used Regen buff." << Player << "health is now " << playerHealth << endl;
    }
    else if (buff == "Lock")
    {
        turn = true;
        cout << Player << "used Lock buff.Opponent's turn will be skip." << endl;

    }
    else if (buff == "Peek")
    {
        if (isLive)
            cout << Player << "used Peek buff.The bullet is live." << endl;
        else
            cout << Player << "used Peek buff.The bullet is blank." << endl;
    }
    else if (buff == "DoubleDamage")
    {
        cout << Player << "used Double Damage buff.Double damage will apply on shoot." << endl;
        damage = 2;
    }
}

void playerTurn(int& playerHealth, int& computerHealth, vector<bool>& bullets, vector<BuffInfo>& playerBuffs, bool& CPUTurn, int& damage) {

    cout << "\nYour remaining health: " << playerHealth << " | Computer's remaining health: " << computerHealth << endl;
    bool isLive = shootBullet(bullets);

    int choice;
    cout << "Do you want to use a buff? (1) Yes | (2) No: ";
    cin >> choice;

    if (choice == 1) {
        int index;
        cout << "Choose a buff to use: ";
        if (playerBuffs.size() > 0)
        {
            for (size_t i = 0; i < playerBuffs.size(); ++i) {
                if (!playerBuffs[i].used) {

                    cout << "(" << i + 1 << ") ";

                    if (playerBuffs[i].buff == "Regen")
                    {
                        cout << "Regen ";

                    }
                    else if (playerBuffs[i].buff == "Lock")
                    {
                        cout << "Lock ";

                    }
                    else if (playerBuffs[i].buff == "Peek")
                    {
                        cout << "Peek ";

                    }
                    else if (playerBuffs[i].buff == "DoubleDamage")
                    {
                        cout << "Double Damage ";

                    }

                }
            }
        }
        else {
            cout << "No buff remain !" << endl;
        }
        cout << endl;
        cin >> index;
        int buffIndex = index - 1;

        if (index > 0 && index <= playerBuffs.size() && !playerBuffs[index - 1].used) {
            applyBuff("You ", playerBuffs[buffIndex].buff, playerHealth, computerHealth, CPUTurn, isLive, damage);
            playerBuffs[index - 1].used = true;
        }
        else {
            cout << "Invalid choice! Buff was canceled." << endl;
        }
    }

    int shootChoice;
    cout << "Your turn! Do you want to shoot (1) yourself or (2) the computer? ";
    cin >> shootChoice;



    if (shootChoice == 1) {
        if (isLive) {
            playerHealth = playerHealth - damage;
            cout << "You shot yourself with a live bullet! Your health is now " << playerHealth << endl;
        }
        else {
            cout << "You shot yourself with a blank bullet. You're safe!" << endl;
        }
    }
    else if (shootChoice == 2) {
        if (isLive) {
            computerHealth = computerHealth - damage;
            cout << "You shot the computer with a live bullet! Computer's health is now " << computerHealth << endl;
        }
        else {
            cout << "You shot the computer with a blank bullet. Computer is safe!" << endl;
        }
    }
    else {
        cout << "Invalid choice! Skipping your turn." << endl;
    }
    cout << endl;
}

void computerTurn(int& playerHealth, int& computerHealth, vector<bool>& bullets, vector<BuffInfo>& computerBuffs, bool& isPlayerTurnSkip, int& damage) {

    int choice = rand() % 2 + 1;
    bool isLive = shootBullet(bullets);
    if (choice == 1) {
        int index = rand() % 2 + 1;
        cout << "Computer Choose a buff. ";
        for (size_t i = 0; i < computerBuffs.size(); ++i) {
            if (!computerBuffs[i].used) {
                cout << "(" << i + 1 << ") ";

                if (computerBuffs[i].buff == "Regen")
                {
                    cout << "Regen ";
                }
                else if (computerBuffs[i].buff == "Lock")
                {
                    cout << "Lock ";
                }
                else if (computerBuffs[i].buff == "Peek")
                {
                    cout << "Peek ";
                }
                else if (computerBuffs[i].buff == "DoubleDamage")
                {
                    cout << "Double Damage ";
                }
            }
        }
        cout << endl;
        int buffIndex = index - 1;
        if (index > 0 && index <= computerBuffs.size() && !computerBuffs[index - 1].used) {
            applyBuff("Computer ", computerBuffs[buffIndex].buff, computerHealth, computerHealth, isPlayerTurnSkip, isLive, damage);
            computerBuffs[index - 1].used = true;
        }
        else {
            cout << "Invalid choice! Buff was canceled." << endl;
        }
    }

    int shootChoice = rand() % 2 + 1;

    cout << "The computer chooses to ";
    if (shootChoice == 1) {
        cout << "shoot itself." << endl;
    }
    else {
        cout << "shoot you." << endl;
    }



    if (shootChoice == 1) {
        if (isLive) {
            computerHealth = computerHealth - damage;
            cout << "The computer shot itself with a live bullet! Computer's health is now " << computerHealth << endl;
        }
        else {
            cout << "The computer shot itself with a blank bullet. Computer is safe!" << endl;
        }
    }
    else {
        if (isLive) {
            playerHealth = playerHealth - damage;
            cout << "The computer shot you with a live bullet! Your health is now " << playerHealth << endl;
        }
        else {
            cout << "The computer shot you with a blank bullet. You're safe!" << endl;
        }
    }
}


int main() {

    int playerHealth, computerHealth, damage;
    vector<bool> bullets;
    vector<BuffInfo> playerBuffs, computerBuffs;
    bool isPlayerTurnSkip = false, isCPUTurnSkip = false;

    cout << "--------------------------------" << endl;
    cout << "Welcome to Bullet Roulette!" << endl;
    cout << "--------------------------------" << endl;
    cout << "At the beginning of the game, 10 bullets are loaded into the gun.\n" << "6 bullets are live, and 4 are blank." << endl;

    while (true) {
        initializeGame(playerHealth, computerHealth, bullets, playerBuffs);
        initializeGame(playerHealth, computerHealth, bullets, computerBuffs);

        cout << "Buff given " << playerBuffs[0].buff << " and " << playerBuffs[1].buff << ".\n";
        damage = 1;
        while (playerHealth > 0 && computerHealth > 0 && !bullets.empty()) {

            isCPUTurnSkip = false;
            if (!isPlayerTurnSkip) {
                playerTurn(playerHealth, computerHealth, bullets, playerBuffs, isCPUTurnSkip, damage);
            }
            else {
                cout << "\nYour's turn is skipped due to Lock buff!" << endl;
            }

            if (playerHealth <= 0 || computerHealth <= 0 || bullets.empty()) {
                break;
            }

            isPlayerTurnSkip = false;
            if (!isCPUTurnSkip) {
                computerTurn(playerHealth, computerHealth, bullets, computerBuffs, isPlayerTurnSkip, damage);
            }
            else {
                cout << "Computer's turn is skipped due to Lock buff!" << endl;
            }

            damage = 1;
        }

        cout << endl;
        if (playerHealth <= 0) {
            cout << "You lost! The computer wins!" << endl;
        }
        else if (computerHealth <= 0) {
            cout << "You win! The computer is defeated!" << endl;
        }
        else {
            cout << "No more bullets left! It's a draw!" << endl;
        }

        int repeat;
        cout << "Do you want to play again ? (1) yes (2) no"; 
        cin >> repeat;

        if (repeat == 1)
        {
            cout << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}
