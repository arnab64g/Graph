#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct treeNode{
     char name[20];
     treeNode* leftc;
     treeNode* rightc;
};
void insertIntoTree(char[][20], treeNode*, int);
void inorder(treeNode*, int);
void preorder(treeNode*, int);
void postorder(treeNode*, int);
int sizeofTree(treeNode*);
treeNode* delectnode(treeNode*, char[20]);
treeNode* NextMax(treeNode*);
int main()
{
     char kirdar[][20] = {"Motu", "Patlu", "Jhatka", "Ghasita", "Cingum", "John", "Number 1", "Number 2",
      "Boxer", "Chaywala", "Gopal", "Madhab", "Tingtong", "Virus", "Mayor", "Sabjiwali", "Chotu", "BubbleGum",
      "Joey", "Marky", "Laxman 1", "Olivia", "Mili", "Distinction", "Laxman 2", "Lucky", "Troublegum",
      "BotoBardhan", "Pappi", "Hera", "Pheri", "Vasooli", "Oggy", "Zero", "Doggy Don", "Chhotu", "Motu PP",
       "Lombu", "Karnal", "Major Saab", "Ballu", "Nana", "Doctor Saab"};
     treeNode *root;
     char nam[20];
     root = (treeNode*) malloc(sizeof(treeNode));
     int len = sizeof(kirdar)/sizeof(char);
     std::cout << "Inserting data..........." << '\n';
     insertIntoTree(kirdar, root, len/20);
     std::cout << "Size of Tree: " << sizeofTree(root) << '\n';
     while (true) {
          std::cout << "Traverse Inworder\n-------------------\n\n" << '\n';
          inorder(root, 0);
          std::cout << "Traverse Preworder\n-------------------\n\n" << '\n';
          preorder(root, 0);
          std::cout << "Traverse Postworder\n-------------------\n\n" << '\n';
          postorder(root, 0);
          std::cout << "\n\nEXECUTE colpleted" << '\n'<<endl;
          std::cout << "Delete Name: ";
          std::cin >> nam;
          if (strcmp(nam, "end") == 0)
               break;
          root = delectnode(root, nam);
          std::cout << "Size of Tree: " << sizeofTree(root) << '\n';
     }
     return 0;
}
void insertIntoTree(char s[][20], treeNode* ptr, int len) {
     char cname[20];
     treeNode *root, *temp, *preTemp;
     root = ptr;
     strcpy(ptr->name, s[0]);
     ptr->leftc = NULL;
     ptr->rightc = NULL;
     for (int i = 1; i < len; i++) {
          temp = root;
          strcpy(cname, s[i]);
          while (temp != NULL) {
               preTemp = temp;
               if (strcmp(cname , temp->name) < 0)
                    temp = temp->leftc;
               else if (strcmp(cname , temp->name) > 0)
                    temp = temp->rightc;
          }
          ptr = (treeNode*) malloc(sizeof(treeNode));
          strcpy(ptr->name, cname);
          ptr->leftc = NULL;
          ptr->rightc = NULL;
          if (strcmp(cname , preTemp->name) < 0)
               preTemp->leftc = ptr;
          else if(strcmp(cname , preTemp->name) > 0)
               preTemp->rightc= ptr;
     }
}
void inorder(treeNode* ptr, int sp) {
     if (ptr == NULL)
          return;
     sp += 10;
     inorder(ptr->leftc, sp);
     for (int i = 0; i < sp; i++)
          std::cout  << " ";
     std::cout << ptr->name << '\n';
     inorder(ptr->rightc, sp);
}
void preorder(treeNode* ptr, int sp) {
     if (ptr == NULL)
          return;
     sp+=10;
     for (int i = 0; i < sp; i++)
          std::cout  << " ";
     std::cout << ptr->name << '\n';
     preorder(ptr->leftc, sp);
     preorder(ptr->rightc, sp);
}
void postorder(treeNode* ptr, int sp) {
     if (ptr == NULL)
          return;
     sp+=10;
     postorder(ptr->leftc, sp);
     postorder(ptr->rightc, sp);
     for (int i = 0; i < sp; i++)
          std::cout  << " ";
     std::cout << ptr->name << '\n';
}
treeNode* delectnode(treeNode* root, char ch[20]){
     treeNode* delNode;
     if (root == NULL)
     {
          cout << ch << ", name not Found."<<endl;
          return root;
     }
     if (strcmp(root->name, ch) == 0) {
          if (root->leftc == NULL && root->rightc == NULL) {
               free(root);
               return NULL;
          }
          else if (root->leftc == NULL && root->rightc != NULL) {
               delNode = root;
               root = root->rightc;
               free(delNode);
               return root;
          }
          else if (root->leftc != NULL && root->rightc == NULL) {
               delNode = root;
               root = root->leftc;
               free(delNode);
               return root;
          }
          else return NextMax(root);
     }
     else if (strcmp(root->name, ch) > 0)
          root->leftc = delectnode(root->leftc, ch);
     else if (strcmp(root->name, ch) < 0)
          root->rightc = delectnode(root->rightc, ch);
     return root;
}
treeNode* NextMax(treeNode *ptr){
     treeNode* delNode, *preNode = NULL;
     delNode = ptr;
     ptr = ptr->rightc;
     while (ptr->leftc != NULL) {
          preNode = ptr;
          ptr = ptr->leftc;
     }
     if (ptr->rightc == NULL && preNode != NULL) {
          preNode->leftc = NULL;
          ptr->rightc = delNode->rightc;
     }
     else if (ptr->rightc != NULL && preNode != NULL) {
          preNode->leftc = ptr->rightc;
          ptr->rightc = delNode->rightc;
     }
     ptr->leftc = delNode->leftc;
     free(delNode);
     return ptr;
}
int sizeofTree(treeNode* ptr)
{
     if (!ptr)
          return 0;
     else
          return 1+sizeofTree(ptr->leftc)+sizeofTree(ptr->rightc);
}
