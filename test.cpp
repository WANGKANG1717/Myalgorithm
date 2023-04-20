
/**
 * @date: 2023-04-20 19:34:29
 * @author: WangKang
 * @blog: kang17.xyz
 * @filepath: test.cpp
 * @description: 测试使用reverse预留空间对string的性能影响
 * Copyright 2023 WANGKANG, All Rights Reserved.
 */
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

const long long int N = 2000000000;
int main() {
    string tmp;
    tmp.reserve(N);
    cout << tmp.capacity() << endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < N; i++) {
        tmp.push_back('0');
    }
    end = clock();
    double res = (end - start) * 1.0 / CLOCKS_PER_SEC;
    cout << res << "s" << endl;

    return 0;
}