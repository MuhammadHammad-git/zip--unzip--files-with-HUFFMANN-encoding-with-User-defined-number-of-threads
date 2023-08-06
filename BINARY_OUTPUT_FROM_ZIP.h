#include <stdlib.h>
#include <stdio.h>


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
        return bi;
}

void Binary_output(char *zipfile){

	FILE* fzip = fopen(zipfile,"rb");
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
	free(binary_string);
	fclose(fzip);
}
