#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head);

int main() {

  return 0;
}

// Always use a prev pointer, make cur.next = prev
// Then move cur to next and repeat

// ***Note
// After the loop exit, the cur pointer always out of range
// Use the prev pointer as the last node of the reversed list
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* p = head;
    while (p != NULL) {
        ListNode* next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }
    return prev;
}