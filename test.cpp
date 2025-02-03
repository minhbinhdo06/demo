#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vector<bool>> visited(N, vector<bool>(M, false));
    int peak_count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (visited[i][j]) continue;

            queue<pair<int, int>> q;
            q.push({i, j});
            visited[i][j] = true;
            vector<pair<int, int>> cells;
            cells.push_back({i, j});
            unordered_set<int> current_region;
            current_region.insert(i * M + j);
            int H = grid[i][j];

            // BFS to find all cells in the current region
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;

                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                            if (!visited[nx][ny] && grid[nx][ny] == H) {
                                visited[nx][ny] = true;
                                q.push({nx, ny});
                                cells.push_back({nx, ny});
                                current_region.insert(nx * M + ny);
                            }
                        }
                    }
                }
            }

            // Check if the region is a peak
            bool valid = true;
            for (auto [x, y] : cells) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;

                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

                        int key = nx * M + ny;
                        if (current_region.count(key)) continue;

                        if (grid[nx][ny] >= H) {
                            valid = false;
                            goto end_check;
                        }
                    }
                }
            }

            end_check:
            if (valid) {
                peak_count++;
            }
        }
    }

    cout << peak_count << endl;

    return 0;
}
