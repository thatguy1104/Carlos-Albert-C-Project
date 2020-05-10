//
// Created by Albert Mukhametov on 09/05/2020.
//

#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define HEX_LEN 20
#define MAX_ITERATIONS 100
#define STR_LEN 5

// Supplementary Functions

int int_len(int value) {
    int l = !value;
    while (value) {
        l++;
        value /= 10;
    }
    return l;
}

void printString(char *str) {
    while (*str != '\0')
        printf("%c", *str++);
    printf("\n");
}

void printMatrix(char matrix[MAX_ITERATIONS][STR_LEN], int inter_used) {
    printf("\n");
    for (int i = 0; i < inter_used + 1; i++) {
        printf("%s\n", matrix[i]);
    }
}

// Main Program Functions

void questions() {
    char continueKey[2];
    printf("Welcome, press any key to start\n");
    fgets(continueKey, 2, stdin);
}

bool check(char *hex) {
    int allZeros = false;
    for (int i = 0; i < strlen(hex) - 1; i++) {
        if ((hex[i] != '0')) {
            allZeros = false;
        } else {
            allZeros = true;
        }
    }
    return allZeros;
}

char *askForHexadecimal() {
    char hex[HEX_LEN];
    char cap[HEX_LEN];
    char noZeros[HEX_LEN];
    char *str = malloc(HEX_LEN);

    printf("Enter a hexadecimal number:\n");
    fgets(hex, HEX_LEN, stdin);

    while (allZeros(hex)) {
        printf("Enter a hexadecimal number:\n");
        fgets(hex, HEX_LEN, stdin);
    }
    for (int i = 0; i < strlen(hex) - 1; i++) {
        str[i] = hex[i];
    }

    char *f = removeZeros(str);
    char *c = capitalise(f);
    printString(c);
    return c;
}

char *capitalise(char *hex) {
    char result[HEX_LEN];
    for (int i = 0; i < strlen(hex); i++) {
        result[i] = toupper(hex[i]);
    }

    char *str = malloc(HEX_LEN);
    for (int i = 0; i < strlen(result); i++) {
        str[i] = result[i];
    }
    return str;
}

char *removeZeros(char *str) {
    char nonZ[HEX_LEN];
    int k = 0;
    bool leading = true;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '0') {
            nonZ[k] = str[i];
            k++;
            leading = false;
        }
        if (str[i] == '0' && !leading) {
            nonZ[k] = str[i];
            k++;
        }
    }
    char *p = malloc(HEX_LEN);
    for (int i = 0; i < strlen(nonZ); i++) {
        p[i] = nonZ[i];
    }
    return p;
}

bool allZeros(char *str) {
    bool zeros = false;
    while (*str != '\n') {
        if (*str != '0') {
            return false;
        }
        str++;
    }
    return true;
}

int HexToDec(char *hex) {
    int len = strlen(hex);
    int base = 1;
    int dec_val = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            dec_val += (hex[i] - 48) * base;
            base *= 16;
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            dec_val += (hex[i] - 55) * base;
            base *= 16;
        }
    }
    return dec_val;
}

char *DecToHex(int decimal) {
    char hexadecimal[5];
    char final[5];
    // Dynamically allocate memory for the final string - it will be used to update it each iteration
    char *str = malloc(5);
    int i = 0, k = 0;

    while (decimal != 0) {
        int temp = 0;
        temp = decimal % 16;
        if (temp < 10) {
            hexadecimal[i] = (char) (temp + 48);
            i++;
        } else {
            hexadecimal[i] = (char) (temp + 55);
            i++;
        }
        decimal = decimal / 16;
    }
    hexadecimal[i] = '\0';

    // Reverse hexadecimal array to get the final result
    for (int j = i - 1; j >= 0; j--) {
        final[k] = hexadecimal[j];
        k++;
    }
    final[k+1] = '\0';

    // For dynamic allocation of memory, copy contents of the final array to the heap
    for (int i = 0; i < strlen(final); i++) {
        str[i] = final[i];
    }
    return str;
}

int squaresum1(char *hex) {
    int Dec2sum = HexToDec(hex);
    int remainder = 0, sum = 0;
    while (Dec2sum > 0) {
        remainder = Dec2sum % 10;
        sum += remainder * remainder;
        Dec2sum = Dec2sum / 10;
    }
    return sum;
}

void iterationLoop(char *hex) {
    int iteration = 0;
    char continue_key[2];
    int sum_of_squares = squaresum1(hex);
    printf("Starting...\n");
    fgets(continue_key, 1, stdin);

    char matrix[MAX_ITERATIONS][STR_LEN];

    while (true) {
        if (iteration != MAX_ITERATIONS && sum_of_squares != 1) {
            fgets(continue_key, 2, stdin);
            strcpy(matrix[iteration], hex);
            printString(hex);
            printf("decimal = %i\n", HexToDec(hex));
            printf("sum of squares = %i\n", squaresum1(hex));
            sum_of_squares = squaresum1(hex);
            hex = DecToHex(sum_of_squares);

            printString(hex);
            iteration++;
        }
        else if (continue_key[0] == ' ') {
            break;
        }
        else if (sum_of_squares == 1) {
            strcpy(matrix[iteration], "1");
            break;
        }
        else {
            break;
        }
    }
    char key[2];
    printf("\nPress any key to show the iterations matrix:\n");
    fgets(key, 2, stdin);
    printMatrix(matrix, iteration);
}

void run() {
    questions();
    char *hexadecimal = askForHexadecimal();
    iterationLoop(hexadecimal);
}

int main() {
    run();
}