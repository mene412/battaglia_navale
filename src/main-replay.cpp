#include "../include/Replay.h"

int main(int argc, char* argv[]){
    Replay replay{"log.txt"};
    replay.start();
    return 0;
}