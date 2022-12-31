#include "../include/main.h"

void fading(int row, int column)
{
    char *fade_menu_items[] = {
        "fading",                       // Bool
        "no-fading-openclose",          // Bool
        "no-fading-destroyed-argb",     // Bool
        "fade-in-step",                 // Float
        "fade-out-step",                // Float
        "fade-delta",                   // Int
        "back",
    };

    char fading_value[6];
    get_bool("fading", fading_value);

    char no_fading_value[6];
    get_bool("no-fading-openclose", no_fading_value);

    char fading_destroyed_value[6];
    get_bool("no-fading-destroyed-argb", fading_destroyed_value);

    char *bool_storage[]    = {fading_value, no_fading_value, fading_destroyed_value};
    char *bool_values[]     = {"false;", "true;"};
    float float_storage[2]  = {get_float(fade_menu_items[3]), get_float(fade_menu_items[4])};

    int input               = 0;
    int selected_item       = 0;
    int fade_delta          = get_value("fade-delta");
    int menu_size           = sizeof(fade_menu_items) / sizeof(fade_menu_items[0]);

    int menu_row;
    int menu_column;
    int bool_counter;
    int float_counter;
    int updated_menu_row;

    int fading_bool;
    int no_fading_bool;
    int no_fading_destroyed_bool;

    WINDOW *fade_window;
    fade_window = newwin(20, 45, row / 2 - 10, (column - 35) / 2);
    keypad(fade_window, TRUE);

    getmaxyx(fade_window, menu_row, menu_column);

    while(input != 'q')
    {
        get_bool("fading", fading_value);
        get_bool("no-fading-openclose", no_fading_value);
        get_bool("no-fading-destroyed-argb", fading_destroyed_value);

        if (strcmp(fading_value, "true") == 0)
            fading_bool = 1;
        else
            fading_bool = 0;

        if (strcmp(no_fading_value, "true") == 0)
            no_fading_bool = 1;
        else
            no_fading_bool = 0;

        if (strcmp(fading_destroyed_value, "true") == 0)
            no_fading_destroyed_bool = 1;
        else
            no_fading_destroyed_bool = 0;

        bool_counter        = 0;
        float_counter       = 0;
        updated_menu_row    = (menu_row - menu_size) / 2;

        werase(fade_window);
        box(fade_window, '|', '-');

        for(int i = 0; i < menu_size; i++)
        {
            if(selected_item == i)
                wattron(fade_window, A_REVERSE);

            if(i < 3)
            {
                mvwprintw(fade_window, updated_menu_row, 10, "%s: %s", 
                        fade_menu_items[i], bool_storage[bool_counter]);

                bool_counter++;
                updated_menu_row++;
            }
            else if (i > 2 && i < 5)
            {
                mvwprintw(fade_window, updated_menu_row, 10, "%s: %.2f", 
                        fade_menu_items[i], float_storage[float_counter]);

                float_counter++;
                updated_menu_row++;
            }
            else if(i == 5)
            {
                mvwprintw(fade_window, updated_menu_row, 10, "%s: %d", fade_menu_items[i], fade_delta);
                updated_menu_row++;
            }
            else if(i == 6)
            {
                 mvwprintw(fade_window, updated_menu_row, 10, "%s", fade_menu_items[i]);
            }

            wrefresh(fade_window);
            wattroff(fade_window, A_REVERSE);
        }

        input = wgetch(fade_window);

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

        if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 0)
        {
            if (fading_bool == 0)
                fading_bool++;
            else if (fading_bool == 1)
                fading_bool--;

            if (selected_item == 0)
                update_string(bool_values[fading_bool], "fading");
        }

        if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 1)
        {
            if (no_fading_bool== 0)
                no_fading_bool++;
            else if (no_fading_bool == 1)
                no_fading_bool--;

            if (selected_item == 1)
                update_string(bool_values[no_fading_bool], "no-fading-openclose");
        }
     
        if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 2)
        {
            if (no_fading_destroyed_bool == 0)
                no_fading_destroyed_bool++;
            else if (no_fading_destroyed_bool == 1)
                no_fading_destroyed_bool--;

            if (selected_item == 2)
                update_string(bool_values[no_fading_destroyed_bool], "no-fading-destroyed-argb");
        }

        if (input == KEY_RIGHT && selected_item == 3)
            if (float_storage[0] < 1)
                update_value_float(float_storage[0] += .01, "fade-in-step", "fade-in-step");
        if (input == KEY_LEFT && selected_item == 3)
            if (float_storage[0] > 0)
                update_value_float(float_storage[0] -= .01, "fade-in-step", "fade-in-step");

        if (input == KEY_RIGHT && selected_item == 4)
            if (float_storage[1] < 1)
                update_value_float(float_storage[1] += .01, "fade-out-step", "fade-out-step");
        if (input == KEY_LEFT && selected_item == 4)
            if (float_storage[1] > 0)
                update_value_float(float_storage[1] -= .01, "fade-out-step", "fade-out-step");

        if (input == KEY_RIGHT && selected_item == 5)
            update_value(fade_delta += 1, "fade-delta", "fade-delta");
        if (input == KEY_LEFT && selected_item == 5)
            if (fade_delta > 0)
                update_value(fade_delta -= 1, fade_menu_items[5], fade_menu_items[5]);

        if(input == '\n' && selected_item == 6)
            break;
    }
    delwin(fade_window);
    touchwin(stdscr);
}
