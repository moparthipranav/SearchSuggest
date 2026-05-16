#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * The problem can be solved using a Trie data structure or Hash Table. 
 * The crux of the problem is retrieval of the suggestions.
 * The more efficient the retrieval the more faster the program, hence I choose the trie data strucutre
 * We can also print easily the suggestions in a alphabetical order.
 * No overhead of hash function in a Trie data structure
 * The time complexity is O(L) where L is the length of the inputString.
 * Extra memory is required for the Trie data structure
*/

// Building a Trie data structure

/** 
 * Breaking down the problem, What is the most fundamental part of the program that is required and I can code -> Trie Node
 * Writing the functions such as insert, delete and search.
 * To understand the insert function, 
 */

// A Trie Node
class TrieNode {
    public:
        TrieNode* children[26]; // An array to store the pointers 
        bool isEndOfWord;   // A delimiter to signal the end of a particular word

        TrieNode() {
            isEndOfWord = false;
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr; // Modern c++ standard
            }
        }
};

class Trie {

    private:
        TrieNode* root;

        void storeAllWordsWithGivenPrefix(TrieNode* node, string currentPrefix, vector<string>& result) { // Doing a dfs search for collecting all words that start with a given prefix
            if (node->isEndOfWord) {
                result.push_back(currentPrefix);
            }
            for (int i = 0; i < 26; ++i) {
                if (node->children[i] != nullptr) {
                    char ch = 'a' + i;
                    storeAllWordsWithGivenPrefix(node->children[i], currentPrefix + ch, result);
                }
            }
        }

    public:
        Trie() {
            root = new TrieNode();
        }

        // Inserting a word
        void insert(string word) {
            TrieNode* node = root;
            for (char ch : word) {
                int index = ch - 'a';
                if (node->children[index] == nullptr) {
                    node->children[index] = new TrieNode();
                }
                node = node->children[index];
            }
            node->isEndOfWord = true;
        }

        vector<string> autocomplete(const string& prefix) {
            TrieNode* node = root;
            vector<string> results;
            for (char c : prefix) {
                if (node->children[c - 'a'] == nullptr) {
                    return results; // Empty vector if the prefix is not found
                }
                node = node->children[c - 'a'];
            }
            storeAllWordsWithGivenPrefix(node, prefix, results);
            return results;
        }

};

string toLowerCase(string s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') c += 32;
    }
    return s;
}

vector<vector<string>> customerReviewSuggestions(vector<vector<string>> reviewDatabase, string customerQuery) {
    // Creating the Trie data structure
    Trie trie;

    // Converting the database into a Trie datastructure
    for (const auto& innerList : reviewDatabase) {
        for (string val : innerList) {
            trie.insert(toLowerCase(val));
        }
    }

    vector<vector<string>> result;
    string currentPrefix = "";
    string query = toLowerCase(customerQuery);

    for (char ch:query) {
        currentPrefix += ch;
        if (currentPrefix.length() >= 2) {
            vector<string> suggestions = trie.autocomplete(currentPrefix);

            if (suggestions.size() > 3) suggestions.resize(3);
            result.push_back(suggestions);
        }
    }
    return result;
}

int main() {
    vector<vector<string>> database = {{"mobile", "mouse", "moneypot", "monitor", "mousepad", "microphone", "motherboard"}};
    string query;
    
    // Read the query from the command line or standard input
    if (!(cin >> query)) return 0;

    vector<vector<string>> suggestions = customerReviewSuggestions(database, query);

    for (const auto& list : suggestions) {
        for (const string& s : list) {
            cout << s << " ";
        }
        cout << "|"; // Use a separator for the frontend to parse
    }
    return 0;
}