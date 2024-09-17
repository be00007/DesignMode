#include "Observer.h"

int main(){
    // 建立目标 //  配套使用
    shared_ptr<CSubject> ConcreteCSubject1 = make_shared<ConcreteCSubject>();
    shared_ptr<CObserver> ConcreteCObserver1 = make_shared<ConcreteCObserver>(ConcreteCSubject1, "2");

    ConcreteCSubject1->Attach(ConcreteCObserver1);
    ConcreteCSubject1->SetSate(2);
    ConcreteCSubject1->Notify();
    ConcreteCSubject1->Detach(ConcreteCObserver1);

    return 0;
}


int GetValidCharByteCount(const char* str, int num) {
    if (!str) return 0;
    int ret = 0;
    int len = strlen(str);
    
    if(num > len) return len; // 如果num大于字符串长度，则限制为字符串长度
    
    const char* sptr;
    for (sptr = str; (sptr - str) < len && ret < num && *sptr;) {
        unsigned char ch = (unsigned char)(*sptr);
        
        if (ch < 0x80) {
            // ASCII character (1 byte)
            sptr++;
            ret++;
        } else if (ch < 0xc0) {
            // Invalid UTF-8
            sptr++;
            ret++;
        } else if (ch < 0xe0) {
            // Two-byte character
            sptr += 2;
            ret++;
        } else if (ch < 0xf0) {
            // Three-byte character
            sptr += 3;
            ret++;
        } else {
            // Four-byte character
            sptr += 4;
            ret++;
        }
    }
    
    return sptr - str; // 返回有效字符所占据的字节数
}