
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

const long long int N = 1000000000;
/**
 * @date: 2023-04-20 19:44:33
 * @author: WANGKANG
 * @description: 经过测试，预留空间后，string1的速度的确提高了一点，但不是很快
 */
int main() {
    string tmp;
    cout << tmp.capacity() << endl;
    clock_t start, end;
    string p = "111111";
    start = clock();
    tmp.reserve(10 * N + 1000);
    // for (int i = 0; i < N * 6; i++) {
    //     tmp.push_back('1');
    // }
    // for (int i = 0; i < N; i++) {
    //     tmp.append(p);
    // }
    tmp.shrink_to_fit();
    end = clock();

    cout << tmp.capacity() << endl;
    double res = (end - start) * 1.0 / CLOCKS_PER_SEC;
    cout << res << "s" << endl;

    return 0;
}