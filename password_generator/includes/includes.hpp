#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

class passwordGenerator {
public:
    int getArgs(int argc, char* argv[]);
    int generatePassword(const char* mode, int length);
    int bufferErrHandler(char* inputBuf);
    void displayHelp();

private:
    char* cBuffer = nullptr;
    char index[74] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
        '3', '4', '5', '6', '7', '8', '9', '0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
        '-', '_'
    };
};

int passwordGenerator::getArgs(int argc, char* argv[]) {

    if (
	    (argc == 3) &&
        (argv[3] == NULL) &&
	    (atoi(argv[2]) > 0)
    ) {
       
	if (strcmp(argv[1], "--simple") == 0) {
            
            generatePassword("simple", atoi(argv[2]));
            return 0;

        } else if (strcmp(argv[1], "--normal") == 0) {

            generatePassword("normal", atoi(argv[2]));
            return 0;

        } else if (strcmp(argv[1], "--strong") == 0) {
            
            generatePassword("strong", atoi(argv[2]));
            return 0;

        } else {
            printf("Input is invalid, type passgen -h for help.\n");
            return -1;
        }

    } else if (
	    (argc == 2) &&
        (argv[2] == NULL) &&
	    ((strcmp(argv[1], "-h") == 0) ||
        (strcmp(argv[1], "--help") == 0))
	) {

	    displayHelp();
	    return 0;

    }else {

       printf("Input is invalid, type passgen -h for help.\n");
       return -1;
 
    }

    return 0;
}

int passwordGenerator::generatePassword(const char* mode, int length) {
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    if (strcmp(mode, "simple") == 0) {
        // a-z = 52 ( look at index )
        cBuffer = (char*)malloc((length + 1) * sizeof(char));
        bufferErrHandler(cBuffer);

        for (int i = 0; i < length + 1; i++) {
            cBuffer[i] = index[rand() %52];
        }
        cBuffer[length] = '\0';

        printf("%s\n", cBuffer);
        free(cBuffer);
        return 0;

    } else if (strcmp(mode, "normal") == 0) {
        // a-0 = 62 ( look at index )
        cBuffer = (char*)malloc((length + 1) * sizeof(char));
        bufferErrHandler(cBuffer);

        for (int i = 0; i < length + 1; i++) {
            cBuffer[i] = index[rand() %62];
        }
        cBuffer[length] = '\0';

        printf("%s\n", cBuffer);
        free(cBuffer);
        return 0;
        
    } else if (strcmp(mode, "strong") == 0) {
        // a-_ = 74 ( look at index )
        cBuffer = (char*)malloc((length + 1) * sizeof(char));
        bufferErrHandler(cBuffer);

        for (int i = 0; i < length + 1; i++) {
            cBuffer[i] = index[rand() %74];
        }
        cBuffer[length] = '\0';

        printf("%s\n", cBuffer);
        free(cBuffer);
        return 0;
    }
    return 0;
}

int passwordGenerator::bufferErrHandler(char* inputBuf) {
    
    if (inputBuf == NULL) {
        printf("Error occurred on allocating buffer.\n");
        return -1;
    }

    return 0;
}

void passwordGenerator::displayHelp() {
    printf("Usage: passwdgen [options] <password_length>\n"
           "Options:\n"
           "  --simple : Generate a simple password using letters (a-z).\n"
           "  --normal : Generate a normal password using letters (a-z) and digits (0-9).\n"
           "  --strong : Generate a strong password using letters (a-z), digits (0-9), and symbols.\n"
           "  -h       : Display this help message.\n"
    );
}
