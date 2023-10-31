/* Noah Scott
 * 10-27-23
 * CiS-17C
 * Project 1 
 * 
 * This is version 2 of the project which 
 * implements a health system and a prime counter.
 * the prime counter will become more relevant as 
 * the this code progresses but for now it is here as a 
 * early adoption to get a feel.
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

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
    int t = 0;
    int playerHealth = 100;
    int aiHealth = 100;

    char input, artificialInput;

   /* cout << "Number of rounds?" << endl;

    cin >> t;
                */

    while (playerHealth != 0 && aiHealth != 0) {
        cout << "Your health is " << playerHealth << endl;
        cout << "ai health is " << aiHealth << endl;
        cout << "Prime: " << primeCounter << endl;

        input = 0;

        vector<char> choices = aiData(input);

        aiChoice(artificialInput, choices);

        cout << "Input r for rock, p for paper, or s for scissors." << endl;

        cin >> input;
        cout << endl;

        aiData(input);

        int result = comparison(input, artificialInput);

        if (result == 1) {
            aiHealth -= 25;

            cout << "ai took damage." << endl;
  /*          cout << "Player Wins!" << endl;
            cout << endl;
            cout << "Your Choice: " << input << endl;
            cout << endl;
            cout << "AI Choice: " << artificialInput << endl;
            cout << endl;    */

        }

        if (result == 0) {
            playerHealth -= 25;
            cout << " You took damage." << endl;
     /*       cout << "AI Wins!" << endl;
            cout << endl;
            cout << "Your Choice: " << input << endl;
            cout << endl;
            cout << "AI Choice: " << artificialInput << endl;
            cout << endl;  */

        }



        if (result == 3) {
            cout << "Prime!" << endl;
            primeCounter++;
       /*     cout << "Draw!" << endl;
            cout << endl;
            cout << "Your Choice: " << input << endl;
            cout << endl;
            cout << "AI Choice: " << artificialInput << endl;
            cout << endl;  */

        }

        if (aiHealth == 0) {

            cout << "You win" << endl;
            
        }

        if (playerHealth == 0) {
            cout << "You lost" << endl;
            
        }
        cout << endl; 
    }

       return 0;
}

