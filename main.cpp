// main.cpp

#include "game.h"
#include "Student.h"
#include "Student_Ranking.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


int main() {
    bool exitGame = false;
    int choice, numPlayers;
    string name;
        // Access the question.csv files
        questionList qlist;
        if (!qlist.readQuestionsFromFile("APDSTR2309_TP071936_TP072003_TP066130_TP065652_TP072011_questions.csv", qlist)) {
            cerr << "Failed to read questions from file." << endl;
            return 1;
        }
        
        // Initialize the question deck once
        questionDeck qdeck(qlist);
        
        // Display 3 default discarded questions
        auto q287 = make_unique<question>();
        q287->quest = "Describe the process of balancing factors in a red-black tree.";
        q287->opt = "A) By rotating nodes to maintain balance factors.\n"
        "B) By using recursion.\n"
        "C) By inserting elements randomly.\n"
        "D) By rearranging elements in ascending order.";
        q287->ans = "A";
        qdeck.enqueue(q287.get());
        
        auto q299 = make_unique<question>();
        q299->quest = "How do you implement a Cartesian tree using a stack?";
        q299->opt = "A) Use a stack to keep track of parent-child relationships while constructing the tree.\n"
        "B) Use a stack to perform depth-first traversal and construct the tree recursively.\n"
        "C) Use a stack to perform breadth-first traversal and construct the tree iteratively.\n"
        "D) Use a stack to store elements and pop them to construct the tree from bottom to top.";
        q299->ans = "B";
        qdeck.enqueue(q299.get());
        
        auto q300 = make_unique<question>();
        q300->quest = "How do you detect a cycle in a linked list?";
        q300->opt = "A) By checking if any two nodes have the same data.\n"
        "B) By using a stack.\n"
        "C) By using Floyd's cycle detection algorithm.\n"
        "D) By traversing the list twice.";
        q300->ans = "C";
        qdeck.enqueue(q300.get());
        
        qdeck.ShuffleDeck(); // shuffle the question
        
        // Initialize the default players
        initializeDefaultPlayers();
        
        cout << "\n▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
        cout << "\n▌     Welcome to the Data Structure and Algorithms Trivial Pursuit Card Game     ▌\n";
        cout << "\n▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
        
        cout << "Please enter the total number of players: ";
        cin >> numPlayers;
        cout << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        
        while (!exitGame)
        {
            for (int i = 0; i < numPlayers; i++)
            {
                bool playerDone = false;
                cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
                cout << "▌              Player " << (i + 1) << "'s turn               ▐\n";
                cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
                
                getStudentDetails();
                
                while (!playerDone)
                {
                    cout << endl << "Hello " << student.getPlayerName() << "!" << endl;
                    cout << "Please select an option below: \n";
                    cout << "1. Start Game\n2. Game Rules\n3. Exit\n";
                    cout << "Your choice: ";
                    cin >> choice;
                    cout << endl;
                    
                    // Validate user input
                    while (cin.fail() || choice < 1 || choice > 3) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid Input. Please try again and enter a number between 1 and 3!\nYour choice: ";
                        cin >> choice;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (choice)
                    {
                        case 1:
                        {
                            startGame(name, playerDone, qdeck);
                            break;
                        }
                        case 2:
                        {
                            displayGameRules();
                            break;
                        }
                        case 3:
                        {
                            playerDone = true;
                            exitGame = true;
                            cout << "You've exit the game. Byebye\n";
                            break;
                        }
                        default:
                        {
                            cout << "Invalid Input. Please Try Again\n";
                            break;
                        }
                    }
                }
                if (playerDone)
                {
                    cout << "------------------ Game finished for " << student.getPlayerName() << " ------------------" << endl << endl;
                }
                
                if (i + 1 == numPlayers) {
                    cout << "The game has ended. Thank you for playing!" << endl;
                    // Display Ranking and Leaderboard information
                    while (!exitGame) {
                        leaderboardMenu(exitGame);
                    }
                }
            }
        }
    
    return 0;
}
