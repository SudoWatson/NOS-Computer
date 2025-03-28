// src/main.cpp
#include "CPU.h"
#include <cstdint>
#include <ncurses.h>
#include <iostream>
#include <ostream>

#define runInstruction() cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();

WINDOW* createWindow(int x, int y, int width, int height, const char* title)
{
    WINDOW* win = newwin(width, height, x, y);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, title);
    wrefresh(win);
    return win;
}

void updateRegisterWindow(WINDOW* win, CPU& cpu)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 3, 3, "Test");
    for (int i = 0; i < 16; i++)
    {
        mvwprintw(win, 1 + (i / 2), (i % 2) * 15 + 2, "R%d: 0x%04X", i, cpu.rc->generalRegisters[i]->readValue());
    }
    wrefresh(win);
}

int main() {
    CPU cpu;


    initscr();
    refresh();

    WINDOW* registers = createWindow(0, 0, 200, 50, "Registers");


    runInstruction();
    runInstruction();

    for (int i = 0; i < 100; i++)
    {
        updateRegisterWindow(registers, cpu);
        getch();  // Get character, waits for input
        // Adds
        runInstruction();
        runInstruction();

        // Jump
        runInstruction();
    }

    endwin();
    return 0;
}







