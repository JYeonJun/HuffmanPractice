#include "Menu.h"

void Start() {
    int input = 0;
    string filename;
    Huffman huff;
    Timer timer;

    system("cls");

    while (1) {
        try {
            cout << "1. 압축하기" << endl;
            cout << "2. 복원하기" << endl;
            cout << "3. 종료하기" << endl;
            cout << "입력: ";
            cin >> input;

            if (input != 1 && input != 2 && input != 3)
                throw input;

            switch (input) {
                case 1:
                    cout << "압축할 파일 이름을 입력하시오: ";
                    cin >> filename;

                    if (filename.find("huff") == -1) {  // 파일 이름에 "huff" 문자열이 존재하지 않으면 압축 수행
                        if (readFile(filename)) {   // 열 수 있는 파일이라면
                            timer.Reset();  // 시간 측정
                            huff.encoding(filename);    // 압축 수행
                            system("cls");
                            cout << "걸린 시간 = " << timer.ElapsedTime() << "초" << endl << endl;
                            PrintEncodingMenu(&huff);   // 압축 메뉴 호출
                        }
                    }
                    else {  // 이미 압축된 파일이 입력된다면
                        system("cls");
                        cout << "압축할 파일 이름을 입력하시오." << endl << endl;
                        continue;
                    }
                    break;
                case 2:
                    cout << "복원할 파일 이름을 입력하시오: ";
                    cin >> filename;
                    
                    if (filename.find("huff") != -1) {  // 파일 이름에 "huff" 문자열이 존재한다면
                        if (readFile(filename)) {   // 유효한 파일인지 검사
                            timer.Reset();
                            huff.decoding(filename);    // 압축 해제 수행
                            system("cls");
                            cout << "걸린 시간 = " << timer.ElapsedTime() << "초" << endl << endl;
                            PrintDecodingMenu(&huff);   // 압축 해제 메뉴 호출
                        }
                    }
                    else {  // 이미 압축된 파일이 입력된다면
                        system("cls");
                        cout << "압축된 파일을 입력하시오." << endl << endl;
                        continue;
                    }
                    break;
                case 3:
                    exit(0);
            }
        }
        catch (...) {
            fflush(stdin);
            cout << "재입력 해주세요" << endl;
            system("pause");
            system("cls");
        }
    }
}

void PrintEncodingMenu(Huffman* huff) {

    int input;

    while (1) {
        cout << "1. 허프만 테이블 출력" << endl;
        cout << "2. 압축률 출력" << endl;
        cout << "3. 문자의 평균 비트 수 출력" << endl;
        cout << "4. 허프만 코드 출력" << endl;
        cout << "5. 결과 파일 출력" << endl;
        cout << "9. 이전 메뉴" << endl;
        cout << "입력: ";
        cin >> input;

        switch (input) {
            case 1:
                system("cls");
                huff->printHfTable();
                break;
            case 2:
                system("cls");
                huff->printCompressibility();
                break;
            case 3:
                system("cls");
                huff->printAverageBit();
                break;
            case 4:
                system("cls");
                cout << huff->printCode() << endl << endl;
                break;
            case 5:
                system("cls");
                huff->printEncodingResult();
                break;
            case 9:
                Start();
                break;
        }
    }
}

void PrintDecodingMenu(Huffman* huff) {
    int input;

    while (1) {
        cout << "1. 결과 파일 출력" << endl;
        cout << "9. 시작 메뉴" << endl;
        cout << "입력: ";
        cin >> input;

        switch (input) {
            case 1:
                system("cls");
                huff->printDecodingResult();
                break;
            case 9:
                Start();
                break;
        }
    }
}