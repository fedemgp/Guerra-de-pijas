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

create a build folder, then in that folder open a console and type:

	cmake ..
	make
	sudo make install

## Run

Once installed, the server can be executed with the command `worms_server PORT` and the client with `worms_client`. The levels editor can be opened by typing `worms_editor`.


### Buttons
 * Left, Right arrows moves the worm across the map.
 * Up and Down arrows increases or decreases aim angle.
 * Space bar: start shoot.
 * Enter: jump.
 * BackSpace: back flip .
 * Numbers 1 to 5 sets timeout of grenades before exploding.
 * F1 to F10 selects weapons, according to the armory help inside the game.
 * Use the mouse to pan the camera.

## FeatureList

* Download sublime text
* [Install Package control](https://packagecontrol.io/installation#st2)
* Go to Preference -> Package Control -> Install Package -> plainTasks
* For a tutorial of plain tasks, visit Preference -> Package Settings -> Plain tasks -> tutorials

## Useful links

[SDL tutorial](http://lazyfoo.net/tutorials/SDL/)

[Box2D: Moving at constant speed](http://www.iforce2d.net/b2dtut/constant-speed)

[YAML Tutorial](https://github.com/jbeder/yaml-cpp/wiki/Tutorial)

[YAML Emitting](https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML)
