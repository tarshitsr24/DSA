class Solution {
public:
    bool checkString(string s) {
        int firstB = s.find('b');
        int lastA = s.find_last_of('a');

        if (lastA == string::npos || firstB == string::npos)
            return true;

        return lastA < firstB;
    }
};