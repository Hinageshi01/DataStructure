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

void doubleTraversal(biTree* p) {
    if (p) {
        cout << p->data;
        doubleTraversal(p->lChild);
        cout << p->data;
        doubleTraversal(p->rChild);
    }
}

void levelorderTraversal(biTree* p) {
    if (p) {
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
    if (!p) return 0;
    else return (1 + getSize(p->lChild) + getSize(p->rChild));
}

int getLeafAmount(biTree* p) {
    if (!p) return 0;
    else
        if (!p->lChild && !p->rChild) return 1;
        else  return getLeafAmount(p->lChild) + getLeafAmount(p->rChild);
}

int getLevelWidth(biTree* p, int level) {
    if (!p) return 0;
    else {
        if (level == 1) return 1;
        return getLevelWidth(p->lChild, level - 1) + getLevelWidth(p->rChild, level - 1);
    }
}

int getWidth(biTree* p) {
    if (!p) return 0;
    if (p) {
        int deep = getDeepth(p), maxWidth = 0;
        int* widths = new int[deep + 5];
        memset(widths, 0, sizeof(widths));
        for (int i = 1; i <= deep; i++) {
            widths[i] = getLevelWidth(p, i);
            if (widths[i] >= maxWidth) maxWidth = widths[i];
        }
        return maxWidth;
    }
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
            return 1;//return 0; Only put the parent node of the target value.
        }
    }
    return 0;
}

int main()
{
    biTree* root;
    createBiTree(root, '@');
    putFathers(root, 'F');
    /*biThrTree* thrt, * head;
    createBiTree(thrt,'@');
    inorderThreadingWithHead(thrt,head);
    inorderTraversalThread(head);*/
    return 0;
}
