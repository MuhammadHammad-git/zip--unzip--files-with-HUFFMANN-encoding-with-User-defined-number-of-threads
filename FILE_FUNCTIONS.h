

char *ar = NULL;

char* File_function(FILE *fstr, int size) {

	ar = (char*)malloc(sizeof(char)*size+1);
	
	if (fstr == NULL) {
		printf("file can't be opened \n");
	}
	
	printf("\n\t**This is the data in your file***");
	printf("\n----------------------------------------\n");
	int trav = 0;
	while (!feof(fstr)) {
		ar[trav] = fgetc(fstr);
		trav++;
	}
	
	
	int rav = 0;
	while (rav < size) {
		printf("%c", ar[rav]);
		rav++;
	}
	
	printf("\n----------------------------------------\n");
	return ar;
}
void FILE_function_free(){
	free(ar);

} 
