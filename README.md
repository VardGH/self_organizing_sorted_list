# Self-Organizing Sorted List

`SelfOrganizingSortedList` is a C++ template class that provides a self-organizing sorted list data structure. This data structure maintains a sorted order of elements.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Constructor](#constructor)
- [Member Functions](#member-functions)
- [Non-Member Functions](#non-member-functions)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Installation

To use the `SelfOrganizingSortedList` class, include the `self_organizing_sorted_list.hpp` header in your C++ project.

```cpp
#include "self_organizing_sorted_list.hpp"
```

## Usage

### Constructor

#### `SelfOrganizingSortedList()`
- Default constructor to create an empty self-organizing sorted list.

#### `SelfOrganizingSortedList(const SelfOrganizingSortedList<T>& other)`
- Copy constructor to create a new list as a copy of an existing list.

#### `SelfOrganizingSortedList<T>& operator=(const SelfOrganizingSortedList<T>& other)`
- Copy assignment operator to assign the contents of an existing list to another list.

#### `SelfOrganizingSortedList(SelfOrganizingSortedList<T>&& other)`
- Move constructor to create a new list by moving the contents of an existing list.

#### `SelfOrganizingSortedList<T>& operator=(SelfOrganizingSortedList<T>&& other)`
- Move assignment operator to move the contents of an existing list to another list.

#### `SelfOrganizingSortedList(std::initializer_list<T> init_list)`
- Constructor with an initializer list to create a list with initial elements.

#### `~SelfOrganizingSortedList()`
- Destructor to clean up the memory used by the list.

### Member Functions

#### Modifiers

- `void push_back(const T& value)`
  - Adds an element to the end of the list.

- `void push_front(const T& value)`
  - Inserts an element at the beginning of the list.

- `void insert(const T& value, const int pos)`
  - Inserts an element at the specified position in the list.

- `void insert(T&& value, const int pos)`
  - Inserts an element at the specified position in the list using move semantics.

- `void insert(const T& value, const int pos, const int count)`
  - Inserts multiple elements of the same value at the specified position.

- `void erase(int pos)`
  - Removes an element at the specified position from the list.

- `void erase(int pos, int count)`
  - Removes multiple elements starting from the specified position.

- `void pop_back()`
  - Removes the last element from the list.

- `void pop_front()`
  - Removes the first element from the list.

- `void clear()`
  - Clears the contents of the list.

- `void resize(size_t count)`
  - Changes the number of elements stored in the list.

- `void emplace_front(size_t count)`
  - Changes the number of elements stored in the list.

- `void swap(SelfOrganizingSortedList<T>& other)`
  - Swaps the contents of two lists.

#### Operations

- `void remove(const T& val)`
  - Removes elements with a specific value from the list.

- `void remove_if(std::function<bool(const T&)> condition)`
  - Removes elements based on a user-defined condition.

- `void splice(int pos, const SelfOrganizingSortedList<T>& other)`
  - Moves elements from another list to the specified position in this list.

- `void reverse()`
  - Reverses the order of elements in the list.

- `void unique()`
  - Removes duplicate elements from the list.

- `void sort()`
  - Sorts the elements in ascending order.

- `void merge(SelfOrganizingSortedList<T>& other)`
  - Merges two lists into one sorted list.

#### Element Access

- `T& front()`
  - Accesses the first element in the list.

- `const T& front() const`
  - Accesses the first element in the list (const version).

- `T& back()`
  - Accesses the last element in the list.

- `const T& back() const`
  - Accesses the last element in the list (const version).

#### Capacity

- `bool empty() const`
  - Checks whether the list is empty.

- `int size() const`
  - Returns the number of elements in the list.

#### Printing

- `void print_next()`
  - Prints the elements of the list in their current order.

- `void print_prev()`
  - Prints the elements of the list in reverse order.

- `void print_asc()`
  - Prints the elements of the list in ascending order.

- `void print_desc()`
  - Prints the elements of the list in descending order.

#### Getter

- `Node<T>* get_head() const`
  - Returns a pointer to the head node of the list.

### Non-Member Functions

- `bool operator==(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists for equality.

- `bool operator!=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists for inequality.

- `bool operator<(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists lexicographically.

- `bool operator<=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists lexicographically.

- `bool operator>(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists lexicographically.

- `bool operator>=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)`
  - Compares two lists lexicographically.

## Examples

Here's how you can create and use a `SelfOrganizingSortedList`:

```cpp
#include "self_organizing_sorted_list.hpp"

int main() {
    SelfOrganizingSortedList<int> list {3, 1, 2};
    list.push_back(4);
    list.sort();
    list.print_asc(); // Output: 1 2 3 4

    return 0;
}
```

## Contributing

Contributions are welcome! If you have any improvements or bug fixes, feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT License.
```
