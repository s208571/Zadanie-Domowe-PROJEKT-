#include <iostream>

using namespace std;

int main() {
    int wybor;

    do {
        cout << "=== MENU GLOWNE ===" << endl;
        cout << "1. Generuj podstawowy SVG" << endl;
        cout << "2. Generuj zaawansowany SVG" << endl;
        cout << "3. Kolko i krzyzyk (wkrotce)" << endl;
        cout << "4. Warcaby (wkrotce)" << endl;
        cout << "5. Pomoc" << endl;
        cout << "6. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch(wybor) {
            case 1: cout << "Wybrano opcje 1" << endl; break;
            case 6: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        }
        cout << endl;
    } while (wybor != 6);

    return 0;
}