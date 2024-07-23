/*
https://leetcode.com/problems/print-zero-even-odd/description/
*/

class ZeroEvenOdd {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool iseven;
    bool isodd;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        iseven=false;
        isodd=false;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
         
        for(int i=0;i<n;i++){
            unique_lock<mutex>lock(mtx);
            cv.wait(lock,[&](){
                bool c1=iseven;
                bool c2=isodd;
                return !c1 && !c2;
            });
            printNumber(0);
            // condition for next 
            if(i%2==0){
                isodd=true;
            }else{
                iseven=true;
            }
            cv.notify_all();
        }

    }

    void even(function<void(int)> printNumber) { 
        for(int i=2;i<=n;i+=2){
            unique_lock<mutex>lock(mtx);
            cv.wait(lock,[&](){
                bool c1=iseven;
                return c1;
            });
            printNumber(i);
            iseven=false;
            cv.notify_all();
        }

    }

    void odd(function<void(int)> printNumber) {             
        for(int i=1;i<=n;i+=2){
            unique_lock<mutex>lock(mtx);
            cv.wait(lock,[&](){
                bool c=isodd;
                return c;
            });
            printNumber(i);
            isodd=false;
            cv.notify_all();
        }
    }
};