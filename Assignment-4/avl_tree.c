
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
  int key;
  struct Node *left;
  struct Node *right;
  int height;
};

int max(int a, int b);

struct Node *newNode(int key);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node *insertNode(struct Node *node, int key);
struct Node *search(struct Node *bst_tree, int s_key);



int main() {
  struct Node *root = NULL;
  clock_t start = clock();
  for (int i = 0; i < 1000000; i++)
  {
      root = insertNode(root, i);
  }
  printf("Ekleme Icin Gecen Sure: %.2fsaniye\n", (double)(clock() - start) / CLOCKS_PER_SEC);
  clock_t search_start = clock();
  search(root, 1234567);
  search(root, 1000007);
  search(root, 10000);
  search(root, 1000);
    search(root,25000);
    search(root,12458);
    search(root,12345);
    search(root,42351);
    search(root,25789);
    search(root,39876);
    search(root,14789);
    search(root,15);
    search(root,155);
    search(root,41);
  printf("Arama Icin Gecen Sure: %.2fsaniye\n", (double)(clock() - search_start) / CLOCKS_PER_SEC);
  printf("Toplam Gecen Sure: %.2fsaniye", (double)(clock() - start) / CLOCKS_PER_SEC);
    

  return 0;
}


// Yüksekliği hesapla
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}


struct Node *newNode(int key) {
  struct Node *node = (struct Node *)
    malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Sağa döndür
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Sola döndür
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Denge faktörünü hesapla
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Düğüm ekle
struct Node *insertNode(struct Node *node, int key) {
  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *search(struct Node *root, int key) {
  if (root == NULL || root->key == key)
    return root;

  if (root->key < key)
    return search(root->right, key);

  return search(root->left, key);
}