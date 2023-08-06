#define MAX_ACII 127
#define Freq_char_placer 0


int freq[MAX_ACII] = { 0 };
int* findFrequency(thread_i *t_i) {
		
	for(int i = t_i->start; i < t_i->end; i++){
		freq[array[i] - Freq_char_placer]++;
	}
	return freq;
}
