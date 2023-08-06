int str_sep(char *input_str, char *parsed_array[], char *delim){
	char *i; 
	char *k;
	int n = 0;
	
	while(1){
	    	i = strstr(input_str, delim);
	    	if (i == NULL){
			strcpy(parsed_array[n],input_str);
			n++;
		    	break;
	    	}
	    	k = (i + strlen(delim));
	    	strcpy(i,"\0");
		strcpy(parsed_array[n],input_str);
		input_str= k;
		n++;
	}
	
	return n;
}
