#include <stdio.h>
#include <stdlib.h>

// Cau truc Node cua cay AVL
typedef struct Node {
    int key; // Gia tri cua nut
    int height; // Chieu cao cua nut
    struct Node* left; // Con tro toi nut con ben trai
    struct Node* right; // Con tro toi nut con ben phai
} Node;

// Ham tim gia tri lon nhat giua hai so
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Ham lay chieu cao cua mot nut
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Ham tao mot nut moi
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Ham xoay phai
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Ham xoay trai
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Ham lay do cao can bang cua mot nut
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Ham chen mot nut vao cay AVL
Node* insert(Node* node, int key) {
    if (!node) return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Khong cho phep trung lap

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    // Truong hop Left Left
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Truong hop Right Right
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Truong hop Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Truong hop Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Ham duyet theo thu tu In-order
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Ham duyet theo thu tu Pre-order
void preOrder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Ham duyet theo thu tu Post-order
void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

int main() {
    Node* root = NULL;
    int input[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(input) / sizeof(input[0]);

    printf("Them cac phan tu vao cay AVL tung buoc:\n");
    for (int i = 0; i < n; i++) {
        printf("Buoc %d: Chen %d\n", i + 1, input[i]);
        root = insert(root, input[i]);

        printf("Duyet In-order: ");
        inOrder(root);
        printf("\n");

        printf("Duyet Pre-order: ");
        preOrder(root);
        printf("\n");

        printf("Duyet Post-order: ");
        postOrder(root);
        printf("\n\n");
    }

    return 0;
}
