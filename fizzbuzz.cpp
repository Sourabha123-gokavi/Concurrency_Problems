/*
https://leetcode.com/problems/fizz-buzz-multithreaded/description/
*/

class FizzBuzz {
private:
    int n;
    int current;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->current=1;
    }


void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() {
                bool c1=current > n;
                bool c2=(current % 3 == 0 && current % 5 != 0);
                return c1 || c2;
            });
            if (current > n) return;
            printFizz();
            ++current;
            cv.notify_all();
        }
    }


    void buzz(function<void()> printBuzz) {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() {
                bool c1=current > n;
                bool c2=(current % 5 == 0 && current % 3 != 0);
                return c1 || c2;
            });
            if (current > n) return;
            printBuzz();
            ++current;
            cv.notify_all();
        }
    }


    void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() {
                bool c1=current > n;
                bool c2=(current % 3 == 0 && current % 5 == 0);
                return c1 || c2;
            });
            if (current > n) return;
            printFizzBuzz();
            ++current;
            cv.notify_all();
        }
    }


    void number(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() {
                bool c1=current > n;
                bool c2=(current % 3 != 0 && current % 5 != 0);
                return c1 || c2;
            });
            if (current > n) return;
            printNumber(current);
            ++current;
            cv.notify_all();
        }
    }
};