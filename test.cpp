#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

vector<int> nearestNeighbor(int n, const vector<vector<int>> &c)
{
    vector<int> path;
    vector<bool> visited(n + 1, false);
    int current = 1;
    path.push_back(current);
    visited[current] = true;

    for (int i = 1; i < n; ++i)
    {
        int next = -1;
        int min_dist = INT_MAX;
        for (int j = 1; j <= n; ++j)
        {
            if (!visited[j] && c[current][j] < min_dist)
            {
                min_dist = c[current][j];
                next = j;
            }
            else if (!visited[j] && c[current][j] == min_dist && j < next)
            {
                next = j;
            }
        }
        path.push_back(next);
        visited[next] = true;
        current = next;
    }
    return path;
}

int calculateCost(const vector<int> &path, const vector<vector<int>> &c)
{
    int cost = 0;
    for (size_t i = 0; i < path.size(); ++i)
    {
        int j = (i + 1) % path.size();
        cost += c[path[i]][path[j]];
    }
    return cost;
}

vector<int> twoOpt(int n, const vector<int> &path, const vector<vector<int>> &c)
{
    vector<int> newPath = path;
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 2; j < n; ++j)
            {
                int a = newPath[i];
                int b = newPath[(i + 1) % n];
                int c_node = newPath[j];
                int d = newPath[(j + 1) % n];
                int current = c[a][b] + c[c_node][d];
                int potential = c[a][c_node] + c[b][d];
                if (potential < current)
                {
                    reverse(newPath.begin() + i + 1, newPath.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
    return newPath;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> c(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> c[i][j];
        }
    }

    vector<int> path = nearestNeighbor(n, c);
    path = twoOpt(n, path, c);

    cout << calculateCost(path,c) << endl;
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
            cout << " ";
        cout << path[i];
    }
    cout << endl;

    return 0;
}
