/*
https://leetcode.com/problems/building-h2o/description/
*/
class H2O {
private:
    int H;
    int O;
    mutex mtx;
    condition_variable cv;
public:
    H2O() {
        H=0;
        O=0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex>lock(mtx);//lock 
        //wait until we have enough oxygen
        cv.wait(lock,[&](){
            return H< 2*(O+1);
        });
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        H++;
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[&](){
            return O<H/2;
        });
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        O++;
        cv.notify_all();
    }
};