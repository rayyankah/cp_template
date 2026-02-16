//offline
// ================ Author: Rayyan Khalil ================

#include <bits/stdc++.h>
using namespace std;

#define vvi vector<vector<int>>
#define vll vector<long long>
#define mi map<int, int>
#define si set<int>
#define mii map<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pi pair<int, int>
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)
#define vv vector
#define myCeil(a, b) (a + b - 1) / b
#define nl '\n'

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    os << "]";
    return os;
}
#ifdef DEBUG
#define debug(x) cerr << "[" << #x << "]: " << x << "\n"
#else
#define debug(x)
#endif

template <class T>
void read(vector<T> &a)
{
    for (auto &x : a)
        cin >> x;
}

const int N = 1e6 + 10;
int isPrime[N];
void sieve()
{
    for (int i = 2; i < N; i++)
    {
        isPrime[i] = 1;
    }
    for (int i = 2; i * i < N; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < N; j += i)
            {
                isPrime[j] = 0;
            }
        }
    }
}

int nextPrime(int n)
{
    if (n <= 1)
        return 2;
    int ans = n + 1;
    while (ans < N && !isPrime[ans])
    {
        ans++;
    }
    return ans;
}
int prevPrime(int n)
{
    if (n <= 2)
        return 2;
    int ans = n - 1;
    while (ans > 1 && !isPrime[ans])
    {
        ans--;
    }
    return ans;
}

ll hash1(const string &s)
{
    ll h = 0;
    int len = min((int)s.size(), 3);
    rep(i, 0, len)
    {
        char ch = tolower(s[i]);
        int val = (ch == ' ') ? 0 : (ch - 'a' + 1);
        h = h * 27 + val;
    }
    return h;
}

ll hash2(const string &s)
{
    ll h = 0;
    for (char ch : s)
    {
        int val = (tolower(ch) - 'a' + 1);
        h = 37 * h + val;
    }
    return h;
}

string generateRandomWord(int length)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dis('a', 'z');
    string word;
    for (int i = 0; i < length; ++i)
    {
        word += dis(gen);
    }
    return word;
}

template <typename K, typename V>
struct Entry
{
    K key;
    V value;
};

template <typename K, typename V>
class ChainingHashTable
{
private:
    vector<list<Entry<K, V>>> table;
    int currSize = 0;
    int tableSize;
    double maxLoad = 0.5;
    double minLoad = 0.25;
    int initSize = 13;
    int lastResizeElems = 0;
    int insertsSinceResz = 0;
    int delsSinceResz = 0;
    ll collisionCount = 0;
    function<ll(const K &)> hashFunc;
    int myHash(const K &key) const
    {
        ll h = hashFunc(key);
        int idx = h % tableSize;
        if (idx < 0)
            idx += tableSize;
        return idx;
    }
    void rehash(bool expand)
    {
        vector<list<Entry<K, V>>> old = table;
        if (expand)
        {
            tableSize = nextPrime(tableSize * 2);
        }
        else
        {
            tableSize = prevPrime(tableSize / 2);
            if (tableSize < initSize)
            {
                tableSize = initSize;
            }
        }
        table.assign(tableSize, {});
        currSize = 0;
        insertsSinceResz = 0;
        delsSinceResz = 0;
        for (const auto &lst : old)
        {
            for (const auto &entry : lst)
            {
                insert(entry.key, entry.value);
            }
        }
        lastResizeElems = currSize;
    }

public:
    ChainingHashTable(function<ll(const K &)> hf)
    {
        hashFunc = hf;
        tableSize = initSize;
        table.assign(tableSize, {});
    }
    bool insert(const K &key, const V &value)
    {
        int idx = myHash(key);
        auto &lst = table[idx];
        for (const auto &entry : lst)
        {
            if (entry.key == key)
            {
                return false;
            }
        }
        collisionCount += lst.size();
        lst.pb({key, value});
        currSize++;
        insertsSinceResz++;
        double load = 1.0 * currSize / tableSize;
        if (load > maxLoad && insertsSinceResz >= lastResizeElems / 2)
        {
            rehash(true);
        }
        return true;
    }
    V search(const K &key, int &hits)
    {
        hits = 0;
        int idx = myHash(key);
        const auto &lst = table[idx];
        for (const auto &entry : lst)
        {
            hits++;
            if (entry.key == key)
            {
                return entry.value;
            }
        }
        return V();
    }
    bool remove(const K &key)
    {
        int idx = myHash(key);
        auto &lst = table[idx];
        for (auto it = lst.begin(); it != lst.end(); it++)
        {
            if (it->key == key)
            {
                lst.erase(it);
                currSize--;
                delsSinceResz++;
                double load = 1.0 * currSize / tableSize;
                if (load < minLoad && tableSize > initSize && delsSinceResz >= lastResizeElems / 2)
                {
                    rehash(false);
                }
                return true;
            }
        }
        return false;
    }
    ll getCollisionCount() const
    {
        return collisionCount;
    }
};

template <typename K, typename V>
class ParentHashTable
{
protected:
    enum EntryType
    {
        ACTIVE,
        DELETED,
        EMPTY
    };
    struct HashEntry
    {
        Entry<K, V> element;
        EntryType info;
        HashEntry()
        {
            info = EMPTY;
        }
        HashEntry(const K &key, const V &value, EntryType i = ACTIVE)
        {
            element = {key, value};
            info = i;
        }
    };
    vector<HashEntry> table;
    int currSize = 0;
    int tableSize;
    double maxLoad = 0.5;
    double minLoad = 0.25;
    int initSize = 13;
    int lastResizeElems = 0;
    int insertsSinceResz = 0;
    int delsSinceResz = 0;
    ll collisionCount = 0;
    function<ll(const K &)> hashFunc;
    ll auxHash(const K &key) const
    {
        ll h = 0;
        for (char ch : key)
        {
            int val = (tolower(ch) - 'a' + 1);
            h = 31 * h + val;
        }
        return h ? h : 1;
    }
    int myHash(const K &key) const
    {
        ll h = hashFunc(key);
        int idx = h % tableSize;
        if (idx < 0)
            idx += tableSize;
        return idx;
    }
    virtual ll probeOffset(const K &key, int i) const = 0;
    int findPos(const K &key, int &hits) const
    {
        hits = 0;
        int i = 0;
        int currPos = myHash(key);
        while (table[currPos].info != EMPTY && table[currPos].element.key != key)
        {
            hits++;
            i++;
            currPos = (myHash(key) + probeOffset(key, i)) % tableSize;
            if (currPos < 0)
                currPos += tableSize;
            if (i > tableSize)
                return -1;
        }
        hits++;
        if (table[currPos].info == EMPTY)
            return -1;
        return currPos;
    }
    void rehash(bool expand)
    {
        vector<HashEntry> old = table;
        if (expand)
        {
            tableSize = nextPrime(tableSize * 2);
        }
        else
        {
            tableSize = prevPrime(tableSize / 2);
            if (tableSize < initSize)
            {
                tableSize = initSize;
            }
        }
        table.resize(tableSize);
        currSize = 0;
        insertsSinceResz = 0;
        delsSinceResz = 0;
        for (auto &entry : table)
        {
            entry.info = EMPTY;
        }
        for (const auto &entry : old)
        {
            if (entry.info == ACTIVE)
            {
                insert(entry.element.key, entry.element.value);
            }
        }
        lastResizeElems = currSize;
    }

public:
    ParentHashTable(function<ll(const K &)> hf)
    {
        hashFunc = hf;
        tableSize = initSize;
        table.resize(tableSize);
    }
    V search(const K &key, int &hit) const
    {
        int idx = findPos(key, hit);
        if (idx == -1)
            return V();
        return table[idx].element.value;
    }
    bool remove(const K &key)
    {
        int hits;
        int idx = findPos(key, hits);
        if (idx == -1)
            return false;
        table[idx].info = DELETED;
        currSize--;
        delsSinceResz++;
        double load = 1.0 * currSize / tableSize;
        if (load < minLoad && tableSize > initSize && delsSinceResz >= lastResizeElems / 2)
        {
            rehash(false);
        }
        return true;
    }
    bool insert(const K &key, const V &value)
    {
        int hits;
        int pos = findPos(key, hits);
        if (pos != -1)
            return false;
        int i = 0;
        int currPos = myHash(key);
        int firDel = -1;
        while (table[currPos].info != EMPTY)
        {
            if (table[currPos].info == DELETED && firDel == -1)
            {
                firDel = currPos;
            }
            i++;
            currPos = (myHash(key) + probeOffset(key, i)) % tableSize;
            if (currPos < 0)
                currPos += tableSize;
            if (i > tableSize)
                return false;
        }

        collisionCount += i;
        pos = (firDel != -1) ? firDel : currPos;
        table[pos] = HashEntry(key, value, ACTIVE);
        currSize++;
        insertsSinceResz++;
        double load = 1.0 * currSize / tableSize;
        if (load > maxLoad && insertsSinceResz >= lastResizeElems / 2)
        {
            rehash(true);
        }
        return true;
    }
    ll getCollisionCount() const
    {
        return collisionCount;
    }
};

template <typename K, typename V>
class DoubleHashingHashTable : public ParentHashTable<K, V>
{
protected:
    ll probeOffset(const K &key, int i) const override
    {
        return i * this->auxHash(key);
    }

public:
    DoubleHashingHashTable(function<ll(const K &)> hf) : ParentHashTable<K, V>(hf)
    {
    }
};
template <typename K, typename V>
class CustomProbingHashTable : public ParentHashTable<K, V>
{
private:
    int C1 = 1;
    int C2 = 3;

protected:
    ll probeOffset(const K &key, int i) const override
    {
        return C1 * i * this->auxHash(key) + C2 * (ll)i * i;
    }

public:
    CustomProbingHashTable(function<ll(const K &)> hf, int c1 = 1, int c2 = 3) : ParentHashTable<K, V>(hf), C1(c1), C2(c2)
    {
    }
};
void generateReport(int c1 = 1, int c2 = 3)
{
    int wordLength = 10;
    vector<pair<string, int>> words;
    set<string> uniqueWords;
    int seq = 1;
    while (words.size() < 10000)
    {
        string word = generateRandomWord(wordLength);
        if (uniqueWords.insert(word).second)
        {
            words.pb({word, seq++});
        }
    }
    vector<string> methods = {"Chaining Method", "Double Hashing", "Custom Probing"};
    vector<function<ll(const string &)>> hashes = {hash1, hash2};
    int collisions[2] = {0, 0};
    int uniques[2] = {0, 0};
    for (int h = 0; h < 2; h++)
    {
        auto hash_fn = hashes[h];
        map<ll, int> count_map;
        int coll_count = 0;
        for (auto &p : words)
        {
            ll raw_hash = hash_fn(p.first);
            if (count_map[raw_hash] > 0)
            {
                coll_count++;
            }
            count_map[raw_hash]++;
        }
        collisions[h] = coll_count;
        uniques[h] = count_map.size();
        cout << "Unique hashes for Hash" << (h + 1) << ": " << uniques[h] << endl;
    }
    cout << setw(25) << "" << setw(25) << "Hash1" << setw(50) << "Hash2" << endl;
    cout << setw(25) << "" << setw(25) << "Number of Collisions" << setw(25) << "Average Hits"
         << setw(25) << "Number of Collisions" << setw(25) << "Average Hits" << endl;
    double avg_hits[3][2];
    ll method_collisions[3][2];
    for (int m = 0; m < 3; m++)
    {
        for (int h = 0; h < 2; h++)
        {
            auto hash_fn = hashes[h];
            unique_ptr<ParentHashTable<string, int>> open_ht;
            unique_ptr<ChainingHashTable<string, int>> chain_ht;
            if (m == 0)
            {
                chain_ht = unique_ptr<ChainingHashTable<string, int>>(new ChainingHashTable<string, int>(hash_fn));
            }
            else if (m == 1)
            {
                open_ht = unique_ptr<DoubleHashingHashTable<string, int>>(new DoubleHashingHashTable<string, int>(hash_fn));
            }
            else
            {
                open_ht = unique_ptr<CustomProbingHashTable<string, int>>(new CustomProbingHashTable<string, int>(hash_fn, c1, c2));
            }
            for (auto &p : words)
            {
                if (m == 0)
                {
                    chain_ht->insert(p.first, p.second);
                }
                else
                {
                    open_ht->insert(p.first, p.second);
                }
            }
            vector<string> keys;
            for (auto &p : words)
            {
                keys.pb(p.first);
            }
            random_shuffle(all(keys));
            keys.resize(1000);
            double sum_hits = 0;
            for (auto &k : keys)
            {
                int hits = 0;
                if (m == 0)
                {
                    chain_ht->search(k, hits);
                }
                else
                {
                    open_ht->search(k, hits);
                }
                sum_hits += hits;
            }
            avg_hits[m][h] = sum_hits / 1000.0;
            if (m == 0)
            {
                method_collisions[m][h] = chain_ht->getCollisionCount();
            }
            else
            {
                method_collisions[m][h] = open_ht->getCollisionCount();
            }
        }
        cout << setw(25) << methods[m]
             << setw(25) << method_collisions[m][0]
             << setw(25) << fixed << setprecision(2) << avg_hits[m][0]
             << setw(25) << method_collisions[m][1]
             << setw(25) << fixed << setprecision(2) << avg_hits[m][1] << endl;
    }
}
void solve()
{
    int n;
    cout << "Enter word length: " << endl;
    cin >> n;
    int c1, c2;
    cout << "Enter C1 and C2 for custom probing: " << endl;
    cin >> c1 >> c2;
    ChainingHashTable<string, int> ht(hash1);

    set<string> unique;
    int val = 1;
    while (unique.size() < 10)
    {
        string word = generateRandomWord(n);
        if (unique.insert(word).second)
        {
            ht.insert(word, val);
            cout << "Inserted: " << word << " with value " << val << endl;
            val++;
        }
    }
    generateReport(c1, c2);
}

signed main()
{
    fast;
    sieve();
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}


// a sec online
// ================ Author: Rayyan Khalil ================

#include <bits/stdc++.h>
using namespace std;

#define vvi vector<vector<int>>
#define vll vector<long long>
#define mi map<int, int>
#define si set<int>
#define mii map<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pi pair<int, int>
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)
#define vv vector
#define myCeil(a, b) (a + b - 1) / b
#define nl '\n'

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    os << "]";
    return os;
}
#ifdef DEBUG
#define debug(x) cerr << "[" << #x << "]: " << x << "\n"
#else
#define debug(x)
#endif

template <class T>
void read(vector<T> &a)
{
    for (auto &x : a)
        cin >> x;
}

const int N = 1e6 + 10;
int isPrime[N];
void sieve()
{
    for (int i = 2; i < N; i++)
    {
        isPrime[i] = 1;
    }
    for (int i = 2; i * i < N; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < N; j += i)
            {
                isPrime[j] = 0;
            }
        }
    }
}

int nextPrime(int n)
{
    if (n <= 1)
        return 2;
    int ans = n + 1;
    while (ans < N && !isPrime[ans])
    {
        ans++;
    }
    return ans;
}
int prevPrime(int n)
{
    if (n <= 2)
        return 2;
    int ans = n - 1;
    while (ans > 1 && !isPrime[ans])
    {
        ans--;
    }
    return ans;
}

ll hash1(const string &s)
{
    ll h = 0;
    int len = min((int)s.size(), 3);
    rep(i, 0, len)
    {
        char ch = tolower(s[i]);
        int val = (ch == ' ') ? 0 : (ch - 'a' + 1);
        h = h * 27 + val;
    }
    return h;
}

ll hash2(const string &s)
{
    ll h = 0;
    for (char ch : s)
    {
        int val = (tolower(ch) - 'a' + 1);
        h = 37 * h + val;
    }
    return h;
}
int hash3(int n)
{
    return n;
}
string generateRandomWord(int length)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dis('a', 'z');
    string word;
    for (int i = 0; i < length; ++i)
    {
        word += dis(gen);
    }
    return word;
}

template <typename K, typename V>
struct Entry
{
    K key;
    V value;
};

template <typename K, typename V>
class ChainingHashTable
{
private:
    vector<list<Entry<K, V>>> table;
    int currSize = 0;
    int tableSize;
    double maxLoad = 0.5;
    double minLoad = 0.25;
    int initSize = 13;
    int lastResizeElems = 0;
    int insertsSinceResz = 0;
    int delsSinceResz = 0;
    ll collisionCount = 0;
    function<ll(const K &)> hashFunc;
    int myHash(const K &key) const
    {
        ll h = hashFunc(key);
        int idx = h % tableSize;
        if (idx < 0)
            idx += tableSize;
        return idx;
    }
    void rehash(bool expand)
    {
        vector<list<Entry<K, V>>> old = table;
        if (expand)
        {
            tableSize = nextPrime(tableSize * 2);
        }
        else
        {
            tableSize = prevPrime(tableSize / 2);
            if (tableSize < initSize)
            {
                tableSize = initSize;
            }
        }
        table.assign(tableSize, {});
        currSize = 0;
        insertsSinceResz = 0;
        delsSinceResz = 0;
        for (const auto &lst : old)
        {
            for (const auto &entry : lst)
            {
                insert(entry.key, entry.value);
            }
        }
        lastResizeElems = currSize;
    }

public:
    ChainingHashTable(function<ll(const K &)> hf)
    {
        hashFunc = hf;
        tableSize = initSize;
        table.assign(tableSize, {});
    }
    bool insert(const K &key, const V &value)
    {
        int idx = myHash(key);
        auto &lst = table[idx];
        for (const auto &entry : lst)
        {
            if (entry.key == key)
            {
                return false;
            }
        }
        collisionCount += lst.size();
        lst.pb({key, value});
        currSize++;
        insertsSinceResz++;
        double load = 1.0 * currSize / tableSize;
        if (load > maxLoad && insertsSinceResz >= lastResizeElems / 2)
        {
            rehash(true);
        }
        return true;
    }
    V search(const K &key, int &hits)
    {
        hits = 0;
        int idx = myHash(key);
        const auto &lst = table[idx];
        for (const auto &entry : lst)
        {
            hits++;
            if (entry.key == key)
            {
                return entry.value;
            }
        }
        return V();
    }
    bool remove(const K &key)
    {
        int idx = myHash(key);
        auto &lst = table[idx];
        for (auto it = lst.begin(); it != lst.end(); it++)
        {
            if (it->key == key)
            {
                lst.erase(it);
                currSize--;
                delsSinceResz++;
                double load = 1.0 * currSize / tableSize;
                if (load < minLoad && tableSize > initSize && delsSinceResz >= lastResizeElems / 2)
                {
                    rehash(false);
                }
                return true;
            }
        }
        return false;
    }
    ll getCollisionCount() const
    {
        return collisionCount;
    }
};

template <typename K, typename V>
class ParentHashTable
{
protected:
    enum EntryType
    {
        OCCUPIED,
        DELETED,
        EMPTY
    };
    struct HashEntry
    {
        Entry<K, V> element;
        EntryType info;
        HashEntry()
        {
            info = EMPTY;
        }
        HashEntry(const K &key, const V &value, EntryType i = OCCUPIED)
        {
            element = {key, value};
            info = i;
        }
    };
    vector<HashEntry> table;
    int currSize = 0;
    int tableSize;
    double maxLoad = 0.5;
    double minLoad = 0.25;
    int initSize = 13;
    int lastResizeElems = 0;
    int insertsSinceResz = 0;
    int delsSinceResz = 0;
    ll collisionCount = 0;
    int pmax;
    int maxprobeseq = 0;
    function<ll(const K &)> hashFunc;
    ll auxHash(const K &key) const
    {
        ll h = 0;
        for (char ch : key)
        {
            int val = (tolower(ch) - 'a' + 1);
            h = 31 * h + val;
        }
        return h ? h : 1;
    }
    int myHash(const K &key) const
    {
        ll h = hashFunc(key);
        int idx = h % tableSize;
        if (idx < 0)
            idx += tableSize;
        return idx;
    }
    virtual ll probeOffset(const K &key, int i) const = 0;
    int findPos(const K &key, int &hits) const
    {
        hits = 0;
        int i = 0;
        int currPos = myHash(key);
        while (table[currPos].info != EMPTY && table[currPos].element.key != key)
        {
            hits++;
            i++;
            currPos = (myHash(key) + probeOffset(key, i)) % tableSize;
            if (currPos < 0)
                currPos += tableSize;
            if (i > tableSize)
                return -1;
        }
        hits++;
        if (table[currPos].info == EMPTY)
            return -1;
        return currPos;
    }
    void rehash(bool expand)
    {
        cout << "--- Rehash Triggered: BEFORE ---" << nl;
        cout << "Table Size: " << tableSize << nl;
        cout << "Active Processes: " << currSize << nl;
        double lf = 1.0 * currSize / tableSize;
        cout << "Load Factor: " << fixed << setprecision(3) << lf << nl;
        cout << "Max Probe Sequence: " << maxprobeseq << nl;
        vector<HashEntry> old = table;
        if (expand)
        {
            tableSize = nextPrime(tableSize * 2);
        }
        else
        {
            tableSize = prevPrime(tableSize / 2);
            if (tableSize < initSize)
            {
                tableSize = initSize;
            }
        }
        table.resize(tableSize);
        currSize = 0;
        insertsSinceResz = 0;
        delsSinceResz = 0;
        maxprobeseq = 0;
        for (auto &entry : table)
        {
            entry.info = EMPTY;
        }
        for (const auto &entry : old)
        {
            if (entry.info == OCCUPIED)
            {
                insert(entry.element.key, entry.element.value);
            }
        }
        lastResizeElems = currSize;
        cout << "--- Rehash Triggered: AFTER ---" << nl;
        cout << "Table Size: " << tableSize << nl;
        cout << "Active Processes: " << currSize << nl;
        lf = 1.0 * currSize / tableSize;
        cout << "Load Factor: " << fixed << setprecision(3) << lf << nl;
        cout << "Max Probe Sequence: " << maxprobeseq << nl;
    }

public:
    ParentHashTable(function<ll(const K &)> hf, int sz, int p_max)
    {
        hashFunc = hf;
        initSize = sz;
        tableSize = initSize;
        table.resize(tableSize);
        pmax = p_max;
    }
    V search(const K &key, int &hit) const
    {
        int idx = findPos(key, hit);
        if (idx == -1)
            return V();
        return table[idx].element.value;
    }
    bool remove(const K &key, bool flag = true)
    {
        int hits;
        int idx = findPos(key, hits);
        if (idx == -1)
            return false;
        table[idx].info = DELETED;
        currSize--;
        delsSinceResz++;
        if (flag)
        {
            cout << "FREE " << key << ": Freed from index " << idx << nl;
        }
        // cout<<maxprobeseq<<nl;
        double load = 1.0 * currSize / tableSize;
        if (tableSize > initSize && delsSinceResz >= 5 && load < 0.2)
        {
            rehash(false);
        }
        return true;
    }
    bool insert(const K &key, const V &value, bool flag = false)
    {
        int hits;
        int pos = findPos(key, hits);
        if (pos != -1)
            return false;
        int i = 0;
        int currPos = myHash(key);
        int firDel = -1;
        int nowprobe = 1;
        bool flagg = false;
        while (table[currPos].info != EMPTY)
        {
            if (table[currPos].info == DELETED && firDel == -1)
            {
                firDel = currPos;
                flagg = true;
                break;
            }
            nowprobe++;
            if (nowprobe > pmax)
            {
                maxprobeseq = pmax;
                rehash(true);
                currPos = myHash(key);
                firDel = -1;
                nowprobe = 1;
                continue;
            }
            // maxprobeseq = max(maxprobeseq, nowprobe);
            i++;
            currPos = (myHash(key) + probeOffset(key, i)) % tableSize;
            if (currPos < 0)
                currPos += tableSize;
            if (i > tableSize)
                return false;
        }

        collisionCount += i;
        pos = (firDel != -1) ? firDel : currPos;
        table[pos] = HashEntry(key, value, OCCUPIED);
        currSize++;
        maxprobeseq = max(maxprobeseq, nowprobe);
        if (flag)
        {
            cout << "ALLOCATE " << key << ": Inserted at index " << pos << " (probes: " << nowprobe << ")" << nl;
        }
        insertsSinceResz++;
        double load = 1.0 * currSize / tableSize;

        return true;
    }
    ll getCollisionCount() const
    {
        return collisionCount;
    }
};

template <typename K, typename V>
class OnlineHashing : public ParentHashTable<K, V>
{
protected:
    ll probeOffset(const K &key, int i) const override
    {
        return i * i;
    }

public:
    OnlineHashing(function<ll(const K &)> hf, int sz, int p_max) : ParentHashTable<K, V>(hf, sz, p_max)
    {
    }
};

void solve()
{
    // int n;
    // cout << "Enter word length: " << nl;
    // cin >> n;
    // int c1, c2;
    // cout << "Enter C1 and C2 for custom probing: " << nl;
    // cin >> c1 >> c2;
    // ChainingHashTable<string, int> ht(hash1);

    // set<string> unique;
    // int val = 1;
    // while (unique.size() < 10)
    // {
    //     string word = generateRandomWord(n);
    //     if (unique.insert(word).second)
    //     {
    //         ht.insert(word, val);
    //         cout << "Inserted: " << word << " with value " << val << nl;
    //         val++;
    //     }
    // }
    // generateReport(c1, c2);

    int n, pmax, q;
    cin >> n >> pmax >> q;

    OnlineHashing<int, int> h1(hash3, n, pmax);
    while (q--)
    {
        string s;
        int key;
        cin >> s >> key;
        if (s == "ALLOCATE")
        {
            h1.insert(key, q, true);
        }
        else
        {
            h1.remove(key, true);
        }
    }
}

signed main()
{
    fast;
    sieve();
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}




// online 2nd one 22
class innerHashTable : public ParentHashTable<string, string>
{
protected:
    ll probeOffset(const string &key, int i) const override
    {
        return i * i;
    }

public:
    innerHashTable(function<ll(const string &)> hf, int sz) : ParentHashTable<string, string>(hf, sz)
    {
    }
    void printAll() const
    {
        for (const auto &entry : table)
        {
            if (entry.info == ACTIVE)
            {
                cout << "( " << entry.element.key << ", " << entry.element.value << " )" << nl;
            }
        }
    }
};

class outerHashTable : public ParentHashTable<string, innerHashTable *>
{
protected:
    ll probeOffset(const string &key, int i) const override
    {
        return i;
    }

public:
    outerHashTable(function<ll(const string &)> hf, int sz) : ParentHashTable<string, innerHashTable *>(hf, sz)
    {
    }
    bool insertOuter(const string &key, const string &key2, const string &value)
    {
        int hits;
        // int pos = findPos(key, hits);
        // if (pos != -1)
        //     return false;
        int i = 0;
        int currPos = myHash(key);
        int firDel = -1;
        while (table[currPos].info != EMPTY)
        {
            if (table[currPos].info == ACTIVE && table[currPos].element.key == key)
            {
                return table[currPos].element.value->insert(key2, value);
            }
            if (table[currPos].info == DELETED && firDel == -1)
            {
                firDel = currPos;
            }
            i++;
            currPos = (myHash(key) + probeOffset(key, i)) % tableSize;
            if (currPos < 0)
                currPos += tableSize;
            if (i > tableSize)
                return false;
        }

        collisionCount += i;
        int pos = (firDel != -1) ? firDel : currPos;
        table[pos] = HashEntry(key, new innerHashTable(hash2, tableSize), ACTIVE);
        table[pos].element.value->insert(key2, value);
        currSize++;
        insertsSinceResz++;
        double load = 1.0 * currSize / tableSize;
        // if (load > maxLoad && insertsSinceResz >= lastResizeElems / 2)
        // {
        //     rehash(true);
        // }
        return true;
    }
    void searchAll(const string &key) const
    {
        int hits = 0;
        int pos = findPos(key, hits);
        if (pos == -1)
        {
            cout << "No entries found for key: " << key << nl;
            return;
        }
        table[pos].element.value->printAll();
    }
    void searchOne(const string &key, const string &key2) const
    {
        int hits;
        int pos = findPos(key, hits);
        if (pos == -1)
        {
            cout << "No entries found for key: " << key << nl;
            return;
        }
        string val = table[pos].element.value->search(key2, hits);
        if (val == "")
        {
            cout << "No entry found for key: " << key2 << " under " << key << nl;
        }
        else
        {
            cout << "Entry found: ( " << key2 << " , " << val << " ) under " << key << nl;
        }
    }
    bool removeOuter(const string &key, const string &key2)
    {
        int hits;
        int pos = findPos(key, hits);
        if (pos == -1)
        {
            return false;
        }
        bool res = table[pos].element.value->remove(key2);
        return res;
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    outerHashTable ht(hash1, n);
    while (q--)
    {
        string cmnd;
        cin >> cmnd;
        if (cmnd == "INSERT")
        {
            string key, key2, value;
            cin >> key >> key2 >> value;
            ht.insertOuter(key, key2, value);
        }
        else if (cmnd == "SEARCH")
        {
            // input can be one or two keys
            string key, key2;
            cin >> key;
            if (cin.peek() != '\n')
            {
                // what does peek mean? -> it checks the next character in the input stream without extracting it. If it's not a newline, it means there's another key to read.
                cin >> key2;
                ht.searchOne(key, key2);
            }
            else
            {
                ht.searchAll(key);
            }
        }
        else if (cmnd == "DELETE")
        {
            string key, key2;
            cin >> key >> key2;
            ht.removeOuter(key, key2);
        }
    }
}






