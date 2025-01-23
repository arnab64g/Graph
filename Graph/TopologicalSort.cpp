#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void topologicalRecurtion(vector<int> m[], int v, int n, stack<int> &s, bool visited[]) {
    visited[n] = true;
    for (int val : m[n])
    {
        if (visited[val] == false)
        {
            topologicalRecurtion(m, v, val, s, visited);
        }
    }
    s.push(n);
}

void topologicalSort(vector<int> m[], int v){
    stack<int> s;
    bool visited[20];

    for (int i = 0; i < 20; i++)
    {
        visited[i] = false;
    }
    
    for (int i = 0; i < v; i++)
    {
        if (visited[i] == false)
        {
            topologicalRecurtion(m, v, i, s, visited);
        }
    }

    cout << "Sorted: " << endl;

    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> m[20];
    int e, v, s, d;
    cout << "Number of Vertices: ";
    cin >> v;
    cout << "Number of Edges: ";
    cin >> e;
    
    for (int i = 0; i < e; i++)
    {
        cout << "(s, d): ";
        cin >> s >> d;
        m[s].push_back(d);
    }
    
    topologicalSort(m, v);

    return 0;
}
