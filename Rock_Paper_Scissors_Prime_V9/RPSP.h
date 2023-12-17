/* 
 * File:   RPSP.h
 * Author: NoahP
 *
 * Created on December 17, 2023, 1:14 PM
 */

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

    void aiData(char playerMove);

    void initAIChoices();

    char aiChoice();

    int playRound();
};

#endif

