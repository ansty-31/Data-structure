#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

const int SIZE = 3079;

// bucket 中的节点
struct hashtable_node {
    hashtable_node * next;
    int key;
    string val;  
};


hashtable_node * new_ht_node(int key, string _val, hashtable_node * _next) {
    hashtable_node * node = new hashtable_node;
    node -> key = key;
    node -> val = _val;
    node -> next = _next;
    return node;
}

struct hashtable {
    hashtable_node * buckets[SIZE]; // bucket 数组
    size_t num_elements; //  元素个数
};

void clear(hashtable * ht);
// 您要提交的代码从这里开始

// 根据函数的框架补充代码，并一起提交。
//创建一个哈希表
hashtable * new_hashtable(size_t n)
{
    hashtable * ht = new hashtable;
    ht->num_elements = 0;
    for (size_t i = 0; i < n; ++i) {
        ht->buckets[i] = nullptr;
    }
    return ht;
}

//销毁一个哈希表
void destroy_hashtable(hashtable * & ht)
{
    clear(ht);
    delete ht;
    ht = nullptr;
}

static size_t myhash(unsigned long x)
{
    return x % SIZE;
}  //请自行补充代码，建议素数 3079

//在哈希表中插入一个元素(key, val)
bool put(hashtable * ht, int key, string val)
{
    size_t index = myhash(static_cast<unsigned long>(key));
    hashtable_node * curr = ht->buckets[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return false;  // 已存在，返回 false
        }
        curr = curr->next;
    }
    hashtable_node * newNode = new_ht_node(key, val, ht->buckets[index]);
    ht->buckets[index] = newNode;
    ht->num_elements++;
    return true;
}    //  不重复插入。已存在，返回 false
 
//根据key从哈希表中取得一个元素，如果不存在，返回false；否则返回true
bool get(const hashtable * ht, int key, string & val)
{
    size_t index = myhash(static_cast<unsigned long>(key));
    hashtable_node * curr = ht->buckets[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            val = curr->val;
            return true;  // 找到，返回 true
        }
        curr = curr->next;
    }
    return false;  // 未找到，返回 false
}

//  清除哈希表ht中所有的节点
void clear(hashtable * ht)
{
    for (size_t i = 0; i < SIZE; ++i) {
        hashtable_node * curr = ht->buckets[i];
        while (curr != nullptr) {
            hashtable_node * temp = curr;
            curr = curr->next;
            delete temp;
        }
        ht->buckets[i] = nullptr;
    }
    ht->num_elements = 0;
}

// 您要提交的代码到这里结束


int main() {
    hashtable * ht = new_hashtable(3079);
    int seed = 0;

    cin >> seed;
    srand(seed); // 自己先随便输入一个整数
    for (int i = 0; i < 1000; ++i) {
        int x = (rand() & 0x7FFF);
        stringstream ss;
        //cout << x << ' '; // 自己调试时使用
        ss << x;
        char tmp[10];
        tmp[0] = 'A' + x % 26;
        tmp[1] = 'a' + ((x % 100) * x) % 26;
        tmp[2] = 0;
        bool ok = put(ht, x, ss.str() + tmp);
        if (!ok) {
            cout << x << " Dup, ";
            if ((x & 3) == 0) cout << endl;
        }
    }
    cout << endl;

    for (int i = 0; i < 15; ++i) {
        int k;
        string val = "None";
        bool found;
        cin >> k;
        found = get(ht, k, val);
        cout << k << ' ' << found << ", " << val << endl;
    }
    cout << endl;

    return 0;
}

