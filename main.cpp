#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

        void setvalue(int value)
        {
            if (value < 1 || value > 13)
                throw std::exception("[card] wrong value");
            c_value = value;

            switch (value)
            {
            case 1:
                path_to_texture = "assets\\A.png";
                break;
            case 11:
                path_to_texture = "assets\\J.png";
                break;
            case 12:
                path_to_texture = "assets\\Q.png";
                break;
            case 13:
                path_to_texture = "assets\\K.png";
                break;
            default:
                path_to_texture = "assets\\" + std::to_string(value) + ".png";
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

    struct deck
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
