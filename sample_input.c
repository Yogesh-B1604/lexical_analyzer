/*
 * sample_input.c
 * This file is the TEST INPUT for our lexical analyzer.
 * It contains various C constructs to test token detection.
 */

/* Standard library includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Custom header */
#include "myheader.h"

/* Preprocessor directives */
#define MAX_SIZE 100
#define PI 3.14159
#define SQUARE(x) ((x) * (x))

/* Structure definition */
struct Student {
    int   roll_number;
    float marks;
    char  name[50];
};

/* Enum definition */
enum Color {
    RED,
    GREEN,
    BLUE
};

/* Global variable */
int global_count = 0;

/* Function prototype */
int add(int a, int b);
float calculate_area(float radius);
void print_message(char* msg);

/* -----------------------------------------------
 * MAIN FUNCTION
 * Entry point of the program
 * ----------------------------------------------- */
int main(int argc, char* argv[]) {

    /* Variable declarations */
    int    number    = 42;
    float  pi_value  = 3.14;
    char   grade     = 'A';
    char   name[]    = "Alice";
    int    array[10];
    int*   pointer   = NULL;

    /* Arithmetic operators */
    int sum        = 10 + 20;
    int difference = 50 - 15;
    int product    = 6 * 7;
    int quotient   = 100 / 4;
    int remainder  = 17 % 5;

    /* Relational and logical operators */
    int is_equal    = (sum == 30);
    int is_not_equal = (number != 0);
    int is_less     = (difference <= 40);
    int is_greater  = (product >= 42);
    int logical_and = (is_equal && is_not_equal);
    int logical_or  = (is_less  || is_greater);

    /* Bitwise operators */
    int bit_and = 12 & 10;
    int bit_or  = 12 | 10;
    int bit_xor = 12 ^ 10;
    int bit_not = ~12;
    int left_shift  = 1 << 3;
    int right_shift = 16 >> 2;

    /* Assignment operators */
    int x = 5;
    x += 3;
    x -= 1;
    x *= 2;
    x /= 4;
    x %= 3;

    /* Increment and Decrement */
    int counter = 0;
    counter++;
    counter--;
    ++counter;
    --counter;

    /* Pointer operators */
    int value = 99;
    pointer   = &value;       /* & = address-of operator */
    int deref = *pointer;     /* * = dereference operator */

    /* String output */
    printf("Hello, World!\n");
    printf("Name: %s, Number: %d, Pi: %.2f\n", name, number, pi_value);
    printf("Grade: %c\n", grade);
    printf("Computed: %d\n", SQUARE(5));

    /* IF - ELSE statement */
    if (number > 0) {
        printf("Number is positive\n");
    } else if (number == 0) {
        printf("Number is zero\n");
    } else {
        printf("Number is negative\n");
    }

    /* WHILE loop */
    int i = 0;
    while (i < 5) {
        printf("While iteration: %d\n", i);
        i++;
    }

    /* FOR loop */
    for (int j = 0; j < MAX_SIZE; j++) {
        array[j] = j * 2;
    }

    /* DO-WHILE loop */
    int k = 10;
    do {
        k--;
        printf("Do-while: k = %d\n", k);
    } while (k > 7);

    /* SWITCH statement */
    enum Color my_color = GREEN;
    switch (my_color) {
        case RED:
            printf("Color is Red\n");
            break;
        case GREEN:
            printf("Color is Green\n");
            break;
        case BLUE:
            printf("Color is Blue\n");
            break;
        default:
            printf("Unknown color\n");
            break;
    }

    /* Struct usage */
    struct Student student1;
    student1.roll_number = 101;
    student1.marks       = 95.5;

    /* Pointer to struct (arrow operator) */
    struct Student* s_ptr = &student1;
    s_ptr->marks = 98.0;

    /* Ternary operator */
    int max_val = (x > number) ? x : number;

    /* Type casting */
    float result = (float)sum / (float)product;

    /* sizeof operator */
    int size_int = sizeof(int);
    int size_arr = sizeof(array);

    /* Nested function calls */
    float area = calculate_area(PI);
    print_message("Analysis complete");

    /* Return from main */
    return 0;
}

/* -----------------------------------------------
 * FUNCTION: add
 * Returns the sum of two integers
 * ----------------------------------------------- */
int add(int a, int b) {
    return a + b;
}

/* -----------------------------------------------
 * FUNCTION: calculate_area
 * Calculates area of a circle given radius
 * ----------------------------------------------- */
float calculate_area(float radius) {
    float area = PI * radius * radius;
    return area;
}

/* -----------------------------------------------
 * FUNCTION: print_message
 * Prints a string with a border
 * ----------------------------------------------- */
void print_message(char* msg) {
    printf("=== %s ===\n", msg);
}
