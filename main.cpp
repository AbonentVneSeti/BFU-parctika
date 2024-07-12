#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <random>
#include<windows.h>
#include <ctime>


int main()
{

    setlocale(LC_ALL, "Russian");

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

    //раздел орнаментов
    sf::Texture ornament1;
    if (!ornament1.loadFromFile("assets/different/ornament1.png"))
    {
        std::cerr << "Error to upload image ornament1 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureornament1(ornament1);
    textureornament1.setPosition(500, 400);

    sf::Texture ornament2;
    if (!ornament2.loadFromFile("assets/different/ornament2.png"))
    {
        std::cerr << "Error to upload image ornament2 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureornament2(ornament2);
    textureornament2.setPosition(900, 400);

    //раздел девушек :D
    sf::Texture devushka1;
    if (!devushka1.loadFromFile("assets/different/devushka1.png"))
    {
        std::cerr << "Error to upload image devushka1 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturedevushka1(devushka1);
    texturedevushka1.setPosition(100, 430);

    sf::Texture devushka2;
    if (!devushka2.loadFromFile("assets/different/devushka2.png"))
    {
        std::cerr << "Error to upload image devushka2 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturedevushka2(devushka2);
    texturedevushka2.setPosition(1400, 480);


    //раздел фонов игры
    //фон 0 как начальный (красный)
    sf::Texture backgroundTexture0;
    backgroundTexture0.loadFromFile("assets/backgrounds/background1.jpg");
    sf::Sprite background0(backgroundTexture0);
    background0.setScale(
        (float)window.getSize().x / backgroundTexture0.getSize().x,
        (float)window.getSize().y / backgroundTexture0.getSize().y
    );

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

    //раздел музыки
    bool mus0 = true, redmus = false, greenmus = false, bluemus = false;
    sf::Music musicmain;
    if (!musicmain.openFromFile("assets/different/musicred.wav"))
    {
        std::cerr << "Error to upload musicred :(" << std::endl;
        return 404;
    }
    musicmain.setVolume(5);
    if (mus0)
    {
        musicmain.play();
        musicmain.setLoop(true);
    }
    else
    {
        musicmain.pause();
    }

    sf::Music musicred;
    if (!musicred.openFromFile("assets/different/musicred.wav"))
    {
        std::cerr << "Error to upload musicred :(" << std::endl;
        return 404;
    }
    musicred.setVolume(5);
    sf::Music musicgreen;
    if (!musicgreen.openFromFile("assets/different/musicgreen.wav"))
    {
        std::cerr << "Error to upload musicgreen :(" << std::endl;
        return 404;
    }
    musicgreen.setVolume(5);
    sf::Music musicblue;
    if (!musicblue.openFromFile("assets/different/musicblue.wav"))
    {
        std::cerr << "Error to upload musicblue :(" << std::endl;
        return 404;
    }
    musicblue.setVolume(5);
    sf::Texture muteTexture;
    if (!muteTexture.loadFromFile("assets/different/playmusic.png")) {
        std::cerr << "Error to upload image playmusic :(" << std::endl;
        return 404;
    }
    sf::Texture unmuteTexture;
    if (!unmuteTexture.loadFromFile("assets/different/mutemusic.png")) {
        std::cerr << "Error to upload image mutemusic :(" << std::endl;
        return 404;
    }
    sf::Sprite muteButton(muteTexture);
    muteButton.setPosition(1200.f, 350.f);

    //раздел кнопок гм
    //кнопка играть
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color(255, 255, 255, 128));
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(2);
    playButton.setScale(1.0f, 0.9f);
    playButton.setPosition(900, 400);

    //кнопка правил
    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    rulesButton.setFillColor(sf::Color(255, 255, 255, 128));
    rulesButton.setOutlineColor(sf::Color::Black);
    rulesButton.setOutlineThickness(2);
    rulesButton.setScale(1.0f, 0.9f);
    rulesButton.setPosition(900, 450);

    //кнопка настроек
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color(255, 255, 255, 128));
    settingsButton.setOutlineColor(sf::Color::Black);
    settingsButton.setOutlineThickness(2);
    settingsButton.setScale(1.0f, 0.9f);
    settingsButton.setPosition(900, 500);

    //кнопка авторов
    sf::RectangleShape authorsButton(sf::Vector2f(200, 50));
    authorsButton.setFillColor(sf::Color(255, 255, 255, 128));
    authorsButton.setOutlineColor(sf::Color::Black);
    authorsButton.setOutlineThickness(2);
    authorsButton.setScale(1.0f, 0.9f);
    authorsButton.setPosition(900, 550);

    //кнопка выхода
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(255, 255, 255, 128));
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setScale(1.0f, 0.9f);
    exitButton.setPosition(900, 600);
    sf::FloatRect exitButtonRect = exitButton.getGlobalBounds();

    //раздел содержания нажатия кнопок гм
    //текст blackjack
    sf::Text blackjack;
    blackjack.setFont(font);
    blackjack.setCharacterSize(150);
    blackjack.setString("BlackJack");
    blackjack.setFillColor(sf::Color(191, 174, 22, 255));
    blackjack.setPosition(635, 50);
    blackjack.setOutlineThickness(0.2);

    //раздел кнопки играть
    //текст играть
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(40);
    playText.setString("Play");
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(960, 397);
    playText.setOutlineThickness(0.2);

    sf::Texture player;
    if (!player.loadFromFile("assets/different/1player.png"))
    {
        std::cerr << "Error to upload image 1player :(" << std::endl;
        return 404;
    }
    sf::Sprite texture1player(player);
    texture1player.setPosition(750, 400);

    sf::Texture players;
    if (!players.loadFromFile("assets/different/2players.png"))
    {
        std::cerr << "Error to upload image 2players :(" << std::endl;
        return 404;
    }
    sf::Sprite texture2players(players);
    texture2players.setPosition(1050, 400);

    sf::Text oneText;
    oneText.setFont(fonttext);
    oneText.setCharacterSize(30);
    oneText.setString("1 Player");
    oneText.setFillColor(sf::Color::White);
    oneText.setPosition(777, 600);
    oneText.setOutlineThickness(0.4);

    sf::Text twoText;
    twoText.setFont(fonttext);
    twoText.setCharacterSize(30);
    twoText.setString("2 Players");
    twoText.setFillColor(sf::Color::White);
    twoText.setPosition(1080, 600);
    twoText.setOutlineThickness(0.4);

    sf::Text soonText;
    soonText.setFont(fonttext);
    soonText.setCharacterSize(30);
    soonText.setString("Soon!");
    soonText.setFillColor(sf::Color::White);
    soonText.setPosition(1090, 350);
    soonText.setOutlineThickness(0.4);

    //раздел правил
    //текст правил
    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(40);
    rulesText.setString("Rules");
    rulesText.setFillColor(sf::Color::Black);
    rulesText.setPosition(953, 447);
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

        "Blackjack, also known as '21', has a simple essence:\n"
        "the player needs to score 21 points or the closest to that\n"
        "A digit has a value in its hand that exceeds the amount in\n"
        "dealer hand, but in no case exceeding 21. If\n"
        "the participant exceeds 21, he burns out. In the event, if\n"
        "the sum of points is the same for him and the dealer, the\n"
        "party ends in a draw and each side remains at\n"
        "your own scenario. In the case of cards that have\n"
        "numbers, you get as many points as written\n"
        "on the map. If there is no number on the card, then points\n"
        "They are given as follows: Ace - 1 point, Jack - 11 points,\n"
        "The Queen - 12 points, the King - 13 points.\n");

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

    //раздел настроек
    //текст настроек
    sf::Text settingsText;
    settingsText.setFont(font);
    settingsText.setCharacterSize(40);
    settingsText.setString("Settings");
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(931, 498);
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
    valueText.setString("Music volume:");
    valueText.setFillColor(sf::Color::White);
    valueText.setOutlineColor(sf::Color::Black);
    valueText.setPosition(845, 250);
    valueText.setOutlineThickness(0.4);

    //ползунок музыки
    sf::RectangleShape sliderBackground(sf::Vector2f(400.f, 50.f));
    sliderBackground.setFillColor(sf::Color(255, 255, 255, 150));
    sliderBackground.setPosition(776.f, 350.f);
    sf::RectangleShape sliderThumb(sf::Vector2f(50.f, 50.f));
    sliderThumb.setFillColor(sf::Color(186, 34, 33, 255));
    sliderThumb.setPosition(1127.f, 350.f);
    float volume = 1.0f;

    //Theme
    sf::Text themeText;
    themeText.setFont(fonttext);
    themeText.setCharacterSize(40);
    themeText.setString("Themes:");
    themeText.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    themeText.setPosition(900, 450);
    themeText.setOutlineThickness(0.4);
    
    //темы
    sf::Texture minibg1;
    if (!minibg1.loadFromFile("assets/different/minibg1.png"))
    {
        std::cerr << "Error to upload image minibg1 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg1(minibg1);
    textureminibg1.setPosition(800, 550);

    sf::Texture minibg2;
    if (!minibg2.loadFromFile("assets/different/minibg2.png"))
    {
        std::cerr << "Error to upload image minibg2 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg2(minibg2);
    textureminibg2.setPosition(950, 550);

    sf::Texture minibg3;
    if (!minibg3.loadFromFile("assets/different/minibg3.png"))
    {
        std::cerr << "Error to upload image minibg3 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg3(minibg3);
    textureminibg3.setPosition(1100, 550);

    //подписи фонов
    sf::Text theme1Text;
    theme1Text.setFont(fonttext);
    theme1Text.setCharacterSize(30);
    theme1Text.setString("Red");
    theme1Text.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    theme1Text.setPosition(805, 710);
    theme1Text.setOutlineThickness(0.4);

    sf::Text theme2Text;
    theme2Text.setFont(fonttext);
    theme2Text.setCharacterSize(30);
    theme2Text.setString("Green");
    theme2Text.setFillColor(sf::Color::White);
    theme2Text.setOutlineColor(sf::Color::Black);
    theme2Text.setPosition(943, 710);
    theme2Text.setOutlineThickness(0.4);

    sf::Text theme3Text;
    theme3Text.setFont(fonttext);
    theme3Text.setCharacterSize(30);
    theme3Text.setString("Blue");
    theme3Text.setFillColor(sf::Color::White);
    theme3Text.setOutlineColor(sf::Color::Black);
    theme3Text.setPosition(1105, 710);
    theme3Text.setOutlineThickness(0.4);

    //текст авторов
    sf::Text authorsText;
    authorsText.setFont(font);
    authorsText.setCharacterSize(40);
    authorsText.setString("Authors");
    authorsText.setFillColor(sf::Color::Black);
    authorsText.setPosition(928, 548);
    authorsText.setOutlineThickness(0.2);

    //Authors
    sf::Text authorText;
    authorText.setFont(font);
    authorText.setCharacterSize(150);
    authorText.setString("Authors");
    authorText.setFillColor(sf::Color::White);
    authorText.setPosition(1500, 1500);
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
    exitText.setPosition(970, 597);
    exitText.setOutlineThickness(0.2);

    //раздел курсоров
    //курсор 0(начальный)
    sf::Texture cursorTexture0;
    if (!cursorTexture0.loadFromFile("assets/different/cursor1.png")) 
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite0(cursorTexture0);
    cursorSprite0.setOrigin(cursorTexture0.getSize().x / 5.0f, cursorTexture0.getSize().y / 5.0f);
    cursorSprite0.setPosition(100.f, 100.f);
    cursorSprite0.setScale(0.04f, 0.04f);
    window.setMouseCursorVisible(false);

    sf::Texture cursorTexture1;
    if (!cursorTexture1.loadFromFile("assets/different/cursor1.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite1(cursorTexture1);
    cursorSprite1.setOrigin(cursorTexture1.getSize().x / 2.0f, cursorTexture1.getSize().y / 2.0f);
    cursorSprite1.setPosition(100.f, 100.f);
    cursorSprite1.setScale(0.05f, 0.05f);

    sf::Texture cursorTexture2;
    if (!cursorTexture2.loadFromFile("assets/different/cursor2.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite2(cursorTexture2);
    cursorSprite2.setOrigin(cursorTexture2.getSize().x / 2.0f, cursorTexture2.getSize().y / 2.0f);
    cursorSprite2.setPosition(100.f, 100.f);
    cursorSprite2.setScale(0.05f, 0.05f);

    sf::Texture cursorTexture3;
    if (!cursorTexture3.loadFromFile("assets/different/cursor3.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite3(cursorTexture3);
    cursorSprite3.setOrigin(cursorTexture3.getSize().x / 2.0f, cursorTexture3.getSize().y / 2.0f);
    cursorSprite3.setPosition(100.f, 100.f);
    cursorSprite3.setScale(0.05f, 0.05f);

    sf::Sprite* currentCursor = &cursorSprite0;




    //фишки
    //100
    sf::Texture sto;
    if (!sto.loadFromFile("assets/chips/100.png"))
    {
        std::cerr << "Error to upload 100 :(" << std::endl;
        return 404;
    }
    sf::Sprite stotexture(sto);
    //250
    sf::Texture dvesti;
    if (!dvesti.loadFromFile("assets/chips/250.png"))
    {
        std::cerr << "Error to upload 250 :(" << std::endl;
        return 404;
    }
    sf::Sprite dvestitexture(dvesti);
    //500
    sf::Texture pyatsot;
    if (!pyatsot.loadFromFile("assets/chips/500.png"))
    {
        std::cerr << "Error to upload 500 :(" << std::endl;
        return 404;
    }
    sf::Sprite pyatsottexture(pyatsot);
    //1000
    sf::Texture tisyacha;
    if (!tisyacha.loadFromFile("assets/chips/1000.png"))
    {
        std::cerr << "Error to upload 1000 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturetisyacha(tisyacha);
    //2500
    sf::Texture dvepyat;
    if (!dvepyat.loadFromFile("assets/chips/2500.png"))
    {
        std::cerr << "Error to upload 2500 :(" << std::endl;
        return 404;
    }
    sf::Sprite dvepyattexture(dvepyat);
    //10000
    sf::Texture desyatk;
    if (!desyatk.loadFromFile("assets/chips/10000.png"))
    {
        std::cerr << "Error to upload 10000 :(" << std::endl;
        return 404;
    }
    sf::Sprite desyatktexture(desyatk);




    //карты
    //2
    sf::Texture two;
    if (!two.loadFromFile("assets/cards/2.png"))
    {
        std::cerr << "Error to upload 2 :(" << std::endl;
        return 404;
    }
    sf::Sprite twotexture(two);
    //3
    sf::Texture three;
    if (!three.loadFromFile("assets/cards/3.png"))
    {
        std::cerr << "Error to upload 3 :(" << std::endl;
        return 404;
    }
    sf::Sprite threetexture(three);
    //4
    sf::Texture four;
    if (!four.loadFromFile("assets/cards/4.png"))
    {
        std::cerr << "Error to upload 4 :(" << std::endl;
        return 404;
    }
    sf::Sprite fourtexture(four);
    //5
    sf::Texture five;
    if (!five.loadFromFile("assets/cards/5.png"))
    {
        std::cerr << "Error to upload 5 :(" << std::endl;
        return 404;
    }
    sf::Sprite fivetexture(five);
    //6
    sf::Texture six;
    if (!six.loadFromFile("assets/cards/6.png"))
    {
        std::cerr << "Error to upload 6 :(" << std::endl;
        return 404;
    }
    sf::Sprite sixtexture(six);
    //7
    sf::Texture seven;
    if (!seven.loadFromFile("assets/cards/7.png"))
    {
        std::cerr << "Error to upload 7 :(" << std::endl;
        return 404;
    }
    sf::Sprite seventexture(seven);
    //8
    sf::Texture eight;
    if (!eight.loadFromFile("assets/cards/8.png"))
    {
        std::cerr << "Error to upload 8 :(" << std::endl;
        return 404;
    }
    sf::Sprite eighttexture(eight);
    //9
    sf::Texture nine;
    if (!nine.loadFromFile("assets/cards/9.png"))
    {
        std::cerr << "Error to upload 3 :(" << std::endl;
        return 404;
    }
    sf::Sprite ninetexture(nine);
    //10
    sf::Texture ten;
    if (!ten.loadFromFile("assets/cards/10.png"))
    {
        std::cerr << "Error to upload 10 :(" << std::endl;
        return 404;
    }
    sf::Sprite tentexture(ten);
    //J
    sf::Texture J;
    if (!J.loadFromFile("assets/cards/J.png"))
    {
        std::cerr << "Error to upload J :(" << std::endl;
        return 404;
    }
    sf::Sprite Jtexture(J);
    //Q
    sf::Texture Q;
    if (!Q.loadFromFile("assets/cards/Q.png"))
    {
        std::cerr << "Error to upload Q :(" << std::endl;
        return 404;
    }
    sf::Sprite Qtexture(Q);
    //K
    sf::Texture K;
    if (!K.loadFromFile("assets/cards/K.png"))
    {
        std::cerr << "Error to upload K :(" << std::endl;
        return 404;
    }
    sf::Sprite Ktexture(K);
    //A
    sf::Texture A;
    if (!A.loadFromFile("assets/cards/A.png"))
    {
        std::cerr << "Error to upload A :(" << std::endl;
        return 404;
    }
    sf::Sprite Atexture(A);




    //рубашки карт
    //красная
    sf::Texture sr;
    if (!sr.loadFromFile("assets/cards/shirtred.png"))
    {
        std::cerr << "Error to upload shirtred :(" << std::endl;
        return 404;
    }
    sf::Sprite srtexture(sr);
    //зелёная
    sf::Texture sg;
    if (!sg.loadFromFile("assets/cards/shirtgreen.png"))
    {
        std::cerr << "Error to upload shirtgreen :(" << std::endl;
        return 404;
    }
    sf::Sprite sgtexture(sg);
    //синяя
    sf::Texture sb;
    if (!sb.loadFromFile("assets/cards/shirtblue.png"))
    {
        std::cerr << "Error to upload shirtblue :(" << std::endl;
        return 404;
    }
    sf::Sprite sbtexture(sb);




    //раздел вывода изображений
    //здесь компилятор разбирается, что ему нужно задействовать, а что нужно отключить...
    bool mutingmusic = false;
    bool showPlay = false, showRules = false, showSettings = false, showAuthors = false;
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
                if (!showPlay  && !showRules && !showSettings && !showAuthors && exitButtonRect.contains(mousePos.x, mousePos.y))
                {
                    window.close();
                }
                if (!showRules && !showSettings && !showAuthors && playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showPlay = true;
                }
                else if (!showPlay && !showRules && !showSettings && rulesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showRules = true;
                }
                else if (!showPlay && !showRules && !showAuthors && settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showSettings = true;
          
                }
                else if (!showPlay && !showRules && !showSettings && authorsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showAuthors = true;
                }
                if ((showPlay || showRules || showAuthors || showSettings) && backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showPlay = false;
                    showRules = false;
                    showSettings = false;
                    showAuthors = false;
                }

                //раздел настроек
                if (showSettings)
                {
                    //ползунок звука
                    if (!showPlay && !showRules && !showAuthors && sliderBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        float sliderX = mousePos.x - sliderBackground.getPosition().x;
                        volume = sliderX / sliderBackground.getSize().x;
                        sliderThumb.setPosition(sliderBackground.getPosition().x + sliderX - sliderThumb.getSize().x / 2, sliderBackground.getPosition().y);
                        musicred.setVolume(volume * 5);
                        musicblue.setVolume(volume * 5);
                        musicgreen.setVolume(volume * 5);
                        musicmain.setVolume(volume * 5);
                    }
                    //кнопка мута звука для каждой из песен темы
                    if (muteButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        mutingmusic = !mutingmusic;
                        if(mus0)
                        {
                            if (mutingmusic)
                            {
                                musicmain.pause();
                                muteButton.setTexture(unmuteTexture);
                            }
                            else
                            {
                                musicmain.play();
                                muteButton.setTexture(muteTexture);
                            }
                        }
                        else if (redmus)
                        {
                            if (mutingmusic)
                            {
                                musicred.pause();
                                muteButton.setTexture(unmuteTexture);
                            }
                            else
                            {
                                musicred.play();
                                muteButton.setTexture(muteTexture);
                            }
                        }
                        else if (greenmus)
                        {
                            if (mutingmusic)
                            {
                                musicgreen.pause();
                                muteButton.setTexture(unmuteTexture);
                            }
                            else
                            {
                                musicgreen.play();
                                muteButton.setTexture(muteTexture);
                            }
                        }
                        else if (bluemus)
                        {
                            if (mutingmusic)
                            {
                                musicblue.pause();
                                muteButton.setTexture(unmuteTexture);
                            }
                            else
                            {
                                musicblue.play();
                                muteButton.setTexture(muteTexture);
                            }
                        }

                    }

                    //замена фона
                    if (textureminibg1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                       currentCursor = &cursorSprite1;
                       sliderThumb.setFillColor(sf::Color(186, 34, 33, 255));
                       background0.setTexture(backgroundTexture1);
                       background0.setScale(
                       (float)window.getSize().x / backgroundTexture1.getSize().x,
                       (float)window.getSize().y / backgroundTexture1.getSize().y
                            );
                       mus0 = false, redmus = true, greenmus = false, bluemus = false;
                       if (redmus && !greenmus && !bluemus)
                       {
                           musicmain.pause();
                           musicblue.pause();
                           musicgreen.pause();
                           if (!mutingmusic) musicred.play();
                           musicred.setLoop(true);
                       }
                    }
                    else if (textureminibg2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                       currentCursor = &cursorSprite2;
                       sliderThumb.setFillColor(sf::Color(78, 123, 50, 255));
                       background0.setTexture(backgroundTexture2);
                       background0.setScale(
                       (float)window.getSize().x / backgroundTexture2.getSize().x,
                       (float)window.getSize().y / backgroundTexture2.getSize().y
                            );
                       mus0 = false, redmus = false, greenmus = true, bluemus = false;
                       if (!redmus && greenmus && !bluemus)
                       {
                           musicmain.pause();
                           musicred.pause();
                           musicblue.pause();
                           if (!mutingmusic) musicgreen.play();
                           musicgreen.setLoop(true);
                       }
                    }
                    else if (textureminibg3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                       currentCursor = &cursorSprite3;
                       sliderThumb.setFillColor(sf::Color(44, 72, 160, 255));
                       background0.setTexture(backgroundTexture3);
                       background0.setScale(
                       (float)window.getSize().x / backgroundTexture3.getSize().x,
                       (float)window.getSize().y / backgroundTexture3.getSize().y
                            );
                       mus0 = false, redmus = false, greenmus = false, bluemus = true;
                       if (!redmus && !greenmus && bluemus)
                       {
                           musicmain.pause();
                           musicred.pause();
                           musicgreen.pause();
                           if (!mutingmusic) musicblue.play();
                           musicblue.setLoop(true);
                       }
                    }
                }
            }
        }

        //давайте рисовать!
        window.clear(sf::Color::White);
        window.draw(background0);

        //играть
        if (showPlay)
        {
            window.draw(textureramka);
            window.draw(texturedevushka1);
            window.draw(texturedevushka2);
            window.draw(texture1player);
            window.draw(texture2players);
            window.draw(soonText);
            window.draw(twoText);
            window.draw(oneText);
            window.draw(backButton);
            window.draw(backText);
        }

        //настройки
        else if (showSettings)
        {
            window.draw(settingText);
            window.draw(backButton);
            window.draw(backText);
            window.draw(valueText);
            window.draw(muteButton);
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
            window.draw(textureornament1);
            window.draw(textureornament2);
            window.draw(texturedevushka1);
            window.draw(texturedevushka2);
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

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        currentCursor->setPosition(static_cast<sf::Vector2f>(mousePos));
        window.draw(*currentCursor);
        window.display();
    }

    return 0;

}
