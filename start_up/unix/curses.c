/*!
 * \file	curses.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-19 14:35:30
 */
#include<unistd.h>

#include<curses.h>

int main(int argc, char* argv[])
{
    initscr();

    box(stdscr, ACS_VLINE, ACS_HLINE); /*draw a box*/
    move(LINES/2, COLS/2); /*move the cursor to the center*/
    waddstr(stdscr, "Hello, world!");
    refresh();
    getch();

    endwin();
    return 0;
}

