#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
using namespace std;
struct edges{
     char name[20];
     edges* next;
};
struct verteces{
     char name[20];
     bool isvisited;
     edges *links;
     verteces *next;
};
struct edgeslist{
     char name1[20];
     char name2[20];
};
verteces* ctrateGraph(verteces*, edgeslist[], int);
edges* addEdges(verteces*, char[20]);
verteces* addVerteces(verteces*, char[20]);
void deleteEdge(verteces*, char[20], char[20]);
void viewVert(verteces*);
void viewEdg(edges*);
void setNotVisited(verteces*);
void BFSTraverse(verteces*, char[20]);
edges *enqueue (edges*, char[20]);
edges *dequeue(edges*);
void setVisited(verteces* ptr, char[20]);
bool isVisited(verteces* ptr, char[20]);
verteces* deleteNode(verteces*, char[20]);
int main()
{
     char name[20], name1[20], name2[20];
     edgeslist lst[] = {{"Motu", "Patlu"}, {"Motu", "Jhatka"}, {"Motu", "John"}, {"Motu", "Cingum"},
      {"Patlu", "John"}, {"Patlu", "Ghasita"}, {"Patlu", "Cingum"}, {"John", "Number 1"}, {"John", "Number 2"},
     {"Number 1", "Number 2"}, {"Cingum", "John"}, {"Jhatka", "Ghasita"}, {"Motu", "Chaywala"},
     {"Cingum", "Mayor"}, {"Motu", "Chotu"}, {"Chaywala", "Sabjiwali"}, {"Gopal", "Madhab"}, {"Gopal", "Laxman 1"},
     {"Madhab", "Laxman 2"}, {"Madhab", "Lucky"}, {"Laxman 2", "Lucky"}, {"BotoBardhan", "Gopal"},
     {"BotoBardhan", "Madhab"}, {"BotoBardhan", "Pappi"}};
     verteces* head;
     int choice, len = sizeof(lst)/sizeof(edgeslist);
     head = ctrateGraph(head, lst, len);
     while (true) {
          viewVert(head);
          setNotVisited(head);
          cout<<"\n\nEnter Choice: ";
          cin>>choice;
          if (choice == 5)
               break;
          switch (choice){
               case 1:
                    std::cout << "\nStart node: ";
                    scanf(" %[^\n]", name);
                    BFSTraverse(head, name);
                    break;
               case 2:
                    cout << "Delete Edge: ";
                    std::cout << "Delete: ";
                    scanf(" %[^\n]", name1);
                    std::cout << "Delete: ";
                    scanf(" %[^\n]", name2);
                    deleteEdge(head, name1, name2);
                    deleteEdge(head, name2, name1);
                    break;
               case 3:
                    std::cout << "Delete Node: ";
                    scanf(" %[^\n]", name);
                    head = deleteNode(head, name);
                    break;
          }
          std::cout << "\n\n" << '\n';
     }
     return 0;
}
edges* addEdges(verteces* ptr, char name[20])
{
     if (ptr->links == NULL) {
          ptr->links = (edges*)malloc(sizeof(edges));
          strcpy(ptr->links->name, name);
          ptr->links->next = NULL;
     }
     else{
          edges* nw, *trv;
          trv = ptr->links;
          while (trv->next)
               trv = trv->next;
          nw =  (edges*)malloc(sizeof(edges));
          strcpy(nw->name, name);
          nw->next = NULL;
          trv->next = nw;
     }
     return ptr->links;
}
verteces* ctrateGraph(verteces* ptr, edgeslist lst[], int len)
{
     verteces* temp;
     temp = NULL;
     temp = addVerteces(temp, lst[0].name1);
     temp->links = addEdges(temp, lst[0].name2);
     ptr = temp;
     temp = addVerteces(temp, lst[0].name2);
     temp->links = addEdges(temp, lst[0].name1);
     for (int i = 1; i < len; i++) {
          temp = addVerteces(ptr, lst[i].name1);
          temp->links = addEdges(temp, lst[i].name2);
          temp = addVerteces(ptr, lst[i].name2);
          temp->links = addEdges(temp, lst[i].name1);
     }
     return ptr;
}
verteces* addVerteces(verteces* ptr, char name[20])
{
     if (ptr == NULL) {
          ptr = (verteces *) malloc(sizeof(verteces));
               strcpy(ptr->name, name);
               ptr->next = NULL;
               ptr->links = NULL;
               return ptr;
     }
     else{
          verteces* trv;
          trv = ptr;
          while (trv->next) {
               if (strcmp(trv->name, name) == 0)
                    return trv;
               else trv = trv->next;
          }
          if (strcmp(trv->name, name) == 0)
               return trv;
          else{
               ptr = (verteces*) malloc(sizeof(verteces));
               strcpy(ptr->name, name);
               ptr->next = NULL;
               ptr->links = NULL;
               trv->next = ptr;
               return ptr;
          }
     }
}
void viewVert(verteces* ptr)
{
     if (ptr) {
          std::cout << '\n';
          std::cout << setw(20) << "=>" << ptr->name;
          viewEdg(ptr->links);
          viewVert(ptr->next);
     }
}
void viewEdg(edges* ptr) {
     if (ptr) {
          std::cout << " -> " << ptr->name;
          viewEdg(ptr->next);
     }
}
void setNotVisited(verteces* ptr) {
     if (ptr) {
          ptr->isvisited = false;
          setNotVisited(ptr->next);
     }
}
void BFSTraverse(verteces* ptr, char name[20]) {
     edges* queue, *tmp;
     verteces *temp;
     queue = NULL;
     queue = enqueue(queue, name);
     temp = addVerteces(ptr, name);
     temp->isvisited = true;
     while (queue) {
          temp = addVerteces(ptr, queue->name);
          tmp = temp->links;
          while (tmp) {
               if (!isVisited(ptr, tmp->name)) {
                    temp = addVerteces(ptr, tmp->name);
                    temp->isvisited = true;
                    queue = enqueue(queue, tmp->name);
               }
               tmp = tmp->next;
          }
          std::cout << queue->name << '\n';
          queue = dequeue(queue);
     }
}
edges* enqueue(edges* ptr, char name[20]){
     static edges* tail;
     if (!ptr) {
          ptr = (edges*) malloc(sizeof(edges));
          strcpy(ptr->name, name);
          ptr->next = NULL;
          tail = ptr;
     }
     else{
          tail->next = (edges*) malloc(sizeof(edges));
          tail = tail->next;
          strcpy(tail->name, name);
          tail->next = NULL;
     }
     return ptr;
}
edges* dequeue(edges* ptr){
     edges* del;
     del = ptr;
     ptr = ptr->next;
     free(del);
     return ptr;
}
bool isVisited(verteces* ptr, char name[20]){
     while (ptr) {
          if (strcmp(ptr->name, name) == 0) {
               if (ptr->isvisited)
                    return true;
               else return false;
          }
          ptr = ptr->next;
     }
     return true;
}
void deleteEdge(verteces* ptr, char name1[20], char  name2[20]){
     verteces* temp;
     edges* tmp, *delEd, *pre = NULL;
     temp = ptr;
     while (temp) {
          if (strcmp(temp->name, name1) == 0)
               break;
          else temp = temp->next;
     }
     tmp = temp->links;
     while (tmp) {
          if (strcmp(tmp->name, name2) == 0){
               delEd = tmp;
               break;
          }
          else{
               pre = tmp;
               tmp = tmp->next;
          }
     }
     if (pre)
          pre->next = delEd->next;
     else temp->links = delEd->next;
     free(delEd);
}
verteces* deleteNode(verteces* ptr, char name[20])
{
     verteces* temp, *delNode, *pre;
     temp = addVerteces(ptr, name);
     viewVert(ptr);
     edges* ed;
     ed = temp->links;
     while (ed) {
          deleteEdge(ptr, temp->name, ed->name);
          deleteEdge(ptr, ed->name, temp->name);
          ed = ed->next;
     }
     if (strcmp(ptr->name, name) == 0) {
          delNode = ptr;
          ptr = ptr->next;
          free(delNode);
          return ptr;
     }
     else{
          temp = ptr;
          while (temp) {
               pre = temp;
               temp = temp->next;
               if (strcmp(temp->name, name) == 0) {
                    delNode = temp;
                    break;
               }
          }
          pre->next = delNode->next;
          free(delNode);
     }
     return ptr;
}
