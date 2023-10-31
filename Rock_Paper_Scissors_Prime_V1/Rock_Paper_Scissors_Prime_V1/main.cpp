/* Noah Scott
 * 10-27-23
 * CiS-17C
 * Project 1 
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

    

    vector<char> choices = {'r', 'p', 's'};

    

    if (input == 'r'){

        choices.push_back('p');

    }

    

    if (input == 'p'){

        choices.push_back('s');

    }

    

    if (input == 's'){

        choices.push_back('r');

    }

    

    else{

        return choices;

    }

    

    return choices;

    

    

}



void aiChoice(char& artificialInput, vector<char>& choices) {

    

    int random_index = rand()  % choices.size();

    

    artificialInput = choices[random_index];

    

    

    

}









int main() {

    

    srand(static_cast<unsigned int> (time(nullptr)));

    

    

    int t = 0;

    

    char input, artificialInput;

    

    

    cout << "Number of rounds?" << endl;

    

    cin >> t;

    

    for (int i = 0; i < t; i++){

        input = 0;

        

        vector<char> choices = aiData(input);

        

        aiChoice(artificialInput, choices);

        

        cout << "Input r for rock, p for paper, or s for scissors." << endl;

        

        cin >> input;

        

        aiData(input);

        

        int result = comparison(input, artificialInput);

        

        if (result == 1){

            cout << "Player Wins!" << endl;

            cout << endl;

            cout << "Your Choice: " << input << endl;

            cout << endl;

            cout << "AI Choice: " << artificialInput << endl;

            cout << endl;

        }

        

        if (result == 0){

            cout << "AI Wins!" << endl;

            cout << endl;

            cout << "Your Choice: " << input << endl;

            cout << endl;

            cout << "AI Choice: " << artificialInput << endl;

            cout << endl;

        }

        

        if (result == 3){

            cout << "Draw!" << endl;

            cout << endl;

            cout << "Your Choice: " << input << endl;

            cout << endl;

            cout << "AI Choice: " << artificialInput << endl;

            cout << endl;

        }

        

        

    }

    

    

    

    return 0;

}
