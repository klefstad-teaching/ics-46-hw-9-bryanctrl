#include "ladder.h"
#include <iostream>

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << ". Because of: " << word1 << "and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){

}

bool is_adjacent(const string& word1, const string& word2){

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){

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

}

void verify_word_ladder(){

}
