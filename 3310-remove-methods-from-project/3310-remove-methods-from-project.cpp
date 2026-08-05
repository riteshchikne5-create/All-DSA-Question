class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        
        // Build graph
        vector<vector<int>> graph(n);

        for (auto &edge : invocations) {
            int a = edge[0];
            int b = edge[1];
            graph[a].push_back(b);
        }

        // Find all suspicious methods using DFS
        vector<bool> suspicious(n, false);

        function<void(int)> dfs = [&](int node) {
            suspicious[node] = true;

            for (int next : graph[node]) {
                if (!suspicious[next]) {
                    dfs(next);
                }
            }
        };

        dfs(k);

        // Check if a non-suspicious method invokes a suspicious method
        for (auto &edge : invocations) {
            int a = edge[0];
            int b = edge[1];

            if (!suspicious[a] && suspicious[b]) {
                // Cannot remove suspicious group
                vector<int> ans;

                for (int i = 0; i < n; i++) {
                    ans.push_back(i);
                }

                return ans;
            }
        }

        // Remove suspicious methods
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
