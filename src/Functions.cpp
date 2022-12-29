#include "Functions.h"
#include <vector>
using namepsace std;
char num_to_lett(int t)
{
    vector<char> letters={'a','b','c','d','e','f','g','h','i','l','m','n'};
    return letters[t-1];
};
int char_to_int(char t)
{
   vector<char> letters={'a','b','c','d','e','f','g','h','i','l','m','n'};
    int s=0;
    while(letters[s]!=t)
        s++;
    return s+1;
};
