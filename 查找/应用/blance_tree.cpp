///二叉排序树的插入查找函数实现。其数据结构定义如下。
typedef char KeyType;
typedef string ValueType;

struct KVNode { //结点类
	KeyType key;
	ValueType value;
};

typedef struct _Node { 
    KVNode data;           	//结点数据域
    struct _Node*  left; 	//结点左子树的指针
    struct _Node*  right; 	//结点右子树的指针
} BSNode, *BSTree;

// 提供的创建二叉树结点的函数 CreateNode
BSNode * CreateNode(KeyType key, ValueType value) {
	BSNode *r = new BSNode;
	r->data.key = key;
	r->data.value = value;
	r->left = NULL;
	r->right = NULL;
	return r;
}

//1 二叉排序树-查找，其中 r 是二叉排序树的根，k是待查找的关键字；如果查找到了，返回结点指针；否则返回NULL

BSTree search( const BSTree r, const KeyType & k);

//2 二叉排序树-插入，其中 root 是二叉排序树的根，k是待插入的关键字，v是关键字对应的值。
void insert(BSTree &root, const KeyType & k, const ValueType & v);