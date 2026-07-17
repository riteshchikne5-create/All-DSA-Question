class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (size[a] < size[b]) swap(a, b);

        parent[b] = a;
        size[a] += size[b];
    }
};

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        DSU dsu(n);

        unordered_map<int, int> factorIndex;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int f = 2; f * f <= x; f++) {
                if (x % f == 0) {

                    if (factorIndex.count(f))
                        dsu.unite(i, factorIndex[f]);
                    else
                        factorIndex[f] = i;

                    while (x % f == 0)
                        x /= f;
                }
            }

            if (x > 1) {
                if (factorIndex.count(x))
                    dsu.unite(i, factorIndex[x]);
                else
                    factorIndex[x] = i;
            }
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, dsu.size[dsu.find(i)]);
        }

        return ans;
    }
};