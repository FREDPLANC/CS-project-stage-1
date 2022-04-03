#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "centerq.h"
using namespace std;

//插入节点
template <class T>
void centerQueue<T>::addNode(centerNode<T> *node, centerNode<T> *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

template <class T>
void centerQueue<T>::insert(centerNode<T> *node)
{
    if (totalnum == 0)
        min = node;
    else
       {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
        }
    totalnum++;
}

template <class T>
void centerQueue<T>::insert(T key)
{
    centerNode<T> *node;
    node = new centerNode<T>(key);
    if (node == NULL) return ;
    insert(node);
}


//取出最小节点并删除
/*
 * 将"堆的最小结点"从根链表中移除，
 * 这意味着"将最小节点所属的树"从堆中移除!
 */
template <class T>
centerNode<T>* centerQueue<T>::extractMin()
{
    centerNode<T> *p = min;

    if (p == p->right)
        min = NULL;
    else
    {
        removeNode(p);
        min = p->right;
    }
    p->left = p->right = p;

    return p;
}
 
/*
 * 将node链接到root根结点
 */
template <class T>
void centerQueue<T>::link(centerNode<T>* node, centerNode<T>* root)
{
    // 将node从双链表中移除
    removeNode(node);
    // 将node设为root的孩子
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}
 
/* 
 * 创建consolidate所需空间
 */
template <class T>
void centerQueue<T>::makeCons()
{
    int old = maxDegree;

    // 计算log2(keyNum)，"+1"意味着向上取整！
    // ex. log2(13) = 3，向上取整为3+1=4。
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    // 因为度为maxDegree可能被合并，所以要maxDegree+1
    cons = (centerNode<T> **)realloc(cons, 
            sizeof(centerQueue<T> *) * (maxDegree + 1));
}

/* 
 * 合并斐波那契堆的根链表中左右相同度数的树
 */
template <class T>
void centerQueue<T>::consolidate()
{
    int i, d, D;
    centerNode<T> *x, *y, *tmp;

    makeCons();//开辟哈希所用空间
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;
 
    // 合并相同度的根节点，使每个度数的树唯一
    while (min != NULL)
    {
        x = extractMin();                // 取出堆中的最小树(最小节点所在的树)
        d = x->degree;                    // 获取最小树的度数
        // cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (cons[d] != NULL)
        {
            y = cons[d];                // y是"与x的度数相同的树" 
            if (x->key > y->key)        // 保证x的键值比y小
                swap(x, y);

            link(y, x);    // 将y链接到x中
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;
 
    // 将cons中的结点重新加到根表中
    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}
 
/*
 * 移除最小节点
 */
template <class T>
void centerQueue<T>::removeMin()
{
    if (min==NULL)
        return ;

    centerNode<T> *child = NULL;
    centerNode<T> *m = min;
    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, min);
        child->parent = NULL;
    }

    // 将m从根链表中移除
    removeNode(m);
    // 若m是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(m->right)，然后再进行调节。
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;

    delete m;
}
/*
 * 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
 */
template <class T>
bool centerHeap<T>::minimum(T *pkey)
{
    if (min==NULL || pkey==NULL)
        return false;

    *pkey = min->key;
    return true;
}

/*
 * 修改度数
 */
template <class T>
void centerHeap<T>::renewDegree(centerNode<T> *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renewDegree(parent->parent, degree);
}
/*
 * 将node从父节点parent的子链接中剥离出来，
 * 并使node成为"堆的根链表"中的一员。
 */
template <class T>
void centerHeap<T>::cut(centerNode<T> *node, centerNode<T> *parent)
{
    removeNode(node);
    renewDegree(parent, node->degree);
    // node没有兄弟
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = false;
    // 将"node所在树"添加到"根链表"中
    addNode(node, min);
}
/*
 * 对节点node进行"级联剪切"
 *
 * 级联剪切：如果减小后的结点破坏了最小堆性质，
 *     则把它切下来(即从所在双向链表中删除，并将
 *     其插入到由最小树根节点形成的双向链表中)，
 *     然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
 */
template <class T>
void centerHeap<T>::cascadingCut(centerNode<T> *node)
{
    FibNode<T> *parent = node->parent;
    if (parent != NULL)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}
/*
 * 将斐波那契堆中节点node的值减少为key
 */
template <class T>
void FibHeap<T>::decrease(FibNode<T> *node, T key)
{
    FibNode<T> *parent;

    if (min==NULL ||node==NULL)
        return ;

    if ( key>=node->key)
    {
        cout << "decrease failed: the new key(" << key <<") "
             << "is no smaller than current key(" << node->key <<")" << endl;
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        cut(node, parent);
        cascadingCut(parent);
    }

    // 更新最小节点
    if (node->key < min->key)
        min = node;
}

/*
 * 将斐波那契堆中节点node的值增加为key
 */
template <class T>
void centerHeap<T>::increase(centerNode<T> *node, T key)
{
    FibNode<T> *child, *parent, *right;

    if (min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        cout << "increase failed: the new key(" << key <<") "
             << "is no greater than current key(" << node->key <<")" << endl;
        return ;
    }

    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->child != NULL)
    {
        child = node->child;
        removeNode(child);               // 将child从node的子链表中删除
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        addNode(child, min);       // 将child添加到根链表中
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // 如果node不在根链表中，
    //     则将node从父节点parent的子链接中剥离出来，
    //     并使node成为"堆的根链表"中的一员，
    //     然后进行"级联剪切"
    // 否则，则判断是否需要更新堆的最小节点
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                min = right;
            right = right->right;
        }
    }
}
/*
 * 更新斐波那契堆的节点node的键值为key
 */
template <class T>
void centerHeap<T>::update(centerNode<T> *node, T key)
{
    if(key < node->key)
        decrease(node, key);
    else if(key > node->key)
        increase(node, key);
    else
        cout << "No need to update!!!" << endl;
}

template <class T>
void centerHeap<T>::update(T oldkey, T newkey)
{
    FibNode<T> *node;

    node = search(oldkey);
    if (node!=NULL)
        update(node, newkey);
}
/*
 * 在最小堆root中查找键值为key的节点
 */
template <class T>
centerNode<T>* centerHeap<T>::search(centerNode<T> *root, T key)
{
    FibNode<T> *t = root;    // 临时节点
    FibNode<T> *p = NULL;    // 要查找的节点

    if (root==NULL)
        return root;

    do
    {
        if (t->key == key)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}
/*
 * 在斐波那契堆中查找键值为key的节点
 */
template <class T>
centerNode<T>* centerHeap<T>::search(T key)
{
    if (min==NULL)
        return NULL;

    return search(min, key);
}

/*
 * 在斐波那契堆中是否存在键值为key的节点。
 * 存在返回true，否则返回false。
 */
template <class T>
bool centerHeap<T>::contains(T key)
{
    return search(key)!=NULL ? true: false;
}

/*
 * 删除结点node
 */
template <class T>
void centerHeap<T>::remove(centerNode<T> *node)
{
    T m = min->key-1;
    decrease(node, m-1);
    removeMin();
}

template <class T>
void centerHeap<T>::remove(T key)
{
    centerNode<T> *node;

    if (min==NULL)
        return ;

    node = search(key);
    if (node==NULL)
        return ;

    remove(node);
}

/*
 * 销毁斐波那契堆
 */
template <class T>
void centerHeap<T>::destroyNode(centerNode<T> *node)
{
    centerNode<T> *start = node;

    if(node == NULL)
        return;

    do {
        destroyNode(node->child);
        // 销毁node，并将node指向下一个
        node = node->right;
        delete node->left;
    } while(node != start);
}

template <class T>
void centerHeap<T>::destroy()
{
    destroyNode(min);
    free(cons);
}
