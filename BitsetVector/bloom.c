#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bloom.h"

const int BLOOM_HASH1 = 17;
const int BLOOM_HASH2 = 29;

// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char * string, int seed, int range)
{
  int i;
  int hash = 0;

  // simple loop for mixing the input string
  for ( i = 0; string[i] != '\0'; i++ ) {
    hash = hash * seed + string[i];
  }
  // check for unlikely case that hash is negative
  if ( hash < 0 ) {
    hash = -hash;
  }
  // bring the hash within the range 0..range-1
  hash = hash % range;

  return hash;
}

// create a new, empty Bloom filter with 'size' slots
struct bloom * bloom_new(int size)
{
	struct bloom*result;
	//int bits;
	int size_in_word;
	result = malloc(sizeof(struct bloom));
	result->ptr = malloc(sizeof(unsigned int));
	size_in_word = size/(sizeof(unsigned int )*8);
	//bits = (sizeof(unsigned int)*8);
    	if((sizeof(unsigned int )*8)!=0){
        size_in_word++;
    	}
    	result->ptr = malloc(sizeof(unsigned int)*size_in_word);
    	for(int i=0;i<size_in_word;i++){
        result->ptr[i]=0;
    	}
    	//result->bits = bits;
    	result->size= size;
   	result->size_in_word = size_in_word;
   	return result;
		
	
}


// check to see if a string is in the set
int bloom_lookup(struct bloom * this, char * item)
{
    int range =this-> size;
    int item1 = hash_string(item,BLOOM_HASH1,range);
    int item2 =hash_string(item,BLOOM_HASH2,range);
    if(this->ptr[item1]==1 && this->ptr[item2]==1){
	return 1;
    }
    return 0;
   
}

// add a string to the set has no effect if the item is already in the
// set; note that you cannot safely remove items from a Bloom filter
void bloom_add(struct bloom * this, char * item)
{
    int range =this-> size;
    int item1 = hash_string(item,BLOOM_HASH1,range);
    int item2 =hash_string(item,BLOOM_HASH2,range);
    assert((item1>=0 &&item1<this->size)==(item2>=0 &&item2<this->size));
    this->ptr[item1]=1;
    this->ptr[item2]=1;
  
}

// place the union of src1 and src2 into dest
void bloom_union(struct bloom * dest, struct bloom * src1,struct bloom * src2)
{
    assert( src1->size ==  src2->size);
    for(int i=0;i < src1->size;i++){ //To find the union of the set use OR
        if( src1->ptr[i]==1 | src2->ptr[i]==1){
		dest->ptr[i]=1;
	}
    }
}

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1,struct bloom * src2)
{
    assert(src1->size ==  src2->size);
    for(int i=0;i < src1->size;i++){ //To find the union of the set use OR
        if( src1->ptr[i]==1 &&  src2->ptr[i]==1){
		dest->ptr[i]=1;
	}
    }

}

int bloom_lookupS(struct bloom*this,int item){
	if(this->ptr[item]==1){
		return 1;
	}
	return 0;
}




// print the contents of the bitset
void bloom_print(struct bloom * this)
{
  int i;
  int size = this->size;
  for ( i = 0; i < size; i++ ) {
    if ( bloom_lookupS(this, i) == 1 ) {
      printf("%d ", i);
    }
  }
  printf("\n");
}









