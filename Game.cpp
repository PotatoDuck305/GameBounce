#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 400), "BOUNCE");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::Vector2f rect_pos(0.f, 150.f);
    sf::Vector2f circle_pos(300, 140);
    sf::RectangleShape rect;
    sf::CircleShape circle;
    sf::Font font;
    sf::SoundBuffer soundBuff;
    sf::Sound sound;
    sf::Music music;
    sf::Text score_txt;
    std::ostringstream sscore;
    auto velocity_x = -2.f;
    auto velocity_y = 3.f;
    auto score = 0;

    music.openFromFile("GameOver.ogg");
    soundBuff.loadFromFile("Bounce.wav");
    sound.setBuffer(soundBuff);
    font.loadFromFile("Into The Void.ttf");
    rect.setSize(sf::Vector2f(20.f,65.f));
    rect.setPosition(rect_pos);
    circle.setRadius(10.5);
    circle.setPosition(circle_pos);
    sscore << "Score:" << score;
    score_txt.setPosition({ 170.f,0.f });
    score_txt.setFont(font);
    score_txt.setString(sscore.str());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                //Player Movement
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    if (rect_pos.y < 50)
                        rect_pos.y -= 0;
                    else rect_pos.y -= 30;
                    break;
                case sf::Keyboard::S:
                    if (rect_pos.y + 65>400)
                        rect_pos.y += 0;
                    else rect_pos.y += 30;
                    break;
                default:
                    break;
                }
            }
        }
        rect.setPosition(rect_pos);
        circle_pos.x += velocity_x;
        circle_pos.y += velocity_y;
        //physics
        if (circle_pos.y+10.5> 400||circle_pos.y+10.5<50)
            velocity_y *= -1;
        if (circle_pos.x>500)
            velocity_x *= -1;
        if (circle_pos.x==rect_pos.x+20)
            if (circle_pos.y + 10.5 >= rect_pos.y && circle_pos.y + 10.5 <= rect_pos.y + 65) {
                velocity_x *= -1.f;
                ++score;
                sscore.str("");
                sscore << "Score: " << score;
                score_txt.setString(sscore.str());
                sound.play();
            }
        //game over
        if (circle_pos.x == 0)
            music.play();

        circle.setPosition(circle_pos);
        window.clear();
        window.draw(score_txt);
        window.draw(rect);
        window.draw(circle);
        window.display();
    }
}

