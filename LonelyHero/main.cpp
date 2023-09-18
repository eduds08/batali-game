#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    constexpr float gravity = 9.81f;
    sf::RenderWindow window{ sf::VideoMode(600, 600), "Lonely Hero" };

    sf::Event event{};

    sf::Texture texture{};
    texture.loadFromFile("./_Idle.png");

    sf::Texture runningTexture{};
    runningTexture.loadFromFile("./_Run.png");

    sf::Texture dirtTexture{};
    dirtTexture.loadFromFile("./dirt.png");

    sf::Sprite sprite{};

    sf::Sprite dirt{ dirtTexture };


    std::vector<sf::Sprite> dirts{};
    std::vector<sf::FloatRect> dirtsBound{};

    for (int i = 0; i < 600; i += 10)
    {
        dirt.setPosition(float(i), 540.f);
        dirts.push_back(dirt);
        dirtsBound.push_back(dirt.getGlobalBounds());
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect{ 0, 0, 120, 80 });
    sprite.setPosition(300.f, 0.f);

    sprite.setOrigin(120.f / 2.f, 80.f / 2.f);

    sprite.setScale(2.f, 2.f);

    bool facingRight = true;

    std::vector<sf::IntRect> rects{};

    constexpr int x = 120;
    constexpr int y = 80;

    rects.push_back(sf::IntRect{ 0, 0, x, y });
    rects.push_back(sf::IntRect{ x, 0, x, y });
    rects.push_back(sf::IntRect{ x*2, 0, x, y });
    rects.push_back(sf::IntRect{ x*3, 0, x, y });
    rects.push_back(sf::IntRect{ x*4, 0, x, y });
    rects.push_back(sf::IntRect{ x*5, 0, x, y });
    rects.push_back(sf::IntRect{ x*6, 0, x, y });
    rects.push_back(sf::IntRect{ x*7, 0, x, y });
    rects.push_back(sf::IntRect{ x*8, 0, x, y });
    rects.push_back(sf::IntRect{ x*9, 0, x, y });

    int textureCount = 0;

    sf::Clock clock{};

    bool running = true;

    std::vector<sf::Sprite>::iterator it;
    std::vector<sf::FloatRect>::iterator it2;

    bool fullscreen = false;

    sf::FloatRect playerBound{};

    bool onFloor = false;

    while (window.isOpen())
    {
        playerBound = sprite.getGlobalBounds();

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T))
        {
            if (!fullscreen)
            {
                fullscreen = true;
                window.create(sf::VideoMode::getDesktopMode(), "Lonely Hero", sf::Style::Fullscreen);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
        {
            if (fullscreen)
                {
                    fullscreen = false;
                    window.create(sf::VideoMode(600, 600), "Lonely Hero");
                }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
        {
            running = true;
            facingRight = false;
            sprite.move(-0.1f, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
        {
            running = true;
            facingRight = true;
            sprite.move(0.1f, 0.f);
        }
        else
        {
            running = false;
        }

        if (facingRight)
        {
            sprite.setScale(2.f, 2.f);
        }
        else
        {
            sprite.setScale(-2.f, 2.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && onFloor == true)
        {
            sprite.move(0.f, -sqrtf(2.f * 981.f * 4.f));
        }

        if (running)
        {
            if (sprite.getTexture() == &texture)
            {
                textureCount = 0;
            }
            sprite.setTexture(runningTexture);
        }
        else
        {
            if (sprite.getTexture() == &runningTexture)
            {
                textureCount = 0;
            }
            sprite.setTexture(texture);
        }

        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() > 0.15f)
        {
            if (textureCount == 10)
                textureCount = 0;
            sprite.setTextureRect(rects[textureCount]);
            textureCount++;
            clock.restart();
        }

        onFloor = false;
        for (it2 = dirtsBound.begin(); it2 != dirtsBound.end(); it2++)
        {
            if (playerBound.intersects(*it2))
            {
                onFloor = true;
            }
        }

        if (!onFloor)
        {
            sprite.move(0.f, gravity * 0.07f);
        }
        

        window.clear(sf::Color(255, 209, 220));
        
        window.draw(sprite);
        
        for (it = dirts.begin(); it != dirts.end(); it++)
        {
            window.draw(*it);
        }

        window.display();
    }

    return 0;
}