#ifndef RPSP_H
#define RPSP_H

#include <vector>


class Game {
public:
    Game();

    int run();

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
    
    void aiData(char input);
    
    void initAIChoices();
    
    void aiChoice(char& artificialInput, char input);
    
    int playRound();
};

#endif // RPSP_H