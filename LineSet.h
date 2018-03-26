#ifndef LINE_SET_H_
#define LINE_SET_H_

#include <vector>

/**
 *  对于每个Gram存储包含它的所有行的编号集合。
 *  现在只是一个有序的std::vector，以后可能会搞点别的。
 */
class LineSet {
    
public:
    std::vector < int > lineList;
    
public:
    /*
     *  构造函数
     */
    LineSet();
    
    /*
     *  析构函数
     */
    virtual ~LineSet();
    
public:
    /*
     *  函数：insertLine
     *  功能：插入一个行编号
     */
    void insertLine(int line);
    
    /*
     *  函数：getSize
     *  功能：获取行集合的大小
     */
    int getSize();
    
    /*
     *  函数：getLineById
     *  功能：获取第i个行编号
     */
    int getLineById(int i);
    
};

#endif // LINE_SET_H_
