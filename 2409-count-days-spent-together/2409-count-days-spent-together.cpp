class Solution {
public:
    int dayOfYear(string s) {
        int month = stoi(s.substr(0, 2));
        int date = stoi(s.substr(3, 2));

        int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};

        int day = date;

        for (int i = 0; i < month - 1; i++) {
            day += daysInMonth[i];
        }

        return day;
    }

    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        int a1 = dayOfYear(arriveAlice);
        int a2 = dayOfYear(leaveAlice);
        int b1 = dayOfYear(arriveBob);
        int b2 = dayOfYear(leaveBob);

        int start = max(a1, b1);
        int end = min(a2, b2);

        if(start>end){
            return 0;
        }

        return end-start+1;


    }
};