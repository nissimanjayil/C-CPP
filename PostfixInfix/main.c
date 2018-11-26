#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

/* Open a file. Abort progam if file cannot be opened */
FILE * open_file(char filename[])
{
  FILE * file;

  file = fopen(filename, "r");
  if ( file == NULL ) {
    printf("FATAL: Error opening file %s. Aborting program.\n", filename);
    exit(1);
  }

  return file;
}

/* read a stream of up to 'size' integers from a text file.
   return number of integers */
void read_in(int a[], int size, char filename[], char* line)
{
  const int max_line = 1024;
  int i;
  FILE * file;
  char * eof;
  file = open_file(filename);
  i = 0;
  eof = fgets(line, max_line, file);
    i++;
  fclose(file);

}

void write_out(int a[], int size)
{
  int i;

  for ( i = 0; i < size; i++ ) {
   // printf("%d\n", a[i]);
  }
}

//Creates a node with integer as the data.
struct node
{
    int data;
    struct node* next;
};

//Creates a node but with character as the data
struct nodeChar
{
    char item;
    struct nodeChar*next_Two;
};

//initialises the head of each of the node.
void init(struct node* head,struct nodeChar*head_Two)
{
    head = NULL;
    head_Two = NULL;
}


//Push operation for the integer data
struct node* push(struct node* head,int data)
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    if(tmp == NULL)
    {
        exit(0);
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    return head;
}

//pushOperation for the character data
struct nodeChar* pushChar(struct nodeChar*head_Two,char item){
    struct nodeChar*tmp = (struct nodeChar*)malloc(sizeof(struct nodeChar));
    if(tmp == NULL){
        exit(0);
    }
    tmp->item = item;
    tmp->next_Two = head_Two;
    head_Two = tmp;
    return head_Two;

};

//Pop operation
struct nodeChar popChar(struct nodeChar*head_Two){
     int retVal = -1;
    struct nodeChar*next_node = NULL;
    if(head_Two == NULL){
        struct nodeChar emptyValue;
        emptyValue.item = 0;
        emptyValue.next_Two=NULL;
        return emptyValue;
    }
    struct nodeChar newValue;
    newValue.item = head_Two->item;
    newValue.next_Two= head_Two->next_Two;
    free(head_Two);
    return newValue;

};

//Pop operation which finds the peek value
struct nodeChar peekChar(struct nodeChar*head_Two){
    int retVal = -1;
    struct nodeChar*next_node = NULL;
    if(head_Two == NULL){
        struct nodeChar emptyValue;
        emptyValue.item = 0;
        emptyValue.next_Two=NULL;
        return emptyValue;
    }
    struct nodeChar newValue;
    newValue.item = head_Two->item;
    newValue.next_Two= head_Two;
    return newValue;

};



//pop operation for the integer data
struct node pop(struct  node* head) {
    int retval = -1;
    struct node * next_node = NULL;


    struct node newValues;
    newValues.data = head->data;
    newValues.next = head->next;
    free(head);
    return newValues;
}




//gets the size of the string.
int getSize(char*line){
    char*temp;
    int size=0;
    for (temp = line; *temp != '\0'; temp++) {
        size++;
    }
    return size;
}

//postfix function this takes the pointer line as the paramter and returns the result
int postfix(char*line){
    struct node* head =NULL;
    int result=0;
    int i=0;
    while(line[0]!='\n')
    {
        bool isNumber=false;
        struct node r;
        struct node t;
        double valueOne;
        double valueTwo;
        char n = line[0];
        if((n=='X')||(n=='+')){
            switch(n){
            case 'X':
                r = pop(head);
                valueOne = r.data;
                head = r.next;
                t = pop(head);
                valueTwo = t.data;
                head = t.next;
                result = valueOne*valueTwo;
                head = push(head,result);
            break;
            case '+':
                r = pop(head);
                valueOne = r.data;
                head = r.next;
                t = pop(head);
                valueTwo = t.data;
                head = t.next;
                result = valueOne+valueTwo;
                head = push(head,result);
            break;
            case '-':
                r = pop(head);
                valueOne = r.data;
                head = r.next;
                t = pop(head);
                valueTwo = t.data;
                head = t.next;
                result = valueOne-valueTwo;
                head = push(head,result);
            break;
            case '/':
                r = pop(head);
                valueOne = r.data;
                head = r.next;
                t = pop(head);
                valueTwo = t.data;
                head = t.next;
                result = valueOne/valueTwo;
                head = push(head,result);
            break;

            }
             line++;
        }else if(n==' '){
           isNumber = false;
            line++;
        }else{
            char *temp = line;
            bool isNumber = true;
            int value;
            while(isNumber){
                if((temp[0+1])!=' '){
                   isNumber = true;
                   value = *temp -48;
                   int doubleValue = value*10;
                   if(isNumber == true){
                    line++;
                    temp++;
                   value = *line -48;
                    doubleValue+=value;
                    head = push(head,doubleValue);
                  break;
                   }
                }else{
                    value = *temp -48;
                    head = push(head,value);
                    isNumber = false;
                }
            }
         line++;
        }
 }
    printf("%d\n",result);
    return result;

}

// precedence function for infix
int precedence(char symbol){
    int result;
    switch(symbol){
    case '^':
    case '*':
        result=3;
        return result;
        break;
    case 'X':
    case '/':
        result =2;
        return result;
        break;
    case '+':
    case '-':
        result =1;
        return result;
        break;
    case ')':
    case '(':
        result= -1;
        return result;
        break;
    }
}

//The infix which is partially working its not poping my value at the top of the stack.
int infix(char*line){
    struct nodeChar*head = NULL;
  // struct nodeChar*operat = NULL;
    int i=0;
    const int size = 1024;
    char outputString[size];
   // char s[size];
    while(line[0]!='\n'){
            struct nodeChar k;
            struct nodeChar p;
            struct nodeChar d;
            struct nodeChar h;
            struct nodeChar preced;
           char oper;
            char symbol;
            char temp;
        char n = line[0];
        if( n=='('){
            head = pushChar(head,n);
            line++;
        }else if((n=='+') ||(n=='-') ||(n=='*')||(n=='/')||(n=='^')||(n=='X')){
            d = peekChar(head);
            temp = d.item;
            head = pushChar(head,temp);
            if(precedence(temp)> precedence(n)){
                preced = popChar(head);
                symbol = preced.item;
                outputString[i] = symbol;
                i=i+1;
                outputString[i] = ' ';
                i++;
            }
            head = pushChar(head,n);
            line++;

        }else if(n==')'){
               k= popChar(head);
               symbol =k.item;
               head = k.next_Two;
            while(symbol!='('){
                outputString[i] = symbol;
                i=i+1;
                outputString[i] = ' ';
                i++;
                h = popChar(head);
                symbol = h.item;
                head = h.next_Two;
            }
            if(head!=NULL){
                popChar(head);

            }

        }else if (n ==' '){
            line++;
        }else if(isdigit(n)){
            outputString[i] = n;
            if(isdigit(line[0+1])){
                outputString[i+1]= line[0+1];
                i++;
                line++;
            }
            i = i+1;
            outputString[i] = '  ';
            i++;
            line++;
        }else{
            line++;
        }
        char*infix = outputString[i];
        postfix(infix);



}
}

//main function which reads the file and writes the file

int main(int argc, char ** argv)
{
 /* char * filename;

  if ( argc == 1 ) {
    printf("Error: No input filename provided\n");
    printf("Usage: %s <input filename>\n", argv[0];
    exit(1);
  }
  else if ( argc > 2 ) {
    printf("Error: Too many command line parameters\n");
    printf("Usage: %s <input filename>\n", argv[0];
    exit(1);
  }
  else {
    filename = argv[1];
  }*/


 FILE*file = fopen("number.txt","r");
 FILE*ofp  = fopen("results.txt", "w");
 if(file!=NULL){
    char h[128];
    char*line = h;
    int i=0;
    int j =0;
    while(fgets(h,sizeof h,file)!=NULL){
        const int size = 107;
        char token[size];
        //char tokenize = token;
        while(line[j]!=' '){
            char g = line[j];
            token[i] =g;
            i++;
            line++;
        }
//This is my code for infix part but i am not getting the right value therefore I commented it.
        //if(token['infix']){
           // infix(line);
        //}else if(token['postfix']){
           // postfix(line);
       // }
        fprintf(ofp,h);
        fputs(h,stdout);
    }
    postfix(h);
    fclose(file);

    if (file == NULL) {
   fprintf(stderr, "Can't open output file %s!\n","number.txt");
    fclose(ofp);
    }
 }else{
    perror("number.txt");

  return 0;
}
}
