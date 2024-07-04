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
            setvalue(value);
        }

        ~card() = default;
        
        void setvalue(int value)
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

        void add_card(int value)
        {
            d_array.push_back(card(value));
        }

        void fill_random(int size)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");

            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
        }

        void refill_random(int size)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");
            d_array.clear();
            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
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
            setvalue(value);
        }

        ~chip() = default;

        void setvalue(int value)
        {
            switch (value)
            {
            case 100:
                c_value = value;
                path_to_texture = "assets\\chips\\100.png";
                return;
            case 250:
                c_value = value;
                path_to_texture = "assets\\chips\\250.png";
                return;
            case 500:
                c_value = value;
                path_to_texture = "assets\\chips\\500.png";
                return;
            case 1000:
                c_value = value;
                path_to_texture = "assets\\chips\\1000.png";
                return;
            case 2500:
                c_value = value;
                path_to_texture = "assets\\chips\\2500.png";
                return;
            case 10000:
                c_value = value;
                path_to_texture = "assets\\chips\\10000.png";
                return;
            default:
                throw std::exception("[chip:setvalue] wrong value");
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

    class Player //класс игрока отдельного, тут короче будут действия типо взять карту там и т.д.
    {
    private:
        deck deck_in_hand;
        chip bet;
    public:

        player() = default;

        void setbet
        {
            //todo
        }

        void take_card_from_deck(deck A)
        {
            //todo
        }

        void take_card(card A)
        {
            //todo
        }

        bool check_value_in_hand()
        {
            //todo
        }

    };

}

int main()
{
    
    srand(time(NULL));

    AVS::deck A;

    A.fill_random(100);
    for (int i = 0; i < A.d_array.size(); i++)
        std::cout << A.d_array[i].get_value() << std::endl;
    A.refill_random(5);

    std::cout << "refill" << std::endl;
    for (int i = 0; i < A.d_array.size(); i++)
        std::cout << A.d_array[i].get_value() << std::endl;
    

    return 0;
}
