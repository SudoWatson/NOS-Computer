// src/main.cpp
#include "CPU.h"
#include <cstdint>
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

void updateRAMWindow(WINDOW* win, CPU& cpu)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "RAM");
    mvwprintw(win, 1, 1, " Addr    Data");
    for (char line = 0; line <= 6; line++)
    {
        const char offset = 3;
        uint16_t marValue = cpu.rc->specialRegisters[0]->readValue();
        uint16_t address = marValue - offset + line;
        if (address == marValue)
        {
            mvwprintw(win, line + 2, 2, "> 0x%04X  0x%04X", address, cpu.ram->values[address]);
        }
        else
        {
            mvwprintw(win, line + 2, 2, "  0x%04X  0x%04X", address, cpu.ram->values[address]);
        }
    }
    wrefresh(win);
}

enum Modes
{
    NORMAL,
    COMMAND,
};

int main() {
    CPU cpu;


    initscr();
    noecho();

    refresh();

    WINDOW* registers = createWindow(0, 0, 15, 40, "Registers");
    WINDOW* bus = createWindow(15, 0, 15, 40, "Buses");
    WINDOW* execution = createWindow(0, 40, 15, 40, "Exectuiton View");
    WINDOW* ram = createWindow(15, 40, 15, 40, "RAM");
    WINDOW* cmd = createWindow(30, 0, 15, 80, "Commands");
    mvwprintw(cmd, 15, 1, "Press 'c' to enter commands, 's' to step through, 'q' to quit");
    wrefresh(cmd);

    char inputChar = 0;
    Modes mode = NORMAL;
    std::string command = "";
    do
    {
        switch (mode)
        {
            case NORMAL:
                switch (inputChar)
                {
                    case 's':
                        cpu.FullCycle();
                        break;
                    case 'r':
                        runInstruction();
                    case 'c':
                        mode = COMMAND;
                        mvwprintw(cmd, 2, 1, ">");
                        wrefresh(cmd);
                        break;
                    default:
                        break;
                }
                break;
            case COMMAND:
                werase(cmd);
                box(cmd, 0, 0);
                switch (inputChar)
                {
                    case '\n':  // Enter
                        if (command.starts_with("HELP"))
                        {
                            if (command.starts_with("HELP LOAD PROGRAM"))
                            {

                                mvwprintw(cmd, 2, 1, "Programs available:");
                                mvwprintw(cmd, 3, 1, "FIBONACCI");
                            }
                            else
                            {
                                mvwprintw(cmd, 2, 1, "Enter 'HELP [PROGRAM]' for help with that command");
                                mvwprintw(cmd, 3, 1, "Commands:");
                                mvwprintw(cmd, 4, 1, "HELP");
                                mvwprintw(cmd, 5, 1, "LOAD PROGRAM");
                            }
                        }
                        else if (command.starts_with("LOAD PROGRAM"))
                        {
                            if (command.starts_with("LOAD PROGRAM FIBONACCI"))
                            {
                                cpu.ram->values[0] = 0xC400;
                                cpu.ram->values[1] = 0x0000;
                                cpu.ram->values[2] = 0xC401;
                                cpu.ram->values[3] = 0x0001;
                                cpu.ram->values[4] = 0x0010;
                                cpu.ram->values[5] = 0x0011;
                                cpu.ram->values[6] = 0x4C00;
                                cpu.ram->values[7] = 0x0004;
                                mvwprintw(cmd, 2, 1, "Loaded 'FIBONACCI' program to ram");
                            }
                            else
                            {
                                mvwprintw(cmd, 2, 1, "Usage: LOAD PROGRAM [NAME]");
                            }
                        }
                        else
                        {
                            mvwprintw(cmd, 2, 1, "Unknown command '%s', type 'HELP' for help", command.c_str());
                        }
                        mode = NORMAL;
                        command = "";
                        break;
                    case 27:  // ESC
                        command = "";
                        mode = NORMAL;
                        break;
                    case 127:  // Backspace
                        if (!command.empty())
                        {
                            command.pop_back();
                        }
                        mvwprintw(cmd, 2, 1, "> %s", command.c_str());
                        break;
                    default:
                        command.push_back(inputChar);
                        mvwprintw(cmd, 2, 1, "> %s", command.c_str());
                        break;
                }
                mvwprintw(cmd, 0, 1, "Commands");
                mvwprintw(cmd, 15, 1, "Press 'c' to enter commands, 's' to step through, 'q' to quit");
                wrefresh(cmd);
                break;
        }
        updateRegisterWindow(registers, cpu);
        updateBusWindow(bus, cpu);
        updateExecutionWindow(execution, cpu);
        updateRAMWindow(ram, cpu);
    }
    while ((inputChar = getch()) != 'q');

    endwin();
    return 0;
}




