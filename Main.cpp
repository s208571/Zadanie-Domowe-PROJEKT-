//Dawid Tomaszewski s208571 grupa 4a
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

// Funkcja tworzy pusty plik SVG o wymiarach 800x600
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
// Funkcja rysuje kształty na podstawie danych wejściowych użytkownika
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
// Funkcja wyswietla plansze Kolko i Krzyzyk w konsoli
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
// Algorytm sztucznej inteligencji dla gracza komputerowego
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
const int W_ROZMIAR = 8;
// Funkcja ustawia poczatkowy stan planszy do Warcabow
void InicjalizacjaWarcaby(char plansza[W_ROZMIAR][W_ROZMIAR])
{
    for (int i = 0; i < W_ROZMIAR; i++)
    {
        for (int j = 0; j < W_ROZMIAR; j++)
        {
            // Ustawiamy puste pola
            // ' ' to jasne pole (niegrywalne), '.' to ciemne pole (grywalne, puste)
            if ((i + j) % 2 == 0) 
                plansza[i][j] = ' '; 
            else 
                plansza[i][j] = '.'; // Kropka ulatwia celowanie
        }
    }

    // Ustawienie pionków (tylko na ciemnych polach)
    // Czarne ('c') na górze (wiersze 0, 1, 2)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < W_ROZMIAR; j++) {
            if ((i + j) % 2 != 0) plansza[i][j] = 'c';
        }
    }

    // Białe ('b') na dole (wiersze 5, 6, 7)
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < W_ROZMIAR; j++) {
            if ((i + j) % 2 != 0) plansza[i][j] = 'b';
        }
    }
}
// Funkcja wyswietla plansze do Warcabow w konsoli
void RysowanieWarcaby(char plansza[W_ROZMIAR][W_ROZMIAR])
{
    cout << "  0 1 2 3 4 5 6 7" << endl; // Nagłówki kolumn
    cout << " +-----------------+" << endl;
    for (int i = 0; i < W_ROZMIAR; i++)
    {
        cout << i << "|"; // Numer wiersza
        for (int j = 0; j < W_ROZMIAR; j++)
        {
            cout << plansza[i][j] << " ";
        }
        cout << "|" << i << endl;
    }
    cout << " +-----------------+" << endl;
}
// Logika ruchu w Warcabach (sprawdzanie poprawnosci i bicia)
// Funkcja zwraca true, jeśli ruch się udał, false jeśli był niedozwolony
bool WykonajRuchWarcaby(char plansza[W_ROZMIAR][W_ROZMIAR], int w1, int k1, int w2, int k2, char gracz)
{
    // 1. Sprawdzenie zakresu
    if (w1 < 0 || w1 > 7 || k1 < 0 || k1 > 7 || w2 < 0 || w2 > 7 || k2 < 0 || k2 > 7) {
        cout << "Blad: Wyjscie poza plansze!" << endl;
        return false;
    }

    // 2. Sprawdzenie wlasciciela (uzywamy tolower, zeby dzialalo dla b i B)
    char p = plansza[w1][k1];
    if (tolower(p) != gracz) { 
        cout << "Blad: To nie twoj pionek!" << endl;
        return false;
    }

    // 3. Cel musi byc pusty
    if (plansza[w2][k2] != '.') {
        cout << "Blad: Pole zajete!" << endl;
        return false;
    }

    int deltaW = w2 - w1;
    int deltaK = k2 - k1;
    bool czyDamka = isupper(p); // Czy to duza litera (B lub C)?

    // 4. Kierunek ruchu (tylko jesli NIE jest damka)
    if (!czyDamka) 
    {
        if (gracz == 'b' && deltaW > 0) {
            cout << "Blad: Zwykly bialy pionek idzie tylko w gore!" << endl;
            return false;
        }
        if (gracz == 'c' && deltaW < 0) {
            cout << "Blad: Zwykly czarny pionek idzie tylko w dol!" << endl;
            return false;
        }
    }

    // 5. Ruch zwykly (o 1 pole)
    if (abs(deltaW) == 1 && abs(deltaK) == 1)
    {
        plansza[w2][k2] = p;     // Przenosimy pionek (zachowujac czy to b czy B)
        plansza[w1][k1] = '.';
        return true;
    }

    // 6. Bicie (o 2 pola)
    else if (abs(deltaW) == 2 && abs(deltaK) == 2)
    {
        int srodekW = (w1 + w2) / 2;
        int srodekK = (k1 + k2) / 2;
        char zbijany = plansza[srodekW][srodekK];

        if (zbijany == '.' || tolower(zbijany) == gracz) {
            cout << "Blad: Nie mozna bic pustego lub swojego!" << endl;
            return false;
        }

        plansza[w2][k2] = p;     // Przenosimy
        plansza[w1][k1] = '.';   // Czyscimy start
        plansza[srodekW][srodekK] = '.'; // Usuwamy zbitego
        return true;
    }

    return false;
}
// Sprawdza czy ktorys gracz stracil wszystkie pionki
bool CzyKoniecWarcabow(char plansza[W_ROZMIAR][W_ROZMIAR], char &wygrany)
{
    int biale = 0;
    int czarne = 0;

    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(tolower(plansza[i][j]) == 'b') biale++;
            if(tolower(plansza[i][j]) == 'c') czarne++;
        }
    }

    if(biale == 0) { wygrany = 'c'; return true; }
    if(czarne == 0) { wygrany = 'b'; return true; }
    return false;
}
// Generuje plik SVG dla gry w Warcaby
void AktualizujSVG_Warcaby(char plansza[8][8])
{
    ofstream plik("gra_warcaby.svg");
    plik << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    // Plansza 400x400 (każde pole 50x50)
    plik << "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;

    // Rysowanie szachownicy
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            int x = j * 50;
            int y = i * 50;
            string kolor = ((i+j)%2 == 0) ? "wheat" : "saddlebrown"; // Jasne i ciemne pola
            
            plik << "<rect x=\"" << x << "\" y=\"" << y 
                 << "\" width=\"50\" height=\"50\" fill=\"" << kolor << "\" />" << endl;

            // Rysowanie pionków
            char p = plansza[i][j];
            if(p != ' ' && p != '.') // Jeśli jest jakiś pionek
            {
                string kolorPionka = (tolower(p) == 'b') ? "white" : "black";
                string obrys = (tolower(p) == 'b') ? "black" : "white"; // Kontrast
                
                // Rysujemy koło (pionek)
                plik << "<circle cx=\"" << x+25 << "\" cy=\"" << y+25 
                     << "\" r=\"20\" fill=\"" << kolorPionka 
                     << "\" stroke=\"" << obrys << "\" stroke-width=\"2\" />" << endl;
                
                // Jeśli to damka (Duża litera), dodajmy oznaczenie (np. kropka w srodku)
                if(isupper(p)) {
                    plik << "<circle cx=\"" << x+25 << "\" cy=\"" << y+25 
                         << "\" r=\"5\" fill=\"red\" />" << endl;
                }
            }
        }
    }
    plik << "</svg>";
    plik.close();
}
// Zapisuje stan gry (plansze i ture) do pliku tekstowego
void ZapiszGre(char plansza[8][8], char gracz)
{
    ofstream plik("zapis_warcaby.txt");
    if(plik.is_open())
    {
        plik << gracz << endl; // Zapisujemy czyja tura
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                plik << plansza[i][j]; // Zapisujemy plansze znak po znaku
            }
            plik << endl;
        }
        plik.close();
        cout << "Gra zostala zapisana!" << endl;
    }
    else cout << "Blad zapisu pliku!" << endl;
}
// Wczytuje stan gry z pliku tekstowego
bool WczytajGre(char plansza[8][8], char &gracz)
{
    ifstream plik("zapis_warcaby.txt");
    if(plik.is_open())
    {
        plik >> gracz; // Wczytuje gracza (b/c)
        
        // Musimy "połknąć" znak nowej linii (enter), który został po wczytaniu gracza
        char smiec;
        plik.get(smiec); 

        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                // Używamy get(), żeby wczytać też spacje!
                plik.get(plansza[i][j]); 
            }
            // Po każdym wierszu w pliku jest enter, musimy go pominąć
            plik.get(smiec); 
        }
        plik.close();
        cout << "Gra wczytana!" << endl;
        return true;
    }
    cout << "Brak pliku zapisu!" << endl;
    return false;
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
            case 3:{
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
    }}
    break;
            case 4: {cout << "Kolko i krzyzyk z komputerem" << endl;
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
                }}
                break;
            case 5: 
        {
            char planszaW[8][8];
            InicjalizacjaWarcaby(planszaW);
            AktualizujSVG_Warcaby(planszaW);

            char obecny_warcaby = 'b'; 
            bool koniecW = false;
            char zwyciezca = ' ';

            while (!koniecW)
            { 
                cout << "\n=== WARCABY ===" << endl;
                cout << "Opcje: 9 9 9 9 (wyjscie), 8 8 8 8 (zapisz), 7 7 7 7 (wczytaj)" << endl;
                RysowanieWarcaby(planszaW);
                
                if(CzyKoniecWarcabow(planszaW, zwyciezca)) {
                    cout << "KONIEC GRY! Wygrywa: " << (zwyciezca == 'b' ? "BIAŁE" : "CZARNE") << endl;
                    cin.ignore(); cin.get();
                    break;
                }

                cout << "Ruch gracza: " << (obecny_warcaby == 'b' ? "BIALE (b)" : "CZARNE (c)") << endl;
                cout << "Podaj ruch (w1 k1 w2 k2): ";
                
                int w1, k1, w2, k2;
                if (!(cin >> w1 >> k1 >> w2 >> k2)) { // Zabezpieczenie przed wpisaniem liter
                    cout << "Blad danych!" << endl;
                    cin.clear(); cin.ignore(1000, '\n');
                    continue;
                }

                // --- OBSLUGA KOMEND SPECJALNYCH ---
                // Wyjście tylko przy 9 9 9 9
                if (w1 == 9 && k1 == 9 && w2 == 9 && k2 == 9) { 
                    koniecW = true; 
                    break; 
                }
                
                // Zapis tylko przy 8 8 8 8
                if (w1 == 8 && k1 == 8 && w2 == 8 && k2 == 8) { 
                    ZapiszGre(planszaW, obecny_warcaby); 
                    continue; 
                }
                
                // Wczytanie tylko przy 7 7 7 7
                if (w1 == 7 && k1 == 7 && w2 == 7 && k2 == 7) { 
                    if(WczytajGre(planszaW, obecny_warcaby)) {
                        AktualizujSVG_Warcaby(planszaW); // Odswiez SVG po wczytaniu
                    }
                    continue; 
                }

                // --- LOGIKA RUCHU ---
                if (WykonajRuchWarcaby(planszaW, w1, k1, w2, k2, obecny_warcaby))
                {
                    // LOGIKA PROMOCJI (DAMKA)
                    // Jeśli biały ('b') dotarł do wiersza 0 -> staje się 'B'
                    if (obecny_warcaby == 'b' && w2 == 0) planszaW[w2][k2] = 'B';
                    // Jeśli czarny ('c') dotarł do wiersza 7 -> staje się 'C'
                    if (obecny_warcaby == 'c' && w2 == 7) planszaW[w2][k2] = 'C';

                    // Aktualizacja i zmiana tury
                    AktualizujSVG_Warcaby(planszaW);
                    obecny_warcaby = (obecny_warcaby == 'b' ? 'c' : 'b');
                }
                else
                {
                    cout << "Blad ruchu! Wcisnij ENTER..." << endl;
                    cin.ignore(); cin.get();
                }
            }
            break; 
        }
            case 6: 
            cout << "=== POMOC ===" << endl;
            cout << "1. Kolko i Krzyzyk: Wybieraj pola numeryczne 1-9." << endl;
            cout << "2. Warcaby: Ruchy podajesz jako 4 liczby: wiersz_z kolumna_z wiersz_do kolumna_do." << endl;
            cout << "   Przyklad: '5 0 4 1' przesuwa pionek z pola (5,0) na (4,1)." << endl;
            cout << "   Biale (b) startuja na dole (wiersze 5-7), Czarne (c) na gorze." << endl;
            cout << "   Aby zapisac gre wpisz: 8 8 8 8. Aby wczytac: 7 7 7 7." << endl;
            cout << "Wcisnij ENTER aby wrocic." << endl;
            cin.get();
            break;
            case 7: cout << "Zamykanie programu..." << endl; break;
            default: cout << "Nieznana opcja!" << endl; break;
        cout << endl;
        }
    } while (wybor_interfejs != 7);

    return 0;
}