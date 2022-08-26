#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

#define SIZE 32
void print_symbols(uint8_t [], size_t);

void usage(int argc, const char *argv0){
    if(argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv0);
        exit(EXIT_FAILURE);
    }
}



int main(int argc, const char *argv[])
{
    usage(argc, argv[0]);


    uint8_t buff[SIZE];    
    FILE *f = fopen(argv[1], "rb");

    if(f == NULL){
        fprintf(stderr, "Could not open file: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    uint8_t ch;
    int column = 0;

    
    while (!feof(f)){
        if(i == 0){
            printf("%08x: ", column); //print number of each column in hex view
        }

        if(i % SIZE == 0 && i != 0){
            print_symbols(buff, i);
            i = 0;
            column += SIZE;
            printf("\n");
        }else{
            ch = fgetc(f);
            printf("%02x ", ch);
            buff[i] = ch;
            i++;
        }
        
    }
    if(i % SIZE-1 != 0){
        print_symbols(buff, i);
    }
    printf("\n");
    
    return 0;
}

void print_symbols(uint8_t buff[], size_t len){
    for(int i = 0; i < SIZE - len; ++i){
        printf("%3c", ' ');
    }
    printf(" | ");
    for (size_t i = 0; i < len; i++)
    {
        if(isprint(buff[i])){
            printf("%c", buff[i]);
        }else{
            printf(".");
        }
    }
    

}
