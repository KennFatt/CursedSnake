# CursedSnake
A simple [Snake game](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) implementation with C++ and library `ncurses` [[wiki](https://en.wikipedia.org/wiki/Ncurses)].  

## Manual build
### Requirements
You have to install `ncurses` to your computer before manually compile this repository.

**Debian based distro**:
```
sudo apt install libncurses-dev
```
**Arch Linux**:
```
sudo pacman -S ncurses
```
**Mac**:
```
brew install ncurses
```
**Windows**
For Windows users, you can build this project using [Cygwin](https://www.cygwin.com/).
Packages:
```
ncurses
libiconv
```

### Steps
1. Clone this repository
    ```
    git clone https://github.com/KennFatt/CursedSnake.git
    ```
2. Change directory and run `make`
    ```
    cd CursedSnake
    make
    ```
3. Executable file will be generated and located at `out/$FILE_NAME`

## Background
Before we move our project with `ncurses`, we've been trying to render all to the default stream (`stdio`) and that's not possible to **handle keyboard signal simultaneously**.  
Even that's still possible with **threading**, it would be more complicated things to do.

Therefore, we choose and use `ncurses` as our main library for rendering system. This library would work fine with POSIX and need some port for Windows.

## Authors
* Kennan Fattahillah [@KennFatt](https://github.com/KennFatt)
* Arvito Putra [@arvitoputra](https://github.com/arvitoputra)
* Sahla Dzulfika