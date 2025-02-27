/*
	HERE I PUT SOME TOOLS THAT WILL HELP RUNNING THE GAME ON OTHER OSes LIKE LINUX.
	I DONT USE IT FOR NOW THOUGH.
	NOTE: THIS CODE MAY NOT BE COMPILED OK FOR NOW, BECAUSE I JUST GATHER THE TOOLS I NEED RANDOMLY
	I WILL MODIFY THIS HEADER LATER. FOR NOW IM DESIGNING THE GAME ONLY FOR WIMNDOWS! */

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -		
// FIRST TOOL: getch()
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

std::atomic<bool> keyPressed(false);

#ifdef _WIN32
void keyListener() {
    _getch();
    keyPressed = true;
}
#else
void keyListener() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    keyPressed = true;
}
#endif
// how to use:
/*
int main() {
    std::thread listenerThread(keyListener);

    std::cout << "Press any key to continue..." << std::endl;

    while (!keyPressed) {
        // Your game logic goes here

        // Sleep for a short duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    listenerThread.join(); // Ensure the listener thread has finished

    std::cout << "\nKey pressed. Continue with your game logic." << std::endl;

    return 0;
}*/

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 2ND TOOL: set console size
#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void setConsoleSize(int width, int height) {
#ifdef _WIN32
    COORD coord;
    coord.X = width;
    coord.Y = height;
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = width - 1;
    rect.Bottom = height - 1;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
#elif defined(__linux__)
    std::cout << "\e[8;" << height << ";" << width << "t";
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 3RD TOOL: move cursor function
#include <iostream>

#ifdef _WIN32
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#elif defined(__linux__)
#include <unistd.h>

void gotoxy(int x, int y) {
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

#endif


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -		
// COMMON:
#include <stdlib.h>
#define BEEP_SOUND() std::cout << (char)7
#define COLOR_BG_GRAY_PEN_RED() system("color 74")
#define COLOR_BG_GRAY_PEN_GREEN() system("color 72")
#define COLOR_BG_GRAY_PEN_BLACK() system("color 70")
#define PAUSE_GAME() system("pause")
