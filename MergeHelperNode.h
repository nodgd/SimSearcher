#ifndef MERGE_HELPER_NODE_H_
#define MERGE_HELPER_NODE_H_

class MergeHelperNode {
    
private:
    //上个节点
    MergeHelperNode * prev;
    //下个节点
    MergeHelperNode * next;
    
public:
    MergeHelperNode();
    virtual ~MergeHelperNode();
    
    friend class MergeHelper;
};

#endif // MERGE_HELPER_NODE_H_
