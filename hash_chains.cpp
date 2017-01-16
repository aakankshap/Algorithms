#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <map>

using std::string;
using std::deque;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    //vector<string> elems;
    std::map<long long, std::deque<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            //for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
            /*for (int i = 0; i < static_cast<int>(elems.size()); i++)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
                    */
            auto it = elems.find(query.ind);
            if (it != elems.end()) {
               for (auto i = 0; i < elems[query.ind].size(); i++) {
                  std::cout << elems[query.ind][i] << " ";
               }
            }
            std::cout << "\n";
        } else {
            auto hash_val = hash_func(query.s);
            //std::cout << "Current query is " << query.s << " hash val is " << hash_val << std::endl;
            auto it = elems.find(hash_val);
            if (query.type == "find") {
               deque<string>::iterator deq_iter;
               if (it != elems.end()) {
                  for (deq_iter = it->second.begin(); deq_iter != it->second.end(); ++deq_iter) {
                     if (*deq_iter == query.s) {
                        writeSearchResult(true);
                        goto end;
                     }
                  }
                  writeSearchResult(false);
                } else {
                  writeSearchResult(false);
                }
               end: {
               }
            }
            else if (query.type == "add") {
                if (it == elems.end()) {
                  elems[hash_val].push_front(query.s);
                } else {
                   //std::cout << " Query " << query.s << " is already present " << std::endl;
                   if (std::find(it->second.begin(), it->second.end(), query.s) == it->second.end()) {
                     //std::cout << " Adding query " << query.s << std::endl;
                     elems[hash_val].push_front(query.s);
                  } else {
                     //std::cout << "Duplicate! Not adding " << std::endl;
                  }
                }
            } else if (query.type == "del") {
                if (it != elems.end()) {
                     //std::cout << " Length of queue is " << it->second.size() << std::endl;
                     for (auto deq_iter = it->second.begin(); deq_iter != it->second.end(); ++deq_iter) {
                        if (*deq_iter == query.s) {
                           it->second.erase(deq_iter);
                           if (it->second.empty()) {
                              elems.erase(it);
                           }
                           break;
                        }
                     }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
