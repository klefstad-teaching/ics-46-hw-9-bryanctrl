#include "ladder.h"
#include <iostream>

vector<string> global_ladder;

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << ". Because of: " << word1 << "and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (d == 0){
        int diff_count = 0;
        if (str1.length() != str2.length()){
            return false;
        }
        for(int i = 0; i < str1.length(); i++){
            if (str1[i] != str2[i]){
                diff_count++;
                if (diff_count > d){
                    return false;
                } 
            }
        }
        return true;
    }
    else if (d == 1){
        const string& shorter = (str1.length() < str2.length()) ? str1 : str2;
        const string& longer = (str1.length() < str2.length()) ? str2 : str1;
        if (longer.length() - shorter.length() > 1){
            return false;
        }
        int i = 0, j = 0;
        int diff_count = 0;
        while(i < shorter.length() && j < longer.length()){
            if (shorter[i] == longer[j]){
                i++;
                j++;
            } else {
                diff_count++;
                if (diff_count > d){
                    return false;
                }
                j++;
            }
        }
        if (j < longer.length()){
            diff_count++;
        }
        return diff_count <= d;
    } else {
        return false;
    }
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(const string& w : word_list){
            if (is_adjacent(last_word, w) && visited.find(w) == visited.end()){
                vector<string> new_ladder = ladder;
                new_ladder.push_back(w);
                if (w == end_word){
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
                visited.insert(w);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream infile(file_name);
    string word;
    while (infile >> word){
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (const auto& c : ladder){
        cout << c << " ";
    }
    cout << endl;
}

void verify_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "Ladder is empty." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size() - 1; ++i) {
        const string& current = ladder[i];
        const string& next = ladder[i + 1];
        if (!is_adjacent(current, next)) {
            cout << "Invalid ladder: \"" << current << "\" and \"" << next << "\" are not adjacent." << endl;
            return;
        }
    }
    cout << "Ladder is valid!" << endl;
}