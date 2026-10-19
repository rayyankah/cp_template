//implementing trie
const int SIZE = 26;
struct TrieNode
{
    int count;
    bool endOfWord;
    TrieNode *children[SIZE];
    TrieNode()
    {
        count = 0;
        endOfWord = false;
        for (int i = 0; i < SIZE; i++)
        {
            children[i] = nullptr;
        }
    }
};
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    void insert(string word)
    {
        TrieNode *temp = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                // ekhono banano hy ni, so new node create
                temp->children[idx] = new TrieNode();
            }
            temp = temp->children[idx];
            temp->count++;
        }
        temp->endOfWord = true;
    }
    bool search(string word)
    {
        TrieNode *temp = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return false;
            }
            temp = temp->children[idx];
        }
        return temp->endOfWord;
    }
    bool startsWith(string prefix)
    {
        TrieNode *temp = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return false;
            }
            temp = temp->children[idx];
        }
        return true;
    }
    int countWordsStartingWith(string prefix)
    {
        TrieNode *temp = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (temp->children[idx] == nullptr)
            {
                return 0;
            }
            temp = temp->children[idx];
        }
        return temp->count;
    }
    void erase(string word)
    {
        if (search(word))
        {
            TrieNode *temp = root;
            for (char c : word)
            {
                int idx = c - 'a';
                temp = temp->children[idx];
                temp->count--;
            }
            temp->endOfWord = false;
        }
    }

};
// usage: Trie t; t.insert(s); t.search(s); t.countWordsStartingWith(p); t.erase(s). lowercase only
