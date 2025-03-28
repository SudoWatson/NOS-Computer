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
    mvwprintw(win, 0, 1, "Registers");
    for (int i = 0; i < 16; i++)
    {
        mvwprintw(win, 1 + (i / 2), (i % 2) * 15 + 2, "R%d: 0x%04X", i, cpu.rc->generalRegisters[i]->readValue());
    }
    wrefresh(win);
}

void updateBusWindow(WINDOW* win, CPU& cpu)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Buses & Data");
    mvwprintw(win, 1, 2, "Main: 0x%04X", *cpu.MainBus->GetValue());
    mvwprintw(win, 2, 2, "Left: 0x%04X", *cpu.LhBus->GetValue());
    mvwprintw(win, 3, 2, "Rght: 0x%04X", *cpu.RhBus->GetValue());
    mvwprintw(win, 4, 2, "ALU:  0x%04X", cpu.alu->readValue());
    mvwprintw(win, 5, 2, "MAR:  0x%04X", cpu.rc->specialRegisters[0]->readValue());
    wrefresh(win);
}

void updateExecutionWindow(WINDOW* win, CPU& cpu)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Execution View");
    mvwprintw(win, 1, 2, "PC:   0x%04X", cpu.rc->specialRegisters[1]->readValue());
    mvwprintw(win, 2, 2, "IR:   0x%04X", cpu.ic->readCurrentInstruction());
    mvwprintw(win, 3, 2, "Instruction: UNKNOWN");
    mvwprintw(win, 4, 2, "Step: 0x%01d", cpu.ic->readCurrentStep());
    wrefresh(win);
}

int main() {
    CPU cpu;


    initscr();
    refresh();

    WINDOW* registers = createWindow(0, 0, 15, 60, "Registers");
    WINDOW* bus = createWindow(15, 0, 15, 60, "Buses");
    WINDOW* execution = createWindow(30, 0, 15, 60, "Exectuiton View");



    char ch;
    do
    {
        runInstruction();
        updateRegisterWindow(registers, cpu);
        updateBusWindow(bus, cpu);
        updateExecutionWindow(execution, cpu);
    }
    while ((ch = getch()) != 'q');

    endwin();
    return 0;
}







