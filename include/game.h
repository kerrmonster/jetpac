#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"

/**
 * Game
 *
 * The heart of the application. Created on main() and is
 * responsible for the low level game loop and init/destroy
 * code.
 */
class Game
{
    public:

        static Game* get_instance();
        static void destroy_instance();

        /**
         * starts the simulation. Returns -1 on failure/error
         * or 0 on normal application exit.
         * @param w width of window
         * @param h height of window
         * @param fs fullscreen flag
         * @return -1 on error, 0 on success
         */
        int run(int width=800, int height=600, bool fs=false);


    private:

        Game();
        ~Game();

        void update(float dt);
        void render();
        void handle_input();

        bool init(int w, int h, bool fs);

        static Game* spInstance;
        bool mRunning { false };
        int mWidth;
        int mHeight;
        bool mFullscreen;
        sf::RenderWindow* mWindow;
        sf::RectangleShape mPlayer;
        
};

#endif

