#include <iostream>
#include "ladder.h"

using namespace std;

int main(){
    string first_word;
    string second_word;
    set<string> word_list;

    cout << "Enter the first word: " << endl;
    cin >> first_word;
    cout << "Enter the second word: " << endl;
    cin >> second_word;

    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(first_word, second_word, word_list);

    if (!ladder.empty()){
        cout << "Word ladder found: " << endl;
        print_word_ladder(ladder);
        cout << "Verifying ladder: " << endl;
        verify_word_ladder(ladder);
    } else {
        cout << "No word ladder found." << endl;
    }
    return 0;
}