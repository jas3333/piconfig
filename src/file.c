#include "../include/main.h"

int get_value(char search_text[])
{
    int value;
    char string[100];
    char search_string[100];

    FILE *file = fopen("/home/jas/.config/picom/picom.conf", "r");
    while (fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s", search_string);
        if (strcmp(search_string, search_text) == 0)
            sscanf(string, "%s = %d", search_string, &value);
    }
    fclose(file);

    return value;
}



void get_bool (char search_text[], char *pointer)
{
    char string[100];
    char search_string[100];

    FILE *file = fopen("/home/jas/.config/picom/picom.conf", "r");

    while (fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s", search_string);
        if (strcmp(search_string, search_text) == 0)
            sscanf(string, "%s = %s", search_string, pointer);
    }
    fclose(file);

    int pointer_length = length(pointer);
    for (int index = 0; index < pointer_length; index++)
        if (pointer[index] == ';')
            pointer[index] = '\0';
}

void update_value(int new_value, char search_string[], char updated_string[])
{
    char string[100];
    char temp[100];

    char file_path[] = "/home/jas/.config/picom/picom.conf";

    FILE *file = fopen(file_path, "r");
    FILE *temp_file = fopen("replace.tmp", "w");

    while(fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s =", temp);
        if (strcmp(temp, search_string) == 0)
            fprintf(temp_file, "%s = %d;\n", updated_string, new_value);
        else
            fputs(string, temp_file);
    }
    fclose(file);
    fclose(temp_file);

    rename("replace.tmp", file_path);
}

void update_value_float(float new_value, char search_string[], char updated_string[])
{
    char string[100];
    char temp[100];

    char file_path[] = "/home/jas/.config/picom/picom.conf";

    FILE *file = fopen(file_path, "r");
    FILE *temp_file = fopen("replace.tmp", "w");

    while(fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s =", temp);
        if (strcmp(temp, search_string) == 0)
            fprintf(temp_file, "%s = %.2f;\n", updated_string, new_value);
        else
            fputs(string, temp_file);
    }
    fclose(file);
    fclose(temp_file);

    rename("replace.tmp", file_path);
}

void update_string(char updated_string[], char search_string[])
{
    char string[100];
    char temp[100];

    char file_path[] = "/home/jas/.config/picom/picom.conf";

    FILE *file = fopen(file_path, "r");
    FILE *temp_file = fopen("replace.tmp", "w");

    while(fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s =", temp);
        if (strcmp(temp, search_string) == 0)
            fprintf(temp_file, "%s = %s\n", search_string, updated_string);
        else
            fputs(string, temp_file);
    }
    fclose(file);
    fclose(temp_file);
    rename("replace.tmp", file_path);
}

float get_float(char search_text[])
{
    float value;
    char string[100];
    char search_string[100];

    FILE *file = fopen("/home/jas/.config/picom/picom.conf", "r");
    while (fgets(string, 100, file) != NULL)
    {
        sscanf(string, "%s", search_string);
        if (strcmp(search_string, search_text) == 0)
            sscanf(string, "%s = %f", search_string, &value);

    }
    fclose(file);

    return value;
}

int length(char *string)
{
    int counter = 0;

    while (string[counter] != '\0')
    {
        counter++;
    }

    return counter;

}
