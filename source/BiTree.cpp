#include <iostream>
#include<bits/stdc++.h>

using namespace std;

typedef struct BiTree {
    char data;
    struct BiTree* lChild, * rChild;
    bool isFirst;
}BiTree;

typedef struct BiThrTree {
    char data;
    struct BiThrTree* lChild, * rChild;
    bool lTag, rTag;
}BiThrTree;

void createBiTree(BiTree*& p, char nullPointerCharacter) {//DRL
    char dataIn;
    cin >> dataIn;
    if (dataIn == nullPointerCharacter)
        p = NULL;
    else {
        p = new BiTree;
        p->data = dataIn;
        p->isFirst = true;
        createBiTree(p->lChild, nullPointerCharacter);
        createBiTree(p->rChild, nullPointerCharacter);
    }
}

void createBiTree(BiThrTree*& p, char nullPointerCharacter) {//DRL
    char dataIn;
    cin >> dataIn;
    if (dataIn == nullPointerCharacter)
        p = NULL;
    else {
        p = new BiThrTree;
        p->data = dataIn;
        createBiTree(p->lChild, nullPointerCharacter);
        createBiTree(p->rChild, nullPointerCharacter);
    }
}

void preorderTraversal(BiTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            cout << p->data;
            preorderTraversal(p->lChild, isRecursive);
            preorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<BiTree*>vis;
        while (p || !vis.empty()) {
            if (p) {
                cout << p->data;
                vis.push(p);
                p = p->lChild;
            }
            else {
                p = vis.top()->rChild;
                vis.pop();
            }
        }
    }
}

void inorderTraversal(BiTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            inorderTraversal(p->lChild, isRecursive);
            cout << p->data;
            inorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<BiTree*>vis;
        while (p || !vis.empty()) {
            if (p) {
                vis.push(p);
                p = p->lChild;
            }
            else {
                cout << vis.top()->data;
                p = vis.top()->rChild;
                vis.pop();
            }
        }
    }
}

void postorderTraversal(BiTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            postorderTraversal(p->lChild, isRecursive);
            postorderTraversal(p->rChild, isRecursive);
            cout << p->data;
        }
    }
    else
    {
        stack<BiTree*>vis;
        while (p || !vis.empty()) {
            if (p) {
                vis.push(p);
                p = p->lChild;
            }
            else {
                if (vis.top()->isFirst) {
                    vis.top()->isFirst = false;
                    p = vis.top()->rChild;
                }
                else {
                    cout << vis.top()->data;
                    vis.pop();
                }
            }
        }
    }
}

void doubleTraversal(BiTree* p) {
    if (p) {
        cout << p->data;
        doubleTraversal(p->lChild);
        cout << p->data;
        doubleTraversal(p->rChild);
    }
}

void levelorderTraversal(BiTree* p) {
    if (p) {
        queue<BiTree*> vis;
        vis.push(p);
        while (!vis.empty()) {
            cout << vis.front()->data;
            if (vis.front()->lChild)
                vis.push(vis.front()->lChild);
            if (vis.front()->rChild)
                vis.push(vis.front()->rChild);
            vis.pop();
        }
    }
}

int getDeepth(BiTree* p) {
    if (!p)
        return 0;
    int lDeepth = getDeepth(p->lChild), rDeepth = getDeepth(p->rChild);
    if (lDeepth >= rDeepth)
        return (lDeepth + 1);
    return (rDeepth + 1);
}

int getSize(BiTree* p) {
    if (!p)
        return 0;
    return (1 + getSize(p->lChild) + getSize(p->rChild));
}

int getLeafAmount(BiTree* p) {
    if (!p)
        return 0;
    if (!p->lChild && !p->rChild)
        return 1;
    return getLeafAmount(p->lChild) + getLeafAmount(p->rChild);
}

int getLevelWidth(BiTree* p, int level) {
    if (!p)
        return 0;
    if (level == 1)
        return 1;
    return getLevelWidth(p->lChild, level - 1) + getLevelWidth(p->rChild, level - 1);
}

int getWidth(BiTree* p) {
    if (!p)
        return 0;
    int deep = getDeepth(p), maxWidth = 0, tmpWidth;
    for (int i = 1; i <= deep; i++) {
        tmpWidth = getLevelWidth(p, i);
        if (tmpWidth >= maxWidth)
            maxWidth = tmpWidth;
    }
    return maxWidth;
}

//biTree* pre = new biTree{ ' ',NULL,NULL,false,false,true };
BiThrTree* pre = new BiThrTree;
void inorderThreading(BiThrTree* p) {
    if (p) {
        inorderThreading(p->lChild);
        if (!p->lChild) {
            p->lTag = 1;
            p->lChild = pre;
        }
        else p->lTag = 0;
        if (!pre->rChild) {
            pre->rTag = 1;
            pre->rChild = p;
        }
        else pre->rTag = 0;
        pre = p;
        inorderThreading(p->rChild);
    }
}

void inorderThreadingWithHead(BiThrTree* p, BiThrTree*& head) {
    head = new BiThrTree;
    head->lTag = 0; head->rTag = 1;
    head->lChild = head->rChild = head;
    if (p){
        head->lChild = p;
        pre = head;
        inorderThreading(p);
        pre->rTag = 1;
        pre->rChild = head;
        head->rChild = pre;
    }
}

void inorderThreadTraversal(BiThrTree* head) {
    BiThrTree* p = head->lChild;
    while (p != head) {
        while (!p->lTag) {
            p = p->lChild;
        }
        cout << p->data;
        while (p->rTag && p->rChild != head) {
            p = p->rChild;
            cout << p->data;
        }
        p = p->rChild;
    }
}

int putFathers(BiTree* p, char x) {
    if (!p)
        return 0;
    if (p->data == x)
        return 1;
    if (putFathers(p->lChild, x) || putFathers(p->rChild, x)) {
        cout << p->data << " ";
        return 1;//return 0; Only put the parent node of the target value.
    }
    return 0;
}

//int main()
//{
//    BiTree* root;
//    createBiTree(root, '@');
//    cout << getWidth(root);
//    /*BiThrTree* thrt, * head;
//    createBiTree(thrt,'@');
//    inorderThreadingWithHead(thrt,head);
//    inorderThreadTraversal(head);*/
//    return 0;
//}
