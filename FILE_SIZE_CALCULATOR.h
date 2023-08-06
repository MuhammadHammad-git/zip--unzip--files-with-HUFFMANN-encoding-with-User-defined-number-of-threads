int getfilesize(char *f) {
	FILE *fs = fopen(f, "r");
	fseek(fs,0,SEEK_END);
	int size = ftell(fs);
	
	fclose(fs);
	return size;
}
