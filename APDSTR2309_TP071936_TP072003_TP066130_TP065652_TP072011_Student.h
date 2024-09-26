
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <list>
#include <chrono> // Library for time measurement
#include "APDSTR2309_TP071936_TP072003_TP066130_TP065652_TP072011_Student_Ranking.h"

using namespace std;

class Student {
private:
    string playerID;
    string playerName;
    string ques1;
    string ques2;
    string ques3;
    int markQues1;
    int markQues2;
    int markQues3;
    int totalMarks;
    double timeTaken;
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point endTime;
    
public:
    // Constructor
    Student() {}
    Student(string id, string name, string q1, string q2, string q3, int mQ1, int mQ2, int mQ3, int tMarks, double tTime)
    : playerID(id), playerName(name), ques1(q1), ques2(q2), ques3(q3), markQues1(mQ1), markQues2(mQ2), markQues3(mQ3), totalMarks(tMarks), timeTaken(tTime) {}
    
    // Getters
    string getPlayerID() const{return playerID;}
    string getPlayerName() const{return playerName;}
    string getQues1() const{return ques1;}
    string getQues2() const{return ques2;}
    string getQues3() const{return ques3;}
    
    int getMarkQues1() const{return markQues1;}
    int getMarkQues2() const{return markQues2;}
    int getMarkQues3() const{return markQues3;}
    int getTotalMarks() const{return markQues1 + markQues2 + markQues3;}
    double getTimeTaken() const{return timeTaken;}
    
    // Setters
    void setPlayerID(const string& id){playerID = id;}
    void setPlayerName(const string& name){playerName = name;}
    void setQues1(const string& q1){ques1 = q1;}
    void setQues2(const string& q2){ques2 = q2;}
    void setQues3(const string& q3){ques3 = q3;}
    void setMarkQues1(int mQ1){markQues1 = mQ1;}
    void setMarkQues2(int mQ2){markQues2 = mQ2;}
    void setMarkQues3(int mQ3){markQues3 = mQ3;}
    void setTimeTaken(double tTime){timeTaken = tTime;}
    
    //function to start the timer after the player select the first question
    void startTimer()
    {
        startTime = chrono::steady_clock::now();
    }
    
    //function to stop the timer
    void stopTimer()
    {
        endTime = chrono::steady_clock::now();
        timeTaken = calculateTimeTaken();
    }
    
    //function to calculate the time taken (in milliseconds)
    long long calculateTimeTaken()
    {
        chrono::duration<double> timeElapsed = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        return timeElapsed.count();
    }
    
};
#endif // STUDENT_HPP

#pragma once
