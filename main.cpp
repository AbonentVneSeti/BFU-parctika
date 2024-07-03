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
    //шрифт и открытие окна
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BlackJack");
    sf::Font font;
    if (!font.loadFromFile("assets/different/LavirePersonalUse.otf"))
    {
        std::cerr << "Error to upload font :(" << std::endl;
        return 404;
    }

    //фон игры
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/backgrounds/background3.jpg"))
    {
        std::cerr << "Error to upload background :(" << std::endl;
        return 404;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    //рамка играть
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color::White);
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(2);
    playButton.setScale(1.0f, 0.9f);
    playButton.setPosition(900, 403);

    //рамка правил
    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    rulesButton.setFillColor(sf::Color::White);
    rulesButton.setOutlineColor(sf::Color::Black);
    rulesButton.setOutlineThickness(2);
    rulesButton.setScale(1.0f, 0.9f);
    rulesButton.setPosition(900, 454);

    //рамка настроек
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setOutlineColor(sf::Color::Black);
    settingsButton.setOutlineThickness(2);
    settingsButton.setScale(1.0f, 0.9f);
    settingsButton.setPosition(900, 504);

    //рамка выхода
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::White);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setScale(1.0f, 0.9f);
    exitButton.setPosition(900, 554);

    //кнопка играть
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(40);
    playText.setString("Play");
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(960, 400);

    //кнопка правил
    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(40);
    rulesText.setString("Rules");
    rulesText.setFillColor(sf::Color::Black);
    rulesText.setPosition(953, 450);

    //кнопка настроек
    sf::Text settingsText;
    settingsText.setFont(font);
    settingsText.setCharacterSize(40);
    settingsText.setString("Settings");
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(929, 500);

    //кнопка выхода
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(40);
    exitText.setString("Exit");
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(968, 550);
    sf::FloatRect exitButtonRect = exitText.getGlobalBounds();

    //курсор
    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromFile("assets/different/cursor.png")) 
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite(cursorTexture);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 3.0f, cursorTexture.getSize().y / 2.0f);
    cursorSprite.setPosition(300.f, 400.f);
    cursorSprite.setScale(0.06f, 0.06f);
    window.setMouseCursorVisible(false);

    //вывод изображений
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (exitButtonRect.contains(mousePos.x, mousePos.y))
                {
                    window.close();
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        cursorSprite.setPosition(static_cast<sf::Vector2f>(mousePos));

        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(playButton);
        window.draw(rulesButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        window.draw(playText);
        window.draw(rulesText);
        window.draw(settingsText);
        window.draw(exitText);
        window.draw(cursorSprite);
        window.display();
    }

    /*
    srand(time(NULL));

    AVS::deck A;

    A.fill_random(100);
    for (int i = 0; i < A.d_array.size(); i++)
        std::cout << A.d_array[i].get_value() << std::endl;
    A.refill_random(5);

    std::cout << "refill" << std::endl;
    for (int i = 0; i < A.d_array.size(); i++)
        std::cout << A.d_array[i].get_value() << std::endl;
    */

    return 0;
}
