#ifndef SELF_ORGANIZING_SORTED_LIST_IMPL_
#define SELF_ORGANIZING_SORTED_LIST_IMPL_

#include <iostream>
#include <utility>

// Default constructor
template <typename T>
SelfOrganizingSortedList<T>::SelfOrganizingSortedList()
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head(nullptr)
    , m_desc_head(nullptr)
    , m_size(0)
{
}

// Copy constructor
template <typename T>
SelfOrganizingSortedList<T>::SelfOrganizingSortedList(const SelfOrganizingSortedList<T>& other)
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head(nullptr)
    , m_desc_head(nullptr)
    , m_size(0)
{
    Node<T>* cur = other.m_head;
    while (cur) {
        push_back(cur->m_data);
        cur = cur->m_next;
    }
}

// Copy assignment operator
template <typename T>
SelfOrganizingSortedList<T>& SelfOrganizingSortedList<T>::operator=(const SelfOrganizingSortedList<T>& other)
{
    if (this != &other) {
        clear();

        Node<T>* cur = other.m_head;
        while (cur) {
            push_back(cur->m_data);
            cur = cur->m_next;
        }
    }
    return *this;
}

// Move constructor
template <typename T>
SelfOrganizingSortedList<T>::SelfOrganizingSortedList(SelfOrganizingSortedList<T>&& other)
    : m_head(other.m_head)
    , m_tail(other.m_tail)
    , m_asc_head(other.m_asc_head)
    , m_desc_head(other.m_desc_head)
    , m_size(other.m_size)
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
    other.m_size = 0;
}

// Move assignment operator
template <typename T>
SelfOrganizingSortedList<T>& SelfOrganizingSortedList<T>::operator=(SelfOrganizingSortedList<T>&& other)
{
    if (this != &other) {
        clear();

        m_head = other.m_head;
        m_tail = other.m_tail;
        m_asc_head = other.m_asc_head;
        m_desc_head = other.m_desc_head;
        m_size = other.m_size;
        
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_asc_head = nullptr;
        other.m_desc_head = nullptr;
        other.m_size = 0;
    }   
    return *this;
}

// Constructor with initializer list
template <typename T>
SelfOrganizingSortedList<T>::SelfOrganizingSortedList(std::initializer_list<T> init_list)
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head(nullptr)
    , m_desc_head(nullptr)
    , m_size(0)
{
    for (const T& elem : init_list) {
        push_back(elem);
    }
}

// Destructor
template <typename T>
SelfOrganizingSortedList<T>::~SelfOrganizingSortedList()
{
    clear();
}

// Removes all nodes from the list
template <typename T>
void SelfOrganizingSortedList<T>::clear()
{
    // Start by clearing the list while m_head is not nullptr
    while (m_head) {
        Node<T>* tmp = m_head;
        m_head = m_head->m_next;
        delete tmp;
    }

    // After the loop, the list is empty, so set all relevant pointers to nullptr
    m_head = nullptr;
    m_tail = nullptr;
    m_asc_head = nullptr;
    m_desc_head = nullptr;
    m_size = 0;
}

// Adds a new node with the given value to the end of the list
template <typename T>
void SelfOrganizingSortedList<T>::push_back(const T& value)
{
    // Create a new node containing the given 'value'
    Node<T>* new_node = new Node<T>(value);

    // Check if the list is empty
    if (!m_head) {
        // If it's empty, set both head and tail to the new node
        m_head = new_node;
        m_tail = new_node;
    } else {
        // If the list is not empty, connect the new node to the end of the list
        new_node->m_prev = m_tail;
        m_tail->m_next = new_node;
        m_tail = new_node;
    }
    put_in_sorted_order(new_node);
    ++m_size;
}

// Adds a new node with the given value to the front of a list. 
template <typename T>
void SelfOrganizingSortedList<T>::push_front(const T& value)
{
    // Create a new node containing the given 'value'
    Node<T>* new_node = new Node<T>(value);

    // Check if the list is empty
    if (!m_head) {
        // If it's empty, set both head and tail to the new node
        m_head = new_node;
        m_tail = new_node;
    } else {
        // If the list is not empty, insert the new node at the front
        new_node->m_next = m_head;
        m_head->m_prev = new_node;
        m_head = new_node;
    }
    put_in_sorted_order(new_node);
    ++m_size;
}

// Function is used to populate a sorted list with a specified number of elements that all have the same given value.
template <typename T>
void SelfOrganizingSortedList<T>::assign(const T& value, size_t count)
{
    // Check if the count is non-positive (including negative)
    if (count <= 0) {
        throw std::runtime_error("Count is negative. Cannot assign()");
    }

    // If the list is not empty, clear it to start with a fresh list
    if (m_head) {
        clear();
    }

    // Loop 'count' times to add 'count' elements with the given value to the list
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}

// Function takes an initializer list of elements and assigns these elements to the list.
template <typename T>
void SelfOrganizingSortedList<T>::assign(std::initializer_list<T> init_list)
{
    // Set the size 0
    m_size = 0;

    // Add each element to the end of the sorted list using push_back
    for (const T& elem : init_list) {
        push_back(elem);
    }
}

// The function adjusts the size of the sorted list to the specified count
template <typename T>
void SelfOrganizingSortedList<T>::resize(size_t count)
{
    // Check if the count is non-positive (including negative)
    if (count <= 0) {
        throw std::runtime_error("Count is negative. Cannot assign()");
    }

    // Increase the size of the list by adding default-initialized elements
    while (this->size() < count) {
        push_back(T{});
    }

    // Decrease the size of the list by removing elements from the end
    while (this->size() > count) {
        pop_back();
    }
}

// 
template <typename T>
void SelfOrganizingSortedList<T>::emplace_front(size_t count)
{
    // Check if the count is non-positive (including negative)
    if (count <= 0) {
        throw std::runtime_error("Count is negative. Cannot assign()");
    }

    // Increase the size of the list by adding default-initialized elements
    while (this->size() < count) {
        push_front(T{});
    }

    // Decrease the size of the list by removing elements from the front
    while (this->size() > count) {
        pop_front();
    }   
} 

/* Function is responsible for inserting a new node with the given value into 
   the sorted list while maintaining both ascending and descending order pointers */
template <typename T>
void SelfOrganizingSortedList<T>::put_in_sorted_order(Node<T>* new_node)
{
    // Check if the new_node is null (nothing to sort)
    if (!new_node) {
        return;
    }

    // If the ascending and descending heads are not set, this is the first node
    if (!m_asc_head) {
        m_asc_head = new_node;
        m_desc_head = new_node;
        return;
    }

    Node<T>* cur = m_asc_head;
    Node<T>* prev = nullptr;

    // Traverse the list in ascending order until we find the appropriate position
    while (cur && cur->m_data < new_node->m_data) {
        prev = cur;
        cur = cur->m_greater;
    }

    // Update the 'greater' pointer of the previous node
    if (prev) {
        prev->m_greater = new_node;
    } else {
        // If there was no previous node, this is the new head in ascending order
        m_asc_head = new_node;
    }

    // Update the 'lesser' pointer of the current node (if it exists)
    if (cur) {
        cur->m_lesser = new_node;
    } else {
        // If there was no current node, this is the new head in descending order
        m_desc_head = new_node;
    }

    // Update the 'lesser' and 'greater' pointers of the new_node
    new_node->m_lesser = prev;
    new_node->m_greater = cur;
}

// Function allows inserting a new element with the given value at a specified position.
template <typename T>
void SelfOrganizingSortedList<T>::insert(const T& value, const int pos)
{
    // Check if the position is out of range
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid position for insert");
    }

    // If inserting at the beginning (position 0), use push_front
    if (pos == 0) {
        push_front(value);
    } 
    // If inserting at the end (position equal to current size), use push_back
    else if (pos == m_size) {
        push_back(value);
    } 
    // Insert at a specific position within the list
    else {
        Node<T>* new_node = new Node<T>(value);
        Node<T>* cur = m_head;

        // Traverse the list to find the node at position (pos - 1)
        for (int i = 0; i < pos - 1; ++i) {
            cur = cur->m_next;
        }

        // Update pointers to insert the new node
        new_node->m_prev = cur;
        new_node->m_next = cur->m_next;
        cur->m_next->m_prev = new_node;
        cur->m_next = new_node;

        // Ensure the list remains sorted with the new node
        put_in_sorted_order(new_node);

        ++m_size;
    }
}

// Function allows inserting a new element with an rvalue reference (T&&) at a specified position.
template <typename T>
void SelfOrganizingSortedList<T>::insert(T&& value, const int pos)
{
    // Check if the position is out of range
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid position for insert");
    }

    // Create a new node with the moved value (using std::move)
    Node<T>* new_node = new Node<T>(std::move(value)); // Move the value into the node

    // If inserting at the beginning (position 0), use push_front
    if (pos == 0) { 
        push_front(new_node->m_data);
    } 
    // If inserting at the end (position equal to current size), use push_back
    else if (pos == m_size) {
        push_back(new_node->m_data);
    } 
    // Insert at a specific position within the list
    else { 
        Node<T>* cur = m_head;

        // Traverse the list to find the node at position (pos - 1)
        for (int i = 0; i < pos - 1; ++i) {
            cur = cur->m_next;
        }

        // Update pointers to insert the new node
        new_node->m_prev = cur;
        new_node->m_next = cur->m_next;
        cur->m_next->m_prev = new_node;
        cur->m_next = new_node;

        // Ensure the list remains sorted with the new node
        put_in_sorted_order(new_node);

        ++m_size;
    }
}

// Function allows inserting multiple elements with the same value at a specified position.
template <typename T>
void SelfOrganizingSortedList<T>::insert(const T& value, const int pos, const int count)
{
    // Check if the position is out of range or count is negative
    if (pos < 0 || pos > m_size || count < 0) {
        throw std::out_of_range("Invalid position for insert or non valid count");
    }

    // If inserting at the beginning (position 0), use push_front multiple times
    if (pos == 0) {
        for (int i = 0; i < count; ++i) {
            push_front(value);
        }
    } else if (pos == m_size) { // If inserting at the end (position equal to current size), use push_back multiple times
        for (int i = 0; i < count; ++i) {
            push_back(value);
        }
    } else { // Insert at a specific position within the list, multiple times
        for (int i = 0; i < count; ++i) {
            Node<T>* new_node = new Node<T>(value);
            Node<T>* cur = m_head;

            // Traverse the list to find the node at position (pos - 1)
            for (int i = 0; i < pos - 1; ++i) {
                cur = cur->m_next;
            }

            new_node->m_prev = cur;
            new_node->m_next = cur->m_next;
            cur->m_next->m_prev = new_node;
            cur->m_next = new_node;

            put_in_sorted_order(new_node);

            ++m_size;
        }
    }
}

// Function allows removing an element at a specified position.
template <typename T>
void SelfOrganizingSortedList<T>::erase(int pos)
{
    // Check if the position is out of range
    if (pos < 0 || pos >= m_size) {
        throw std::out_of_range("Invalid position for erase");
    }

    // If erasing at the beginning (position 0), use pop_front
    if (pos == 0) {
        pop_front();
    }
    // If erasing at the end (position equal to current size - 1), use pop_back 
    else if (pos == m_size - 1) {
        pop_back();
    }
    // Erase at a specific position within the list
    else {
        Node<T>* current = m_head;

        // Traverse the list to find the node at the specified position
        for (int i = 0; i < pos; ++i) {
            current = current->m_next;
        }

        // Update pointers to remove the current node
        current->m_prev->m_next = current->m_next;
        current->m_next->m_prev = current->m_prev;

        // Remove the current node from sorted order
        remove_sorted_node(current);

        delete current;
        --m_size;
    }
}

// Function allows removing multiple elements at a specified position.
template <typename T>
void SelfOrganizingSortedList<T>::erase(int pos, int count)
{
    // Check if the position and count are within valid bounds
    if (pos < 0 || pos >= m_size || count >= m_size || count < 0) {
        throw std::out_of_range("Invalid position for erase");
    }

    // If erasing at the beginning (position 0), use pop_front multiple times
    if (pos == 0) {
        for (int i = 0; i < count; ++i) {
            pop_front();
        }
    } else if (pos == m_size - 1) { // If erasing at the end (position equal to current size - 1), use pop_back multiple times
        for (int i = 0 ; i < count; ++i) {
            pop_back();
        }
    } else { // Erase at a specific position within the list, multiple times
        for (int i = 0; i < count; ++i) {
            Node<T>* current = m_head;

            // Traverse the list to find the node at the specified position
            for (int i = 0; i < pos; ++i) {
                current = current->m_next;
            }

            // Update pointers to remove the current node
            current->m_prev->m_next = current->m_next;
            current->m_next->m_prev = current->m_prev;

            // Remove the current node from sorted order
            remove_sorted_node(current);

            delete current;
            --m_size;
        }
    }
}

// Function removes the last element (tail) from the list.
template <typename T>
void SelfOrganizingSortedList<T>::pop_back() 
{
    // Check if the list is empty
    if (!m_tail) {
        throw std::runtime_error("List is empty. Cannot pop_back()");
    }

    // Create a temporary pointer 'tmp' to the current tail node
    Node<T>* tmp = m_tail;

    // If there's only one element in the list, set all pointers to nullptr
    if (m_head == m_tail) {
        m_head = nullptr;
        m_tail = nullptr;
        m_asc_head = nullptr;
        m_desc_head = nullptr;
    } else {
        // Update 'm_tail' to the previous node, and set its 'm_next' to nullptr
        m_tail = m_tail->m_prev;
        m_tail->m_next = nullptr;
    }

    // Remove the current tail node from sorted order
    remove_sorted_node(tmp);

    delete tmp;
    --m_size;
}

// Function removes the first element (head) from the list.
template <typename T>
void SelfOrganizingSortedList<T>::pop_front()
{
    if (!m_head) {
        throw std::runtime_error("List is empty. Cannot pop_front()");
    }

    // Create a temporary pointer 'tmp' to the current head node
    Node<T>* tmp = m_head;

    // If there's only one element in the list, set all pointers to nullptr
    if (m_head == m_tail) {
        m_head = nullptr;
        m_tail = nullptr;
        m_asc_head = nullptr;
        m_desc_head = nullptr;
    } else {
        // Update 'm_head' to the next node, and set its 'm_prev' to nullptr
        m_head = m_head->m_next;
        m_head->m_prev = nullptr;
    }

    // Remove the current head node from sorted order
    remove_sorted_node(tmp);

    delete tmp;
    --m_size;
}

// Function removes all occurrences of a specified element with the given data from the list.
template <typename T>
void SelfOrganizingSortedList<T>::remove(const T& data) 
{
    // Check if the list is empty
    if (!m_head) {
        throw std::runtime_error("List is empty. Cannot remove()");
    }

    Node<T>* cur = m_head;

    while (cur) {
         // Check if the data of the current node matches the target data
        if (cur->m_data == data) {
            if (cur->m_prev) {
                // Update the 'm_next' pointer of the previous node
                cur->m_prev->m_next = cur->m_next;
            } else {
                // If there's no previous node, update the 'm_head' pointer
                m_head = cur->m_next;
            }

             // Update the 'm_prev' pointer of the next node
            if (cur->m_next) {
                cur->m_next->m_prev = cur->m_prev;
            } else {
                // If there's no next node, update the 'm_tail' pointer
                m_tail = cur->m_prev;
            }

            // Remove the current node from the sorted order
            remove_sorted_node(cur);

            delete cur;
            --m_size;
        }
        // Move to the next node in the list
        cur = cur->m_next;
    }
}

// Function removes all nodes from the sorted list for which a specified condition function returns true
template <typename T>
void SelfOrganizingSortedList<T>::remove_if(std::function<bool(const T&)> condition)
{
    // Check if the list is empty
    if (!m_head) {
        throw std::runtime_error("List is empty. Cannot remove_if()");
    }

    Node<T>* cur = m_head;

    while (cur) {
        // Check if the condition function returns true for the current node's data
        if (condition(cur->m_data)) {
            Node<T>* node_to_remove = cur;

            // Update the 'm_next' pointer of the previous node
            if (cur->m_prev) {
                cur->m_prev->m_next = cur->m_next;
            } else {
                // If there's no previous node, update the 'm_head' pointer
                m_head = cur->m_next;
            }

            // Update the 'm_prev' pointer of the next node
            if (cur->m_next) {
                cur->m_next->m_prev = cur->m_prev;
            } else {
                // If there's no next node, update the 'm_tail' pointer
                m_tail = cur->m_prev;
            }

            // Remove the current node from the sorted order
            remove_sorted_node(node_to_remove);

            delete node_to_remove;
            --m_size;
        }
        // Move to the next node in the list
        cur = cur->m_next;
    }  
}

// Function allows elements from another SelfOrganizingSortedList (other) to be inserted into the current list at a specified position (pos).
template <typename T>
void SelfOrganizingSortedList<T>::splice(int pos, const SelfOrganizingSortedList<T>& other)
{
    // Check if the specified position is negative
    if (pos < 0) {
        throw std::runtime_error("pos is negative");
    }
    
    // Check if the current list is empty
    if (!m_head) {
        throw std::runtime_error("List is empty");
    }

    Node<T>* cur = other.m_head;
    // Iterate through the 'other' list and insert its elements into the current list at the specified position
    for (int i = 0; i < other.size(); ++i) {
        insert(cur->m_data, pos + i);
        cur = cur->m_next;
    }
}

// Function reverses the order of elements in the list.
template <typename T>
void SelfOrganizingSortedList<T>::reverse() 
{
    // Check if the list is empty or contains only one element
    if (!m_head || !m_tail) {
        return;
    }

    Node<T>* cur = m_head;
    Node<T>* temp;

    while (cur) {
        // Swap next and prev
        temp = cur->m_next;
        cur->m_next = cur->m_prev;
        cur->m_prev = temp;
        cur = temp;
    }

    // Swap m_head and m_tail pointers
    temp = m_head;
    m_head = m_tail;
    m_tail = temp;
}

// Function removes a given node from the sorted order of the list. 
template <typename T>
void SelfOrganizingSortedList<T>::remove_sorted_node(Node<T>* elem)
{
    // Check if the provided node 'elem' is valid
    if (!elem) {
        return;
    }

    // Update the 'm_greater' pointer of the previous node to skip 'elem'
    if (elem->m_lesser) {
        elem->m_lesser->m_greater = elem->m_greater;
    } else {
        // If 'elem' was the first node in ascending order, update 'm_asc_head'
        m_asc_head = elem->m_greater;
    }

     // Update the 'm_lesser' pointer of the next node to skip 'elem'
    if (elem->m_greater) {
        elem->m_greater->m_lesser = elem->m_lesser;
    } else {
        // If 'elem' was the last node in descending order, update 'm_desc_head'
        m_desc_head = elem->m_lesser;
    }
}

// Function prints the elements of the list in the order they appear in the list.
template <typename T>
void SelfOrganizingSortedList<T>::print_next()
{
    if (!m_head) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node<T>* cur = m_head;

    // Iterate through the list and print each element followed by a space
    while (cur) {
        std::cout << cur->m_data << " ";
        cur = cur->m_next;
    }
    std::cout << std::endl;
}

// Function prints the elements of the list in reverse order.
template <typename T>
void SelfOrganizingSortedList<T>::print_prev()
{
    if (!m_tail) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node<T>* cur = m_tail;

    // Iterate through the list in reverse order and print each element followed by a space
    while (cur) {
        std::cout << cur->m_data << " ";
        cur = cur->m_prev;
    }
    std::cout << std::endl;
}

// Function is designed to print the elements of the list in ascending order.
template <typename T>
void SelfOrganizingSortedList<T>::print_asc()
{
    if (!m_asc_head) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node<T>* cur = m_asc_head;

    // Iterate through the list in ascending order and print each element followed by a space
    while (cur) {
        std::cout << cur->m_data << " ";
        cur = cur->m_greater;
    }
    std::cout << std::endl; 
}

// Function is designed to print the elements of the list in descending order.
template <typename T>
void SelfOrganizingSortedList<T>::print_desc()
{
    if (!m_desc_head) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node<T>* cur = m_desc_head;

    // Iterate through the list in descending order and print each element followed by a space
    while (cur) {
        std::cout << cur->m_data << " ";
        cur = cur->m_lesser;
    }
    std::cout << std::endl; 
}

// Return the current size of the list.
template <typename T>
int SelfOrganizingSortedList<T>::size() const
{
    return m_size;
}

// Return a reference to the data of the first element (head) of the list.
template <typename T>
T& SelfOrganizingSortedList<T>::front()
{
    return m_head->m_data;
}

// Return a reference to the data of the first element (head) of the list (read-only).
template <typename T>
const T& SelfOrganizingSortedList<T>::front() const
{
    return m_head->m_data;
}

// Return a reference to the data of the last element (tail) of the list.
template <typename T>
T& SelfOrganizingSortedList<T>::back()
{
    return m_tail->m_data;
}

// Return a constant reference to the data of the last element (tail) of the list (read-only).
template <typename T>
const T& SelfOrganizingSortedList<T>::back() const
{
    return m_tail->m_data;
}

// Check if the list is empty by comparing the size to zero.
template <typename T>
bool SelfOrganizingSortedList<T>::empty() const
{
    return m_size == 0;
}

// Return a pointer to the head of the list.
template <typename T>
Node<T>* SelfOrganizingSortedList<T>::get_head() const
{
    return m_head;
}

// Swaps the contents.
template <typename T>
void SelfOrganizingSortedList<T>::swap(SelfOrganizingSortedList<T>& other)
{
    // Swap the size
    std::swap(m_size, other.m_size);

    // Swap the head pointers
    std::swap(m_head, other.m_head);

    // Swap the tail pointers
    std::swap(m_tail, other.m_tail);

    // Swap the ascending sorted head pointers
    std::swap(m_asc_head, other.m_asc_head);

    // Swap the descending sorted head pointers
    std::swap(m_desc_head, other.m_desc_head);
}

// Removes duplicate elements.
template <typename T>
void SelfOrganizingSortedList<T>::unique()
{
    if (!m_asc_head) {
        // The list is empty, nothing to remove.
        return;
    }

    Node<T>* cur = m_asc_head;

    while (cur && cur->m_greater) {
        if (cur->m_data == cur->m_greater->m_data) {
            // Duplicate element found, remove the next (greater) node.
            Node<T>* duplicate = cur->m_greater;
            
            duplicate->m_prev->m_next = duplicate->m_next;
            duplicate->m_next->m_prev = duplicate->m_prev;

            remove_sorted_node(duplicate);

            --m_size; // Decrement the size.
        } else {
            // Move to the next element.
            cur = cur->m_greater;
        }
    }
}

// Function allows to combine the contents of two lists.
template <typename T>
void SelfOrganizingSortedList<T>::merge(SelfOrganizingSortedList<T>& other)
{
    if (!other.m_head) {
        return; // Nothing to merge from the other list.
    }

    if (!m_head) {
        // If the current list is empty, simply copy the other list.
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_asc_head = other.m_asc_head;
        m_desc_head = other.m_desc_head;
        m_size = other.m_size;

        // Clear the other list.
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_asc_head = nullptr;
        other.m_desc_head = nullptr;
        other.m_size = 0;

        return;
    }

    // Merge the two lists into the current list.
    while (other.m_head) {
        Node<T>* cur = other.m_head;
        other.m_head = other.m_head->m_next;
        cur->m_next = nullptr;
        cur->m_prev = nullptr;
        cur->m_lesser = nullptr;
        cur->m_greater = nullptr;

        m_tail->m_next = cur;
        cur->m_prev = m_tail;
        m_tail = cur;
        put_in_sorted_order(m_tail); // Ensure sorted order is maintained.
    }

    // Clear the other list.
    other.m_tail = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
    other.m_size = 0;
}

// Sorts the elements in the SelfOrganizingSortedList in ascending order.
template <typename T>
void SelfOrganizingSortedList<T>::sort()
{
    // Reconfigure pointers for ascending order.
    m_head = m_asc_head;
    m_tail = m_desc_head;
    Node<T>* cur = m_head;
    while (cur) {
        cur->m_next = cur->m_greater;
        cur->m_prev = cur->m_lesser;
        cur = cur->m_next;
    }
}

// Checks that lhs == rhs
template <typename T>
bool operator==(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    Node<T>* cur1 = lhs.get_head();
    Node<T>* cur2 = rhs.get_head();

    // Compare the elements of both lists element by element
    while (cur1) {
        if (cur1->m_data != cur2->m_data) {
            return false;
        }
        cur1 = cur1->m_next;
        cur2 = cur2->m_next;
    }
    return true;
}

// Checks that lhs != rhs
template <typename T>
bool operator!=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    // Invert the result of the equality operator to check if the lists are not equal
    return !(lhs == rhs);
}

// Checks that lhs < rhs
template <typename T>
bool operator<(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    Node<T>* cur1 = lhs.get_head();
    Node<T>* cur2 = rhs.get_head();

    // Compare the elements of both lists element by element
    while (cur1) {
        if (cur1->m_data >= cur2->m_data) {
            return false;
        }
        cur1 = cur1->m_next;
        cur2 = cur2->m_next;
    }
    return true;
}

// Checks that lhs <= rhs
template <typename T>
bool operator<=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    Node<T>* cur1 = lhs.get_head();
    Node<T>* cur2 = rhs.get_head();

    // Compare the elements of both lists element by element
    while (cur1) {
        if (cur1->m_data > cur2->m_data) {
            return false;
        }
        cur1 = cur1->m_next;
        cur2 = cur2->m_next;
    }
    return true;
}

// Checks that lhs > rhs
template <typename T>
bool operator>(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    // Use the < operator to check if 'lhs' is greater than 'rhs', then invert the result
    return !(lhs < rhs);
}

// Checks that lhs >= rhs
template <typename T>
bool operator>=(const SelfOrganizingSortedList<T>& lhs, const SelfOrganizingSortedList<T>& rhs)
{
    // Use the <= operator to check if 'lhs' is greater than or equal to 'rhs', then invert the result
    return !(lhs <= rhs);
}

#endif // SELF_ORGANIZING_SORTED_LIST_IMPL_