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

#define MAX_STRING_LENGTH 256
#define NUMBER_STRING_COUNT 10

// --------------------------------------------------------
// Constants

const char* INPUT_FILE_PATH = "res/input.txt";

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

INTERNAL void Day1TwoDigitsSum(const char* filename = INPUT_FILE_PATH) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY1 :: Could not open file from path = '%s'", filename);
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
    printf("DAY1 :: Expected=55477, Actual=%d\n", sum);
}

INTERNAL void Day2TwoSpelledOutNumbersSum(const char* filename = INPUT_FILE_PATH) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY2 :: Could not open file from path = '%s'", filename);
        return;
    }

    char buf[MAX_STRING_LENGTH];
    for (int line = 0; fgets(buf, MAX_STRING_LENGTH, file) != nullptr; line++) {
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
    printf("DAY2 :: Expected=54431, Actual=%d\n", sum);
}
// --------------------------------------------------------

int main() {
    Day1TwoDigitsSum();
    Day2TwoSpelledOutNumbersSum();
    return 0x0000000000000000000000000000000000000000000000;
}