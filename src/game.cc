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
    
    while (mRunning) {

        // TODO: add timing code to loop

        handle_input();

        update(1.0f);

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

void Game::update(float dt) {}

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

    mShape = sf::CircleShape(100.f);
    mShape.setFillColor(sf::Color::Green);

    mRunning = true;
    return true;
}
