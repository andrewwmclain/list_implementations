/*
    Title:      list implementations – dlinkedlist.cpp
    Purpose:    implement the dlinkedlist class methods
    Author:     Andrew McLain
    Date:       May 10, 2020
*/

#include "object.h"
#include "dlinkedlist.h"

#include <string>
#include <sstream>
using std::string;

/*
* DoubleLinkedList copy constructor
* initializes double linked list with values of other list
* @param const DoubleLinkedList &other - double linked list to copy from
* @returns nothing
*/
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList &other){
    //set each element equal to other list by traversing
    for (Node* tmp = other._head; tmp != nullptr; tmp = tmp->next){
        Insert(tmp->data->Clone(), _size);
    }
}

/*
* DoubleLinkedList assignment operator
* assigns double linked list with values of rhs list
* @param const DoubleLinkedList &rhs - double linked list to copy from
* @returns *this - this double linked list object
*/
DoubleLinkedList &DoubleLinkedList::operator=(const DoubleLinkedList &rhs) {
    //set each element equal to rhs list by traversing
    for (Node* tmp = rhs._head; tmp != nullptr; tmp = tmp->next){
        Insert(tmp->data->Clone(), _size);
    }
	return *this;
}

/*
* DoubleLinkedList constructor
* initializes empty double linked list
* @param none
* @returns nothing
*/
DoubleLinkedList::DoubleLinkedList() : _head(nullptr), _tail(nullptr){
}

/*
* DoubleLinkedList destructor
* clears out the double linked list when object goes out of scope
* @param none
* @returns nothing
*/
DoubleLinkedList::~DoubleLinkedList() {
    Node* tempNode = _head;
    //delete data from each node and then delete each node
    while (_head != nullptr){
        _head = tempNode->next;
        if (tempNode->data)
            delete tempNode->data;
        delete tempNode;
        tempNode = _head;
    }
}

/*
* Insert
* insert given element at given position
* @param Object* element - pointer to element to be added
* @param size_t position - position to add element at
* @returns true if element can be added, false if cannot
* position must be a valid index in the linked list
*/
bool DoubleLinkedList::Insert(Object *element, size_t position) {
    //can't insert at invalid position
    if (position > _size){
        return false;
    }
    //make new node
    Node* neo = new Node;
    neo->data = element;
    neo->next = nullptr;
    neo->previous = nullptr;
    //if list is empty
    if (_size == 0){
        _head = neo;
        _tail = neo;
    }else if (position == 0){ //inserting at head of non-empty list
        neo->next = _head;
        _head = neo;
        _tail = neo;
    }else{ //insert in middle or end of list
        Node* tmp = _head;
        for (size_t i = 0; i < position -1; i++){
            tmp = tmp->next;
        }
        neo->next = tmp->next;
        tmp->next = neo;
        if(tmp == _tail){ //insert at end of list
            _tail = neo;
        }
    }
    _size++;
    return true;
}

/*
* IndexOf
* find position of given element in linked list
* @param const Object* element - pointer to element to be searched
* @returns -1 if element not found, index of element otherwise
*/
int DoubleLinkedList::IndexOf(const Object *element) const {
    size_t index = 0;
    //traverse list until element found
    for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next){
        if (tmp->data->Equals(*element)){
            return index;
        }
        index++;
    }
    //element not found
    return -1;
}

/*
* Remove
* remove element at given position
* @param size_t position - position of element to be removed
* @returns pointer to object being removed, nullptr if position invalid or element not found
* position must be a valid index in the linked list
*/
Object *DoubleLinkedList::Remove(size_t position) {
    //invalid position
    if (position >= _size){
        return nullptr;
    }
    Object* retVal = nullptr;
    Node* tmp = nullptr;
    if (position == 0){ //element at head
        retVal = _head->data;
        _head->data = nullptr;
        tmp = _head->next;
        _head->next = nullptr;
        if(_tail == _head){
            _tail = tmp;
        }
        delete _head;
        _head = tmp;
    }else { //element not at head
        tmp = _head;
        for (size_t i = 0; i < position -1; i++){
            tmp = tmp->next;
        }
        Node* toRemove = tmp->next;
        retVal = toRemove->data;
        tmp->next = toRemove->next;
        if(toRemove->next != nullptr){ //if element removed is not at end of list
            toRemove->next->previous = tmp;
            toRemove->next = nullptr;
        }
        else{ //element removed is at end of list
            _tail = tmp;
        }
        toRemove->previous = nullptr;
        toRemove->data = nullptr;
        delete toRemove;
    }
    _size--;
    return retVal;
}

/*
* Get
* return element at given position
* @param size_t position - position to retrieve element from
* @returns pointer to element at that position, nullptr if position invalid or element not found
* position must be a valid index in the linked list
*/
Object *DoubleLinkedList::Get(size_t position) const {
    //invalid position
    if (position >= _size){
        return nullptr;
    }
    Node* tmp = _head;
    //traverse list until position reached
    for (size_t i = 0; i < position; i++) {
        tmp = tmp->next;
    }
    return tmp->data;
}

/*
* ToString
* return string representation of list
* @param none
* @returns string of elements in linked list
*/
string DoubleLinkedList::ToString() const {
    std::stringstream retVal;
    retVal << "{";
    Node* tmp;
    //print each node traversing
    for (tmp = _head; tmp->next != nullptr; tmp = tmp->next) {
        retVal << tmp->data->ToString() << ", ";
    }
    retVal << tmp->data->ToString() << "}";
    return retVal.str();
}

/*
* Clear
* clears elements in linked list
* @param none
* @returns nothing
*/
void DoubleLinkedList::Clear() {
    Node* tempNode = _head;
    //delete each node until nullptr node reached
    while (_head != nullptr){
        _head = tempNode->next;
        if (tempNode->data)
            delete tempNode->data;
        delete tempNode;
        tempNode = _head;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}
