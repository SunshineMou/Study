#include<iostream>

using namespace std;

class static_test{
    public:
        static static_test* instance();

        void run();

        void stop();
};

static_test* static_test::instance(){
    void* iStaic = NULL;
    if(iStatic == NULL)
        iStatic = (static_test*)new static_test;
    return iStatic;
}

void static_test::run(){
    cout << "Function-> run" << endl;
}

void static_test::stop(){
    cout << "Function-> stop" << endl;
}


int main(){
    static_test::instance()->run();
    static_test::instance()->stop();

    return 0;
}

