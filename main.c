#include "header/main.h"

int main()
{
    initscr();
    noecho();
    curs_set(0);

    char *menu_items[] = {
        "Corners",
        "Shadows", 
        "Fading",
        "Opacity",
        "Blur",
        "Animations",
        "Exit",
    };
    
    int row;
    int column;
    int menu_row;
    int menu_column;
    int updated_menu_row;

    int input           = 0;
    int selected_item   = 0;
    int program_active  = 1;
    int menu_size       = sizeof(menu_items) / sizeof(menu_items[0]);

    getmaxyx(stdscr, row, column);

    WINDOW *menu;
    menu = newwin(20, 35, row / 2 - 10, (column - 35) / 2);
    keypad(menu, TRUE);
    getmaxyx(menu, menu_row, menu_column);

    int menu_column_center = ((menu_column - strlen(menu_items[0])) / 2);


    while(program_active)
    {
        box(menu, '|', '-');
        refresh();
        // Resets menu to original position
        updated_menu_row = (menu_row - menu_size) / 2;

        for(int i = 0; i < menu_size; i++)
        {
            if (i == selected_item)
                wattron(menu, A_REVERSE);

            mvwprintw(menu, updated_menu_row, menu_column_center, "%s", menu_items[i]);
            wrefresh(menu);
            wattroff(menu, A_REVERSE);
            updated_menu_row++;
        }

        input = wgetch(menu);

        if (input == 'q')
            program_active = 0;

        if(input == KEY_DOWN || input == 'j')
        {
            if(selected_item == menu_size - 1)
            {
                selected_item = 0;
            }
            else
                selected_item++;
        }
        if (input == KEY_UP || input == 'k')
        {
            if (selected_item == 0)
            {
                selected_item = menu_size - 1;
            }
            else
                selected_item--;
        }

        if (input == '\n' && selected_item == 0)
        {
            werase(menu);
            corners(row, column);
        }
        if (input == '\n' && selected_item == 1)
        {
            werase(menu);
            shadows(row, column);
        }
        if (input == '\n' && selected_item == 2)
        {
            werase(menu);
            fading(row, column);
        }
        if (input == '\n' && selected_item == 3)
        {
            werase(menu);
            opacity(row, column);
        }
        if (input == '\n' && selected_item == 4)
        {
            werase(menu);
            blur(row, column);
        }

        if (input == '\n' && selected_item == 5)
        {
            werase(menu);
            animations(row, column);
        }
        if (input == '\n' && selected_item == 6)
            program_active = 0;
    }

    endwin();
    return 0;
}
   
