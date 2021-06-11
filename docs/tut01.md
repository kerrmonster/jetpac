# Writing a game - Part 1

## Introduction
This is an introductory tutorial to game programming on Linux using SFML as the layer between our code and the low-level platform API's (such as OpenGL, sound, etc). We won't be
creating the next _Call Of Duty_ or any type of 3D game for that matter - we'll stick to the basics and create a _Pong_ clone, which will give us the footing we need to move on
to bigger projects.

For this tutorial I plan to make use of _Git_ and unlike a lot of other tutorials, actually use the _branch_ command to create a separate branch for the current item we're working on. This isn't only good practice, it could mean the difference between a project that will build correctly, and one that is broken. I'll make use of C++11 were appropriate, and use the _Standard Library_ were possible for containers etc.

## Setting up
We'll need a directory to keep our project in, so from the terminal ```mkdir pong && cd pong``` will create a project folder for us and change to that directory. We'll also need to
init an emtpy Git repository in our folder, so issue the command ```git init```. We also need a ```.gitignore``` file where we can note files and directories that we don't want to be in our repository, so create this file ```touch .gitignore```. Open the file in your favorite text editor and add the following

    .*o
    *~
    pong

This tells Git not to add Object files, Emacs temporary/backup files and the game binary to the repository. Now that thats out of the way, we'll need to create two directories, one for our source code, and one for our headers. From the shell, ```mkdir {include,src}``` will create our two directories ready to hold our code files.

One of the hardest challenges I found coming to Linux/*BSD was the whole _Autotools_ system for building software, and after all these years I still don't understand it. I have managed to cobble together a ```Makefile``` for building projects, but it always involves Google, and copy and paste from one of my other projects. Create the Makefile in the root of the project ```touch Makefile``` and edit it like so:

    CC = g++
    CFLAGS = -Wall -g
    LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

    INCLUDES = -I./include

    SRCS = \
        src/main.cc
    
    OBJS - $(SRCS:.cc=.o)

    MAIN = pong

    .PHONY: depend clean

    all: $(MAIN)
        @echo Pong has been built.

    $(MAIN): $(OBJS)
        $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LDFLAGS)

    .cc.o:
        $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

    clean:
        $(RM) src/.o *~ $(MAIN)

    depend: $(SRCS)
        makedepend $(INCLUDES) $^

    # DO NOT DELETE THIS LINE -- make depend needs it

This is a basic Makefile that will suit our needs, and for now all we'll need to do, is add the names of our source files to the ```SRCS``` variable as we go. To make sure it's working as expected, go ahead and create the file ```src/main.cc`` with the following content:

    #include <stdio.h>

    int main(int argc, char* argv[]) {
        
        printf("Hello World\n");

        return 0;

    }

Save it and from the terminal issue ```make```. If all goes well, you should have a ```pong``` binary in your directory which you can run ```./pong``` and it will output

    ./pong
    Hello World

    $

Thats it. If you got this far and have no errors, then congratulations your build system is ready to build and compile our code. You should now add everything to your git repositiory:

    git add .
    git commit -am"Initial import of build system"

Until the next time...

_Hairymunky_
