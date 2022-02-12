#include "huffman.h"
#include "Timer.h"
#include "FileIO.h"

void Huffman::decoding(string filename) {  // 복원

    ifstream fin;
    ofstream fout;
    int num;    // 전체 문자 개수
    char ch;    // 문자
    char codeln;    // 허프만 코드 길이
    char hfcode;    // 각 문자의 허프만 코드를 읽어올 변수
    string ret = "";
    Node* cur;
    string huff = "complete.txt";
    long size;

    Node* node = new Node();

    root = node;

    fin.open(filename, ios_base::in | ios_base::binary);
    fin.unsetf(ios::skipws);

    // 저장할 파일명 생성
    filename.erase(filename.find("huff"), 4);
    filename.replace(filename.find('.'), filename.length() - filename.find('.'), huff);
    this->filename = filename;
    
    fout.open(filename, ios_base::out | ios_base::trunc);   // 텍스트 모드

    /* 헤더 파일 정보 읽기 */
    fin >> size;
    fin >> ch;
    fin >> num;

    for (int i = 0; i < num; i++) { // 문자의 개수만큼 정보를 읽어온다.
        ret = "";
        cur = root;
        fin >> ch;
        fin >> codeln;

        /* 허프만 트리 복원 */
        for (int j = 0; j < (int)codeln; j++) {
            fin >> hfcode;
            ret += hfcode;

            if (ret[j] == '0') {
                if (cur->left == nullptr) {
                    Node* newNode = new Node();
                    cur->left = newNode;
                }
                cur = cur->left;
            }

            else if (ret[j] == '1') {
                if (cur->right == nullptr) {
                    Node* newNode = new Node();
                    cur->right = newNode;
                }
                cur = cur->right;
            }

            else {
                cout << "error" << endl;
                exit(0);
            }
        }

        cur->ch = ch;
    }

    cur = root;

    while (fin >> ch) { // 1바이트씩 읽는다.
        int msb = 7;
        for (int i = 0; i < 8; i++) {
            if (ch & (1 << msb)) {
                if (cur->right != nullptr)
                    cur = cur->right;
            }

            else {
                if (cur->left != nullptr)
                    cur = cur->left;
            }

            msb--;
            size--;

            if ((cur->left == nullptr) && (cur->right == nullptr)) {
                fout << cur->ch;
                cur = root;
            }

            if (size == 0)
                break;
        }
    }

    cout << endl;
    fin.close();
    fout.close();
}