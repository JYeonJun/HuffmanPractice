#include "FileIO.h"

bool readFile(const string filename) {
    ifstream fin(filename);

    if (!fin) {
        system("cls");
        cout << filename << "������ �� �� �����ϴ�." << endl;
        fin.close();
        return FALSE;
    }

    fin.close();
    return TRUE;
}