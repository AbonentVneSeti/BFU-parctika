#include <iostream>
#include <exception>

#include <string>
#include <vector>

#include <random>
#include <ctime>

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

        void random_sort()// перефасовать колоду
        {
            if(d_array.size() == 0)
                throw std::exception("[deck:random_sort] empty arr");

            //todo 
        }
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

        void take_card_from_deck(deck other) // берется последняя карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_card_from_deck] empty deck");
            p_deck_in_hand.add_card(other.d_array[other.d_array.size()-1]);
        }

        void take_rand_card_from_deck(deck other) // берется случайная карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_rand_card_from_deck] empty deck");
            p_deck_in_hand.add_card(other.d_array[( rand() % other.d_array.size() )]);
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
            for (int i = 0; i < p_deck_in_hand.d_array.size(); i++)
            {
                tmp += p_deck_in_hand.d_array[i].get_value();
            }
            return tmp;
        }
        
        void clear_deck() //опустошить колоду
        {
            p_deck_in_hand.clear_deck();
        }
    };

}

int main()
{
    srand(time(NULL));

    AVS::player player;
    AVS::player dealer;

    AVS::deck X; //как оно бля называется

    const int start_size = 52; //размер колоды

    bool exit = true;//штука для выхода
    bool first_move = true; // первый ход

    while (exit)
    {
        if (first_move)
        {
            X.fill_in_order(start_size);

            std::cout << "Input your bet: 100, 250, 500, 1000, 2500 or 10000" << std::endl;
            int tmp = -1;
            AVS::chip bet;
            while (!bet.set_value(tmp))
            {
                std::cin >> tmp;
            }
            std::cout << "Successful" << std::endl;
            
            for (int i = 0; i < 2; i++)
            {
                player.take_rand_card_from_deck(X);
                dealer.take_rand_card_from_deck(X);
            }

            first_move = false;
        }

        //todo

    }
    

    return 0;
}
