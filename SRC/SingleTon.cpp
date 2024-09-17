#include "SingleTon.h"

int main(){
    Example* Do = CSingleTon<Example>::GetInstance();
    cout << Do << endl;
    Example* Do1 = CSingleTon<Example>::GetInstance();
    cout << Do1 << endl;
    return Do->PrintfExample();
}