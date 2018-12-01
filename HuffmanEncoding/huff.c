// code for a huffman coder

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "huff.h"
#include "bitfile.h"
#define EOT 4

//int compoundSequenceNumber =NUM_CHARS;	
// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
	struct huffcoder*result;
	result = malloc(sizeof(struct huffcoder));
   	 return result;

};


// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
    FILE*file = fopen(filename,"r");
    char item;
    do{
     item = getc(file);
	this->freqs[(int)item]++;
	//printf("char:%c freq:%d\n", item,(this->freqs)[(int)item]);
    }while(item!=EOF);

    int i;
    for(i=0;i<NUM_CHARS;i++){
        if(this->freqs[i]==0){
            this->freqs[i]=1;
        }
    }
   fclose(file);

}



//This function creates a huffchar structure
struct huffchar *  huffchar_new(unsigned char c,int freq)
{
	struct huffchar*result;
	result = malloc(sizeof(struct huffchar));
	result->u.c = c;
	result->freq = freq;
	result->is_compound =0;
	result->seqno = (int)c;
    return result;

};

//This function creates another huffchar compound structure it adds the frequencies together and adds a sequence number.
struct huffchar *  huffchar_compound(struct huffcoder*this,struct huffchar* numberOne,struct huffchar* numberTwo,int seqno){
	struct huffchar*result = malloc(sizeof(struct huffchar));
	result->freq = (numberOne->freq +numberTwo->freq);
	result->seqno =seqno;
	result->is_compound=1;
	result->u.compound.left = numberOne;
	result->u.compound.right = numberTwo;
	return result;
};

//This function finds the minimum frequency in the array
int getLowestFrequencyIndex(struct huffchar*rootNodes[NUM_CHARS]){
	int min_freq = 1000000000;
	int min_seq = 0;
	int min_index = -1;
	int i;
	for(i=0;i<NUM_CHARS;i++){
		if(rootNodes[i] !=NULL){
			if(rootNodes[i]->freq <min_freq){
				min_freq = rootNodes[i]->freq;
				min_seq = rootNodes[i]->seqno;
				min_index =i;
			}else if(rootNodes[i]->freq==min_freq){
				if(rootNodes[i]->seqno <min_seq){
					min_freq = rootNodes[i]->freq;
					min_seq = rootNodes[i]->seqno;
					min_index =i;
				
				}
			}
		}
	}
	return min_index;
} 


int getNumberNodes(struct huffchar**rootNodes) {
	int count=0;
	for(int i=0;i<NUM_CHARS;i++){
		if(rootNodes[i]!=NULL){
			count++;
		}
	}
	return count;
}

//using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
	struct huffchar*rootNodes[NUM_CHARS];
	for(int i=0;i<NUM_CHARS;i++){
		rootNodes[i]= huffchar_new((char)i,this->freqs[i]);
	}
	int num_Nodes=NUM_CHARS;
	for(int i=0;i<NUM_CHARS-1;i++){
		struct huffchar*new_node;	
		struct huffchar*new_nodeT;
		struct huffchar*compound;
		int numberOne = getLowestFrequencyIndex(rootNodes);
		new_node = rootNodes[numberOne];	
		rootNodes[numberOne]=NULL;

		int numberTwo = getLowestFrequencyIndex(rootNodes);
		new_nodeT = rootNodes[numberTwo];	
		rootNodes[numberTwo]=NULL;

		compound=huffchar_compound(this,new_node,new_nodeT,num_Nodes);
		num_Nodes++;
		rootNodes[numberOne]=compound;	

	}
	
	int compound_index;
	for(int i=0;i<NUM_CHARS;i++){
	if(rootNodes[i]!=NULL){
		compound_index =i;
		break;
	}
	}
	this->tree=rootNodes[compound_index];

}


// recursive function to convert the Huffman tree into a table of
// Huffman codes
void tree2table_recursive(struct huffcoder * this, struct huffchar * node,unsigned int path, int depth)
{
	if(node->is_compound){
		path = path<<1;
		tree2table_recursive(this,node->u.compound.left,path,depth+1);
		path = path|1;
		tree2table_recursive(this,node->u.compound.right,path,depth+1);
	}else{
		unsigned char index = node->u.c;
		this->codes[index]=path;
		this->code_lengths[index]=depth;
		
	}
		

}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
	tree2table_recursive(this,this->tree,0,0);
}


void write_EOT(struct bitfile*filename,struct huffcoder * this){
	int code_eot = this->codes[EOT];
	int codeL_eot = this->code_lengths[EOT];
	for(int i=0;i<codeL_eot;i++){
		int bit = (( code_eot >> (codeL_eot-i-1)) & 1);
		bitfile_write_bit(filename,bit);
	}
}

// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for ( i = 0; i < NUM_CHARS; i++ ) {
    // put the code into a string
    for ( j =0;j< this->code_lengths[i]; j++) {
      buffer[j] = ((this->codes[i] >> (this->code_lengths[i]-j-1)) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';

    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);;
}
}




// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,char * output_filename)
{

	FILE*rfile = fopen(input_filename,"r");
	struct bitfile*wfile = bitfile_open(output_filename,"w");
	wfile->buffer=0;
	unsigned char item;
	while(!feof(rfile)){
		item = fgetc(rfile);
		int code = this->codes[(int)item];
		int codeL = this->code_lengths[(int)item];
		if(code==this->codes[255]){
			break;
		}
		for(int j=0;j<codeL;j++){	
			int bit = (( code >> (codeL-j-1)) & 1);
			bitfile_write_bit(wfile,bit);
		}	
	}
		
	write_EOT(wfile,this);
	bitfile_close(wfile);
}



// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,char * output_filename)
{
	
	struct bitfile*rfile = bitfile_open(input_filename,"r");
	FILE*file = fopen(output_filename,"w");
	struct huffchar*ptr =this->tree;
	int finished=0;
	unsigned char item;
	//getting the first character from the file because the index is not full;
	rfile->buffer =fgetc(rfile->file);
	while(!finished){
		while(ptr->is_compound==1){
		int bit = bitfile_read_bit(rfile);
		  if(bit==0){
		   ptr= ptr->u.compound.left;
		  }else if(bit==1){
                  ptr= ptr->u.compound.right;
		  } 	
		}	
		 //check if the character is equal to eot.	
		  item =ptr->u.c;
		  if((int)item ==4){
			finished=1;
		  }else{
		   fputc(item,file);
		   ptr=this->tree;
          }
		   
	}	
	
}

