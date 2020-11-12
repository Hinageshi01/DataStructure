#include <iostream>
#include<bits/stdc++.h> 

using namespace std;


typedef struct biTree {
    char data;
    struct biTree* lChild, * rChild;
    bool isFirst = true;
}biTree;

typedef struct biThrTree {
    char data;
    struct biThrTree* lChild, * rChild;
    bool lTag, rTag;
}biThrTree;

void createBiTree(biTree*& p,char nullPointerCharacter) {//DRL
    char dataIn;
    cin >> dataIn;
    if (dataIn == nullPointerCharacter)
        p = NULL;
    else {
        p = new biTree;
        p->data = dataIn;
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

void preorderTraversal(biTree* p,bool isRecursive) {
    if (isRecursive) {
        if (p) {
            cout << p->data;
            preorderTraversal(p->lChild, isRecursive);
            preorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<biTree*>vis;
        biTree* tmp = p;
        while (tmp||!vis.empty())
        {
            if (tmp) {
                cout << tmp->data;
                vis.push(tmp);
                tmp = tmp->lChild;
            }
            else {
                tmp = vis.top()->rChild;
                vis.pop();
            }
        }
    }
}

void inorderTraversal(biTree* p,bool isRecursive) {
    if (isRecursive) {
        if (p) {
            inorderTraversal(p->lChild, isRecursive);
            cout << p->data;
            inorderTraversal(p->rChild, isRecursive);
        }
    }
    else {
        stack<biTree*>vis;
        biTree* tmp = p;
        while (tmp || !vis.empty()) {
            if (tmp) {
                vis.push(tmp);
                tmp = tmp->lChild;
            }
            else {
                cout << vis.top()->data;
                tmp = vis.top()->rChild;
                vis.pop();
            }
        }
    }
}

void postorderTraversal(biTree* p,bool isRecursive) {
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
        biTree* tmp = p;
        while (tmp||!vis.empty()) {
            if (tmp) {
                vis.push(tmp);
                tmp = tmp->lChild;
            }
            else {
                if (vis.top()->isFirst) {
                    vis.top()->isFirst = false;
                    tmp = vis.top()->rChild;
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
        int m = getDeepth(p->lChild), n = getDeepth(p->rChild);
        if (m > n) return (m + 1);
        else return (n + 1);
    }
}

int getSize(biTree* T)
{
    if (T == NULL) return 0;
    else return (1 + getSize(T->lChild) + getSize(T->rChild));
}

int getLeafAmount(biTree* T)
{
    if (!T) return 0;
    else
        if (!T->lChild && !T->rChild) return 1;
        else  return getLeafAmount(T->lChild) + getLeafAmount(T->rChild);
}

//biTree* pre = new biTree{ ' ',NULL,NULL,false,false,true };
biThrTree* pre = new biThrTree;
void inorderThreading(biThrTree* p) {
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
    head->lTag = 0;head->rTag = 1;
    head->rChild = head;
    if (!p)
        head->lChild = head;
    else {
        head->lChild = p;
        pre = head;
        inorderThreading(p);
        pre->rChild = head;
        pre->rTag = 1;
        head->rChild = pre;
    }
}

void inorderTraversalThread(biThrTree* head) {
    biThrTree* p=head->lChild;
    while (p!=head) {
        while (!p->lTag) p = p->lChild;
        cout << p->data;
        while (p->rTag && p->rChild != head) {
            p = p->rChild;
            cout << p->data;
        }
        p = p->rChild;
    }
    cout << p->data;
}

int main()
{
    /*biTree* root;
    createBiTree(root,'@');*/
    pre->rChild = NULL;
    biThrTree* thrt, * head;
    createBiTree(thrt,'@');
    inorderThreadingWithHead(thrt,head);
    inorderTraversalThread(thrt);
    return 0;
}