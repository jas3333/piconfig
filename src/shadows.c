#include "../include/main.h"

void shadows(int row, int column)
{
    char *menu_items[] = {
        "shadow",               // Bool
        "shadow-radius",        // Int
        "shadow-offset-x",      // Int
        "shadow-offset-y",      // Int
        "shadow-opacity",       // Float
        "back",
    };

    char shadow[6];
    get_bool("shadow", shadow);

    int shadow_bool;

    if (strcmp(shadow, "true") == 0)
        shadow_bool = 1;
    else
        shadow_bool = 0;

    char *bool_values[] = {"false;", "true;"};

    int int_values[3] = {
        get_value("shadow-radius"),
        get_value("shadow-offset-x"),
        get_value("shadow-offset-y"),
    };

    int menu_row;
    int menu_column;    
    int updated_menu_row;

    int int_values_counter      = 0;
    int menu_size               = sizeof(menu_items) / sizeof(menu_items[0]);
    int selected_item           = 0;
    int input                   = 0;
    float shadow_opacity        = get_float("shadow-opacity");


    WINDOW *shadows_window;
    shadows_window = newwin(20, 35, row / 2 - 10, (column - 35) / 2);
    keypad(shadows_window, TRUE);

    getmaxyx(shadows_window, menu_row, menu_column);

    while (input != 'q')
    {
       get_bool("shadow", shadow);

       updated_menu_row = (menu_row - menu_size) / 2;
       int_values_counter = 0;
       werase(shadows_window);
       box(shadows_window, '|', '-');

       for (int i = 0; i < menu_size; i++)
       {
           if (selected_item == i)
               wattron(shadows_window, A_REVERSE);
           if (i == 0)
           {
               mvwprintw(shadows_window, updated_menu_row, 10, "%s: %s", menu_items[i], shadow);
               updated_menu_row++;
           }
           else if(i > 0 && i < 4)
           {
               mvwprintw(shadows_window, updated_menu_row, 10, "%s: %d", menu_items[i], int_values[int_values_counter]);
               int_values_counter++;
               updated_menu_row++;
           }
           else if(i == 4)
           {
               mvwprintw(shadows_window, updated_menu_row, 10, "%s: %.2f", menu_items[i], shadow_opacity);
               updated_menu_row++;
           }
           else if (i == 5)
           {
               mvwprintw(shadows_window, updated_menu_row, 10, "%s", menu_items[i]);
               updated_menu_row++;
           }

           wrefresh(shadows_window);
           wattroff(shadows_window, A_REVERSE);
       }

       input = wgetch(shadows_window);

       if (input == KEY_DOWN || input == 'j')
       {
           if (selected_item == menu_size - 1)
               selected_item = 0;
           else
               selected_item++;
       }
       if (input == KEY_UP || input == 'k')
       {
           if (selected_item == 0)
               selected_item = menu_size - 1;
           else
               selected_item--;
       }

       if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 0)
       {
           if (shadow_bool == 0)
               shadow_bool++;
           else if(shadow_bool == 1)
               shadow_bool--;

           update_string(bool_values[shadow_bool], "shadow");
       }
      
       if (input == KEY_RIGHT && selected_item == 1)
       {
           update_value(int_values[0] += 1, "shadow-radius", "shadow-radius");
       }
       if (input == KEY_LEFT && selected_item == 1)
       {
           update_value(int_values[0] -= 1, "shadow-radius", "shadow-radius");
       }
       if (input == KEY_RIGHT && selected_item == 2)
       {
           update_value(int_values[1] += 1, "shadow-offset-x", "shadow-offset-x");
       }
       if (input == KEY_LEFT && selected_item == 2)
       {
           update_value(int_values[1] -= 1, "shadow-offset-x", "shadow-offset-x");
       }
       if (input == KEY_RIGHT && selected_item == 3)
       {
           update_value(int_values[2] += 1, "shadow-offset-y", "shadow-offset-y");
       }
       if (input == KEY_LEFT && selected_item == 3)
       {
           update_value(int_values[2] -= 1, "shadow-offset-y", "shadow-offset-y");
       }
       if (input == KEY_RIGHT && selected_item == 4)
       {
           if (shadow_opacity < 1)
               update_value_float(shadow_opacity += .05, "shadow-opacity", "shadow-opacity");
       }
       if (input == KEY_LEFT && selected_item == 4)
       {
           if (shadow_opacity > 0)
               update_value_float(shadow_opacity -= .05, "shadow-opacity", "shadow-opacity");
       }

       if (input == '\n' && selected_item == 5)
           break;
    }

    // Delete the window to get back to the main menu
    delwin(shadows_window);
    touchwin(stdscr);
}
