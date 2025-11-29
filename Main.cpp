#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

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
    cout <<"Teraz bede pytac o wymary i kolory!, jesli nie znasz kolorow to liste masz na stronie https://www.w3schools.com/colors/colors_names.asp" << endl;
    Sleep(4000);
    bool Kolizja;
    do 
    {
        Kolizja=false;

        cout << "Podaj wspolrzedne okregu(x,y) oraz jego promien(r) i jego kolor" << endl;
        cin >> kolo_x >> kolo_y >> kolo_r >> kolo_kolor;

        cout << "Podaj wspolrzedne prostokota(x,y) oraz jego wymiary(szerokosc, wysokosc) i jego kolor" << endl;
        cin >> prostokat_x >> prostokat_y >> prostokat_szer >> prostokat_wys >> prostokat_kolor;

        cout << "Podaj wspolrzedne poczatku lini(x1,y1) oraz wspolrzedne jej konca(x2,y2) jej grubosc i jej kolor" << endl;
        cin >> linia_x1 >> linia_y1 >> linia_x2 >> linia_y2 >> linia_grubosc >> linia_kolor;

        int k_lewo = kolo_x - kolo_r;
        int k_prawo = kolo_x + kolo_r;
        int k_gora = kolo_y - kolo_r;
        int k_dol = kolo_y + kolo_r;

        int p_lewo = prostokat_x;
        int p_prawo = prostokat_x + prostokat_szer;
        int p_gora = prostokat_y;
        int p_dol = prostokat_y + prostokat_wys;

        int l_lewo = min(linia_x1, linia_x2);
        int l_prawo = max(linia_x1, linia_x2);
        int l_gora = min(linia_y1, linia_y2);
        int l_dol = max(linia_y1, linia_y2);
        
        bool zderzenie_kolo_prost = (k_prawo > p_lewo && k_lewo < p_prawo && k_dol > p_gora && k_gora < p_dol);
        bool zderzenie_kolo_linia = (k_prawo > l_lewo && k_lewo < l_prawo && k_dol > l_gora && k_gora < l_dol);
        bool zderzenie_prost_linia = (p_prawo > l_lewo && p_lewo < l_prawo && p_dol > l_gora && p_gora < l_dol);

        if(zderzenie_kolo_linia==true||zderzenie_kolo_prost==true||zderzenie_prost_linia==true)
        {
            cout <<" BLAD! Obiekty na siebie nachodza, podaj ponownie wymiary." << endl;
            Kolizja=true;
        }
        else
        {
            Kolizja=false;
        }
    } while (Kolizja == true);
    

    ofstream plik("rysunek.svg");
    
    plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    plik << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
    plik << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    plik << "<circle cx=\" "<< kolo_x << "\" cy=\" "<< kolo_y << "\" r=\" "<< kolo_r << "\" fill=\" "<< kolo_kolor << "\" />" <<endl;
    plik << "<rect x=\" "<< prostokat_x << "\" y=\" "<< prostokat_y << "\" width=\" "<< prostokat_szer << "\" height=\" " << prostokat_wys << "\" fill=\" " << prostokat_kolor << "\" />" <<endl;
    plik << "<line x1=\" "<< linia_x1 << "\" y1=\" "<< linia_y1 << "\" x2=\" "<< linia_x2 << "\" y2=\" " << linia_y2 << "\" stroke=\" " << linia_kolor << "\" stroke-width=\" " << linia_grubosc << "\" />" <<endl;
    plik << "</svg>";
}

int main() 
{
    int wybor;

    do 
    {
        cout << "=== MENU GLOWNE ===" << endl;
        cout << "1. Generuj podstawowy SVG" << endl;
        cout << "2. Generuj zaawansowany SVG" << endl;
        cout << "3. Kolko i krzyzyk (wkrotce)" << endl;
        cout << "4. Warcaby (wkrotce)" << endl;
        cout << "5. Pomoc(Jak grac w gry)" << endl;
        cout << "6. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch(wybor) 
        {
            case 1: GenerowaniePustegoSVG(); break;
            case 2: RysowanieKrztaltow(); break;
            case 6: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        }
        cout << endl;
    } while (wybor != 6);

    return 0;
}