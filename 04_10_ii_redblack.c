// red_black_tree.c
#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *NIL; // sentinel
} RBTree;

// ------------------- Helpers & Creation -------------------

RBTree* createTree() {
    RBTree *T = (RBTree*)malloc(sizeof(RBTree));
    T->NIL = (Node*)malloc(sizeof(Node));
    T->NIL->color = BLACK;
    T->NIL->left = T->NIL->right = T->NIL->parent = NULL;
    T->root = T->NIL;
    return T;
}

Node* createNode(RBTree *T, int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->color = RED;           // new nodes are RED
    n->left = T->NIL;
    n->right = T->NIL;
    n->parent = NULL;
    return n;
}

void freeNode(Node *n) {
    free(n);
}

// ------------------- Rotations -------------------

void leftRotate(RBTree *T, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != T->NIL) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree *T, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != T->NIL) x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}


void insertFixup(RBTree *T, Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right; // uncle
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2
                    z = z->parent;
                    leftRotate(T, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(T, z->parent->parent);
            }
        } else {
            // mirror
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2
                    z = z->parent;
                    rightRotate(T, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void insertItem(RBTree *T, int key) {
    Node *z = createNode(T, key);
    Node *y = NULL;
    Node *x = T->root;

    while (x != T->NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else if (z->key > x->key) x = x->right;
        else {
            freeNode(z);
            return;
        }
    }
    z->parent = y;
    if (y == NULL) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    if (z->left == NULL) z->left = T->NIL;
    if (z->right == NULL) z->right = T->NIL;

    insertFixup(T, z);
}


Node* searchItem(RBTree *T, int key) {
    Node *x = T->root;
    while (x != T->NIL) {
        if (key == x->key) return x;
        else if (key < x->key) x = x->left;
        else x = x->right;
    }
    return T->NIL;
}


void transplant(RBTree *T, Node *u, Node *v) {
    if (u->parent == NULL) T->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

Node* treeMinimum(RBTree *T, Node *x) {
    while (x->left != T->NIL) x = x->left;
    return x;
}

void deleteFixup(RBTree *T, Node *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                // case 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(T, w);
                    w = x->parent->right;
                }
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(T, x->parent);
                x = T->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                // case 1
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                // case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T, w);
                    w = x->parent->left;
                }
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void deleteItem(RBTree *T, int key) {
    Node *z = searchItem(T, key);
    if (z == T->NIL) return;

    Node *y = z;
    Color yOriginalColor = y->color;
    Node *x;

    if (z->left == T->NIL) {
        x = z->right;
        transplant(T, z, z->right);
    } else if (z->right == T->NIL) {
        x = z->left;
        transplant(T, z, z->left);
    } else {
        y = treeMinimum(T, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFixup(T, x);
    }

    freeNode(z);
}


void deleteTreeHelper(RBTree *T, Node *n) {
    if (n == T->NIL || n == NULL) return;
    deleteTreeHelper(T, n->left);
    deleteTreeHelper(T, n->right);
    freeNode(n);
}

void deleteTree(RBTree *T) {
    if (T == NULL) return;
    deleteTreeHelper(T, T->root);
    if (T->NIL) free(T->NIL);
    free(T);
}


void inorderPrint(RBTree *T, Node *n) {
    if (n == T->NIL) return;
    inorderPrint(T, n->left);
    printf("%d(%s) ", n->key, n->color==RED ? "R":"B");
    inorderPrint(T, n->right);
}


int main() {
    RBTree *T = createTree();

    int arr[] = {20, 15, 25, 10, 5, 1, 30, 28, 40, 35};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < n; ++i) insertItem(T, arr[i]);

    printf("Inorder after inserts:\n");
    inorderPrint(T, T->root);
    printf("\n");

    printf("Search 25: ");
    Node *s = searchItem(T, 25);
    printf(s != T->NIL ? "found\n" : "not found\n");

    deleteItem(T, 25);
    deleteItem(T, 20);
    printf("Inorder after deletions (25, 20):\n");
    inorderPrint(T, T->root);
    printf("\n");

    deleteTree(T);
    return 0;
}
