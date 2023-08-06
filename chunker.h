#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _thread_i {
	int start;
	int end;
	int *freqI;
}thread_i;

	thread_i *t_i;
thread_i* chunker(int array_size, int num_threads) {

	t_i = (thread_i*)malloc(sizeof(thread_i)*num_threads);
	int k = 0;
	char marg[array_size];
	while(k < array_size+1) {
		marg[k] = k;
		k++;
	}
	
	int chunk = floor((float)array_size/num_threads);
	int thindex;
	int n = 0;
	for(int i = 0; i < array_size-1; i = i + chunk){
		if (n >=  num_threads-1){
		t_i[n].start = i;
		t_i[n].end = array_size-1;
		break;
		}
		int index = (int)i/chunk;
		t_i[n].start = i;
		t_i[n].end = i + chunk < array_size ? i + chunk : array_size;
		thindex = index;
		n++;
	}
	return t_i;
}

void chunker_free(){
	free(t_i);

}
