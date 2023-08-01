#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r) {
  extraMemoryAllocated = 0; // Initialize memory allocation count
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  // Create temporary arrays
  int *leftArray = (int *)malloc(sizeof(int) * n1);
  int *rightArray = (int *)malloc(sizeof(int) * n2);
  extraMemoryAllocated += sizeof(int) * (n1 + n2);

  // Copy data to temporary arrays
  for (i = 0; i < n1; i++)
    leftArray[i] = pData[l + i];
  for (j = 0; j < n2; j++)
    rightArray[j] = pData[m + 1 + j];

  // Merge the temporary arrays back into pData[l..r]
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (leftArray[i] <= rightArray[j]) {
      pData[k] = leftArray[i];
      i++;
    } else {
      pData[k] = rightArray[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of leftArray and rightArray, if any
  while (i < n1) {
    pData[k] = leftArray[i];
    i++;
    k++;
  }
  while (j < n2) {
    pData[k] = rightArray[j];
    j++;
    k++;
  }

  // Free temporary arrays
  free(leftArray);
  free(rightArray);
}

void mergeSort(int pData[], int l, int r) {
  extraMemoryAllocated = 0; // Initialize memory allocation count
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);
    merge(pData, l, m, r);
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int *pData, int n) {
  extraMemoryAllocated = 0; // Initialize memory allocation count
  int i, j, key;
  for (i = 1; i < n; ++i) {
    key = pData[i];
    j = i - 1;
    while (j >= 0 && pData[j] > key) {
      pData[j + 1] = pData[j];
      --j;
    }
    pData[j + 1] = key;
  }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int *pData, int n) {
  extraMemoryAllocated = 0; // Initialize memory allocation count
  int i, j, temp;
  for (i = 0; i < n - 1; ++i) {
    for (j = 0; j < n - i - 1; ++j) {
      if (pData[j] > pData[j + 1]) {
        temp = pData[j];
        pData[j] = pData[j + 1];
        pData[j + 1] = temp;
      }
    }
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int *pData, int n) {
  extraMemoryAllocated = 0; // Initialize memory allocation count
  int i, j, minIdx, temp;
  for (i = 0; i < n - 1; ++i) {
    minIdx = i;
    for (j = i + 1; j < n; ++j) {
      if (pData[j] < pData[minIdx]) {
        minIdx = j;
      }
    }
    if (minIdx != i) {
      temp = pData[i];
      pData[i] = pData[minIdx];
      pData[minIdx] = temp;
    }
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (int *)malloc(sizeof(int) * dataSz);
    for (int i = 0; i < dataSz; i++) {
      fscanf(inFile, "%d", &(*ppData)[i]);
    }

    fclose(inFile);
  }
  // Implement parse data block

  return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
  int i, sz = dataSz - 100;
  printf("\tData:\n\t");
  for (i = 0; i < 100; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\t");

  for (i = sz; i < dataSz; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\n");
}

int main(void) {
  clock_t start, end;
  int i;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

  for (i = 0; i < 3; ++i) {
    int *pDataSrc, *pDataCopy;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0)
      continue;

    pDataCopy = (int *)malloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSz);
    printf("---------------------------\n");

    printf("Selection Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    selectionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Insertion Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    insertionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Bubble Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    bubbleSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Merge Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    mergeSort(pDataCopy, 0, dataSz - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    free(pDataCopy);
    free(pDataSrc);
  }
}