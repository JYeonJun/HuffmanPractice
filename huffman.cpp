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

void Huffman::printEncodingResult() {   // 압축 결과 파일을 출력
    ifstream fin;
    char buf[1024];
    fin.open(filename, ios_base::in | ios_base::binary);
    
    while (fin) {
        fin.read(buf, 1023);
        buf[fin.gcount()] = '\0';
        cout << buf << endl << endl;
    }
}

void Huffman::printDecodingResult() {   // 압축 해제 결과 파일 출력

    ifstream fin(filename);
    string str;

    while (getline(fin, str))
        cout << str << endl;

    cout << endl << endl;
}

void Huffman::printCompressibility() {  // 압축률 출력(원본 파일 크기, 결과 파일 크기, 압축률)
    cout << "원본 파일 크기 = " << input_filesize << "바이트" <<endl;
    cout << "압축된 파일 크기 = " << output_filesize << "바이트" <<endl;

    cout << "압축률 = " << (1 - (output_filesize / input_filesize)) * 100 << "%" << endl << endl;
}

void Huffman::printHfTable() {   // 허프만 테이블 출력
    cout << "------------------------------------" << endl;
    cout << " 문자	빈도수	허프만코드" << endl;
    cout << "------------------------------------" << endl;

    for (auto& e : ms) {   
        if (e.first == '\n')
            cout << " 개행" << "\t ";

        else if (e.first == ' ')
            cout << "칸 띄움" << "\t ";


        else
            cout << " " << e.first << "\t ";

        cout << mf.find(e.first)->second << "\t ";
        cout << e.second << endl;
    }

    cout << endl << endl;
}

void Huffman::printAverageBit() { // 문자 당 평균 비트 수 출력
    int sum = 0;

    for (auto& e : ms)
        sum += e.second.size();


    cout << "문자 당 평균 비트 수 = " << (double)sum / ms.size() << "개" << endl << endl;
}

string Huffman::printCode() const {   // 입력 받은 파일의 문자열 코드 반환
    if (code == "") // 허프만 코드가 비어있다면
        cout << "Encoding First ! \n";  // 인코딩 수행 하라고 출력

    return code;    // 허프만 코드 반환
}

double Huffman::fileSize(const string filename) {
    ifstream fin(filename);
    double sub;

    streamoff start, end;    //텍스트 파일 크기 저장 변수

    start = fin.tellg();     //파일 크기 계산
    fin.seekg(0, ios::end);
    end = fin.tellg();

    sub = end - start;

    return sub;
}

bool Node::operator()(const Node* lhs, const Node* rhs) const {
    return lhs->cnt > rhs->cnt;
}