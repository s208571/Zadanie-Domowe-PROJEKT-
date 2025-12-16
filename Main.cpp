#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <vector>
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
    Sleep(3000);
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
            //kolizja
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
    plik.close();
}
// Funkcje do Kolko i Krzyzyk, sprawdzanie wygranej i rysowanie planszy w konsoli
bool SprwadzWygranaKK(char planszaKK[3][3], char gracz)
{
    for(int i=0; i<3; i++)
    {
        if(planszaKK[i][0]==gracz && planszaKK[i][1]==gracz && planszaKK[i][2]==gracz)
            return true;
        if(planszaKK[0][i]==gracz && planszaKK[1][i]==gracz && planszaKK[2][i]==gracz)
            return true;
    }
    if(planszaKK[0][0]==gracz && planszaKK[1][1]==gracz && planszaKK[2][2]==gracz)
        return true;
    if(planszaKK[0][2]==gracz && planszaKK[1][1]==gracz && planszaKK[2][0]==gracz)
        return true;

    return false;
}
void RysowanieKK(char planszaKK[3][3])
{
    for(int z=0; z<3; z++)
{
    for(int i=0; i<3; i++)
    {
        cout<<" "<<planszaKK[z][i]<<" ";
        if (i<2) cout<< "|";
    }
    cout << endl;
    if (z<2) cout << "---+---+---"<<endl;
}
}
// Funkcja aktualizujaca plik SVG na podstawie stanu planszy
void AktualizujSVG(char plansza[3][3])
{
    ofstream plik("gra_kolko_krzyzyk.svg");

    
    plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    plik << "<svg width=\"300\" height=\"300\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;

    
    plik << "<rect width=\"300\" height=\"300\" fill=\"white\" />" << endl;
    plik << "<line x1=\"100\" y1=\"0\" x2=\"100\" y2=\"300\" stroke=\"black\" stroke-width=\"5\" />" << endl;
    plik << "<line x1=\"200\" y1=\"0\" x2=\"200\" y2=\"300\" stroke=\"black\" stroke-width=\"5\" />" << endl;
    plik << "<line x1=\"0\" y1=\"100\" x2=\"300\" y2=\"100\" stroke=\"black\" stroke-width=\"5\" />" << endl;
    plik << "<line x1=\"0\" y1=\"200\" x2=\"300\" y2=\"200\" stroke=\"black\" stroke-width=\"5\" />" << endl;

    
    for(int wiersz = 0; wiersz < 3; wiersz++)
    {
        for(int kolumna = 0; kolumna < 3; kolumna++)
        {
            
            int cx = (kolumna * 100) + 50; 
            int cy = (wiersz * 100) + 50;
            char znak = plansza[wiersz][kolumna];

            if(znak == 'O')
            {
                plik << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"40\" stroke=\"blue\" stroke-width=\"5\" fill=\"none\" />" << endl;
            }
            else if(znak == 'X')
            {
                plik << "<line x1=\"" << cx-30 << "\" y1=\"" << cy-30 << "\" x2=\"" << cx+30 << "\" y2=\"" << cy+30 << "\" stroke=\"red\" stroke-width=\"5\" />" << endl;
                plik << "<line x1=\"" << cx+30 << "\" y1=\"" << cy-30 << "\" x2=\"" << cx-30 << "\" y2=\"" << cy+30 << "\" stroke=\"red\" stroke-width=\"5\" />" << endl;
            }
        }
    }

    plik << "</svg>";
    plik.close(); 
}
void RuchKomputera(char gra[3][3], char znakPC, char znakGracza)
{
    cout << "Komputer mysli..." << endl;
    Sleep(1000); // Symulacja myslenia

    // Sprawdzamy ile pol jest wolnych (zeby wiedziec czy to 1. ruch)
    int wolne = 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(gra[i][j] != 'X' && gra[i][j] != 'O') wolne++;

    // 1. PIERWSZY KROK
    // Jesli PC jest 'O' (zaczyna) i plansza pusta -> Srodek
    if (znakPC == 'O' && wolne == 9)
    {
        gra[1][1] = znakPC; 
        return;
    }

    // 2. BLOKOWANIE (Jesli gracz ma 2 w linii)
    // Sprawdzamy wszystkie linie. Jesli sa 2 znaki gracza i 1 wolny -> wstawiamy tam.
    // Tablica wszystkich mozliwych linii (wspolrzedne punktow)
    int linie[8][3][2] = {
        {{0,0}, {0,1}, {0,2}}, {{1,0}, {1,1}, {1,2}}, {{2,0}, {2,1}, {2,2}}, // Poziome
        {{0,0}, {1,0}, {2,0}}, {{0,1}, {1,1}, {2,1}}, {{0,2}, {1,2}, {2,2}}, // Pionowe
        {{0,0}, {1,1}, {2,2}}, {{0,2}, {1,1}, {2,0}}  // Przekatne
    };

    for(int i=0; i<8; i++)
    {
        int licznikGracza = 0;
        int licznikWolnych = 0;
        int w_wolne = -1, k_wolne = -1; // Zapamietujemy gdzie jest wolne pole

        for(int j=0; j<3; j++)
        {
            int w = linie[i][j][0]; //wiersz
            int k = linie[i][j][1]; //kolumna
            if(gra[w][k] == znakGracza) licznikGracza++;
            else if(gra[w][k] != znakPC) // Czyli jest cyfra (wolne)
            {
                // Zapamietujemy miejsce wolnego pola
                licznikWolnych++;
                w_wolne = w;
                k_wolne = k;
            }
        }
        // Jesli sa 2 znaki gracza i 1 wolne -> stawiamy tam znakPC
        if(licznikGracza == 2 && licznikWolnych == 1)
        {
            gra[w_wolne][k_wolne] = znakPC; // BLOKUJEMY!
            return;
        }
    }

    // 3. STAWIANIE PRZY SWOIM (Budowanie)
    // Szukamy swojego znaku i sprawdzamy czy obok jest wolne
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            // Znajdujemy swoj znak
            if(gra[i][j] == znakPC)
            {
                // Sprawdzamy sasiadow (gora, dol, lewo, prawo)
                // Jesli wolne -> stawiamy tam
                if(i>0 && gra[i-1][j] != 'X' && gra[i-1][j] != 'O') { gra[i-1][j] = znakPC; return; }
                if(i<2 && gra[i+1][j] != 'X' && gra[i+1][j] != 'O') { gra[i+1][j] = znakPC; return; }
                if(j>0 && gra[i][j-1] != 'X' && gra[i][j-1] != 'O') { gra[i][j-1] = znakPC; return; }
                if(j<2 && gra[i][j+1] != 'X' && gra[i][j+1] != 'O') { gra[i][j+1] = znakPC; return; }
            }
        }
    }

    // 4. LOSOWY RUCH (Ostatecznosc)
    // Zbieramy wolne pola do wektora i losujemy jedno
    vector<pair<int, int>> dostepne;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(gra[i][j] != 'X' && gra[i][j] != 'O') 
                dostepne.push_back({i, j});

    if(!dostepne.empty())
    {
        int los = rand() % dostepne.size();
        gra[dostepne[los].first][dostepne[los].second] = znakPC;
    }
}
int main() 
{
    srand(time(NULL)); // Zmienna do losowania
    char aktualny_gracz = 'O';
    int wybor_interfejs;
    int wybor_polaKK;
    int liczba_ruchowKK = 0;
    bool koniec_gryKK = false;
    char gra[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    do 
    {
       
        cout << "=== MENU GLOWNE ===" << endl;
        cout << "1. Generuj podstawowy SVG" << endl;
        cout << "2. Generuj zaawansowany SVG" << endl;
        cout << "3. Kolko i krzyzyk" << endl;
        cout << "4. Kolko i krzyzyk z komputerem" << endl;
        cout << "5. Warcaby" << endl;
        cout << "6. Pomoc(Jak grac w gry)" << endl;
        cout << "7. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor_interfejs;
        cin.ignore(1000, '\n');
        switch(wybor_interfejs) 
        {
            case 1: GenerowaniePustegoSVG(); break;
            case 2: RysowanieKrztaltow(); break;
            case 3:
    liczba_ruchowKK = 0;
    koniec_gryKK = false;
    aktualny_gracz = 'O';

    gra[0][0] = '1'; gra[0][1] = '2'; gra[0][2] = '3';
    gra[1][0] = '4'; gra[1][1] = '5'; gra[1][2] = '6';
    gra[2][0] = '7'; gra[2][1] = '8'; gra[2][2] = '9';
    AktualizujSVG(gra);
    while (koniec_gryKK == false && liczba_ruchowKK < 9)
    {
        RysowanieKK(gra);
        cout << "Tura gracza: " << aktualny_gracz << endl;
        cout << "Masz 30 sekund na wykonanie ruchu." << endl;
        time_t start = time(0);
        cout << "Wybierz pole (1-9): ";
        cin >> wybor_polaKK;
        time_t stop = time(0);
        double czas_sekundy = difftime(stop, start);
        cin.ignore(1000, '\n');
        if(czas_sekundy > 30)
        {
            cout << "Przekroczono limit czasu! Przegrywasz." << endl;
            Sleep(2000);
            if (aktualny_gracz == 'O') aktualny_gracz = 'X';
            else aktualny_gracz = 'O';
            cout<<"Wygrywa gracz: "<<aktualny_gracz<<endl;
            cout<<"Wcisnij ENTER aby wrocic do menu."<<endl;
            cin.get();
            koniec_gryKK = true;
            break;
        }
        bool poprawny_ruch = true;

        switch(wybor_polaKK)
        {
            // wybieranie pola
            case 1: if(gra[0][0]=='1') gra[0][0]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 2: if(gra[0][1]=='2') gra[0][1]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 3: if(gra[0][2]=='3') gra[0][2]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 4: if(gra[1][0]=='4') gra[1][0]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 5: if(gra[1][1]=='5') gra[1][1]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 6: if(gra[1][2]=='6') gra[1][2]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 7: if(gra[2][0]=='7') gra[2][0]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 8: if(gra[2][1]=='8') gra[2][1]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            case 9: if(gra[2][2]=='9') gra[2][2]=aktualny_gracz; else {cout<<"Zajete!"<<endl; poprawny_ruch=false; Sleep(1000);} break;
            default: cout<<"Nie ma takiego pola!"<<endl; poprawny_ruch=false; Sleep(1000); break;
        }
        // Po udanym ruchu:
        if(poprawny_ruch == true)
        {
            AktualizujSVG(gra);
            if (SprwadzWygranaKK(gra, aktualny_gracz) == true)
            {
                RysowanieKK(gra);
                cout << "\n==================="<< endl;
                cout << "Gracz " << aktualny_gracz << " wygrywa!" << endl;
                cout << "===================\n"<< endl;
                cout << "Wcisnij ENTER aby wrocic do menu." << endl;
                cin.get();
                koniec_gryKK = true;
                
            }
            else
            {   // Sprawdzamy remis
                liczba_ruchowKK++;
                if(liczba_ruchowKK == 9)
                {
                    
                    RysowanieKK(gra);
                    cout << "\n==================="<< endl;
                    cout << "Remis!" << endl;
                    cout << "===================\n"<< endl;
                    cout << "Wcisnij ENTER aby wrocic do menu." << endl;
                    cin.get();
                    koniec_gryKK = true;
                    
                }
                else
                {
                    if (aktualny_gracz == 'O') aktualny_gracz = 'X';
                    else aktualny_gracz = 'O';
                }
            }
        }
    }
    break;
            case 4: cout << "Kolko i krzyzyk z komputerem" << endl;
            liczba_ruchowKK = 0;
                koniec_gryKK = false;
                // Inicjalizacja planszy
                gra[0][0]='1'; gra[0][1]='2'; gra[0][2]='3';
                gra[1][0]='4'; gra[1][1]='5'; gra[1][2]='6';
                gra[2][0]='7'; gra[2][1]='8'; gra[2][2]='9';
                AktualizujSVG(gra);

                char znakGracza, znakPC;
                cout << "Chcesz grac O (zaczynasz) czy X (drugi)? (o/x): ";
                cin >> znakGracza;
                cin.ignore(1000, '\n');
                // Ustawienie znakow i kto zaczyna
                if(znakGracza == 'x' || znakGracza == 'X') {znakGracza = 'X'; znakPC = 'O'; aktualny_gracz = 'O';}
                else {znakGracza = 'O'; znakPC = 'X'; aktualny_gracz = 'O';}
                // Główna pętla gry
                while (!koniec_gryKK && liczba_ruchowKK < 9)
                {
                    RysowanieKK(gra);
                    
                    if(aktualny_gracz == znakGracza)
                    {
                        // Tura GRACZA (z czasem)
                        cout << "TWOJA TURA (" << znakGracza << ")" << endl;
                        cout << "Masz 30 sekund! Wybierz pole (1-9): ";
                        time_t start = time(0); 
                        cin >> wybor_polaKK;
                        time_t stop = time(0);
                        cin.ignore(1000, '\n');

                        if (difftime(stop, start) > 30.0) {
                            cout << "ZA DLUGO! Komputer wygrywa walkowerem." << endl;
                            cin.get();
                            koniec_gryKK = true;
                            break;
                        }

                        int w = (wybor_polaKK-1)/3; //wiersze
                        int k = (wybor_polaKK-1)%3; //kolumny
                        if(wybor_polaKK >= 1 && wybor_polaKK <= 9 && gra[w][k] != 'X' && gra[w][k] != 'O')
                        {
                            gra[w][k] = znakGracza;
                            // Po udanym ruchu:
                            AktualizujSVG(gra);
                            if(SprwadzWygranaKK(gra, znakGracza)) {
                                RysowanieKK(gra);
                                cout << "GRATULACJE! Pokonales komputer!" << endl;
                                cin.get(); koniec_gryKK = true;
                            }
                            else {
                                liczba_ruchowKK++;
                                aktualny_gracz = znakPC;
                            }
                        }
                    }
                    else
                    {
                        // Tura KOMPUTERA (Automatyczna)
                        RuchKomputera(gra, znakPC, znakGracza);
                        AktualizujSVG(gra);
                        if(SprwadzWygranaKK(gra, znakPC)) {
                            RysowanieKK(gra);
                            cout << "KOMPUTER WYGRAL! Sprobuj jeszcze raz." << endl;
                            cin.get(); koniec_gryKK = true;
                        }
                        else {
                            liczba_ruchowKK++;
                            aktualny_gracz = znakGracza;
                        }
                    }
                }
                if(liczba_ruchowKK == 9 && !koniec_gryKK) {
                     cout << "REMIS!" << endl; cin.get();
                }
                break;
            case 5: cout << "Warcaby" << endl; break;
            case 6: cout << "Pomoc w budowie." << endl; break;
            case 7: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        cout << endl;
        }
    } while (wybor_interfejs != 7);

    return 0;
}
