#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

//Hackコンピュータが16bitコンピュータのため 0 から ((2^16)-1) までを考えられれば今は良い
int BIT = 16;

void exit_with_msg(char *msg) 
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

//ec = error checked
unsigned long ec_strtoul(char *argv, int base) {
                 char *end;
        unsigned long input = strtoul(argv, &end, base);

        if (*end != '\0') 
                exit_with_msg("[!] Error: Non numeric charcter detected");
        
        return input;
}

bool is_over_or_under_flowing(int min, unsigned long max, unsigned long input) 
{
        if (input < min || max < input)
                return 1;
        else 
                return 0;
}

void print_usage()
{
        printf("usage:\n");
        printf("        [+] debi <decimal number> <option>\n");
        printf("available option: -r\n");
}

int main(int argc, char *argv[]) 
{
        if (argv[1] == NULL) {
                print_usage();
                return 0;
        }
        unsigned long input_decimal = ec_strtoul(argv[1], 10);

        bool enable_readable_mode = false;
        if (argv[2] != NULL && strncmp(argv[2], "-r", 2) == 0) {
                enable_readable_mode = true;
        }

        int min = 0;
        unsigned long max = pow(2, BIT) -  1;
        if (is_over_or_under_flowing(min, max, input_decimal))
                exit_with_msg("[!] Error: Input range is: min = 0, max = (2^BIT)-1");

         int index = 0;
        bool output_binary[BIT];
        for (index = 0; index < BIT; index++)
                output_binary[index] = 0;

        for (index = 0; input_decimal != 0; index++, input_decimal /= 2){
                output_binary[index] = input_decimal % 2;
        }

        for(index = BIT-1; index >= 0; index--) {
                printf("%d", output_binary[index]);
                if (enable_readable_mode && index % 4 == 0)
                        printf(" ");
        }
        puts("");

        return 0;
}
