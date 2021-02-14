#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
struct TreeNode{
     char name[20];
     TreeNode* leftc;
     TreeNode* rightc;
     int height;
};
TreeNode* insertAVL(TreeNode*, char[][20], int);
TreeNode* delectnode(TreeNode*, char[20]);
TreeNode* NextMax(TreeNode *);
TreeNode* leftRotate(TreeNode*);
TreeNode* rightRotate(TreeNode*);
TreeNode* balance(TreeNode*);
int getheight(TreeNode*);
int height(TreeNode*);
int balanceFactor(TreeNode*);
void inorder(TreeNode*, int);
int sizeofTree(TreeNode*);
int main(){
     char kirdar[][20] = {"Motu", "Patlu", "Jhatka", "Ghasita", "Cingum", "John", "Number 1", "Number 2",
      "Boxer", "Chaywala", "Gopal", "Madhab", "Tingtong", "Virus", "Mayor", "Sabjiwali", "Chotu", "BubbleGum",
      "Joey", "Marky", "Laxman 1", "Olivia", "Mili", "Distinction", "Laxman 2", "Lucky", "Troublegum",
      "BotoBardhan", "Pappi", "Hera", "Pheri", "Vasooli", "Oggy", "Zero", "Doggy Don", "Chhotu", "Motu PP",
       "Lombu", "Karnal", "Major Saab", "Ballu", "Nana", "Doctor Saab"};
     TreeNode* root;
     char name[20];
     int len = sizeof(kirdar)/sizeof(kirdar[0]);
     root = (TreeNode*) malloc(sizeof(TreeNode));
     root = insertAVL(root, kirdar, len);
     std::cout << "====================================================================" << '\n';
     inorder(root, 0);
     std::cout << "====================================================================" << '\n';
     while (true) {
          std::cout << "Delete Name: ";
          std::cin >> name;
          if (strcmp(name, "end") == 0)
               break;
          root = delectnode(root, name);
          root->height = getheight(root);
          root = balance(root);
          root->height = getheight(root);
          std::cout << "-------------------------------------------------------------------" << '\n';
          inorder(root, 0);
          std::cout << "Size of Tree: " << sizeofTree(root) << '\n';
     }
     return 0;
}
TreeNode* insertAVL(TreeNode* ptr, char s[][20], int len) {
     char cname[20];
     TreeNode *root, *temp, *preTemp;
     root = ptr;
     strcpy(ptr->name, s[0]);
     ptr->leftc = NULL;
     ptr->rightc = NULL;
     ptr->height = 1;
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
          ptr = (TreeNode*) malloc(sizeof(TreeNode));
          strcpy(ptr->name, cname);
          ptr->leftc = NULL;
          ptr->rightc = NULL;
          ptr->height = 1;
          if (strcmp(cname , preTemp->name) < 0)
               preTemp->leftc = ptr;
          else if(strcmp(cname , preTemp->name) > 0)
               preTemp->rightc= ptr;
          root->height = getheight(root);
          root = balance(root);
          std::cout << (i+1)<< ". " << s[i] << endl;
     }
     return root;
}
TreeNode* leftRotate(TreeNode* root){
     TreeNode* ptr;
     ptr = root->rightc;
     root->rightc = ptr->leftc;
     ptr->leftc = root;
     return ptr;
}
int height(TreeNode* ptr){
     if(ptr==NULL)
          return 0;
     else return ptr->height;
}
int getheight(TreeNode* ptr){
     if (ptr == NULL)
          return 0;
     else{
          ptr->height = getheight(ptr->leftc) > getheight(ptr->rightc) ? getheight(ptr->leftc) : getheight(ptr->rightc);
          ptr->height++;
          return ptr->height;
     }
}
TreeNode* rightRotate(TreeNode* root){
     TreeNode* ptr;
     ptr = root->leftc;
     root->leftc = ptr->rightc;
     ptr->rightc = root;
     return ptr;
}
void inorder(TreeNode* ptr, int sp) {
     if (ptr == NULL)
          return;
     sp += 10;
     inorder(ptr->leftc, sp);
     for (int i = 0; i < sp; i++)
          std::cout  << " ";
     std::cout << ptr->name <<" ("<< ptr->height << ")" << '\n';
     inorder(ptr->rightc, sp);
}
TreeNode* balance(TreeNode* ptr){
     TreeNode* temp;
     if (ptr->leftc != NULL)
          ptr->leftc = balance(ptr->leftc);
     if (ptr->rightc != NULL)
          ptr->rightc = balance(ptr->rightc);
     if (balanceFactor(ptr) > 1){
          if (balanceFactor(ptr->leftc) < 0)
               ptr->leftc = leftRotate(ptr->leftc);
          ptr = rightRotate(ptr);
     }
     else if (balanceFactor(ptr) < -1){
          if (balanceFactor(ptr->rightc) > 0)
               ptr->rightc = rightRotate(ptr->rightc);
          ptr = leftRotate(ptr);
     }
     ptr->height = getheight(ptr);
     return ptr;
}
TreeNode* delectnode(TreeNode* root, char ch[20]){
     TreeNode* delNode;
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
TreeNode* NextMax(TreeNode *ptr){
     TreeNode* delNode, *preNode = NULL;
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
int balanceFactor(TreeNode* ptr){
     return height(ptr->leftc) - height(ptr->rightc);
}
int sizeofTree(TreeNode* ptr){
     if (!ptr)
          return 0;
     else return 1+sizeofTree(ptr->leftc)+sizeofTree(ptr->rightc);
}
