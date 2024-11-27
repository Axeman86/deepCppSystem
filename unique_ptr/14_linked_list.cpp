/**
 * @file 14_linked_list.cpp
 * @brief 使用unique_ptr实现链表，避免内存泄漏，以及代码更加简洁，不需要手动delete，使用make_unique替代new关键字
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-27
 */

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Node
{
    int data;
    // Node* next;
    std::unique_ptr<Node> next;

    /* Node() { cout << "Node ctor: " << endl; } */
    ~Node() { cout << "Node dtor: " << data << endl; }
};

struct List
{
    std::unique_ptr<Node> head;

    /* void push(int data) { head = std::unique_ptr<Node>(new Node{ data, std::move(head) }); } */
    void push(int data)
    {
        auto temp  = std::make_unique<Node>();
        temp->data = data;
        temp->next = std::move(head);
        head       = std::move(temp);
    }

    List() { cout << "List ctor: " << endl; }
    //避免递归结构带来栈溢出
    ~List()
    {
        cout << "List dtor: " << endl;
        while (head)
        {
            head = std::move(head->next);
        }
    }
};

int main()
{
    List mylist;

    for (int i = 1; i < 10000; i++)
    {
        mylist.push(i);
    }

    cout << "end of main" << endl;
}
