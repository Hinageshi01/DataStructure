﻿#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define MAX_VEX 100
typedef int vexType;

typedef struct AdjListNode {
    vexType name;
    int weight;
    struct AdjListNode* next;
}AdjListNode;

typedef struct Graph {
    int vexNum, arcNum;
    AdjListNode adjList[MAX_VEX];
}Graph;

int getIndex(Graph G, vexType vex) {
    int index;
    for (index = 0; index < G.vexNum; index++) {
        if (G.adjList[index].name == vex)
            return index;
    }
}

void createAdjList(Graph& G, bool isDirected) {
    cin >> G.vexNum >> G.arcNum;
    for (int i = 0; i < G.vexNum; i++) {
        cin >> G.adjList[i].name;
        G.adjList[i].next = NULL;
    }
    for (int k = 0; k < G.arcNum; k++) {
        vexType vex1, vex2;
        cin >> vex1 >> vex2;
        int i = getIndex(G, vex1), j = getIndex(G, vex2);
        AdjListNode* tmpVex2 = new AdjListNode;
        tmpVex2->name = vex2;
        //tmpVex2->weight = 0;
        tmpVex2->next = G.adjList[i].next;
        G.adjList[i].next = tmpVex2;
        if (!isDirected) {
            AdjListNode* tmpVex1 = new AdjListNode;
            tmpVex1->name = vex1;
            //tmpVex1->weight = 0;
            tmpVex1->next = G.adjList[j].next;
            G.adjList[j].next = tmpVex1;
        }
    }
}

void GFSAdjList(Graph G, vexType firstVex) {
    queue<vexType> vis;
    bool visited[MAX_VEX] = { false };
    vis.push(firstVex);
    while (!vis.empty()) {
        int index = getIndex(G, vis.front());
        vis.pop();
        if (!visited[index]) {
            cout << "v" << G.adjList[index].name << " ";
            visited[index] = true;//Only mark when output
        }
        AdjListNode* p = G.adjList[index].next;
        while (p) {
            int index2 = getIndex(G, p->name);
            if (!visited[index2])
                vis.push(p->name);
            p = p->next;
        }
    }
}

/**No need to use this function in common situation, it's just prepare for the stupid RuiGeOJ*/
void reversePush(Graph G, AdjListNode* p, stack<vexType>& vis, bool visited[MAX_VEX]) {//Reverse push one line into stack
    if (p) {
        reversePush(G, p->next, vis, visited);
        int j = getIndex(G, p->name);
        if (!visited[j])
            vis.push(p->name);
    }
}

void DFSAdjList(Graph G, vexType firstVex) {
    stack<vexType> vis;
    bool visited[MAX_VEX] = { false };
    vis.push(firstVex);
    while (!vis.empty()) {
        int i = getIndex(G, vis.top());
        vis.pop();
        if (!visited[i]) {
            cout << "v" << G.adjList[i].name << " ";
            visited[i] = true;//Only mark when output
        }
        AdjListNode* p = G.adjList[i].next;
        reversePush(G, p, vis, visited);
    }
}

void putAdjList(Graph G) {
    for (int i = 1; i <= G.vexNum; i++) {
        cout << i << ":";
        AdjListNode* p = G.adjList[i].next;
        while (p) {
            cout << p->name << " ";
            p = p->next;
        }
        cout << endl;
    }
}

int getOutDegree(Graph G, vexType vex) {
    int index = getIndex(G, vex), sum = 0;
    AdjListNode* p = G.adjList[index].next;
    while (p) {
        sum++;
        p = p->next;
    }
    return sum;
}

int getInDegree(Graph G, vexType vex) {
    int barrel[MAX_VEX] = { 0 };
    for (int i = 0; i < G.vexNum; i++) {
        AdjListNode* p = G.adjList[i].next;
        while (p) {
            int index = getIndex(G, p->name);
            barrel[index]++;
            p = p->next;
        }
    }
    return barrel[getIndex(G, vex)];
}

bool toopSort(Graph G) {
    int inDegree[MAX_VEX] = { 0 }, cnt = 0;
    stack<vexType> vis;
    vexType tmpVex;
    for (int i = 0; i < G.vexNum; i++) {
        tmpVex = G.adjList[i].name;
        inDegree[i] = getInDegree(G, tmpVex);
        if (!inDegree[i])
            vis.push(G.adjList[i].name);
    }
    while (!vis.empty()) {
        tmpVex = vis.top();
        cout << "v" << tmpVex << " ";
        vis.pop();
        cnt++;
        int i = getIndex(G, tmpVex);
        AdjListNode* p = G.adjList[i].next;
        while (p) {
            tmpVex = p->name;
            int j = getIndex(G, tmpVex);
            inDegree[j]--;
            if (!inDegree[j])
                vis.push(tmpVex);
            p = p->next;
        }
    }
    if (cnt < G.vexNum)
        return false;
    return true;
}

int main()
{
    Graph G;
    createAdjList(G, false);
    DFSAdjList(G, 1);
    return 1;
}
