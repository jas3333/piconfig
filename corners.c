#include "header/main.h"

void corners(int row, int column)
{
    char *menu_items[] = {
        "corner-radius",
        "back",
    };

    int corner_value    = get_value("corner-radius");
    int menu_size       = sizeof(menu_items) / sizeof(menu_items[0]);
    int selected_item   = 0;
    int input           = 0;

    int menu_row;
    int menu_column;
    int updated_menu_row;

    WINDOW *corner_window;
    corner_window = newwin(20, 35, row / 2 - 10, (column - 35) / 2);
    keypad(corner_window, TRUE);

    getmaxyx(corner_window, menu_row, menu_column);

    while(input != 'q')
    {
        // Reset the row so it doesn't continue to increase
        updated_menu_row = (menu_row - menu_size) / 2;
        werase(corner_window);
        box(corner_window, '|', '-');

    
        for (int i = 0; i < menu_size; i++)
        {
            // Highlight selected item
            if (selected_item == i)
                wattron(corner_window, A_REVERSE);

            if (i == 0)
            {
                mvwprintw(corner_window, updated_menu_row, 10, "%s: %d", menu_items[i], corner_value);
                updated_menu_row++;
            }
            if (i)
            {
                mvwprintw(corner_window, updated_menu_row, 10, "%s", menu_items[i]);
            }
            wrefresh(corner_window);
            wattroff(corner_window, A_REVERSE);
           
        }

        input = wgetch(corner_window);

        if (input == KEY_DOWN)
        {
            if (selected_item == menu_size - 1)
                selected_item = 0;
            else
                selected_item++;
        }
        if (input == KEY_UP)
        {
            if (selected_item == 0)
                selected_item = menu_size - 1;
            else
                selected_item--;
        }

        if ((input == KEY_RIGHT || input == 'l') && selected_item == 0)
            if (corner_value < 20)
                update_value(corner_value += 1, "corner-radius", "corner-radius");

        if ((input == KEY_LEFT || input == 'h') && selected_item == 0)
            if (corner_value > 0)
                update_value(corner_value -= 1, "corner-radius", "corner-radius");

        if (input == '\n' && selected_item == 1)
            break;
    }
    delwin(corner_window);
    touchwin(stdscr);
}
