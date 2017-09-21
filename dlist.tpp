/*
The distributed list (dlist) library provides very light-weight real-time
capable list classes with can optionally be ordered or circular.
Copyright (C) 2017..2017  Thomas Schöpping

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DLIST_TPP_
#define _DLIST_TPP_

#include <dlist.hpp>

#include <cassert>

namespace dlist
{

////////////////////////////////////////////////////////////////////////////////
// ITEMS                                                                      //
////////////////////////////////////////////////////////////////////////////////

// BASE_SLITEM /////////////////////////////////////////////////////////////////

_slitem::_slitem() :
  m_next(nullptr)
{}

inline bool _slitem::attached() const
{
  return (this->m_next != nullptr);
}

inline bool _slitem::operator==(const _slitem& i) const
{
  return identical(*this, i);
}

inline bool _slitem::operator!=(const _slitem& i) const
{
  return !identical(*this, i);
}

inline bool _slitem::identical(const _slitem &a, const _slitem &b)
{
  return (a.m_next == b.m_next);
}

// BASE_DLITEM /////////////////////////////////////////////////////////////////

_dlitem::_dlitem() :
  m_prev(nullptr), m_next(nullptr)
{}

inline bool _dlitem::attached() const
{
  return (this->m_prev != nullptr) || (this->m_next != nullptr);
}

inline bool _dlitem::operator==(const _dlitem& i) const
{
  return identical(*this, i);
}

inline bool _dlitem::operator!=(const _dlitem& i) const
{
  return !identical(*this, i);
}

inline bool _dlitem::identical(const _dlitem &a, const _dlitem &b)
{
  return (a.m_prev == b.m_prev) && (a.m_next == b.m_next);
}

// _BASE_ITEM //////////////////////////////////////////////////////////////////

template<typename T>
_item<T>::_item(T& d) :
  m_data(d)
{}

template<typename T>
inline T& _item<T>::operator*()
{
  return m_data;
}

template<typename T>
inline T* _item<T>::operator->()
{
  return &m_data;
}

template<typename T>
inline bool _item<T>::operator==(const _item& i) const
{
  return identical(*this, i);
}

template<typename T>
inline bool _item<T>::operator!=(const _item& i) const
{
  return !identical(*this, i);
}

template<typename T>
inline bool _item<T>::identical(const _item &a, const _item &b)
{
  return (&a.m_data == &b.m_data);
}

// SL_ITEM /////////////////////////////////////////////////////////////////////

template<typename T>
slitem<T>::slitem(T& d) :
  _slitem(), _item<T>(d)
{}

template<typename T>
inline bool slitem<T>::attached() const
{
  return _slitem::attached();
}

template<typename T>
inline bool slitem<T>::operator==(const _slitem& i) const
{
  return identical(*this, *static_cast<const slitem*>(&i));
}

template<typename T>
inline bool slitem<T>::operator==(const _item<T>& i) const
{
  return identical(*this, *static_cast<const slitem*>(&i));
}

template<typename T>
inline bool slitem<T>::operator==(const slitem& i) const
{
  return identical(*this, i);
}

template<typename T>
inline bool slitem<T>::operator!=(const _slitem& i) const
{
  return !identical(*this, *static_cast<const slitem*>(&i));
}

template<typename T>
inline bool slitem<T>::operator!=(const _item<T>& i) const
{
  return !identical(*this, *static_cast<const slitem*>(&i));
}

template<typename T>
inline bool slitem<T>::operator!=(const slitem& i) const
{
  return !identical(*this, i);
}

template<typename T>
inline bool slitem<T>::identical(const slitem &a, const slitem &b)
{
  return (_slitem::identical(a, b) && _item<T>::identical(a, b));
}

// DL_ITEM /////////////////////////////////////////////////////////////////////

template<typename T>
dlitem<T>::dlitem(T& d) :
  _dlitem(), _item<T>(d)
{}

template<typename T>
inline bool dlitem<T>::attached() const
{
  return _dlitem::attached();
}

template<typename T>
inline bool dlitem<T>::operator==(const _dlitem& i) const
{
  return identical(*this, *static_cast<const dlitem*>(&i));
}

template<typename T>
inline bool dlitem<T>::operator==(const _item<T>& i) const
{
  return identical(*this, *static_cast<const dlitem*>(&i));
}

template<typename T>
inline bool dlitem<T>::operator==(const dlitem& i) const
{
  return identical(*this, i);
}

template<typename T>
inline bool dlitem<T>::operator!=(const _dlitem& i) const
{
  return !identical(*this, *static_cast<const dlitem*>(&i));
}

template<typename T>
inline bool dlitem<T>::operator!=(const _item<T>& i) const
{
  return !identical(*this, *static_cast<const dlitem*>(&i));
}

template<typename T>
inline bool dlitem<T>::operator!=(const dlitem& i) const
{
  return !identical(*this, i);
}

template<typename T>
inline bool dlitem<T>::identical(const dlitem &a, const dlitem &b)
{
  return (_dlitem::identical(a, b) && _item<T>::identical(a, b));
}

////////////////////////////////////////////////////////////////////////////////
// ITERATORS                                                                  //
////////////////////////////////////////////////////////////////////////////////

// SL_ITERATOR /////////////////////////////////////////////////////////////////

template<typename T>
sliterator<T>::sliterator() :
  m_item(nullptr)
{}

template<typename T>
sliterator<T>::sliterator(const sliterator& it) :
  m_item(it.m_item)
{}

template<typename T>
inline sliterator<T>& sliterator<T>::operator=(const sliterator& it)
{
  this->m_item = it.m_item;
  return *this;
}

template<typename T>
inline bool sliterator<T>::operator==(const sliterator& it) const
{
  return (this->m_item == it.m_item);
}

template<typename T>
inline bool sliterator<T>::operator!=(const sliterator& it) const
{
  return (this->m_item != it.m_item);
}

template<typename T>
inline sliterator<T>& sliterator<T>::operator++()
{
  if (this->m_item != nullptr) {
    this->m_item = static_cast<item*>(this->m_item->m_next);
  }
  return *this;
}

template<typename T>
inline T& sliterator<T>::operator*()
{
  return this->m_item->m_data;
}

template<typename T>
inline T* sliterator<T>::operator->()
{
  return (this->m_item != nullptr) ? &(this->m_item->m_data) : nullptr;
}

template<typename T>
T* sliterator<T>::peek(const unsigned int n) const
{
  item* i(this->m_item);
  unsigned int cnt(n);
  // peek forwards
  while (cnt > 0 && i != nullptr) {
    i = static_cast<item*>(i->m_next);
    --cnt;
  }
  return (i != nullptr) ? &(i->m_data) : nullptr;
}

template<typename T>
inline const typename sliterator<T>::item* sliterator<T>::valid() const
{
  return this->m_item;
}

// DL_ITERATOR /////////////////////////////////////////////////////////////////

template<typename T>
dliterator<T>::dliterator() :
  m_item(nullptr)
{}

template<typename T>
dliterator<T>::dliterator(const dliterator& it) :
  m_item(it.m_item)
{}

template<typename T>
inline dliterator<T>& dliterator<T>::operator=(const dliterator& it)
{
  this->m_item = it.m_item;
  return *this;
}

template<typename T>
inline bool dliterator<T>::operator==(const dliterator& it) const
{
  return (this->m_item == it.m_item);
}

template<typename T>
inline bool dliterator<T>::operator!=(const dliterator& it) const
{
  return (this->m_item != it.m_item);
}

template<typename T>
inline dliterator<T>& dliterator<T>::operator++()
{
  if (this->m_item != nullptr) {
    this->m_item = static_cast<item*>(this->m_item->m_next);
  }
  return *this;
}

template<typename T>
inline dliterator<T>& dliterator<T>::operator--()
{
  if (this->m_item != nullptr) {
    this->m_item = static_cast<item*>(this->m_item->m_prev);
  }
  return *this;
}

template<typename T>
inline T& dliterator<T>::operator*()
{
  return this->m_item->m_data;
}

template<typename T>
inline T* dliterator<T>::operator->()
{
  return (this->m_item != nullptr) ? &(this->m_item->m_data) : nullptr;
}

template<typename T>
T* dliterator<T>::peek(const int n) const
{
  item* i(this->m_item);
  int cnt(n);
  // peek forwards or skip if n <= 0
  while (cnt > 0 && i != nullptr) {
    i = static_cast<item*>(i->m_next);
    --cnt;
  }
  // peek backwards or skip if n >= 0
  while (cnt < 0 && i != nullptr) {
    i = static_cast<item*>(i->m_prev);
    ++cnt;
  }
  return (i != nullptr) ? &(i->m_data) : nullptr;
}

template<typename T>
inline  const typename dliterator<T>::item* dliterator<T>::valid() const
{
  return this->m_item;
}

////////////////////////////////////////////////////////////////////////////////
// BASE DLIST CLASSES                                                         //
////////////////////////////////////////////////////////////////////////////////

// _BASE_DLIST /////////////////////////////////////////////////////////////////

template<linked_t LINKED, property_t PROPERTY, typename T>
_dlist<LINKED, PROPERTY, T>::_dlist()
{}

// _BASE_SLDLIST ///////////////////////////////////////////////////////////////

template<property_t PROPERTY, typename T>
_sldlist<PROPERTY, T>::_sldlist() :
  _dlist<SINGLY_LINKED, PROPERTY, T>()
{}

// _BASE_DLDLIST ///////////////////////////////////////////////////////////////

template<property_t PROPERTY, typename T>
_dldlist<PROPERTY, T>::_dldlist() :
  _dlist<DOUBLY_LINKED, PROPERTY, T>()
{}

////////////////////////////////////////////////////////////////////////////////
// SINGLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

// SINGLY LINKED DLIST /////////////////////////////////////////////////////////

template<typename T>
sldlist<T>::sldlist() :
  _sldlist<NONE, T>(), _first(), _last()
{}

template<typename T>
inline bool sldlist<T>::empty() const
{
  assert(!((this->_first.m_item == nullptr) ^ (this->_last.m_item == nullptr)));

  return (this->_first.m_item == nullptr);
}

template<typename T>
size_t sldlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(1);
    iterator it(this->_first);
    while (it != this->_last) {
      ++it;
      ++cnt;
    }
    return cnt;
  }
}

template<typename T>
bool sldlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterate through the list and search for d
  else {
    iterator it(this->_first);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->_last) {
        ++it;
      }
      // break the loop when all items have been checked
      else {
        return false;
      }
    }
  }
}

template<typename T>
size_t sldlist<T>::clear()
{
  size_t cnt(0);
  // pop all elements
  while (this->pop_front() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename sldlist<T>::item* sldlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterat through the list and remove the first item pointing to rm
  else {
    iterator current(this->_first);
    iterator last;
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // the first item matches
        if (current == this->_first) {
          // if the last item will be removed, set all pointers accordingly
          if (this->_first == this->_last) {
            this->_first.m_item = nullptr;
            this->_last.m_item = nullptr;
          }
          // increase the _first iterator
          else {
            ++this->_first;
          }
        }
        // the last item matches
        else if (current == this->_last) {
          this->_last = last;
          this->_last.m_item->m_next = nullptr;
        }
        // any item inbetween the first and the last item will be removed
        else {
          last.m_item->m_next = current.m_item->m_next;
        }
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->_last) {
        last = current;
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool sldlist<T>::operator==(const sldlist& l) const
{
  return (this->_first == l._first) && (this->_last == l._last);
}

template<typename T>
inline bool sldlist<T>::operator!=(const sldlist& l) const
{
  return (this->_first != l._first) || (this->_last != l._last);
}

template<typename T>
inline typename sldlist<T>::iterator sldlist<T>::front() const
{
  return this->_first;
}

template<typename T>
inline typename sldlist<T>::iterator sldlist<T>::back() const
{
  return this->_last;
}

template<typename T>
void sldlist<T>::push_front(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize both iterators
  if (this->empty()) {
    this->_first.m_item = &i;
    this->_last.m_item = &i;
    return;
  }
  // append the item at the front
  else {
    i.m_next = this->_first.m_item;
    this->_first.m_item = &i;
    return;
  }
}

template<typename T>
void sldlist<T>::push_back(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize both iterators
  if (this->empty()) {
    this->_first.m_item = &i;
    this->_last.m_item = &i;
    return;
  }
  // append the item at the back
  else {
    this->_last.m_item->m_next = &i;
    ++this->_last;
    return;
  }
}

template<typename T>
typename sldlist<T>::item* sldlist<T>::pop_front()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_first == this->_last) {
    item* i(this->_first.m_item);
    this->_first.m_item = nullptr;
    this->_last.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the first item
  else {
    item* i(this->_first.m_item);
    ++this->_first;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename sldlist<T>::item* sldlist<T>::pop_back()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_first == this->_last) {
    item* i(this->_last.m_item);
    this->_first.m_item = nullptr;
    this->_last.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the last item
  else {
    item* i(this->_last.m_item);
    // find the item before the last
    iterator it(this->_first);
    while (it.m_item->m_next != this->_last.m_item) {
      ++it;
    }
    this->_last = it;
    this->_last.m_item->m_next = nullptr;
    return i;
  }
}

// SINGLY LINKED ORDERED DLIST /////////////////////////////////////////////////

template<typename T>
slodlist<T>::slodlist(cmp_f& cmp) :
  _sldlist<ORDERED, T>(), m_min(), m_max(), m_cmp(cmp)
{}

template<typename T>
inline bool slodlist<T>::empty() const
{
  assert(!((this->m_min.m_item == nullptr) ^ (this->m_max.m_item == nullptr)));

  return (this->m_min.m_item == nullptr);
}

template<typename T>
size_t slodlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(1);
    iterator it(this->m_min);
    while (it != this->m_max) {
      ++it;
      ++cnt;
    }
    return cnt;
  }
}

template<typename T>
bool slodlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterate through the list and search for d
  else {
    iterator it(this->m_min);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->m_max) {
        ++it;
      }
      // break the loop when all items have been checked
      else {
        return false;
      }
    }
  }
}

template<typename T>
size_t slodlist<T>::clear()
{
  size_t cnt(0);
  // pop all elements
  while (this->removeMin() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename slodlist<T>::item* slodlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterate through the list and remove the first item poining to rm
  else {
    iterator current(this->m_min);
    iterator last;
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // the minimum item matches
        if (current == this->m_min) {
          // if the last item will be removed, set all pointers accordingly
          if (this->m_min == this->m_max) {
            this->m_min.m_item = nullptr;
            this->m_max.m_item = nullptr;
          }
          // increase the m_min iterator
          else {
            ++this->m_min;
          }
        }
        // the maximum item matches
        else if (current == this->m_max) {
          this->m_max = last;
          this->m_max.m_item->m_next = nullptr;
        }
        // any item inbetween the minimum and the maximum will be removed
        else {
          last.m_item->m_next = current.m_item->m_next;
        }
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->m_max) {
        last = current;
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool slodlist<T>::operator==(const slodlist& l) const
{
  return (this->m_min == l.m_min) && (this->m_max == l.m_max) && (this->m_cmp == l.m_cmp);
}

template<typename T>
inline bool slodlist<T>::operator!=(const slodlist& l) const
{
  return (this->m_min != l.m_min) || (this->m_max != l.m_max) || (this->m_cmp != l.m_cmp);
}

template<typename T>
inline typename slodlist<T>::iterator slodlist<T>::min() const
{
  return this->m_min;
}

template<typename T>
inline typename slodlist<T>::iterator slodlist<T>::max() const
{
  return this->m_max;
}

template<typename T>
void slodlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize it
  if (this->empty()) {
    this->m_min.m_item = &i;
    this->m_max.m_item = &i;
    return;
  }
  // iterate through the list and insert the item at the correct location
  else {
    iterator current(this->m_min);
    iterator last;
    while (true) {
      // check, whether i is smaller compared to the current item
      if (!this->m_cmp(*current, *i)) {
        // special case: if i is smaller than the first item, prepend it
        if (current == this->m_min) {
          i.m_next = this->m_min.m_item;
          this->m_min.m_item = &i;
        }
        // insert the item
        else {
          last.m_item->m_next = &i;
          i.m_next = current.m_item;
        }
        return;
      }
      // if all items in the list are smaller, append it
      else if (current == this->m_max) {
        this->m_max.m_item->m_next = &i;
        ++this->m_max;
        return;
      }
      // keep going as long as the end is not reached yet
      else {
        last = current;
        ++current;
      }
    }
  }
}

template<typename T>
typename slodlist<T>::item* slodlist<T>::removeMin()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->m_min == this->m_max) {
    item* i(this->m_min.m_item);
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the smallest item
  else {
    item* i(this->m_min.m_item);
    ++this->m_min;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename slodlist<T>::item* slodlist<T>::removeMax()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->m_min == this->m_max) {
    item* i(this->m_max.m_item);
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the largest item
  else {
    item* i(this->m_max.m_item);
    // find the item before the last
    iterator it(this->m_min);
    while (it.m_item->m_next != this->m_max.m_item) {
      ++it;
    }
    this->m_max = it;
    this->m_max.m_item->m_next = nullptr;
    return i;
  }
}

template<typename T>
void slodlist<T>::sort()
{
  // if the list contains less than two items, return immediately
  if (this->m_min.m_item == this->m_max.m_item) {
    return;
  }
  // clear the list, and reinsert all items
  else {
    // initialize temporary iterators and item pointer
    iterator min_tmp(this->m_min);
    iterator max_tmp(this->m_max);
    item* i(nullptr);

    // reset the list
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;

    // re-insert all items
    bool abort(false);
    while (!abort) {
      // check if this is the last iteration
      abort = (min_tmp == max_tmp);

      // detach and item and re-insert it in this list
      i = min_tmp.m_item;
      ++min_tmp;
      i->m_next = nullptr;
      this->insert(*i);
    }

    return;
  }
}

//// SINGLY LINKED CIRCULAR DLIST //////////////////////////////////////////////

template<typename T>
slcdlist<T>::slcdlist() :
  _sldlist<CIRCULAR, T>(), m_latest()
{}

template<typename T>
inline bool slcdlist<T>::empty() const
{
  return (this->m_latest.m_item == nullptr);
}

template<typename T>
size_t slcdlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(0);
    iterator it(this->m_latest);
    do {
      ++it;
      ++cnt;
    } while (it != this->m_latest);
    return cnt;
  }
}

template<typename T>
bool slcdlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterate through the list and search for d
  else {
    iterator it(this->m_latest);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else {
        ++it;
        // break the loop when all items have been checked
        if (it == this->m_latest) {
          return false;
        }
      }
    }
  }
}

template<typename T>
size_t slcdlist<T>::clear()
{
  size_t cnt(0);
  // remove all elements
  while (this->remove_eldest() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename slcdlist<T>::item* slcdlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterate through the list and remove the first item poitning to rm
  else {
    iterator current(this->m_latest);
    ++current;
    iterator last(this->m_latest);
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // if the m_latest item matches
        if (current == this->m_latest) {
          // if the last item will be removed, set all pointers accordingly
          if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
            item* i(this->m_latest.m_item);
            this->m_latest.m_item = nullptr;
            return i;
          }
          // decrease the m_latest iterator
          else {
            this->m_latest = last;
          }
        }
        last.m_item->m_next = current.m_item->m_next;
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->m_latest) {
        last = current;
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool slcdlist<T>::operator==(const slcdlist& l) const
{
  return (this->m_latest == l.m_latest);
}

template<typename T>
inline bool slcdlist<T>::operator!=(const slcdlist& l) const
{
  return (this->m_latest != l.m_latest);
}

template<typename T>
inline typename slcdlist<T>::iterator slcdlist<T>::latest() const
{
  return this->m_latest;
}

template<typename T>
inline typename slcdlist<T>::iterator slcdlist<T>::eldest() const
{
  iterator it(this->m_latest);
  ++it;
  return it;
}

template<typename T>
void slcdlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize its iterator and the items m_next pointer
  if (this->empty()){
    this->m_latest.m_item = &i;
    i.m_next = &i;
    return;
  }
  // insert the item as the m_latest
  else {
    i.m_next = this->m_latest.m_item->m_next;
    this->m_latest.m_item->m_next = &i;
    ++this->m_latest;
    return;
  }
}

template<typename T>
typename slcdlist<T>::item* slcdlist<T>::removeLatest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
    item* i(this->m_latest.m_item);
    this->m_latest.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the latest and decrement the iterator
  else {
    item* i(this->m_latest.m_item);
    // search for the second latest item
    iterator second_latest(this->m_latest);
    ++second_latest;
    while (second_latest.m_item->m_next != this->m_latest.m_item) {
      ++second_latest;
    }
    second_latest.m_item->m_next = this->m_latest.m_item->m_next;
    this->m_latest = second_latest;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename slcdlist<T>::item* slcdlist<T>::remove_eldest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
    item* i(this->m_latest.m_item);
    this->m_latest.m_item = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the eldest
  else {
    item* i(static_cast<item*>(this->m_latest.m_item->m_next));
    this->m_latest.m_item->m_next = i->m_next;
    i->m_next = nullptr;
    return i;
  }
}

////////////////////////////////////////////////////////////////////////////////
// DOUBLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

//// DOUBLY LINKED DLIST ///////////////////////////////////////////////////////

template<typename T>
dldlist<T>::dldlist() :
  _dldlist<NONE, T>(), _first(), _last()
{}

template<typename T>
inline bool dldlist<T>::empty() const
{
  assert(!((this->_first.m_item == nullptr) ^ (this->_last.m_item == nullptr)));

  return (this->_first.m_item == nullptr);
}

template<typename T>
size_t dldlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(1);
    iterator it(this->_first);
    while (it != this->_last) {
      ++it;
      ++cnt;
    }
    return cnt;
  }
}

template<typename T>
bool dldlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterate through the list and search for d
  else {
    iterator it(this->_first);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->_last) {
        ++it;
      }
      // break the loop when all ites have been checked
      else {
        return false;
      }
    }
  }
}

template<typename T>
size_t dldlist<T>::clear()
{
  size_t cnt(0);
  // pop all elements
  while (this->pop_front() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename dldlist<T>::item* dldlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterate throuh the list and remove the first item pointing to rm
  else {
    iterator current(this->_first);
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // the first item matches
        if (current == this->_first) {
          // if the last item will be reomved, set all pointers accordingly
          if (this->_first == this->_last) {
            this->_first.m_item = nullptr;
            this->_last.m_item = nullptr;
          }
          // increase the _first iterator
          else {
            ++this->_first;
            this->_first.m_item->m_prev = nullptr;
          }
        }
        // the last item matches
        else if (current.m_item == this->_last.m_item) {
          --this->_last;
          this->_last.m_item->m_next = nullptr;
        }
        // any item inbetween the first and last item will be removed
        else {
          static_cast<item*>(current.m_item->m_prev)->m_next = current.m_item->m_next;
          static_cast<item*>(current.m_item->m_next)->m_prev = current.m_item->m_prev;
        }
        current.m_item->m_prev = nullptr;
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep goind as long as the end is not reached yet
      else if (current != this->_last) {
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool dldlist<T>::operator==(const dldlist& l) const
{
  return (this->_first == l._first) && (this->_last == l._last);
}

template<typename T>
inline bool dldlist<T>::operator!=(const dldlist& l) const
{
  return (this->_first != l._first) || (this->_last != l._last);
}

template<typename T>
inline typename dldlist<T>::iterator dldlist<T>::front() const
{
  return this->_first;
}

template<typename T>
inline typename dldlist<T>::iterator dldlist<T>::back() const
{
  return this->_last;
}

template<typename T>
void dldlist<T>::push_front(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize both iterators
  if (this->empty()) {
    this->_first.m_item = &i;
    this->_last.m_item = &i;
    return;
  }
  // append the item at the front
  else {
    i.m_next = this->_first.m_item;
    this->_first.m_item->m_prev = &i;
    --this->_first;
    return;
  }
}

template<typename T>
void dldlist<T>::push_back(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize both iterators
  if (this->empty()) {
    this->_first.m_item = &i;
    this->_last.m_item = &i;
    return;
  }
  // append the item at the back;
  else {
    this->_last.m_item->m_next = &i;
    i.m_prev = this->_last.m_item;
    ++this->_last;
    return;
  }
}

template<typename T>
typename dldlist<T>::item* dldlist<T>::pop_front()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_first == this->_last) {
    item* i(this->_first.m_item);
    this->_first.m_item = nullptr;
    this->_last.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the first item
  else {
    item* i(this->_first.m_item);
    ++this->_first;
    this->_first.m_item->m_prev = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename dldlist<T>::item* dldlist<T>::pop_back()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_first == this->_last) {
    item* i(this->_last.m_item);
    this->_first.m_item = nullptr;
    this->_last.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the last item
  else {
    item* i(this->_last.m_item);
    --this->_last;
    this->_last.m_item->m_next = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

//// DOUBLY LINKED ORDERED DLIST ///////////////////////////////////////////////

template<typename T>
dlodlist<T>::dlodlist(cmp_f& cmp) :
  _dldlist<ORDERED, T>(), m_min(), m_max(), m_cmp(cmp)
{}

template<typename T>
inline bool dlodlist<T>::empty() const
{
  assert(!((this->m_min.m_item == nullptr) ^ (this->m_max.m_item == nullptr)));

  return (this->m_min.m_item == nullptr);
}

template<typename T>
size_t dlodlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(1);
    iterator it(this->m_min);
    while (it != this->m_max) {
      ++it;
      ++cnt;
    }
    return cnt;
  }
}

template<typename T>
bool dlodlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterator through the list and search for d
  else {
    iterator it(this->m_min);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->m_max) {
        ++it;
      }
      // break the loop when all item have been checked
      else {
        return false;
      }
    }
  }
}

template<typename T>
size_t dlodlist<T>::clear()
{
  size_t cnt(0);
  // pop all elements
  while (this->removeMin() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename dlodlist<T>::item* dlodlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterate through the list and remove the first item pointing to rm
  else {
    iterator current(this->m_min);
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // the minimum item matches
        if (current == this->m_min) {
          // if the last item will be removed, set all pointers accordingly
          if (this->m_min == this->m_max) {
            this->m_min.m_item = nullptr;
            this->m_max.m_item = nullptr;
          }
          // increase the m_min iterator
          else {
            ++this->m_min;
            this->m_min.m_item->m_prev = nullptr;
          }
        }
        // the maximum item matches
        else if (current == this->m_max) {
          --this->m_max;
          this->m_max.m_item->m_next = nullptr;
        }
        // any item inbtetween the minimum and the maximum will be removed
        else {
          static_cast<item*>(current.m_item->m_prev)->m_next = current.m_item->m_next;
          static_cast<item*>(current.m_item->m_next)->m_prev = current.m_item->m_prev;
        }
        current.m_item->m_prev = nullptr;
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->m_max) {
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool dlodlist<T>::operator==(const dlodlist& l) const
{
  return (this->m_min == l.m_min) && (this->m_max == l.m_max) && (this->m_cmp == l.m_cmp);
}

template<typename T>
inline bool dlodlist<T>::operator!=(const dlodlist& l) const
{
  return (this->m_min != l.m_min) || (this->m_max != l.m_max) || (this->m_cmp != l.m_cmp);
}

template<typename T>
inline typename dlodlist<T>::iterator dlodlist<T>::min() const
{
  return this->m_min;
}

template<typename T>
inline typename dlodlist<T>::iterator dlodlist<T>::max() const
{
  return this->m_max;
}

template<typename T>
void dlodlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize it
  if (this->empty()) {
    this->m_min.m_item = &i;
    this->m_max.m_item = &i;
    return;
  }
  // iteratr through the list and insert the item at the correct location
  else {
    iterator current(this->m_min);
    while (true) {
      // check, whether i is smaller compared to the current item and insert it
      if (!m_cmp(*current, *i)) {
        // special case: if i is smaller than the first item, prepend it
        if (current == this->m_min) {
          i.m_next = current.m_item;
          current.m_item->m_prev = &i;
          --this->m_min;
        }
        // insert the item
        else {
          static_cast<item*>(current.m_item->m_prev)->m_next = static_cast<item*>(&i);
          i.m_prev = current.m_item->m_prev;
          i.m_next = current.m_item;
          current.m_item->m_prev = &i;
        }
        return;
      }
      // if all items in the list are smaller, append it
      else if (current == this->m_max) {
        this->m_max.m_item->m_next = &i;
        i.m_prev = this->m_max.m_item;
        ++this->m_max;
        return;
      }
      // keep going as long as the end is not reached yet
      else {
        ++current;
      }
    }
  }
}

template<typename T>
typename dlodlist<T>::item* dlodlist<T>::removeMin()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->m_min == this->m_max) {
    item* i(this->m_min.m_item);
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the smallest item
  else {
    item* i(this->m_min.m_item);
    ++this->m_min;
    this->m_min.m_item->m_prev = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename dlodlist<T>::item* dlodlist<T>::removeMax()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  if (this->m_min == this->m_max) {
    item* i(this->m_max.m_item);
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the largest item
  else {
    item* i(this->m_max.m_item);
    --this->m_max;
    this->m_max.m_item->m_next = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
void dlodlist<T>::sort()
{
  // if the list contains less than two items, return immediately
  if (this->m_min.m_item == this->m_max.m_item) {
    return;
  }
  // clear the list, and reinsert all items
  else {
    // initialize temporary iterators and item pointer
    iterator min_tmp(this->m_min);
    iterator max_tmp(this->m_max);
    item* i(nullptr);

    // reset the list
    this->m_min.m_item = nullptr;
    this->m_max.m_item = nullptr;

    // re-insert all items
    bool abort(false);
    while (!abort) {
      // check if this is the last iteration
      abort = (min_tmp == max_tmp);

      // detach and item and re-insert it in this list
      i = min_tmp.m_item;
      ++min_tmp;
      i->m_prev = nullptr;
      i->m_next = nullptr;
      this->insert(*i);
    }

    return;
  }
}

//// DOUBLY LINKED CIRCULAR DLIST //////////////////////////////////////////////

template<typename T>
dlcdlist<T>::dlcdlist() :
  _dldlist<CIRCULAR, T>(), m_latest()
{}

template<typename T>
inline bool dlcdlist<T>::empty() const
{
  return (this->m_latest.m_item == nullptr);
}

template<typename T>
size_t dlcdlist<T>::size() const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return 0;
  }
  // iterate through the list
  else {
    size_t cnt(0);
    iterator it(this->m_latest);
    do {
      ++it;
      ++cnt;
    } while (it != this->m_latest);
    return cnt;
  }
}

template<typename T>
bool dlcdlist<T>::contains(const T& d) const
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return false;
  }
  // iterate through the list and search for d
  else {
    iterator it(this->m_latest);
    while (true) {
      // test for d
      if (&(it.m_item->m_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else {
        ++it;
        // break the loop when all items have been checked
        if (it == this->m_latest) {
          return false;
        }
      }
    }
  }
}

template<typename T>
size_t dlcdlist<T>::clear()
{
  size_t cnt(0);
  // remove all elements
  while (this->remove_eldest() != nullptr) {
    ++cnt;
  }
  return cnt;
}

template<typename T>
typename dlcdlist<T>::item* dlcdlist<T>::remove(const T& rm)
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // iterator through the list and remove the first item pointing to rm
  else {
    iterator current(this->m_latest);
    ++current;
    while (true) {
      // test for rm
      if (&(current.m_item->m_data) == &rm) {
        // if the m_latest item matches
        if (current == this->m_latest) {
          // if the last item will be removed, set all pointer accordingly
          if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
            item* i(this->m_latest.m_item);
            this->m_latest.m_item = nullptr;
            return i;
          }
          // decrease the m_latest iterator
          else {
            --this->m_latest;
          }
        }
        static_cast<item*>(current.m_item->m_prev)->m_next = current.m_item->m_next;
        static_cast<item*>(current.m_item->m_next)->m_prev = current.m_item->m_prev;
        current.m_item->m_prev = nullptr;
        current.m_item->m_next = nullptr;
        return current.m_item;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->m_latest) {
        ++current;
      }
      // break the loop when all items have been checked
      else {
        return nullptr;
      }
    }
  }
}

template<typename T>
inline bool dlcdlist<T>::operator==(const dlcdlist& l) const
{
  return (this->m_latest == l.m_latest);
}

template<typename T>
inline bool dlcdlist<T>::operator!=(const dlcdlist& l) const
{
  return (this->m_latest != l.m_latest);
}

template<typename T>
inline typename dlcdlist<T>::iterator dlcdlist<T>::latest() const
{
  return this->m_latest;
}

template<typename T>
inline typename dlcdlist<T>::iterator dlcdlist<T>::eldest() const
{
  iterator it(this->m_latest);
  ++it;
  return it;
}

template <typename T>
void dlcdlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize its iterator and the items m_prev and m_next pointers
  if (this->empty()) {
    this->m_latest.m_item = &i;
    i.m_prev = &i;
    i.m_next = &i;
    return;
  }
  // insert the item as the m_latest
  else {
    i.m_prev = this->m_latest.m_item;
    i.m_next = this->m_latest.m_item->m_next;
    static_cast<item*>(this->m_latest.m_item->m_next)->m_prev = &i;
    this->m_latest.m_item->m_next = &i;
    ++this->m_latest;
    return;
  }
}

template<typename T>
typename dlcdlist<T>::item* dlcdlist<T>::removeLatest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
    item* i(this->m_latest.m_item);
    this->m_latest.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the latest and decrement the iterator
  else {
    item* i(this->m_latest.m_item);
    --this->m_latest;
    this->m_latest.m_item->m_next = i->m_next;
    static_cast<item*>(this->m_latest.m_item->m_next)->m_prev = this->m_latest.m_item;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

template<typename T>
typename dlcdlist<T>::item* dlcdlist<T>::remove_eldest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->m_latest.m_item->m_next == this->m_latest.m_item) {
    item* i(this->m_latest.m_item);
    this->m_latest.m_item = nullptr;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
  // remove the eldest
  else {
    item* i(static_cast<item*>(this->m_latest.m_item->m_next));
    this->m_latest.m_item->m_next = i->m_next;
    static_cast<item*>(this->m_latest.m_item->m_next)->m_prev = this->m_latest.m_item;
    i->m_prev = nullptr;
    i->m_next = nullptr;
    return i;
  }
}

} /* namespace dlist */

#endif /* _DLIST_TPP_ */
