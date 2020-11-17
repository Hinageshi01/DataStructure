#include <iostream>
#include<bits/stdc++.h>

using namespace std;

typedef struct biTree {
    char data;
    struct biTree* lChild, * rChild;
    bool isFirst;
}biTree;

typedef struct biThrTree {
    char data;
    struct biThrTree* lChild, * rChild;
    bool lTag, rTag;
}biThrTree;

void createBiTree(biTree*& p, char nullPointerCharacter) {//DRL
    char dataIn;
    cin >> dataIn;
    if (dataIn == nullPointerCharacter)
        p = NULL;
    else {
        p = new biTree;
        p->data = dataIn;
        p->isFirst = true;
        createBiTree(p->lChild, nullPointerCharacter);
        createBiTree(p->rChild, nullPointerCharacter);
    }
}

void createBiTree(biThrTree*& p, char nullPointerCharacter) {//DRL
    char dataIn;
    cin >> dataIn;
    if (dataIn == nullPointerCharacter)
        p = NULL;
    else {
        p = new biThrTree;
        p->data = dataIn;
        createBiTree(p->lChild, nullPointerCharacter);
        createBiTree(p->rChild, nullPointerCharacter);
    }
}

void preorderTraversal(biTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            cout << p->data;
            preorderTraversal(p->lChild, isRecursive);
            preorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<biTree*>vis;
        while (p || !vis.empty())
        {
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

void inorderTraversal(biTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            inorderTraversal(p->lChild, isRecursive);
            cout << p->data;
            inorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<biTree*>vis;
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

void postorderTraversal(biTree* p, bool isRecursive) {
    if (isRecursive) {
        if (p) {
            postorderTraversal(p->lChild, isRecursive);
            postorderTraversal(p->rChild, isRecursive);
            cout << p->data;
        }
    }
    else
    {
        stack<biTree*>vis;
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

void levelorderTraversal(biTree* p) {
    queue<biTree*> vis;
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

int getDeepth(biTree* p) {
    if (!p) return 0;
    else {
        int lDeepth = getDeepth(p->lChild), rDeepth = getDeepth(p->rChild);
        if (lDeepth > rDeepth) return (lDeepth + 1);
        else return (rDeepth + 1);
    }
}

int getSize(biTree* p) {
    if (p == NULL) return 0;
    else return (1 + getSize(p->lChild) + getSize(p->rChild));
}

int getLeafAmount(biTree* p) {
    if (!p) return 0;
    else
        if (!p->lChild && !p->rChild) return 1;
        else  return getLeafAmount(p->lChild) + getLeafAmount(p->rChild);
}

//biTree* pre = new biTree{ ' ',NULL,NULL,false,false,true };
biThrTree* pre = new biThrTree;
void inorderThreading(biThrTree*& p) {
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

void inorderThreadingWithHead(biThrTree* p, biThrTree*& head) {
    head = new biThrTree;
    head->lTag = 0; head->rTag = 1;
    head->rChild = head;
    if (!p)
        head->lChild = head;
    else {
        head->lChild = p;
        pre = head;
        inorderThreading(p);
        pre->rTag = 1;
        pre->rChild = head;
        head->rChild = pre;
    }
}

void inorderTraversalThread(biThrTree* head) {
    biThrTree* p = head->lChild;
    while (p != head) {
        while (!p->lTag) p = p->lChild;
        cout << p->data;
        while (p->rTag && p->rChild != head) {
            p = p->rChild;
            cout << p->data;
        }
        p = p->rChild;
    }
}

int putFathers(biTree* p, char x) {
    if (!p) return 0;
    if (p->data == x) return 1;
    if (p) {
        if (putFathers(p->lChild, x) || putFathers(p->rChild, x)) {
            cout << p->data << " ";
            return 1;
        }
    }
    return 0;
}

//int main()
//{
//    /*biTree* root;
//    createBiTree(root, '@');
//    preorderTraversal(root, 1); cout << " ";
//    preorderTraversal(root, 0);
//    cout << endl;
//    inorderTraversal(root, 1); cout << " ";
//    inorderTraversal(root, 0);
//    cout << endl;
//    postorderTraversal(root, 1); cout << " ";
//    postorderTraversal(root, 0);
//    cout << endl;
//    cout << getDeepth(root) <<  " ";
//    cout << getSize(root) <<  " ";
//    cout << getLeafAmount(root) <<  " ";*/
//    biThrTree* thrt, * head;
//    createBiTree(thrt,'@');
//    inorderThreadingWithHead(thrt,head);
//    inorderTraversalThread(head);
//    return 0;
//}
