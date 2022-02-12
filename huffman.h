#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <queue>
#include <stack>
#include <map>
#include <iostream>
#include <utility>
#include "Timer.h"
#include "FileIO.h"

using namespace std;

class Node {    // ���� Ʈ���� �����ϱ� ���� ��� Ŭ����
public:
    Node() : left(nullptr), right(nullptr), cnt(0), ch(0) {}
    Node(char ch, int cnt) : left(nullptr), right(nullptr), cnt(cnt), ch(ch) {}
    Node(Node* left, Node* right) : left(left), right(right), cnt(left->cnt + right->cnt), ch(0) {}

    bool operator()(const Node* lhs, const Node* rhs) const;

    Node* left;
    Node* right;
    unsigned int cnt;   // �� ������ �󵵸� �����ϴ� ����
    char ch;    // ���ڸ� �����ϴ� ����
};

class Huffman { // ������ �ڵ��� ���� Huffman Ŭ����
public:
    Huffman() : root(nullptr), code(""), filename(""), amount(0), codesize(0), input_filesize(0), output_filesize(0) {}
    ~Huffman();

    void encoding(const string& input); // ���ڵ�
    void decoding(string filename); // ���� ���� ����

    double fileSize(const string filename);  // ���� ũ�� ��ȯ
    void creatHfFile(string filename);  // ���� ������ �����Ѵ�.

    void printHfTable();   // ������ ���̺� ���
    void printEncodingResult(); // ��� ���� ���
    void printDecodingResult(); // ���� ��� ���� ���
    void printCompressibility();    // ����� ���(���� ���� ũ��, ��� ���� ũ��, �����)
    void printAverageBit(); // ���� �� ��� ��Ʈ �� ���
    string printCode() const; // ������ �ڵ� ���
    
private:
    Node* root;  // ������ Ʈ���� ��Ʈ ��带 ����Ų��. 
    string code;    // ���� ��ü�� ������ �ڵ�
    string filename;    // �Է� ���� �̸�
    map<char, int> mf;  // ���ڿ� �󵵸� �����ϴ� ��
    map<char, string> ms;   // ���ڿ� ������ �ڵ带 �����ϴ� ��
    map<char, char> md;  // ���ڿ� ������ �ڵ� ���̸� �����ϴ� ��
    int amount;    // �󵵰� 1 �̻��� ������ ������ �����ϴ� ����
    long codesize;   // �ڵ��� ���� �����ϴ� ����

    void makeHfTable(const string& input); // ���� ������ ������ �ڵ�� ��ȯ

    long double input_filesize; // �Է� ���� ������
    long double output_filesize;    // ��� ���� ������
};

#endif