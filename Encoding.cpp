#include "huffman.h"

void Huffman::encoding(const string& filename) {
    ifstream fin(filename);
    fin.unsetf(ios::skipws);
    char ch;

    // 문자와 빈도 저장
    while (fin >> ch) { // 파일에서 문자를 하나씩 읽어와
        mf[ch]++;   // 각 문자의 빈도를 저장
    }

    amount = mf.size();

    // 우선순위 큐를 생성
    priority_queue<Node*, vector<Node*>, Node> pq;
    for (auto& e : mf) {
        pq.push(new Node(e.first, e.second));   // 문자의 빈도가 적은 순으로 우선순위 큐에 삽입한다.
    }

    // 허프만 트리 생성
    while (pq.size() > 1) { // 우선순위 큐에 노드가 존재한다면
        Node* left = pq.top();

        pq.pop();
        Node* right = pq.top();

        pq.pop();

        Node* newNode = new Node(left, right);  // 허프만 트리 루트 노드를 생성해 
        pq.push(newNode);   // 우선순위 큐에 삽입한다.
    }

    root = pq.top(); // Node 포인터에 최종 허프만 트리를 대입한다.
    pq.pop();   // 우선순위 큐를 제거한다.

    fin.close();
    makeHfTable(filename);    // 허프만 트리를 이용해 문자를 허프만 코드로 변경
}

void Huffman::makeHfTable(const string& filename) {   // 문자를 허프만 코드로 변환
    ifstream fin(filename);
    fin.unsetf(ios::skipws);
    char ch;
    string code = "";   // 허프만코드를 저장할 문자열

    stack<pair<Node*, string>> st;  // Node 포인터와 문자열을 가지는 스택 생성
    st.push({ root, "" });   // 스택에 허프만트리와 빈 문자열을 삽입

    while (!st.empty()) {   // 스택이 빌때까지
        Node* cur = st.top().first;
        string tmp = st.top().second;
        st.pop();

        if (cur->right != nullptr) {    // 오른쪽에 노드가 존재한다면
            st.push({ cur->right, tmp + "1" }); // 문자의 허프만 코드에 1 추가
        }
        if (cur->left != nullptr) { // 왼쪽에 노드가 존재한다면
            st.push({ cur->left, tmp + "0" });  // 문자의 허프만 코드에 0추가
        }

        if (cur->left == nullptr && cur->right == nullptr) {    // 리프노드에 도달했다면 각 문자의 코드 저장
            ms[cur->ch] = tmp;   // 문자와 허프만 코드 저장
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
    char buffer = 0;    // 각 문자의 허프만 코드를 저장할 변수
    char ch;
    int msb = 7;
    int idx = 0;
    int test = 1;

    input_filesize = fileSize(filename);

    fin.unsetf(ios::skipws);

    // 저장할 파일명 생성
    filename.replace(filename.find('.'), filename.length() - filename.find('.'), huff);
    this->filename = filename;

    fout.open(filename, ios_base::out | ios_base::trunc | ios_base::binary);    // 바이너리 모드로 파일을 연다.

    if (!fout) {
        system("cls");
        cout << filename << "파일을 열 수 없습니다." << endl;
        return;
    }

    /* 압축파일 헤더 생성 */
    // 저장하는 파일 전체 비트 수, 빈도 수가 1 이상인 무자 개수, 문자, 문자의 허프만 코드 길이, 각 문자의 허프만 코드 저장
    fout << codesize;
    fout << " ";
    fout << amount; // 빈도 수가 1 이상인 문자 개수 저장


    for (auto it = ms.begin(); it != ms.end(); it++) {
        fout << it->first;  // 각 문자 저장
        fout << (char)it->second.size();  // 각 문자의 허프만 코드 길이 저장
        fout << it->second; // 각 문자의 허프만 코드 저장
    }   // 각 문자의 허프만 코드를 비트 단위 저장하면 더 효율적

    /* 허프만 코드 저장 */
    while (fin >> ch) {
        for (auto it = ms.begin(); it != ms.end(); it++) {
            if (ch == it->first) {  // 읽어온 문자가 map에 존재하는 문자라면

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