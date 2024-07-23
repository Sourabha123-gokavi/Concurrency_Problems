/*
https://leetcode.com/problems/print-foobar-alternately/description/
*/

class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    int f;
    int b;

public:
    FooBar(int n) {
        this->n = n;
        f=0;
        b=0;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex>lock(mtx);//lock it
            cv.wait(lock,[&](){
                return f==b;
            });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            f++;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex>lock(mtx);
            cv.wait(lock,[&](){
                return b+1==f;
            });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            b++;
            cv.notify_all();
        }
    }
};