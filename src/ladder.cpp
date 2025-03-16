#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "error with " << word1 << ", " << word2 << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1.size() != str2.size()) {
        return false;
    }
    int count = 0;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            if (++count > d) {
                return false;
            }
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;

    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff > 1) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) return {};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> to_erase;

        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();

            string last_word = ladder.back();

            for (const string& word : word_list) {
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                    to_erase.insert(word);
                }
            }
        }

        for (const string& word : to_erase) {
            visited.insert(word);
        }
    }

    return {};
}



void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cout << "file didnt open" << file_name << endl;
        return;
    }
    
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word mapping." << endl;
        return;
    } 

    for (const string& word : ladder) {
        cout << word << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}