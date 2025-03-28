// src/main.cpp
#include "CPU.h"
#include <ncurses.h>
#include <string>

#define runInstruction() cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();

WINDOW* createWindow(int x, int y, int width, int height, const char* title)
{
    WINDOW* win = newwin(width, height, x, y);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", title);  // TODO: I get a warning if I don't format this, same with the strings below. Not sure why, look into it
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
    mvwprintw(win, 1, 2, "Main: %s", cpu.MainBus->GetValue() != nullptr ? std::format("0x{:04X}", *cpu.MainBus->GetValue()).c_str() : "0x____");
    mvwprintw(win, 2, 2, "Left: %s", cpu.LhBus->GetValue() != nullptr ? std::format("0x{:04X}", *cpu.LhBus->GetValue()).c_str() : "0x____");
    mvwprintw(win, 3, 2, "Rght: %s", cpu.RhBus->GetValue() != nullptr ? std::format("0x{:04X}", *cpu.RhBus->GetValue()).c_str() : "0x____");
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
    mvwprintw(win, 2, 2, "RC:   0x%04X", cpu.rc->readValue());
    mvwprintw(win, 3, 2, "IR:   0x%04X", cpu.ic->readCurrentInstruction());
    mvwprintw(win, 4, 2, "Instruction: UNKNOWN");
    mvwprintw(win, 5, 2, "Step: 0x%01d", cpu.ic->readCurrentStep());
    wrefresh(win);
}

int main() {
    CPU cpu;


    initscr();
    refresh();

    WINDOW* registers = createWindow(0, 0, 15, 40, "Registers");
    WINDOW* bus = createWindow(15, 0, 15, 40, "Buses");
    WINDOW* execution = createWindow(0, 40, 15, 40, "Exectuiton View");



    char ch = 0;
    do
    {
        switch (ch)
        {
            case 's':
                cpu.FullCycle();
                break;
            case 'r':
                runInstruction();
                break;
            default:
                break;
        }
        updateRegisterWindow(registers, cpu);
        updateBusWindow(bus, cpu);
        updateExecutionWindow(execution, cpu);
    }
    while ((ch = getch()) != 'q');

    endwin();
    return 0;
}




