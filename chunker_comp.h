#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _thread_i_comp {
	int start;
	int end;
	int index_comp;
}thread_i_comp;

	thread_i_comp *t_i_comp;
thread_i_comp* chunker_comp(int array_size, int num_threads) {
	t_i_comp = (thread_i*)malloc(sizeof(thread_i)*num_threads);
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
		t_i_comp[n].start = i;
		t_i_comp[n].end = array_size-1;
		//printf("%d:   start %d, end %d\n", n, t_i_comp[n].start, t_i_comp[n].end);
		break;
		}
		int index = (int)i/chunk;
		t_i_comp[n].start = i;
		t_i_comp[n].end = i + chunk < array_size ? i + chunk : array_size;
		thindex = index;
		//printf("%d:   start %d, end %d\n", n, t_i_comp[n].start, t_i_comp[n].end);
		n++;
	}
	return t_i_comp;
}

void chunker_comp_free(){
	free(t_i_comp);

}
