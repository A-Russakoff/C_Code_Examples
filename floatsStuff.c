#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include<stdlib.h>
 
#define MAX_MANTISSA 8388608
#define NORM 0
#define DNORM 1
#define SPEC 2
#define BIAS 127

typedef struct flt{
	int sign;
	int expo;
	float mantissa;
	int mode;} flt;

int get_flt_bits_int(float);
char getSignChar(float);
int getSignInt(float);
char* getExpoString(float);
int getExpoInt(float f);
int getExpoMode(float);
char* getMantissaString(float);
float getMantissaFloat(float);
char* getFloatString(float);
float power(int,int);
flt getFloatStruct(float);
void printFloatStruct(flt);
float calcFloatStruct(flt); 
int getMantissaInt(float);





/*
    Declare a "typedef struct {} flt;" to contain data for a float
    The data should include:
        An integer for the sign
            (1 for positive, -1 for negative)
        An integer for the exponent value
            (should be bit value to integer minus BIAS or -126 for denormalized)
        A float to contain the value of the mantissa
            (Actual float value extracted from the binary value)
        An integer to contain the mode using the defines above
            (NORM, DNORM and SPEC)
    Example after processing: -15.375 = 1 10000010 11101100000000000000000
        sign = -1
        exp = 3
        man = 0.9218750000
        mode = NORM
*/


float power(int base, int expo){
	float value=base;
	int flag=0;
	if (expo<0) {expo=(-1)*(expo);flag=1;}
	
	
	if (expo==0){value=1;return value;}
	while (expo!=1){
	value = value*base;
	expo--;
	}
	if (flag == 1){value=(1/value);}
	return value;
}





/*
    Write a function get_flt_bits_int to return an integer with the
    bits copied from a float.
    Example:
        for f = -15.375,
        the bits of int n = 11000001011101100000000000000000
    Look at the slides and code from the float lectures and use the
    indirection trick.  This can easily be done in one line of code.
    The function should accept a float and return an int.
*/
int get_flt_bits_int(float f){
int i = *((int *)&f);
}



/*
    Write a function that returns the sign of a float as a char.
    You should call get_flt_bits_int to get the bits in an int
    and return '1' if the sign is negative else return '0'.  The
    function should accept a float and return a string.
*/
char getSignChar(float fl){
	
	int i = get_flt_bits_int(fl);	
	if (i>=0){return '0';}else return '1';

}



/*
    Write a function that returns the sign of a float as an integer.
    You should call get_flt_bits_int to get the bits in an int
    and return -1 if the sign is negative else return 1.  The function
    should accept a float and return an int.
*/
int getSignInt(float fl){
	
	int i = get_flt_bits_int(fl);	
	if (i>=0){return 1;}else return -1;

}




/*
    Write a function to return a string containing the
    actual binary value of the exponent of a float in a
    char array.  You should call get_flt_bits_int to get
    the bits in an int and return the string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are "10000010"
    The function should accept a float and return a string.
*/
char* getExpoString(float fl){
int i;
int N = 23;
char* buffer=malloc(9); //don't forget to free after each call
int f = get_flt_bits_int(fl);
for (i=0;i<8;i++){
	
	if(f & (1<<N)){
		buffer[7-i]='1';
		}
	else{
		buffer[7-i]='0';
		}
	N++;

}
buffer[8]='\0';

return buffer;

}
/*
    Write a function to return an integer containing the
    actual integer value of the exponent of a float.  You
    should call get_flt_bits_int to get the bits in an int
    and return the int with the exponent value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are 10000010
            the actual value of the exponent is 3
    The function should accept a float and return an int.
*/
int getExpoInt(float f){
	int i;
	int N=23;
	int mult=1;
	int fl = get_flt_bits_int(f);
	int expo=0;
	for (i=0;i<8;i++){
		if (fl&(1<<N)){
		expo = expo + mult;
		
		}
	mult=mult*2;	
	N++;
	}
	return (expo-BIAS);
	
}


/*
    Write a function to return an integer containing the
    mode of the exponent of a float.  You should call
    get_flt_exp_val to get the bits in an int and return
    the int with the mode value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are 10000010
            the mode is NORM
    The function should accept a float and return an int.
*/

int getExpoMode(float f){
	int fl = getExpoInt(f) + BIAS;
	int i;
	int mode = 0;
	int N = 0;
	for (i=0;i<8;i++){
		if (fl&(1<<N)) {
		mode++;
		}
		N++;
	}
	if (mode==0){return DNORM;}
	else if (mode==8){return SPEC;}
	else return NORM;

}


/*
    Write a function to return a string containing the
    actual binary value of the mantissa of a float in a
    char array.  You should call get_flt_bits_int to get
    the bits in an int and return the string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the mantissa bits are 
            "11101100000000000000000"
            "11101100000000000000000 //love to see it	
    The function should accept a float and return a string.
*/

char* getMantissaString(float f){
	int fl = get_flt_bits_int(f);
	int i;
	//remember to free when called
	char *buffer = malloc(24);
	for (i=0;i<23;i++){
		if (fl & (1<<i)) {buffer[22-i]='1';}else{buffer[22-i]='0';}
		
	}
	buffer[23]='\0';
	return buffer;

}


/*
    Write a function to return a float containing the
    actual float value of the mantissa of a float.  You
    should call get_flt_bits_int to get the bits in an int
    and return the int with the mantissa value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the mantissa bits are 11101100000000000000000
            the actual value of the mantissa is 0.9218750000
    The function should accept a float and return an int.
*/

float getMantissaFloat(float f){
	int fl = get_flt_bits_int(f);
	int i=22;
	float mult = (0.5);
	float mantissa=0.0;
	
	for (i=22;i>=0;i--){
		if (fl & (1<<i)) {mantissa=mantissa+mult;}
		mult = mult*(0.5);
	}
	return mantissa;
}




/*
    Write a function to return a string containing the
    actual binary value of a float in a char array.  You
    should call get_flt_sign_char, get_flt_exp_str and
    get_flt_man_str to get the bits in an char and two
    strings and return the concatenated string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            The sign is '1'
            the exponent is "10000010" 111 01000001 1
            and the mantissa bits are "11101100000000000000000"
            The string should be formatted as:
                "1 10000010 11101100000000000000000" to clearly
                separate the 3 parts.
    The function should accept a float and return a string.
*/
char* getFloatString(float f){
	int i;
	char *buffer=malloc(35);
	buffer[34]='\0';
	buffer[0]=getSignChar(f);
	buffer[1]=' '; buffer[10]=' ';
	char*expo=getExpoString(f);
	char*mantissa=getMantissaString(f);
	for (i=2;i<10;i++){buffer[i]=expo[i-2];}
	for (i=11;i<35;i++){buffer[i]=mantissa[i-11];}
	free(expo);free(mantissa);
	return buffer;


}

//adding a function to get mantissa as an int
int getMantissaInt(float f){
	int fl = (*(int*)&f);
	
	fl = (fl & MAX_MANTISSA); 
	
	printf("getMantissaInt test %d\n", fl);
	return fl;

}




/*
    Write a function to separate the parts of a float
    into a flt struct as described above.  You should
    call get_flt_sign_val, get_flt_exp_mode,
    get_flt_exp_val and get_flt_man_val.
    Hint:  make sure to set exponent to -126 for
    DNORM mode.
*/

 flt getFloatStruct(float f){
	flt a;
	a.sign = getSignInt(f);
	a.expo=getExpoInt(f);
	a.mantissa=getMantissaFloat(f);
	a.mode=getExpoMode(f);
	if (a.mode==DNORM) {a.expo=-126;}
	return a;

}




/*
    Write a function to print a flt struct to screen.
    It should accept a flt struct and return nothing.
    Hint: Use if statement to print mode.
*/
void printFloatStruct(flt a){
	printf("sign %d, expo %d, mantissa %0.23f:\n", a.sign, a.expo, a.mantissa);
	
	if (a.mode==NORM){printf("Normalized\n");}
	else if (a.mode==DNORM){printf("De-Normalized\n");}
	else {printf("Special value\n");}


}



/*
    Write a function to get the actual float value back
    out of a flt struct.
    Hints:
        The float value produced will depend on the mode.
        To set a float to infinity use the math library constant INFINITY
        To set a float to not-a-number use the math library constant NAN
        Check the slides and text for conditions for NORN, DNORM and SPEC
        You need to return (sign) * M * 2^e
*/

float calcFloatStruct(flt a){
	if (a.mode==DNORM){
		if ((a.mantissa==0.0)&&(a.sign==1)){return 0.0;}
		else {return a.sign*(1+a.mantissa)*power(2,a.expo);}	
	}
	if (a.mode==SPEC){
		if (a.mantissa==0.0) {return INFINITY;}
		else return NAN;
	}
	return a.sign*(1+a.mantissa)*power(2,a.expo);
}


/*
    Write a main function that calls an prints results for
    each function when completed.
    get_flt_sign_char
    get_flt_sign_val

    get_flt_exp_str
    get_flt_exp_val

    get_flt_man_str
    get_flt_man_val

    get_flt_bits_str

    get_flt_val_flt
    print_flt

    get_flt_bits_val
*/
int main(){
	
	float input;
	
	printf("Enter a number to test:  ");
	
	scanf("%f", &input);
	
	printf("\nThank you, your input has been stored as  :\n %0.23f\n\n", input);
	
	
	
	
	printf("get_flt_bits_int(input) returns %d\n\n", get_flt_bits_int(input));
	
	printf("getSignChar(input) returns %c\n\n", getSignChar(input));
	
	printf("getSignInt(input) returns %d\n\n", getSignInt(input));
	
	printf("getExpoString(input) returns %s\n\n", getExpoString(input));
	
	printf("getExpoInt(input) returns %d\n\n", getExpoInt(input));
	
	printf("getMantissaString(input) returns %s\n\n", getMantissaString(input));
	
	printf("getMantissaFloat(input) returns %0.23f\n\n", getMantissaFloat(input));
	
	printf("getFloatString(input) returns %s\n\n", getFloatString(input));
	
	printf("function printFloatStruct(getFloatStruct(input)) prints: \n\n");
	
	printFloatStruct(getFloatStruct(input));
	
	printf("\nfunction calcFloatStruct(getFloatStruct(input)) returns %0.23f\n", calcFloatStruct(getFloatStruct(input)));

	




    return 0;
}
/*
 *
 * TEST MAIN PLEASE IGNORE!
 *
*/

/*int main(){
	float f = -15.375;
	int i = get_flt_bits_int(f);
	printf("%d\n", i);
	char signChar = getSignChar(f);
	printf("%c\n", signChar);
	int signInt = getSignInt(f);
	printf("%d\n", signInt);
	char * expo=getExpoString(f);
	printf("working if prints %s\n", expo);
	free(expo);
	printf("working if prints %s\n", expo);
	int expo1=getExpoInt(f);
	printf("expo1 is %d\n", expo1);
	int zero = 0;
	float negg = *((float *)&zero);
	float inf = 1.0/0.0;
	int mode=getExpoMode(f);
	printf("value of mode is %d\n", mode);
	printf("mantissa attempt %s\n", getMantissaString(f));
	printf("mantissa float attempt %f\n", getMantissaFloat(f));
	char * string = getFloatString(f);
	printf("float string progress %s\n", string);
	flt a = getFloatStruct(f);
	printf("sign %d, expo %d, mantissa %f:\nmode %d\n", a.sign, a.expo, a.mantissa, a.mode);
	printFloatStruct(a);
	printFloatStruct(getFloatStruct(1.0/0.0));
	printFloatStruct(getFloatStruct(0.00000000000000000000001));
	
	int base=2;
	int exp=-5;
	printf("value from power is %f\n", power(base, exp));
	printf("first take???? %f\n", calcFloatStruct(getFloatStruct(f)));
	printf("\n----------------------------\n");
	printf("test inf comes out '%f'\n", calcFloatStruct(getFloatStruct(inf)));
	int t = 1;
	float dnorm=*((float *)&t);
	printf("test dnorm comes out '%f'\n", calcFloatStruct(getFloatStruct(dnorm)));
	printFloatStruct(getFloatStruct(dnorm));
	printf("dnorm float is %0.50f\n", dnorm);
	union SWAP {
		float floatBit;
		int intBit;
	};
	
	union SWAP swap;
	swap.intBit = t;
	
	printf("union float %f\n", swap.floatBit);
	
	swap.floatBit = -15.375;
	
	printf("%d\n", swap.intBit);
	printf("%d\n", *((int *) &f));
	swap.intBit = MAX_MANTISSA;
	printf("%d\n", swap.intBit);
	int test = getMantissaInt(swap.floatBit);
	printf("back in main getMantissaInt  %d\n", test);
	swap.intBit = 67108860;
	int test2 = getMantissaInt(swap.floatBit);
	printf("back in main getMantissaInt  %d\n", test2);
	swap.intBit=2139095041;
	printf("calcFloatStruct test %f\n", calcFloatStruct(getFloatStruct(  swap.floatBit  )));
	
	
	
	
}*/





















