#ifndef GRAM_SET_NODE_H_
#define GRAM_SET_NODE_H_

class GramSetNode {
    
private:
    //字符集大小
    static int Z;
    //字符对应的数值编号，范围[0, Z - 1]，这个数组不清理
    static int * asciiId;
    
private:
    //子节点列表
    GramSetNode ** son;
    
    
public:
    /*
     *  构造函数
     */
    GramSetNode();
    
    /*
     *  析构函数
     */
    virtual ~GramSetNode();
    
public:
    /*
     *  函数：getSonByAscii
     *  功能：返回子节点指针
     */
    GramSetNode * getSonByAscii(char ch);
    
    /*
     *  函数：setSonByAscii
     *  功能：加个新儿子
     */
    void setSonByAscii(char ch, GramSetNode * ns);
    
public:
    /*
     *  函数：init
     *  功能：设置Z和asciiId
     */
    static void init(int Z_, int * asciiId_);
};

#endif // GRAM_SET_NODE_H_
