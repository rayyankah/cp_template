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
