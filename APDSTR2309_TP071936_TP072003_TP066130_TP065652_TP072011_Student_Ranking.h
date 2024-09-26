#pragma once
//  Student_Ranking.h

#ifndef STUDENT_RANKING_H
#define STUDENT_RANKING_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

bool stringCompare(string str1, string str2)
{
    if (str1.length() != str2.length())
        return false;

    for (int i = 0; i < str1.length(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }

    return true;
}

struct playerList
{
    string playerID;
    string playerName;
    string ques1;
    string ques2;
    string ques3;
    int markQues1;
    int markQues2;
    int markQues3;
    int totalMarks;
    int timeTaken;
    int rank;
    playerList* nextAddress;
    playerList* prevAddress;
}*head, * tail;


playerList* createNewStudent(string playerID, string playerName, string ques1, string ques2, string ques3, int markQues1, int markQues2, int markQues3, int totalMarks, int timeTaken)
{
    playerList* newStudent = new playerList;
    newStudent->playerID = playerID;
    newStudent->playerName = playerName;
    newStudent->ques1 = ques1;
    newStudent->ques2 = ques2;
    newStudent->ques3 = ques3;
    newStudent->markQues1 = markQues1;
    newStudent->markQues2 = markQues2;
    newStudent->markQues3 = markQues3;
    newStudent->totalMarks = totalMarks;
    newStudent->timeTaken = timeTaken;
    newStudent->nextAddress = nullptr; //NULL to nullptr
    newStudent->prevAddress = nullptr;

    return newStudent;
}


void RankingSorting(playerList* newStudent)
{
    //empty list
    if (head == nullptr){
        head = tail = newStudent;
    }
    //if the player's mark is higher than the current highest
    else if (newStudent->totalMarks > head->totalMarks){
        head->prevAddress = newStudent;
        newStudent->nextAddress = head;
        head = newStudent;
    }
    //if the player's mark is lower than the current lowest
    else if (newStudent->totalMarks < tail->totalMarks){
        tail->nextAddress = newStudent;
        newStudent->prevAddress = tail;
        tail = newStudent;
    }
    //if the mark is same higher but time is lesser
    else if (newStudent->totalMarks == head->totalMarks && newStudent->timeTaken < head->timeTaken){
        head->prevAddress = newStudent;
        newStudent->nextAddress = head;
        head = newStudent;
    }
    //if the mark is same lower but time is more
    else if (newStudent->totalMarks == tail->totalMarks && newStudent->timeTaken > tail->timeTaken){
        tail->nextAddress = newStudent;
        newStudent->prevAddress = tail;
        tail = newStudent;
}
    else{
        playerList* current = head->nextAddress;
        while (current != nullptr){//NULL to nullptr
            //if the mark is higher
            if (newStudent->totalMarks > current->totalMarks){
                current->prevAddress->nextAddress = newStudent;
                newStudent->nextAddress = current;
                newStudent->prevAddress = current->prevAddress;
                current->prevAddress = newStudent;
                break;
            }
            //if the mark is same but time is lesser
            else if (newStudent->totalMarks == current->totalMarks && newStudent->timeTaken < current->timeTaken){
                current->prevAddress->nextAddress = newStudent;
                newStudent->nextAddress = current;
                newStudent->prevAddress = current->prevAddress;
                current->prevAddress = newStudent;
                break;
            }
            //if marks and timing is same
            else if (newStudent->totalMarks == current->totalMarks && newStudent->timeTaken == current->timeTaken){
                current->nextAddress->prevAddress = newStudent;
                newStudent->prevAddress = current;
                newStudent->nextAddress = current->nextAddress;
                current->nextAddress = newStudent;
            }
            //if the player's mark is lower than the current lowest
            else if (newStudent->totalMarks < tail->totalMarks){
                tail->nextAddress = newStudent;
                newStudent->prevAddress = tail;
                tail = newStudent;
                // Update the previous tail node's nextAddress pointer
                newStudent->prevAddress->nextAddress = newStudent;
            }
            current = current->nextAddress;
        }
    }
}

//print player ranking
void displayLeaderboard()
{
    int listing = 1, flag = 0;
    playerList* current = head;
    if (current != nullptr){//NULL to nullptr
        cout << "Generating Leaderboard..." << endl;
        flag = 1;
    }

    while (current != nullptr){//NULL to nullptr
        cout << endl << string(100, '=') << endl;
        cout << left << "Rank " << setw(10) << listing << "Name: " << setw(20) << current->playerName << "Total Score: " << setw(10) << current->totalMarks << "Time Taken: " << setw(5) << current->timeTaken << "s" << endl;
        cout << "Question 1: " << current->ques1 << " (Score: " << setw(2) << current->markQues1 << setw(17) << ")" << endl;
        cout << "Question 2: " << current->ques2 << " (Score: " << setw(2) << current->markQues2 << setw(17) << ")" << endl;
        cout << "Question 3: " << current->ques3 << " (Score: " << setw(2) << current->markQues3 << setw(17) << ")" << endl;
        cout << string(100, '=') << endl;
        listing++;
        current = current->nextAddress;
    }
    if (flag != 1){
        cout << "No Players Record Exist" << endl;
    }
}

void displayRanking(){
    playerList* current = head;
    int listing = 1, flag = 0;
    if (current != nullptr)//NULL to nullptr
    {
        cout << "Generating Ranking..." << endl;
        flag = 1;
    }
    cout << endl << string(100, '-') << endl;
    do {

        cout << left << "Rank " << setw(5) << listing << setw(20) << current->playerName << "Total Score: " << setw(10) << current->totalMarks << "Time Taken: " << setw(5) << current->timeTaken << "s" << endl;
        current = current->nextAddress;
        listing++;
    } while (current != NULL && listing <= 30);

    if (flag != 1)
    {
        cout << "No Players Record Exist" << endl;
    }
    cout << string(100, '-') << endl << endl;
}


void searchPlayers()
{
    string searchInput;
    int flag = 0, rank = 1;
    cout << endl << "Player's Info (Name/Player ID): ";
    getline(cin, searchInput);
    cout << "Searching for player " << searchInput << "..." << endl << endl;
    playerList* current = head;
    while (current != nullptr)
    {
        current->rank = rank;
        if (stringCompare(searchInput, current->playerID) || stringCompare(searchInput, current->playerName))
        {
            cout << left << "ID: " << setw(10) << current->playerID << "Name: " << setw(25) << current->playerName << endl;
            cout << string(100, '-') << endl;
            cout << "Question 1: " << current->ques1 << " (Score: " << setw(2) << current->markQues1 << setw(17) << ")" << endl;
            cout << "Question 2: " << current->ques2 << " (Score: " << setw(2) << current->markQues2 << setw(17) << ")" << endl;
            cout << "Question 3: " << current->ques3 << " (Score: " << setw(2) << current->markQues3 << setw(17) << ")" << endl;
            cout << string(100, '-') << endl;
            cout << "Rank " << setw(8) << current->rank << "Total Score: " << current->totalMarks << endl << endl;
            flag = 1;
        }
        rank++;
        current = current->nextAddress;
    }
    if (flag == 0)
    {

        int choice;
        cout << "Player " << searchInput << " is not found. Do you want try another players? " << endl;
        cout << "1- Yes 2- No" << endl << "Enter Choice: ";
        cin >> choice;
        if (choice == 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            searchPlayers();
        }
        else if (choice != 2)
        {
            cout << "Invalid Input" << endl;
        }
    }
}

void leaderboardMenu(bool &exitGame){
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
    cout << "▌              Leaderboard Menu              ▐\n";
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    int choice;
    cout << "1. Top 30 Ranking\n2. Score-Based Leaderboard\n3. Search for your score\n4. Exit Game\n";
    cout << "Your choice: ";
    cin >> choice;
    cout << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1:
            displayRanking();
            break;
        case 2:
            displayLeaderboard();
            break;
        case 3:
            searchPlayers();
            break;
        case 4:
            exitGame = true;
            break;
        default:
            break;
    }
}

#endif //STUDENT_RANKING_HPP

