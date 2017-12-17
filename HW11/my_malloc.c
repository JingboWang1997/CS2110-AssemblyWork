/*
 * CS 2110 Spring 2017
 * Author: Jingbo Wang
 */
#include <stdio.h>
/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this for my_sbrk */
#include "my_sbrk.h"
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* This is the size of the metadata struct and canary footer in bytes */
#define TOTAL_METADATA_SIZE (sizeof(metadata_t) + sizeof(int))

/* This is the minimum size of a block in bytes, where it can
 * store the metadata, canary footer, and at least 1 byte of data
 */
#define MIN_BLOCK_SIZE (TOTAL_METADATA_SIZE + 1)

/* Used in canary calcuations. See the "Block Allocation" section of the
 * homework PDF for details.
 */
#define CANARY_MAGIC_NUMBER 0xE629

/* Feel free to delete this (and all uses of it) once you've implemented all
 * the functions
 */
#define UNUSED_PARAMETER(param) (void)(param)

static metadata_t *insert(metadata_t *list, metadata_t *item);

/* Our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t *freelist;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See my_malloc.h for documentation
 */
void *my_malloc(size_t size) {
	//special cases
    if (size >= SBRK_SIZE)
    {
    	my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
    	return NULL;
    }
    if (size == 0) 
    {
    	my_malloc_errno = NO_ERROR;
    	return NULL;
    }

    //initialize
    if (freelist == NULL)
    {
    	freelist = my_sbrk(SBRK_SIZE);
    	if (freelist == NULL)
    	{
    		my_malloc_errno = OUT_OF_MEMORY;
    		return NULL;
    	}
    	freelist->next = NULL;
    	freelist->size = SBRK_SIZE;
    }

    //actual size needed
    size_t realSize = size + TOTAL_METADATA_SIZE;

    //traverse freelist
    metadata_t *previous = NULL;
    metadata_t *freeCur = freelist;
    while (freeCur != NULL)
    {
    	if (freeCur->size == realSize)
    	{
    		//remove
    		metadata_t *raw = freeCur;
    		metadata_t *next = raw->next;
    		raw->next = NULL;
    		if (previous != NULL)
    		{
    			//previous exists
    			previous->next = next;

    		}
    		else
    		{
    			//freeCur is the head of freelist
    			freelist = next;
    		}
    		//removed from list

    		//set up raw
    		raw->canary = ((uintptr_t)raw ^ CANARY_MAGIC_NUMBER) - raw->size;
    		unsigned int *tailCanary = (unsigned int *)(((uint8_t *)raw + raw->size) - sizeof(int));
    		*tailCanary = raw->canary;

    		//give pointer to user
    		my_malloc_errno = NO_ERROR;
    		return (uint8_t *)raw + sizeof(metadata_t);
    	}
    	else if (freeCur->size >= realSize+MIN_BLOCK_SIZE)
    	{
    		//cast pointer with (uint8_t *)
    		//split
    		metadata_t *raw = freeCur;
    		metadata_t *next = raw->next;
    		metadata_t *leftOver = (metadata_t *)((uint8_t *)raw + realSize);
    		leftOver->size = raw->size - realSize;
    		leftOver->next = next;

    		raw->size = realSize;
    		raw->next = NULL;

    		//remove
    		if (previous != NULL)
    		{
    			//previous exists
    			previous->next = leftOver;

    		}
    		else
    		{
    			//freeCur is the head of freelist
    			freelist = leftOver;
    		}

    		//set up
    		raw->canary = ((uintptr_t)raw ^ CANARY_MAGIC_NUMBER) - raw->size;
    		unsigned int *tailCanary = (unsigned int *)(((uint8_t *)raw + raw->size) - sizeof(int));
    		*tailCanary = raw->canary;

    		//organize free list (move left over to front)
    		//	previous->leftOver->next

    		//check if already at beginning and if smaller than previous
    		if (previous != NULL && previous->size > leftOver->size) 
    		{
    			//take out leftOver from the list
	    		previous->next = next;
	    		leftOver->next = NULL;

	    		//set up traversal
	    		//goal: cur is the first bigger than leftOver
	    		//		insert in front of cur
    			insert(freelist, leftOver);
    		}

    		//give pointer to user
    		my_malloc_errno = NO_ERROR;
    		return (uint8_t *)raw + sizeof(metadata_t);
    	}
    	previous = freeCur;
    	freeCur = freeCur->next;
    }

    //traverse again for special condition
    metadata_t *newPrevious = NULL;
    metadata_t *newFreeCur = freelist;
    while (newFreeCur != NULL)
    {
    	if (newFreeCur->size > realSize && newFreeCur->size < realSize+MIN_BLOCK_SIZE)
    	{
    		//remove
    		metadata_t *raw = newFreeCur;
    		metadata_t *next = raw->next;

    		realSize = raw->size;

    		raw->next = NULL;
    		if (newPrevious != NULL)
    		{
    			//previous exists
    			newPrevious->next = next;

    		}
    		else
    		{
    			//freeCur is the head of freelist
    			freelist = next;
    		}

    		//set up with some extra space in body
    		raw->canary = ((uintptr_t)raw ^ CANARY_MAGIC_NUMBER) - raw->size;
    		unsigned int *tailCanary = (unsigned int *)(((uint8_t *)raw + raw->size) - sizeof(int));
    		*tailCanary = raw->canary;

    		//give pointer to user
    		my_malloc_errno = NO_ERROR;
    		return (uint8_t *)raw + sizeof(metadata_t);
    	}
    	newPrevious = newFreeCur;
    	newFreeCur = newFreeCur->next;
    }

    //no space left, call sbrk again and add it to freelist (merge if need to)
    //set up
    metadata_t *newSpace = my_sbrk(SBRK_SIZE);
    if (newSpace == NULL)
    {
    	my_malloc_errno = OUT_OF_MEMORY;
    	return NULL;
    }
    newSpace->next = NULL;
    newSpace->size = SBRK_SIZE;

    //put in the list
    //check if can merge with anyone
    metadata_t *mergePrev = NULL;
    metadata_t *mergeCur = freelist;
    int merged = 0;
    while (mergeCur != NULL && !merged)
    {
    	if ((uint8_t *)mergeCur + mergeCur->size == (uint8_t *)newSpace)
    	{
    		//mergeCur | newSpace
    		mergeCur->size += newSpace->size;
    		merged = 1;

    		//move mergeCur back if possible
    		//make sure mergeCur is not the end of list and is bigger than the next
    		if (mergeCur->next != NULL && mergeCur->size > mergeCur->next->size)
    		{
    			//take out mergeCur from the list
    			//mergePrev->mergeCur->(mergeCur->next)
    			if (mergePrev == NULL)
    			{
    				//mergeCur is the head
    				freelist = mergeCur->next;
    				mergeCur->next = NULL;
    			}
    			else
    			{
    				mergePrev->next = mergeCur->next;
    				mergeCur->next = NULL;
    			}

	    		//set up traversal
	    		//goal: cur is the first bigger than leftOver
	    		//		insert in front of cur

    			freelist = insert(freelist, mergeCur);
    		}
    	}
    	// else if ((uint8_t *)newSpace + newSpace->size == (uint8_t *)mergeCur)
    	// {
    	// 	//newSpace | mergeCur
    	// 	newSpace->size += mergeCur->size;
    	// 	newSpace->next = mergeCur->next;
    	// 	if (mergePrev != NULL)
    	// 	{
    	// 		//previous exists
    	// 		mergePrev->next = newSpace;
    	// 	}
    	// 	else
    	// 	{
    	// 		//previous is head pointer
    	// 		freelist = newSpace;
    	// 	}
    	// 	merged = 1;

    	// 	//move newSpace back if possible
    	// }
    	mergePrev = mergeCur;
    	mergeCur = mergeCur->next;
    }


    if (!merged)
    {
    	//not merged, append to tail
    	metadata_t *tail =mergePrev;
    	tail->next = newSpace;
    }

    //go again
    return my_malloc(size);
}

/* REALLOC
 * See my_malloc.h for documentation
 */
void *my_realloc(void *ptr, size_t size) {
	//edge case
    if (ptr == NULL)
    {
    	return my_malloc(size);
    }
    if (size == 0 && ptr != NULL)
    {
    	my_free(ptr);
    	return NULL;
    }

    //get size of old
    metadata_t *item =  (metadata_t *)((uint8_t *)ptr - sizeof(metadata_t));
    unsigned int actualDataSize = item->size - TOTAL_METADATA_SIZE;

    //check canary
    if (item->canary != ((uintptr_t)item ^ CANARY_MAGIC_NUMBER) - item->size)
    {
    	my_malloc_errno = CANARY_CORRUPTED;
    	return NULL;
    }
    else if (*(unsigned int *)(((uint8_t *)item + item->size) - sizeof(int)) != item->canary)
    {
    	my_malloc_errno = CANARY_CORRUPTED;
    	return NULL;
    }

    //malloc new block
    metadata_t *result = my_malloc(size);

    //copy data in according to the shortest length of the new and the old
    if (actualDataSize >= size)
    {
    	//shrink
    	memcpy(result, ptr, size);
    }
    else
    {
    	//expand
    	memcpy(result, ptr, actualDataSize);
    }
    

    //free old
    my_free(ptr);

    //return new
    return result;
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    void *result = my_malloc(nmemb * size);
    if (result == NULL)
    {
    	return NULL;
    }
    result = memset(result, 0, nmemb * size);
    return result;
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void *ptr) {
    if (ptr == NULL)
    {
    	my_malloc_errno = NO_ERROR;
    	return;
    }

    metadata_t *item = (metadata_t *)((uint8_t *)(ptr) - sizeof(metadata_t));

    //check canary
    if (item->canary != ((uintptr_t)item ^ CANARY_MAGIC_NUMBER) - item->size)
    {
    	my_malloc_errno = CANARY_CORRUPTED;
    	return;
    }
    else if (*(unsigned int *)(((uint8_t *)item + item->size) - sizeof(int)) != item->canary)
    {
    	my_malloc_errno = CANARY_CORRUPTED;
    	return;
    }

    //check if can merge with anyone in the freelist
    //check merge right
    //item | curR
    metadata_t *prevR = NULL;
    metadata_t *curR = freelist;
    int mergedR = 0;
    while (curR != NULL && !mergedR)
    {
    	if ((uint8_t *)item + item->size == (uint8_t *)curR)
    	{
    		//found
    		//merge and take out
    		item->size += curR->size;
    		if (prevR == NULL)
    		{
    			//curR is head
    			freelist = curR->next;
    		}
    		else
    		{
    			prevR->next = curR->next;
    		}
    		curR->next = NULL;
    		mergedR = 1;
    	}
    	prevR = curR;
    	curR = curR->next;
    }

    //check merge left
    //curL | item
    //(uint8_t *)mergeCur + mergeCur->size == (uint8_t *)newSpace
    metadata_t *prevL = NULL;
    metadata_t *curL = freelist;
    int mergedL = 0;
    while (curL != NULL && !mergedL)
    {
    	if ((uint8_t *)curL + curL->size == (uint8_t *)item)
    	{
    		//found
    		//merge and take out
    		curL->size += item->size;
    		if (prevL == NULL)
    		{
    			//curL is head
    			freelist = curL->next;
    		}
    		else
    		{
    			prevL->next = curL->next;
    		}
    		curL->next = NULL;
    		mergedR = 1;
    		item = curL;
    	}
    	prevL = curL;
    	curL = curL->next;
    }

    freelist = insert(freelist, item);
    my_malloc_errno = NO_ERROR;
    return;
}

static metadata_t *insert(metadata_t *list, metadata_t *item) {
	if (list == NULL)
	{
		item->next = NULL;
		return item;
	}
	metadata_t *result = list;
	//set up traversal
	//goal: cur is the first bigger than item
	//		insert in front of cur
	metadata_t *prev = NULL;
	metadata_t *cur = list;
	int found = 0;
	while (cur != NULL && !found)
	{
		if (cur->size > item->size)
		{
			//found the position 
			//prev->cur
			//prev->item->cur
			if (prev == NULL)
			{
				//cur is the head
				item->next = cur;
				result = item;
				found = 1;
			}
			else
			{
				prev->next = item;
				item->next = cur;
				found = 1;
			}
		}
		prev = cur;
		cur = cur->next;
	}

	if (!found)
	{
		//insert in the end
		metadata_t *tail = prev;
		tail->next = item;
		item->next = NULL;
	}
	return result;
}