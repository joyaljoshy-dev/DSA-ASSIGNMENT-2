/*
 * Hash Table for a Music Application - Division Method
 * -----------------------------------------------------
 * a) Insert song IDs using h(k) = k mod TABLE_SIZE, resolving collisions
 *    with separate chaining. Table is displayed after every insertion.
 * b) Search for a set of IDs using (i) hashing and (ii) linear search,
 *    counting comparisons for each.
 * c) Prints collision count and load factor; full analysis is in
 *    docs/complexity_analysis.md, docs/comparison_table.md and
 *    docs/conclusion.md.
 *
 * Compile : gcc -o hash_table src/hash_table.c
 * Run     : ./hash_table
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define NUM_IDS 8

typedef struct Node {
    int key;
    struct Node *next;
} Node;

Node *table[TABLE_SIZE];
int collisionCount = 0;

/* ---------- Division method hash function ---------- */
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

/* ---------- Display the whole table ---------- */
void displayTable(void) {
    printf("%-8s%-30s\n", "Index", "Bucket Contents");
    printf("------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%-8d", i);
        Node *temp = table[i];
        printf("[");
        int first = 1;
        while (temp != NULL) {
            if (!first) printf(", ");
            printf("%d", temp->key);
            first = 0;
            temp = temp->next;
        }
        printf("]\n");
    }
    printf("\n");
}

/* ---------- Insert with chaining; reports collisions ---------- */
void insert(int key) {
    int index = hashFunction(key);
    int collided = (table[index] != NULL);
    if (collided) collisionCount++;

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    if (table[index] == NULL) {
        table[index] = newNode;
    } else {
        Node *temp = table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Inserting %4d -> h(%d) = %d mod %d = %d   [%s]\n",
           key, key, key, TABLE_SIZE, index,
           collided ? "COLLISION" : "No collision");
    displayTable();
}

/* ---------- Search using hashing ----------
 * comparisons = 1 (computing the hash / jumping to the bucket)
 *             + 1 per key checked inside that bucket
 */
int searchHash(int key, int *outIndex, int *outComparisons) {
    int comparisons = 1;
    int index = hashFunction(key);
    Node *temp = table[index];
    while (temp != NULL) {
        comparisons++;
        if (temp->key == key) {
            *outIndex = index;
            *outComparisons = comparisons;
            return 1;
        }
        temp = temp->next;
    }
    *outIndex = index;
    *outComparisons = comparisons;
    return 0;
}

/* ---------- Plain linear search over the original array ---------- */
int linearSearch(int arr[], int n, int key, int *outIndex, int *outComparisons) {
    int comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == key) {
            *outIndex = i;
            *outComparisons = comparisons;
            return 1;
        }
    }
    *outIndex = -1;
    *outComparisons = comparisons;
    return 0;
}

int main(void) {
    int songIDs[NUM_IDS] = {105, 210, 315, 420, 525, 630, 735, 840};

    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    printf("==================================================================\n");
    printf("PART A: INSERTION USING DIVISION METHOD  (table size m = %d)\n", TABLE_SIZE);
    printf("==================================================================\n");

    for (int i = 0; i < NUM_IDS; i++) {
        insert(songIDs[i]);
    }

    double loadFactor = (double) NUM_IDS / TABLE_SIZE;

    printf("Total collisions during insertion : %d\n", collisionCount);
    printf("Load factor (alpha = n / m)        : %.2f\n\n", loadFactor);

    printf("==================================================================\n");
    printf("PART B: SEARCH COMPARISON - HASHING vs LINEAR SEARCH\n");
    printf("==================================================================\n");

    int searchIDs[] = {420, 735, 999, 105};
    int numSearches = 4;

    printf("%-8s%-12s%-12s%-14s%-12s\n",
           "Key", "HashFound", "HashComp", "LinearFound", "LinearComp");
    printf("----------------------------------------------------------\n");

    int totalHashComp = 0, totalLinearComp = 0;

    for (int i = 0; i < numSearches; i++) {
        int key = searchIDs[i];
        int hIndex, hComp, lIndex, lComp;

        int foundHash   = searchHash(key, &hIndex, &hComp);
        int foundLinear = linearSearch(songIDs, NUM_IDS, key, &lIndex, &lComp);

        totalHashComp   += hComp;
        totalLinearComp += lComp;

        printf("%-8d%-12s%-12d%-14s%-12d\n",
               key,
               foundHash   ? "True" : "False", hComp,
               foundLinear ? "True" : "False", lComp);
    }

    printf("\nAverage comparisons (Hashing)       : %.2f\n",
           (double) totalHashComp / numSearches);
    printf("Average comparisons (Linear Search) : %.2f\n",
           (double) totalLinearComp / numSearches);

    /* free allocated nodes */
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *temp = table[i];
        while (temp != NULL) {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }

    return 0;
}
