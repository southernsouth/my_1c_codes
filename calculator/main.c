#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


short check_read_number(bool *p_read_number, short *p_start_index, short *p_end_index, char *example, float *numbers_list, short *p_number_index, short *len_operators);
void move_array_float(short *index, float *array, short *len);
void move_array_char(short *index, char *array, short *len);

int main(){
    // get example
    char example[255];
    printf("Input example:\n");
    
    fgets(example, 255, stdin);
    if (example[strlen(example) - 1] == '\n') example[strlen(example) - 1] = '\0';
 
    // get numbers and operators
    int example_length = strlen(example);
  
    short code = 0;
    bool read_number = false;
    short start_index = 0, end_index = 0, number_index = 0, operators_index = 0;

    float numbers_list[example_length]; for (short i = 0 ; i < example_length ; i++) numbers_list[i] = 0;
    char operators_list[example_length];
    for (short i = 0 ; i < example_length ; i++){
        char *pi = &example[i];
        if (*pi == ' ') {
            if (read_number){
                code = check_read_number(&read_number, &start_index, &end_index, example, numbers_list, &number_index, &operators_index);
                if (code == 1){
                    printf("No operator!1");
                    return 1;
                }
            }

            continue;
        } else if (*pi == '0' || *pi == '1' || *pi == '2' || *pi == '3' || *pi == '4' || *pi == '5' || *pi == '6' || *pi == '7' || *pi == '8' || *pi == '9') {
            if (read_number){
                end_index++;
            } else {
                read_number = true;
                start_index = i;
                end_index = i;
            }
        } else if (*pi == '+' || *pi == '-' || *pi == '/' || *pi == '*') {
            if (read_number){
                code = check_read_number(&read_number, &start_index, &end_index, example, numbers_list, &number_index, &operators_index);
                if (code == 1){
                    printf("No operator!2");
                    return 1;
                }
            }
            if ( number_index <= operators_index || i == example_length - 1){
                if (*pi == '/')
                    numbers_list[number_index] = 1;
                number_index++;
            }

            operators_list[operators_index] = *pi;
            operators_index++;

        } else {
            printf("Unacceptable symbol!\n");

            return 1;
        }
    }
    if (read_number){
        code = check_read_number(&read_number, &start_index, &end_index, example, numbers_list, &number_index, &operators_index);
        if (code == 1){
            printf("No operator!3");
            return 1;
        }
    }

    // counting
    for (short i = 0 ; i < operators_index ; i++){
        if (operators_list[i] == '*'){
            numbers_list[i+1] = numbers_list[i] * numbers_list[i+1];
            move_array_float(&i, numbers_list, &number_index);
            move_array_char(&i, operators_list, &operators_index);
            number_index--;
            operators_index--;
            i--;
        } else if (operators_list[i] == '/') {
            numbers_list[i+1] = numbers_list[i] / numbers_list[i+1];
            move_array_float(&i, numbers_list, &number_index);
            move_array_char(&i, operators_list, &operators_index);
            number_index--;
            operators_index--;
            i--;
        }
    }

    for (short i = 0 ; i < operators_index ; i++){
        if (operators_list[i] == '+'){
            numbers_list[i+1] = numbers_list[i] + numbers_list[i+1];
            move_array_float(&i, numbers_list, &number_index);
            move_array_char(&i, operators_list, &operators_index);
            number_index--;
            operators_index--;
            i--;
        } else if (operators_list[i] == '-') {
            numbers_list[i+1] = numbers_list[i] - numbers_list[i+1];
            move_array_float(&i, numbers_list, &number_index);
            move_array_char(&i, operators_list, &operators_index);
            number_index--;
            operators_index--;
            i--;
        }
    }

    printf("Result: %g\n", numbers_list[0]);

    return 0; 
}

short check_read_number(bool *read_number, short *start_index, short *end_index, char *example, float *numbers_list, short *number_index, short *len_operators){
    if (*len_operators < *number_index)
        return 1;

    *read_number = false;

    char number_string[*end_index - *start_index + 1];
    for (short i = 0 ; i < *end_index - *start_index + 1 ; i++)
        number_string[i] = example[*start_index + i];

    numbers_list[*number_index] = atoi(number_string);
    *number_index += 1;

    return 0;
}

void move_array_float(short *index, float *array, short *len){
    for (short i = *index ; i < (*len - 1) ; i++)
        array[i] = array[i + 1];
}

void move_array_char(short *index, char *array, short *len){
    for (short i = *index ; i < (*len - 1) ; i++)
        array[i] = array[i + 1];
}

