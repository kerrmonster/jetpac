#include "game.h"

Game* Game::spInstance = nullptr;

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
  
        sf::Time newTime = clock.restart();
        float frameTime = newTime.asSeconds() - currentTime.asSeconds();
        currentTime = newTime;

        while (frameTime > 0.0f) {
            float deltaTime = std::min(frameTime, dt);
            update(deltaTime);
            frameTime -= deltaTime;
            t += deltaTime;
        }

        render();
    }

    // all done, return success to main
    return 0;
}


void Game::render() {

    // clear window
    mWindow->clear();

    // Draw stuff here
    mWindow->draw(mShape);

    // Flip buffers
    mWindow->display();
}

void Game::update(float dt) {

    printf("\e[1A\e[K%.4f\n", dt);

}

void Game::handle_input() {

    sf::Event event;

    while (mWindow->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            mWindow->close();
            mRunning = false;
        }
    }
}

bool Game::init(int w, int h, bool fs) {

    mWindow = new sf::RenderWindow(sf::VideoMode(w, h), "JetPac");
    mWindow->setVerticalSyncEnabled(true);
    //mWindow->setFramerateLimit(60);

    mShape = sf::CircleShape(100.f);
    mShape.setFillColor(sf::Color::Green);

    mRunning = true;
    return true;
}
