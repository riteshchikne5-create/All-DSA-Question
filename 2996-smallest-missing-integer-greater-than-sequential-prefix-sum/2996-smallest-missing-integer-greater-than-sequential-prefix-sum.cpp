class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];

        // Find the longest sequential prefix
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }

        // Find the smallest missing number >= sum
        int x = sum;

        while (true) {
            bool found = false;

            for (int num : nums) {
                if (num == x) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return x;
            }

            x++;
        }
    }
};