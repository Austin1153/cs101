#include <iostream>
#include <string>

using namespace std;

class Clock {
    protected:
        int Hour;
        int minute;
        int second;
        string meridian;
    public:
        Clock(int h, int m, int s, string M) {
            if (h > 12 || h < 0) cout << "invalid Hour";
            else Hour = h;
            if (m > 59 || m < 0) cout << "invalid minute";
            else minute = m;
            if (s > 59 || s < 0) cout << "invalid second";
            else second = s;
            if (M != "AM" && M != "PM") cout << "invalid meridian";
            else meridian = M;
        }
        void display() {
            cout << Hour << ':' << minute << ':' << second << ' ' << meridian;
        }
};

class StandardClock : Clock {
    public:
        StandardClock(int h, int m, int s, string M) : Clock(h, m, s, M) {};
        void display() {
            if (meridian == "AM") cout << "上午 ";
            else cout << "下午 ";
            cout << Hour << ':' << minute << ':' << second;
        }
};

class MilitaryClock : Clock {
    public:
        MilitaryClock(int h, int m, int s, string M) : Clock(h, m, s, M) {};
        void display() {
            if (meridian == "AM") cout << Hour;
            else cout << Hour + 12;
            cout << ':' << minute << ':' << second;
        }
};

int main() {
    Clock cc(10, 25, 43, "AM");
    StandardClock sc(10, 25, 43, "AM");
    MilitaryClock mc(10, 25, 43, "PM");
    cc.display();
    sc.display();
    mc.display();
    return 0;
}