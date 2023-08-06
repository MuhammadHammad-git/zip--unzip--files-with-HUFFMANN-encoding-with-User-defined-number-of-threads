#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "FILE_SIZE_CALCULATOR.h"
#include "str_sep.h"




char* binary_string;
    int bi = 0;
int Dec_to_Bin(int n)
{
    char binaryNum[50] = { 0 };
 
    int i = 0;
    char integ;
    while (n > 0) {
 	integ = (n % 2)+48;
        binaryNum[i] = integ;
        n = n / 2;
        i++;
    }
    
    while(i < 8){
    integ = 0+48;
    binaryNum[i] = integ;
    i++;
    }
    
    int j = i-1;
    while(j > 0) {
        binary_string[bi] = binaryNum[j];
        j--; bi++;
        }
        binary_string[bi] = binaryNum[0];
        bi++;
        return bi;
}

void Binary_output(char *zipfile){

	FILE* fzip = fopen(zipfile,"rb");
	if(fzip == NULL){
	 	printf("file could not open file\nExit ");
	 	exit(-1);
	}
	int fsize = getfilesize(zipfile);
	binary_string = (char*)calloc(fsize*9,sizeof(char));
	unsigned char a[fsize+2];
	size_t nmemb = fsize;
	size_t size = 1;
	int dec = 0;
	int binary_stringlen = 0;
	
	fread(a, size, nmemb, fzip);
	for(int i = 0; i < nmemb; i++){
		dec = a[i];
		binary_stringlen = Dec_to_Bin(dec);
	}
	int kl = 1;
	int inc = 0;
	printf("\n");
	fclose(fzip);
}








int main(int argc, char **argv) {
	int ch;
	if (argv[1] == NULL||argv[2] == NULL||argv[3] == NULL){
	 perror("Arguments are <Filename> <No. of threads> <ZIpfilename>\n Exiting: ");
	 exit(-1);
	}
	char* zipfile = argv[1];
	printf("Your Selected ZIP FILE is: %s\n",zipfile);
	
	if (access(zipfile, F_OK) == 0) {
		printf("File %s Exists!\n",zipfile);
	}else{
		printf("%s\n",zipfile);
		perror("File Doesnot Exists!\nExit: ");
		exit(-1);
	}
	char* unzippedfile = argv[3];
	
	if (access(unzippedfile, F_OK) == 0) {
	    printf("File %s already exists\nDo you want to overwrite its contents? <y/n>\n", argv[3]);
	    printf("Your uncompressed OUTPUT FILE will be: %s\n",unzippedfile);
	    ch = getchar();
	    if (ch == 'y' || ch == 'Y'){
	    	printf("YES\n");
	    	printf("OVERWRITING FILE!\n");
	    	remove(unzippedfile);
	    	}
	    if (ch == 'n' || ch == 'N'){
	    	printf("Try again with another file name\n");	       
		exit(0);
	    	}
		if(ch != 'n' && ch != 'N' && ch != 'y' && ch != 'Y') {
		printf("Try again exiting\n");	       
		exit(0);
		}
	}
	
	
	
	FILE *funcomp;
	char *arg = "Encoder_file.txt";
	char delim[9];
	
	int nmemb = getfilesize("Encoder_file.txt");
	size_t size = sizeof(char);
	strcpy(delim,"bsee19020");
	char **parsed_array = (char**)malloc(sizeof(char*)*2);
	char **character_encoding = (char**)malloc(sizeof(char*)*180);
	FILE *enc_f = fopen(arg, "r");
	
	if (enc_f == NULL) {
			printf("\n Cannot open file: %s\n",arg);
			exit(1);
		}
	parsed_array[0] = (char*)calloc((nmemb+1),sizeof(char));
	parsed_array[1] = (char*)calloc((nmemb+1),sizeof(char));
	char* input_str = (char*)calloc((nmemb+1),sizeof(char));
	fread(input_str, size, nmemb, enc_f);
	
	int encod_bound = str_sep(input_str, parsed_array, delim);
	
	for(int i = 0; i < 180; i++){
		character_encoding[i] = (char*)calloc(16,sizeof(char));
	}
	
	strcpy(delim,"ITU");
	int en = str_sep(parsed_array[0], character_encoding, delim);
	
	
	Binary_output(zipfile);
	printf("Binary string from zipfile\n--------------------------\n%s\n--------------------------\n", binary_string);
	
	printf("Your uncompressed DATA:\n---------------------------------------\n");
	int j = 0;
	int m, bn = 0;
	int boundary_strln = strlen(parsed_array[1]);
	char comp[16];
	funcomp = fopen(unzippedfile,"a");
	while(j < boundary_strln){
		encod_bound = (parsed_array[1][j] - 48);
		m = 0;
		while(m < encod_bound){
			comp [m] = binary_string[bn];
			m++;
			bn++;
		}
		comp[m] = '\0';
		for(int i = 0; i < en; i+=2){
			if(strcmp(character_encoding[i],comp)==false){ 
				fprintf(funcomp ,"%s",character_encoding[i-1]);
				printf("%s",character_encoding[i-1]);
				}
		}
	j++;
	}
	
	printf("\n---------------------------------------\n");
	for(int i = 0; i < 180; i++)
		free(character_encoding[i]);
	
	
	free(character_encoding);
	free(parsed_array[0]);
	free(parsed_array[1]);
	free(parsed_array);
	free(input_str);
	free(binary_string);
	fclose(funcomp);
	fclose(enc_f);
}
