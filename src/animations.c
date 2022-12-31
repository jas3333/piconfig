#include "../include/main.h"

void animations(int row, int column)
{
    char *animations_menu[] = {
        "animations", 									//Bool          
		"animation-clamping", 							//Bool
		"animation-for-open-window", 					//String
		"animation-for-transient-window", 				//String
		"animation-for-workspace-switch-in", 			//String
		"animation-for-workspace-switch-out", 			//String
		"animation-stiffness", 							//Int
		"animation-dampening", 							//int
		"animation-window-mass", 						//Float
        "back",
    };


    char animations_value[6];
    get_bool("animations", animations_value);

	char clamping_value[6];
	get_bool("animation-clamping", clamping_value);

	char open_window[20];
	get_bool("animation-for-open-window", open_window);

	char transient_window[20];
	get_bool("animation-for-transient-window", transient_window);

	char switch_in[20];
	get_bool("animation-for-workspace-switch-in", switch_in);

	char switch_out[20];
	get_bool("animation-for-workspace-switch-out", switch_out);


    int input           = 0;
    int menu_size       = sizeof(animations_menu) / sizeof(animations_menu[0]);
    int bool_counter    = 0;
    int selected_item   = 0;

    char *bool_values[] = {"false;", "true;"};
    char *bool_menu_values[] = {"false", "true"};
	char *animation_values[] = {"zoom", "slide-up", "slide-down"};

	char *string_storage[] = {
		animations_value,
		clamping_value,
		open_window,
		transient_window,
		switch_in,
		switch_out,
	};

    int menu_row;
    int menu_column;
    int updated_menu_row;
    int animations_bool;

	// Selectors
	int clamping_selector;
	int transient_window_selector;
	int switch_in_selector;
	int switch_out_selector;
	int open_window_selector;


    if (strcmp(animations_value, "true") == 0)
        animations_bool = 1;
    else
        animations_bool = 0;

	if (strcmp(clamping_value, "true") == 0)
		clamping_selector = 1;
	else
		clamping_selector = 0;

	if(strcmp(open_window, "zoom") == 0) 
		open_window_selector = 0;
	else if(strcmp(open_window, "slide-up") == 0) 
		open_window_selector = 1;
	else if (strcmp(open_window, "slide-down") == 0) 
		open_window_selector = 2;
	

    WINDOW *animations_window;
    animations_window = newwin(20, 60, row / 2 - 10, (column - 35) / 2);
    keypad(animations_window, TRUE);

    getmaxyx(animations_window, menu_row, menu_column);

    while(input != 'q')
    {
        werase(animations_window);
        box(animations_window, '|', '-');
        updated_menu_row = (menu_row - menu_size) / 2;

        for (int i = 0; i < menu_size; i++)
        {
            if (selected_item == i)
                wattron(animations_window, A_REVERSE);

			if (i < 6)
                mvwprintw(animations_window, updated_menu_row, 10, "%s: %s", animations_menu[i], string_storage[i]);
            
                   
            wrefresh(animations_window);
            wattroff(animations_window, A_REVERSE);
            updated_menu_row++;
        }

        input = wgetch(animations_window);
        
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

        if (selected_item == 0 && (input == KEY_RIGHT || input == KEY_LEFT))
        {
            if (animations_bool == 0)
                animations_bool++;
            else
                animations_bool--;

            update_string(bool_values[animations_bool], "animations");
            strcpy(animations_value, bool_menu_values[animations_bool]);
        }

        if (selected_item == 1 && input == '\n')
            break;
    }

    delwin(animations_window);
    touchwin(stdscr);
}
