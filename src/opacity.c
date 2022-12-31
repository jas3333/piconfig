#include "../include/main.h"
#include <curses.h>

void opacity(int row, int column)
{
    char *opacity_menu[] = {
        "inactive-opacity-override",    //Bool 
        "inactive-opacity",             //Float
        "frame-opacity",                //Float
        "active-opacity",               //Float
        "inactive-dim",                 //Float
        "back",
    };

    char override_value[6];
    get_bool("inactive-opacity-override", override_value);

    char *bool_values[] = {"false;", "true"};

    float float_storage[4] = {
        get_float(opacity_menu[1]),
        get_float(opacity_menu[2]),
        get_float(opacity_menu[3]),
        get_float(opacity_menu[4]),
    };

    int input           = 0;
    int menu_size       = sizeof(opacity_menu) / sizeof(opacity_menu[0]);
    int selected_item   = 0;

    int menu_row;
    int menu_column;
    int float_counter;
    int override_bool;
    int updated_menu_row;

    WINDOW *opacity_window;
    opacity_window = newwin(20, 45, row / 2 - 10, (column - 35) / 2);
    keypad(opacity_window, TRUE);
    getmaxyx(opacity_window, menu_row, menu_column);

    while (input != 'q')
    {
        get_bool(opacity_menu[0], override_value);

        if (strcmp(override_value, "true") == 0)
            override_bool = 1;
        else
            override_bool = 0;

        float_counter       = 0;
        updated_menu_row    = (menu_row - menu_size) / 2;

        werase(opacity_window);
        box(opacity_window, '|', '-');

        for (int i = 0; i < menu_size; i++)
        {
            if (selected_item == i)
                wattron(opacity_window, A_REVERSE);

            if (i == 0)
            {
                mvwprintw(opacity_window, updated_menu_row, 10, "%s: %s", 
                        opacity_menu[i], override_value);

                updated_menu_row++;
            }

            else if (i > 0 && i < 5)
            {
                mvwprintw(opacity_window, updated_menu_row, 10, "%s: %.2f", 
                        opacity_menu[i], float_storage[float_counter]);

                float_counter++;
                updated_menu_row++;
            }

            else if (i == 5)
                mvwprintw(opacity_window, updated_menu_row, 10, "%s", opacity_menu[i]);

            wrefresh(opacity_window);
            wattroff(opacity_window, A_REVERSE);
        }

        input = wgetch(opacity_window);

        if(input == KEY_DOWN)
        {
            if(selected_item == menu_size - 1)
                selected_item = 0;
            else
                selected_item++;
        }
        if(input == KEY_UP)
        {
            if(selected_item == 0)
                selected_item = menu_size - 1;
            else
                selected_item--;
        }

        // Inactive Opacity Override
        if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 0)
        {
            if (override_bool == 0)
                override_bool++;
            else if (override_bool == 1)
                override_bool--;

            update_string(bool_values[override_bool], opacity_menu[0]);
        }

        // Inactive Opacity
        if (input == KEY_RIGHT && selected_item == 1)
            if (float_storage[0] < .95)
                update_value_float(float_storage[0] += .05, opacity_menu[1], opacity_menu[1]);
        if (input == KEY_LEFT && selected_item == 1)
            if (float_storage[0] > 0)
                update_value_float(float_storage[0] -= .05, opacity_menu[1], opacity_menu[1]);

        // Frame Opacity
        if (input == KEY_RIGHT && selected_item == 2)
            if (float_storage[1] < .95)
                update_value_float(float_storage[1] += .05, opacity_menu[2], opacity_menu[2]);
        if (input == KEY_LEFT && selected_item == 2)
            if (float_storage[1] > 0)
                update_value_float(float_storage[1] -= .05, opacity_menu[2], opacity_menu[2]);

        // Active Opacity
        if (input == KEY_RIGHT && selected_item == 3)
            if (float_storage[2] < .95)
                update_value_float(float_storage[2] += .05, opacity_menu[3], opacity_menu[3]);
        if (input == KEY_LEFT && selected_item == 3)
            if (float_storage[2] > 0)
                update_value_float(float_storage[2] -= .05, opacity_menu[3], opacity_menu[3]);

        // Inactive Dim
        if (input == KEY_RIGHT && selected_item == 4)
            if (float_storage[3] < .95)
                update_value_float(float_storage[3] += .05, opacity_menu[4], opacity_menu[4]);
        if (input == KEY_LEFT && selected_item == 4)
            if (float_storage[3] > 0)
                update_value_float(float_storage[3] -= .05, opacity_menu[4], opacity_menu[4]);

        if (input == '\n' && selected_item == 5)
            break;
    }
    delwin(opacity_window);
    touchwin(stdscr);
}
