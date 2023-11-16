#ifndef RPSP_H
#define RPSP_H

#include <vector>

class Game {
public:
    Game();

    void run();

private:
    int primeCounter;
    int playerHealth;
    int aiHealth;
    int maxHealth;
    int numberOfPrimes;

    int sieveOfE(int n);
    
    bool isPrime(int n);
    
    void displayHealthBar(int health, int maxHealth);
    
    void displayAsciiArt(char choice);
    
    int comparison(char input, char artificialInput, int primeCounter);
    
    std::vector<char> aiData(char input);
    
    void aiChoice(char& artificialInput, std::vector<char>& choices);
    
    void playRound();
};

#endif // RPSP_H
