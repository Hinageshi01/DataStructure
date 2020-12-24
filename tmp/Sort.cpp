#include <iostream>
#include<bits/stdc++.h>

using namespace std;

void insertSort(int* list, int lenth) {
    int i, j;
    for (i = 2; list[i] != 0; i++) {
        if (list[i] < list[i - 1]) {
            list[0] = list[i];
            for (j = i; list[j - 1] > list[0]; j--) {
                list[j] = list[j - 1];
            }
            list[j] = list[0];
        }
    }
}

void bubbleSort(int* list, int lenth) {
    bool flag = true;
    while (lenth-- && flag) {
        flag = false;
        for (int i = 1; i <= lenth; i++) {
            if (list[i] > list[i + 1]) {
                swap(list[i], list[i + 1]);
                flag = true;
            }
        }
    }
}

void simpleSelectionSort(int* list, int lenth) {
    int i, j;
    for (i = 1; i < lenth; i++) {
        int min = 999999, minIndex;
        for (j = i; j <= lenth; j++) {
            if (list[j] < min) {
                min = list[j];
                minIndex = j;
            }
        }
        swap(list[i], list[minIndex]);
    }
}

int main()
{
    int i, num, list[999] = { 0 };
    cin >> num;
    for (i = 1; num != 0; i++) {
        list[i] = num;
        cin >> num;
    }
    int lenth = i - 1;
    simpleSelectionSort(list, lenth);
    for (int j = 1; j <= lenth; j++) {
        cout << list[j] << " ";
    }
    return 0;
}
