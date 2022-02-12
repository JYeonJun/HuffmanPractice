#include "huffman.h"

Huffman::~Huffman() {
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* cur = st.top();
        st.pop();

        if (cur->left)
            st.push(cur->left);
        if (cur->right)
            st.push(cur->right);

        delete cur;
    }

    root = nullptr;
}

void Huffman::printEncodingResult() {   // ���� ��� ������ ���
    ifstream fin;
    char buf[1024];
    fin.open(filename, ios_base::in | ios_base::binary);
    
    while (fin) {
        fin.read(buf, 1023);
        buf[fin.gcount()] = '\0';
        cout << buf << endl << endl;
    }
}

void Huffman::printDecodingResult() {   // ���� ���� ��� ���� ���

    ifstream fin(filename);
    string str;

    while (getline(fin, str))
        cout << str << endl;

    cout << endl << endl;
}

void Huffman::printCompressibility() {  // ����� ���(���� ���� ũ��, ��� ���� ũ��, �����)
    cout << "���� ���� ũ�� = " << input_filesize << "����Ʈ" <<endl;
    cout << "����� ���� ũ�� = " << output_filesize << "����Ʈ" <<endl;

    cout << "����� = " << (1 - (output_filesize / input_filesize)) * 100 << "%" << endl << endl;
}

void Huffman::printHfTable() {   // ������ ���̺� ���
    cout << "------------------------------------" << endl;
    cout << " ����	�󵵼�	�������ڵ�" << endl;
    cout << "------------------------------------" << endl;

    for (auto& e : ms) {   
        if (e.first == '\n')
            cout << " ����" << "\t ";

        else if (e.first == ' ')
            cout << "ĭ ���" << "\t ";


        else
            cout << " " << e.first << "\t ";

        cout << mf.find(e.first)->second << "\t ";
        cout << e.second << endl;
    }

    cout << endl << endl;
}

void Huffman::printAverageBit() { // ���� �� ��� ��Ʈ �� ���
    int sum = 0;

    for (auto& e : ms)
        sum += e.second.size();


    cout << "���� �� ��� ��Ʈ �� = " << (double)sum / ms.size() << "��" << endl << endl;
}

string Huffman::printCode() const {   // �Է� ���� ������ ���ڿ� �ڵ� ��ȯ
    if (code == "") // ������ �ڵ尡 ����ִٸ�
        cout << "Encoding First ! \n";  // ���ڵ� ���� �϶�� ���

    return code;    // ������ �ڵ� ��ȯ
}

double Huffman::fileSize(const string filename) {
    ifstream fin(filename);
    double sub;

    streamoff start, end;    //�ؽ�Ʈ ���� ũ�� ���� ����

    start = fin.tellg();     //���� ũ�� ���
    fin.seekg(0, ios::end);
    end = fin.tellg();

    sub = end - start;

    return sub;
}

bool Node::operator()(const Node* lhs, const Node* rhs) const {
    return lhs->cnt > rhs->cnt;
}