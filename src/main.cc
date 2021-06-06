#include "game.h"


int main(int argc, char* argv[]){
    
    // run app with default window settings
    int ret = Game::get_instance()->run();

    // finished
    Game::destroy_instance();

    return ret;
}
