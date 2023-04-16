#include <iostream>
#include <string>
#include <windows.h>
#include "headers_project.hpp"

using namespace std;

int main()
{
    string name, address, delivery_date, choice,delivery_time, food_list[return_size_of_menu()][3];
    int table_number, answer, size_of_food_menu = return_size_of_menu(), total_price = 0;
    bool exit = false;
    vector<pair<string, int>> order_list;

    read_menu_from_file(food_list);

    while(!exit)
    {
        system("cls");
        start_menu(answer);

        switch(answer){
            case 1 : //skladanie zamowienia 
            {  
                name = give_name();
                choose_place(choice);

                if(choice=="na miejscu")
                {
                    delivery_time = "20";
                    in_a_restaurant(table_number);
                    exit = true;
                }
                else if(to_delivery(address, delivery_time))
                    exit = true;
                    
                break;
                // przechodzimy do funkcji add_order oraz do whila pod tym switchem i po zakonczeniu zewnetrznej petli while
            }

            case 2 : //wyswietlanie menu
                system("cls");
                cin.ignore();

                print_food_list(food_list, size_of_food_menu);
                cout<<endl<<"Aby wrocic do ekranu startowego nacisnij ENTER"<<endl;
                getchar();
                system("cls");

                break;

            case 3 : //wyswietla informacje o pierogarni
                system("cls");
                restaurant_data();
                break;

            case 0 : //wyjscie z programu
                cout << "Dziekujemy za korzystanie z naszej aplikacji\n\n";
                system("pause");
                std::exit(1);

            default :
                cout<<"Nie ma takiej opcji!"<<endl<<endl;
        }
    }

    add_order(order_list, food_list, total_price); //tworzenie zamowienia po wybraniu (na miejscu, dowoz)

    do { //drugi interfejs , mozliwosc modyfikacji zamowienia po wybraniu pierwszego dania
        system("cls");  
        cout << "1. Wybierz kolejne danie\n"
                "2. Anuluj jedno z dan\n"
                "3. Pokaz moje zamowienie\n"
                "4. Chce zakonczyc zamowienie!\n";
        cin >> answer;

        switch (answer) {
            case 1: //dodanie kolejnego dania
                add_order(order_list, food_list, total_price); 
                break;

            case 2: //Anulowanie jednego z dań lub błąd i powrót do "do" jesli nie ma nic na liscie zamowienia
                if (!order_list.empty())
                    cancel_an_order(order_list, total_price);
                else
                {
                    cout << "Nie mozesz usunac nic z listy poniewaz jest ona pusta... ";
                    Sleep(1500); 
                }
                break;

            case 3: //wyswietlenie zamowienia na ekranie
                cin.ignore();
                system("cls"); 

                if (!order_list.empty())
                {
                    for (auto &elem: order_list) //automatycznie pobiera elementy z wektora order_list , pierwszy element jest stringiem(nazwa) a drugi jest int (cena)
                        cout << elem.first << " | Cena: " << elem.second << " PLN" << endl;

                    cout << "------------------------------------------------\n"
                            "Cena calkowita = " << total_price << " PLN" << endl << endl;
                    cout << endl << "Aby wrocic do ekranu startowego nacisnij ENTER" << endl;
                    getchar();
                }
                else
                {
                    cout << "Nie mozna wyswietlic listy, poniewaz jest ona pusta... ";
                    Sleep(1500);
                }
                break;

            case 4: //wyjscie z petli 
                summary(name, address, delivery_time, total_price, choice, order_list, table_number); // wyswietlenie planowanego czasu dostawy/przygotowania, zapisanie rachunku do pliku txt oraz zamkniecie aplikacji z komunikatem i oczekiwaniem na nacisniecie klawisza 
                exit = false;
                break;

            case 0: //wyjscie z programu
                cout << "Dziekujemy za korzystanie z naszej aplikacji\n\n";
                system("pause");
                std::exit(1);
                break;

            default: //uzytkownik podal zla wartosc do "answer"
                cout << "Nie ma takiej opcji.  Wybierz ponownie";
                break;
        }
    } while (exit);

    system("pause");
    return 0;
}


