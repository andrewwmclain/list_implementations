/*
    Title:      list implementations – vsarray.cpp
    Purpose:    implement the vsarray class methods
    Author:     Andrew McLain
    Date:       May 10, 2020
*/

#include "object.h"
#include "list.h"
#include "vsarray.h"
#include "person.h"
#include "integer.h"

#include <string>
#include <sstream>
using std::string;

/*
* VSArray constructor
* initializes VSArray with a given capacity and delta
* @param size_t capacity - capacity of underlying array
* @param double increasePercentage - value by which underlying array size increases during resize
* @returns nothing
*/
VSArray::VSArray(size_t capacity, double increasePercentage) : _capacity(capacity), _delta(increasePercentage){
    //initialize data array
    _data = new Object*[_capacity];
    _size = 0;

    //set each element in data array to nullptr default
    for(size_t i = 0; i < _capacity; i++){
        _data[i] = nullptr;
    }
}

/*
* VSArray copy constructor
* initializes VSArray list with values of other list
* @param const VSArray &list - VSArray list to copy from
* @returns nothing
*/
VSArray::VSArray(const VSArray& list){
    //copy data members from other list into this VSArray, make sure capacity is the same
    _capacity = list._capacity;
    _delta = list._delta;
    _size = list._size;
    _data = new Object*[_capacity];

    //set elements in this VSArray equal to elements in other list
    for(size_t i = 0; i < _size; i++){
        _data[i] = list.Get(i)->Clone();
    }
    //set any remaining empty elements to nullptr
    for(size_t i = _size; i < _capacity; i++){
        _data[i] = nullptr;
    }
}

/*
* VSArray destructor
* clears out the VSArray when object goes out of scope
* @param none
* @returns nothing
*/
VSArray::~VSArray(){
    //delete each element in this array from the heap
    for(size_t i = 0; i < _size; i++){
            delete _data[i];
    }
    //delete data array from heap
    delete[] _data;
}

/*
* VSArray assignment operator
* assigns VSArray with values of rhs list
* @param const VSArray &rhs - VSArray to copy from
* @returns *this - this VSArray object
*/
const VSArray& VSArray::operator=(const VSArray& rhs){
    //if rhs is the same as this, do nothing
    if(&rhs == this){
        return *this;
    }

    //if the capacities are different, make them equal
    if (_capacity != rhs._capacity){
        Clear();
        delete[] _data;
        _capacity = rhs._capacity;
        _data = new Object*[_capacity];
        //set elements to nullptr default
        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = nullptr;
        }
    }

    //make this data elements equal to rhs data elements
    for(size_t i = 0; i < _size; i++){
        _data[i] = rhs._data[i]->Clone();
    }

	return *this;
}

/*
* Insert
* insert given element at given position
* @param Object* element - pointer to element to be added
* @param size_t position - position to add element at
* @returns true if element can be added, false if cannot
* position must be a valid index in the VSArray
*/
bool VSArray::Insert(Object* element, size_t position){
    //can't insert at position > size
    if(position > _size){
        return false;
    }
    //if array is full, resize
    if(_size == _capacity)
        Resize();

    delete _data[_size];

    //shift elements over for insertion
    for(size_t i = _size; i > position; i--){
        _data[i] = _data[i - 1];
    }

    //insert element at position and increase size
    _data[position] = element;
    _size++;
	return true;
}

/*
* IndexOf
* find position of given element in VSArray
* @param const Object* element - pointer to element to be searched
* @returns -1 if element not found, index of element otherwise
*/
int VSArray::IndexOf(const Object* element)const{
    //traverse array until element is found and return index
    for(size_t i = 0; i < _size; i++) {
        if (_data[i]->Equals(*element)){
            return i;
        }
    }
    //return -1 if traversal complete without finding element
	return -1;
}

/*
* Remove
* remove element at given position
* @param size_t position - position of element to be removed
* @returns pointer to object being removed, nullptr if position invalid or element not found
* position must be a valid index in the VSArray
*/
Object* VSArray::Remove(size_t position){
    //can't remove from position outside of range
    if(position >= _size)
        return nullptr;

    //get a pointer to object at position so it's not lost
    Object* retVal = _data[position];

    //shift object pointers to the left for removal
    for(size_t i = position; i < _size - 1; i++){
        _data[i] = _data[i + 1];
    }

    //last element is a repeat so make it nullptr
    _data[_size - 1] = nullptr;
    _size--;
	return retVal;
}

/*
* Get
* return element at given position
* @param size_t position - position to retrieve element from
* @returns pointer to element at that position, nullptr if position invalid or element not found
* position must be a valid index in the VSArray
*/
Object* VSArray::Get(size_t position)const{
    //invalid position
    if(position >= _size)
        return nullptr;
    else
        return _data[position];
}

/*
* ToString
* return string representation of VSArray
* @param none
* @returns string of elements in VSArray
*/
string VSArray::ToString()const{
    std::stringstream ss;
    ss << "{";
    //traverse list for each element string
    for(size_t i = 0; i < _size - 1; i++){
        ss << _data[i]->ToString();
	}
    ss << _data[_size - 1]->ToString() << "}";
    return ss.str();
}

/*
* Clear
* clears elements in VSArray
* @param none
* @returns nothing
*/
void VSArray::Clear(){
    //traverse list deleting elements from heap
    for(size_t i = 0; i < _size; i++){
        delete _data[i];
        _data[i] = nullptr;
    }
    _size = 0;
}

/*
* Resize
* resizes the underlying array in VSArray
* @param none
* @returns nothing
*/
void VSArray::Resize() {
    //change capacity
    _capacity = _capacity + (_delta * _capacity);

    //temporary arr to copy to/from
    Object** arr = new Object*[_capacity];

    //copy data array to temp array
    for(size_t i = 0; i < _size; i++)
        arr[i] = _data[i];

    //delete tmp array, but don't remove elements from heap
    for(size_t i = 0; i < _size; i++)
        _data[i] = nullptr;
    delete[] _data;

    //initialize new data array
    _data = new Object*[_capacity];

    //make new data array pointers point to tmp array's elements
    for(size_t i = 0; i < _size; i++)
        _data[i] = arr[i];
    for(size_t i = _size; i < _capacity; i++)
        _data[i] = nullptr;

    //delete temp array but don't remove elements from heap
    delete[] arr;
}

/*
* GetCapacity
* returns capacity of underlying array in VSArray
* @param none
* @returns capacity of array
*/
size_t VSArray::GetCapacity() const {
	return _capacity;
}
