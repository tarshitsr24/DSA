class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int firstCritical = -1;
        int prevCritical = -1;

        int minDistance = INT_MAX;
        int maxDistance = -1;

        while (curr->next != nullptr) {
            bool isMaxima = curr->val > prev->val &&
                            curr->val > curr->next->val;

            bool isMinima = curr->val < prev->val &&
                            curr->val < curr->next->val;

            if (isMaxima || isMinima) {
                
                if (firstCritical == -1) {
                    // First critical point
                    firstCritical = index;
                } else {
                    // Distance from previous critical point
                    minDistance = min(minDistance, index - prevCritical);

                    // Distance from first critical point
                    maxDistance = index - firstCritical;
                }

                prevCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        return {minDistance, maxDistance};
    }
};