#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

int array[3000];

//请根据需要自行补充代码，下面的函数框架仅供参考
// 提交下面的代码

// v 是数组，start是起始下标（含），end是终止下标（含）
void mysort(int* v, int start, int end)
{
    if (start >= end) return;
    int mid = v[(start + end) / 2];
    int i = start, j = end;
    while (i <= j) {
        while (v[i] < mid) i++;
        while (v[j] > mid) j--;
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    if (start < j) mysort(v, start, j);
    if (i < end) mysort(v, i, end);
}
// k是关键字，v 是数组，start是起始下标（含），end是终止下标（含）
int bSearch(int k, int * v, int start, int end)
{
    while (start <= end) {
        int mid = (start + end) / 2;
        if (v[mid] == k) return mid;
        else if (v[mid] < k) start = mid + 1;
        else end = mid - 1;
    }
    return -1;
}


//请根据需要在上面自行补充代码
// 提交以上的代码

int main() {
    //default_random_engine e;
    int seed;
    cin >> seed;
    srand(seed); //e.seed(seed);
    for (int i = 0; i < 3000; ++i)
        array[i] = (random() & 0x3FFF); // (e() & 0x3FFF);

    mysort(array, 0, 2999); // 注意是2999
    for (int i = 0; i < 2999; i++)
        if (array[i+1] < array[i]) cout << "Error: " << i << " - " << array[i+1] << '/' << array[i] << endl;
    for (int i = 0; i < 3000; i+=100)
        cout << array[i] << ' ';
    cout << endl;
    for (int i = 0; i < 10; ++i) {
        int k, found;
        cin >> k;
        found = bSearch(k, array, 0, 2999);
        cout << found << ' ';
    }
    cout << endl;
 
    return 0;
}