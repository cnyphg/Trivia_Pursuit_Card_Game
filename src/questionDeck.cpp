//questionDeck.cpp

#include "questionDeck.h"
using namespace std;

questionDeck::questionDeck(const questionList& list) : qlist(list) {
    question* current = qlist.getHead();
    while (current != nullptr) {
        question* newQuestion = new question(*current);
        newQuestion->next = nullptr;
        if (questionsTail) {
            questionsTail->next = newQuestion;
            questionsTail = newQuestion;
        }
        else {
            questionsHead = questionsTail = newQuestion;
        }
        current = current->next;
    }

    // Initialize unanswered stack with all questions
    current = questionsHead;
    while (current != nullptr) {
        pushUnanswered(current);
        current = current->next;
    }
}

questionDeck::~questionDeck() {
    while (unansweredHead) {
        StackNode* temp = unansweredHead;
        unansweredHead = unansweredHead->next;
        delete temp;
    }
    while (answeredHead) {
        StackNode* temp = answeredHead;
        answeredHead = answeredHead->next;
        delete temp;
    }
    while (discardedFront) {
        QueueNode* temp = discardedFront;
        discardedFront = discardedFront->next;
        delete temp;
    }
    while (questionsHead) {
        question* temp = questionsHead;
        questionsHead = questionsHead->next;
        delete temp;
    }
}

void questionDeck::ShuffleDeck() {
    if (!questionsHead || !questionsHead->next) {
        return; // No need to shuffle if 0 or 1 questions
    }

    // Count the number of questions
    int count = countQuestions();

    // Create an array of pointers to questions
    question** arr = new question * [count];
    question* current = questionsHead;
    for (int i = 0; i < count; i++) {
        arr[i] = current;
        current = current->next;
    }

    // Declare and initialize discardedSet
    unordered_set<question*> discardedSet;

    // Store discarded questions in a set
    QueueNode* discardCurrent = discardedFront; // Assuming discardedFront is the front of the discarded deck
    while (discardCurrent) {
        discardedSet.insert(discardCurrent->data);
        discardCurrent = discardCurrent->next;
    }

    // Shuffle the array, excluding discarded questions
    srand(time(0));
    int shuffledCount = 0;
    for (int i = count - 1; i > 0 && shuffledCount < count; i--) {
        if (discardedSet.find(arr[i]) == discardedSet.end()) {
            int j = rand() % (i + 1);
            if (discardedSet.find(arr[j]) == discardedSet.end()) {
                swap(arr[i], arr[j]);
                shuffledCount++;
            }
        }
    }
    // Rebuild the linked list with the shuffled questions
    questionsHead = arr[0];
    current = questionsHead;
    for (int i = 1; i < count; i++) {
        current->next = arr[i];
        current = current->next;
    }
    current->next = nullptr;
    questionsTail = current;

    // Push the shuffled questions into the unanswered deck stack, avoiding those in the discarded queue
    unansweredHead = nullptr;
    for (int i = 0; i < count; i++) {
        if (discardedSet.find(arr[i]) == discardedSet.end()) {
            pushUnanswered(arr[i]);
        }
    }
    delete[] arr;
}

void questionDeck::DisplayUnansweredQuestions() const {
    if (!unansweredHead) {
        cout << "No unanswered questions to display." << endl;
        return;
    }

    StackNode* current = unansweredHead;
    int questionNumber = 1;
    while (current) {
        question* q = current->data;
        cout << "Question " << questionNumber++ << ": " << q->quest << endl;
        cout << "Options: \n" << q->opt << endl;
        cout << "Answer: " << q->ans << endl;
        cout << endl;
        current = current->next;
    }
}

void questionDeck::AnswerQuestion(const string& quest, const string& ans, const int choice, int& score, int questionNum) {
    question* current = questionsHead;
    question* prev = nullptr;
    score = 0;
    while (current) {
        if (current->quest == quest) {
            bool correct = qlist.CheckAnswer(quest, ans);
            if (choice == 1) {
                // Answer from unanswered deck
                if (correct) {
                    score = 10;
                    // If the question was answered correctly, pop it from the unanswered deck
                    popAnswered();
                    pushAnswered(current); // Push the answered question into the answered stack
                    cout << "Correct! 10 point earned!" << endl;
                }
                else {
                    enqueue(current); // Store the discarded question
                    cout << "Incorrect!" << endl;
                }
            }
            else if (choice == 2) {
                // Answer from discarded deck
                if (correct) {
                    score = 8;
                    cout << "Discarded question answered correctly! 8 point earned " << endl;
                    // If the question was answered correctly, dequeue it from the discarded queue
                    question* discardedQuestion = getDiscardedQuestionByNumber(questionNum);
                    if (discardedQuestion) {
                        dequeueSpecific(discardedQuestion);
                        pushAnswered(discardedQuestion); // Push the answered question into the answered stack
                        //cout << "Discarded question answered correctly! 8 point earned " << endl;
                        
                        
                    }
                }
                else {
                    cout << "Incorrect! Question remains in the discarded deck." << endl;
                }
            }
            else {
                cout << "Invalid choice!" << endl;
            }
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Question not found!" << endl;
}

void questionDeck::DisplayAnsweredQuestions() const {
    if (!answeredHead) {
        cout << "No questions have been answered correctly." << endl;
        return;
    }

    StackNode* current = answeredHead;
    int questionNumber = 1;
    while (current) {
        question* q = current->data;
        cout << "Question " << questionNumber++ << ": " << q->quest << endl;
        cout << "Options: \n" << q->opt << endl;
        cout << "Answer: " << q->ans << endl;
        cout << endl;
        current = current->next;
    }
}

bool questionDeck::DisplayDiscardedQuestions() const {
    if (!discardedFront) {
        cout << "Opps... No questions have been discarded" << endl;
        cout << "You will be given a question from unanswered deck" << endl << endl;
        return false;
    }

    int questionNumber = 1;
    QueueNode* current = discardedFront;
    while (current) {
        question* q = current->data;
        cout << "Question " << questionNumber++ << ": " << q->quest << endl;
        cout << "Options: \n" << q->opt << endl;
        cout << endl;
        current = current->next;
    }
    return true;
}

void questionDeck::DiscardRandomQuestions(int count) {
    int totalQuestions = countQuestions();
    if (totalQuestions == 0) return;

    question** arr = new question * [totalQuestions];
    question* current = questionsHead;
    for (int i = 0; i < totalQuestions; i++) {
        arr[i] = current;
        current = current->next;
    }

    srand(static_cast<unsigned int>(time(0)));
    for (int i = totalQuestions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }

    for (int i = 0; i < count && i < totalQuestions; ++i) {
        enqueue(arr[i]);
    }
    delete[] arr;
}

void questionDeck::pushUnanswered(question* q) {
    StackNode* newNode = new StackNode(q);
    newNode->next = unansweredHead;
    unansweredHead = newNode;
}

question* questionDeck::popUnanswered() {
    if (!unansweredHead) {
        return nullptr;
    }
    StackNode* temp = unansweredHead;
    unansweredHead = unansweredHead->next;
    question* poppedQuestion = temp->data;
    delete temp;
    return poppedQuestion;
}

void questionDeck::pushAnswered(question* q) {
    StackNode* newNode = new StackNode(q);
    newNode->next = answeredHead;
    answeredHead = newNode;
}

question* questionDeck::popAnswered() {
    if (!answeredHead) {
        return nullptr;
    }
    StackNode* temp = answeredHead;
    answeredHead = answeredHead->next;
    question* poppedQuestion = temp->data;
    delete temp;
    return poppedQuestion;
}

void questionDeck::enqueue(question* q) {
    QueueNode* newNode = new QueueNode(q);
    if (!discardedRear) {
        discardedFront = discardedRear = newNode;
    }
    else {
        discardedRear->next = newNode;
        discardedRear = newNode;
    }
}

// Not Used
question* questionDeck::dequeue() {
    if (!discardedFront) {
        return nullptr;
    }
    QueueNode* temp = discardedFront;
    discardedFront = discardedFront->next;
    if (!discardedFront) {
        discardedRear = nullptr;
    }
    question* dequeuedQuestion = temp->data;
    delete temp;
    return dequeuedQuestion;
}

question* questionDeck::dequeueSpecific(question* q) {
    if (!discardedFront) {
        return nullptr;
    }

    QueueNode* current = discardedFront;
    QueueNode* previous = nullptr;

    while (current && current->data != q) {
        previous = current;
        current = current->next;
    }

    if (current) {
        if (previous) {
            previous->next = current->next;
        }
        else {
            discardedFront = current->next;
        }

        if (!current->next) {
            discardedRear = previous;
        }

        question* dequeuedQuestion = current->data;
        delete current;
        return dequeuedQuestion;
    }
    return nullptr;
}


int questionDeck::countQuestions() const {
    int count = 0;
    question* current = questionsHead;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

question* questionDeck::getDiscardedQuestionByNumber(int number) {
    int count = 1;
    QueueNode* current = discardedFront;
    while (current != nullptr) {
        if (count == number) {
            return current->data;
        }
        current = current->next;
        count++;
    }
    return nullptr;
}

