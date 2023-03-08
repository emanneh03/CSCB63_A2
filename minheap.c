/*
 * Our min-heap implementation.
 *
 * Author (starter code): A. Tafliovich.
 */

#include "minheap.h"

#define ROOT_INDEX 1
#define NOTHING -1

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Returns True if 'maybeIdx' is a valid index in minheap 'heap', and 'heap'
 * stores an element at that index. Returns False otherwise.
 */
bool isValidIndex(MinHeap* heap, int maybeIdx) {
    if (heap != NULL) {
        if (maybeIdx > 0 && maybeIdx <= heap->size) {
            return true;
        }
    }
    return false;
}


/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex) {
    if (heap != NULL) {
        if (isValidIndex(heap, nodeIndex)) {
            return heap->arr[nodeIndex].priority;
        }
    }
}


/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex) {
    if (heap == NULL) return NOTHING;
    int left_child = nodeIndex * 2;
    if (isValidIndex(heap, left_child)) {
        return left_child;
    }
    return NOTHING;
}


/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex) {
    if (heap == NULL) return NOTHING;
    int right_child = nodeIndex * 2 + 1;
    if (isValidIndex(heap, right_child)) {
        return right_child;
    }
    return NOTHING;
}


/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex) {
    if (heap == NULL) return NOTHING;
    int parent_node = nodeIndex/2;
    if (isValidIndex(heap, parent_node)) {
        return parent_node;
    }
    return NOTHING;
}


/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */
void swap(MinHeap* heap, int index1, int index2) {
    //capacity or size?
    if (heap == NULL) return;
    if (isValidIndex(heap, index1) && isValidIndex(heap, index2)) {
        //pointer?
        HeapNode temp = heap->arr[index1];
        heap->arr[index1] = heap->arr[index2];
        heap->arr[index2] = temp;
    }
}



/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex) {
    if (heap == NULL || !isValidIndex(heap, nodeIndex)) return;
    int child_node = nodeIndex;
    while (isValidIndex(heap, parentIdx(heap, child_node))) {
        int parent_node = parentIdx(heap, child_node);
        if (priorityAt(heap, child_node) < priorityAt(heap, parent_node)) {
            swap(heap, parent_node, child_node);
        }
        child_node = parent_node;
    }
}


/* Returns the the index of the child with the minimum priority.
 */
int minIdx(MinHeap* heap, int parent_node) {
    int left_child = leftIdx(heap, parent_node);
    int right_child = rightIdx(heap, parent_node);
    return priorityAt(heap, left_child) < priorityAt(heap, right_child) ? ++left_child : ++right_child;
}


/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap) {
    if (heap == NULL) return;
    int parent_node = ROOT_INDEX;
    while (isValidIndex(heap, minIdx(heap, parent_node))) {
        int min_child = minIdx(heap, parent_node);
        if (priorityAt(heap, min_child) > priorityAt(heap, parent_node)) {
            swap(heap, parent_node, min_child);
        }
        parent_node = min_child;
    }
}


/* Doubles the capacity of minheap 'heap'.
 */
void doubleCapacity(MinHeap* heap) {
    int capacity = heap->capacity * 2;
    heap->capacity = capacity;
    heap->arr = realloc(heap->arr, (capacity + ROOT_INDEX) * sizeof(HeapNode));
    heap->indexMap = realloc(heap->indexMap, (capacity + ROOT_INDEX) * sizeof(int));
}


/*********************************************************************
 * Required functions
 ********************************************************************/

/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap) {
    if (heap != NULL) {
        return heap->arr[ROOT_INDEX];
    }
}


/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap) {
    if (heap != NULL) {
        HeapNode min_node = getMin(heap);
        swap(heap, ROOT_INDEX, heap->size);
        heap->size--;
        bubbleDown(heap);
        return min_node;
    }
}


/* Inserts a new node with priority 'priority' and value 'value' into minheap
 * 'heap'. If 'heap' is full, double the capacity of 'heap' before inserting
 * the new node.
 */
void insert(MinHeap* heap, int priority, void* value) {
    if (heap != NULL) {
        if (heap->size == heap->capacity) doubleCapacity(heap);
        int id = heap->size;
        heap->size++;
        heap->arr[heap->size].priority = priority;
        heap->arr[heap->size].value = value;
        heap->arr[heap->size].id = heap->size;
        heap->indexMap[heap->size] = priorityAt(heap, heap->size);
        bubbleUp(heap, heap->size);
    }
}


/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority) {
    if (heap != NULL) {
        int index = heap->indexMap[id];
        if (isValidIndex(heap, index) && priorityAt(heap, index) > newPriority) {
            heap->arr[index].priority = newPriority;
            bubbleUp(heap, index);
            return true;
        }//change id
    }
    return false;
}


/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity > 0
 */
MinHeap* newHeap(int capacity) {
    if (capacity <= 0) return NULL;
    MinHeap* heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (HeapNode *)malloc((capacity + ROOT_INDEX) * sizeof(HeapNode));
    heap->indexMap = (int *)malloc((capacity + ROOT_INDEX) * sizeof(int));
    return heap;
}


/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap) {
    if (heap == NULL) return;
    free(heap->arr);
    free(heap->indexMap);
    free(heap);
}


/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/

/* Prints the contents of this heap, including size, capacity, full index
 * map, and, for each non-empty element of the heap array, that node's ID and
 * priority. */
void printHeap(MinHeap* heap) {
    printf("MinHip with size: %d\n\tcapacity: %d\n\n", heap->size,
           heap->capacity);
    printf("index: priority [ID]\t ID: index\n");
    for (int i = ROOT_INDEX; i <= heap->size; i++)
        printf("%d: %d [%d]\t\t%d: %d\n", i, heap->arr[i].priority, heap->arr[i].id,
               i, heap->indexMap[i]);
    for (int i = heap->size + 1; i <= heap->capacity; i++)
        printf("\t\t\t%d: %d\n", i, heap->indexMap[i]);
    printf("\n\n");
}


/*********************************************************************
 ** Helper functions not provided in the starter code
 *********************************************************************/
