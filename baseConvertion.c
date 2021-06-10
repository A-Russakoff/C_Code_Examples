/*

    Number converter

    Menu
    Convert between integer, binary, octal and hexadecimal

    This program should accept numeric values in hexadecimal,
    decimal, octal and binary formats as:

        Hex 0x0 to 0xFFFFFFFF
        Dec 0 to 4294967295
        Oct o0 to o37777777777
        Bin b0 to b11111111111111111111111111111111

    After a value is input the code in main will interpret the
    data types above an process the conversion to an unsigned
    int.  The unsigned int will be used to convert the input to
    strings containing hexadecimal, octal and binary strings.

*/

#include <stdio.h>
#include<stdlib.h>
#include <string.h>


//int input_to_decimal(char *input);
unsigned int bin_to_uint(char *input);
unsigned int oct_to_uint(char *input);
unsigned int hex_to_uint(char *input);
unsigned int dec_to_uint(char *input);
void uint_to_hex(unsigned int n, char *output);
void uint_to_oct(unsigned int n, char *output);
void uint_to_bin(unsigned int n, char *output);


int error = 0;


int main(){

    char input[50];
    unsigned int n = 0;
    char output[50];

    // Write code here to test your functions
    
  
    
    // Uncomment code below when done

    printf("Enter a binary, octal, decimal or hexadecimal number\n");
    printf("convert > ");
    gets(input);

    // Detect input data type
    // Hexadecimal
    if(input[0] == '0' && input[1] == 'x'){
        n = hex_to_uint(input);
    }
    // Decimal
    else if(input[0] >= '0' && input[0] <= '9'){
        n = dec_to_uint(input);
    }
    // Octal
    else if(input[0] == 'o'){
        n = oct_to_uint(input);
    }
    // Binary
    else if(input[0] == 'b'){
        n = bin_to_uint(input);
    }
    // Unknown
    else{
        printf("ERROR: Unknown data type: %s\n", input);
    }

    // Print results
    printf("The decimal value of %s is %u\n", input, n);
    uint_to_hex(n, output);
    printf("The hexadecimal value of %s is %s\n", input, output);
    uint_to_oct(n, output);
    printf("The octal value of %s is %s\n", input, output);
    uint_to_bin(n, output);
    printf("The binary value of %s is %s\n", input, output);

	printf("Would you like to try another? Enter y or Y to try again.\n");
	char c;
	c = getc(stdin);
	//putc(c);
	getc(stdin);
	if (c=='y' || c=='Y'){
	return main();} else {
    return 0;}
}


/*
    This function converts the value part of the hex
    string to an unsigned integer value.  The first
    two chars are 0x, which tells that the string is
    in hex.  Start processing the value at index 2 until
    the null, calculating the int value as you would on
    paper.  Try on paper first.
*/
// Convert a hexadecimal char array to uint
unsigned int hex_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int mul= 1;

    // Declare iterator
    int i;

    // Loop through value part of input string
    
    for (i=(strlen(input)-1);i>1;i--){//miss index 0,1

        // If between 0 and 9 add 0 to 9 to res with multiplier
        
        if (input[i]>='0'&&input[i]<='9'){
        	res = res + ((input[i]-'0')*mul);
        
        }

        // If between A and F add 10 to 15 to res with multiplier
        else if (input[i]>='A'&&input[i]<='F'){
        	res = res + ((input[i]-'A'+10)*mul);
        
        } 

        // Error - exit
        else {
        printf("Error!!-- not a valid hex???\n");
        exit(0); //um I'm not sure this is right? there is an int called error provide by prof???
        }
        
        mul=mul*16;

        // Advance multiplier to next position value
        
	}
    return res;
}


/*
    Copy hex_to_uint() and modify for decimal input.
*/
// Convert a unsigned integer char array to uint
unsigned int dec_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    int mul = 1;
    int i;
    for (i=(strlen(input)-1);i>=0;i--){ 
    	if (input[i]>='0'&&input[i]<='9'){
        	res = res + ((input[i]-'0')*mul);
        
        } 
        else {
        	printf("Error!! -- not a valid decimal???\n");
        	exit(1);
        }
        mul=mul*10;
    	
    }

    return res;
}


/*
    Copy dec_to_uint() and modify for octal input.
*/
// Convert a octal char array to uint
unsigned int oct_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    int mul = 1;
    int i;
    for (i=(strlen(input)-1);i>0;i--){ //(i>0) miss index 0
    	if (input[i]>='0'&&input[i]<='9'){
        	res = res + ((input[i]-'0')*mul);
        
        } 
        else {
        	printf("Error!! -- not a valid octal???\n");
        	exit(2);
        }
        mul=mul*8;
    	
    }

    return res;

}


/*
    Copy oct_to_uint() and modify for binary input.
*/
// Convert a binary char array to unsigned int
unsigned int bin_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;

    int mul = 1;
    int i;
    for (i=(strlen(input)-1);i>0;i--){ //(i>0) miss index 0
    	if (input[i]>='0'&&input[i]<='9'){
        	res = res + ((input[i]-'0')*mul);
        
        } 
        else {
        	printf("Error!! -- not a valid binary number???\n");
        	exit(3);
        }
        mul=mul*2;
    	
    }

    return res;
}


/*
    This function converts from unsigned int to a hex
    char array.  Try this on paper before coding.
*/
// Convert a unsigned integer char array to hexadecimal
void uint_to_hex(unsigned int n, char *output){
    // Declare a uint for remainder
    //unsigned int rem;

    // Declare an int for division
    int base = 16;

    // Declare a char array buffer
    char buffer[50];
    
    //declare iterator 
    int i=0;
    // Use a loop to generate a hex string - string will be reverse
    while (n!=0){
		int mod = n%base;
		n = n/base;
		if (mod>=0&&mod<=9){
			buffer[i]=mod + '0'; 
		} else if (mod>=10&&mod<=15){
			buffer [i] = mod + 'A' - 10;
		} else {
			printf("ERROR!! DEC TO HEX FAILED!!!");
			exit(4);
		}
		i++;
	}
    	

    // Get last hex char <----wat?
    //seriously wat???

    // Put null at end of buffer
    buffer[i] = '\0';

    // Copy 0x to output string
    output[0]='0';
    output[1]='x';
    
    
    // Copy chars from buffer in reverse order to output string
    for (i=0; i<(strlen(buffer)+2); i++){//add "+2" --> (i=0; i<strlen(buffer)+2); i++;) for 0x
		output[i+2] = buffer[strlen(buffer)-i-1];//output i+2, space for 0x
	}
	output[i] = '\0';
	

    return;
}


/*
    Copy uint_to_hex() and modify for octal
*/
// Convert a unsigned integer char array to octal
void uint_to_oct(unsigned int n, char *output){
	 
	int base = 8;
	char buffer[50];
	int i=0;
	while (n!=0){
		int mod = n%base;
		n = n/base;
		if (mod>=0&&mod<=8){
			buffer[i]=mod + '0'; 
		} else {
			printf("ERROR!! DEC TO OCT FAILED!!!");
			exit(5);
		}
		i++;
	}
	buffer[i] = '\0';
	output[0]='o';

	for (i=0; i<(strlen(buffer)+1); i++){//add"+1"-->(i=0;i<strlen(buffer)+2); i++;) for 'o'
		output[i+1] = buffer[strlen(buffer)-i-1];//output i+1, space for 'o'
	}
	
	output[i] = '\0';
	return;
}


/*
    Copy uint_to_oct() and modify for binary
*/
// Convert a unsigned integer char array to binary
void uint_to_bin(unsigned int n, char *output){
	
	int base = 2;
	char buffer[50];
	int i=0;
	while (n!=0){
		int mod = n%base;
		n = n/base;
		if (mod>=0&&mod<=1){
			buffer[i]=mod + '0'; 
		} else {
			printf("ERROR!! DEC TO OCT FAILED!!!");
			exit(6);
		}
		i++;
	}
	buffer[i] = '\0';
	output[0]='b';

	for (i=0; i<(strlen(buffer)+1); i++){//add"+1"-->(i=0;i<strlen(buffer)+2); i++;) for 'o'
		output[i+1] = buffer[strlen(buffer)-i-1];//output i+1, space for 'b'
	}
	
	output[i] = '\0';

    return;
}

































