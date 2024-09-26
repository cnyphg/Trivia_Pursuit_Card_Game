//questions.h

#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct question {
    string quest;
    string opt;
    string ans;
    question* next;
};

class questionList {
    question* head = nullptr;
    int size = 0;

public:
    questionList() {}

    question* createNewNode(const string& quest, const string& opt, const string& ans);
    void InsertToEnd(const string& quest, const string& opt, const string& ans);
    void DisplayQuestions() const;
    string formatString(const string& str) const;
    bool CheckAnswer(const string& quest, const string& userAnswer) const;
    question* getHead() const { return head; }
    bool readQuestionsFromFile(const std::string& filename, questionList& qlist);
};

#endif // QUESTIONS_HPP
#pragma once




