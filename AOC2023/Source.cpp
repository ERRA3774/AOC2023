// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996) // _CRT_SECURE_NO_WARNINGS

#define INLINE inline
#define INTERNAL static
#define GLOBAL static

#define MAX_STRING_LENGTH 256
#define NUMBER_STRING_COUNT 10

// --------------------------------------------------------
// Constants

const char* DAY1_INPUT_FILE_PATH = "res/day1.txt";
const char* DAY2_INPUT_FILE_PATH = "res/day2.txt";

const char* NumberStringTable[NUMBER_STRING_COUNT]{
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
// --------------------------------------------------------


// --------------------------------------------------------
// First Aid Functions

INLINE bool IsDigit(char ch) {
    return ch <= '9' && ch >= '0';
}

INLINE int GetNumber(const char* str) {
    int res = -1;

    if (str == nullptr || strlen(str) < 3) {
        return -1;
    }

    for (int i = 0; i < NUMBER_STRING_COUNT; i++) {
        if (str[0] == NumberStringTable[i][0] && str[1] == NumberStringTable[i][1]) {
            return i;
        }
    }

    return res;
}
// --------------------------------------------------------


// --------------------------------------------------------
// Poetry 

INTERNAL void Day1TwoDigitsSum(const char* filename = DAY1_INPUT_FILE_PATH) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY1 :: Part 1 :: Could not open file from path = '%s'", filename);
        return;
    }

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        char* l = buf;
        char* r = buf + strlen(buf) - 1;

        int d1 = -1;
        int d2 = -1;

        for (; l <= r; ) {

            if (!IsDigit(*l)) {
                l++;
            }

            if (!IsDigit(*r)) {
                r--;
            }

            if (IsDigit(*l) && IsDigit(*r)) {
                d1 = (*l - '0');
                d2 = (*r - '0');
                break;
            }
        }
        sum += (d1 * 10 + d2);
    }

    fclose(file);
    printf("DAY1 :: Part 1:: Expected=55477, Actual=%d\n", sum);
}

INTERNAL void Day1TwoSpelledOutNumbersSum(const char* filename = DAY1_INPUT_FILE_PATH) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY1 :: Part 2 :: Could not open file from path = '%s'", filename);
        return;
    }

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        char* l = buf;
        char* r = buf + strlen(buf) - 1;

        int min = (int)strlen(buf) - 1;
        int max = 0;

        int d1 = -1;
        int d2 = -1;

        bool found = false;
        for (int i = 0; i < NUMBER_STRING_COUNT; i++) {
            int pos;
            char* first = strstr(buf, NumberStringTable[i]);
            if (first != nullptr) {
                found = true;
                pos = (int)(first - buf);

                if (pos < min) {
                    min = pos;
                }
            }

            char* last = nullptr;
            while (first != nullptr) {
                last = first;
                first = strstr(first + 1, NumberStringTable[i]);
            }

            if (last != nullptr) {
                found = true;
                pos = (int)(last - buf);

                if (pos > max) {
                    max = pos;
                }
            }
        }

        if (found) {
            d1 = GetNumber(buf + min);
            d2 = GetNumber(buf + max);

            for (; l < buf + min; l++) {
                if (IsDigit(*l)) {
                    d1 = *l - '0';
                    break;
                }
            }

            for (; r > buf + max; r--) {
                if (IsDigit(*r)) {
                    d2 = *r - '0';
                    break;
                }
            }
        }
        else {
            for (; l <= r; ) {

                if (!IsDigit(*l)) {
                    l++;
                }

                if (!IsDigit(*r)) {
                    r--;
                }

                if (IsDigit(*l) && IsDigit(*r)) {
                    d1 = (*l - '0');
                    d2 = (*r - '0');
                    break;
                }
            }
        }
        sum += (d1 * 10 + d2);
    }

    fclose(file);
    printf("DAY1 :: Part 2 :: Expected=54431, Actual=%d\n", sum);
}

enum ColorType {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,

    COLOR_COUNT,
};

INTERNAL void Day2SumOfValidGames(const char* filename = DAY2_INPUT_FILE_PATH) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY2 :: Part 1 :: Could not open file from path = '%s'", filename);
        return;
    }

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr; ) {
        bool valid = true;
        char* tok = strtok(buf, " :,;");
        tok = strtok(nullptr, " :,;");
        int id = atoi(tok);

        int gameCube[COLOR_COUNT] = {
            12, // RED 
            13, // GREEN
            14, // BLUE
        };

        while ((tok = strtok(nullptr, " ,;")) != nullptr) {
            int n = atoi(tok);
            tok = strtok(nullptr, " ,");

            char* r = nullptr;
            if (tok) {
                r = tok + strlen(tok) - 1;

                if (strstr(tok, "red")   != nullptr && gameCube[COLOR_RED]   < n ||
                    strstr(tok, "green") != nullptr && gameCube[COLOR_GREEN] < n ||
                    strstr(tok, "blue")  != nullptr && gameCube[COLOR_BLUE]  < n) {
                    valid = false;
                }

                if (r && *r == ';') {
                    // Finished the set in a game
                    continue;
                }
            }
        }

        if (!valid) {
            continue;
        }

        sum += id;
    }

    fclose(file);
    printf("DAY2 :: Part 1 :: Expected=2879, Actual=%d\n", sum);
}

// --------------------------------------------------------


int main() {
    Day1TwoDigitsSum();
    Day1TwoSpelledOutNumbersSum();
    Day2SumOfValidGames();
    return 0x0000000000000000000000000000000000000000000000;
}