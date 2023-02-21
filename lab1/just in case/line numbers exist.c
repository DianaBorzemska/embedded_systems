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

struct Node* newTree(char *p){
struct Node * n = malloc(sizeof(struct Node));
n->data = malloc(strlen(p)+1);
strcpy(n->data,p);
n->ltree=n->rtree = NULL;
return n;
}

struct Node * insert(struct Node* tree,char *p){
if (tree == NULL)
   return newTree(p);
int cmp =strcmp(p,tree->data);
int c = __LINE__;
if (cmp == 0 ){
     //insert(tree->linenum,c);
     return tree; 
   
}
else if (cmp < 0){
    //insert linenum
    tree->ltree = insert(tree->ltree,p);
    //tree->ltree = insert(tree->linenum,c);
}
else
   tree->rtree = insert(tree->rtree,p);
  // tree->rtree = insert(tree->linenum,c);
return tree;
}

void inorder(struct Node* tree){
if (tree == NULL)
   return ;
   inorder(tree->ltree);
   printf("%s\n %d",tree->data,tree->linenum);
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
        // have id
        id[j]=0;       
        head =insert(head,id);
        printf("id = %s\n %d\n",id,lines);
        j=0;
        }
      
      }


   }
   //inorder(head);
}

     
   
     
