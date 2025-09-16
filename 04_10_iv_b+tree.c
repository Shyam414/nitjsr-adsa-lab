#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3   

typedef struct BPlusNode {
    bool leaf;
    int n;                  
    int keys[ORDER];        
    struct BPlusNode *child[ORDER + 1];
    struct BPlusNode *next; 
} BPlusNode;

typedef struct {
    BPlusNode *root;
} BPlusTree;

BPlusNode *newNode(bool leaf) {
    BPlusNode *p = calloc(1, sizeof(BPlusNode));
    p->leaf = leaf;
    return p;
}

BPlusTree *createTree() {
    BPlusTree *T = malloc(sizeof(BPlusTree));
    T->root = newNode(true);
    return T;
}

BPlusNode *searchItem(BPlusTree *T, int key, int *idx) {
    BPlusNode *x = T->root;
    while (!x->leaf) {
        int i=0;
        while (i<x->n && key >= x->keys[i]) i++;
        x = x->child[i];
    }
    for (int i=0;i<x->n;i++)
        if (x->keys[i]==key) { if(idx) *idx=i; return x; }
    return NULL;
}

void splitLeaf(BPlusTree *T, BPlusNode *leaf, int *upKey, BPlusNode **newLeaf) {
    int mid = leaf->n/2;
    *upKey = leaf->keys[mid];
    *newLeaf = newNode(true);

    int j=0;
    for (int i=mid; i<leaf->n; i++)
        (*newLeaf)->keys[j++] = leaf->keys[i];
    (*newLeaf)->n = j;
    leaf->n = mid;
    (*newLeaf)->next = leaf->next;
    leaf->next = *newLeaf;
}

void splitInternal(BPlusNode *node, int *upKey, BPlusNode **newNodeOut) {
    int mid = node->n/2;
    *upKey = node->keys[mid];

    BPlusNode *nn = newNode(false);
    int j=0;
    for (int i=mid+1;i<node->n;i++) nn->keys[j++] = node->keys[i];
    for (int i=mid+1;i<=node->n;i++) nn->child[i-mid-1] = node->child[i];
    nn->n = j;
    node->n = mid;
    *newNodeOut = nn;
}

void insertIntoLeaf(BPlusNode *leaf, int key) {
    int i=leaf->n-1;
    while (i>=0 && leaf->keys[i]>key) {
        leaf->keys[i+1]=leaf->keys[i];
        i--;
    }
    leaf->keys[i+1]=key;
    leaf->n++;
}

BPlusNode* insertRec(BPlusNode *node, int key, int *upKey, BPlusNode **newChild) {
    if (node->leaf) {
        if (node->n < ORDER-1) { insertIntoLeaf(node,key); return NULL; }
        insertIntoLeaf(node,key);
        splitLeaf(NULL,node,upKey,newChild);
        return node;
    }

    int i=0;
    while (i<node->n && key>=node->keys[i]) i++;
    int promoted;
    BPlusNode *nc;
    BPlusNode *child = insertRec(node->child[i],key,&promoted,&nc);

    if (!child) return NULL;

    if (node->n < ORDER-1) {
        for (int j=node->n;j>i;j--) {
            node->keys[j]=node->keys[j-1];
            node->child[j+1]=node->child[j];
        }
        node->keys[i]=promoted;
        node->child[i+1]=nc;
        node->n++;
        return NULL;
    }

    node->keys[node->n]=promoted;
    node->child[node->n+1]=nc;
    node->n++;
    splitInternal(node,upKey,newChild);
    return node;
}

void insertItem(BPlusTree *T, int key) {
    int up; BPlusNode *newc;
    BPlusNode *split = insertRec(T->root,key,&up,&newc);
    if (split) {
        BPlusNode *nr = newNode(false);
        nr->keys[0]=up;
        nr->child[0]=split;
        nr->child[1]=newc;
        nr->n=1;
        T->root=nr;
    }
}

void freeNode(BPlusNode *x) {
    if (!x->leaf)
        for (int i=0;i<=x->n;i++) freeNode(x->child[i]);
    free(x);
}
void deleteTree(BPlusTree *T) {
    if (T) { freeNode(T->root); free(T); }
}

int main() {
    BPlusTree *T = createTree();
    int arr[]={10,20,5,6,12,30,7,17,25,3};
    for(int i=0;i<10;i++) insertItem(T,arr[i]);

    int pos;
    BPlusNode *res = searchItem(T,12,&pos);
    if(res) printf("Found %d in leaf position %d\n",res->keys[pos],pos);

    // print leaves
    printf("Leaves: ");
    BPlusNode *p=T->root;
    while(!p->leaf) p=p->child[0];
    while(p){ for(int i=0;i<p->n;i++) printf("%d ",p->keys[i]); p=p->next;}
    printf("\n");

    deleteTree(T);
    return 0;
}
