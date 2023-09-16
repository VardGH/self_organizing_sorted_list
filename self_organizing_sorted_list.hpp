#ifndef SELF_ORGANIZING_SORTED_LIST_HPP_
#define SELF_ORGANIZING_SORTED_LIST_HPP_

#include "node.hpp"
#include <functional>
#include <initializer_list>

template <typename T>
class SelfOrganizingSortedList
{
public:
    SelfOrganizingSortedList(); // Default constructor
    
    SelfOrganizingSortedList(const SelfOrganizingSortedList<T>& other); // Copy constructor
    SelfOrganizingSortedList<T>& operator=(const SelfOrganizingSortedList<T>& other); // Copy assignment operator
    
    SelfOrganizingSortedList(SelfOrganizingSortedList<T>&& other); // Move constructor
    SelfOrganizingSortedList<T>& operator=(SelfOrganizingSortedList<T>&& other); // Move assignment operator

    SelfOrganizingSortedList(std::initializer_list<T> init_list); // Constructor with initializer list
    
    ~SelfOrganizingSortedList();  // Destructor

public:
    // Member functions
    void assign(const T& value, size_t count); // Assigns values to the container
    void assign(std::initializer_list<T> init_list);

    // Modifiers
    void push_back(const T& value); // Adds an element to the end
    void push_front(const T& value); // Inserts an element to the beginning

    void insert(const T& value, const int pos); // Inserts elements
    void insert(T&& value, const int pos);
    void insert(const T& value, const int pos, const int count); // Adds elements by the given amount

    void erase(int pos); // Erases elements
    void erase(int pos, int count);

    void pop_back(); // Removes the last element
    void pop_front(); // Removes the first element

    void clear(); // Clears the contents

    void resize(size_t count); // Changes the number of elements stored
    void emplace_front(size_t count); // Changes the number of elements stored
    void swap(SelfOrganizingSortedList<T>& other); // Swaps the contents

    // Operations
    void remove(const T& val); // Removes elements satisfying specific criteria
    void remove_if(std::function<bool(const T&)> condition); 
    void splice(int pos, const SelfOrganizingSortedList<T>& other); // Moves elements from another list
    void reverse(); // Reverses the order of the elements
    void unique(); // Removes duplicate elements
    void sort(); // Sorts the elements
    void merge(SelfOrganizingSortedList<T>& other); // merges two lists

    // Element access
    T& front(); // Access the first element
    const T& front() const;
    T& back(); // Access the last element
    const T& back() const;

    // Capacity
    bool empty() const; // Checks whether the container is empty
    int size() const; // Returns the number of elements

    // Prints
    void print_next();
    void print_prev();
    void print_asc();
    void print_desc();

    // getters prt
    Node<T>* get_head() const;
    
private:
    void put_in_sorted_order(Node<T>* elem); // Function to insert a node into sorted order in the list
    void remove_sorted_node(Node<T>* elem); // Function to remove a node from sorted order in the list
    void advance_node(Node<T>* elem); 

private:
    Node<T>* m_head;
    Node<T>* m_tail;
    Node<T>* m_asc_head;
    Node<T>* m_desc_head;
    int m_size;
};

// Non-member functions
// Lexicographically compares the values in the list
template <typename T>
bool operator==(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

template <typename T>
bool operator!=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

template <typename T>
bool operator<(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

template <typename T>
bool operator<=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

template <typename T>
bool operator>(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

template <typename T>
bool operator>=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs);

#include "self_organizing_sorted_list_impl_.hpp"

#endif // SELF_ORGANIZING_SORTED_LIST_HPP_