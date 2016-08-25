#include <SFML/Graphics.hpp>

class Game
{
    public:
                Game();
        void    run();
        bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
    private:
        void    processEvents();
        void    update(sf::Time deltaTime);
        void    render();
        void    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    private:
        sf::RenderWindow mWindow;
        sf::Sprite mPlayer;
        sf::Texture mTexture;
};
int main()
{
    Game game;
    game.run();
}
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "MoveAgain")
    , mPlayer()
    , mTexture()
{
    if (!mTexture.loadFromFile("playGame.bmp"))
    {
        // Handle loading error
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);
}

void Game::run()
{
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            handlePlayerInput(event.key.code, true);
        else if(event.type == sf::Event::KeyReleased)
            handlePlayerInput(event.key.code, false);
        else if(event.type == sf::Event::Closed)
            mWindow.close();

    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::update(sf::Time deltaTime)
{
    float PlayerSpeed = 1.f;
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;
    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}
