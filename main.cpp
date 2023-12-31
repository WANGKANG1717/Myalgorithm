#include "my.h"
// 111111111122222333344444566777888899990000
// 111111111122222333344444566777888899990000
/**
 * @date: 2023-04-20 09:44:20
 * 统一使用new 和 delete 来管理内存
 */
#include "cpp/basic.cpp"
#include "cpp/header/AdaptableMessageHeader.cpp"
#include "cpp/header/ColorPalette.cpp"
#include "cpp/header/FileHeader.cpp"
#include "cpp/header/ImageBitmapData.cpp"
#include "cpp/header/MessageHeader.cpp"
#include "cpp/imgType/BMP.cpp"
#include "cpp/imgType/DIMG.cpp"
#include "head/basic.h"
#include "head/header/AdaptableMessageHeader.h"
#include "head/header/ColorPalette.h"
#include "head/header/FileHeader.h"
#include "head/header/ImageBitmapData.h"
#include "head/header/MessageHeader.h"
#include "head/imgType/BMP.h"
#include "head/imgType/DIMG.h"
int main() {
    /*     DIMG dimg("11呃呃.dimg");
        uint dataSize = dimg.getImgData().getSize();
        cout << dataSize << endl;
        uchar *data = new uchar[dataSize + 10];
        uchar *res = NULL;
        uint resSize;
        memcpy(data, dimg.getImgData().getImgData(), dataSize);
        string HuffmanCode[N];
        huffmanCompress(data, dataSize, res, resSize, HuffmanCode);
        // debug(dataSize);
        // uchar *data2 = NULL;
        // huffmanDecompress(data2, dataSize, res, resSize, HuffmanCode);
        // for (int i = 0; i < dataSize; i++) {
        //     if (data[i] != data2[i]) {
        //         Error("data[i] != data2[i]");
        //         exit(0);
        //     }
        // }
        cout << "压缩前数据大小:" << dataSize << endl;
        cout << "压缩后数据大小:" << resSize << endl;
        cout << "压缩率:" << (resSize * 1.0 / dataSize) * 100 << "%" << endl;
        cout << "数据一致！恭喜恭喜！！！" << endl; */
    /*     // char *data = "111111111122222333344444566777888899990000";
        // char *data = "11111111111231231231231";
        char *data = "122333444455555000000";
        uint dataSize = strlen(data);
        uchar *res = NULL;
        uint resSize = -1;
        string HuffmanCode[N];
        /////////////////////////压缩/////////////////////////////
        huffmanCompress((uchar *)data, dataSize, res, resSize, HuffmanCode);
        // for (int i = 0; i < resSize; i++) {
        //     cout << bitset<8>(res[i]);
        // }
        // cout << endl;
        // /////////////////////////解压缩////////////////////////////
        uchar *data2 = NULL;
        huffmanDecompress(data2, dataSize, res, resSize, HuffmanCode);

        for (int i = 0; i < dataSize; i++) {
            if (data2[i] != data[i]) {
                cout << "Error data2[i]!=data[i]" << endl;
                exit(0);
            }
        }
        cout << "数据一致，请放心使用！" << endl; */

    ///////////////////////////////////////////////////////////////////////////////////////
    // 122333444455555000000
    // string tmp = "122333444455555000000";
    // string pCodeModel = "111011111111110110110000000000101010101101010101010";
    //                  "11101111111111011011000000000010101010110101010101000000"
    //                  "11101111111111011011000000000010101010110101010101000000"
    string tmp = "";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i + 1; j++) {
            tmp.push_back((uchar)i);
        }
    }
    // for (int i = 0; i < 100000; i++) {
    //     tmp.push_back((uchar)255);
    // }
    for (int i = 0; i < 100000; i++) {
        tmp.push_back((uchar)200);
    }
    /*     tmp.reserve(10000000);
        srand((uint)(time(0)));
        for (int i = 0; i < 100000; i++) {
            tmp.push_back((uchar)randomNum(0, N - 1));
        }
        tmp.shrink_to_fit(); */
    // for (int i = 0; i < 1000000; i++) {
    //     cout << (uint)tmp[i];
    // }
    // cout << tmp.size() << endl;
    uint dataSize = tmp.size();
    uchar *data = new uchar[dataSize];
    uchar *res = NULL;
    uint resSize;
    for (int i = 0; i < dataSize; i++) {
        data[i] = tmp[i];
    }
    string HuffmanCode[N];
    huffmanCompress(data, dataSize, res, resSize, HuffmanCode);
    // debug(dataSize);
    uchar *data2 = NULL;
    huffmanDecompress(data2, dataSize, res, resSize, HuffmanCode);
    for (int i = 0; i < dataSize; i++) {
        if (data[i] != data2[i]) {
            Error("data[i] != data2[i]");
            exit(0);
        }
    }
    cout << "压缩前数据大小:" << dataSize << endl;
    cout << "压缩后数据大小:" << resSize << endl;
    cout << "压缩率:" << (resSize * 1.0 / dataSize) * 100 << "%" << endl;
    cout << "数据一致！恭喜恭喜！！！" << endl;
    // for (int i = 0; i < N; i++) {
    //     cout << HuffmanCode[i] << endl;
    // }
    // for (int i = 0; i < dataSize; i++) {
    //     cout << (uint)data2[i];
    // }
    // cout << endl;

    // cout << resSize << endl;
    // for (int i = 0; i < resSize; i++) {
    //     cout << bitset<8>(res[i]);
    // }
    // for (int i = 0; i < N; i++) {
    //     cout << HuffmanCode[i] << endl;
    // }

    // for (int i = 0; i < dataSize; i++) {
    //     // cout << char(data[i] + '0');
    //     cout << (uint)data[i];
    // }

    ///////////////////////////////////////////////////////////////////////////////////////
    // for (int i = 0; i < N; i++) {
    //     cout << HuffmanCode[i] << " " << HuffmanCode[i].size() << endl;
    // }
    // for (int i = 0; i < N; i++) {
    //     cout << HuffmanCode[i] << endl;
    // }
    // huffmanDecompress(data2, dataSize, res, resSize, HuffmanCode);
    // uchar c = 45;
    // cout << EnCode(c) << endl;
    // for (uchar c = 0; c <= 255; c++) {
    //     if (DeCode(EnCode(c), 0) != c) {
    //         cout << "ERROR" << endl;
    //     }
    //     if (c == 255) {
    //         break;
    //     }
    // }
    // string p = "";
    // p.push_back((uchar)0);
    // cout << p.size() << endl;
    // cout << (int)'\0' << endl;
    // cout << p << endl;
    // for (uchar i = 0; i <= 255; i++) {
    //     p.push_back((uchar)i);
    //     if (i == 255) break;
    //     // cout << (ushort)i << endl;
    // }
    // string pp = p;
    // cout << p << endl;
    // cout << p.size() << endl;
    // cout << p << endl;
    // const char *s = new char[100000];
    // s = p.c_str();
    // cout << strlen(s) << endl;
    // for (int i = 0; i <= 255; i++) {
    //     cout << s[i];
    // }
    // cout << endl;
    // cout << strlen(s) << endl;

    // for (int i = 0; i <= 255; i++) {
    //     cout << p[i] << endl;
    // }
    ///////////////////////////////////////////////////////////////////////////////////
    // char *data = "111111111122222333344444566777888899990000";
    // uint dataSize = strlen(data);
    // uchar *res;
    // uint resSize = -1;
    // string HuffmanCode[N];
    // // getHuffmanCode((uchar *)data, dataSize, HuffmanCode);
    // /////////////////////////压缩/////////////////////////////
    // huffmanCompress((uchar *)data, dataSize, res, resSize, HuffmanCode);
    // // cout << data << endl;
    // // cout << dataSize << endl;
    // // cout << resSize << endl;
    // /////////////////////////解压缩////////////////////////////
    // uchar data2[100000];
    // // for (int i = 0; i < N; i++) {
    // //     cout << HuffmanCode[i] << endl;
    // // }
    // // huffmanDecompress(data2, dataSize, res, resSize, HuffmanCode);
    // string pCode = "1010101010101010101001001001001001011111111111111110110110110110111101011011111011111001100110000000000000000100100100111101110111011100";
    // string p = Convert2Binary(pCode);
    // for (int i = 0; i < resSize; i++) {
    //     if (p[i] != res[i]) {
    //         cout << "ERROR" << endl;
    //     }
    // }
    // for (int i = 0; i < p.size(); i++) {
    //     cout << uint(p[i]) << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < resSize; i++) {
    //     cout << uint(res[i]) << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < resSize; i++) {
    //     cout << bitset<8>(res[i]);
    // }
    // cout << endl;
    // cout << endl;
    /*     string pCode = "1010101010101010101001001001001001011111111111111110110110110110111101011011111011111001100110000000000000000100100100111101110111011100";
        // cout << pCode.size() << endl;
        // string p = Convert2Binary(pCode);
        // for (int i = 0; i < p.size(); i++) {
        //     cout << bitset<8>(p[i]);
        // }
        // cout << endl;
        string p2 = "1010101010101010101001001001001001011111111111111110110110110110111101011011111011111001100110000000000000000100100100111101110111011100";
        cout << (pCode == p2) << endl; */
    return 0;
}
// #include "my.h"
// #define debug(x) cout << #x << "=" << x << endl
// int main() {
//     // srand((uint)time(0));
//     // for (int i = 0; i < 100; i++) {
//     //     string key = randomKey(9);
//     //     cout << key << endl;
//     //     uint key2 = stringToUint(key);
//     //     cout << key2 << endl;
//     //     string key3 = uintToString(key2);
//     //     cout << key3 << endl;
//     // }
//     // uint key = getRandomKEY();
//     // debug(key);
//     // string p = "wa ajks k的卡还贷款看到发不发了u点十八点卡巴八分+零八分吧看见那!@#$$%^^&*()\\+-*/55++\\\\/\\|}{\\]\\]\\[[:L\"\\L\\L>>??\"LKM<LPUYYGFVBVHJGYG\"\\]\\]}";

//     // // debug(p);
//     // for (int i = 0; i < 10000000; i++) {
//     //     uint key = getRandomKEY();
//     //     string p1, p2;
//     //     p1 = MyDecrypt(p, key);
//     //     p2 = MyDecrypt(p1, key);
//     //     if (p2 != p) {
//     //         cout << "Error!" << endl;
//     //     }
//     // }

//     // debug(p1);

//     // debug(p2);
//     // srand((uint)(time(0)));
//     // string KEY = randomKey(9);
//     // debug(KEY);
//     // uint key = stringToUint(KEY);
//     // string key = randomKey();
//     // string p = "1111111111111111111111111111大多数的大大大苏打实打实的大大撒大苏打撒旦大苏打大";
//     // debug(p);
//     // // debug(key);
//     // p = MyEncrypt(p, 1212);
//     // debug(p);
//     // p = MyDecrypt(p, 1212);
//     // debug(p);
//     //
//     // for (int i = 0; i < 10; i++) {
//     //     string p = randomNum(9);
//     //     cout << p << endl;
//     //     cout << stringToUint(p) << endl;
//     //     // cout << randomKey() << endl;
//     // }
//     // string key = randomKey();
//     // cout << key << endl;
//     // string num = randomNum(9);
//     // cout << num << endl;
//     // string KEY = key + num;
//     // cout << key.length() << " " << num.length() << endl;
//     // cout << KEY << endl;
//     // cout << KEY.substr(0, 16) << endl;
//     // cout << KEY.substr(16, 16 + 9) << endl;

//     // srand((unsigned int)(time(0)));
//     // cout << randomNUM(0, 2147483647) << endl;
//     // string p = "我是王庆康";
//     // string p1 = MyEncrypt(p, 0);
//     // string p2 = MyDecrypt(p1, 0);
//     // cout << p << endl;
//     // cout << p1 << endl;
//     // cout << p2 << endl;
//     // cout << randomKey() << endl;
//     // string p = "11212122121212122";
//     // cout << p << endl;
//     // for (int i = 0; i < p.size(); i++) {
//     //     cout << int(p[i]) << " ";
//     // }
//     // cout << endl;
//     // // string p2 = MyEncrypt(p, 4294967295);
//     // string p2 = MyEncrypt(p, 1111111111);
//     // for (int i = 0; i < p2.size(); i++) {
//     //     cout << int(p2[i]) << " ";
//     // }
//     // cout << endl;

//     // string p3 = MyEncrypt(p2, 1111111111);
//     // for (int i = 0; i < p3.size(); i++) {
//     //     cout << int(p3[i]) << " ";
//     // }
//     // cout << endl;
//     // cout << p3 << endl;

//     // string p = "ASDAD";
//     // string key = "1234567890123456";
//     // string res = AES(p, key);
//     // for (int i = 0; i < res.length(); i++) {
//     //     cout << (int)res[i] << " ";
//     // }
//     // cout << endl;
//     // string res2 = DeAES(res, key);
//     // for (int i = 0; i < res2.length(); i++) {
//     //     cout << (int)res2[i] << " ";
//     // }
//     // cout << endl;
//     // cout << res2 << endl;
//     return 0;
// }
// #include "aes.cpp"
// #include "aes.h"
// // 其它头文件
// int main(int argc, char const *argv[]) {
//     // 加密, 其中plain是明文字符数组， len是长度， key是密钥
//     char plain[] = "1234567890123456";
//     int len = 16;
//     char key[] = "1234567890123456";
//     for (int i = 0; i < len; i++) {
//         printf("%d ", plain[i]);
//     }
//     printf("\n");
//     aes(plain, len, key);
//     for (int i = 0; i < len; i++) {
//         printf("%d ", plain[i]);
//     }
//     printf("\n");
//     printf("%s\n", key);
//     // 解密，其中ciphertext是密文字符数组， len是长度， key是密钥
//     char ciphertext[20];
//     strcpy(ciphertext, plain);
//     for (int i = 0; i < len; i++) {
//         printf("%d ", ciphertext[i]);
//     }
//     printf("\n");
//     deAes(ciphertext, len, key);
//     for (int i = 0; i < len; i++) {
//         printf("%d ", ciphertext[i]);
//     }
//     printf("\n");
// }
