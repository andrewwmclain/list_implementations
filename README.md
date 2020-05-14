# Implementing the Abstract Data Type List

This assignment will help you practice:
- Implementing ADT List using Variable Size Arrays
- Implementing ADT List using Double Linked Lists

## Given
You are given the following files

File | Comments
-----|---------
`dlinkedlist.cpp` | Implementation of the Double Linked List
`dlinkedlist.h` | Declaration of the `DoubleLinkedList` class, you should not modify this file
`integer.cpp` / `integer.h` | `Integer` class declaration and definition, you should not modify this file
`list.cpp` / `list.h` | ADT `List` class declaration and implementation, you should not modify this file
`makefile` | Use this to build your project
`object.cpp` / `object.h` | `Object` class declaration and definition, you should not modify this file
`person.cpp` / `person.h` | `Person` class declaration and definition, you should not modify this file
`test.cpp` | Unit tests, contains the main function, you should not modify this file
`vsarray.cpp` | Implementation of the Variable Size Array List
`vsarray.h` | Declaration of `VSArray` class, you should not modify this file

## Testing your program

1. Move to the directory where your source code is
    `cd development/adt-list-your-git-user/`
1. Build your program using `make`
    `make`
1. Run the unit test
    `cmake-build-test/list`

The expected output should be:
```
====================================


There are 2 sets of unit tests:
   1. Double Linked List        - 55
   2. Variable Size Array List  - 55
====================================
====================================


Double Linked List Tests
TESTING: Double Linked List

      1.82
      3.64
      5.45
      7.27
      9.09
     10.91
     12.73
     14.55
     16.36
     18.18
     20.00
     21.82
     23.64
     25.45
     27.27
     29.09
     30.91
     32.73
     34.55
     36.36
     38.18
     40.00
     41.82
     43.64
     45.45
     47.27
     49.09
     50.91
     52.73
     54.55
     56.36
     58.18
     60.00
     61.82
     63.64
     65.45
     67.27
     69.09
     70.91
     72.73
     74.55
     76.36
     78.18
     80.00
     81.82
     83.64
     85.45
     87.27
     89.09
     90.91
     92.73
     94.55
     96.36
     98.18
    100.00
= = = = = = = = = = = = = = = = = = = = =

F i n i s h e d   S u c c e s s f u l l y
Variable Size Array List Tests
TESTING: Variable Size Array List

      1.82
      3.64
      5.45
      7.27
      9.09
     10.91
     12.73
     14.55
     16.36
     18.18
     20.00
     21.82
     23.64
     25.45
     27.27
     29.09
     30.91
     32.73
     34.55
     36.36
     38.18
     40.00
     41.82
     43.64
     45.45
     47.27
     49.09
     50.91
     52.73
     54.55
     56.36
     58.18
     60.00
     61.82
     63.64
     65.45
     67.27
     69.09
     70.91
     72.73
     74.55
     76.36
     78.18
     80.00
     81.82
     83.64
     85.45
     87.27
     89.09
     90.91
     92.73
     94.55
     96.36
     98.18
    100.00
= = = = = = = = = = = = = = = = = = = = =

F i n i s h e d   S u c c e s s f u l l y
- - - - - - - - - - - - - - - - - - -

    C O N G R A T U L A T I O N S
          All test passed!
```

## Reminders

Your code:
1. Should compile without warnings
1. Should not have memory leaks
1. Should not crash
1. Should apply all good programming practices, including taking advantage of the
 initialization technique in constructors

