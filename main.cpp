#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
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
    setlocale(LC_ALL, "Russian");

    //открытие окна
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BlackJack");
    window.setFramerateLimit(144);

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

    //фоны игры
    sf::Texture backgroundTexture1;
    if (!backgroundTexture1.loadFromFile("assets/backgrounds/background1.jpg"))
    {
        std::cerr << "Error to upload background1 :(" << std::endl;
        return 404;
    }
    sf::Sprite background1(backgroundTexture1);
    background1.setScale(
        (float)window.getSize().x / backgroundTexture1.getSize().x,
        (float)window.getSize().y / backgroundTexture1.getSize().y
    );

    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("assets/backgrounds/background2.jpg"))
    {
        std::cerr << "Error to upload background2 :(" << std::endl;
        return 404;
    }
    sf::Sprite background2(backgroundTexture2);
    background2.setScale(
        (float)window.getSize().x / backgroundTexture2.getSize().x,
        (float)window.getSize().y / backgroundTexture2.getSize().y
    );

    sf::Texture backgroundTexture3;
    if (!backgroundTexture3.loadFromFile("assets/backgrounds/background3.jpg"))
    {
        std::cerr << "Error to upload background3 :(" << std::endl;
        return 404;
    }
    sf::Sprite background3(backgroundTexture3);
    background3.setScale(
        (float)window.getSize().x / backgroundTexture3.getSize().x,
        (float)window.getSize().y / backgroundTexture3.getSize().y
    );

    sf::Music music;
    if (!music.openFromFile("assets/different/mainmusic.wav"))
    {
        std::cerr << "Error to upload music :(" << std::endl;
        return 404;
    }
    music.play();
    music.setLoop(true);

    //кнопка играть
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color(255, 255, 255, 128));
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(2);
    playButton.setScale(1.0f, 0.9f);
    playButton.setPosition(900, 350);

    //кнопка правил
    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    rulesButton.setFillColor(sf::Color(255, 255, 255, 128));
    rulesButton.setOutlineColor(sf::Color::Black);
    rulesButton.setOutlineThickness(2);
    rulesButton.setScale(1.0f, 0.9f);
    rulesButton.setPosition(900, 400);

    //кнопка настроек
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color(255, 255, 255, 128));
    settingsButton.setOutlineColor(sf::Color::Black);
    settingsButton.setOutlineThickness(2);
    settingsButton.setScale(1.0f, 0.9f);
    settingsButton.setPosition(900, 450);

    //кнопка авторов
    sf::RectangleShape authorsButton(sf::Vector2f(200, 50));
    authorsButton.setFillColor(sf::Color(255, 255, 255, 128));
    authorsButton.setOutlineColor(sf::Color::Black);
    authorsButton.setOutlineThickness(2);
    authorsButton.setScale(1.0f, 0.9f);
    authorsButton.setPosition(900, 500);

    //кнопка выхода
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(255, 255, 255, 128));
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setScale(1.0f, 0.9f);
    exitButton.setPosition(900, 550);
    sf::FloatRect exitButtonRect = exitButton.getGlobalBounds();

    //текст blackjack
    sf::Text blackjack;
    blackjack.setFont(font);
    blackjack.setCharacterSize(150);
    blackjack.setString("BlackJack");
    blackjack.setFillColor(sf::Color(191, 174, 22, 255));
    blackjack.setPosition(650, 50);
    blackjack.setOutlineThickness(0.2);

    //текст играть
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(40);
    playText.setString("Play");
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(960, 347);
    playText.setOutlineThickness(0.2);

    //текст правил
    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(40);
    rulesText.setString("Rules");
    rulesText.setFillColor(sf::Color::Black);
    rulesText.setPosition(953, 397);
    rulesText.setOutlineThickness(0.2);

    sf::Text mainrules;
    mainrules.setFont(font);
    mainrules.setCharacterSize(100);
    mainrules.setString("Rules of 'BlackJack'");
    mainrules.setOutlineThickness(2);
    mainrules.setFillColor(sf::Color::White);
    mainrules.setPosition(550, 40);
    mainrules.setOutlineThickness(0.4);

    sf::Text rulesContentText;
    rulesContentText.setFont(fonttext);
    rulesContentText.setCharacterSize(25);
    rulesContentText.setString(

        L"Блэкджек, также известный как '21', имеет простую суть:\n"
        L"игроку нужно набрать 21 очко или ближайшее к этой\n"
        L"цифре значение в руке, превышающее сумму в руке у,\n"
        L"дилера но ни в коем случае не превышающее 21. Если\n"
        L"участник превышает 21, он сгорает. В случае, если\n"
        L"сумма очков одинакова у него и дилера, партия\n"
        L"заканчивается вничью и каждая сторона остается при\n"
        L" своем раскладе. В случае с картами, на которых есть\n"
        L"цифры, вы получаете столько очков, сколько написано\n"
        L"на карте. Если же на карте нет цифры, то очки\n"
        L"даются следующим образом: Туз - 1 очко, Валет - 11 очков,\n"
        L"Дама - 12 очков, Король - 13 очков.\n");

    rulesContentText.setFillColor(sf::Color::White);
    rulesContentText.setOutlineThickness(1);
    rulesContentText.setPosition(640, 240);
    rulesContentText.setOutlineThickness(0.2);

    //рамка правил
    sf::Texture ramka;
    if (!ramka.loadFromFile("assets/different/ramka.png"))
    {
        std::cerr << "Error to upload image ramka :(" << std::endl;
        return 404;
    }
    sf::Sprite textureramka(ramka);
    textureramka.setPosition(500, 150);


    //кнопка назад
    sf::RectangleShape backButton(sf::Vector2f(120, 40));
    backButton.setFillColor(sf::Color(255, 255, 255, 0));
    backButton.setScale(1.0f, 0.9f);
    backButton.setPosition(1270, 770);

    //текст назад
    sf::Text backText;
    backText.setFont(font);
    backText.setCharacterSize(50);
    backText.setString("Back");
    backText.setOutlineThickness(2);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(1250, 740);
    backText.setOutlineThickness(0.2);

    //текст настроек
    sf::Text settingsText;
    settingsText.setFont(font);
    settingsText.setCharacterSize(40);
    settingsText.setString("Settings");
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(929, 447);
    settingsText.setOutlineThickness(0.2);

    //Settings
    sf::Text settingText;
    settingText.setFont(font);
    settingText.setCharacterSize(150);
    settingText.setString("Settings");
    settingText.setFillColor(sf::Color::White);
    settingText.setPosition(700, 50);
    settingText.setOutlineThickness(0.2);

    //громкость музыки
    sf::Text valueText;
    valueText.setFont(fonttext);
    valueText.setCharacterSize(40);
    valueText.setString(L"Громкость музыки:");
    valueText.setFillColor(sf::Color::White);
    valueText.setOutlineColor(sf::Color::Black);
    valueText.setPosition(775, 250);
    valueText.setOutlineThickness(0.4);

    //ползунок музыки
    sf::RectangleShape sliderBackground(sf::Vector2f(400.f, 50.f));
    sliderBackground.setFillColor(sf::Color(255, 255, 255, 150));
    sliderBackground.setPosition(776.f, 350.f);
    sf::RectangleShape sliderThumb(sf::Vector2f(50.f, 50.f));
    sliderThumb.setFillColor(sf::Color(191, 174, 22, 250));
    sliderThumb.setPosition(1127.f, 350.f);
    float volume = 1.0f;

    //Theme
    sf::Text themeText;
    themeText.setFont(fonttext);
    themeText.setCharacterSize(40);
    themeText.setString(L"Темы:");
    themeText.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    themeText.setPosition(925, 450);
    themeText.setOutlineThickness(0.4);
    
    //темы
    sf::Texture minibg1;
    if (!minibg1.loadFromFile("assets/different/minibg1.png"))
    {
        std::cerr << "Error to upload image minibg1 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg1(minibg1);
    textureminibg1.setPosition(800, 530);

    sf::Texture minibg2;
    if (!minibg2.loadFromFile("assets/different/minibg2.png"))
    {
        std::cerr << "Error to upload image minibg2 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg2(minibg2);
    textureminibg2.setPosition(937, 530);

    sf::Texture minibg3;
    if (!minibg3.loadFromFile("assets/different/minibg3.png"))
    {
        std::cerr << "Error to upload image minibg3 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg3(minibg3);
    textureminibg3.setPosition(1077, 530);

    //подписи фонов
    sf::Text theme1Text;
    theme1Text.setFont(fonttext);
    theme1Text.setCharacterSize(20);
    theme1Text.setString(L"Красная");
    theme1Text.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    theme1Text.setPosition(805, 650);
    theme1Text.setOutlineThickness(0.4);

    sf::Text theme2Text;
    theme2Text.setFont(fonttext);
    theme2Text.setCharacterSize(20);
    theme2Text.setString(L"Зелёная");
    theme2Text.setFillColor(sf::Color::White);
    theme2Text.setOutlineColor(sf::Color::Black);
    theme2Text.setPosition(945, 650);
    theme2Text.setOutlineThickness(0.4);

    sf::Text theme3Text;
    theme3Text.setFont(fonttext);
    theme3Text.setCharacterSize(20);
    theme3Text.setString(L"Синяя");
    theme3Text.setFillColor(sf::Color::White);
    theme3Text.setOutlineColor(sf::Color::Black);
    theme3Text.setPosition(1095, 650);
    theme3Text.setOutlineThickness(0.4);

    //текст авторов
    sf::Text authorsText;
    authorsText.setFont(font);
    authorsText.setCharacterSize(40);
    authorsText.setString("Authors");
    authorsText.setFillColor(sf::Color::Black);
    authorsText.setPosition(929, 497);
    authorsText.setOutlineThickness(0.2);

    //Authors
    sf::Text authorText;
    authorText.setFont(font);
    authorText.setCharacterSize(150);
    authorText.setString("Authors");
    authorText.setFillColor(sf::Color::White);
    authorText.setPosition(700, 50);
    authorText.setOutlineThickness(0.2);

    //Kravchuk Svetozar
    sf::Text authorsContentText1;
    authorsContentText1.setFont(fonttext);
    authorsContentText1.setCharacterSize(25);
    authorsContentText1.setString("Kravchuk Svetozar");
    authorsContentText1.setFillColor(sf::Color::White);
    authorsContentText1.setOutlineThickness(1);
    authorsContentText1.setPosition(630, 630);
    authorsContentText1.setOutlineThickness(0.2);

    sf::Texture raccoonka;
    if (!raccoonka.loadFromFile("assets/different/raccoonka.png"))
    {
        std::cerr << "Error to upload image raccoonKa >:(" << std::endl;
        return 404;
    }
    sf::Sprite textureraccoonka(raccoonka);
    textureraccoonka.setPosition(600, 300);

    //Solovyevsky Mark
    sf::Text authorsContentText2;
    authorsContentText2.setFont(fonttext);
    authorsContentText2.setCharacterSize(25);
    authorsContentText2.setString("Solovyevsky Mark");
    authorsContentText2.setFillColor(sf::Color::White);
    authorsContentText2.setOutlineThickness(1);
    authorsContentText2.setPosition(1080, 632);
    authorsContentText2.setOutlineThickness(0.2);

    sf::Texture abonentvneseti;
    if (!abonentvneseti.loadFromFile("assets/different/abonentvneseti.png"))
    {
        std::cerr << "Error to upload image abonentvneseti >:(" << std::endl;
        return 404;
    }
    sf::Sprite textureabonentvneseti(abonentvneseti);
    textureabonentvneseti.setPosition(1050, 300);


    //текст выхода
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(40);
    exitText.setString("Exit");
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(968, 547);
    exitText.setOutlineThickness(0.2);

    //курсор
    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromFile("assets/different/cursor.png")) 
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite(cursorTexture);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 2.0f, cursorTexture.getSize().y / 2.0f);
    cursorSprite.setPosition(100.f, 100.f);
    cursorSprite.setScale(0.05f, 0.05f);
    window.setMouseCursorVisible(false);

    //здесь компилятор разбирается, что ему нужно задействовать, а что нужно отключить...
    bool showRules = false;
    bool showSettings = false;
    bool showAuthors = false;
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
                if (!showRules && !showAuthors && !showSettings && exitButtonRect.contains(mousePos.x, mousePos.y))
                {
                    window.close();
                }
                if (!showSettings && !showAuthors && rulesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showRules = true;
                }
                else if (!showSettings && !showRules && authorsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showAuthors = true;
   
                }
                else if (!showAuthors && !showRules && settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showSettings = true;
                }
                if ((showRules || showAuthors || showSettings) && backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showRules = false;
                    showAuthors = false;
                    showSettings = false;
                }
                if (sliderBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
                {
                    float sliderX = mousePos.x - sliderBackground.getPosition().x;
                    volume = sliderX / sliderBackground.getSize().x;
                    sliderThumb.setPosition(sliderBackground.getPosition().x + sliderX - sliderThumb.getSize().x / 2, sliderBackground.getPosition().y);
                    music.setVolume(volume * 100);
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        cursorSprite.setPosition(static_cast<sf::Vector2f>(mousePos));

        //давайте рисовать!
        window.clear(sf::Color::White);
        window.draw(background1);

        //настройки
        if (showSettings)
        {
            window.draw(settingText);
            window.draw(backButton);
            window.draw(backText);
            window.draw(valueText);
            window.draw(sliderBackground);
            window.draw(sliderThumb);
            window.draw(themeText);
            window.draw(textureminibg1);
            window.draw(textureminibg2);
            window.draw(textureminibg3);
            window.draw(theme1Text);
            window.draw(theme2Text);
            window.draw(theme3Text);
        }
        //авторы
        else if (showAuthors)
        {
            window.draw(authorText);
            window.draw(backButton);
            window.draw(backText);
            window.draw(authorsContentText1);
            window.draw(textureraccoonka);
            window.draw(authorsContentText2);
            window.draw(textureabonentvneseti);
        }
        //правила
        else if (showRules)
        {
            window.draw(textureramka);
            window.draw(mainrules);
            window.draw(rulesContentText);
            window.draw(backButton);
            window.draw(backText);
        }
        //главное меню
        else
        {
            window.draw(blackjack);
            window.draw(playButton);
            window.draw(rulesButton);
            window.draw(settingsButton);
            window.draw(authorsButton);
            window.draw(exitButton);
            window.draw(playText);
            window.draw(rulesText);
            window.draw(settingsText);
            window.draw(authorsText);
            window.draw(exitText);
        }

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
