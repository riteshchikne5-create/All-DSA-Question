class Solution {
public:
    struct Node {
        char leftChar, rightChar;
        int leftLen, rightLen;
        int best, len;

        Node() {
            leftChar = rightChar = '#';
            leftLen = rightLen = best = len = 0;
        }

        Node(char c) {
            leftChar = rightChar = c;
            leftLen = rightLen = best = len = 1;
        }
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.leftLen = a.leftLen;
        res.rightLen = b.rightLen;

        res.best = max(a.best, b.best);

        // Can join suffix of a and prefix of b
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.rightLen + b.leftLen);

            // Entire left segment has the same character
            if (a.leftLen == a.len) {
                res.leftLen = a.len + b.leftLen;
            }

            // Entire right segment has the same character
            if (b.rightLen == b.len) {
                res.rightLen = b.len + a.rightLen;
            }
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        this->s = s;

        int n = s.length();
        int k = queryIndices.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            update(
                1,
                0,
                n - 1,
                queryIndices[i],
                queryCharacters[i]
            );

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};