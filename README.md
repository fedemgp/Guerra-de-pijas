## Build Dependencies

### SDL2

SDL2 handles the GUI on the client application.

    sudo apt-get install libsdl2-dev


### SDL2 image

SDL2-image is a library that allows to load (among others) PNG images using SDL2.

    sudo apt-get install libsdl2-image-dev


### SDL ttf

A library to render text from SDL.

    sudo apt-get install libsdl2-ttf-dev

### SDL mixer

A library to use sound from SDL.

    sudo apt-get install libsdl2-mixer-dev


## Qt-5 (editor)

    sudo apt-get install qt5-default qtdeclarative5-dev qtcreator


### clang-format (optional)

`clang-format` is used to format all the source code files. It requires `clang-format` installed:

    sudo apt-get install clang-format


## Build instructions

Run `make help` to get more information about different build options.
### Alternative
create a folder build, then in that folder open a console and type:
	
	cmake ..
	make

It will generate the client and server executables and it will copy the assets folder in there so the user can execute the game with no problem.

## Run
It is necessary to open two clients to start the game.

## FeatureList

* Download sublime text
* [Install Package control](https://packagecontrol.io/installation#st2)
* Go to Preference -> Package Control -> Install Package -> plainTasks
* For a tutorial of plain tasks, visit Preference -> Package Settings -> Plain tasks -> tutorials

## Useful links

[SDL tutorial](http://lazyfoo.net/tutorials/SDL/)

[Box2D: Moving at constant speed](http://www.iforce2d.net/b2dtut/constant-speed)
