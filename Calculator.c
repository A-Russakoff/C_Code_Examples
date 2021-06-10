/*

    Safe integer calculator - warns if an overflow or
    underflow error occurs.


    No math operators (+ - * / % ++ or --) except simple
    assignment (=). 

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// Prototypes
int _add(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int neg(int a);
int mul(int a, int b);
int divide(int a, int b);
int mod(int a, int b);
int power(int a, int b);
int convert(char *input);
//add prototypes
void menu();


// Main
int main(int argc, char *argv[]){

    int res = 0;        // Cumulative result - running total
    int n = 0;          // For number conversion from input string
    char input[50];     // Input string
    input[0] = '\0';    // Put null in operator char so loop works

    // Write code here to test your functions
    // Uncomment code below when done

    // Loop until quit is selected
    while(input[0] != 'q' && input[0] != 'Q'){
        // Show menu choices
        menu();
        // Print prompt with running total
        printf("\nres = %d > ", res);
        // Get input string
        gets(input);
        // Clear screen
        
        //the following line only works for Linux cmd line. Please uncomment only if using linux
        system("clear");//changed from cls to clear
       
       
       //The following line only works for Windows cmd line. Please uncomment only if using windows
       //system("cls");

        // Switch on operator char input[0]
        switch (input[0]){
            case '+':
                res = add(res, convert(input));
                break;
            case '-':
                res = sub(res, convert(input));
                break;
            case '*':
                res = mul(res, convert(input));
                break;
            case '/':
                res = divide(res, convert(input));
                break;
            case '%':
                res = mod(res, convert(input));
                break;
            case '~':
                res = neg(res);
                break;
            case '^':
                res = power(res, convert(input));
                break;
            case 'c':
            case 'C':
                res = 0;
                break;
            case 'q':
            case 'Q':
                printf("Good-bye!\n");
                break;
            default:
                printf("Enter a valid operator and operand\n");

        }

    }


    return 0;
}


// Show menu choices
void menu(){
    printf("\nSafe Integer Calculator\n");
    printf("+ x to add\n");
    printf("- x to subtract\n");
    printf("* x to multiply\n");
    printf("/ x to divide\n");
    printf("%% x to modulus\n"); //possible mistake here, should be % or \n???
    printf("~ x to negate\n");
    printf("^ x to raise by power x\n");
    printf("c x to clear result\n");
    printf("q x to quit\n");
    return;
}


/*
    This function should only use bitwise operators and
    relational operators
*/
// Add operation using only bitwise operators
int _add(int a, int b){
    // Loop until b is zero
	while(b!=0){
        // Find carry 1 bits - a AND b assign to carry
	int c = a & b;
        // Find non carry 1 bits - a XOR b assign to a
	a = a ^ b;
        // Multiply carry by 2 by shift and assign to b
        b = c<<1;
        }

    return a;
}


/*
    Safe add() should call _add() and check for both
    overflow and underflow errors.
*/
// Safe add operation
int add(int a, int b){
    // Declare int for result
    int res = 0;
    // Call to _add() a and b and assign to result
    res = _add(a,b);

    // Check for overflow - look at page 90 in book
    if (a>0&&b>0) {
    	if (res<0){
    		printf("Overflow Error!!!\n");
    		exit(0);
    	}
    }

    // Check for underflow - look at page 90 in book
    if (a<0&&b<0) {
    	if (res>=0){
    		printf("Negative Overflow Error!!!\n");
    		exit(1);
    	}
    }
    

    return res;
}


/*
    Negate a by using a bitwise operator and safe add().
    Look on page 95 in book.
    Replace the zero with an expression that solves this.
*/
// Define negation with ~ and safe add
int neg(int a){
    // Return negation of a and add 1
    
    return add(~a,1);   // Replace 0 with code
}


/*
    Remember that subtraction is the same as addition
    if you negate one of the operands.
    Replace the zero with an expression that solves this.
*/
// Define safe subtract by safe add - negate b
int sub(int a, int b){
    return add(a,neg(b)); // Replace 0 with code
}


/*
    Safe mul() uses an iterative call to safe add()
    to calculate a product. Remember that
        5 x 4 = 5 + 5 + 5 + 5 = 20
*/
// Define safe multiply by calling safe add b times
int mul(int a, int b){
    // Declare and initialize cumulative result
    int res = 0;
    // Declare sign of product - initially assume positive
    int sign = 1;

    // For efficiency - smaller number should be multiplier
    if ( a < b){
		int temp = a;
		a = b;
		b = temp;
	}

    // Absolute value of a and flip sign
    if ( a < 0){
		 a = neg(a);
		 sign = neg(sign);
	}

    // Absolute value of b and flip sign
    if (b < 0){
		b = neg(b);
		sign = neg(sign);
	}

    // Accumulate result
    while (b!=0){
		res = add(res,a);
		b = sub(b,1);
	}

    // Set sign to output
    if (sign < 0)
		res = neg(res);

    return res;
}


/*
    Safe div() repeatedly subtracts b from a, counting the
    number of subtractions until a < b, which it returns.
*/
// Define safe divide by calling safe subtract b times
int divide(int a, int b){
    // Declare int to count how many times can b be subtracted from a
    int cnt = 0;
    // Declare sign
	int sign = 1;
    // Absolute value of a and flip sign
	if ( a < 0){
		a = neg(a);
		sign = neg(sign);
	}

    // Absolute value of b and flip sign
	if (b < 0){
		b = neg(b);
		sign = neg(sign);
	}

    // loop to calculate how many times can b be subtracted from a
	while (b<=a){
		a = sub(a,b);
		cnt = add(cnt,1);
	}

    // Set sign to output
    if (sign<1){
    	cnt = neg(cnt);
    }

    return cnt;
}


/*
    Safe mod() repeatedly subtracts b from a until a < b, returning a.
*/
// Define safe modulus by calling safe subtract
int mod(int a, int b){
    // Absolute value of a
	if (a<0){a = neg(a);}
    // Absolute value of b
	if (b<0){b = neg(b);}
    // Find remainder by repeated subtraction a - b
	while (a>=b){
	a = sub(a,b);	
	}
    return a;
}


/*
    Safe pow() calculates as the math pow function but
    only uses the safe operations.
        res = n^exp
    Loop until exp is zero
        res = res * n
        exp = exp - 1
    Remember the special case for n^0

*/
// Define safe pow by calling safe multiply exp times
int power(int n, int exp){
	// Declare int for result of n^exp
	int res = 1;
    
	//code to throw away negative exponents
	if (exp<0){
	printf("Negative exponent not allowed!!\n");
	return res;
	}
	// Loop and multiply to calculate n^exp
	while (exp>0){
		res = mul(n,res);
		exp=sub(exp,1);
	}
	
	return res;
}


/*
    This function extracts the integer value from the input string.
        If input = "+ -123", res = -123.
        If input = "* 987654", res = 987654.
    The best way to solve complicated problems is to work them out
    on paper first.
*/
// Extract the integer from the input string and convert to int
int convert(char *input){
	// Declare int for result extracted from input
	int res = 0;
	// Declare int for sign of result
	int sign = 1;
	// Declare two iterators
	int i=2;
	int j=0;
	// Declare a buffer for numeric chars
	char buffer[50];
	// Set error to zero - no error found yet
	int error = 0;
	// Check for space in element 1
	if (input[1]!=' ') {
	printf("Input Error!!\n while checking for null space\n");
	exit(3);
	}
	// Check for negative integer at element 2
	if (input[2] == '-'){
		sign = neg(sign);
		i = add(i,1);
		
	}

	// Loop to copy all numeric chars to buffer
	// i is iterator for input string and should start at first numeric char
	// j is iterator for buffer where numeric chars are copied
	// This must test for chars between 0 and 9
	while(input[i]!='\0'){
		
		if ((input[i]>='0')&&(input[i]<='9')){
		
			buffer[j]=input[i];
			i=add(i,1);
			j=add(j,1);
		}
		else { 
			printf("Input Error!!\n");
			exit(4);
		}
	}
	// j is iterator for buffer where numeric chars are copied
	// This must test for chars between 0 and 9

	// i gets position of last numeric char in buffer //seems like it would be j???
	

	// j is now used for pow function - start at zero //seems like it would be i???
	
	i=0;
	j=sub(j,1);
	// Construct integer from buffer using pow j increases and i decreases
	while(j>=0){
	
		res = add(res,mul(sub(buffer[j],'0'),power(10,i)));
		
		i=add(i,1);
		j=sub(j,1);
		
		
		
	
	
	}

	// Set sign for output
	
	res=mul(res,sign);
    return res;
}

