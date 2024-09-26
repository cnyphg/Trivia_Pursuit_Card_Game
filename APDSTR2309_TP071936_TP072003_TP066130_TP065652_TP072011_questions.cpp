#include "APDSTR2309_TP071936_TP072003_TP066130_TP065652_TP072011_questions.h"

question* questionList::createNewNode(const string& quest, const string& opt, const string& ans) {
    return new question{ quest, opt, ans, nullptr };
}

void questionList::InsertToEnd(const string& quest, const string& opt, const string& ans) {
    question* newNode = createNewNode(quest, opt, ans);
    if (!head) {
        head = newNode;
    }
    else {
        question* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}

void questionList::DisplayQuestions() const {
    question* current = head;
    while (current) {
        cout << "Question: " << current->quest << endl;
        cout << "Options: \n" << current->opt << endl;
        cout << "Answer: " << current->ans << endl;
        current = current->next;
    }
}

string questionList::formatString(const string& str) const{
    string formatted;
    for (char c : str) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            formatted += std::toupper(static_cast<unsigned char>(c));
        }
    }
    return formatted;
}

bool questionList::CheckAnswer(const string& quest, const string& userAnswer) const {
    question* current = head;
    while (current) {
        if (current->quest == quest) {
            string formattedUserAnswer = formatString(userAnswer); // Initialize an empty string to store the formatted answer
            string formattedCorrectAnswer = formatString(current->ans);

            return formattedCorrectAnswer == formattedUserAnswer; // Compare the formatted answer with the answer stored in the current question node
        }
        current = current->next;
    }
    return false; // Return false if the question is not found
}

bool questionList::readQuestionsFromFile(const string& filename, questionList& qlist) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;

    // Check for and skip the Byte Order Mark (BOM)
    char bom[3] = { 0 };
    file.read(bom, 3);
    if (!(bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF')) {
        file.seekg(0);
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string quest, opt, ans;

        getline(ss, quest, '|');
        getline(ss, opt, '|');
        getline(ss, ans, '\n');

        replace(opt.begin(), opt.end(), ';', '\n');

        quest.erase(remove(quest.begin(), quest.end(), '\"'), quest.end());
        opt.erase(remove(opt.begin(), opt.end(), '\"'), opt.end());
        ans.erase(remove(ans.begin(), ans.end(), '\"'), ans.end());

        qlist.InsertToEnd(quest, opt, ans);
    }

    file.close();
    return true;
}
