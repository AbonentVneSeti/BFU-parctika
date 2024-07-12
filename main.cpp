#include <iostream>
#include <exception>

#include <string>
#include <vector>

#include <random>
#include <ctime>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

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

    class Button {
    private:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f normal;
        sf::Vector2i TextureSize;
        sf::Vector2i TextureStart;
        sf::RenderWindow* window;
        sf::Color ButtonColor;
        sf::Color BorderColor;
        bool BorderSet = false, ButtonTextureEnabled = false, BorderTextureEnabled, in = true;
        float BorderSize = 0;
        sf::Texture ButtonTexture;
        sf::Sprite ButtonSprite;
        sf::Mouse::Button MouseClickButton;
    public:
        Button(sf::Vector2f pos, sf::Vector2f sizes, sf::RenderWindow* wind) {
            position = pos;
            size = sizes;
            window = wind;
        }

        void setButtonColor(sf::Color col) {
            ButtonColor = col;
            ButtonTextureEnabled = false;
        }

        void setButtonTexture(std::string name, sf::Vector2i place, sf::Vector2i siz) {
            TextureSize = siz, TextureStart = place;
            if (!ButtonTexture.loadFromFile(name)) MessageBox(NULL, "Не удалось загрузить файл", "Ошибка", MB_ICONERROR);
            ButtonSprite.setTexture(ButtonTexture);
            ButtonTextureEnabled = true;
        }

        void setBorder(int sizew) {
            if (sizew % 2 != 0) { BorderSize = sizew + 1; }
            else BorderSize = sizew;
            BorderSet = true;
        }

        void setBorderColor(sf::Color col) {
            BorderColor = col;
            BorderSet = true;
        }

        void setMouseClickButton(sf::Mouse::Button click) {
            MouseClickButton = click;
        }
        bool check_mouse_click()
        {
            sf::Vector2i MouseCoords = sf::Mouse::getPosition(*window);
            sf::Vector2u WinSize = (*window).getSize();
            if (MouseCoords.x <= WinSize.x && MouseCoords.y <= WinSize.y && MouseCoords.x >= position.x && MouseCoords.x <= position.x + normal.x && MouseCoords.y >= position.y && MouseCoords.y <= position.x + normal.y && sf::Mouse::isButtonPressed(MouseClickButton)) {
                return true;
            }
            else return false;
        }
        void draw() {
            if (in) normal = size;
            if (size.x > TextureSize.x || size.y > TextureSize.y) size.x = TextureSize.y; size.y = TextureSize.y;
            if (!BorderSet && !ButtonTextureEnabled) {
                sf::RectangleShape button(size);
                button.setPosition(position);
                button.setFillColor(ButtonColor);
                (*window).draw(button);
            }
            if (!BorderSet && ButtonTextureEnabled) {
                ButtonSprite.setPosition(position);
                (*window).draw(ButtonSprite);
            }
            if (BorderSet && !ButtonTextureEnabled) {
                sf::Vector2f BorderVecSize = { BorderSize, BorderSize };
                sf::Vector2f BorderVecPos = { BorderSize / 2, BorderSize / 2 };

                sf::RectangleShape button(size - BorderVecSize);
                button.setPosition(position + BorderVecPos);
                button.setFillColor(ButtonColor);

                sf::RectangleShape border(size);
                border.setPosition(position);
                border.setFillColor(BorderColor);

                (*window).draw(border);
                (*window).draw(button);
            }
            if (BorderSet && ButtonTextureEnabled) {
                ButtonSprite.setTextureRect(sf::IntRect(TextureStart.x, TextureStart.y, size.x - BorderSize, size.y - BorderSize));
                ButtonSprite.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);

                sf::RectangleShape border(normal);
                border.setPosition(position);
                border.setFillColor(BorderColor);


                sf::RectangleShape mask(sf::Vector2f(normal.x - BorderSize, normal.y - BorderSize));
                mask.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);
                mask.setFillColor(sf::Color::Black);
                in = false;

                (*window).draw(border);
                (*window).draw(mask);
                (*window).draw(ButtonSprite);
            }

            /*sf::Vector2i MouseCoords = sf::Mouse::getPosition(*window);
            sf::Vector2u WinSize = (*window).getSize();
            if (MouseCoords.x <= WinSize.x && MouseCoords.y <= WinSize.y && MouseCoords.x >= position.x && MouseCoords.x <= position.x + normal.x && MouseCoords.y >= position.y && MouseCoords.y <= position.x + normal.y && sf::Mouse::isButtonPressed(MouseClickButton)) {
                return true;
            }
            else return false;*/
        }

    };

}


int main()
{
    //базовые настройки.
    bool game = true; // эта штука будет у тебя в меню выставлятся

    AVS::player player;
    AVS::player dealer;

    int all_money = 2000;//все деньги
    short start_size = 52;// размер колоды
    AVS::deck X; // колода откуда берутся карты

    bool first_move = true; // первый ход
    bool chosing_bet = true;// выбор ставки
    bool dealers_move = false; // ход дилера
    bool win = false; // в случае победы
    bool lose = false; // в случае поражения
    bool push = false; // в случае пуша

    //открытие окна
//sf::Style::Fullscreen
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BlackJack");
    window.setFramerateLimit(60);

    //раздел шрифтов
    //шрифт 1 (для заголовков)
    sf::Font font;
    if (!font.loadFromFile("assets/different/LavirePersonalUse.otf"))
    {
        std::cerr << "Error to upload font :(" << std::endl;
        return 404;
    }

    //шрифт 2 (для текста)
    sf::Font fonttext;
    if (!fonttext.loadFromFile("assets/different/MagnetTrial-Light.ttf"))
    {
        std::cerr << "Error to upload fonttext :(" << std::endl;
        return 404;
    }
    
    //раздел фонов игры
    //фон 0 как начальный (красный)
    sf::Texture backgroundTexture0;
    backgroundTexture0.loadFromFile("assets/backgrounds/background1.jpg");
    sf::Sprite background0(backgroundTexture0);
    background0.setScale(
        (float)window.getSize().x / backgroundTexture0.getSize().x,
        (float)window.getSize().y / backgroundTexture0.getSize().y
    );
    background0.setTexture(backgroundTexture0);

    //кнопки
    //взять карту
    sf::RectangleShape getButton(sf::Vector2f(300, 120));
    getButton.setFillColor(sf::Color(255, 255, 255, 128));
    getButton.setOutlineColor(sf::Color::Black);
    getButton.setOutlineThickness(2);
    getButton.setScale(1.0f, 0.9f);
    getButton.setPosition(50, 750);

    sf::Text getText;
    getText.setFont(font);
    getText.setCharacterSize(60);
    getText.setString("get");
    getText.setFillColor(sf::Color::Black);
    getText.setPosition(50+100, 750+20);
    getText.setOutlineThickness(0.2);

    //передать ход
    sf::RectangleShape passButton(sf::Vector2f(300, 120));
    passButton.setFillColor(sf::Color(255, 255, 255, 128));
    passButton.setOutlineColor(sf::Color::Black);
    passButton.setOutlineThickness(2);
    passButton.setScale(1.0f, 0.9f);
    passButton.setPosition(50, 900);

    sf::Text passText;
    passText.setFont(font);
    passText.setCharacterSize(60);
    passText.setString("Enough");
    passText.setFillColor(sf::Color::Black);
    passText.setPosition(50 + 60, 900 + 20);
    passText.setOutlineThickness(0.2);

    //кнопки ставок
    AVS::Button *set_bet_100 = new AVS::Button(sf::Vector2f(500, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_100).setButtonTexture("assets/chips/100.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_100).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_250 = new AVS::Button(sf::Vector2f(810, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_250).setButtonTexture("assets/chips/250.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_250).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_500 = new AVS::Button(sf::Vector2f(1120, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_500).setButtonTexture("assets/chips/500.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_500).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_1000 = new AVS::Button(sf::Vector2f(500, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_1000).setButtonTexture("assets/chips/1000.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_1000).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_2500 = new AVS::Button(sf::Vector2f(810, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_2500).setButtonTexture("assets/chips/2500.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_2500).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_10000 = new AVS::Button(sf::Vector2f(1120, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_10000).setButtonTexture("assets/chips/10000.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_10000).setMouseClickButton(sf::Mouse::Button::Left);

    //тексты значений
    //все деньги
    std::string all_money_str = std::to_string(all_money);

    sf::RectangleShape moneyFrame(sf::Vector2f(240+27*(all_money_str.size()), 60));
    moneyFrame.setFillColor(sf::Color(255, 255, 255, 128));
    moneyFrame.setOutlineColor(sf::Color::Black);
    moneyFrame.setOutlineThickness(2);
    moneyFrame.setScale(1.0f, 0.9f);
    moneyFrame.setPosition(10, 10);

    sf::Text moneyText;
    moneyText.setFont(fonttext);
    moneyText.setCharacterSize(40);
    moneyText.setString("All money: "+all_money_str);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setPosition(20, 10);
    moneyText.setOutlineThickness(0.2);
    
    //текущая ставка
    sf::RectangleShape curr_bet_Frame(sf::Vector2f(115 + 27, 60));
    curr_bet_Frame.setFillColor(sf::Color(255, 255, 255, 128));
    curr_bet_Frame.setOutlineColor(sf::Color::Black);
    curr_bet_Frame.setOutlineThickness(2);
    curr_bet_Frame.setScale(1.0f, 0.9f);
    curr_bet_Frame.setPosition(10, 80);

    sf::Text curr_bet_Text;
    curr_bet_Text.setFont(fonttext);
    curr_bet_Text.setCharacterSize(40);
    curr_bet_Text.setString("bet: 0");
    curr_bet_Text.setFillColor(sf::Color::Black);
    curr_bet_Text.setPosition(20, 80);
    curr_bet_Text.setOutlineThickness(0.2);

    //штука при выборе ставки
    //текущая ставка
    sf::RectangleShape chose_bet_frame(sf::Vector2f(365, 60));
    chose_bet_frame.setFillColor(sf::Color(255, 255, 255, 128));
    chose_bet_frame.setOutlineColor(sf::Color::Black);
    chose_bet_frame.setOutlineThickness(2);
    chose_bet_frame.setScale(1.0f, 0.9f);
    chose_bet_frame.setPosition(500, 130);

    sf::Text chose_bet_text;
    chose_bet_text.setFont(fonttext);
    chose_bet_text.setCharacterSize(40);
    chose_bet_text.setString("Choose your bet!");
    chose_bet_text.setFillColor(sf::Color::Black);
    chose_bet_text.setPosition(510, 130);
    chose_bet_text.setOutlineThickness(0.2);

    while (window.isOpen())
    {
        
        if (game)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                window.clear(sf::Color::White);
                window.draw(background0);
                if (chosing_bet)
                {
                    if(all_money >= 100) (*set_bet_100).draw();
                    if(all_money >= 250) (*set_bet_250).draw();
                    if(all_money >= 500) (*set_bet_500).draw();
                    if (all_money >= 1000) (*set_bet_1000).draw();
                    if (all_money >= 2500) (*set_bet_2500).draw();
                    if (all_money >= 10000) (*set_bet_10000).draw();

                    if ((*set_bet_1000).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 1000) player.set_bet(1000);
                        chosing_bet = false;
                    }
                    if ((*set_bet_2500).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 2500) player.set_bet(2500);
                        chosing_bet = false;
                    }
                    if ((*set_bet_10000).check_mouse_click())
                    {
                        if(chosing_bet && all_money >= 10000) player.set_bet(10000);
                        chosing_bet = false;
                    }
                    if ((*set_bet_100).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 100) player.set_bet(100);
                        chosing_bet = false;
                    }
                    if ((*set_bet_250).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 250) player.set_bet(250);
                        chosing_bet = false;
                    }
                    if ((*set_bet_500).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 500) player.set_bet(500);
                        chosing_bet = false;
                    }
                    if (!chosing_bet)
                    {
                        std::string bet_str = std::to_string(player.get_bet().get_value());
                        curr_bet_Frame.setSize(sf::Vector2f(115 + 27 * (bet_str.size()), 60));
                        curr_bet_Text.setString("bet: " + bet_str);

                        all_money -= player.get_bet().get_value();

                        std::string all_money_str = std::to_string(all_money);
                        moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                        moneyText.setString("All money: " + all_money_str);
                    }
                    window.draw(chose_bet_frame);
                    window.draw(chose_bet_text);
                }
            }
            window.draw(moneyFrame);
            window.draw(moneyText);

            window.draw(curr_bet_Frame);
            window.draw(curr_bet_Text);
        }

        window.display();

    }


    delete set_bet_100;
    delete set_bet_250;
    delete set_bet_500;
    delete set_bet_1000;
    delete set_bet_2500;
    delete set_bet_10000;
    return 0;
}

/*int main()
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
}*/

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