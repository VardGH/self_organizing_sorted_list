#ifndef NODE_IMPL_HPP_
#define NODE_IMPL_HPP_

#include <utility>

template <typename T>
Node<T>::Node()
    : m_data(0)
    , m_prev(nullptr)
    , m_next(nullptr)
    , m_greater(nullptr)
    , m_lesser(nullptr)
{
}

template <typename T>
Node<T>::Node(const T& data)
    : m_data(data)
    , m_prev(nullptr)
    , m_next(nullptr)
    , m_greater(nullptr)
    , m_lesser(nullptr)
{
}


template <typename T>
Node<T>::Node(const Node<T>& other)
    : m_data(other.m_data)
    , m_prev(nullptr)
    , m_next(nullptr)
    , m_greater(nullptr)
    , m_lesser(nullptr)
{
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& other)
{
    if (this != &other) {
        m_data = other.m_data;
        m_prev = nullptr;
        m_next = nullptr;
        m_greater = nullptr;
        m_lesser = nullptr;
    }
    return *this;
}

template <typename T>
Node<T>::Node(Node<T>&& other) noexcept
    : m_data(std::move(other.m_data))
    , m_prev(other.m_prev)
    , m_next(other.m_next)
    , m_greater(other.m_greater)
    , m_lesser(other.m_lesser)
{
    other.m_data = 0;
    other.m_next = nullptr;
    other.m_prev = nullptr;
    other.m_greater = nullptr;
    other.m_lesser = nullptr;
}

template <typename T>
Node<T>&& Node<T>::operator=(Node<T>&& other) noexcept
{
    if (this != &other) {
        m_data = std::move(other.m_data);
        m_prev = other.m_prev;
        m_next = other.m_next;
        m_greater = other.m_greater;
        m_lesser = other.m_lesser;

        other.m_data = 0;
        other.m_next = nullptr;
        other.m_prev = nullptr;
        other.m_greater = nullptr;
        other.m_lesser = nullptr;
    }
    return *this;
}

#endif // NODE_IMPL_HPP