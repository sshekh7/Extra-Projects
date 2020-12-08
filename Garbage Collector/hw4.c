#include "memlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mm.h"

struct memory_region{
  size_t * start;
  size_t * end;
};

struct memory_region global_mem;
struct memory_region stack_mem;

void walk_region_and_mark(void* start, void* end);

// PROVIDED BY US (DO NOT CHANGE)
// ------------------------------
// grabbing the address and size of the global memory region from proc 
void init_global_range(){
  int next = 0;
  char file[100];
  char * line=NULL;
  size_t n=0;
  size_t read_bytes=0;
  size_t start, end;


  sprintf(file, "/proc/%d/maps", getpid());
  FILE * mapfile  = fopen(file, "r");
  if (mapfile==NULL){
    perror("opening maps file failed\n");
    exit(-1);
  }

  int counter=0;
  while ((read_bytes = getline(&line, &n, mapfile)) != -1) {
    // .data of hw4 executable
    if (strstr(line, "hw4") != NULL && strstr(line,"rw-p")){
      sscanf(line, "%lx-%lx", &start, &end);
      global_mem.start = (void*) start;
      global_mem.end = (void*) end;
      break;
    }

  }
  fclose(mapfile);
}

// marking related operations

int is_marked(unsigned int * chunk) {
  return ((*chunk) & 0x2) > 0;
}

void mark(unsigned int * chunk) {
  (*chunk)|=0x2;
}

void clear_mark(unsigned int * chunk) {
  (*chunk)&=(~0x2);
}

// chunk related operations

#define chunk_size(c)  ((*((unsigned int *)c))& ~(unsigned int)7 ) 
void* next_chunk(void* c) { 
  if(chunk_size(c) == 0) {
    fprintf(stderr,"Panic, chunk is of zero size.\n");
  }
  if((c+chunk_size(c)) < mem_heap_hi())
    return ((void*)c+chunk_size(c));
  else 
    return 0;
}

int in_use(void *c) { 
  return *(unsigned int *)(c) & 0x1;
}

// FOR YOU TO IMPLEMENT
// --------------------
// the actual collection code
void sweep() {
  void * chunk = mem_heap_lo(); // stores the start of heap memory
  void * next_chunk_temp; // stores specific instance of chunk in each iteration of the while loop

  // traverses the entire heap memory and performs garbage collection for marked chunks
  while((chunk  < mem_heap_hi()) && (chunk_size(chunk) > 0)){
    next_chunk_temp = next_chunk(chunk);  // stores spefcific (unchanged) instance of the chunk
    if(is_marked(chunk)) clear_mark(chunk); // if the chunk is marked, it unmarks the chunk using the utility function
    else if (in_use(chunk)) mm_free(chunk+4); // if allocated, mm_free memory
    chunk = next_chunk_temp; // goes (traverses) to the header of the next chunk which was stored earlier
  } // while ends
} // sweep ends

// determine if what "looks" like a pointer actually points to an 
// in use block in the heap. if so, return a pointer to its header 
void * is_pointer(void * ptr) {
  // Here's a helpful print statement that shows some available memory operations and working with pointers
  // printf("checking for pointeryness of %p between %p and %p\n",ptr, mem_heap_lo(), mem_heap_hi());
  // DONE

  // check if the passed in pointer is in the heap or not
  if(ptr < mem_heap_lo() || ptr > mem_heap_hi()) return NULL;


  void * temp = mem_heap_lo(); // stores the start address of the heap memory
  void * next_temp; // stores spefcific (unchanged) instance of the chunk
  while(temp < mem_heap_hi() && chunk_size(temp) > 0) // while in range
  {
    next_temp = next_chunk(temp); // stores spefcific (unchanged) instance of the chunk

    // If we hit that specific chunk where ptr is located
    if(temp <= ptr && ptr < next_temp){  
      if(chunk_size(temp) != 0 && in_use(temp)) return temp;     // if allocated, the return 
      else return NULL;
    }
    temp = next_temp; // if does not find ptr in current chunk, moves to the next chunk in the heap
  }
  return NULL;
}

// walk through memory specified by function arguments and mark
// each chunk
void walk_region_and_mark(void* start, void* end) {
  //fprintf(stderr, "walking %p - %p\n", start, end);
  // TODO

  // Taken the special value of (end - 8) because in each recursive iteration, the value goes till +8 of the current value in used,
  // So to avoid seg fault while traversing entire list, meanwhile checking each ptr for allocation in the heap, is the function of this while loop.
  while(start < end - 8){
    void * temp = is_pointer((void*)*(size_t*)start); // stores specific instance of the chunk.
    if(temp == NULL) { start += 4; continue;} // if the chunk is not allocated in the heap, move ahead (start += 4)
    if(is_marked(temp)) { start += 4; continue;} // if the chunk is already marked in the heap, move head (start += 4)
    mark(temp); // mark the current chunk
    walk_region_and_mark(temp + 4, temp + chunk_size(temp)); // recursive call with new changed parameter to traverse the payload and mark them
    start += 4; 
  }
}

// PROVIDED BY US (DO NOT CHANGE)
// ------------------------------
// standard initialization 

void init_gc() {
  size_t stack_var;
  init_global_range();
  // since the heap grows down, the end is found first
  stack_mem.end=(size_t *)&stack_var;
}

void gc() {
  size_t stack_var;
  // grows down, so start is a lower address
  stack_mem.start=(size_t *)&stack_var;
  // walk memory regions
  walk_region_and_mark(global_mem.start,global_mem.end);
  walk_region_and_mark(stack_mem.start,stack_mem.end);
  sweep();
}
