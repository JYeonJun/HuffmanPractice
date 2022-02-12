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

class Node {    // 이진 트리를 구성하기 위한 노드 클래스
public:
    Node() : left(nullptr), right(nullptr), cnt(0), ch(0) {}
    Node(char ch, int cnt) : left(nullptr), right(nullptr), cnt(cnt), ch(ch) {}
    Node(Node* left, Node* right) : left(left), right(right), cnt(left->cnt + right->cnt), ch(0) {}

    bool operator()(const Node* lhs, const Node* rhs) const;

    Node* left;
    Node* right;
    unsigned int cnt;   // 각 문자의 빈도를 저장하는 변수
    char ch;    // 문자를 저장하는 변수
};

class Huffman { // 허프만 코딩을 위한 Huffman 클래스
public:
    Huffman() : root(nullptr), code(""), filename(""), amount(0), codesize(0), input_filesize(0), output_filesize(0) {}
    ~Huffman();

    void encoding(const string& input); // 인코딩
    void decoding(string filename); // 복원 파일 생성

    double fileSize(const string filename);  // 파일 크기 반환
    void creatHfFile(string filename);  // 압축 파일을 생성한다.

    void printHfTable();   // 허프만 테이블 출력
    void printEncodingResult(); // 결과 파일 출력
    void printDecodingResult(); // 복원 결과 파일 출력
    void printCompressibility();    // 압축률 출력(원본 파일 크기, 결과 파일 크기, 압축률)
    void printAverageBit(); // 문자 당 평균 비트 수 출력
    string printCode() const; // 허프만 코드 출력
    
private:
    Node* root;  // 허프만 트리의 루트 노드를 가리킨다. 
    string code;    // 파일 전체의 허프만 코드
    string filename;    // 입력 파일 이름
    map<char, int> mf;  // 문자와 빈도를 저장하는 맵
    map<char, string> ms;   // 문자와 허프만 코드를 저장하는 맵
    map<char, char> md;  // 문자와 허프만 코드 길이를 저장하는 맵
    int amount;    // 빈도가 1 이상인 문자의 개수를 저장하는 변수
    long codesize;   // 코드의 길이 저장하는 변수

    void makeHfTable(const string& input); // 파일 내용을 허프만 코드로 변환

    long double input_filesize; // 입력 파일 사이즈
    long double output_filesize;    // 결과 파일 사이즈
};

#endif