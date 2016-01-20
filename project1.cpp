#include "thread.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int max_disk_queue = 0;
vector<int> q;

struct thread_arg {
    int argc;
    char** argv;
};

struct Request {
    string name;
    int num;
};

void requester_thread(void *a) {
    Request *r = (Request*) a;
    cout << r->num << endl;
}

void server_thread(void *a) {
    
    thread_arg *arg = (thread_arg*) a;
    for (int i = 0; i < arg->argc-2; i++) {
        Request *r = new Request{arg->argv[i+2],i};
        thread t((thread_startfunc_t) requester_thread, (void *) r);
    }
    
    
}

int main (int argc, char **argv){
    
    thread_arg *arg = new thread_arg{argc, argv};
    
    max_disk_queue = stoi(argv[1]);
    

    
    cpu::boot((thread_startfunc_t) server_thread,(void *) arg, 0);
    
}