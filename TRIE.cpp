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

//================ Code starts here ================
void
solve()
{
    int n;
    cin >>n;
    Trie trie;
    rep(i,0,n){
        string s;
        cin >>s;
        trie.insert(s);

    }
    int q;
    cin >>q;
    while(q--){
        string s;
        cin >>s;
        if(trie.search(s)){
            cout<<"Found\n";
        }
        else{
            cout<<"Not Found\n";
        }
    }

}





//vasilly's multiset
const int SIZE = 26;
struct TrieNode
{
    int count;
    int val;
    TrieNode *children[2];
    TrieNode()
    {
        count = 0;
        val = 1;
        for (int i = 0; i < 2; i++)
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
        root->val = 0;
    }
    void insert(int n)
    {
        TrieNode *temp = root;
        for(int i=30; i>=0;i--){
            int bit = (1<<i) & n ? 1:0;
            if(temp->children[bit]==nullptr){
                temp->children[bit]= new TrieNode();

            }
            temp = temp->children[bit];
            temp->count++;

        }
        temp->val = n;
    }
    void erase(int n)
    {
        TrieNode *temp = root;
        for(int i=30; i>=0; i--){
            int bit = ((1<<i) &n ?1:0);

            temp = temp->children[bit];
            temp->count--;

        }
        
    }
    int getMaxXor(int n){
        TrieNode* temp = root;
        for(int i=30; i>=0; i--){
            int bit = ((1<<i) & n) ? 1 : 0;
            int pref = bit ^ 1;
            if(temp->children[pref] && temp->children[pref]->count > 0){
                temp = temp->children[pref];
            } else if(temp->children[bit] && temp->children[bit]->count > 0){
                temp = temp->children[bit];
            } else {
                break;
            }
        }
        return temp->val ^ n;
    }

};

//================ Code starts here ================
void
solve()
{
    Trie trie;
    int q;
    cin >>q;
    trie.insert(0);
    while(q--){
       char ch;
       int n;
       cin >>ch>>n;
       if(ch=='+'){
        trie.insert(n);
       }
       else if(ch=='-'){
        trie.erase(n);
       }
       else{
        cout<<trie.getMaxXor(n)<<nl;
       }
    }

}


