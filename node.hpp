#ifndef NODE_HPP_
#define NODE_HPP_

template <typename T>
class Node
{
public:
    Node(); // Default constructor
    explicit Node(const T& data); // Constructor with parameter

    
    Node(const Node<T>& other); // Copy constructor
    Node<T>& operator=(const Node<T>& other); // Copy assignment operator

    Node(Node<T>&& other) noexcept; // Move constructor
    Node<T>&& operator=(Node<T>&& other) noexcept; // Move assignment operator
    
    ~Node() = default; // Destructor

public:
    T m_data;
    Node<T>* m_prev;
    Node<T>* m_next;
    Node<T>* m_greater;
    Node<T>* m_lesser;
};

#include "node_impl_.hpp"

#endif // NODE_HPP_