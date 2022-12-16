#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
  int key;
  struct node *left, *right;
};


struct node *Create_Node(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

struct node *insert(struct node *node, int key) {
  // Ağaç boş ise yeni bir düğüm oluştur
  if (node == NULL) return Create_Node(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

//Ağaçta Ara
struct node *search(struct node *bst_tree, int s_key) {
  if (bst_tree == NULL || bst_tree->key == s_key) return bst_tree;

  // Değer ağaçtaki değerden büyükse sağa, küçükse sola git
  if (bst_tree->key < s_key) return search(bst_tree->right, s_key);

  // Değer ağaçtaki değerden küçükse sola git
  return search(bst_tree->left, s_key);
}

// Driver code
int main() {
    clock_t begin = clock();
  struct node *root = NULL;
    for(int i=0; i<43000; i++)
        root = insert(root, i);
    //43.000 değerden sonra buffer overflow hatası veriyor.
    printf("43.000 Eleman Eklemek Icin Gecen Sure: %.02f saniye\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
    clock_t start_search = clock();
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
    printf("Aramalar Icin Gecen Sure: %.lg saniye\n", (long double)(clock() - start_search) / CLOCKS_PER_SEC);
    printf("Toplam Sure: %.02f saniye\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
}