#include "Menu.h"

void Start() {
    int input = 0;
    string filename;
    Huffman huff;
    Timer timer;

    system("cls");

    while (1) {
        try {
            cout << "1. �����ϱ�" << endl;
            cout << "2. �����ϱ�" << endl;
            cout << "3. �����ϱ�" << endl;
            cout << "�Է�: ";
            cin >> input;

            if (input != 1 && input != 2 && input != 3)
                throw input;

            switch (input) {
                case 1:
                    cout << "������ ���� �̸��� �Է��Ͻÿ�: ";
                    cin >> filename;

                    if (filename.find("huff") == -1) {  // ���� �̸��� "huff" ���ڿ��� �������� ������ ���� ����
                        if (readFile(filename)) {   // �� �� �ִ� �����̶��
                            timer.Reset();  // �ð� ����
                            huff.encoding(filename);    // ���� ����
                            system("cls");
                            cout << "�ɸ� �ð� = " << timer.ElapsedTime() << "��" << endl << endl;
                            PrintEncodingMenu(&huff);   // ���� �޴� ȣ��
                        }
                    }
                    else {  // �̹� ����� ������ �Էµȴٸ�
                        system("cls");
                        cout << "������ ���� �̸��� �Է��Ͻÿ�." << endl << endl;
                        continue;
                    }
                    break;
                case 2:
                    cout << "������ ���� �̸��� �Է��Ͻÿ�: ";
                    cin >> filename;
                    
                    if (filename.find("huff") != -1) {  // ���� �̸��� "huff" ���ڿ��� �����Ѵٸ�
                        if (readFile(filename)) {   // ��ȿ�� �������� �˻�
                            timer.Reset();
                            huff.decoding(filename);    // ���� ���� ����
                            system("cls");
                            cout << "�ɸ� �ð� = " << timer.ElapsedTime() << "��" << endl << endl;
                            PrintDecodingMenu(&huff);   // ���� ���� �޴� ȣ��
                        }
                    }
                    else {  // �̹� ����� ������ �Էµȴٸ�
                        system("cls");
                        cout << "����� ������ �Է��Ͻÿ�." << endl << endl;
                        continue;
                    }
                    break;
                case 3:
                    exit(0);
            }
        }
        catch (...) {
            fflush(stdin);
            cout << "���Է� ���ּ���" << endl;
            system("pause");
            system("cls");
        }
    }
}

void PrintEncodingMenu(Huffman* huff) {

    int input;

    while (1) {
        cout << "1. ������ ���̺� ���" << endl;
        cout << "2. ����� ���" << endl;
        cout << "3. ������ ��� ��Ʈ �� ���" << endl;
        cout << "4. ������ �ڵ� ���" << endl;
        cout << "5. ��� ���� ���" << endl;
        cout << "9. ���� �޴�" << endl;
        cout << "�Է�: ";
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
        cout << "1. ��� ���� ���" << endl;
        cout << "9. ���� �޴�" << endl;
        cout << "�Է�: ";
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