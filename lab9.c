#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Hash table size
#define HASH_SIZE 100

// HashType
struct HashType
{
    struct RecordType* record;
    struct HashType* next;
};

// Hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Initialize hash table
struct HashType** initializeHashTable()
{
    struct HashType** hashTable = (struct HashType**)malloc(sizeof(struct HashType*) * HASH_SIZE);
    for (int i = 0; i < HASH_SIZE; ++i)
        hashTable[i] = NULL;
    return hashTable;
}

// Insert record into hash table
void insertRecord(struct HashType** hashTable, struct RecordType record)
{
    int index = hash(record.id);
    struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));
    newNode->record = &record;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType** hashTable)
{
    printf("Records in Hash Table:\n");
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct HashType* current = hashTable[i];
        printf("Index %d -> ", i);
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->record->id, current->record->name, current->record->order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Parse input file to records
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

// Print records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType** hashTable = initializeHashTable();

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
        insertRecord(hashTable, pRecords[i]);

    // Display records in hash table
    displayRecordsInHash(hashTable);
    free(pRecords);

    return 0;
}