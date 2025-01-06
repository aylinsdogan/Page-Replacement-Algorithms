#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

typedef struct {
	int pageNum;
	int writingTime; 
	int accesTime; 
	int readCount; 
} Page;

typedef struct {
	int numOfPage;
	int capacity;
	Page *Pages;
} Memory;

void clearMemory(Memory *memory) {
	memory->numOfPage=0;
    for(int i=0; i < memory->capacity; i++) { 
		memory->Pages[i].pageNum=-1;
		memory->Pages[i].writingTime=0;
		memory->Pages[i].accesTime=0;
		memory->Pages[i].readCount=1;
    }
}


int FIFO(int size, int *process_accesses, Memory *memory) { 
	int pageFault=0;
	int index = 0;
	
	for(int i=0;i < size; i++){
		int avail = 0;
		for(int j=0; j < memory->capacity; j++) { 
			if(process_accesses[i] == memory->Pages[j].pageNum){
				avail=1;
				break;
			}
		}
		if(avail == 0){
			pageFault++;
			int repIndex=0;
			int boo = 0;
			
			for(int j=0; j < memory->capacity ;j++){
				if(memory->Pages[j].pageNum == -1){
					repIndex = j;
					memory->Pages[repIndex].pageNum = process_accesses[i];
					boo = 1;
					break;
				}
			}
			if(boo == 0) {
				memory->Pages[index].pageNum = process_accesses[i];
				index++;
				index = index % memory->capacity;

			}
		}
	}
	
	return pageFault;
}

int LFU(int size, int *process_accesses, Memory *memory) { 
	int pageFault=0;
	int index = 0;
	
	for(int i=0;i < size; i++){
		int avail = 0;
		for(int j=0; j < memory->capacity; j++) { 
			if(process_accesses[i] == memory->Pages[j].pageNum){
				avail=1;
				memory->Pages[j].readCount++;
				break;
			}
		}
		if(avail == 0){
			pageFault++;
			int repIndex=0;
			int boo = 0;
			
			for(int j=0; j < memory->capacity ;j++){
				if(memory->Pages[j].pageNum == -1){
					repIndex = j;
					memory->Pages[repIndex].pageNum = process_accesses[i];
					boo = 1;
					break;
				}
			}
			if(boo == 0){
				int index2= INT_MAX;
				int loc=0;
				for(int z=0; z < memory->capacity; z++){
					if(memory->Pages[z].readCount < index2){
						index2 = memory->Pages[z].readCount;
						loc = z;
					}
				}
				for(int z=loc; z < memory->capacity-1; z++){
					memory->Pages[z] = memory->Pages[z+1];
				}

				memory->Pages[memory->capacity-1].pageNum = process_accesses[i];
			}
		}
	}
	
	return pageFault;
}

int LRU(int size, int *process_accesses, Memory *memory) { 
	int pageFault=0;
	int index = 0;
	
	for(int i=0;i < size; i++){
		int avail = 0;
		for(int j=0; j < memory->capacity; j++) {
			if(process_accesses[i] == memory->Pages[j].pageNum){
				avail=1;
				memory->Pages[j].accesTime=i;
				break;
			}
		}
		if(avail == 0){
			
			pageFault++;
			int repIndex=0;
			int boo = 0;
			
			for(int j=0; j < memory->capacity ;j++){
				if(memory->Pages[j].pageNum == -1){
					repIndex = j;
					memory->Pages[repIndex].pageNum = process_accesses[i];
					memory->Pages[repIndex].accesTime = i;
					boo = 1;
					break;
				}
			}
			if(boo == 0){
				int index2= INT_MAX;
				int loc = -1;
				for(int z=0; z < memory->capacity; z++){
					if(memory->Pages[z].accesTime < index2){
						index2 = memory->Pages[z].accesTime;
						loc = z;
					}
				}
				
				memory->Pages[loc].pageNum = process_accesses[i];
				memory->Pages[loc].accesTime = i;
			}
		}
	}
	
	return pageFault;
}

int Random(int size, int *process_accesses, Memory *memory) { 
	int pageFault=0;
	int index = 0;
	
	for(int i=0;i < size; i++){
		int avail = 0;
		for(int j=0; j < memory->capacity; j++) { 
			if(process_accesses[i] == memory->Pages[j].pageNum){
				avail=1;
				break;
			}
		}
		if(avail == 0){
			pageFault++;
			int repIndex=0;
			int boo = 0;
			
			for(int j=0; j < memory->capacity ;j++){
				if(memory->Pages[j].pageNum == -1){
					repIndex = j;
					memory->Pages[repIndex].pageNum = process_accesses[i];
					boo = 1;
					break;
				}
			}
			if(boo == 0){
				int randomNum = rand() % memory->capacity; 
				memory->Pages[randomNum].pageNum = process_accesses[i];
			}
		}
	}
	
	return pageFault;
}

int allFrequency(int *process_accesses, int size,int num){
	int frequency = 0;
	
	for(int i=0;i < size; i++){
		if(num == process_accesses[i]){
			frequency++;
		}
	}
	return frequency;
}

int Weighted_Random(int size, int *process_accesses, Memory *memory) {
	int pageFault=0;
	int index = 0;
	double tmpArr[size];
	int tmpArrSize=0;
	
	for(int i=0;i < size; i++){
		tmpArr[i]=0.0;
	}
	
	for(int i=0;i < size; i++){
		tmpArr[process_accesses[i]]++;
	}
	double bigSum =0;
	for(int i=0;i < size; i++){
		bigSum+=tmpArr[i];
	}
	
	for(int i=0;i < size; i++){
		if(tmpArr[i]!=0.0)
			tmpArr[i]=bigSum/tmpArr[i];
	}

	for(int i=0;i < size; i++){
		int avail = 0;
		for(int j=0; j < memory->capacity; j++) { 
			if(process_accesses[i] == memory->Pages[j].pageNum){
				avail=1;
				memory->Pages[j].readCount++;
				break;
			}
		}
		if(avail == 0){
			pageFault++;
			int repIndex=0;
			int boo = 0;
			
			for(int j=0; j < memory->capacity ;j++){
				if(memory->Pages[j].pageNum == -1){
					repIndex = j;
					memory->Pages[repIndex].pageNum = process_accesses[i];
					boo = 1;
					break;
				}
			}
			if(boo == 0){
				int index2= INT_MAX;
				int loc=0;
				double smallBigSum = 0.0;
				for(int z=0; z < memory->capacity; z++){
					smallBigSum+=tmpArr[memory->Pages[z].pageNum];
				}
				double random_value;
				random_value = (double)rand()/RAND_MAX*smallBigSum;
				smallBigSum = 0.0;
				for(int z=0; z < memory->capacity; z++){
					smallBigSum+=tmpArr[memory->Pages[z].pageNum]; 
					if(smallBigSum>=random_value){
						loc=z;
						break;
					}
				}
				for(int z=loc; z < memory->capacity-1; z++){
					memory->Pages[z] = memory->Pages[z+1];
				} 
				memory->Pages[memory->capacity-1].pageNum = process_accesses[i];
			}		
		}
	}
	
	return pageFault;
}

int main(int argc, char *argv[]) {
    
	if (argc != 2) {
        printf("Usage: %s <numOfPages>\n", argv[0]);
        return 1;
    }

    int numOfPages = atoi(argv[1]);

    if (numOfPages <= 0) {
        printf("Invalid number of pages. Please enter a positive integer.\n");
        return 1;
    }
    
    Memory *memory = malloc(sizeof(Memory));
    memory->numOfPage = 0;
    memory->capacity = numOfPages; 
    memory->Pages = malloc(memory->capacity * sizeof(Page));
    
    FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    char *line = NULL;  
    size_t len = 0;   
    srand((unsigned int)time(NULL));
    clearMemory(memory);
    while (getline(&line, &len, file) != -1) {

        line[strcspn(line, "\n")] = '\0';
		
	int *process_acsesses = NULL;
        int size = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            size++;
            process_acsesses = realloc(process_acsesses, size * sizeof(int));
            if (process_acsesses == NULL) {
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }
            process_acsesses[size - 1] = atoi(token);
            token = strtok(NULL, ",");         
		}
		printf("Sayfa Erisim Listesi: ");
		for(int i=0;i < size; i++){
			printf("%d ", process_acsesses[i]);
		}
		printf("\n");
		
		int fifo = FIFO(size,process_acsesses,memory);
		printf("FIFO: %d \n", fifo);
		clearMemory(memory);
		
		int lru = LRU(size,process_acsesses,memory);
		printf("LRU: %d \n", lru);
		clearMemory(memory);
		
		int lfu = LFU(size,process_acsesses,memory);
		printf("LFU: %d \n", lfu);
		clearMemory(memory);
			
		float averageOfRandom=0;
		for(int z=0; z < 1000 ; z++){
			clearMemory(memory);
			averageOfRandom += Random(size,process_acsesses,memory);
		}
		printf("Random: %f \n", (averageOfRandom/1000));
		clearMemory(memory);
		
		double averageOfWRandom=0;
		for(int z=0; z < 1000 ; z++){
			clearMemory(memory);
			averageOfWRandom += Weighted_Random(size,process_acsesses,memory);
		}
		
		printf("Weighted Random: %f \n", (averageOfWRandom/1000));
		printf("--------------------------------\n");
		clearMemory(memory);
	}	
}
