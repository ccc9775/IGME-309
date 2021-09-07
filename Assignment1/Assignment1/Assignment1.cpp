// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//IGME309-5
//Chase Call
//Assignment 01

#include <iostream>
using namespace std;

int main()
{
    //intro to the program
    cout << "Welcome to the HiLo Guessing Game!" << endl;
    cout << "Please guess a number between 1-100" << endl;

    //variables of the program
    srand(time(NULL));
    int guesses = 0;
    int number;
    int guessedNumber = 0;
    string input;
    bool toQuit = false;

    //randomize the number
    number = (rand() % 100) + 1;

    //while the player doesn't want to quit and the guessed number isn't correct
    while (guessedNumber != number && toQuit == false)
    {
        //tell the user to enter a number
        cout << endl << "Enter a Number(101 to quit): ";
        cin >> guessedNumber;
        
        //if the user wants to quit
        if (guessedNumber == 101) {
            cout << "You have selected to quit the game. Are you sure? (y/n);";
            cin >> input;

            //check to see if the user does want to quit. If they do, break the loop
            if (input == "y") {
                toQuit = true;
                break;
            }

        }
        //if the number is too low, say so
        else if (guessedNumber < number) {
            cout << "That guess was too low" << endl;
        }
        //if the number is too high, say so
        else if (guessedNumber > number) {
            cout << "That guess was too high" << endl;
        }
        //if you guessed the right number, tell the user and say their number of guesses
        else if (guessedNumber == number) {
            cout << "That guess was correct!" << endl;
            cout << "Number of guesses " << guesses << endl;

            //see if the user wants to play again
            cout << endl << "Would you like to play again? (y/n):";
            cin >> input;

            //if they want ot play again, reset the guesses and randomize the number
            if (input == "y") {
                guesses = 0;
                toQuit = false;
                number = (rand() % 100) + 1;
            }
            //if they don;t want to play again, break the loop
            else if (input == "n") {
                toQuit = true;
                break;
            }
        }

        //increase the guess amount
        guesses++;

    }

    return 0;
}


