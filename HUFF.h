// Huffman Coding in C
//#include "encoder_str.h"
#define MAX_TREE_HT 50
typedef struct _encod {
	char char_value;
	char replacer[MAX_TREE_HT];
} encod;
int first_time = 1;
int placer = 0;
int il;

int str_len = 0;
encod *en = NULL;
int index_val = 0;
struct MinHeap *minHeap = NULL;
struct MinHNode *temp = NULL;
struct MinHeap *m = NULL;
  struct MinHNode *left, *right, **top;


  struct MinHNode *tem = NULL;
	char* str = NULL; 
struct MinHNode {
  char item;
  unsigned freq;
  struct MinHNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHNode **array;
};

// Create nodes
struct MinHNode *newNode(char item, unsigned freq) {
	//temp[sizeof(struct MinHNode)];
 temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

  temp->left = temp->right = NULL;
  temp->item = item;
  temp->freq = freq;
	//tem = &temp;
  return temp;
}

// Create min heap
struct MinHeap *createMinH(unsigned capacity) {
  minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
  return minHeap;
}
void free_HUFF(){
	free(en);
}
// Print the array
void printArray(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("  \n");
}


void printtoscreenencoding(int nos){
	for(int i = 0; i < placer; i++){
		printf("---%c----", en[i].char_value);
		printf("||%s", en[i].replacer);
		
		printf("\n");	 
		}
		printf("-----------------------\n");
	}


void write_forencoding(int arr[], int n, char ch){
	en[placer].char_value = ch;
	int ik;
	for (ik = 0; ik < n; ++ik){
	en[placer].replacer[ik] = arr[ik]+48;
	
	}
	placer++;
}
int deletefile(char* filename){
	if (remove(filename) == 0){
	printf("Previous encoder file deleted successfully\n");
	}else{
	printf("Previous encoder file could not be deleted!\nData is appended at the end of file\n");
	
	}

}

// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
  struct MinHNode *t = *a;
  *a = *b;
  *b = t;
}

// Heapify
void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

// Check if size if 1
int checkSizeOne(struct MinHeap *minHeap) {
  return (minHeap->size == 1);
}

// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap) {
  temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);
  
  return temp;
}

// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while(1)
  if (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  else {
  
  minHeap->array[i] = minHeapNode;
  
  break;}

  //
}

void buildMinHeap(struct MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode *root) {
  return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
 	
  minHeap = createMinH(size);
  
  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(item[i],freq[i]);
    
  minHeap->size = size;
  buildMinHeap(minHeap);
  return minHeap;
}

struct MinHNode *buildHuffmanTree(char item[], int freq[], int size) {

  minHeap = createAndBuildMinHeap(item, freq, size);
top = (struct MinHNode **)malloc(sizeof(struct MinHNode*)*size);
il = 0;
  while (!checkSizeOne(minHeap)) {
    left = extractMin(minHeap);
    right = extractMin(minHeap);
	
    top[il] = (struct MinHNode *)malloc(sizeof(struct MinHNode));
    top[il]->item = '$';
    top[il]->freq = left->freq + right->freq;
    top[il]->left = left;
    top[il]->right = right;

    insertMinHeap(minHeap, top[il]);
  	il++;
  }
  return extractMin(minHeap);
}

void printHCodes(struct MinHNode *root, int arr[], int top) {
  if (root->left) {
    arr[top] = 0;
    printHCodes(root->left, arr, top + 1);
  }
  if (root->right) {
    arr[top] = 1;
    printHCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root)) {
  // printf("  %c   | ", root->item);
 //  printArray(arr, top);
   write_forencoding(arr,top,root->item);
  }
}

// Wrapper function
void HuffmanCodes(char item[], int freq[], int size) {
  struct MinHNode *root = buildHuffmanTree(item, freq, size);
	
  int arr[MAX_TREE_HT], tope = 0;

  printHCodes(root, arr, tope);
	for(int k = 0; k <il; k++){
	free(top[k]);
	}
	free(top);
	
	
	free(minHeap->array);
	free(minHeap);
}
void HUFF(char *arr, int* freq, int size) {
 str_len = size;
  en = (encod*)calloc(255,sizeof(encod));
  printf("\n-----------------------\n");
  printf("--Char--||Huffman code ");
  printf("\n-----------------------\n");
  HuffmanCodes(arr, freq, size);
  printtoscreenencoding(size);
  deletefile("Encoder_file.txt");

}
