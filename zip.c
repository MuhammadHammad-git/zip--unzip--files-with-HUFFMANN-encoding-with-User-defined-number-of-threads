// Libraries
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
// My Header Files
#include "chunker.h"
#include "chunker_comp.h"
#include "FILE_SIZE_CALCULATOR.h"
#include "FILE_FUNCTIONS.h"
#include "HUFF.h"
#include "bit_filer.h"

#define MAX_ACII 127
#define Freq_char_placer 0


	
	pthread_mutex_t mutex;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	int encoding = 0;
	char **encoding_str = NULL;
	
	int chunk = 0;
	int stringlen = 0;
	
	
	int fm[255]; 
	char cm[255];
	char *array = NULL;
	int *F_Freq = NULL;
	char **output_str = NULL;
	
	thread_i *t_i_main = NULL;
	
	
	thread_i_comp *t_i_com = NULL;
void free_threadfreq(int NO){
	for(int i = 0; i < NO; i++)
			free(t_i_main[i].freqI);
}

void FREQUENCY_THREADS(thread_i *t_i) {
	t_i->freqI = (int*)calloc(255,sizeof(int));
	
	for(int i = t_i->start; i < t_i->end; i++){
		t_i->freqI[array[i]]++;
	}
}



void COMPRESSION_THREADS(thread_i_comp *t_i_C) {

	
	output_str[t_i_C->index_comp] = (char*)malloc(sizeof(char)*(20*(t_i_C->end - t_i_C->start)));
	encoding_str[t_i_C->index_comp] = (char*)malloc(sizeof(char)*(20*(t_i_C->end - t_i_C->start)));

	

		for(int i = t_i_C->start; i < t_i_C->end; i++) {
		char ts[1];
		ts[1] = '\0';
			for(int ic = 0; ic < stringlen; ic++) {
		 
		 		if(array[i] == en[ic].char_value){
		 
		 			 if (i == t_i_C->start){
		 				strcpy(output_str[t_i_C->index_comp],en[ic].replacer);
		
		 				ts[0] = (strlen(en[ic].replacer)+48);
		
		 				strcpy(encoding_str[t_i_C->index_comp],ts);
		 				
		 				} else {
		
						strcat(output_str[t_i_C->index_comp],en[ic].replacer);
						ts[0] = (strlen(en[ic].replacer)+48);
		
						strcat(encoding_str[t_i_C->index_comp],ts);//(strlen(en[ic].replacer)+48));
						}
					}
				}
		}
}+-+-



// Driver Code
int main(int argc, char **argv) {

	if (argv[1] == NULL||argv[2] == NULL||argv[3] == NULL){
	 perror("Arguments are <Filename> <No. of threads> <ZIpfilename>\n Exiting: ");
	 exit(-1);
	}
	char* filenametoC = argv[1];
	char* Comfile = argv[3];
	char ch;
	 
		if (access(Comfile, F_OK) == 0) {
		    printf("File %s already exists\nDo you want to overwrite its contents? <y/n>\n", argv[3]);
		    ch = getchar();
		    if (ch == 'y' || ch == 'Y'){
		    	printf("YES\n");
		    	printf("OVERWRITING FILE!\n");
		    	remove(Comfile);
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
		int size = getfilesize(filenametoC);
		int N_O_Cthreads = 0;
		int N_O_Fthreads = 0;
		int N_O_AllTHREADS = atoi(argv[2]);
		if(N_O_AllTHREADS < 1){
		perror("Thread EXCEPTION:\nInvalid Amount of Threads! TRY AGAIN\nExit");
			exit(0);
		}
		N_O_Fthreads = floor(N_O_AllTHREADS/2);
		if(N_O_AllTHREADS == 1){
		N_O_Cthreads = 1;
		N_O_Fthreads = 1;
		}else{
		N_O_Cthreads = N_O_AllTHREADS-N_O_Fthreads;
		}
		if (N_O_Fthreads > size-5)
		{
			perror("Thread EXCEPTION:\nthere are too many threads compared to your Array size! Decrease the number of threads and try again!\nExit");
			exit(0);
		}
		
		delete_zip(Comfile);
		
		pthread_mutex_init(&mutex, NULL);
		F_Freq = (int*)calloc(255,sizeof(int));
		printf("\nYou have asked for %d number of threads!\nThreads will be divided into frequency finder threads and Compression Threads\n\n", N_O_AllTHREADS);
		
		FILE *bin;
		FILE* fp = fopen(filenametoC, "r");
		
		if(fp == NULL)
		perror("Your TARGET FILE cannot be opened!");
		else
		printf("Your TARGET FILE is:\t| %s | \n",argv[1]);
		
		printf("Your OUTPUT FILE will be:\t| %s | \n",argv[3]);
		array = File_function(fp,size);
		
		pthread_t thread_F[N_O_Fthreads];
		
		pthread_t thread_C[N_O_Cthreads];
		
		t_i_main = chunker(size, N_O_Fthreads);
		
		while(chunk < N_O_Fthreads) {
		printf("This CHUNK %d:	from %d, to %d belongs to thread no %d\n", chunk+1, t_i_main[chunk].start, t_i_main[chunk].end, chunk);
		
		pthread_create(&thread_F[chunk], NULL, (void*)FREQUENCY_THREADS, &t_i_main[chunk]);
			
			
			chunk++;
		}
		
		for(int k = 0; k < N_O_Fthreads;k++)
			pthread_join(thread_F[k],NULL);
			
		for(int k = 0; k < N_O_Fthreads;k++){
			
			for(int in = 0; in < 225;in++)
				F_Freq[in] = F_Freq[in]+t_i[k].freqI[in];
				
		}
		
		
		
		
		
		for (int i = 0; i < MAX_ACII; i++) {
		
			if (F_Freq[i] != 0) {
				fm[stringlen] = F_Freq[i];
				cm[stringlen] = (i + Freq_char_placer);
				stringlen++;
			}
			
		}
		
		int incr = 0;
		
		
		
		fclose(fp);
		
		HUFF(cm, fm, stringlen);
		
		
		t_i_com = chunker_comp(size, N_O_Cthreads);
		int comp_inc = 0;
		
		output_str = (char**)malloc(sizeof(char*)*N_O_Cthreads);
		encoding_str = (char**)malloc(sizeof(char*)*N_O_Cthreads);
		
		while(comp_inc < N_O_Cthreads) {
		
		t_i_com[comp_inc].index_comp = comp_inc;
		
		pthread_create(&thread_C[comp_inc], NULL, (void*)COMPRESSION_THREADS, &t_i_com[comp_inc]);
			comp_inc++;
		}
		
		
		for(int k = 0; k < N_O_Cthreads;k++)
			pthread_join(thread_C[k],NULL);

		
		
		bin = fopen(Comfile, "ab");
		
		if(bin == NULL)
		perror("Your output ZIP FILE could not be created!\n");
		else
		printf("Your output ZIP FILE: | %s | is created succesfully!\n",argv[3]);
		
		char arrC[8];
		int increment = 0;
		int CI = 0;
		int current = 0;
		int output_size = 0;
		for(int si = 0; si < N_O_Cthreads;si++){
			output_size = strlen(output_str[si]);
			while (increment < output_size){
				while(CI < 8){
					arrC[CI] = output_str[si][increment];
					increment++;
					CI++;
					if(increment == output_size && CI <  8) { 
						current = CI; break;
						}else {
							current = 0;
						}
					}
					CI = current;
					if(current == 0){
					bit_filer(arrC, bin);}
					else if(current != 0 && si == N_O_Cthreads-1) {
				arrC[current] = '\0';
				bit_filer(arrC, bin);
					}
			}
			increment = 0;
			free(output_str[si]);
			
		}
		
			//Print to File
		FILE *ENCOD = fopen("Encoder_file.txt","a");
		if (ENCOD == NULL){
		perror("Encoder_file.txt could not be created!\n");
		} else {
			for (int i = 0; i < placer; i++) 
				fprintf(ENCOD, "ITU%cITU%s", en[i].char_value,en[i].replacer);
			fprintf(ENCOD, "bsee19020");
			for (int i = 0; i < N_O_Cthreads; i++) {
				fprintf(ENCOD, "%s", encoding_str[i]);
				free(encoding_str[i]);
			}
			fclose(ENCOD);
		}
		fclose(bin);
		free_HUFF();
		free(array);
		free_threadfreq(N_O_Fthreads);
		chunker_free();
		free(output_str);
		chunker_comp_free();
		free(encoding_str);
		free(F_Freq);
		pthread_mutex_destroy(&mutex);
}
