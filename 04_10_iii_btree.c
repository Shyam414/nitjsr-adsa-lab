#include <stdio.h>
#include <stdlib.h>

typedef struct BTreeNode {
    int *keys;
    int t;
    struct BTreeNode **C;
    int n;
    int leaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
    int t;
} BTree;

BTree* createBTree(int t) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->t = t;
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = 1;
    node->n = 0;
    node->keys = (int*)malloc(sizeof(int)*(2*t-1));
    node->C = (BTreeNode**)malloc(sizeof(BTreeNode*)*(2*t));
    tree->root = node;
    return tree;
}

BTreeNode* searchBTree(BTreeNode* node, int key) {
    int i = 0;
    while(i < node->n && key > node->keys[i]) i++;
    if(i < node->n && node->keys[i] == key) return node;
    if(node->leaf) return NULL;
    return searchBTree(node->C[i], key);
}

void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    int t = y->t;
    BTreeNode* z = (BTreeNode*)malloc(sizeof(BTreeNode));
    z->t = t;
    z->leaf = y->leaf;
    z->n = t-1;
    z->keys = (int*)malloc(sizeof(int)*(2*t-1));
    z->C = (BTreeNode**)malloc(sizeof(BTreeNode*)*(2*t));

    for(int j=0;j<t-1;j++) z->keys[j] = y->keys[j+t];
    if(!y->leaf) for(int j=0;j<t;j++) z->C[j] = y->C[j+t];

    y->n = t-1;

    for(int j = x->n;j>=i+1;j--) x->C[j+1] = x->C[j];
    x->C[i+1] = z;

    for(int j = x->n-1;j>=i;j--) x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t-1];

    x->n += 1;
}

void insertNonFull(BTreeNode* x, int key) {
    int i = x->n-1;
    if(x->leaf) {
        while(i>=0 && key < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = key;
        x->n += 1;
    } else {
        while(i>=0 && key < x->keys[i]) i--;
        i++;
        if(x->C[i]->n == 2*x->t-1) {
            splitChild(x,i,x->C[i]);
            if(key > x->keys[i]) i++;
        }
        insertNonFull(x->C[i],key);
    }
}

void insertBTree(BTree* tree, int key) {
    BTreeNode* r = tree->root;
    if(r->n == 2*tree->t-1) {
        BTreeNode* s = (BTreeNode*)malloc(sizeof(BTreeNode));
        s->t = tree->t;
        s->leaf = 0;
        s->n = 0;
        s->keys = (int*)malloc(sizeof(int)*(2*tree->t-1));
        s->C = (BTreeNode**)malloc(sizeof(BTreeNode*)*(2*tree->t));
        s->C[0] = r;
        tree->root = s;
        splitChild(s,0,r);
        insertNonFull(s,key);
    } else insertNonFull(r,key);
}

void inorderBTree(BTreeNode* node) {
    if(node != NULL) {
        int i;
        for(i=0;i<node->n;i++) {
            if(!node->leaf) inorderBTree(node->C[i]);
            printf("%d ",node->keys[i]);
        }
        if(!node->leaf) inorderBTree(node->C[i]);
    }
}

void deleteBTreeNode(BTreeNode* node) {
    if(!node->leaf) for(int i=0;i<=node->n;i++) deleteBTreeNode(node->C[i]);
    free(node->keys);
    free(node->C);
    free(node);
}

void deleteBTree(BTree* tree) {
    deleteBTreeNode(tree->root);
    free(tree);
}

int main() {
    BTree* tree = createBTree(3); // t = 3

    int arr[] = {10,20,5,6,12,30,7,17};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++) insertBTree(tree,arr[i]);

    printf("B-Tree inorder: ");
    inorderBTree(tree->root);
    printf("\n");

    BTreeNode* found = searchBTree(tree->root,12);
    if(found) printf("Found 12\n");
    else printf("12 not found\n");

    deleteBTree(tree);
    return 0;
}
