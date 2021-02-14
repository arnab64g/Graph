#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;
struct Characters{
     char name[20];
     Characters* next;
};
struct Showname{
     char name[20];
     int num;
     Characters* clst;
     Showname* next;
};
struct ArrayList{
     char cname[20];
     char sname[20];
};
Showname* createTable(ArrayList[], int);
Showname* addShow(Showname*, char[20]);
Characters* addCharacter(Characters*, char[20]);
void ViewList(Showname*, int);
void ViewCname(Characters*, int);
int main()
{
     ArrayList nk[] = {{"Motu", "Motu Patlu"}, {"Patlu", "Motu Patlu"}, {"Jhatka", "Motu Patlu"},
     {"Ghasita", "Motu Patlu"}, {"Cingum", "Motu Patlu"}, {"John", "Motu Patlu"}, {"Number1", "Motu Patlu"},
     {"Number2", "Motu Patlu"}, {"Boxer", "Motu Patlu"}, {"Chaywala", "Motu Patlu"}, {"Gopal", "Golmal Jr."},
     {"Madhab", "Golmal Jr."}, {"Virus", "Motu Patlu"}, {"Mayor", "Motu Patlu"},
     {"Sabjiwali", "Motu Patlu"}, {"Chotu", "Motu Patlu"},{"BubbleGum", "Motu Patlu"},
     {"Troublegum", "Motu Patlu"}, {"BotoBardhan", "Golmal Jr."}, {"Pappi", "Golmal Jr."},
     {"Hera", "Motu Patlu"}, {"Pheri", "Motu Patlu"}, {"Vasooli", "Golmal Jr."}, {"Oggy", "Oggy and Cocr"},
     {"Jack", "Oggy and Cocr"}, {"Joey", "Oggy and Cocr"}, {"Marky", "Oggy and Cocr"}, {"Laxman 1", "Golmal Jr."},
     {"Olivia", "Oggy and Cocr"}, {"Mili", "Golmal Jr."}, {"Distinction", "Golmal Jr."}, {"Laxman 2", "Golmal Jr."},
     {"Lucky", "Golmal Jr."}, {"Doggy Don", "Pakdam Pakdai"}, {"Chhotu", "Pakdam Pakdai"},{"Motu PP", "Pakdam Pakdai"},
      {"Lombu", "Pakdam Pakdai"}, {"Karnal", "Pakdam Pakdai"}, {"Major Saab", "Pakdam Pakdai"}, {"Ballu", "Pakdam Pakdai"},
      {"Nana", "Pakdam Pakdai"}, {"Doctor Saab", "Pakdam Pakdai"}};
     int len = sizeof(nk)/sizeof(ArrayList);
     Showname* head, *ptr;
     head = createTable(nk, len);
     ptr = head;
     while (ptr) {
          std::cout <<setw(20) << left << ptr->name;
          cout << " (" << ptr->num << ") "<< '\n';
          ptr = ptr->next;
     }
     std::cout << "\n\n\n" << '\n';
     ViewList(head, 1);
     return 0;
}
Showname* createTable(ArrayList lst[], int len){
     Showname* ptr, *select;
     ptr = NULL;
     for (int i = 0; i < len; i++) {
          if (!ptr) {
               ptr = addShow(ptr, lst[i].sname);
               select = ptr;
          }
          else select = addShow(ptr, lst[i].sname);
          select->clst = addCharacter(select->clst, lst[i].cname);
          select->num++;
     }
     return ptr;
}
Showname* addShow(Showname* root, char name[20]){
     if (!root) {
          root = (Showname*) malloc(sizeof(Showname));
          strcpy(root->name, name);
          root->clst = NULL;
          root->next = NULL;
          root->num = 0;
          return root;
     }
     else{
          while (root->next) {
               if (strcmp(root->name, name) == 0)
                    return root;
               else root = root->next;
          }
          if (strcmp(root->name, name) == 0)
               return root;
          else{
               Showname* ptr;
               ptr = (Showname*) malloc(sizeof(Showname));
               strcpy(ptr->name, name);
               ptr->next = NULL;
               ptr->clst = NULL;
               ptr->num = 0;
               root->next = ptr;
               return ptr;
          }
     }
}
Characters* addCharacter(Characters* root, char name[20]){
     if (!root) {
          root = (Characters*) malloc(sizeof(Characters));
          strcpy(root->name, name);
          root->next = NULL;
     }
     else{
          Characters* ptr, *temp;
          temp = root;
          while (temp->next)
               temp = temp->next;
          ptr = (Characters*) malloc(sizeof(Characters));
          strcpy(ptr->name, name);
          ptr->next = NULL;
          temp->next = ptr;
     }
     return root;
}
void ViewList(Showname* ptr, int n) {
     if (!ptr)
          return;
     else{
          std::cout << n << ". "<< ptr->name << "(" << ptr->num <<")\n----------------------------\n";
          ViewCname(ptr->clst, 1);
          std::cout << "\n\n";
          ViewList(ptr->next, n+1);
     }
}
void ViewCname(Characters* ptr, int n) {
     if (!ptr)
          return;
     else{
          std::cout << n << ". " << ptr->name << endl;
          ViewCname(ptr->next, n+1);
     }
}
