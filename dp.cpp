/*
https://leetcode.com/problems/the-dining-philosophers/
*/

class DiningPhilosophers {
    mutex mtx;
    condition_variable cv;
    vector<bool>fork;
    vector<bool>eating;
public:
    DiningPhilosophers(): fork(5, true), eating(5, false) {}

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
                    int id=philosopher;
                    int leftfork=id;
                    int rightfork=(id+1)%5;
                    unique_lock<mutex>lock(mtx);
                    cv.wait(lock,[&](){
                        bool c1=fork[leftfork];
                        bool c2=fork[rightfork];
                        bool c3=!eating[leftfork];
                        bool c4=!eating[rightfork];
                        return(c1 && c2 && c3 && c4);
                    });
                    fork[leftfork]=false;
                    fork[rightfork]=false;
                    eating[id]=true;
                    pickLeftFork();
                    pickRightFork();
                    eat();
                    putLeftFork();
                    putRightFork();
                    fork[leftfork]=true;
                    fork[rightfork]=true;
                    eating[id]=false;
                    cv.notify_all();

		
    }
};