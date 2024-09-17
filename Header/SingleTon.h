#ifndef __SINGLETON__
#define __SINGLETON__
#include <iostream>
#include <iostream>
using namespace std;
/*
*static instance是为了提供全局访问点；
*static GetInstance是为了通过类名直接调用。
*一般成员函数需要实例才能使用，但是GetInstance本意就是用来生成实例，所以其需要是static类型的
*/
template <class T>
class CSingleTon{
private:
    static T* instance;
    CSingleTon() = default;
    ~CSingleTon() = default;
    CSingleTon(const CSingleTon&) = delete; //  禁止拷贝构造函数和赋值操作符
    CSingleTon& operator=(const CSingleTon&) = delete;  
public:
    static T* GetInstance(){
        if(instance != nullptr){
            return instance;
        }
        /*
        *加（）是为了确保其调用构造函数；不加的话，假设构造函数=default，则产生问题。
        */
        instance = new T();
        return instance;
    }
};
/*
*static成员变量属于类，需要在类外部且使用前进行初始化
*/
template <class T>
T* CSingleTon<T>::instance = nullptr;

class Example
{
private:
    Example() = default;
    ~Example() = default;
    /*友元声明为private或者public对单例性质并没有什么影响，只不过private可以：
    *表明该类的主要成员和接口是私有的，只有被声明的友元类可以访问；
    *将友元关系隐藏起来，只暴露接口部分，减少外界对类内部实现细节的关注
    */
   friend CSingleTon<Example>;
public: 
    int PrintfExample(){
        printf("You are yes!");
        return 0;
    }
};

#endif //(__SINGLETON__)