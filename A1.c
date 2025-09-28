#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void div_convert (uint32_t n, int base , char *out) {
char temp [65]; // Temporary buffer
int pos = 0;

// Handle zero case
if (n == 0) {
    strcpy (out , "0");
    return ;
}

// Extract digits from right to left
while (n > 0) {
    int remainder = n % base ;
    n = n / base ;// Convert digit to character
    
    if (remainder < 10){
    temp [pos ++] = '0' + remainder;} 
    else {
    temp [pos ++] = 'A' + (remainder - 10);}

    for (int  i = 0; i < pos; i++){
        out[i]=temp[pos-1-i];
    }
    out [pos] = '\0';
}
}

void sub_convert(uint32_t n, int base, char *out){

    if (n == 0) {
    strcpy (out , "0");
    return ;
    }

    if( base <2 || base > 16){
        out[0] = '\0';
        return;
    }

    uint32_t power = 1;

    while(power <= n/ (uint32_t)base){
        power *= (uint32_t)base;    
    }

    int index = 0;

    while (power > 0){
        uint32_t digit = n/ power;
        

        n -= digit * power;
        power /= (uint32_t)base;

        out[index++] = (digit < 10) ? ('0' + (int)digit) : ('A' + (int)(digit -10));

    }
    out[index]='\0';

}


void print_tables ( uint32_t n) {
    char bin [33] , oct [12] , hex [9];
    // Original number
    div_convert (n, 2, bin);
    div_convert (n, 8, oct);
    div_convert (n, 16, hex);
    printf (" Original : Binary =%s Octal =%s Decimal =%u Hex =%s\n",
        bin , oct , n, hex);
        
    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert ( shifted , 2, bin);
    div_convert ( shifted , 8, oct);
    div_convert ( shifted , 16, hex);
    printf (" Left Shift by 3: Binary =%s Octal =%s Decimal =%u Hex =%s\n",
    bin , oct , shifted , hex);
    
    // AND with 0 xFF
    uint32_t masked = n & 0xFF;
    div_convert ( masked , 2, bin);
    div_convert ( masked, 8, oct);
    div_convert ( masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);

}


void oct_to_bin(const char *oct, char *out){

    const char *binary_map[] = {"000","001","010","011","100","101","110","111"};

    int len = strlen(oct);
    out[0] = '\0';

    for(int i = 0; i < len; i++){
    
        if(oct[i] < '0' || oct[i] > '7'){
            out[0] = '\0';
         return;
        }

        int index = oct[i] - '0';
        strcat(out,binary_map[index]);
        
    }
}

void oct_to_hex(const char *oct, char *out){

    char binary_arr [512];

    oct_to_bin(oct,binary_arr);

    int len = strlen(binary_arr);

    int remainder = len%4;

    int extra_zeros = 4 - remainder;

    char padded[512];

    for (int i = 0; i < extra_zeros; i++)
    {
       padded[i] = '0';
    }
    strcpy(padded + extra_zeros,binary_arr);

    int array_size = strlen(padded);

    int counter =0;

    for(int i = 0; i < array_size; i+= 4){
        
        char four_digits[5];
        strncpy(four_digits,&padded[i],4); 
        four_digits[4] = '\0';
        
        if (strcmp(four_digits, "0000") == 0) {
            out[counter++] = '0';
        } else if (strcmp(four_digits, "0001") == 0) {
            out[counter++] = '1';
        } else if (strcmp(four_digits, "0010") == 0) {
            out[counter++] = '2';
        } else if (strcmp(four_digits, "0011") == 0) {
            out[counter++] = '3';
        } else if (strcmp(four_digits, "0100") == 0) {
            out[counter++] = '4';
        } else if (strcmp(four_digits, "0101") == 0) {
            out[counter++] = '5';
        } else if (strcmp(four_digits, "0110") == 0) {
            out[counter++] = '6';
        } else if (strcmp(four_digits, "0111") == 0) {
            out[counter++] = '7';
        } else if (strcmp(four_digits, "1000") == 0) {
            out[counter++] = '8';
        } else if (strcmp(four_digits, "1001") == 0) {
            out[counter++] = '9';
        } else if (strcmp(four_digits, "1010") == 0) {
            out[counter++] = 'A';
        } else if (strcmp(four_digits, "1011") == 0) {
            out[counter++] = 'B';
        } else if (strcmp(four_digits, "1100") == 0) {
            out[counter++] = 'C';
        } else if (strcmp(four_digits, "1101") == 0) {
            out[counter++] = 'D';
        } else if (strcmp(four_digits, "1110") == 0) {
            out[counter++] = 'E';
        } else if (strcmp(four_digits, "1111") == 0) {
            out[counter++] = 'F';
        }
    }
    out[counter] = '\0'; 
}
void hex_to_bin(const char *hex, char *out){
    out[0] = '\0';

    int len = strlen(hex);

    int counter = 0;
    
    for(int i = 0; i < len; i++){

        char hex_arr[2];
        hex_arr[0] = toupper(hex[i]);
        hex_arr[1] = '\0';
    
        if (strcmp(hex_arr, "0") == 0) {
            strcat(out,"0000");

        } else if (strcmp(hex_arr, "1") == 0) {
            strcat(out,"0001");

        } else if (strcmp(hex_arr, "2") == 0) {
            strcat(out,"0010");

        } else if (strcmp(hex_arr, "3") == 0) {
            strcat(out,"0011");

        } else if (strcmp(hex_arr, "4") == 0) {
            strcat(out,"0100");

        } else if (strcmp(hex_arr, "5") == 0) {
            strcat(out,"0101");

        } else if (strcmp(hex_arr, "6") == 0) {
            strcat(out,"0110");

        } else if (strcmp(hex_arr, "7") == 0) {
            strcat(out,"0111");

        } else if (strcmp(hex_arr, "8") == 0) {
            strcat(out,"1000");

        } else if (strcmp(hex_arr, "9") == 0) {
            strcat(out,"1001");

        } else if (strcmp(hex_arr, "A") == 0) {
            strcat(out,"1010");

        } else if (strcmp(hex_arr, "B") == 0) {
            strcat(out,"1011");

        } else if (strcmp(hex_arr, "C") == 0) {
            strcat(out,"1100");

        } else if (strcmp(hex_arr, "D") == 0) {
            strcat(out,"1101");

        } else if (strcmp(hex_arr, "E") == 0) {
            strcat(out,"1110");

        } else if (strcmp(hex_arr, "F") == 0) {
            strcat(out,"1111");
        }else{
            out[0] = '\0';
            return;
        }
    }  
}


void to_sign_magnitude(int32_t number, char *out){
    char temp [65];
    div_convert(number < 0 ? -number : number,2,temp);

    int len = strlen(temp);

    int extra_zeros = 32 - len;

    char newtemp[512];

    if(number >= 0){
        for (int i = 0; i < extra_zeros; i++){
            newtemp[i] = '0';
        }
        strcpy(newtemp + extra_zeros,temp);
        strcpy(out,newtemp);
    } else {
        newtemp[0] = '1';
        for (int i = 1; i <= extra_zeros-1; i++){
            newtemp[i] = '0';
        }
        strcpy(newtemp + extra_zeros,temp);
        strcpy(out,newtemp);
    }
    
}

void to_ones_complement(int32_t number, char *out){
     char temp [65];

      if(number == 0){
        for(int i = 0; i < 32; i++){
            out[i] = '0';
        }
        out[32] = '\0';
        return;
    }
    div_convert(number < 0 ? -number : number,2,temp);

    int len = strlen(temp);

    int extra_zeros = 32 - len;

    char newtemp[512];

    if(number >= 0){
        for (int i = 0; i < extra_zeros; i++)
        {
            newtemp[i] = '0';
        }
        strcpy(newtemp + extra_zeros,temp);
        strcpy(out,newtemp);

    } else {

    for (int i = 0; i < len; i++){
        if(temp[i] == '0'){
        temp[i] = '1';
        }else if(temp[i] == '1'){
         temp[i] = '0';
        }

    }
    

    for (int i = 0; i < extra_zeros; i++)
    {
       newtemp[i] = '1';
    }
    strcpy(newtemp + extra_zeros,temp);
    strcpy(out,newtemp);
    }
    

}
void to_twos_complement(int32_t number, char *out){
     char temp [65];

    if(number == 0){
        for(int i = 0; i < 32; i++){
            out[i] = '0';
        }
        out[32] = '\0';
        return;
    }    

    div_convert(number < 0 ? -number : number,2,temp);

    int len = strlen(temp);

    int extra_digits = 32 - len;

    char newtemp[512];

    if(number >= 0){
        for (int i = 0; i < extra_digits; i++){
            newtemp[i] = '0';
        }
        strcpy(newtemp + extra_digits,temp);
        newtemp[32] = '\0';
        strcpy(out,newtemp);

    } else {
         for (int i = 0; i < len; i++){
            if(temp[i] == '0'){
                temp[i] = '1';
            }else if(temp[i] == '1'){
                temp[i] = '0';
            }
         }
        
        for (int i = 0; i < extra_digits; i++){
            newtemp[i] = '1';
        }
        strcpy(newtemp + extra_digits,temp);
        newtemp[32] = '\0';

        int carry = 1;
    
    for(int i = 31; i >= 0; i--) {
        
        if (newtemp[i] == '1' && carry == 1) {
            newtemp[i] = '0';  
        } else if (newtemp[i] == '0' && carry == 1) {
            newtemp[i] = '1';  
            carry = 0;
        } 
        
    }
    strcpy(out,newtemp);
    }
   
}


int main(){
    char actual_output [65];

//   div_convert(3405774592,16, actual_output);
//     printf(actual_output);

//     sub_convert(3405774592,16, actual_output);
//     printf(actual_output );

//     print_tables(4294967295);

//     oct_to_bin("10", actual_output);

//     printf("Binary: %s\n", actual_output);
typedef struct {
    char function_name [50];
    char input [100];
    char expected_output [100];
} TestCase ;

TestCase test []={
    {"oct_to_bin","725","111010101"},
    {"oct_to_bin","345","011100101"},
    {"oct_to_bin","777","111111111"},

    {"oct_to_bin","0","000"},
    {"oct_to_bin","1","001"},
    {"oct_to_bin","7","111"},

    {"oct_to_bin","10","001000"},
    {"oct_to_bin","100","001000000"},
    {"oct_to_bin","377","011111111"},

    {"oct_to_hex","345","E5"},
    {"oct_to_hex","777","1FF"},
    {"oct_to_hex","100","40"},

    {"oct_to_hex","0","0"},
    {"oct_to_hex","1","1"},
    {"oct_to_hex","7","7"},

    {"oct_to_hex","1234","29C"},
    {"oct_to_hex","7654","FAC"},

    {"hex_to_bin","A3","10100011"},
    {"hex_to_bin","FF","11111111"},
    {"hex_to_bin","1A","00011010"},

    {"hex_to_bin","a3","10100011"},
    {"hex_to_bin","Ff","11111111"},
    {"hex_to_bin","aC","10101100"},

    {"hex_to_bin","0","0000"},
    {"hex_to_bin","1","0001"},
    {"hex_to_bin","F","1111"},

    {"hex_to_bin","CAFE","1100101011111110"},
    {"hex_to_bin","1234","0001001000110100"},

    {"to_sign_magnitude","5","00000000000000000000000000000101"},
    {"to_sign_magnitude","1","00000000000000000000000000000001"},
    {"to_sign_magnitude","255","00000000000000000000000011111111"},

    {"to_sign_magnitude","-5","10000000000000000000000000000101"},
    {"to_sign_magnitude","-1","10000000000000000000000000000001"},
    {"to_sign_magnitude","-255","10000000000000000000000011111111"},

    {"to_sign_magnitude","0","00000000000000000000000000000000"},

    {"to_ones_complement","5","00000000000000000000000000000101"},
    {"to_ones_complement","1","00000000000000000000000000000001"},
    {"to_ones_complement","255","00000000000000000000000011111111"},

    {"to_ones_complement","-5","11111111111111111111111111111010"},
    {"to_ones_complement","-1","11111111111111111111111111111110"},
    {"to_ones_complement","-255","11111111111111111111111100000000"},

    {"to_ones_complement","0","00000000000000000000000000000000"},

    {"to_twos_complement","5","00000000000000000000000000000101"},
    {"to_twos_complement","1","00000000000000000000000000000001"},
    {"to_twos_complement","255","00000000000000000000000011111111"},

    {"to_twos_complement", "-5", "11111111111111111111111111111011"},
    {"to_twos_complement","-1","11111111111111111111111111111111"},
    {"to_twos_complement","-255","11111111111111111111111100000001"},

    {"to_twos_complement","0","00000000000000000000000000000000"},
        
    {"to_twos_complement","2147483647","01111111111111111111111111111111"},
    {"to_twos_complement","-2147483648","10000000000000000000000000000000"},
};

int total_tests = sizeof(test) / sizeof(test[0]);
int passed_test = 0;

for (int i = 0; i < total_tests; i++) {
    TestCase var_test = test[i];
    actual_output[0] = '\0';
    if (strcmp(var_test.function_name, "oct_to_bin") == 0) {
        oct_to_bin(var_test.input, actual_output);
    } else if (strcmp(var_test.function_name, "oct_to_hex") == 0) {
        oct_to_hex(var_test.input, actual_output);
    } else if (strcmp(var_test.function_name, "hex_to_bin") == 0){
        hex_to_bin(var_test.input, actual_output);
    }else if (strcmp(var_test.function_name, "to_sign_magnitude") == 0) {
        int32_t number = atoi(var_test.input);
        to_sign_magnitude(number, actual_output);
    } else if (strcmp(var_test.function_name, "to_ones_complement") == 0) {
        int32_t number = atoi(var_test.input);
        to_ones_complement(number, actual_output);
    } else if (strcmp(var_test.function_name, "to_twos_complement") == 0) {
        int32_t number = atoi(var_test.input);
        to_twos_complement(number, actual_output);
    }else {
        printf("Test %d: Unknown function name: %s\n", i + 1, var_test.function_name);
        continue;
    }
    
    int pass = strcmp(actual_output, var_test.expected_output) == 0;
    
    if (pass) {
        passed_test++;
    }
        printf("Test %d: %s(%s) → Expected: \"%s\", Got: \"%s\" [%s]\n",
        i + 1,
        var_test.function_name,
        var_test.input,
        var_test.expected_output,
        actual_output,
        pass ? "PASS" : "FAIL");
    }
    printf("Summary: %d/%d tests passed.\n", passed_test, total_tests);       


    return 0;
    //ends the main function
}