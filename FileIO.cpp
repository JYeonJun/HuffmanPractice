#include "FileIO.h"

bool readFile(const string filename) {
    ifstream fin(filename);

    if (!fin) {
        system("cls");
        cout << filename << "파일을 열 수 없습니다." << endl;
        fin.close();
        return FALSE;
    }

    fin.close();
    return TRUE;
}