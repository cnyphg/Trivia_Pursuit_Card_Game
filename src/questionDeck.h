//questionDeck.h
#pragma once
#ifndef QUESTIONDECK_H
#define QUESTIONDECK_H

#include "questions.h"
#include <cstdlib>
#include <ctime>
#include <unordered_set>
using namespace std;

class questionDeck {
private:
    questionList qlist;
    question* questionsHead = nullptr;
    question* questionsTail = nullptr;

    struct StackNode { // Stack for questions
        question* data;
        StackNode* next;
        StackNode(question* q) : data(q), next(nullptr) {}
    };
    StackNode* unansweredHead = nullptr;
    StackNode* answeredHead = nullptr;

    struct QueueNode { // Queue for discarded questions
        question* data;
        QueueNode* next;
        QueueNode(question* q) : data(q), next(nullptr) {}
    };

    QueueNode* discardedFront = nullptr;
    QueueNode* discardedRear = nullptr;

public:
    explicit questionDeck(const questionList& list);
    ~questionDeck();

    void ShuffleDeck();
    void DisplayUnansweredQuestions() const;
    void AnswerQuestion(const string& quest, const string& ans, const int choice, int& score, int questionNum);
    void DisplayAnsweredQuestions() const;
    bool DisplayDiscardedQuestions() const;
    void DiscardRandomQuestions(int count);

    //stack & queue operations
    void pushUnanswered(question* q);
    question* popUnanswered();
    void pushAnswered(question* q);
    question* popAnswered();
    void enqueue(question* q);
    question* dequeue();
    question* dequeueSpecific(question* q); 
    int countQuestions() const;
    question* getDiscardedQuestionByNumber(int number);
};

#endif // QUESTIONDECK_HPP#pragma once









