#include "huffman.h"

void Huffman::encoding(const string& filename) {
    ifstream fin(filename);
    fin.unsetf(ios::skipws);
    char ch;

    // ���ڿ� �� ����
    while (fin >> ch) { // ���Ͽ��� ���ڸ� �ϳ��� �о��
        mf[ch]++;   // �� ������ �󵵸� ����
    }

    amount = mf.size();

    // �켱���� ť�� ����
    priority_queue<Node*, vector<Node*>, Node> pq;
    for (auto& e : mf) {
        pq.push(new Node(e.first, e.second));   // ������ �󵵰� ���� ������ �켱���� ť�� �����Ѵ�.
    }

    // ������ Ʈ�� ����
    while (pq.size() > 1) { // �켱���� ť�� ��尡 �����Ѵٸ�
        Node* left = pq.top();

        pq.pop();
        Node* right = pq.top();

        pq.pop();

        Node* newNode = new Node(left, right);  // ������ Ʈ�� ��Ʈ ��带 ������ 
        pq.push(newNode);   // �켱���� ť�� �����Ѵ�.
    }

    root = pq.top(); // Node �����Ϳ� ���� ������ Ʈ���� �����Ѵ�.
    pq.pop();   // �켱���� ť�� �����Ѵ�.

    fin.close();
    makeHfTable(filename);    // ������ Ʈ���� �̿��� ���ڸ� ������ �ڵ�� ����
}

void Huffman::makeHfTable(const string& filename) {   // ���ڸ� ������ �ڵ�� ��ȯ
    ifstream fin(filename);
    fin.unsetf(ios::skipws);
    char ch;
    string code = "";   // �������ڵ带 ������ ���ڿ�

    stack<pair<Node*, string>> st;  // Node �����Ϳ� ���ڿ��� ������ ���� ����
    st.push({ root, "" });   // ���ÿ� ������Ʈ���� �� ���ڿ��� ����

    while (!st.empty()) {   // ������ ��������
        Node* cur = st.top().first;
        string tmp = st.top().second;
        st.pop();

        if (cur->right != nullptr) {    // �����ʿ� ��尡 �����Ѵٸ�
            st.push({ cur->right, tmp + "1" }); // ������ ������ �ڵ忡 1 �߰�
        }
        if (cur->left != nullptr) { // ���ʿ� ��尡 �����Ѵٸ�
            st.push({ cur->left, tmp + "0" });  // ������ ������ �ڵ忡 0�߰�
        }

        if (cur->left == nullptr && cur->right == nullptr) {    // ������忡 �����ߴٸ� �� ������ �ڵ� ����
            ms[cur->ch] = tmp;   // ���ڿ� ������ �ڵ� ����
        }
    }

    while (fin >> ch)
        code += ms[ch];

    this->code = code;
    codesize = this->code.size();

    fin.close();
    creatHfFile(filename);
}

void Huffman::creatHfFile(string filename) {
    string huff = "huff.txt";
    ifstream fin(filename);
    ofstream fout;
    char buffer = 0;    // �� ������ ������ �ڵ带 ������ ����
    char ch;
    int msb = 7;
    int idx = 0;
    int test = 1;

    input_filesize = fileSize(filename);

    fin.unsetf(ios::skipws);

    // ������ ���ϸ� ����
    filename.replace(filename.find('.'), filename.length() - filename.find('.'), huff);
    this->filename = filename;

    fout.open(filename, ios_base::out | ios_base::trunc | ios_base::binary);    // ���̳ʸ� ���� ������ ����.

    if (!fout) {
        system("cls");
        cout << filename << "������ �� �� �����ϴ�." << endl;
        return;
    }

    /* �������� ��� ���� */
    // �����ϴ� ���� ��ü ��Ʈ ��, �� ���� 1 �̻��� ���� ����, ����, ������ ������ �ڵ� ����, �� ������ ������ �ڵ� ����
    fout << codesize;
    fout << " ";
    fout << amount; // �� ���� 1 �̻��� ���� ���� ����


    for (auto it = ms.begin(); it != ms.end(); it++) {
        fout << it->first;  // �� ���� ����
        fout << (char)it->second.size();  // �� ������ ������ �ڵ� ���� ����
        fout << it->second; // �� ������ ������ �ڵ� ����
    }   // �� ������ ������ �ڵ带 ��Ʈ ���� �����ϸ� �� ȿ����

    /* ������ �ڵ� ���� */
    while (fin >> ch) {
        for (auto it = ms.begin(); it != ms.end(); it++) {
            if (ch == it->first) {  // �о�� ���ڰ� map�� �����ϴ� ���ڶ��

                for (int letter = 0; letter < it->second.size(); letter++) {

                    if (msb == -1) {
                        fout << buffer;
                        buffer = 0;
                        msb = 7;
                    }

                    if (it->second[letter] == '1') {
                        buffer = (buffer | (1 << msb));
                    }

                    msb--;
                }
                break;
            }
        }
    }

    fout << buffer;

    fin.close();
    fout.close();

    output_filesize = fileSize(filename);
}