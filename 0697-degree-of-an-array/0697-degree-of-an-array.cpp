class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> freq;
        unordered_map<int, int> first;
        unordered_map<int, int> last;

        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];

            if (first.find(x) == first.end()) {
                first[x] = i;
            }

            last[x] = i;
            freq[x]++;
        }

        int degree = 0;
        for (auto &p : freq) {
            degree = max(degree, p.second);
        }

        int ans = nums.size();

        for (auto &p : freq) {
            if (p.second == degree) {
                ans = min(ans, last[p.first] - first[p.first] + 1);
            }
        }

        return ans;
    }
};