#include <stdlib.h>
#include <ncurses.h>
#include <string.h>



// Prototypes

int get_value(char search_text[]);
void get_bool(char search_text[], char *pointer);
void update_value(int new_value, char search_string[], char updated_string[]);
void update_value_float(float new_value, char search_string[], char updated_string[]);
void update_string(char update_string[], char search_string[]);
float get_float(char search_text[]);
void shadows(int row, int column);
void corners(int row, int column);
void fading(int row, int column);
void opacity(int row, int column);
void blur(int row, int column);
void animations(int row, int column);
int length(char *string);

