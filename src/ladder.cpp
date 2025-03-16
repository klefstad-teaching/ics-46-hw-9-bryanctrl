#include "ladder.h"
#include <iostream>
#include <algorithm>

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << ". Because of: " << word1 << "and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(d == 0){
        return str1 == str2;
    } else if(d == 1){
        if(str1.size() == str2.size()){
            int diff = 0;
            for (size_t i = 0; i < str1.size(); i++){
                if(str1[i] != str2[i]) diff++;
                if(diff > 1) return false;
            }
            return diff <= 1;
        }
        else if(abs((int)str1.size() - (int)str2.size()) == 1){
            const string& shorter = (str1.size() < str2.size()) ? str1 : str2;
            const string& longer  = (str1.size() < str2.size()) ? str2 : str1;
            int i = 0, j = 0;
            bool foundDifference = false;
            while(i < shorter.size() && j < longer.size()){
                if(shorter[i] == longer[j]){
                    i++; j++;
                } else {
                    if(foundDifference) return false;
                    foundDifference = true;
                    j++;
                }
            }
            return true;
        }
        return false;
    }
    return false;
}


bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        return {};
    }

    if (word_list.find(end_word) == word_list.end()){
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    set<string> diction = word_list;
    ladder_queue.push({begin_word});
    diction.erase(begin_word);

    while(!ladder_queue.empty()){
        int level_size = ladder_queue.size();
        set<string> words_used;
        for (int i = 0; i < level_size; i++){
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();
            vector<string> candidates;
            for (const auto& w : diction){
                if (is_adjacent(last_word, w)){
                    candidates.push_back(w);
                }
            }
            for (const auto &w : candidates) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(w);
                if (w == end_word){
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
                words_used.insert(w);
            }
        }
        for (const auto &w : words_used) {
            diction.erase(w);
        }
    }
    error(begin_word, end_word, "no ladder found");
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
    for (const string& c : ladder){
        cout << c << " ";
    }
    cout << endl;
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