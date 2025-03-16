#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"
#include <vector>
#include <string>
#include <set>
#include <sstream>


// Helper function
std::string capture_ladder_output(const std::vector<std::string>& ladder) {
    std::ostringstream oss;
    for (const auto& word : ladder) {
        oss << word << " ";
    }
    return oss.str();
}

// Ladder Tests
TEST(LadderTests, WordLadder_BasicCases) {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    auto ladder1 = generate_word_ladder("cat", "dog", word_list);
    EXPECT_EQ(ladder1.size(), 4);

    auto ladder2 = generate_word_ladder("marty", "curls", word_list);
    EXPECT_EQ(ladder2.size(), 6);

    auto ladder3 = generate_word_ladder("code", "data", word_list);
    EXPECT_EQ(ladder3.size(), 6);

    auto ladder4 = generate_word_ladder("work", "play", word_list);
    EXPECT_EQ(ladder4.size(), 6);

    auto ladder5 = generate_word_ladder("sleep", "awake", word_list);
    EXPECT_EQ(ladder5.size(), 8);

    auto ladder6 = generate_word_ladder("car", "cheat", word_list);
    EXPECT_EQ(ladder6.size(), 4);
}

TEST(LadderTests, WordLadder_IdenticalWords) {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    auto ladder = generate_word_ladder("were", "were", word_list);
    if (ladder.size() == 2){
      EXPECT_EQ(ladder.front(), "were");
      EXPECT_EQ(ladder.back(), "were");
    } else{
      EXPECT_EQ(ladder.size(), 0);
    }
}

TEST(LadderTests, WordLadder_InvalidPath) {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    auto ladder = generate_word_ladder("abcdef", "ghijkl", word_list);
    EXPECT_TRUE(ladder.empty());
}

// Dijkstra Tests
TEST(DijkstraTests, ShortestPaths) {
    Graph G;
    file_to_graph("src/medium.txt", G);

    vector<int> previous;
    auto distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_NE(distances[1], INF);
    EXPECT_NE(distances[2], INF);
}

TEST(DijkstraTests, ExtractPathAndCost) {
    Graph G;
    file_to_graph("src/medium.txt", G);
    vector<int> previous;
    auto distances = dijkstra_shortest_path(G, 0, previous);

    auto path = extract_shortest_path(distances, previous, 3);
    std::ostringstream oss;
    for (int node : path) oss << node << " ";
    std::string path_str = oss.str();

    EXPECT_FALSE(path.empty());
    EXPECT_LT(distances[3], INF);
}

TEST(DijkstraTests, PrintPathOutput) {
    std::ostringstream oss;
    vector<int> path = {0, 2, 3};
    int cost = 9;
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    print_path(path, cost);
    std::cout.rdbuf(orig_buf);

    std::string output = oss.str();
    EXPECT_NE(output.find("0 2 3"), std::string::npos);
    EXPECT_NE(output.find("Total cost is 9"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}