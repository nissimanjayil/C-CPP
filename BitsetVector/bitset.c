#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "bitset.h"

/*struct bitset{
    int size_in_int;
    int size_in_word;
    int bits;
    unsigned int *ptr;
};*/

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size){
    struct bitset*result;
    int size_in_word;
    int bits;
    result = malloc(sizeof(struct bitset));
    bits = (sizeof(unsigned int)*8);
    size_in_word = size/(sizeof(unsigned int)*8);
    if((sizeof(unsigned int )*8)!=0){
        size_in_word++;
    }
    result->ptr = malloc(sizeof(unsigned int )*size_in_word);
    for(int i=0;i<size_in_word;i++){
        result->ptr[i]=0;
    }
    result->bits = bits;
    result->size_in_int = size;
    result->size_in_word = size_in_word;
    return result;
};

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this){
     int size_of_the_set;
     size_of_the_set = this->size_in_int;
   //printf("%d",size_of_the_set);
    return size_of_the_set;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int count =0;
    for(int i=0;i<this->size_in_int;i++){
        if((this->ptr[i]&=1<<(i)) >0 ){
            count++;
        }
    }
    return count;
}

// check to see if an item is in the set
//This functions left shifts 1 into the place of the desired bit, AND it with the number, if it is >0 then the desired bit is 1
int bitset_lookup(struct bitset * this, int item){
    if(item >=0 && item < this->size_in_int){
        int i = item/this->bits;
        int j = item%this->bits;
        if((this->ptr[i]&1<<(j)) > 0){
            return 1;
        }
    }
    return 0;

}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
//OR for adding an item
int bitset_add(struct bitset * this, int item){
    if(item >= 0 && item < this->size_in_int){
        int i = item / this->bits;
        int j = item % this->bits;
        int mask = 1<<(j);
        this->ptr[i] |= mask;
        return 1;
    }
    else{
        return 0;
    }

}

// remove an item with number 'item' from the set
//
int bitset_remove(struct bitset * this, int item){
    if(item >= 0 && item < this->size_in_int){
        int i = item / this->bits;
        int j = item % this->bits;
        int mask = 1<<(j);
        mask = ~mask;   // sets all bits to 1 except the desired bit
        this->ptr[i] &= mask;
        return 1;
    }
    else{
        return 0;
    }
}
// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2){
    assert(src1->size_in_int == src2->size_in_int);
    assert(src1->size_in_int == dest->size_in_int);
    for(int i=0;i < src1->size_in_word;i++){ //To find the union of the set use OR
        dest->ptr[i] = src1->ptr[i] | src2->ptr[i];
    }
}
// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2){
    assert(src1->size_in_int == src2->size_in_int);
    assert(src1->size_in_int == dest->size_in_int);
    for(int i=0;i < src1->size_in_word;i++){  //To find the intersection of the set use AND
        dest->ptr[i] = src1->ptr[i] & src2->ptr[i];
    }
}


// print the contents of the bitset
void bitset_print(struct bitset * this)
{
  int i;
  int size = bitset_size(this);
  for ( i = 0; i < size; i++ ) {
    if ( bitset_lookup(this, i) == 1 ) {
      printf("%d ", i);
    }
  }
  printf("\n");
}
 

