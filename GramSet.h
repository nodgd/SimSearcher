#ifndef GRAM_SET_H_
#define GRAM_SET_H_

#include "GramSetNode.h"

class GramSet {
    
private:
    //字符集大小
    static int Z;
    //字符对应的数值编号，范围[0, Z - 1]，这个数组不清理
    static int * asciiId;
    
private:
    //根节点
    GramSetNode * root;
    
public:
    /*
     *  构造函数
     */
    GramSet();
    
    /*
     *  析构函数
     */
    virtual ~GramSet();

    
public:
    /*
     *  函数：init
     *  功能：设置Z和asciiId
     */
    static void init(int Z_, int * asciiId_);
};

#endif // GRAM_SET_H_
