/* Noah Scott
 * 10-27-23
 * CiS-17C
 * Project 1
 *
 * This versions includes sieve and isPrime functions to make the PRIME aspect of this game
 * function
 *
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

int sieveOfE(const int n) {
    if (n < 2) {
        return 0; // No primes less than 2
    }

    bool* primeList = new bool[n + 1];
    memset(primeList, true, n + 1); // Initialize all elements to true

    primeList[0] = primeList[1] = false; // 0 and 1 are not prime numbers

    for (int p = 2; p * p <= n; p++) {
        if (primeList[p]) {
            for (int i = p * p; i <= n; i += p) {
                primeList[i] = false;
            }
        }
    }

    int primeCount = 0;
    for (int i = 2; i <= n; i++) {
        if (primeList[i]) {
            primeCount++;
        }
    }

    delete[] primeList; // Deallocate the memory 
    return primeCount;
}


bool isPrime(int n) {
    
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void displayHealthBar(int health, int maxHealth) {
    int barWidth = 20; // Width of the health bar
    int healthUnits = (health * barWidth) / maxHealth; // Calculate the number of '#' characters
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < healthUnits) {
            cout << "#"; // Health remaining
        }
        else {
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
     case '1': // Assuming '1' is the character for PRIME
         cout <<
                "    /\\  \n"
                "   /  \\ \n"
                "  /____\\ \n"
                "  \\    / \n"
                "   \\  /  \n"
                "    \\/   \n";
         break;

    default:
        cout << "Invalid choice\n";
        break;
    }
}

int comparison(char input, char artificialInput, int primeCounter) {

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
    
    if (input == '1') {
        if (isPrime(primeCounter)) {
            
            return 2;
            
        }
        
        else {
            cout << endl << "Prime Counter is not prime your choice will count as ROCK" << endl;
            
            input = 'r';
            
            return comparison(input, artificialInput, primeCounter);
            
        }
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
    int numberOfPrimes = 0;
    
    char input, artificialInput;


    while (playerHealth > 0 && aiHealth > 0) {
        cout << "Your health: " << endl;
        displayHealthBar(playerHealth, maxHealth);
        cout << endl << "A.I. health: " << endl;
        displayHealthBar(aiHealth, maxHealth);
        cout << endl << "Prime: " << primeCounter << endl;
        cout << endl << boolalpha << "Prime number is prime: " << isPrime(primeCounter) << endl << endl; //This is for debugging purposes
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
        int result = comparison(input, artificialInput, primeCounter);
        
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
            primeCounter = rand() % 100;
        }
        
        else if (result == 2){
            cout << "PRIME has been casted!" << endl;
            numberOfPrimes = sieveOfE(primeCounter);
            
            aiHealth -= 25*numberOfPrimes;
            
        }
        
        if (aiHealth <= 0) {

            cout << endl << "You win!" << endl;

        }

        if (playerHealth <= 0) {
            cout << endl << "You lost!" << endl;

        }
        cout << endl;
    }

    return 0;
}