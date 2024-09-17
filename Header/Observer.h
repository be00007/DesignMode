#ifndef __OBSERVER__
#define __OBSERVER__
#include <iostream>  
#include <vector>  
#include <memory>  
#include <list>
#include <algorithm>
using namespace std;

/*
*从表面来说，观察者和被观察者的类相互交流，
*也不需要采用友元函数的方式，因为两者交流之中是对整个类进行访问，并不是类中的成员
*/
class CSubject; //  增加声明

class CObserver
{
// 为了派生类访问
protected:
    shared_ptr<CSubject> m_CSubject;
    string m_strName;
public:
    CObserver(const shared_ptr<CSubject> pCSubject, const string &name="unknow")
        : m_CSubject(pCSubject), m_strName(name){}
    virtual ~CObserver() = default;
    virtual void Update() = 0;
    virtual const string &name(){return m_strName;}
};
class CSubject{
protected:
    list<shared_ptr<CObserver>> m_pCObserver_list;
    int m_nState;
public:
    CSubject() : m_nState(0){}
    virtual ~CSubject() = default;

    virtual void Attach(const shared_ptr<CObserver> pCObserver) = 0;
    virtual void Detach(const shared_ptr<CObserver> pCObserver) = 0;
    virtual void Notify() = 0;

    virtual void SetSate(int state){
        m_nState = state;
        printf("Subject update!\n");
    }
    virtual int GetState() {return m_nState;}
};

class ConcreteCSubject : public CSubject{
public:
    void Attach(const shared_ptr<CObserver> pCObserver) override{
        auto iter = find(m_pCObserver_list.begin(), m_pCObserver_list.end(), pCObserver);
        if(iter == m_pCObserver_list.end()){
            m_pCObserver_list.emplace_back(pCObserver);
            printf("Attach observer\n");
        }else{
            printf("Attach failed, have it\n");
        }
    }
    void Detach(const shared_ptr<CObserver> pCObserver) override{
        auto iter = find(m_pCObserver_list.begin(), m_pCObserver_list.end(), pCObserver);
        if(iter == m_pCObserver_list.end()){
            printf("Detach failed, have no it\n");
        }else{
            // remove删除相等的值，如果存在多个相等的值;erase需要预删元素的迭代器
            m_pCObserver_list.remove(pCObserver);
        }
    }
    void Notify() override{
        if(!m_pCObserver_list.empty()){
            auto it = m_pCObserver_list.begin();
            while (it != m_pCObserver_list.end())
            {
                (*it++)->Update();
            }
        }  
    }
};

class ConcreteCObserver : public CObserver{
public:
    ConcreteCObserver() = default; // 添加默认构造函数

    ConcreteCObserver(const shared_ptr<CSubject> pCSubject, const string &name="unknow")
        : CObserver(pCSubject, name){}
    void Update() override{
        printf("This name is:%s\n", m_strName.c_str());
    }
};


#endif // __OBSERVER__