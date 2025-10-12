# Search AutoComplete System

Search autocomplete is designed to enhance user experience by providing real-time suggestions based on partial input. For example, typing `app` may yield `apple, applet, application.`

For simplicity, the suggestions are ranked in 2 ways:
1. alphabetical order
2. frequency

Users should be able to configure:
1. ranking strategy
2. number of returned suggestions

Assume the system is case insensitive.

## Design

### 1. 
```cpp
class SearchAutocomplete {
    - vector<RankingStrategy*> rankingStrategies;
    - RankingStrategy* activeStrategy;
    - string currentPrefix;
    - TrieNode* trieRoot;
    - TrieNode* prefixNode;
    + void setRankingStrategy();
    + void addRankingStrategy();
    + vector<string> autocompleteSearch(char input);
    + void clearSearch();
};
```

### 2.
```cpp
class RankingStrategy {
    - string name;
    - string description;
    + virtual vector<string> getTopSuggestions(int N, TrieNode* trie_ptr);
    + virtual ~RankingStrategy();
}
```

### 3.
```cpp
class TrieNode {
    string prefix;
    bool isWordEnd;
    map<char, TreeNode*> next;
    TrieNode* prev;
    int frequency;

    + void updateFrequency();
    + string getPrefix();
    + TreeNode* moveTo(char input);
};
```

### Notes
- This current design is extensible to new ranking strategies *but* results in slow querying.
- If the ranking strategy is based on frequency, then must traverse through all inserted words with the same prefix.
- If each `TrieNode` tracks the top N words, faster `O(1)` queries but slower insertion (i.e. `O(L * N)` where L is the length of the search).