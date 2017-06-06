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

// _BASE_ITEM //////////////////////////////////////////////////////////////////

template<typename T>
_base_item<T>::_base_item(T& d) :
  _data(d)
{}

template<typename T>
inline T& _base_item<T>::operator *()
{
  return _data;
}

template<typename T>
inline T* _base_item<T>::operator ->()
{
  return &_data;
}

// SL_ITEM /////////////////////////////////////////////////////////////////////

template<typename T>
sl_item<T>::sl_item(T& d) :
  _base_item<T>(d), _next(nullptr)
{}

template<typename T>
inline bool sl_item<T>::attached() const
{
  return (this->_next != nullptr);
}

template<typename T>
inline bool sl_item<T>::operator ==(const sl_item& i) const
{
  return identical(*this, i);
}

template<typename T>
inline bool sl_item<T>::operator !=(const sl_item& i) const
{
  return !identical(*this, i);
}

template<typename T>
inline bool sl_item<T>::identical(const sl_item &a, const sl_item &b)
{
  return (&a._data == &b._data) && (a._next == b._next);
}

// DL_ITEM /////////////////////////////////////////////////////////////////////

template<typename T>
dl_item<T>::dl_item(T& d) :
  _base_item<T>(d), _prev(nullptr), _next(nullptr)
{}

template<typename T>
inline bool dl_item<T>::attached() const
{
  return (this->_prev != nullptr || this->_next != nullptr);
}

template<typename T>
inline bool dl_item<T>::operator ==(const dl_item& i) const
{
  return identical(*this, i);
}

template<typename T>
inline bool dl_item<T>::operator !=(const dl_item& i) const
{
  return !identical(*this, i);
}

template<typename T>
inline bool dl_item<T>::identical(const dl_item &a, const dl_item &b)
{
  return (&a._data == &b._data) && (a._prev == b._prev) && (a._next == b._next);
}

////////////////////////////////////////////////////////////////////////////////
// ITERATORS                                                                  //
////////////////////////////////////////////////////////////////////////////////

// SL_ITERATOR /////////////////////////////////////////////////////////////////

template<typename T>
sl_iterator<T>::sl_iterator() :
  _p(nullptr)
{}

template<typename T>
sl_iterator<T>::sl_iterator(const sl_iterator& it) :
  _p(it._p)
{}

template<typename T>
inline sl_iterator<T>& sl_iterator<T>::operator =(const sl_iterator& it)
{
  this->_p = it._p;
  return *this;
}

template<typename T>
inline bool sl_iterator<T>::operator ==(const sl_iterator& it) const
{
  return (this->_p == it._p);
}

template<typename T>
inline bool sl_iterator<T>::operator !=(const sl_iterator& it) const
{
  return (this->_p != it._p);
}

template<typename T>
inline sl_iterator<T>& sl_iterator<T>::operator ++()
{
  if (this->_p != nullptr) {
    this->_p = this->_p->_next;
  }
  return *this;
}

template<typename T>
inline T& sl_iterator<T>::operator *()
{
  return this->_p->_data;
}

template<typename T>
inline T* sl_iterator<T>::operator ->()
{
  return (this->_p != nullptr) ? &(this->_p->_data) : nullptr;
}

template<typename T>
T* sl_iterator<T>::peek(const unsigned int n) const
{
  item_t* i(this->_p);
  unsigned int cnt(n);
  // peek forwards
  while (cnt > 0 && i != nullptr) {
    i = i->_next;
    --cnt;
  }
  return (i != nullptr) ? &(i->_data) : nullptr;
}

template<typename T>
inline const typename sl_iterator<T>::item_t* sl_iterator<T>::item() const
{
  return this->_p;
}

// DL_ITERATOR /////////////////////////////////////////////////////////////////

template<typename T>
dl_iterator<T>::dl_iterator() :
  _p(nullptr)
{}

template<typename T>
dl_iterator<T>::dl_iterator(const dl_iterator& it) :
  _p(it._p)
{}

template<typename T>
inline dl_iterator<T>& dl_iterator<T>::operator =(const dl_iterator& it)
{
  this->_p = it._p;
  return *this;
}

template<typename T>
inline bool dl_iterator<T>::operator ==(const dl_iterator& it) const
{
  return (this->_p == it._p);
}

template<typename T>
inline bool dl_iterator<T>::operator !=(const dl_iterator& it) const
{
  return (this->_p != it._p);
}

template<typename T>
inline dl_iterator<T>& dl_iterator<T>::operator ++()
{
  if (this->_p != nullptr) {
    this->_p = this->_p->_next;
  }
  return *this;
}

template<typename T>
inline dl_iterator<T>& dl_iterator<T>::operator --()
{
  if (this->_p != nullptr) {
    this->_p = this->_p->_prev;
  }
  return *this;
}

template<typename T>
inline T& dl_iterator<T>::operator *()
{
  return this->_p->_data;
}

template<typename T>
inline T* dl_iterator<T>::operator ->()
{
  return (this->_p != nullptr) ? &(this->_p->_data) : nullptr;
}

template<typename T>
T* dl_iterator<T>::peek(const int n) const
{
  item_t* i(this->_p);
  int cnt(n);
  // peek forwards or skip if n <= 0
  while (cnt > 0 && i != nullptr) {
    i = i->_next;
    --cnt;
  }
  // peek backwards or skip if n >= 0
  while (cnt < 0 && i != nullptr) {
    i = i->_prev;
    ++cnt;
  }
  return (i != nullptr) ? &(i->_data) : nullptr;
}

template<typename T>
inline  const typename dl_iterator<T>::item_t* dl_iterator<T>::item() const
{
  return this->_p;
}

////////////////////////////////////////////////////////////////////////////////
// BASE DLIST CLASSES                                                         //
////////////////////////////////////////////////////////////////////////////////

// _BASE_DLIST /////////////////////////////////////////////////////////////////

template<linked_t LINKED, property_t PROPERTY, typename T>
_base_dlist<LINKED, PROPERTY, T>::_base_dlist()
{}

// _BASE_SLDLIST ///////////////////////////////////////////////////////////////

template<property_t PROPERTY, typename T>
_base_sldlist<PROPERTY, T>::_base_sldlist() :
  _base_dlist<SINGLY_LINKED, PROPERTY, T>()
{}

// _BASE_DLDLIST ///////////////////////////////////////////////////////////////

template<property_t PROPERTY, typename T>
_base_dldlist<PROPERTY, T>::_base_dldlist() :
  _base_dlist<DOUBLY_LINKED, PROPERTY, T>()
{}

////////////////////////////////////////////////////////////////////////////////
// SINGLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

// SINGLY LINKED DLIST /////////////////////////////////////////////////////////

template<typename T>
sldlist<T>::sldlist() :
  _base_sldlist<NONE, T>(), _first(), _last()
{}

template<typename T>
inline bool sldlist<T>::empty() const
{
  assert(!((this->_first._p == nullptr) ^ (this->_last._p == nullptr)));

  return (this->_first._p == nullptr);
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
      if (&(it._p->_data) == &d) {
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
      if (&(current._p->_data) == &rm) {
        // the first item matches
        if (current == this->_first) {
          // if the last item will be removed, set all pointers accordingly
          if (this->_first == this->_last) {
            this->_first._p = nullptr;
            this->_last._p = nullptr;
          }
          // increase the _first iterator
          else {
            ++this->_first;
          }
        }
        // the last item matches
        else if (current == this->_last) {
          this->_last = last;
          this->_last._p->_next = nullptr;
        }
        // any item inbetween the first and the last item will be removed
        else {
          last._p->_next = current._p->_next;
        }
        current._p->_next = nullptr;
        return current._p;
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
inline bool sldlist<T>::operator ==(const sldlist& l) const
{
  return (this->_first == l._first) && (this->_last == l._last);
}

template<typename T>
inline bool sldlist<T>::operator !=(const sldlist& l) const
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
    this->_first._p = &i;
    this->_last._p = &i;
    return;
  }
  // append the item at the front
  else {
    i._next = this->_first._p;
    this->_first._p = &i;
    return;
  }
}

template<typename T>
void sldlist<T>::push_back(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize both iterators
  if (this->empty()) {
    this->_first._p = &i;
    this->_last._p = &i;
    return;
  }
  // append the item at the back
  else {
    this->_last._p->_next = &i;
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
    item* i(this->_first._p);
    this->_first._p = nullptr;
    this->_last._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the first item
  else {
    item* i(this->_first._p);
    ++this->_first;
    i->_next = nullptr;
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
    item* i(this->_last._p);
    this->_first._p = nullptr;
    this->_last._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the last item
  else {
    item* i(this->_last._p);
    // find the item before the last
    iterator it(this->_first);
    while (it._p->_next != this->_last._p) {
      ++it;
    }
    this->_last = it;
    this->_last._p->_next = nullptr;
    return i;
  }
}

// SINGLY LINKED ORDERED DLIST /////////////////////////////////////////////////

template<typename T>
slodlist<T>::slodlist(cmp_f& cmp) :
  _base_sldlist<ORDERED, T>(), _min(), _max(), _cmp(cmp)
{}

template<typename T>
inline bool slodlist<T>::empty() const
{
  assert(!((this->_min._p == nullptr) ^ (this->_max._p == nullptr)));

  return (this->_min._p == nullptr);
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
    iterator it(this->_min);
    while (it != this->_max) {
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
    iterator it(this->_min);
    while (true) {
      // test for d
      if (&(it._p->_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->_max) {
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
  while (this->remove_min() != nullptr) {
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
    iterator current(this->_min);
    iterator last;
    while (true) {
      // test for rm
      if (&(current._p->_data) == &rm) {
        // the minimum item matches
        if (current == this->_min) {
          // if the last item will be removed, set all pointers accordingly
          if (this->_min == this->_max) {
            this->_min._p = nullptr;
            this->_max._p = nullptr;
          }
          // increase the _min iterator
          else {
            ++this->_min;
          }
        }
        // the maximum item matches
        else if (current == this->_max) {
          this->_max = last;
          this->_max._p->_next = nullptr;
        }
        // any item inbetween the minimum and the maximum will be removed
        else {
          last._p->_next = current._p->_next;
        }
        current._p->_next = nullptr;
        return current._p;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->_max) {
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
inline bool slodlist<T>::operator ==(const slodlist& l) const
{
  return (this->_min == l._min) && (this->_max == l._max) && (this->_cmp == l._cmp);
}

template<typename T>
inline bool slodlist<T>::operator !=(const slodlist& l) const
{
  return (this->_min != l._min) || (this->_max != l._max) || (this->_cmp != l._cmp);
}

template<typename T>
inline typename slodlist<T>::iterator slodlist<T>::min() const
{
  return this->_min;
}

template<typename T>
inline typename slodlist<T>::iterator slodlist<T>::max() const
{
  return this->_max;
}

template<typename T>
void slodlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize it
  if (this->empty()) {
    this->_min._p = &i;
    this->_max._p = &i;
    return;
  }
  // iterate through the list and insert the item at the correct location
  else {
    iterator current(this->_min);
    iterator last;
    while (true) {
      // check, whether i is smaller compared to the current item
      if (!this->_cmp(*current, *i)) {
        // special case: if i is smaller than the first item, prepend it
        if (current == this->_min) {
          i._next = this->_min._p;
          this->_min._p = &i;
        }
        // insert the item
        else {
          last._p->_next = &i;
          i._next = current._p;
        }
        return;
      }
      // if all items in the list are smaller, append it
      else if (current == this->_max) {
        this->_max._p->_next = &i;
        ++this->_max;
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
typename slodlist<T>::item* slodlist<T>::remove_min()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_min == this->_max) {
    item* i(this->_min._p);
    this->_min._p = nullptr;
    this->_max._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the smallest item
  else {
    item* i(this->_min._p);
    ++this->_min;
    i->_next = nullptr;
    return i;
  }
}

template<typename T>
typename slodlist<T>::item* slodlist<T>::remove_max()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_min == this->_max) {
    item* i(this->_max._p);
    this->_min._p = nullptr;
    this->_max._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the largest item
  else {
    item* i(this->_max._p);
    // find the item before the last
    iterator it(this->_min);
    while (it._p->_next != this->_max._p) {
      ++it;
    }
    this->_max = it;
    this->_max._p->_next = nullptr;
    return i;
  }
}

template<typename T>
void slodlist<T>::sort()
{
  // if the list contains less than two items, return immediately
  if (this->_min._p == this->_max._p) {
    return;
  }
  // clear the list, and reinsert all items
  else {
    // initialize temporary iterators and item pointer
    iterator min_tmp(this->_min);
    iterator max_tmp(this->_max);
    item* i(nullptr);

    // reset the list
    this->_min._p = nullptr;
    this->_max._p = nullptr;

    // re-insert all items
    bool abort(false);
    while (!abort) {
      // check if this is the last iteration
      abort = (min_tmp == max_tmp);

      // detach and item and re-insert it in this list
      i = min_tmp._p;
      ++min_tmp;
      i->_next = nullptr;
      this->insert(*i);
    }

    return;
  }
}

//// SINGLY LINKED CIRCULAR DLIST //////////////////////////////////////////////

template<typename T>
slcdlist<T>::slcdlist() :
  _base_sldlist<CIRCULAR, T>(), _latest()
{}

template<typename T>
inline bool slcdlist<T>::empty() const
{
  return (this->_latest._p == nullptr);
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
    iterator it(this->_latest);
    do {
      ++it;
      ++cnt;
    } while (it != this->_latest);
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
    iterator it(this->_latest);
    while (true) {
      // test for d
      if (&(it._p->_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else {
        ++it;
        // break the loop when all items have been checked
        if (it == this->_latest) {
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
    iterator current(this->_latest);
    ++current;
    iterator last(this->_latest);
    while (true) {
      // test for rm
      if (&(current._p->_data) == &rm) {
        // if the _latest item matches
        if (current == this->_latest) {
          // if the last item will be removed, set all pointers accordingly
          if (this->_latest._p->_next == this->_latest._p) {
            item* i(this->_latest._p);
            this->_latest._p = nullptr;
            return i;
          }
          // decrease the _latest iterator
          else {
            this->_latest = last;
          }
        }
        last._p->_next = current._p->_next;
        current._p->_next = nullptr;
        return current._p;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->_latest) {
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
inline bool slcdlist<T>::operator ==(const slcdlist& l) const
{
  return (this->_latest == l._latest);
}

template<typename T>
inline bool slcdlist<T>::operator !=(const slcdlist& l) const
{
  return (this->_latest != l._latest);
}

template<typename T>
inline typename slcdlist<T>::iterator slcdlist<T>::latest() const
{
  return this->_latest;
}

template<typename T>
inline typename slcdlist<T>::iterator slcdlist<T>::eldest() const
{
  iterator it(this->_latest);
  ++it;
  return it;
}

template<typename T>
void slcdlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize its iterator and the items _next pointer
  if (this->empty()){
    this->_latest._p = &i;
    i._next = &i;
    return;
  }
  // insert the item as the _latest
  else {
    i._next = this->_latest._p->_next;
    this->_latest._p->_next = &i;
    ++this->_latest;
    return;
  }
}

template<typename T>
typename slcdlist<T>::item* slcdlist<T>::remove_latest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->_latest._p->_next == this->_latest._p) {
    item* i(this->_latest._p);
    this->_latest._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the latest and decrement the iterator
  else {
    item* i(this->_latest._p);
    // search for the second latest item
    iterator second_latest(this->_latest);
    ++second_latest;
    while (second_latest._p->_next != this->_latest._p) {
      ++second_latest;
    }
    second_latest._p->_next = this->_latest._p->_next;
    this->_latest = second_latest;
    i->_next = nullptr;
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
  else if (this->_latest._p->_next == this->_latest._p) {
    item* i(this->_latest._p);
    this->_latest._p = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the eldest
  else {
    item* i(this->_latest._p->_next);
    this->_latest._p->_next = i->_next;
    i->_next = nullptr;
    return i;
  }
}

////////////////////////////////////////////////////////////////////////////////
// DOUBLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

//// DOUBLY LINKED DLIST ///////////////////////////////////////////////////////

template<typename T>
dldlist<T>::dldlist() :
  _base_dldlist<NONE, T>(), _first(), _last()
{}

template<typename T>
inline bool dldlist<T>::empty() const
{
  assert(!((this->_first._p == nullptr) ^ (this->_last._p == nullptr)));

  return (this->_first._p == nullptr);
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
      if (&(it._p->_data) == &d) {
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
      if (&(current._p->_data) == &rm) {
        // the first item matches
        if (current == this->_first) {
          // if the last item will be reomved, set all pointers accordingly
          if (this->_first == this->_last) {
            this->_first._p = nullptr;
            this->_last._p = nullptr;
          }
          // increase the _first iterator
          else {
            ++this->_first;
            this->_first._p->_prev = nullptr;
          }
        }
        // the last item matches
        else if (current._p == this->_last._p) {
          --this->_last;
          this->_last._p->_next = nullptr;
        }
        // any item inbetween the first and last item will be removed
        else {
          current._p->_prev->_next = current._p->_next;
          current._p->_next->_prev = current._p->_prev;
        }
        current._p->_prev = nullptr;
        current._p->_next = nullptr;
        return current._p;
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
inline bool dldlist<T>::operator ==(const dldlist& l) const
{
  return (this->_first == l._first) && (this->_last == l._last);
}

template<typename T>
inline bool dldlist<T>::operator !=(const dldlist& l) const
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
    this->_first._p = &i;
    this->_last._p = &i;
    return;
  }
  // append the item at the front
  else {
    i._next = this->_first._p;
    this->_first._p->_prev = &i;
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
    this->_first._p = &i;
    this->_last._p = &i;
    return;
  }
  // append the item at the back;
  else {
    this->_last._p->_next = &i;
    i._prev = this->_last._p;
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
    item* i(this->_first._p);
    this->_first._p = nullptr;
    this->_last._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the first item
  else {
    item* i(this->_first._p);
    ++this->_first;
    this->_first._p->_prev = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
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
    item* i(this->_last._p);
    this->_first._p = nullptr;
    this->_last._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the last item
  else {
    item* i(this->_last._p);
    --this->_last;
    this->_last._p->_next = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
}

//// DOUBLY LINKED ORDERED DLIST ///////////////////////////////////////////////

template<typename T>
dlodlist<T>::dlodlist(cmp_f& cmp) :
  _base_dldlist<ORDERED, T>(), _min(), _max(), _cmp(cmp)
{}

template<typename T>
inline bool dlodlist<T>::empty() const
{
  assert(!((this->_min._p == nullptr) ^ (this->_max._p == nullptr)));

  return (this->_min._p == nullptr);
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
    iterator it(this->_min);
    while (it != this->_max) {
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
    iterator it(this->_min);
    while (true) {
      // test for d
      if (&(it._p->_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else if (it != this->_max) {
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
  while (this->remove_min() != nullptr) {
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
    iterator current(this->_min);
    while (true) {
      // test for rm
      if (&(current._p->_data) == &rm) {
        // the minimum item matches
        if (current == this->_min) {
          // if the last item will be removed, set all pointers accordingly
          if (this->_min == this->_max) {
            this->_min._p = nullptr;
            this->_max._p = nullptr;
          }
          // increase the _min iterator
          else {
            ++this->_min;
            this->_min._p->_prev = nullptr;
          }
        }
        // the maximum item matches
        else if (current == this->_max) {
          --this->_max;
          this->_max._p->_next = nullptr;
        }
        // any item inbtetween the minimum and the maximum will be removed
        else {
          current._p->_prev->_next = current._p->_next;
          current._p->_next->_prev = current._p->_prev;
        }
        current._p->_prev = nullptr;
        current._p->_next = nullptr;
        return current._p;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->_max) {
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
inline bool dlodlist<T>::operator ==(const dlodlist& l) const
{
  return (this->_min == l._min) && (this->_max == l._max) && (this->_cmp == l._cmp);
}

template<typename T>
inline bool dlodlist<T>::operator !=(const dlodlist& l) const
{
  return (this->_min != l._min) || (this->_max != l._max) || (this->_cmp != l._cmp);
}

template<typename T>
inline typename dlodlist<T>::iterator dlodlist<T>::min() const
{
  return this->_min;
}

template<typename T>
inline typename dlodlist<T>::iterator dlodlist<T>::max() const
{
  return this->_max;
}

template<typename T>
void dlodlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize it
  if (this->empty()) {
    this->_min._p = &i;
    this->_max._p = &i;
    return;
  }
  // iteratr through the list and insert the item at the correct location
  else {
    iterator current(this->_min);
    while (true) {
      // check, whether i is smaller compared to the current item and insert it
      if (!_cmp(*current, *i)) {
        // special case: if i is smaller than the first item, prepend it
        if (current == this->_min) {
          i._next = current._p;
          current._p->_prev = &i;
          --this->_min;
        }
        // insert the item
        else {
          current._p->_prev->_next = &i;
          i._prev = current._p->_prev;
          i._next = current._p;
          current._p->_prev = &i;
        }
        return;
      }
      // if all items in the list are smaller, append it
      else if (current == this->_max) {
        this->_max._p->_next = &i;
        i._prev = this->_max._p;
        ++this->_max;
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
typename dlodlist<T>::item* dlodlist<T>::remove_min()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  else if (this->_min == this->_max) {
    item* i(this->_min._p);
    this->_min._p = nullptr;
    this->_max._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the smallest item
  else {
    item* i(this->_min._p);
    ++this->_min;
    this->_min._p->_prev = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
}

template<typename T>
typename dlodlist<T>::item* dlodlist<T>::remove_max()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterators
  if (this->_min == this->_max) {
    item* i(this->_max._p);
    this->_min._p = nullptr;
    this->_max._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the largest item
  else {
    item* i(this->_max._p);
    --this->_max;
    this->_max._p->_next = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
}

template<typename T>
void dlodlist<T>::sort()
{
  // if the list contains less than two items, return immediately
  if (this->_min._p == this->_max._p) {
    return;
  }
  // clear the list, and reinsert all items
  else {
    // initialize temporary iterators and item pointer
    iterator min_tmp(this->_min);
    iterator max_tmp(this->_max);
    item* i(nullptr);

    // reset the list
    this->_min._p = nullptr;
    this->_max._p = nullptr;

    // re-insert all items
    bool abort(false);
    while (!abort) {
      // check if this is the last iteration
      abort = (min_tmp == max_tmp);

      // detach and item and re-insert it in this list
      i = min_tmp._p;
      ++min_tmp;
      i->_prev = nullptr;
      i->_next = nullptr;
      this->insert(*i);
    }

    return;
  }
}

//// DOUBLY LINKED CIRCULAR DLIST //////////////////////////////////////////////

template<typename T>
dlcdlist<T>::dlcdlist() :
  _base_dldlist<CIRCULAR, T>(), _latest()
{}

template<typename T>
inline bool dlcdlist<T>::empty() const
{
  return (this->_latest._p == nullptr);
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
    iterator it(this->_latest);
    do {
      ++it;
      ++cnt;
    } while (it != this->_latest);
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
    iterator it(this->_latest);
    while (true) {
      // test for d
      if (&(it._p->_data) == &d) {
        return true;
      }
      // keep going as long as the end is not reached yet
      else {
        ++it;
        // break the loop when all items have been checked
        if (it == this->_latest) {
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
    iterator current(this->_latest);
    ++current;
    while (true) {
      // test for rm
      if (&(current._p->_data) == &rm) {
        // if the _latest item matches
        if (current == this->_latest) {
          // if the last item will be removed, set all pointer accordingly
          if (this->_latest._p->_next == this->_latest._p) {
            item* i(this->_latest._p);
            this->_latest._p = nullptr;
            return i;
          }
          // decrease the _latest iterator
          else {
            --this->_latest;
          }
        }
        current._p->_prev->_next = current._p->_next;
        current._p->_next->_prev = current._p->_prev;
        current._p->_prev = nullptr;
        current._p->_next = nullptr;
        return current._p;
      }
      // keep going as long as the end is not reached yet
      else if (current != this->_latest) {
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
inline bool dlcdlist<T>::operator ==(const dlcdlist& l) const
{
  return (this->_latest == l._latest);
}

template<typename T>
inline bool dlcdlist<T>::operator !=(const dlcdlist& l) const
{
  return (this->_latest != l._latest);
}

template<typename T>
inline typename dlcdlist<T>::iterator dlcdlist<T>::latest() const
{
  return this->_latest;
}

template<typename T>
inline typename dlcdlist<T>::iterator dlcdlist<T>::eldest() const
{
  iterator it(this->_latest);
  ++it;
  return it;
}

template <typename T>
void dlcdlist<T>::insert(item& i)
{
  assert(!i.attached());

  // if the list is empty, initialize its iterator and the items _prev and _next pointers
  if (this->empty()) {
    this->_latest._p = &i;
    i._prev = &i;
    i._next = &i;
    return;
  }
  // insert the item as the _latest
  else {
    i._prev = this->_latest._p;
    i._next = this->_latest._p->_next;
    this->_latest._p->_next->_prev = &i;
    this->_latest._p->_next = &i;
    ++this->_latest;
    return;
  }
}

template<typename T>
typename dlcdlist<T>::item* dlcdlist<T>::remove_latest()
{
  // if the list is empty, return immediately
  if (this->empty()) {
    return nullptr;
  }
  // if the last item will be removed, invalidate the iterator
  else if (this->_latest._p->_next == this->_latest._p) {
    item* i(this->_latest._p);
    this->_latest._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the latest and decrement the iterator
  else {
    item* i(this->_latest._p);
    --this->_latest;
    this->_latest._p->_next = i->_next;
    this->_latest._p->_next->_prev = this->_latest._p;
    i->_prev = nullptr;
    i->_next = nullptr;
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
  else if (this->_latest._p->_next == this->_latest._p) {
    item* i(this->_latest._p);
    this->_latest._p = nullptr;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
  // remove the eldest
  else {
    item* i(this->_latest._p->_next);
    this->_latest._p->_next = i->_next;
    this->_latest._p->_next->_prev = this->_latest._p;
    i->_prev = nullptr;
    i->_next = nullptr;
    return i;
  }
}

} /* namespace dlist */

#endif /* _DLIST_TPP_ */
