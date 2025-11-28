#include <iostream>
#include <fstream>

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

        switch(wybor) 
        {
            case 1: 
            {
                cout << "Generuje pusty plik SVG" << endl;
                ofstream plik("rysunek.svg");
                plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
                plik << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
                plik << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
                plik << "</svg>";
                plik.close(); break;
            }
            case 6: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        }
        cout << endl;
    } while (wybor != 6);

    return 0;
}