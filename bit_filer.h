#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

	
void bit_filer(char *c, FILE *bin)
{
	
	 = "100001";
	long l = strtol(c, 0, 2);
	
	unsigned char b = l & 0xffl;
	
	fwrite(&b, 1, 1, bin);

}
















void delete_zip(char* file){
	remove(file);
}
