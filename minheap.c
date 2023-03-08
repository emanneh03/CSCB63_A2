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
    if (maybeIdx > 0 && maybeIdx <= heap->size) {
        return true;
    }
    return false;
}


/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex) {
    if (heap != NULL && isValidIndex(nodeIndex)) {
        int left_child = nodeIndex * 2;
        if (left_child < heap->size) {
            return left_child;
        }
    }
}

    
/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex) {
    if (heap != NULL && isValidIndex(nodeIndex)) {
        int right_child = nodeIndex * 2 + 1;
        if (right_child < heap->size) {
            return right_child;
        }
    }
}


/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex) {
    if (heap != NULL && isValidIndex(nodeIndex)) {
        int parent_node = nodeIndex/2;
        return parent_node;
    }
}


/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */
void swap(MinHeap* heap, int index1, int index2) {
    //capacity or size?
    if (heap == NULL) return;
    if (isValidIndex(index1) && isValidIndex(index2)) {
        HeapNode* temp = heap->arr[index1];
        heap->arr[index1] = heap->arr[index2];
        heap->arr[index2] = temp;
    }
}



/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex) {
    if (heap == NULL || !isValidIndex(nodeIndex)) return;
    int child_node = nodeIndex;
    while (isValidIndex(parentIdx(heap, child_node))) {
        int parent_node = parentIdx(heap, child_node);
        if (heap->arr[child_node].priority > heap->arr[parent_node]) {
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
    return heap->arr[left_child].priority < heap->arr[right_child].priority ? ++left_child : ++right_child;
}
    
    
/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap) {
    if (heap == NULL) return;
    int parent_node = heap->arr[1];
    while (isValidIndex(minIdx(heap, parent_node))) {
        int min_child = minIdx(heap, parent_node);
        if (heap->arr[min_child].priority > heap->arr[parent_node]) {
            swap(heap, parent_node, child_node);
        }
        parent_node = min_child;
    }
}


/* Doubles the capacity of minheap 'heap'.
 */
void doubleCapacity(MinHeap* heap);


/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex) {
    if (heap != NULL) {
        if (isValidIndex(nodeIndex)) {
            return heap->arr[nodeIndex]->priority;
        }
    }
}

/*********************************************************************
 * Required functions
 ********************************************************************/



/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/

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
