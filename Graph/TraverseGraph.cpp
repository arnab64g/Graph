#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

void createGraph(vector<int>[]);
void showGraph(vector<int>[]);
void traverseGraphBFS(vector<int>[]);
void traverseGraphDFS(vector<int>[]);

int main()
{
    vector<int> v[10];
    createGraph(v);

    cout<<"\nGraph Created." << endl;

    showGraph(v);

    traverseGraphBFS(v);
    traverseGraphDFS(v);

    std::cout << "\n\n";
    return 0;
}

void createGraph(vector<int> v[])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (j % 2 != i%2)
                v[i].push_back(j);
}

void showGraph(vector<int> v[])
{
    for (int i = 0; i < 10; i++){
        cout << i << ": ";
        for(int x: v[i])
            cout<<x<<' ';
        cout<<endl;
    }
}

void traverseGraphBFS(vector<int> v[])
{
    queue<int> q;
    bool visited[10] = {false};
    int n;
    int vts;
    cout<<"\nStarting Verteces: ";
    cin>> n;
    q.push(n);
    visited[n] = true;
    while (!q.empty()){
        vts = q.front();
        for(int x: v[vts])
            if (visited[x] == false){
                q.push(x);
                visited[x] = true;
            }
        cout << " -> " <<vts;
        q.pop();
    }
    cout <<endl;
}

void traverseGraphDFS(vector<int> v[])
{
    stack<int> s;
    int n, tv;
    bool visited[10] = {false};
    bool iselse;
    cout << "Traverse from: ";
    cin>>n;
    s.push(n);
    cout << " -> " << n;
    visited[n] = true;
    while (!s.empty()){
        tv = s.top();
        iselse = false;
        for(int x:v[tv])
            if (!visited[x]){
                iselse = true;
                s.push(x);
                cout << " -> " << x;
                visited[x] = true;
                break;
            }
        if (!iselse)
            s.pop();
    }
}
