#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int extraMemoryAllocated;


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
   
   if (l < r) {
        int mid = (l + r) / 2; 
        mergeSort(pData, l, mid); //Divides array into two halves
        mergeSort(pData, mid + 1, r);

        // Merge the two sorted subarrays
        int TEMP1 = mid - l + 1;
        int TEMP2 = r - mid;
        
        int * LEFT = (int *)malloc(sizeof(int) * TEMP1);
        extraMemoryAllocated += sizeof(LEFT); //Gets data of LEFT to extraMem
        int * RIGHT = (int *)malloc(sizeof(int) * TEMP2);
        extraMemoryAllocated += sizeof(RIGHT); //Gets data of RIGHT to extraMem

        for (int i = 0; i < TEMP1; i++) { //Fills the arrays with data
            LEFT[i] = pData[l + i];
        }
        for (int j = 0; j < TEMP2; j++) {
            RIGHT[j] = pData[mid + 1 + j];
        }

        int i = 0;
        int j = 0; //resets all values to zero
        int k = l;
        while (i < TEMP1 && j < TEMP2) {
            if (LEFT[i] <= RIGHT[j]) {
                pData[k] = LEFT[i];
                i++;
            } else {
                pData[k] = RIGHT[j];
                j++;
            }
            k++;
        }
        while (i < TEMP1) {
            pData[k] = LEFT[i];
            i++;
            k++;
        }
        while (j < TEMP2) {
            pData[k] = RIGHT[j];
            j++;
            k++;
        }

        free(LEFT);
        free(RIGHT); //Frees the memory
    }
   
}


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
     
    for (int i = 1; i < n; i++) {
        int element = pData[i]; //Saves for use in future condition
        int j = i - 1;    //And for the use of a temporary placeholder
        
        while (j >= 0 && pData[j] > element) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = element; //Swaps no matter whaat but 
        //The j value is the only thing tht really changes.
        //Or doesn't change
    }
}


// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
   
    int x = 0;
    int temp = 0; //Used as temporary
    int test = 0;


    for(int i = 0; i < n-1; i++){ //Loops through till the end

        for(int y = 0; y < n - i - 1; y++){
                if(pData[y] > pData[y+1]){

                    temp = pData[y + 1]; //lower value to the
                    pData[y + 1] = pData[y];//Current index
                    pData[y] = temp;
                }
            
        }
    }
   
}


// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{

    for (int i = 0; i < n-1; i++)
    {
        int min = i; //Keeps the current min index
                            //To compare with i
        for (int j = i+1; j < n; j++) //Checks the curent min index
        { //Wiht I
          if (pData[j] < pData[min]){
              min = j;
          }
        }
        if (min != i){ //If I is different it does swaps the values
            int temp = pData[min];
            pData[min] = pData[i];
            pData[i] = temp;
        }

    }
}



// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
   

/*
    if(extraMemoryAllocated != 0){
        free(*ppData);
        *ppData = NULL;
    }
*/
   


    if (inFile)
    {
       
        char buff[200];//creating char array to store data of file  
        char buff2[20];
        int i = 0;


        //int temp[10000]; works with this but not the dynamic??
       
        fscanf(inFile, "%s", buff2);
        dataSz = atoi(buff2);


        //extraMemoryAllocated = dataSz;
        printf("EXTRA MEMORY IS %d\n", extraMemoryAllocated);
       
        int * temp = (int*)malloc(sizeof(int) * dataSz);


        while(fscanf(inFile, "%s", buff)!=EOF){  
            //printf("data size is %d\n", dataSz);
            temp[i] = atoi(buff);
            i++;


        }  
        
        *ppData = temp;
       
       
    }
    fclose(inFile);
   
    return dataSz;
}


// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i=0;i<100;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");
   
    for (i=sz;i<dataSz;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}


int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}