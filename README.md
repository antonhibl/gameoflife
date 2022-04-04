# Conway's Game of Life

Written in C++ with either randomized start or a standard game start. compile for c++ using ```g++ life.cpp -o life``` or ```clang life.cpp -o life```, or if you prefer to use JavaScript then run the *life.js* file using ```node life.js```. The program itself can be run just using ```./life``` or optionally you can include a ```--random``` flag to create an even more randomized start to the game. The game will either terminate and tell you how many generations have passed or it will run forever; it can be stopped whenever the user choose using Control+C if needed.

**DISCLAIMER**: This may not work as well on windows due to the fact I utilize ASCII escape patterns to colorize the text in this game, which consequently only works on *nix systems.

**EXAMPLE**:

Running the game with: ```./life --random```, the console looks like so:

<img src="https://media.giphy.com/media/HsUKwZe6Kr4Zd0JgC6/giphy.gif" alt="Game of Life" width="800" height="450" />

