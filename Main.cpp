#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void GenerowaniePustegoSVG()
{
    cout << "Generuje podstawowy(pusty) plik SVG" << endl;
    ofstream plik("rysunek.svg");
    plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    plik << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
    plik << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    plik << "</svg>";
    plik.close();
}

void RysowanieKrztaltow()
{
    int kolo_x, kolo_y, kolo_r;
    string kolo_kolor;
    int prostokat_x, prostokat_y, prostokat_szer, prostokat_wys;
    string prostokat_kolor;
    int linia_x1, linia_y1,  linia_x2, linia_y2, linia_grubosc;
    string linia_kolor;


    cout << "Podaj wspolrzedne okregu(x,y) oraz jego promien(r) i jego kolor" << endl;
    cin >> kolo_x, kolo_y, kolo_r, kolo_kolor;

    cout << "Podaj wspolrzedne prostokota(x,y) oraz jego wymiary(szerokosc, wysokosc) i jego kolor" << endl;
    cin >> prostokat_x, prostokat_y, prostokat_szer, prostokat_wys, prostokat_kolor;

    cout << "Podaj wspolrzedne poczatku lini(x1,y1) oraz wspolrzedne jej konca(x2,y2) jej grubosc i jej kolor" << endl;
    cin >> linia_x1, linia_y1, linia_x2, linia_y2, linia_grubosc, linia_kolor;

    ofstream plik("rysunek.svg");
    
    plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    plik << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
    plik << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    plik << "<circle cx=\" "<< kolo_x << " cy=\" "<< kolo_y << " r=\" "<< kolo_r << " fill=\" "<< kolo_kolor << "\" />" <<endl;
    plik << "<rect x=\" "<< prostokat_x << " y=\" "<< prostokat_y << " width=\" "<< prostokat_szer << " height=\" " << prostokat_wys << " fill=\" " << prostokat_kolor << "\" />" <<endl;
    plik << "<line x1=\" "<< linia_x1 << " y1=\" "<< linia_y1 << " x2=\" "<< linia_x2 << " y2=\" " << linia_y2 << " stroke=\" " << linia_kolor << " stroke-width=\" " << linia_grubosc << "\" />" <<endl;
    plik << "</svg>";
}
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
            case 1: GenerowaniePustegoSVG(); break;
            case 6: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        }
        cout << endl;
    } while (wybor != 6);

    return 0;
}