#include "../include/main.h"

void blur(int row, int column)
{

    char *blur_menu[] = {
        "blur-method",              // String
        "blur-size",                // Float
        "blur-strength",            // Float
        "blur-deviation",           // Float
        "blur-background",          // Bool
        "blur-background-frame",    // Bool
        "blur-background-fixed",    // Bool
        "back",
    };

    char blur_method[20];
    get_bool("blur-method", blur_method);

    char blur_background[6];
    get_bool("blur-background", blur_background);

    char blur_background_frame[6];
    get_bool("blur-background-frame", blur_background_frame);

    char blur_background_fixed[6];
    get_bool("blur-background-fixed", blur_background_fixed);

    char *bool_storage[]        = {blur_background, blur_background_frame, blur_background_fixed};
    char *bool_values[]         = {"false;", "true;"};
    char *menu_bool_values[]    = {"false", "true"};
    char *blur_methods[]        = {"\"gaussian\"", "\"dual_kawase\""};

    float float_storage[4] = {
        get_float(blur_menu[1]), 
        get_float(blur_menu[2]), 
        get_float(blur_menu[3]), 
    };

    int input           = 0;
    int menu_size       = sizeof(blur_menu) / sizeof(blur_menu[0]);
    int bool_counter    = 0;
    int selected_item   = 0;
    int float_counter   = 0;
    

    int menu_row;
    int menu_column;
    int updated_menu_row;

    int background_bool;
    int blur_method_switch;
    int background_frame_bool;
    int background_fixed_bool;

    if (strcmp(blur_method, blur_methods[0]) == 0)
        blur_method_switch = 0;
    else if (strcmp(blur_method, blur_methods[1]) == 0)
        blur_method_switch = 1;

    if (strcmp(blur_background, "true") == 0)
        background_bool = 1;
    else
        background_bool = 0;

    if (strcmp(blur_background_frame, "true") == 0)
        background_frame_bool = 1;
    else
        background_frame_bool = 0;

    if (strcmp(blur_background_fixed, "true") == 0)
        background_fixed_bool = 1;
    else
        background_fixed_bool = 0;

    WINDOW *blur_window;
    blur_window = newwin(20, 45, row / 2 - 10, (column - 35) / 2);
    keypad(blur_window, TRUE);

    getmaxyx(blur_window, menu_row, menu_column);

    while (input != 'q')
    {
        bool_counter        = 0;
        float_counter       = 0;
        updated_menu_row    = (menu_row - menu_size) / 2;

        werase(blur_window);
        box(blur_window, '|', '-');
        
        for (int i = 0; i < menu_size; i++)
        {
            if (selected_item == i)
                wattron(blur_window, A_REVERSE);

            if (i == 0)
            {
                mvwprintw(blur_window, updated_menu_row, 10, "%s: %s", blur_menu[i], blur_methods[blur_method_switch]);
                updated_menu_row++;
            }

            if (i > 0 && i < 4)
            {
                mvwprintw(blur_window, updated_menu_row, 10, "%s: %.2f", blur_menu[i], float_storage[float_counter]);
                updated_menu_row++;
                float_counter++;
            }

            if (i > 3 && i < 7)
            {
                mvwprintw(blur_window, updated_menu_row, 10, "%s: %s", blur_menu[i], bool_storage[bool_counter]);
                updated_menu_row++;
                bool_counter++;
            }

            if (i == 7)
                mvwprintw(blur_window, updated_menu_row, 10, "%s", blur_menu[i]);

            wrefresh(blur_window);
            wattroff(blur_window, A_REVERSE);
        }

        input = wgetch(blur_window);

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


        // Blur Method {gaussian, dual_kawase}
        if ((input == KEY_LEFT || input == KEY_RIGHT) && selected_item == 0)
        {
            if (blur_method_switch == 0)
                blur_method_switch += 1;
            else if (blur_method_switch == 1)
                blur_method_switch -= 1;

            update_string(blur_methods[blur_method_switch], blur_menu[0]);
        }

        // Blur Size - Controls Gaussian
        if (input == KEY_RIGHT && selected_item == 1)
            if (float_storage[0] < 40)
                update_value_float(float_storage[0] += .1, blur_menu[1], blur_menu[1]);
        if (input == KEY_LEFT && selected_item == 1)
            if (float_storage[0] > 0)
                update_value_float(float_storage[0] -= .1, blur_menu[1], blur_menu[1]);

        // Blur Strength - Controls Kawase
        if (input == KEY_RIGHT && selected_item == 2)
            if (float_storage[1] < 10)
                update_value_float(float_storage[1] += .05, blur_menu[2], blur_menu[2]);
         if (input == KEY_LEFT && selected_item == 2)
            if (float_storage[1] > 1)
                update_value_float(float_storage[1] -= .05, blur_menu[2], blur_menu[2]);

         // Blur Deviation
         if (input == KEY_RIGHT && selected_item == 3)
             if (float_storage[2] < 20)
                 update_value_float(float_storage[2] += .5, blur_menu[3], blur_menu[3]);
          if (input == KEY_LEFT && selected_item == 3)
             if (float_storage[2] > 1)
                 update_value_float(float_storage[2] -= .5, blur_menu[3], blur_menu[3]);

          // Blur-background
          if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 4)
          {
              if (background_bool == 0)
                  background_bool += 1;
              else if (background_bool == 1)
                  background_bool -= 1;

              update_string(bool_values[background_bool], blur_menu[4]);
              bool_storage[0] = menu_bool_values[background_bool];

          }
     
          // Blur-background-frame
           if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 5)
           {
               if (background_frame_bool == 0)
                   background_frame_bool += 1;
               else if (background_frame_bool == 1)
                   background_frame_bool -= 1;

               update_string(bool_values[background_frame_bool], blur_menu[5]);
               bool_storage[1] = menu_bool_values[background_frame_bool];
           }

          // Blur-background-fixed
           if ((input == KEY_RIGHT || input == KEY_LEFT) && selected_item == 6)
           {
               if (background_fixed_bool == 0)
                   background_fixed_bool += 1;
               else if (background_fixed_bool == 1)
                   background_fixed_bool -= 1;

               update_string(bool_values[background_fixed_bool], blur_menu[6]);
               bool_storage[2] = menu_bool_values[background_fixed_bool];
           }

        if (input == '\n' && selected_item == 7)
            break;
    }
    delwin(blur_window);
    touchwin(stdscr);
}
