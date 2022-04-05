/********************************************************************
  2022 Copyright (c) saeedsolutions.blogspot.com
  All right reserved.

  Author: Saeed Yasin

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
********************************************************************/
#ifndef __LIST_H
#define __LIST_H

template <class T>
class Link;
template <class T>
class List_iterator;

template <class T>
class List
{
public:
  typedef List_iterator<T> iterator;

  List();
  ~List();

  // bool empty() const;
  // unsigned int size() const;
  // T &back() const;
  // T &front() const;
  void push_front(const T &x);
  void push_back(const T &x);
  void pop_front();
  void pop_back();
  void reverse();
  iterator begin() const;
  iterator end() const;
  // void insert(iterator pos, const T &x);
  // void erase(iterator &pos);
  // List<T> &operator=(const List<T> &l);

protected:
  Link<T> *first_link;
  Link<T> *last_link;
  unsigned int list_size;
};

template <class T>
class Link
{
private:
  Link(const T &x);

  T value;
  Link<T> *next_link;
  Link<T> *prev_link;

  friend class List<T>;
  friend class List_iterator<T>;
};

template <class T>
class List_iterator
{
public:
  typedef List_iterator<T> iterator;

  List_iterator();
  List_iterator(Link<T> *source_link);

  T &operator*();
  bool operator==(const iterator &rhs) const;
  bool operator!=(const iterator &rhs) const;
  iterator &operator++();
  // iterator operator++(int);
  iterator &operator--();
  // iterator operator--(int);

protected:
  Link<T> *current_link;

  friend class List<T>;
};

template <class T>
List<T>::List()
{
  first_link = 0;
  last_link = 0;
  list_size = 0;
}

template <class T>
List<T>::~List()
{
  Link<T> *l = first_link;
  while (l != 0)
  {
    Link<T> *next = l->next_link;
    delete l;
    l = next;
  }
}

template <class T>
void List<T>::push_front(const T &x)
{
  Link<T> *new_link = new Link<T>(x);
  if (first_link == 0)
  {
    first_link = new_link;
    last_link = new_link;
  }
  else
  {
    first_link->prev_link = new_link;
    new_link->next_link = first_link;
    first_link = new_link;
  }
  list_size++;
}

template <class T>
void List<T>::push_back(const T &x)
{
  Link<T> *new_link = new Link<T>(x);
  if (first_link == 0)
  {
    first_link = new_link;
    last_link = new_link;
  }
  else
  {
    new_link->prev_link = last_link;
    last_link->next_link = new_link;
    last_link = new_link;
  }
  list_size++;
}

template <class T>
void List<T>::pop_front(void)
{
  if (first_link != 0)
  {
    Link<T> *next_link = first_link->next_link;
    if (next_link != 0)
    {
      next_link->prev_link = 0;
      delete first_link;
      first_link = next_link;
    }
    else
    {
      delete first_link;
      first_link = 0;
      last_link = 0;
    }
    list_size--;
  }
}

template <class T>
void List<T>::pop_back(void)
{
  if (last_link != 0)
  {
    Link<T> *prev_link = last_link->prev_link;
    if (prev_link != 0)
    {
      prev_link->next_link = 0;
      delete last_link;
      last_link = prev_link;
    }
    else
    {
      delete last_link;
      last_link = 0;
      first_link = 0;
    }
    list_size--;
  }
}

template <class T>
void List<T>::reverse(void)
{
  Link<T> *first = last_link;
  Link<T> *second = first->prev_link;
  last_link->next_link = last_link->prev_link;
  last_link->prev_link = 0;
  while (second != 0)
  {
    second->next_link = second->prev_link;
    second->prev_link = first;
    first = second;
    second = first->next_link;
  }
  first_link = last_link;
  last_link = first;
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{
  return iterator(first_link);
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
  return iterator(last_link);
}

template <class T>
Link<T>::Link(const T &x)
    : value(x), next_link(0), prev_link(0)
{
}

template <class T>
List_iterator<T>::List_iterator()
    : current_link(0)
{
}

template <class T>
List_iterator<T>::List_iterator(Link<T> *source_link)
    : current_link(source_link)
{
}

template <class T>
T &List_iterator<T>::operator*()
{
  return current_link->value;
}

template <class T>
List_iterator<T> &List_iterator<T>::operator++()
{
  current_link = (current_link == 0) ? 0 : current_link->next_link;
  return *this;
}

template <class T>
bool List_iterator<T>::operator==(const iterator &rhs) const
{
  return (this->current_link == rhs.current_link);
}

template <class T>
bool List_iterator<T>::operator!=(const iterator &rhs) const
{
  return !(*this == rhs);
}

#endif
