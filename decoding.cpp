#include "huffman.h"
#include "Timer.h"
#include "FileIO.h"

void Huffman::decoding(string filename) {  // ����

    ifstream fin;
    ofstream fout;
    int num;    // ��ü ���� ����
    char ch;    // ����
    char codeln;    // ������ �ڵ� ����
    char hfcode;    // �� ������ ������ �ڵ带 �о�� ����
    string ret = "";
    Node* cur;
    string huff = "complete.txt";
    long size;

    Node* node = new Node();

    root = node;

    fin.open(filename, ios_base::in | ios_base::binary);
    fin.unsetf(ios::skipws);

    // ������ ���ϸ� ����
    filename.erase(filename.find("huff"), 4);
    filename.replace(filename.find('.'), filename.length() - filename.find('.'), huff);
    this->filename = filename;
    
    fout.open(filename, ios_base::out | ios_base::trunc);   // �ؽ�Ʈ ���

    /* ��� ���� ���� �б� */
    fin >> size;
    fin >> ch;
    fin >> num;

    for (int i = 0; i < num; i++) { // ������ ������ŭ ������ �о�´�.
        ret = "";
        cur = root;
        fin >> ch;
        fin >> codeln;

        /* ������ Ʈ�� ���� */
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

    while (fin >> ch) { // 1����Ʈ�� �д´�.
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