//game.h

#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
using namespace std;

#include "questions.cpp"
#include "questionDeck.cpp"
#include "Student.h"
#include "Student_Ranking.h"

void getStudentDetails();
void displayGameRules();
void initializeDefaultPlayers();
void startGame(string& name);
playerList* newStudent;
Student student;

// Rules and Feautures used in this game
void getStudentDetails() {
    string id, name;
    cout << "Please enter your Student ID: ";
    getline(cin, id);
    cout << "Please enter your name: ";
    getline(cin, name);
    student.setPlayerID(id);
    student.setPlayerName(name);
}

// Function to read questions from CSV and store them in a list
list<string> readQuestionsFromCSV(const string& filePath) {
    ifstream file(filePath);
    list<string> questions;
    string line;

    while (getline(file, line)) {
        questions.push_back(line);
    }

    file.close();
    return questions;
}

// Function to initialize default players
void initializeDefaultPlayers() {
    list<string> names = {
        "Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hannah", "Isaac", "Jack",
        "Karen", "Liam", "Mia", "Noah", "Olivia", "Peter", "Quincy", "Rachel", "Sophia", "Thomas",
        "Uma", "Victor", "Wendy", "Xander", "Yara", "Zane", "Amber", "Brian", "Catherine", "Dylan",
        "Ella", "Felix", "Georgia", "Henry", "Ivy", "Jason", "Kim", "Leo", "Megan", "Nathan",
        "Oscar", "Paula", "Quinn", "Riley", "Sam", "Tina", "Ulysses", "Violet", "Will", "Xena",
        "Yvonne", "Zach", "Anna", "Ben", "Chloe", "Daniel", "Elena", "Finn", "Gina", "Hank",
        "Isabel", "Jake", "Kylie", "Lucas", "Molly", "Nate", "Qing", "Meng", "Kai"
    };

    int marks[] = { 0, 8, 10 }; // Possible marks
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    // Read questions from CSV file
    list<string> questions = readQuestionsFromCSV("questions_only.csv");
    if (questions.size() < 3) {
        cerr << "Not enough questions in the CSV file." << endl;
        return;
    }

    for (int i = 3; i <= 69; ++i) {
        std::string id = "ID" + std::to_string(i);
        auto nameIt = names.begin();
        std::advance(nameIt, rand() % names.size());
        std::string name = *nameIt;

        // Randomly select 3 unique questions
        vector<string> selectedQuestions;
        for (int j = 0; j < 3; ++j) {
            auto questionIt = questions.begin();
            std::advance(questionIt, rand() % questions.size());
            selectedQuestions.push_back(*questionIt);
            questions.erase(questionIt); // Remove the question to avoid repetition
        }
        int mQ1 = marks[rand() % 3]; // Random marks from the set {0, 8, 10}
        int mQ2 = marks[rand() % 3];
        int mQ3 = marks[rand() % 3];
        int totalMarks = mQ1 + mQ2 + mQ3;
        int timeTaken = rand() % 201;

        playerList* newStudent = createNewStudent(id, name, selectedQuestions[0], selectedQuestions[1], selectedQuestions[2], mQ1, mQ2, mQ3, totalMarks, timeTaken);
        RankingSorting(newStudent);
    }
}

void displayGameRules() {
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
    cout << "▌          Game Rules         ▌\n";
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "1.  You will be participating in three rounds of the game." << endl;
    cout << "2.  In each round, you will have the opportunity to answer one question." << endl;
    cout << "3.  You can choose to draw a question card from the deck of unanswered questions or select from the pile of discarded cards." << endl;
    cout << "4.  If you answer a question correctly, you will receive the full score stated on the card." << endl;
    cout << "5.  If you answer a question from a discarded card, you will receive 80% of the overall score." << endl;
    cout << "6.  After answering a question, you must place the answered question card on top of the answered card deck." << endl;
    cout << "7.  If you choose not to answer a question, the card will be discarded to the end of the deck of discarded cards." << endl;
    cout << "8.  After three rounds or when all questions are answered, the top 30 winners will be announced and displayed in a hierarchical chart." << endl;
    cout << "9.  Additionally, your scores from each round, along with the questions answered, will be displayed on a leaderboard." << endl;
    cout << "10. Use the search function to find your name in the winners' chart and to identify your scores and performance in the leaderboard." << endl << endl;
    cout << "~~~~~  Good luck, and may the best player win!  ~~~~~" << endl << endl;
}


void startGame(string& name, bool& playerDone, questionDeck& qdeck){
    string playerID;
    string ques1;
    string ques2;
    string ques3;
    string anyKey;
    cout << "Enter any key when you are ready to start the game. ";
    getline(cin, anyKey);
    cout << "Game starting..." << endl << endl;
    
    for (int round = 1; round <= 3; ++round)
    {
        int userScore = 0;
        if (round == 1) { //start the Timer
            student.startTimer();
        }
        
        question* currentQuestion = qdeck.popUnanswered();
        if (currentQuestion == nullptr) {
            cout << "No more questions to answer." << endl;
            break;
        }
        cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
        cout << "  Round " << round << " for " << student.getPlayerName() << " \n";
        cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";

        // Display discarded cards (if any)
        cout << "Discarded Cards: " << endl;
        int answer;
        if (!qdeck.DisplayDiscardedQuestions()) //if no discarded question, auto proceed to unanswered
        {
            answer = 1;
        }
        else {
            cout << "Do you want to answer from the unanswered deck or the discarded deck ?" << endl;
            cout << "1) Unanswered Deck\n2) Discarded Deck" << endl;
            cout << "Your choice: ";
            cin >> answer;
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << endl;
        }
        
        // Validate user input
        while (answer != 1 && answer != 2) {
            cout << "Invalid input. Please enter '1' for unanswered or '2' for discarded.\nYour choice:  ";
            cin >> answer;
            cin.clear();
            cout << endl;
        }
        
        if (answer == 1) {
            //cout << "------------------ Answering from unanswered deck ------------------" << endl;
            cout << "Question: " << currentQuestion->quest << endl;
            cout << "Options: \n" << currentQuestion->opt << endl;
            
            string userAnswer;
            bool validAnswer = false;
            while (!validAnswer) {
                cout << "Enter your answer (Enter 0 to skip the question): ";
                getline(cin, userAnswer);
                
                if (userAnswer.length() == 1 &&
                    (userAnswer == "a" || userAnswer == "A" ||
                     userAnswer == "b" || userAnswer == "B" ||
                     userAnswer == "c" || userAnswer == "C" ||
                     userAnswer == "d" || userAnswer == "D" ||
                     userAnswer == "0")) {
                    validAnswer = true;
                }
                else {
                    cout << "Invalid input. Please enter A, B, C, D, or 0." << endl;
                }
                
            }
            
            if (userAnswer != "0") {
                //cout << "Answering Question..." << endl;
                //the last parameter 'questionNum' is used when choice == 2, when choice == 1 , set it to 0 and ignore usage
                qdeck.AnswerQuestion(currentQuestion->quest, userAnswer, answer, userScore, 0);
            }
            else {
                cout << "Skipping Question..." << endl;
                qdeck.enqueue(currentQuestion);
            }
            
            switch (round)
            {
                case 1:
                    student.setQues1(currentQuestion->quest);
                    student.setMarkQues1(userScore);
                    break;
                case 2:
                    student.setQues2(currentQuestion->quest);
                    student.setMarkQues2(userScore);
                    break;
                case 3:
                    student.setQues3(currentQuestion->quest);
                    student.setMarkQues3(userScore);
                    break;
                default:
                    break;
            }
            
        }
        else if (answer == 2) {
            //cout << "------- Answering from discarded deck -------" << endl;
            //qdeck.DisplayDiscardedQuestions();
            
            bool questionFound = false;
            while (!questionFound) {
                cout << "Enter the number of the question that you want to answer: ";
                int discardedQuestionNumber;
                cin >> discardedQuestionNumber;
                cout << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (cin.fail()) {
                    cout << "Invalid input. Please try again." << endl << endl;
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    continue;
                }
                
                question* selectedQuestion = qdeck.getDiscardedQuestionByNumber(discardedQuestionNumber);
                if (selectedQuestion != nullptr) {
                    questionFound = true;
                    cout << "Question: " << selectedQuestion->quest << endl;
                    cout << "Options: \n" << selectedQuestion->opt << endl;
                    
                    string userAnswer;
                    bool validAnswer = false;
                    while (!validAnswer) {
                        cout << "\nEnter your answer (Enter 0 to skip the question): ";
                        getline(cin, userAnswer);
                        
                        if (userAnswer.length() == 1 &&
                            (userAnswer == "a" || userAnswer == "A" ||
                             userAnswer == "b" || userAnswer == "B" ||
                             userAnswer == "c" || userAnswer == "C" ||
                             userAnswer == "d" || userAnswer == "D" ||
                             userAnswer == "0")) {
                            validAnswer = true;
                        }
                        else {
                            cout << "Invalid input. Please enter A, B, C, D, or 0." << endl;
                        }
                    }
                    
                    if (userAnswer != "0") {
                        //cout << "Answering Question..." << endl;
                        qdeck.AnswerQuestion(selectedQuestion->quest, userAnswer, answer, userScore, discardedQuestionNumber);
                    }
                    else {
                        cout << "Skipping Question..." << endl;
                        // Optionally handle the skipping logic for discarded questions here
                    }
                    
                    switch (round)
                    {
                        case 1:
                            student.setQues1(selectedQuestion->quest);
                            student.setMarkQues1(userScore);
                            break;
                        case 2:
                            student.setQues2(selectedQuestion->quest);
                            student.setMarkQues2(userScore);
                            break;
                        case 3:
                            student.setQues3(selectedQuestion->quest);
                            student.setMarkQues3(userScore);
                            break;
                        default:
                            break;
                    }
                } else {
                    cout << "Question not found. Please try again" << endl << endl;
                    questionFound = false;
                }
            }
        }
        
        if (round == 3) {
            student.stopTimer();
            // Calculate total marks and time taken
            // Create a new player and add to ranking list
            newStudent = createNewStudent(student.getPlayerID(), student.getPlayerName(),
                student.getQues1(), student.getQues2(),student.getQues3(),
                student.getMarkQues1(),student.getMarkQues2(), student.getMarkQues3(),
                student.getTotalMarks(), student.getTimeTaken());
            RankingSorting(newStudent);
            playerDone = true;
            break;
        }
    }
}
#endif // GAME_HPP
