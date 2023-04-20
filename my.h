/**
 * @author: WangKang
 * @date: 2023-04-19 14:46:17
 * @blog: kang17.xyz
 * @filepath: my.h
 * @description: 主要用于实现一些额外的附加功能
 * Copyright 2023 WANGKANG, All Rights Reserved.
 */

/**
 * 写在前面
 *  本以为找到一个AES的包就可以万事大吉了，结果那个算法是有bug的，导致我无论如何都不能得出想要的结果4
 *  最后还是转投自己写的算法了。。。。。
 *  浪费了一天的时间。。。。。。
 *  2023/4/19
 */
// @date: 2023-04-19 14:46:48
// @brief: 已经实现信息加密功能，开始哈夫曼无损压缩算法的研究
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#define debug(x) cout << #x << "=" << x << endl
#define Error(x) cout << "ERROR: " << #x << endl;

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
using namespace std;
// 此数字用来加密密钥
const uint __KEY__ = 1717171717;
const uchar __ENCRYPT__ = 1;

const string CHAR = "0123456789";
/// @brief 随机数生成器 范围为0-RAND_MAX 这个范围不能满足较大数字的生成
/// @param low 下界（含）
/// @param high 上界（含）
/// @return 随机数
int randomNum(int low, int high) {
    return rand() % (high - low + 1) + low;
}

/// @brief 随机生成k位数的数字串
/// @param k 位数
/// @return k位数的数字串
string randomKey(uint k) {
    if (k <= 0) {
        return "0";
    }
    string key = "";
    srand((uint)(time(0)));
    for (int i = 0; i < k; i++) {
        // 需要保证是一个10位数
        if (i == 0) {
            key.push_back(CHAR[randomNum(1, 9)]);
        } else {
            key.push_back(CHAR[randomNum(0, 9)]);
        }
    }
    return key;
}

uint stringToUint(string x) {
    uint key = 0;
    for (int i = 0; i < x.size(); i++) {
        key = key * 10 + x[i] - '0';
    }
    return key;
}

string uintToString(uint x) {
    string key = "";
    while (x > 0) {
        key.push_back(x % 10 + '0');
        x /= 10;
    }
    reverse(key.begin(), key.end());
    return key;
}
/// @brief 得到9位数的随机key
/// @return uint型的key
uint getRandomKEY() {
    return stringToUint(randomKey(9));
}

void printByInt(string p) {
    for (int i = 0; i < p.size(); i++) {
        cout << (int)p[i] << " ";
    }
    cout << endl;
}

string Encrypt(string p, uint key) {
    // cout << bitset<32>(key) << endl;
    unsigned char one = ((key ^ 0xFF000000) >> 24);
    unsigned char two = ((key ^ 0x00FF0000) >> 16);
    unsigned char three = ((key ^ 0x0000FF00) >> 8);
    unsigned char four = ((key ^ 0x000000FF));
    uchar k[4] = {one, two, three, four};
    // cout << bitset<8>(one) << endl;
    // cout << bitset<8>(two) << endl;
    // cout << bitset<8>(three) << endl;
    // cout << bitset<8>(four) << endl;
    // 取出一个整数中的8位作为一个字符
    for (int i = 0; i < p.size(); i++) {
        int pos = i % 4;
        p[i] = p[i] ^ k[pos];
    }
    return p;
}

string Decrypt(string p, uint key) {
    return Encrypt(p, key);
}

//////////////////////////////哈夫曼算法/////////////////////
/**
 @date: 2023-04-19 19:39:05
 * 写到后面发现搞一个类比较好。。。。。。。。
 */
// N 代表255个颜色分量，也即要编码的叶子节点的数量 0-N-1(数据范围)
// sumN 代表总的哈夫曼树的节点总数
const uint N = 6;
const uint sumN = N * 2 - 1;
uint num[N];                  // 0-255存储的是颜色分量的个数（也即权值），不排序。
const uint MAXN = 100000000;  // 预先分配的比较大的空间
/**
 * @date: 2023-04-20 11:33:15
 * @brief: 调试用
 */
string pCode1;
string pCode2;

/** @date: 2023-04-19 16:17:22
 * color要编码的颜色
 * parent 父节点下标
 * lchild 左孩子下标
 * rchild 右孩子下标
 */
struct Node {
    uchar color;
    uint parent;
    uint lchild;
    uint rchild;
    uint weight;
    Node() {
        color = 0;
        parent = lchild = rchild = -1;
        weight = 0;
        /**
         * @date: 2023-04-20 17:47:58
         * @brief: 哈夫曼树的权重不能为0，否则会出现算法错误，如11112 N=6 0-5 你自己试一下就知道了
         *         解决办法：
         *             1.令初始权重为1
         *             2.先统计num，如果发现0-N-1存在权重为0的节点，则所有节点权重加1 ✓
         */
    }
    friend ostream &operator<<(ostream &out, const Node &a) {
        printf("<color:%d, weight:%d, parent:%d, lchild:%d, rchild:%d>", a.color, a.weight, a.parent, a.lchild, a.rchild);
        return out;
    }
} HuffmanTree[sumN];

void printHuffmanTree() {
    for (int i = 0; i < sumN; i++) {
        cout << i << " " << HuffmanTree[i] << endl;
    }
}
/**
 * @date: 2023-04-19 16:57:09
 * @description: 初始化函数
 */
void initHuffmanTree() {
    for (int i = 0; i < sumN; i++) {
        HuffmanTree[i] = Node();
    }
}

////////////////////////////////////////////////压缩部分///////////////////////////////////////////////
/**
 * @date: 2023-04-19 16:30:18
 * @param: minl 权值最小的节点1，作为左孩子
 * @param: minr 权值最小的节点2，作为右孩子
 * @param: k 当前取值的上限（不含）
 * @description: 在结构体中选取权值最小的两个节点，作为左孩子和右孩子
 */
const uint MAXNUM = 0xffffffff;
void getMinNode(uint &l, uint &r, uint k) {
    uint minl = MAXNUM;
    uint minr = MAXNUM;
    for (int i = 0; i < k; i++) {
        if (HuffmanTree[i].parent == -1) {  // 父节点为-1证明还没由加入哈夫曼树
            if (HuffmanTree[i].weight < minl) {
                l = i;
                minl = HuffmanTree[i].weight;
            } else if (HuffmanTree[i].weight < minr) {
                r = i;
                minr = HuffmanTree[i].weight;
            }
        }
    }
}

/**
 * @date: 2023-04-20 17:46:52
 * @brief: 这里有一个需要注意的点，权重不能为0，至少为1
 */
void generateHuffmanCode(uchar *data, uint dataSize, string HuffmanCode[N]) {
    fill(num, num + N, 1);
    // 统计不同颜色点的个数 0 - N-1
    for (int i = 0; i < dataSize; i++) {
        num[(uint)data[i]]++;
    }
    // 采用权重为零的第一种解决方案，即初试num[i]=1
    initHuffmanTree();
    // printHuffmanTree();
    // 设置好哈夫曼树结构体
    for (int i = 0; i < N; i++) {
        HuffmanTree[i].color = uchar(i);
        HuffmanTree[i].weight = num[i];
    }
    // 开始构造哈夫曼树
    for (uint p = N; p <= sumN - 1; p++) {
        uint minl, minr;
        getMinNode(minl, minr, p);
        HuffmanTree[minl].parent = p;
        HuffmanTree[minr].parent = p;
        HuffmanTree[p].lchild = minl;
        HuffmanTree[p].rchild = minr;
        HuffmanTree[p].weight = HuffmanTree[minl].weight + HuffmanTree[minr].weight;
    }
    // printHuffmanTree();
    // 生成哈夫曼编码
    /** @date: 2023-04-19 17:00:01
     * 规定左分支为0，右分支为1
     */
    for (int i = 0; i < N; i++) {
        string code = "";
        int cur = i;
        do {
            int parent = HuffmanTree[cur].parent;
            if (HuffmanTree[parent].lchild == cur) {
                code.push_back('0');
            } else if (HuffmanTree[parent].rchild == cur) {
                code.push_back('1');
            }
            cur = parent;
        } while (HuffmanTree[cur].parent != -1);
        reverse(code.begin(), code.end());
        HuffmanCode[i] = code;
    }
    // for (int i = 0; i < N; i++) {
    //     cout << HuffmanCode[i] << endl;
    // }
}

/**
 * @date: 2023-04-19 20:17:51
 * @param: pCode 要编码的串，pos pCode中的位置 8个为一组
 * @return: pos位置起8个01串的编码
 * @description: 将01串转换为二进制流
 */
uchar DeCode(string pCode, int pos) {
    uchar c = 0;
    for (int i = 0; i < 8; i++) {
        c = ((c << 1) + (pCode[pos + i] - '0'));
    }
    return c;
}

string &Convert2Binary(const string &pCode) {
    string *p = new string();
    *p = "";
    if (pCode.size() % 8 != 0) {
        cout << "pCode的长度错误,不为8的整数倍,请检查!" << endl;
        return *p;
    }
    p->reserve(MAXN);
    for (int i = 0; i < pCode.size(); i += 8) {
        p->push_back(DeCode(pCode, i));
    }
    p->shrink_to_fit();
    return *p;
}

/**
 * @date: 2023-04-19 15:15:54
 * @param: data 原数据
 * @param: dataSize 原数据大小
 * @param: res 压缩后的数据 初始值一定要置为NULL
 * @param: resSize 压缩后的数据大小
 * @description: 哈夫曼压缩图片数据
 */
void huffmanCompress(uchar *data, const uint &dataSize, uchar *&res, uint &resSize, string HuffmanCode[N]) {
    // 第一步，得到哈夫曼编码,存储在变量HuffmanCode中
    generateHuffmanCode((uchar *)data, dataSize, HuffmanCode);
    // printHuffmanTree();
    // for (int i = 0; i < N; i++) {
    //     cout << i << ":" << HuffmanCode[i] << endl;
    // }
    /** @date: 2023-04-19 17:27:31
     * pCode 存储待压缩数据的二进制串编码
     *       注意，因为要转换为字节表示，所以，pCode的长度必须为8的倍数，所以编码后，不足8的补零
     *       后面在解码的时候，要维护一个解码数num，保证只解码dataSize个数据
     */
    string pCode = "";
    pCode.reserve(dataSize);
    for (int i = 0; i < dataSize; i++) {
        pCode.append(HuffmanCode[(uchar)data[i]]);
    }
    // 补足长度
    int offset = (8 - pCode.size() % 8) % 8;  // 这个公式要理解
    for (int i = 0; i < offset; i++) {
        pCode.push_back('0');
    }
    pCode.shrink_to_fit();
    // cout << pCode << endl;
    // cout << pCode.size() << endl;
    pCode1 = pCode;
    // cout << "huffmanCompress:" << endl;
    // cout << "pCode:" << endl;
    // cout << pCode << endl;
    // cout << pCode.size() << endl;
    // cout << "----------------------------------" << endl;
    /**
     * @date: 2023-04-19 17:34:05
     * 将01字符串转换为二进制数据
     */
    string p = Convert2Binary(pCode);
    // debug("Convert2Binary");
    // debug(p.size());
    // debug(pCode.size());
    if (p.size() * 8 != pCode.size()) {
        Error("p.size()*8!=pCode.size()");
        exit(0);
    }
    resSize = p.size();
    // 注意
    if (res != NULL) {
        delete[] res;
    }
    res = new uchar[resSize + 10];
    for (int i = 0; i < resSize; i++) {
        res[i] = (uchar)p[i];  // 这里可能存在一定的转换问题
    }
    cout << "压缩成功，数据已返回！\n";
}

/**
 * @date: 2023-04-19 20:18:58
 * @param: c 要转换为01串的字符
 * @return: 01串
 * @description: 将字符解码为01串
 */
string EnCode(uchar c) {
    string p = "";
    for (int i = 0; i < 8; i++) {
        p.push_back(uchar(c % 2 + (uchar)'0'));
        c >>= 1;
    }
    reverse(p.begin(), p.end());
    return p;
}

/**
 * @date: 2023-04-19 20:13:42
 * @param: res 压缩后的数据
 * @param: resSize 数据大小
 * @return: 二进制01字符串（哈夫曼编码串的合集）
 * @description: 为了方便起见，这里和之前的逆过程有点出入，不管了
 */
string Binary2Convert(uchar *res, uint resSize) {
    string pCode = "";
    for (int i = 0; i < resSize; i++) {
        pCode.append(EnCode(res[i]));
    }
    return pCode;
}

//////////////////////////////////////////////////解压缩部分//////////////////////////////////////////////////////
/**
 * @date: 2023-04-19 20:59:43
 * 为了方便的进行解码，拟打算根据哈夫曼编码构造一棵链式二叉树
 */

typedef struct LinkNode {
    uchar color;
    bool isLeaf;  // 用来判断是否是叶节点（不加也行，只需要判断左右孩子为空即可）
    LinkNode *lchild;
    LinkNode *rchild;
    LinkNode() {
        color = 0;
        isLeaf = false;
        lchild = NULL;
        rchild = NULL;
    }
} *LinkHuffmanTree;

void printLinkHuffmanTree(LinkHuffmanTree T) {
    if (T == NULL) {
        return;
    }
    if (T->isLeaf == true && (T->lchild != NULL || T->rchild != NULL)) {
        Error("383 line");
    }
    cout << (uint)(T->color) << endl;
    if (T->lchild) printLinkHuffmanTree(T->lchild);
    if (T->rchild) printLinkHuffmanTree(T->rchild);
}

/**
 * @date: 2023-04-19 21:11:15
 * @param: T 要插入的哈夫曼树
 * @param: c 叶子节点中的color
 * @param: huffcode color的哈夫曼编码
 * @param: pos 现在走到那个位置了
 * @description: 注意，千万别忘了在T前面加&
 */

void insertIntoLinkHuffmanTree(LinkHuffmanTree &T, const uchar &c, const string &huffcode, int pos, const int &len) {
    if (T == NULL) {
        T = new LinkNode();
    }

    if (pos == len) {
        T->color = c;
        T->isLeaf = true;
        return;
    }

    if (huffcode[pos] == '0') {  // 向左走
        insertIntoLinkHuffmanTree(T->lchild, c, huffcode, pos + 1, len);
    } else if (huffcode[pos] == '1') {  // 向右走
        insertIntoLinkHuffmanTree(T->rchild, c, huffcode, pos + 1, len);
    } else {
        cout << "Error Code!" << endl;
        exit(0);
    }
}

LinkHuffmanTree generateHuffmanTree(const string HuffmanCode[N]) {
    LinkHuffmanTree T = NULL;
    for (int i = 0; i < N; i++) {
        insertIntoLinkHuffmanTree(T, uchar(i), HuffmanCode[i], 0, HuffmanCode[i].size());
    }
    return T;
}

/**
 * @date: 2023-04-20 11:50:23
 * @param: pCode 01哈夫曼编码串
 * @param: dataSzie 原本的数据大小
 * @param: T 哈夫曼编码树
 * @return: 解码后的数据
 * @description: 得到解码后的数据
 */
string getData(const string pCode, uint dataSize, LinkHuffmanTree T) {
    if (T == NULL) {
        cout << "Error T==NULL getData" << endl;
        exit(0);
    }
    string p = "";
    LinkHuffmanTree cur = T;
    for (int i = 0; i < pCode.size(); i++) {
        if (pCode[i] == '0') {
            cur = cur->lchild;
        } else if (pCode[i] == '1') {
            cur = cur->rchild;
        } else {
            cout << "Error code getData!" << endl;
            exit(0);
        }
        if (cur == NULL) {
            cout << "ERROR cur==NULL getdata" << endl;
            exit(0);
        }
        // 来到叶子节点
        if (cur->isLeaf == true) {
            p.push_back(cur->color);
            if (p.size() == dataSize) break;  // 说明已经获取到足够的数据了
            cur = T;
        }
    }
    return p;
}

/**
 * @date: 2023-04-19 19:33:41
 * @param: data 解压后的数据存放的位置
 * @param: dataSize 预计解压大小，也就是原来的数据的大小
 * @param: res 压缩数据
 * @param: resSize 压缩数据的大小
 * @param: HuffmanCode 哈夫曼编码 也就是压缩时得到的哈夫曼编码
 * @description:
 *      哈夫曼解压缩算法主函数
 *      这里为了和压缩算法保持对称性，这里不改变数据的相对位置
 *      另外,要记住,因为在压缩时,为了保证01字符串长度为8的倍数,而向01串添加了冗余数据
 *      因此,为了准确的拿到原本的数据,需要保留压缩前的数据大小dataSize
 *
 */
void huffmanDecompress(uchar *&data, const uint dataSize, uchar *res, const uint resSize, const string HuffmanCode[N]) {
    /**
     @date: 2023-04-19 20:11:53
     * 这里为了简单起见，直接得到二进制字符串
     */
    string pCode = Binary2Convert(res, resSize);
    pCode2 = pCode;
    if (pCode1 != pCode2) {
        cout << "Error pCode1!=pCode2" << endl;
    }
    // cout << "huffmanDecompress:" << endl;
    // cout << "pCode:\n"
    //      << pCode << endl;
    // cout << "--------------------------------------" << endl;
    /**
     * @date: 2023-04-19 20:51:10
     * 流程：
     * 1，使用哈夫曼编码获得哈夫曼树
     * 2，通过哈夫曼树解码01串
     */
    LinkHuffmanTree T = generateHuffmanTree(HuffmanCode);  // 经过调试，应该没什么问题了
    // printLinkHuffmanTree(T);
    /**
     * @date: 2023-04-20 10:22:29
     * 解码得到原来的编码
     */
    string p = getData(pCode, dataSize, T);
    // for (int i = 0; i < dataSize; i++) {
    //     cout << p[i];
    // }
    // cout << endl;
    if (data != NULL) {
        delete data;
    }
    data = new uchar[dataSize + 10];  // 多申请点空间
    for (int i = 0; i < dataSize; i++) {
        data[i] = (uchar)p[i];
    }
    cout << "解压缩成功，数据已返回" << endl;
}

/**
 * 预计流程：
 * 统计0-255像素点的个数
 * 构造哈夫曼树
 * 生成哈夫曼编码
 * 由data数据生成哈夫曼编码字符串
 * 由编码串生成二进制串
 * 返回数据
 */
/**
 * 哈夫曼树可以采用数组，也可以采用树，这里采用数组吧！难度基本一样的
 */