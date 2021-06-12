#include "game.h"

Game* Game::spInstance = nullptr;

float ballX = 8.f;
float ballY = 8.f;

Game* Game::get_instance() {
    if (spInstance == nullptr)
        spInstance = new Game();

    return spInstance;
}


void Game::destroy_instance() {
    if (spInstance) {
        delete spInstance;
        spInstance = nullptr;
    }
}


Game::Game() {

    mWindow = nullptr;
}

Game::~Game() {

    if (mWindow)
        delete mWindow;

    mWindow = nullptr;
}


int Game::run(int width, int height, bool fs)
{
    // init systems
    if (!init(width, height, fs))
    {
        return -1;
    }

    // setup clock for timing
    float t=0.0f;
    float dt = 1.f/60.f;
    sf::Clock clock;

    sf::Time currentTime = clock.restart();

    while (mRunning) {
   
        handle_input();  
  
        //sf::Time newTime = clock.restart();
        //float frameTime = newTime.asSeconds() - currentTime.asSeconds();
        //currentTime = newTime;

        //while (frameTime > 0.0f) {
           // float deltaTime = std::min(frameTime, dt);
        update(0.016);
           // frameTime -= deltaTime;
           // t += deltaTime;
        //}

        render();
    }

    // all done, return success to main
    return 0;
}


void Game::render() {

    // clear window
    mWindow->clear();

    // Draw stuff here
    mWindow->draw(mPlayer);

    mWindow->draw(mBall);

    // Flip buffers
    mWindow->display();
}

void Game::update(float dt) {

    // ball physics
    
    mBall.move(ballX, ballY);
    sf::Vector2f ballPos = mBall.getPosition();

    if (ballPos.x < 0) {
        ballPos.x = 0;
        ballX = -ballX;    
    }

    if (ballPos.x > mWindow->getSize().x) {
        ballPos.x = mWindow->getSize().x - mBall.getSize().x;
        ballX = -ballX;    
    }

    if (ballPos.y < 0) {
        ballPos.y = 0;
        ballY = -ballY;    
    }

    if (ballPos.y > mWindow->getSize().y) {
        ballPos.y = mWindow->getSize().y - mBall.getSize().y;
        ballY = -ballY;    
    }

    mBall.setPosition(ballPos);
    
    // collision detection
    if (ballPos.x < mPlayer.getPosition().x + mPlayer.getSize().x &&
        ballPos.x + mBall.getSize().x > mPlayer.getPosition().x &&
        ballPos.y < mPlayer.getPosition().y + mPlayer.getSize().y &&
        ballPos.y + mBall.getSize().y > mPlayer.getPosition().y) 
    {
            // collision
        ballX = -ballX;
    }
}

void Game::handle_input() {

    sf::Event event;

    while (mWindow->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            mWindow->close();
            mRunning = false;
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        mPlayer.move(sf::Vector2f(0,-5));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        mPlayer.move(sf::Vector2f(0,5));
    }

    sf::Vector2f pos = mPlayer.getPosition();

    if (pos.y < 0) {
        mPlayer.setPosition(sf::Vector2f(25, 0));
    }

    float maxY = (mWindow->getSize().y - mPlayer.getSize().y);

    if (pos.y > maxY) {
        mPlayer.setPosition(sf::Vector2f(25, maxY));
    }    
}

bool Game::init(int w, int h, bool fs) {

    mWindow = new sf::RenderWindow(sf::VideoMode(w, h), "GK Engine");
    mWindow->setVerticalSyncEnabled(true);

    // Player init
    mPlayer = sf::RectangleShape(sf::Vector2f(10,50));
    mPlayer.setFillColor(sf::Color::Green);
    mPlayer.setPosition(sf::Vector2f(25.f, (float)(mWindow->getSize().y-mPlayer.getSize().y)/2));

    // Ball init
    mBall = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
    mBall.setFillColor(sf::Color::Yellow);
    mBall.setPosition(sf::Vector2f((float)mWindow->getSize().x/2, (float)mWindow->getSize().y/2));

    mRunning = true;
    return true;
}
