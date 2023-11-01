/* Noah Scott
 * 10-27-23
 * CiS-17C
 * Project 1
 *
 * This version of the code adds in some ASCII Art for the sake of
 * making the program a bit more polished. I also made the prime counter
 * generate a random number each time and will eventually add a sieve to find the number of primes
 * from 2 to n where n is the number from our prime counter. If the n is prime and
 * the player chooses to use the prime attack then the damage the player does is the number
 * of primes found from 2 to n multiplied by 10.
 *
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;


void displayHealthBar(int health, int maxHealth) {
    int barWidth = 20; // Width of the health bar
    int healthUnits = (health * barWidth) / maxHealth; // Calculate the number of '#' characters
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < healthUnits) {
            cout << "#"; // Health remaining
        } else {
            cout << "-"; // Health lost
        }
    }
    cout << "] " << health << " / " << maxHealth << endl; // Display current health and max health
}




void displayAsciiArt(char choice) {
    switch (choice) {
        case 'r':
            cout <<
                 "    _______\n"
                 "---'   ____)\n"
                 "      (_____)\n"
                 "      (_____)\n"
                 "      (____)\n"
                 "---.__(___)\n";
            break;
        case 'p':
            cout <<
                 "    _______\n"
                 "---'   ____)____\n"
                 "          ______)\n"
                 "          _______)\n"
                 "         _______)\n"
                 "---.__________)\n";
            break;
        case 's':
            cout <<
                 "    _______\n"
                 "---'   ____)____\n"
                 "          ______)\n"
                 "       __________)\n"
                 "      (____)\n"
                 "---.__(___)\n";
            break;
        default:
            cout << "Invalid choice\n";
            break;
    }
}

int comparison(char input, char artificialInput) {

    if (input == 'r' && artificialInput == 's') {
        return 1;

    }

    if (input == 'r' && artificialInput == 'p') {
        return 0;

    }

    if (input == 'p' && artificialInput == 'r') {
        return 1;

    }

    if (input == 'p' && artificialInput == 's') {
        return 0;

    }

    if (input == 's' && artificialInput == 'p') {
        return 1;

    }

    if (input == 's' && artificialInput == 'r') {
        return 0;

    }

    else {
        return 3;

    }

}

vector<char> aiData(char input) {

    vector<char> choices = { 'r', 'p', 's' };

    if (input == 'r') {
        choices.push_back('p');

    }

    if (input == 'p') {
        choices.push_back('s');

    }

    if (input == 's') {
        choices.push_back('r');

    }

    else {
        return choices;

    }

    return choices;

}

void aiChoice(char& artificialInput, vector<char>& choices) {

    int random_index = rand() % choices.size();

    artificialInput = choices[random_index];

}

int main() {

    srand(static_cast<unsigned int> (time(nullptr)));
    int primeCounter = 0;
    int playerHealth = 100;
    int aiHealth = 100;
    int maxHealth = 100;

    char input, artificialInput;


    while (playerHealth != 0 && aiHealth != 0) {
        cout << "Your health: "  << endl;
        displayHealthBar(playerHealth, maxHealth);
        cout << endl <<  "A.I. health: " << endl;
        displayHealthBar(aiHealth, maxHealth);
        cout << endl << "Prime: " << primeCounter << endl;

        input = 0;

        vector<char> choices = aiData(input);

        aiChoice(artificialInput, choices);

        cout << "Input r for rock, p for paper, or s for scissors." << endl;

        cin >> input;
        cout << endl << "Your choice: " << endl;
        displayAsciiArt(input);
        aiData(input);
        cout << endl << "A.I. choice: " << endl;
        displayAsciiArt(artificialInput);
        int result = comparison(input, artificialInput);

        if (result == 1) {
            aiHealth -= 25;

            cout << "ai took damage." << endl;

        }

        else if (result == 0) {
            playerHealth -= 25;
            cout << " You took damage." << endl;


        }



        else if (result == 3) {
            cout << "Prime!" << endl;
            primeCounter = rand() %100;
        }

         if (aiHealth == 0) {

            cout << endl <<  "You win!" << endl;

        }

        if (playerHealth == 0) {
            cout << endl << "You lost!" << endl;

        }
        cout << endl;
    }

    return 0;
}
