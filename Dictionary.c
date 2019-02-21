/*
* Name: Sidharth Naik
* ID: 1647945
* Class: 12B/M
* Date: February 19,2018
* Description: This is the Dictionary ADT has all the ADT methods
* File Name: Dictionary.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


// private types --------------------------------------------------------------

// Defines the pairObject
typedef struct PairObj{
  char* key;
  char* value;
} PairObj;

// Gives PairObj* a placeholder name of Pair
typedef PairObj* Pair;

// newPair()
// Constructor for pair
Pair newPair(char* k, char* v){
  Pair P = malloc(sizeof(PairObj));
  assert(P!=NULL);
  P->key = k;
  P->value = v;
  return(P);
}

// freePair()
// deconstructor
void freePair(Pair* pP){
  if( pP!=NULL && *pP!=NULL ){
    free(*pP);
    *pP = NULL;
  }
}

// NodeObj
typedef struct NodeObj{
   struct PairObj* pair;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* key, char* value) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->pair = newPair(key,value);
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// Dictionary Obj
typedef struct DictionaryObj{
   Node head;
   int numItems;
} DictionaryObj;

typedef DictionaryObj* Dictionary;

// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->head = NULL;
   D->numItems = 0;
   return D;
}

// freeDictionary()
// destructor for the Dictionarytype
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      if( !isEmpty(*pD) ) {
        makeEmpty(*pD);
      }
      free(*pD);
      *pD = NULL;
   }
}

//findKey()
// returns a reference to the Node with the specific value key
Node findKey(Dictionary D, char* key){

  for(Node N = D->head; N !=NULL; N = N->next){
    if(strcmp((N->pair->key),key) == 0){
      return N;
    }
  }
  return NULL;
}

//findPrevKey()
// returns a reference to the Node before the Node with the specific value key
Node findPrevKey(Dictionary D, char* key){
  int i = 0;
  //Finds the key value's placement in the array sets = i
  for(Node N = D->head; N != NULL; N = N->next, i++){
    if(strcmp((N->pair->key),key) == 0){
      break;
    }
  }
  int k =0;
  //Goes until k = i-1 returns Node which is the prev
  for(Node N = D-> head; k < i; N = N->next, k++){
    if(k == i-1){
      return N;
    }
  }
  return NULL;
}

// ADT operations

// isEmpty()
// returns 1 (true) if D is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
   return(D->numItems==0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D) {
  return D->numItems;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* key){
  Node N = findKey(D,key);
  if(N == NULL){

    return NULL;

  } else {

    return (N->pair->value);

  }
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* key, char* value){

   if( lookup(D,key) != NULL ){
      fprintf(stderr, "cannot insert duplicate keys\n");
      exit(EXIT_FAILURE);
   }
   if(D->numItems == 0){
     Node N = newNode(key,value);
     N->next = D->head;
     D->head = N;
   } else {
     Node P = findPrevKey(D,key);
     Node C = P->next;
     P->next = newNode(key,value);
     P = P->next;
     P->next = C;
   }

   (D->numItems)++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* key){
   if( lookup(D,key) == NULL ){
      fprintf(stderr, "cannot delete non-existent key\n");
      exit(EXIT_FAILURE);
   }
   if( findPrevKey(D,key) == NULL){
     Node N = D->head;
     D->head = (D->head)->next;
     N->next = NULL;
     freePair(&(N->pair));
     freeNode(&N);
   }else{
     Node P = findPrevKey(D,key);
     Node N = P->next;
     P->next = N->next;
     N->next = NULL;
     freePair(&(N->pair));
     freeNode(&N);
   }
  (D->numItems)--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){

   while( D->numItems > 0){
     delete(D, D->head->pair->key);
   }

}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D){
    for(Node N=D->head; N != NULL; N=N->next){
      fprintf(out,"%s %s\n",N->pair->key, N->pair->value);
    }
}
