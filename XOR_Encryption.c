#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* make_rand_key(int, char *key);
void encrypt(char *clear_file, char *encrypt_file, char *cipher_file);
void decrypt(char *key_file, char *cipher_file, char *clear_file);
char* read_file(int, char *file_name);
void write_file(int, char *file_name, char*filestr);

int main(){
	
	//getting user's choice to encrypt, decrypt, or exit
	char userChoice;
	while(userChoice != '3'){
		printf("Encrypt a file: 1");
		printf("\nDecrypt a file: 2");
		printf("\nExit program: 3");
		printf("\nEnter a choice: ");
		userChoice = getchar();
	
		//initializing strings to point to file names
		char clear_file[] = "clear_file.txt";
		char key_file[] = "key_file.txt";
		char cipher_file[] = "cipher_file.txt";

		//running the program the user chooses
		switch(userChoice){
			case '1':
				printf("Encrpytion\n");
				encrypt(clear_file, key_file, cipher_file);
				break;
			case '2':
				printf("Decryption\n");
				decrypt(key_file, cipher_file, clear_file);
				break;
			case '3':
				printf("Exit program\n");
				return 0;
			default: 
				printf("Not a valid choice\n\n");
				char userChoice;
				break;
		}
	}
	return 0;
}

char* make_rand_key(int length, char* key){
	
	//if length of the array is greater than 0, we can make a key
	if(length>0){
		
		//allocating the key and checking if memory was allocated
		//char* key = (char *)malloc(length+1);
		key = malloc(length);
		if(key == NULL){
			printf("Error: Memory for key was not allocated");
			exit(0);
		}
		
		//generating a random key using rand
		srand(time(NULL));
		int i;
		for(i=0; i<length; i++){
			key[i] = (char)rand()%256;
			if (key[i]==0) key[i]=1;
			if (key[i]==EOF) key[i]=key[i]-1;
		}
		key[i] = '\0';
		printf("\nKey: %s", key);

		return key;
	}
	else{
		printf("Error: key was not generated\n");
		return NULL;
	}
}

//reads the clear_file.txt to a string, encrypts the string with a generated key,
//then writes encrypted text to the cipher_file.txt
void encrypt(char* clear_file, char* key_file, char* cipher_file){

	//reading the text to encrypt and putting it to a string
	char *clear_text; 
	clear_text = read_file(0, clear_file);
	
	//test
	printf("\n this is the clear txt in encrypt %s\n", clear_text);

	//finding the length of the encrypt string
	int length = strlen(clear_text);
	
	//making a key and encrypt text
	//then checking memory
	char* key = make_rand_key(length, key);
	//char *encrypted = (char *)malloc((length+1)*sizeof(char));
	char *encrypted = malloc((length));
	
	if (encrypted == NULL){
		printf("\nError: Memory for encrypted text no allocated");
		exit(0);
	}

	//encrypting the text using the key
	int i;
	for(i=0; i<length; i++){
		//encrypted[i] = clear_file[i] ^ key[i];
		encrypted[i] = clear_text[i] ^ key[i];
	}
	//encrypted[i] = '\0';

	printf("\nEncrypted text: %s\n", encrypted);
	//writing the encrypted text to cpiher_file.txt
	//writing the key to key_file.txt to use for decrypted
	write_file(length, cipher_file, encrypted);
	write_file(length, key_file, key);

	//freeing memory
	free(encrypted);
	free(key);
}

void decrypt(char* key_file, char* cipher_file, char* clear_file){
	
	//getting the key from the key_file.txt
	char *key = read_file(0, key_file);

	printf("\nKey: %s", key);
	
	int length = strlen(key);
	/*while(clear_file[length] != '\0'){
		length++;
	}*/
	
	//getting the encrypted text from the cipher_file
	//char *encrypted = (char *)malloc((length+1)*sizeof(char));
	char *encrypted = malloc(length);
	encrypted = read_file(length, cipher_file);
	printf("\nEncrypted: %s", encrypted);
	
	if(encrypted == NULL){
		printf("\nError: Memory for encrypted not allocated");
		exit(0);
	}
	
	//char *decrypted = (char *)malloc(length+1);
		char *decrypted = malloc(length);
	if(decrypted == NULL){
		printf("\nError: memory for decrypted not allocated");
		exit(0);
	}
	
	//decrypting the encrypted text
	int i;
	for(i=0; i<length; i++){
		char c = encrypted[i] ^ key[i];
		decrypted[i] = c;
	}
	decrypted[i] = '\0';
	
	//writing the decrypted text to the file
	//freeing memory
	//changed go write to complete.txt file name, I forget what was here before
	write_file(length, "complete.txt", decrypted);
	free(encrypted);
	free(decrypted);
	
}

char* read_file(int len, char *file_name){

	//pointer to the file program is reading
	FILE *ftr = fopen(file_name, "r");

	if(ftr == NULL){
		printf("\nError: Read file cannot be opened");
		exit(0);
	}
	//int length =0;
	int length = len;
	if(len == 0){
		while(getc(ftr) != EOF){
			length++;
		}
	}
	//test
	printf("\nthis is length in read file %d\n", length);
	//allocating memory for the file string and checking the memory
	//char *fileString = (char *)malloc((length+1)*sizeof(char));	
	char *fileString = malloc(length);
	if(fileString == NULL){
		printf("\nError: Memory for read file string not allocated");
		exit(0);
	}

	//for loop to put each character of the file into a string
	rewind(ftr);
	int i = 0;
	for(i=0; i<length; i++){
		fileString[i] = getc(ftr);
	}
	fileString[i] = '\0';
	
	//closing the file and returning the string of text
	fclose(ftr);
	return fileString;

}

void write_file(int length, char*file_name, char *fileStr){
	
	//Pointer to the file the program is writing to
	FILE *ftw = fopen(file_name, "w");
	
	//checking that file can be opened
	if(ftw == NULL){
		printf("\nError: Write file cannot be opened");
		exit(0);
	}
	
	//finding the length of file if unknown
	if(length == 0){
		length = strlen(fileStr);
	}

	//writing each character of the string to the file
	int i;
	for(i=0; i<length; i++){
		putc(fileStr[i], ftw);
	}
	
	//closing the file
	fclose(ftw);

}
