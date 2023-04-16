#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <time.h>
#include "headers_project.hpp"

using namespace std;

//wczytanie menu i ewentualne info o bledzie
void read_menu_from_file(string food_list[][3])
{
    ifstream file;
    file.open("menu.txt");

    string line, word;

    if(file.is_open())
    {
        int i = 0;
        while (getline(file, line))
        {
            stringstream full_line(line);
            int j = 0;

            while(getline(full_line, word, ';'))
            {
                food_list[i][j] = word;

                j++;
            }

            i++;
        }
    }
    else
	{
        cout << "Nie udalo sie otworzyc pliku" << endl;
        exit(3);
    }
    
    file.close();
}

void start_menu(int &answer){ // wyswietla dane restauracji

    
    cout<< "Pierogarnia CDV" << endl<< endl;
    Sleep(1000); //program czeka sekundę

    cout << "Co chcesz zrobic?" << endl;
    cout << "1.Zlozyc zamowienie"<< endl;
    cout << "2.Zobaczyc menu" << endl;
    cout << "3.Zobaczyc informacje o restauracji" << endl;
    cout << "0.Wyjsc" << endl;
    cout << "Wybor : ";
    cin >> answer;
    system("cls"); // wyczyszcza to co jest wyswietlone na ekranie
}

//case 1
string give_name(){ // uzytkownik wpisuje imię

    string name;
    cout<<"Podaj swoje imie : ";
    cin>>name;
    system("cls");
    return name;
}

void choose_place(string &choice){ // wybór czy danie ma być dostarczone na miejscu czy na dowóz

    cin.ignore(); // inaczej przyjmuje poprzedni cin za dane do getline

    time_t now = time(0);
    tm *ltm = localtime(&now);

    int hour = ltm->tm_hour;
    
    while(true){

        cout<<"Chcesz zjesc na miejscu czy na dowoz ?"<<endl;
        cout<<"Napisz : na miejscu lub na dowoz : ";
        getline(cin, choice);  // sam cin pobiera tylko do spacji
        system("cls");

        transform(choice.begin(),choice.end(),choice.begin(),::tolower); // jesli uzytkownik poda wielką litere to zostanie zmieniona i warunek zadziala poprawnie

        if(choice =="na miejscu")
            break;
        else if(choice =="na dowoz")
            if(hour >= 10 && hour <= 18)    // *dodac funkcje sprawdzajaca date itp... (returnuje true lub false)*
                break;
            else
            {
                cout << "Nie przyjmujemy zamowien na dowoz o tej godzinie..." << endl;
                Sleep(1500);
                system("cls");
            }
        else
            cout<<"Nie ma takiej opcji ! Wybierz ponownie. "<<endl<<endl;
    }
}

void in_a_restaurant(int &table_number)
{
    srand(time(NULL));  //srand- start randomize , time(NULL) pobiera liczbe sekund od 1 stycznia 1970r.
    table_number = rand()%30+1; //losuje liczbe od 1 do 30

    cout << "Twoj numerek stolika to : " << table_number << endl << endl;
    Sleep(2000);
}

bool to_delivery(string &address, string &delivery_time)
{  //uzytkownik wybral dowóz
//tutaj komenda cin.ignore powoduje problem gdzie program czeka na znak bez komunikatu a bez smiga jak talala

    int choice;
    cout << "Podaj swoj adres : ";
    getline(cin,address);

    system("cls");

    if(confirm_opening_time(delivery_time))
        return true;
    else
        return false;
}

//case 2 funkcje  //pokazuje menu 
void print_food_list(string food_list[][3], const int &size)
{
    int iterator = 1;
    for(int i=0; i<size; i++)
    {
        cout << iterator << ". Danie: " << food_list[i][0] << " | Cena - " << food_list[i][1] << " PLN | Skladniki: " << food_list[i][2]<< endl;
        iterator++;
    }
}
//case 3 funkcje   //informacje o restauracji
void restaurant_data()
{
    cin.ignore();
    cout << "************   INFORMACJE O PIEROGARNI  ************" << endl;
    cout << "Pierogarnia CDV" << endl << endl;
    cout << "Poznan, ul.Kutrzeby 69a" << endl << endl;
    cout << "Nr telefonu: +48 943 217 381" << endl;
    cout << "Godziny otwarcia:" << endl;
    cout << "Poniedzialek:         10:00 - 21:00" << endl;
    cout << "Wtorek:               10:00 - 21:00" << endl;
    cout << "Sroda:                10:00 - 21:00" << endl;
    cout << "Czwartek:             10:00 - 19:00" << endl;
    cout << "Piatek:               12:00 - 23:00" << endl;
    cout << "Sobota:               12:00 - 23:00" << endl;
    cout << "Niedziela:            10:00 - 19:00" << endl;
    cout << endl << "Aby wrocic do ekranu startowego nacisnij ENTER " << endl;
    getchar();
}


//tworzenie zamowienia po wybraniu (na miejscu, dowoz)
void add_order(vector<pair<string, int>> &order_list, string food_list[][3], int &total_price)
{
    system("cls");

    string food_name;
    int servings, price, food_index;

    do
    {
        print_food_list(food_list, return_size_of_menu());
        cout << "\nWybierz danie z listy : ";
        cin >> food_index;

        if(food_index >= 1 && food_index <= return_size_of_menu())
        {
            cout << "\nTwoj wybor: " << food_list[food_index-1][0] << " | " << food_list[food_index-1][1] << " PLN\n\n";
            if(validate()) //uzytkownik potwierdzil swoj wybor
                break;
            else
                system("cls");
        }
        else
        {
            system("cls");
            cout << "Niepoprawny numer dania...\n";
        }
    } while(true);

    food_name = food_list[food_index-1][0];
    price = stoi(food_list[food_index-1][1]);

    system("cls");

    do
    {
        cout << "\n************** |" << food_list[food_index-1][0] << " | " << food_list[food_index-1][1] << " PLN| **************\n";
        cout << "\nPodaj ile porcji dania chcesz dodac do swojego zamowienia (1-12): ";
        cin >> servings;

        if(servings >= 1 && servings <= 12)
            break;
        else
        {
            system("cls");
            cout << "Ilosc porcji nieprawidlowa...\n";
        }
    } while(true);

    order_list.emplace_back(food_name, price * servings);
    total_price += price * servings;
}

// tylko w drugim interfejsie
void cancel_an_order(vector<pair<string, int>> &order_list, int &total_price)
{
    int choice;
    char answer;

    system("cls");

    do
    {
        int i = 1;
            
        for (auto &elem: order_list)
        {
            cout << i << ". " << elem.first << ", Cena: " << elem.second << " PLN" << endl;
            i++;
        }

        cout << "Ktora pozycje ze swojego zamowienia chcialbys usunac ? \n";
        cin >> choice;

        if(choice > 0 && choice <= order_list.size())
        {
            if(validate())
            {
                total_price -= order_list[choice - 1].second;
                order_list.erase(order_list.begin() + choice - 1);
                break;
            }
            else
                system("cls");
        }
        else
        {
            system("cls");
            cout << "Tego numeru nie ma na liscie...\n\n";
        }
    } while(true);
}
// tylko w drugim interfejsie
void summary(string &name, string &address, string &delivery_time, int &total_price, string &choice, vector<pair<string, int>> &order_list, int &table_number)
{
    int index = delivery_time.find(':')+1;

    system("cls");
    cout << "Zamowienie klienta " << name << endl;
    
    if(choice == "na miejscu")
        cout << "Planowany czas przygotowania zamowienia to : " << delivery_time << " " << return_postfix(delivery_time) << endl;
    else
    {
        if(stoi(delivery_time.substr(index)) < 10)
        {
            delivery_time.insert(index, "0");
            cout << "Planowany czas dostawy - " << delivery_time;
        }
        else
            cout << "Planowany czas dostawy - " << delivery_time;
    }

    cout << "\nKwota do zaplaty wynosi : " << total_price << " PLN" << endl;

    Sleep(3000);

    cout << "\nZapisywanie rachunku do pliku...\n";

    Sleep(1000);
    system("cls");
    
    for(int i=0; i<=2; i++)  //program udaje, że pracuje xd
    {
        for(int j=0; j<=2; j++)
        {
            cout<<".";
            Sleep(300);
        }
    system("cls");
    }

    ofstream bill; //zapisywanie rachunku do pliku
    bill.open("rachunek.txt");
    
    if(choice == "na miejscu")
    {
        if(bill.is_open())
        {
            bill << " --------- Zamowienie klienta " << name << " ---------\n"
                    "Numer stolika " << table_number <<
                    "\n\n Czas oczekiwania na zamowienie - " << delivery_time << " " << return_postfix(delivery_time) << endl;
            bill << "\nZawartosc zamowienia:\n"
                    "------------------------------------------------\n";

            for (auto &order: order_list)
                bill << order.first << "   |   " << order.second << " PLN\n";

            bill << "------------------------------------------------\n"
                    "Podliczona cena za zamowienie:    " << total_price << " PLN";

            bill.close();
        } 
    } 
    else
    {
        if(bill.is_open())
        {
            bill << " --------- Zamowienie klienta " << name << " ---------\n";

            if(stoi(delivery_time.substr(index)) < 10)
            {
                delivery_time.insert(index, "0");
                bill << "\n Czas dostawy - " << delivery_time[0] << delivery_time[1] << delivery_time[2] << "0" << delivery_time[index];
            }
            else
                bill << "\n Czas dostawy - " << delivery_time;

            bill << "\n Adres dostawy: " << address <<
                    "\n\n Zawartosc zamowienia:\n"
                    "------------------------------------------------\n";

            for (auto &order: order_list) //dla kazdego elementu z zamowienia
                bill << order.first << "   |   " << order.second << " PLN\n";

            bill << "------------------------------------------------\n"
                    "Podliczona cena za zamowienie:    " << total_price << " PLN";

            bill.close(); //zamkniecie pliku
        }
    }

    cout << endl <<  "Twoj rachunek zostal zapisany do pliku tekstowego !" << endl;
    cout << "Dziekujemy i zapraszamy ponownie!" << endl << endl;
}

//funkcja pomocnicza do wyznaczenia dlugosci tablicy dla zmiennej food_list z ktorej 
//na ekran wyrzucamy menu : read_menu_from_file(food_list);
int return_size_of_menu()
{
    int size = 0;

    ifstream file; 
    file.open("menu.txt"); //przypisuje do "file" plik menu.txt i go otwiera

    string line; 

    if(file.is_open()) 
    {
        while (getline(file, line)) //pobiera linie z "file" (czyli z menu.txt) i przypisuje ja do "line"
            size++;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        exit(3);
    }
    file.close(); //zamyka plik

    return size;
}


bool validate() //uzytkownik potwierdza swoj wybor 
{
    char are_you_sure;
    
    while(true) 
    {
        cout << "Czy jestes pewien swojego wyboru? (t/n) ";
        cin >> are_you_sure;
    
        are_you_sure = tolower(are_you_sure); //zamienia pojedyczny znak na maly
    
        if(are_you_sure == 't' || are_you_sure == 'n')
            break;
        else
        {
            system("cls");
            cout << "Wpisz tylko t lub n!" << endl;
        }
    }
    
    if(are_you_sure == 't')
        return true;
    else
        return false;
}

string return_postfix(string &time_in_mins)
{
    char last_num_char = time_in_mins.at(time_in_mins.length() - 1);
    int last_num_int = int(last_num_char) - '0';

    if(time_in_mins == "1")
        return "minuta";
    if((last_num_int >= 2 && last_num_int <= 4))
        return "minuty";
    if(last_num_int == 0 || (last_num_int >= 5 && last_num_int <= 9))
        return "minut";

    return "";
}

bool confirm_opening_time(string &delivery_time)
{
    time_t czas;
    SYSTEMTIME st;
    GetSystemTime(&st);
    struct tm * data;
    char godzina[ 80 ];
    time( & czas );
    data = localtime( & czas );

    strftime( godzina, 80, "Teraz jest %H:%M ", data ); // tu jest aktualna godzina
    cout << godzina << endl;
    int time_open, time_closed;


    switch(st.wDayOfWeek) {  // pobierany jest aktualny dzien tygodnia i w zaleznosci od niego wybiera sie case
        case 1:
        case 2:
        case 3:
            cout << "Dzis restauracja pracuje w godzinach: 10-21" << endl;
            Sleep(3000);
            time_open = 10;
            time_closed = 21;
            break;
        case 4:
        case 7:
            cout << "Dzis restauracja pracuje w godzinach: 10-19" << endl;
            Sleep(3000);
            time_open = 10;
            time_closed = 19;
            break;
        case 5:
        case 6:
            cout << "Dzis restauracja pracuje w godzinach: 12-23" << endl;
            Sleep(3000);
            time_open = 12;
            time_closed = 23;
            break;
    }

    if(st.wHour >= time_open && st.wHour <= time_closed) //sprawdza czy godzina nie minela
        return confirm_time(delivery_time, time_open, time_closed);
    else
    {
        cout << "Ta godzina juz minela ! Zamowienie niemozliwe" << endl;
        Sleep(1500);
        return false;
    }
}

bool confirm_time(string &delivery_time, int &time_open, int &time_closed) // sprawdzenie czy godzina jest do realizacji
{
    time_t nowuptime = time(0);
    tm *ltm = localtime(&nowuptime);
    int hour = ltm->tm_hour, minute = ltm->tm_min, delivery_hour, delivery_minute;
    string answer;

    cout << "Pierogarnia jest aktualnie otwarta" << endl;

    while(true)
    {
        system("cls");
        cout << "Podaj godzine dowozu ktora cie interesuje (godzina i minuty oddzielone spacja) " << endl;
        cin >> delivery_hour >> delivery_minute;

        if(delivery_hour >= hour)
        {
            if (delivery_hour == hour)
            {
                if (delivery_minute == minute)
                {
                    cout << "Niestety nie mozemy przyjac zamownia do realizacji w tych godzinach " << endl;
                    Sleep(1500);
                    return false;
                }
                else if (delivery_minute > minute)
                {
                    if (delivery_minute - minute >= 25)
                    {
                        if(minute_check(time_open, time_closed, delivery_minute, delivery_hour))
                        {
                            cout << "Zapraszamy do zlozenia zamowienia" << endl;
                            delivery_time = to_string(delivery_hour) + ":" + to_string(delivery_minute);
                            return true;
                        }
                        else
                            return false;
                    }
                    else
                    {
                        cout << "Niestety nie mozemy przyjac zamownia do realizacji w tych godzinach " << endl;
                        Sleep(1500);
                        return false;
                    }
                }
                else
                {
                    cout << "Niestety nie mozemy przyjac zamownia do realizacji w tych godzinach " << endl;
                    Sleep(1500);
                    return false;
                }
            }
            else
            {
                if(minute_check(time_open, time_closed, delivery_minute, delivery_hour))
                {
                    cout << "Zapraszamy do zlozenia zamowienia" << endl;
                    delivery_time = to_string(delivery_hour) + ":" + to_string(delivery_minute);
                    return true;
                }
                else
                    return false;
            }
        }
        else
        {
            cout << "Ta godzina juz minela...";
            return false;
        }
    }
}

bool minute_check(int &time_open, int &time_closed , int &delivery_minute, int &delivery_hour) //sprawdza czy godzina i minuta ISTNIEJE i czy jest mozliwe zamowienie
{
    if ((delivery_hour >= 0) && (delivery_hour <= 23) && (delivery_minute >= 0) && (delivery_minute <= 59)) // czy godzina istnieje
    {
        if((delivery_hour > time_open) && (delivery_hour < time_closed)) // czy czas jest w pracy pierogarnii
        {
            if((delivery_hour == time_closed - 1) && (delivery_minute > 30)) // czy zdazy sie zrealizowac zamowienie przed koncem dnia
            {
                cout << "Przykro nam ale nie zdazymy zrealizowac twojego zamowienia przed koncem pracy pierogarnii"<< endl;
                Sleep(2000);
                return false;
            }
            else
                return true;
        }
        else
        {
            cout << "Przykro nam, godzina wykracza poza godziny pracy pierogarni...";
            Sleep(2000);
            return false;
        }
    }
    else
    {
        cout << "Przykro nam, godzina nie istnieje...";
        Sleep(2000);
        return false;
    }
}