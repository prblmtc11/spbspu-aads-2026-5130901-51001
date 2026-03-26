#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace yarmolinskaya
{
  template< class T >
  class List
  {
  private:
    struct Node
    {
      T data;
      Node* next;

      Node(const T& value):
        data(value),
        next(nullptr)
      {}
    };

  public:
    class Iterator
    {
    public:
      Iterator(Node* ptr = nullptr):
        ptr_(ptr)
      {}

      T& operator*()
      {
        return ptr_->data;
      }

      Iterator& operator++()
      {
        ptr_ = ptr_->next;
        return *this;
      }

      bool operator!=(const Iterator& other) const
      {
        return ptr_ != other.ptr_;
      }

    private:
      Node* ptr_;
    };

    List():
      head_(nullptr),
      tail_(nullptr)
    {}

    ~List()
    {
      clear();
    }

    bool empty() const noexcept
    {
      return head_ == nullptr;
    }

    T& front()
    {
      return head_->data;
    }

    T& back()
    {
      return tail_->data;
    }

    void push_front(const T& value)
    {
      Node* node = new Node(value);
      node->next = head_;
      head_ = node;

      if (!tail_)
      {
        tail_ = node;
      }
    }

    void push_back(const T& value)
    {
      Node* node = new Node(value);

      if (!head_)
      {
        head_ = tail_ = node;
      }
      else
      {
        tail_->next = node;
        tail_ = node;
      }
    }

    void pop_front()
    {
      if (!head_) return;

      Node* tmp = head_;
      head_ = head_->next;

      if (!head_)
      {
        tail_ = nullptr;
      }

      delete tmp;
    }

    void clear()
    {
      while (!empty())
      {
        pop_front();
      }
    }

    Iterator begin()
    {
      return Iterator(head_);
    }

    Iterator end()
    {
      return Iterator(nullptr);
    }

  private:
    Node* head_;
    Node* tail_;
  };
}

#endif
