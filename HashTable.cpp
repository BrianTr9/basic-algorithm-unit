#include <bits/stdc++.h>
using namespace std;

// Simple fixed-capacity hash table with chaining (long long -> long long).
// Notes:
// - capacity should be a power of two for the index mask to work (default 2^16).
// - Uses std::hash<long long> and chaining via vectors.

struct HashTable {
    size_t cap;
    vector<vector<pair<long long,long long>>> table;
    HashTable(size_t capacity = 1u<<16) : cap(capacity), table(cap) {}

    inline size_t index_of(long long x) const {
        return (size_t)(std::hash<long long>{}(x)) & (cap - 1);
    }

    void put(long long key, long long value) {
        size_t i = index_of(key);
        for (auto &p : table[i]) if (p.first == key) { p.second = value; return; }
        table[i].push_back({key, value});
    }

    bool get(long long key, long long &out) const {
        size_t i = index_of(key);
        for (const auto &p : table[i]) if (p.first == key) { out = p.second; return true; }
        return false;
    }

    void erase(long long key) {
        size_t i = index_of(key);
        auto &bucket = table[i];
        for (size_t j = 0; j < bucket.size(); ++j) if (bucket[j].first == key) { bucket[j] = bucket.back(); bucket.pop_back(); return; }
    }
};

// Process commands (separated from main for clearer IO/logic separation)
// Input format:
// q
// then q lines, each: put k v | get k | erase k
void run_hash_table(istream &in, ostream &out){
    int q; if (!(in >> q)) return;
    HashTable hm;
    while (q--) {
        string op; in >> op;
        if (op == "put") {
            long long k, v; in >> k >> v; hm.put(k, v);
        } else if (op == "get") {
            long long k; in >> k; long long val;
            if (hm.get(k, val)) out << val << '\n'; else out << "null\n";
        } else if (op == "erase") {
            long long k; in >> k; hm.erase(k);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    run_hash_table(cin, cout);
    return 0;
}
