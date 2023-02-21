#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
char * data;
int linenum[15];
struct Node *ltree;
struct Node *rtree;
};

struct Node* head;

struct Node* newTree(char *p, int l){
struct Node * n = malloc(sizeof(struct Node));
n->data = malloc(strlen(p)+1);
n->linenum[0] = malloc(sizeof(int));
strcpy(n->data,p);
n->linenum[0] = l;
n->ltree=n->rtree = NULL;
return n;
}

struct Node * insert(struct Node* tree,char *p, int l){
if (tree == NULL)
   return newTree(p,l);
int cmp =strcmp(p,tree->data);
if (cmp == 0 ){
     int countline=0;
     for(int i = 0; i< 15;i++){
         countline++;
         if(tree->linenum[i]== 0){
            break;
         } 
     }
     tree->linenum[countline-1]=l;
     return tree;    
}
else if (cmp < 0){
    tree->ltree = insert(tree->ltree,p,l);
}
else
   tree->rtree = insert(tree->rtree,p,l);
return tree;
}

void inorder(struct Node* tree){
if (tree == NULL)
   return ;
   inorder(tree->ltree);
   printf("\n%s: ",tree->data);
   for(int i = 0; i< 15;i++){
      if(tree->linenum[i]== 0){
            break;
         }
      if(tree->linenum[i+1]== 0){
         printf("%d ", tree->linenum[i]);
            break;
         }
      printf("%d, ", tree->linenum[i]);
      
     }
   inorder(tree->rtree);
}

main(){
char buf[200];
FILE *fp;
fp=fopen("test.txt","r");

char id[100];
int j;
int lines=0;
while (fgets(buf,100,fp)){
  int i=0;
  lines++;
  int len =strlen(buf);
  for (j=0,i=0;i<len;i++){
      if (isalpha(buf[i]) || buf[i]=='_'){
        while (buf[i] && (isalnum(buf[i]) || buf[i]=='_'))
           id[j++] = buf[i++];
        id[j]=0;       
        head =insert(head,id, lines);
        j=0;
        }
      
      }


   }
   inorder(head);
}

     
   
     
