#include <iostream>
#include <exception>

#include <string>
#include <vector>

#include <random>
#include <ctime>
#include <windows.h>

namespace AVS
{
    class card // Класс, который описывает отдельную карту.
    {
    private:
        int c_value = 0;
        std::string path_to_texture;
    public:
        card() = default;
        
        card(int value)
        {
            set_value(value);
        }

        ~card() = default;
        
        void set_value(int value)
        {
            if (value < 1 || value > 13)
                throw std::exception("[card:setvalue] wrong value");
            c_value = value;

            switch (value)
            {
            case 1:
                path_to_texture = "assets\\cards\\A.png";
                return;
            case 11:
                path_to_texture = "assets\\cards\\J.png";
                return;
            case 12:
                path_to_texture = "assets\\cards\\Q.png";
                return;
            case 13:
                path_to_texture = "assets\\cards\\K.png";
                return;
            default:
                path_to_texture = "assets\\cards\\" + std::to_string(value) + ".png";
            }
        }
        
        int get_value()
        {
            return c_value;
        }
        
        std::string get_texture_path()
        {
            return path_to_texture;
        }
    };

    struct deck // грубо говоря массив для карт
    {
        std::vector<card> d_array;

        deck() = default;

        ~deck() = default;

        void add_card(int value)//добавить карту, заданую только значением
        {
            d_array.push_back(card(value));
        }

        void add_card(card A) // добавить заданную карту
        {
            d_array.push_back(A);
        }

        void fill_random(int size) // добавить случайные карты(всего size штук)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");

            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
        }

        void refill_random(int size) // Полностью перезаполнить случайными картами (опять size штук)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");
            d_array.clear();
            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
        }

        void clear_deck() //опустошить колоду
        {
            d_array.clear();
        }

        void fill_in_order(int size) //заполнить колоду по-порядку
        {
            if (size < 1)
                throw std::exception("[deck:fill_in_ord] wrong size");
           
            add_card(1);
            for (int i = 1; i < size; i++)
            {
                add_card( i % 13 + 1 );
            }
        }
        void erase(int i)
        {
            if (i >= d_array.size() || i < 0)
                throw std::exception("[deck:erase] wrong element");
            
            d_array.erase(d_array.begin() + i);
        }

        int size()
        {
            return d_array.size();
        }

        card& operator[] (int i)
        {
            return d_array[i];
        }

        /*
        void random_sort()// перефасовать колоду
        {
            if(d_array.size() == 0)
                throw std::exception("[deck:random_sort] empty arr");

            //todo 
        }
        */
    };

    class chip // фишка для ставки
    {
    private:
        int c_value = 0;
        std::string path_to_texture;
    public:
        chip() = default;

        chip(int value)
        {
            set_value(value);
        }

        ~chip() = default;

        bool set_value(int value)
        {
            switch (value)
            {
            case 0:
                c_value = 0;
                path_to_texture = "None";
                return true;
            case 100:
                c_value = value;
                path_to_texture = "assets\\chips\\100.png";
                return true;
            case 250:
                c_value = value;
                path_to_texture = "assets\\chips\\250.png";
                return true;
            case 500:
                c_value = value;
                path_to_texture = "assets\\chips\\500.png";
                return true;
            case 1000:
                c_value = value;
                path_to_texture = "assets\\chips\\1000.png";
                return true;
            case 2500:
                c_value = value;
                path_to_texture = "assets\\chips\\2500.png";
                return true;
            case 10000:
                c_value = value;
                path_to_texture = "assets\\chips\\10000.png";
                return true;
            default:
                return false;
                //throw std::exception("[chip:setvalue] wrong value");
            }
        }

        int get_value()
        {
            return c_value;
        }

        std::string get_texture_path()
        {
            return path_to_texture;
        }
    };

    class player //класс игрока отдельного, тут короче будут действия типо взять карту там и т.д.
    {
    private:
        deck p_deck_in_hand;
        chip p_bet = 0;
    public:

        player() = default;

        void set_bet(chip bet)// по факту можно рассмотреть ставку не только из одной фишки, а из л/к фишек, которые унас есть, однако нужно тогда сделать то как они лежат
        {
            p_bet = bet;
        }

        chip get_bet()
        {
            return p_bet;
        }

        void take_card_from_deck(deck& other) // берется последняя карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_card_from_deck] empty deck");

            p_deck_in_hand.add_card(other[other.d_array.size()-1]);
            other.erase(other.d_array.size() - 1);
        }

        void take_rand_card_from_deck(deck& other) // берется случайная карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_rand_card_from_deck] empty deck");

            int i = rand() % other.d_array.size();
            p_deck_in_hand.add_card(other[i]);
            other.erase(i);
        }

        void take_card(card A) // берется заданная карта
        {
            p_deck_in_hand.add_card(A);
        }

        int check_value_in_hand() // суммарное значение карт на руках
        {
            if(p_deck_in_hand.d_array.empty())
                return 0;
            int tmp = 0;
            for (int i = 0; i < p_deck_in_hand.size(); i++)
            {
                tmp += p_deck_in_hand[i].get_value();
            }
            return tmp;
        }
        
        void clear_deck() //опустошить колоду
        {
            p_deck_in_hand.clear_deck();
        }

        deck& get_deck()
        {
            return p_deck_in_hand;
        }
    };

}

int main()
{
    AVS::player player;
    AVS::player dealer;

    short start_size = 52;// размер колоды
    int all_money = 10000; //все деньги, желательно тоже считывать из файла

    AVS::deck X; //я всё ещё не знаю как его назвать

    bool exit = true;//штука для выхода
    bool first_move = true; // первый ход
    bool dealers_move = false; // ход дилера
    bool win = false; // в случае победы
    bool lose = false; // в случае поражения
    bool push = false; // в случае пуша

    while (exit)
    {
        if (first_move) //первый ход
        {
            X.fill_in_order(start_size);//перезаполняем колоду

            std::cout << "Your money: " << all_money << std::endl;
            std::cout << "Input your bet: 0, 100, 250, 500, 1000, 2500 or 10000" << std::endl;

            int tmp = -1;
            AVS::chip bet;
            while (!bet.set_value(tmp)) // цикл для считывания ставки, в случае, с сфмл, то легче сделать просто кнопки, устанавливающие сумму ставки
            {
                std::cin >> tmp;
                if (tmp > all_money)
                {
                    std::cout << "out of money" << std::endl;
                    tmp = -1;
                }
            }
            player.set_bet(AVS::chip(tmp));

            std::cout << "Successful" << std::endl;


            for (int i = 0; i < 2; i++) //берутся по 2 карты игроку и дилеру, можно добавить сразу две анимации
            {
                player.take_rand_card_from_deck(X);
                dealer.take_rand_card_from_deck(X);
            }

            first_move = false;

            Sleep(500);
            system("cls");
        }
        else if (!dealers_move) // ход игрока; здесь нужно заменить cin на кнопки, а также добавить анимацию взятия карты
        {
            std::cout << "moves:\n1 - take card\n2 - enough\n3 - exit" << std::endl;
            int move;
            do
            {
                std::cin >> move;
            } while (move != 1 && move != 2 && move != 3);

            switch (move)
            {
            case 1://взятие карты
                player.take_rand_card_from_deck(X);
                break;
            case 2://передача хода
                dealers_move = true;
                break;
            case 3://выход, он не нужен если через сфмл
                exit = false;
                break;
            default:
                break;
            }
        }
        else if (dealers_move)//тоже логическая часть, можно добавить сюда анимацию взятия карт для дилера
        {
            if (dealer.check_value_in_hand() <= player.check_value_in_hand())
            {
                dealer.take_rand_card_from_deck(X);
            }
        }

        //check win
        {//чисто логическая часть, не трогаем, пусть работает
            short pltmp = player.check_value_in_hand();
            short dltmp = dealer.check_value_in_hand();

            if (pltmp == dltmp && pltmp >= 21)
                push = true;
            else if (pltmp == 21)
                win = true;
            else if (dltmp == 21)
                lose = true;
            else if (pltmp > 21 && dltmp < 21)
                lose = true;
            else if (pltmp < 21 && dltmp > 21)
                win = true;
            else if (pltmp > 21 && dltmp > 21)
            {
                if (pltmp < dltmp)
                    win = true;
                else
                    lose = true;
            }
            else if (dltmp > pltmp && dealers_move)
                lose = true;
        }

        //базовый вывод, заменить на постоянный вывод в сфмле, там ну как-нибудь.
        system("cls");
        std::cout << "your bet: " << player.get_bet().get_value() << "     all your money: " << all_money << std::endl;
        std::cout << "your score: " << player.check_value_in_hand() << std::endl;
        std::cout << "dealer score: " << dealer.check_value_in_hand() << std::endl;

        if (win || lose || push) // cout заменить на вывод сообщения на экран.
        {
            if (win)
            {
                std::cout << "You win!" << std::endl;
                all_money += player.get_bet().get_value();
            }
            if (lose)
            {
                std::cout << "You lose!" << std::endl;
                all_money -= player.get_bet().get_value();
            }
            else
                std::cout << "push" << std::endl;

            std::cout << "1 - restart\n3 - exit" << std::endl;
            int move;
            do
            {
                std::cin >> move;
            } while (move != 1 && move != 3);
            switch (move)
            {
            case 1://restart
                first_move = true;
                dealers_move = false;
                win = false;
                lose = false;
                push = false;
                player.set_bet(0);
                player.clear_deck();
                dealer.clear_deck();
                system("cls");
                break;
            case 3://выход
                exit = false;
                break;
            default:
                break;
            }
        }
        Sleep(300);
    }

    return 0;
}

//так, описание работы краткое
// сначала идёт 
//      либо первый ход, т.е. устанавливается ставка, берутся 2 карты и т.д.
//      либо ход игрока, т.е. возможность просто выключить прогу(ну это тебе не надо), взять карту, и передать ход дилеру
//      либо ход дилера, который берет карту, если у него меньше очков, чем у игрока.
// после 1-й из этих операций идёт проверка победы(или непобеды), которая просто меняет булы победы or поражения or пуша на труе
// ну и после всего идёт проверка на win,lose,push, и если что-то из этого есть, то игроку даётся возможность выйти, или играть следующую,
//      соотв-но меняются и деньги и т.д., устанавливается первый ход
// потом цикл повторяется


//получить общий счёт всех карт в колоде игрока:    player.check_value_in_hand()
//получить колоду игрока:                           player.get_deck()
//получить карту в колоде игрока:                   player.get_deck()[i], где i - номер нужной карты в колоде.
//получить счёт карты в колоде игрока:              player.get_deck()[i].get_value()
//получить путь к текстуре конкретной карты:        player.get_deck()[i].get_texture_path()


//получить путь к текстуре фишки(Ставки) у игрока:  player.get_bet().get_texture_path()
//получить значение фишки(Ставки) у игрока:  player.get_bet().get_value()