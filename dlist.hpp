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

#ifndef _DLIST_HPP_
#define _DLIST_HPP_

#include <iterator>
#include <cstddef>

namespace dlist {

////////////////////////////////////////////////////////////////////////////////
// TEMPLATE ENUMERATORS AND STATIC FUNCTIONS                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Enum to differentiate between singly and doubly linked dlists.
 */
enum linked_t {
  SINGLY_LINKED,  /**< Identifier for singly linked dlists. */
  DOUBLY_LINKED,  /**< Identifier for doubly linked dlists. */
};

/**
 * @brief   Enum to differentiate between standard, ordered and circular dlists.
 */
enum property_t {
  NONE,       /**< Identifier for standard dlists. */
  ORDERED,    /**< Identifier for ordered dlists. */
  CIRCULAR,   /**< Identifier for circular dlists. */
};

/**
 * @brief   Default compare function for ordered dlists.
 *
 * @tparam T  Argument type or objects to compare.
 *
 * @param[in] a   First argument to compare.
 * @param[in] b   Second argument to compare.
 *
 * @return    true, if a is smaller than b.
 */
template<typename T>
static inline bool default_cmp(const T& a, const T& b)
{
  return (a < b);
}

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS                                                       //
////////////////////////////////////////////////////////////////////////////////

template<typename T> class _base_item;
template<typename T> class sl_item;
template<typename T> class dl_item;
template<typename T> class sl_iterator;
template<typename T> class dl_iterator;
template<linked_t LINKED, property_t PROPERTY, typename T> class _base_dlist;
template<property_t PROPERTY, typename T> class _base_sldlist;
template<property_t PROPERTY, typename T> class _base_dldlist;
template<typename T> class sldlist;
template<typename T> class slodlist;
template<typename T> class slcdlist;
template<typename T> class dldlist;
template<typename T> class dlodlist;
template<typename T> class dlcdlist;

////////////////////////////////////////////////////////////////////////////////
// ITEMS                                                                      //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Base class for dlist items.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class _base_item
{
protected:
  /**
   * @brief   Content/payload of the item.
   */
  T& _data;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  _base_item();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  _base_item(const _base_item&); // forbidden

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  _base_item& operator=(const _base_item&); // forbidden

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the _base_item.
   */
  _base_item(T& d);

  /**
   * @brief   Indirection operator.
   *
   * @return  Reference to the content/payload.
   */
  T& operator *();

  /**
   * @brief   Dereference operator.
   *
   * @return  Pointer to the content/payload.
   */
  T* operator ->();

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @return  true, if the item is attached to a dlist.
   */
  virtual bool attached() const = 0;
};

/**
 * @brief   Singly linked dlist item class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class sl_item : public _base_item<T>
{
  friend class sl_iterator<T>;
  friend class sldlist<T>;
  friend class slodlist<T>;
  friend class slcdlist<T>;

private:
  /**
   * @brief   Pointer to the next item in the dlist.
   */
  sl_item* _next;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  sl_item();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  sl_item(const sl_item&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  sl_item& operator=(const sl_item&);

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the sl_item.
   */
  sl_item(T& d);

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @note    The result of the function may be false negative.
   *
   * @return  true, if the item is attached to a dlist.
   *
   * @retval true   The sl_item is attached to a dlist.
   * @retval false  The sl_item is either not attached to a dlist, or is the last item in a non-circular list.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The sl_item to compare.
   *
   * @return    true, if the sl_items are identical.
   */
  bool operator ==(const sl_item& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The sl_item to compare.
   *
   * @return    true, if the sl_items are not identical.
   */
  bool operator !=(const sl_item& i) const;

  /**
   * @brief   Checks whether the given sl_items are identical.
   *
   * @param[in] a   The first sl_item to compare.
   * @param[in] b   The second sl_item to compare.
   *
   * @return    true, if the both sl_items are identical.
   */
  static bool identical(const sl_item& a, const sl_item& b);
};

/**
 * @brief   Doubly linked dlsit item class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class dl_item : public _base_item<T>
{
  friend class dl_iterator<T>;
  friend class dldlist<T>;
  friend class dlodlist<T>;
  friend class dlcdlist<T>;

private:
  /**
   * @brief   Pointer to the next item in the dlist.
   */
  dl_item* _prev;

  /**
   * @brief   Pointer to the previous item in the dlist.
   */
  dl_item* _next;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  dl_item();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  dl_item(const dl_item&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  dl_item& operator=(const dl_item&);

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the dl_item.
   */
  dl_item(T& d);

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @return  true, if the item is attached to a dlist.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The dl_item to compare.
   *
   * @return    true, if the dl_items are identical.
   */
  bool operator ==(const dl_item& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The dl_item to compare.
   *
   * @return    true, if the dl_items are not identical.
   */
  bool operator !=(const dl_item& i) const;

  /**
   * @brief   Checks whether the given dl_items are identical.
   *
   * @param[in] a   The first dl_item to compare.
   * @param[in] b   The second dl_item to compare.
   *
   * @return    true, if the both dl_items are identical.
   */
  static bool identical(const dl_item& a, const dl_item& b);
};

////////////////////////////////////////////////////////////////////////////////
// ITERATORS                                                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Singly linked dlist iterator class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class sl_iterator : public std::iterator<std::forward_iterator_tag, sl_item<T>, size_t>
{
  friend class sldlist<T>;
  friend class slodlist<T>;
  friend class slcdlist<T>;

public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef sl_item<T> item_t;

private:
  /**
   * @brief   Pointer to the associated sl_item or a nullpointer.
   */
  item_t* _p;

public:
  /**
   * @brief   Default constructor.
   */
  sl_iterator();

  /**
   * @brief   Copy constructor.
   *
   * @param[in] it  Iterator to be copied.
   */
  sl_iterator(const sl_iterator& it);

  /**
   * @brief   Copy operator.
   *
   * @param[in] it  Iterator to be copied.
   *
   * @return  Reference to the resulting iterator.
   */
  sl_iterator& operator =(const sl_iterator& it);

  /**
   * @brief   Equality operator.
   *
   * @param[in] it  The sl_iterator to compare.
   *
   * @return    true, if the sl_iterators are equal.
   */
  bool operator ==(const sl_iterator& it) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] it  The sl_iterator to sompare.
   *
   * @return    true, if the sl_iterators are not equal.
   */
  bool operator !=(const sl_iterator& it) const;

  /**
   * @brief   Increment operator.
   * @details The pointer to the associated item _p is altered to point to the next item in the dlist.
   *          If there is no next item in the list, _p will become a nullpointer.
   *          If _p is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  sl_iterator& operator ++();

  /**
   * @brief   Indirection operator.
   *
   * @note    Function call will fail if no item is associated to the sl_iterator.
   *
   * @return  Refeerence to the payload of the associated sl_item.
   */
  T& operator *();

  /**
   * @brief   Dereference iterator.
   *
   * @return  Pointer to the the payload of the associated sl_item or a nullpointer of no item is associated.
   */
  T* operator ->();

  /**
   * @brief   Peeks an arbitrary number of steps ahead in the dlist.
   *
   * @details If no sl_item is associated to the sl_iterator, or the sl_item is not attached, or the given arguments exceeds the list, a nullpointer is returned.
   *
   * @param[in] n   Number of steps to peek ahead.
   *
   * @return  Pointer to the payload of the according sl_item or a nullpointer.
   */
  T* peek(const unsigned int n = 1) const;

  /**
   * @brief   Retrieves the pointer to the associated item.
   *
   * @return  Constant pointer to the associated item or a nullpointer.
   */
  const item_t* item() const;
};

/**
 * @brief   Doubly linked dlist iterator class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class dl_iterator : public std::iterator<std::bidirectional_iterator_tag, dl_item<T>, size_t>
{
  friend class dldlist<T>;
  friend class dlodlist<T>;
  friend class dlcdlist<T>;

public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef dl_item<T> item_t;

private:
  /**
   * @brief   Pointer to the associated dl_item or a nullpointer.
   */
  item_t* _p;

public:
  /**
   * @brief   Default constructor.
   */
  dl_iterator();

  /**
   * @brief   Copy constructor.
   *
   * @param[in] it  Iterator to be copied.
   */
  dl_iterator(const dl_iterator& it);

  /**
   * @brief   Copy operator.
   *
   * @param[in] it  Iterator to be copied.
   *
   * @return  Reference to the resulting iterator.
   */
  dl_iterator& operator =(const dl_iterator& it);

  /**
   * @brief   Equality operator.
   *
   * @param[in] it  The dl_iterator to compare.
   *
   * @return    true, if the dl_iterators are equal.
   */
  bool operator ==(const dl_iterator& it) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] it  The dl_iterator to sompare.
   *
   * @return    true, if the dl_iterators are not equal.
   */
  bool operator !=(const dl_iterator& it) const;

  /**
   * @brief   Increment operator.
   * @details The pointer to the associated item _p is altered to point to the next item in the dlist.
   *          If there is no next item in the list, _p will become a nullpointer.
   *          If _p is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  dl_iterator& operator ++();

  /**
   * @brief   Decrement operator.
   * @details The pointer to the associated item _p is altered to point to the previous item in the dlist.
   *          If there is no previous item in the list, _p will become a nullpointer.
   *          If _p is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  dl_iterator& operator --();

  /**
   * @brief   Indirection operator.
   *
   * @note    Function call will fail if no item is associated to the dl_iterator.
   *
   * @return  Refeerence to the payload of the associated dl_item.
   */
  T& operator *();

  /**
   * @brief   Dereference iterator.
   *
   * @return  Pointer to the the payload of the associated dl_item or a nullpointer of no item is associated.
   */
  T* operator ->();

  /**
   * @brief   Peeks an arbitrary number of steps ahead/behind in the dlist.
   *
   * @details If no dl_item is associated to the dl_iterator, or the dl_item is not attached, or the given arguments exceeds the list, a nullpointer is returned.
   *
   * @param[in] n   Number of steps to peek ahead (positive) or behind (negative).
   *
   * @return  Pointer to the payload of the according dl_item or a nullpointer.
   */
  T* peek(const int n = 1) const;
  const item_t* item() const;
};

////////////////////////////////////////////////////////////////////////////////
// BASE DLIST CLASSES                                                         //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Abstract dlist base class.
 *
 * @tparam LINKED     Type of linkage of the items of the dlist.
 *                    Possible values are SINGLY_LINKED and DOUBLY_LINKED.
 * @tparam PROPERTY   Characteristic of the dlist.
 *                    Possible values are NONE, ORDERED, and CIRCULAR.
 * @tparam T          Type of the data stored in the dlist.
 */
template<linked_t LINKED, property_t PROPERTY, typename T>
class _base_dlist
{
public:
  /**
   * @brief   Default constructor.
   */
  _base_dlist();

  /**
   * @brief   Checks whether the dlist is empty.
   *
   * @return  true, if the dlist contains no items.
   */
  virtual bool empty() const = 0;

  /**
   * @brief   Retrieves the size of the dlist.
   *
   * @return  Number of items in the dlist.
   */
  virtual size_t size() const = 0;

  /**
   * @brief   Checks whether the dlist contains the specified item.
   *
   * @return  true, if the specified item is part of the dlist.
   */
  virtual bool contains(const T&) const = 0;

  /**
   * @brief   Removes all items from the dlist.
   *
   * @return  The number of removed items.
   */
  virtual size_t clear() = 0;
};

/**
 * @brief   Abstract singly linked dlist base class.
 *
 * @tparam PROPERTY   Characteristic of the dlist.
 *                    Possible values are NONE, ORDERED, and CIRCULAR.
 * @tparam T          Type of the data stored in the dlist.
 */
template<property_t PROPERTY, typename T>
class _base_sldlist : public _base_dlist<SINGLY_LINKED, PROPERTY, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef sl_item<T> item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef sl_iterator<T> iterator;

public:
  /**
   * @brief   Default constructor.
   */
  _base_sldlist();

  /**
   * @brief   Removes a specific object from the list.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed sl_item or a nullpointer if the list does not contain the specified object.
   */
  virtual item* remove(const T& rm) = 0;
};

/**
 * @brief   Abstract doubly linked dlist base class.
 *
 * @tparam PROPERTY   Characteristic of the dlist.
 *                    Possible values are NONE, ORDERED, and CIRCULAR.
 * @tparam T          Type of the data stored in the dlist.
 */
template<property_t PROPERTY, typename T>
class _base_dldlist : public _base_dlist<DOUBLY_LINKED, PROPERTY, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef dl_item<T> item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef dl_iterator<T> iterator;

public:
  /**
   * @brief   Default constructor.
   */
  _base_dldlist();

  /**
   * @brief   Removes a specific object from the list.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed dl_item or a nullpointer if the list does not contain the specified object.
   */
  virtual item* remove(const T& rm) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// SINGLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Standard singly linked dlist class.
 *
 * @tparam T  Type of the data stored in the sldlist.
 */
template<typename T>
class sldlist : public _base_sldlist<NONE, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _base_sldlist<NONE, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _base_sldlist<NONE, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the first item in the sldlist.
   */
  iterator _first;

  /**
   * @brief   Iterator pointing to the last item in the sldlist.
   */
  iterator _last;

public:
  /**
   * @brief   Default constructor.
   */
  sldlist();

  /**
   * @brief   Checks whether the sldlist is empty.
   *
   * @return  true, if the sldlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the sldlist.
   *
   * @return  Number of items in the sldlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the sldlist contains the specified item.
   *
   * @return  true, if the specified item is part of the sldlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the sldlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the sldlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const sldlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const sldlist& l) const;

  /**
   * @brief   Retrieves an iterator to the first element in the sldlist.
   *
   * @return  Iterator pointing to the first element in the sldlist.
   */
  iterator front() const;

  /**
   * @brief   Retrieves an iterator to the last element in the sldlist.
   *
   * @return  Iterator pointing to the last element in the sldlist.
   */
  iterator back() const;

  /**
   * @brief   Appends an item at the front of the sldlist.
   *
   * @param[in] i   The item to append.
   */
  void push_front(item& i);

  /**
   * @brief   Appends an item at the back of the sldlist.
   *
   * @param[in] i   The item to append.
   */
  void push_back(item& i);

  /**
   * @brief   Removes the first item from the sldlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the sldlist was empty.
   */
  item* pop_front();

  /**
   * @brief   Removes the last item from the sldlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the sldlist was empty.
   */
  item* pop_back();
};

/**
 * @brief   Singly linked ordered dlist class.
 *
 * @details   Items are ordered from the smallest to the largest.
 *
 * @tparam T  Type of the data stored in the slodlist.
 */
template<typename T>
class slodlist : public _base_sldlist<ORDERED, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _base_sldlist<ORDERED, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _base_sldlist<ORDERED, T>::iterator iterator;

  /**
   * @brief   Alias for compare function.
   *
   * @details The compare function takes two objects as arguments and returns a bool.
   *          By definition, the function shall return true if the first argumend is considered smaller than the second argument.
   */
  typedef bool (cmp_f)(const T&, const T&);

private:
  /**
   * @brief   Iterator pointing to the minimum item in the slodlist.
   */
  iterator _min;

  /**
   * @brief   Iterator pointing to the maximum item in the slodlist.
   */
  iterator _max;

  /**
   * @brief   Reference to a compare function.
   */
  const cmp_f& _cmp;

public:
  /**
   * @brief   Standard constructor.
   *
   * @param[in] cmp   Reference to a compare function.
   */
  slodlist(cmp_f& cmp = default_cmp);

  /**
   * @brief   Checks whether the slodlist is empty.
   *
   * @return  true, if the slodlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the slodlist.
   *
   * @return  Number of items in the slodlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the slodlist contains the specified item.
   *
   * @return  true, if the specified item is part of the slodlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the slodlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the slodlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const slodlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const slodlist& l) const;

  /**
   * @brief   Retrieves an iterator to the minimum element in the slodlist.
   *
   * @return  Iterator pointing to the minimum element in the slodlist.
   */
  iterator min() const;

  /**
   * @brief   Retrieves an iterator to the maximum element in the slodlist.
   *
   * @return  Iterator pointing to the maximum element in the slodlist.
   */
  iterator max() const;

  /**
   * @brief   Inserts the specified item in the slodlist.
   *
   * @param[in] i   The item to be insterted.
   */
  void insert(item& i);

  /**
   * @brief   Removes the minimum item from the slodlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the slodlist was empty.
   */
  item* remove_min();

  /**
   * @brief   Removes the maximum item from the slodlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the slodlist was empty.
   */
  item* remove_max();

  /**
   * @brief   Sorts all items in the list in case some values have been modified.
   */
  void sort();
};

/**
 * @brief   Singly linked circular dlist class.
 *
 * @tparam T  Type of the data stored in the slcdlist.
 */
template<typename T>
class slcdlist : public _base_sldlist<CIRCULAR, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _base_sldlist<CIRCULAR, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _base_sldlist<CIRCULAR, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the most recently inserted item in the slcdlist.
   */
  iterator _latest;

public:
  /**
   * @brief   Default constructor.
   */
  slcdlist();

  /**
   * @brief   Checks whether the slcdlist is empty.
   *
   * @return  true, if the slcdlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the slcdlist.
   *
   * @return  Number of items in the slcdlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the slcdlist contains the specified item.
   *
   * @return  true, if the specified item is part of the slcdlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the slcdlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the slcdlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const slcdlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const slcdlist& l) const;

  /**
   * @brief   Retrieves an iterator to the latest element in the slcdlist.
   *
   * @return  Iterator pointing to the most recently added element in the slcdlist.
   */
  iterator latest() const;

  /**
   * @brief   Retrieves an iterator to the eldest element in the slcdlist.
   *
   * @return  Iterator pointing to the oldest element in the slcdlist.
   */
  iterator eldest() const;

  /**
   * @brief   Inserts the specified item in the slcdlist.
   *
   * @param[in] i   The item to be insterted.
   */
  void insert(item& i);

  /**
   * @brief   Removes the latest item from the slcdlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the slcdlist was empty.
   */
  item* remove_latest();

  /**
   * @brief   Removes the oldest item from the slcdlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the slcdlist was empty.
   */
  item* remove_eldest();
};

////////////////////////////////////////////////////////////////////////////////
// DOUBLY LINKED DLIST CLASSES                                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Standard doubly linked dlist class.
 *
 * @tparam T  Type of the data stored in the dldlist.
 */
template<typename T>
class dldlist : public _base_dldlist<NONE, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _base_dldlist<NONE, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _base_dldlist<NONE, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the first item in the dldlist.
   */
  iterator _first;

  /**
   * @brief   Iterator pointing to the last item in the dldlist.
   */
  iterator _last;

public:
  /**
   * @brief   Default constructor.
   */
  dldlist();

  /**
   * @brief   Checks whether the dldlist is empty.
   *
   * @return  true, if the dldlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the dldlist.
   *
   * @return  Number of items in the dldlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the dldlist contains the specified item.
   *
   * @return  true, if the specified item is part of the dldlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the dldlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the dldlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const dldlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const dldlist& l) const;

  /**
   * @brief   Retrieves an iterator to the first element in the dldlist.
   *
   * @return  Iterator pointing to the first element in the dldlist.
   */
  iterator front() const;

  /**
   * @brief   Retrieves an iterator to the last element in the dldlist.
   *
   * @return  Iterator pointing to the last element in the dldlist.
   */
  iterator back() const;

  /**
   * @brief   Appends an item at the front of the dldlist.
   *
   * @param[in] i   The item to append.
   */
  void push_front(item& i);

  /**
   * @brief   Appends an item at the back of the dldlist.
   *
   * @param[in] i   The item to append.
   */
  void push_back(item& i);

  /**
   * @brief   Removes the first item from the dldlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the dldlist was empty.
   */
  item* pop_front();

  /**
   * @brief   Removes the last item from the dldlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the dldlist was empty.
   */
  item* pop_back();
};

/**
 * @brief   Doubly linked ordered dlist class.
 *
 * @details   Items are ordered from the smallest to the largest.
 *
 * @tparam T  Type of the data stored in the dlodlist.
 */
template<typename T>
class dlodlist : public _base_dldlist<ORDERED, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _base_dldlist<ORDERED, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _base_dldlist<ORDERED, T>::iterator iterator;

  /**
   * @brief   Alias for compare function.
   *
   * @details The compare function takes two objects as arguments and returns a bool.
   *          By definition, the function shall return true if the first argumend is considered smaller than the second argument.
   */
  typedef bool (cmp_f)(const T&, const T&);

private:
  /**
   * @brief   Iterator pointing to the minimum item in the dlodlist.
   */
  iterator _min;

  /**
   * @brief   Iterator pointing to the maximum item in the dlodlist.
   */
  iterator _max;

  /**
   * @brief   Reference to a compare function.
   */
  const cmp_f& _cmp;

public:
  /**
   * @brief   Standard constructor.
   *
   * @param[in] cmp   Reference to a compare function.
   */
  dlodlist(cmp_f& cmp = default_cmp);

  /**
   * @brief   Checks whether the dlodlist is empty.
   *
   * @return  true, if the dlodlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the dlodlist.
   *
   * @return  Number of items in the dlodlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the dlodlist contains the specified item.
   *
   * @return  true, if the specified item is part of the dlodlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the dlodlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the dlodlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const dlodlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const dlodlist& l) const;

  /**
   * @brief   Retrieves an iterator to the minimum element in the dlodlist.
   *
   * @return  Iterator pointing to the minimum element in the dlodlist.
   */
  iterator min() const;

  /**
   * @brief   Retrieves an iterator to the maximum element in the dlodlist.
   *
   * @return  Iterator pointing to the maximum element in the dlodlist.
   */
  iterator max() const;

  /**
   * @brief   Inserts the specified item in the dlodlist.
   *
   * @param[in] i   The item to be insterted.
   */
  void insert(item& i);

  /**
   * @brief   Removes the minimum item from the dlodlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the dlodlist was empty.
   */
  item* remove_min();

  /**
   * @brief   Removes the maximum item from the dlodlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the dlodlist was empty.
   */
  item* remove_max();

  /**
   * @brief   Sorts all items in the list in case some values have been modified.
   */
  void sort();
};

/**
 * @brief   Doubly linked circular dlist class.
 *
 * @tparam T  Type of the data stored in the dlcdlist.
 */
template<typename T>
class dlcdlist : public _base_dldlist<CIRCULAR, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _base_dldlist<CIRCULAR, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _base_dldlist<CIRCULAR, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the most recently inserted item in the dlcdlist.
   */
  iterator _latest;

public:
  /**
   * @brief   Default constructor.
   */
  dlcdlist();

  /**
   * @brief   Checks whether the dlcdlist is empty.
   *
   * @return  true, if the dlcdlist contains no items.
   */
  bool empty() const;

  /**
   * @brief   Retrieves the size of the dlcdlist.
   *
   * @return  Number of items in the dlcdlist.
   */
  size_t size() const;

  /**
   * @brief   Checks whether the dlcdlist contains the specified item.
   *
   * @return  true, if the specified item is part of the dlcdlist.
   */
  bool contains(const T& d) const;

  /**
   * @brief   Removes all items from the dlcdlist.
   *
   * @return  The number of removed items.
   */
  size_t clear();

  /**
   * @brief   Removes a specific object from the dlcdlist.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed item or a nullpointer if the list does not contain the specified object.
   */
  item* remove(const T &rm);

  /**
   * @brief   Equality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are equal.
   */
  bool operator ==(const dlcdlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator !=(const dlcdlist& l) const;

  /**
   * @brief   Retrieves an iterator to the latest element in the dlcdlist.
   *
   * @return  Iterator pointing to the most recently added element in the dlcdlist.
   */
  iterator latest() const;

  /**
   * @brief   Retrieves an iterator to the eldest element in the dlcdlist.
   *
   * @return  Iterator pointing to the oldest element in the dlcdlist.
   */
  iterator eldest() const;

  /**
   * @brief   Inserts the specified item in the dlcdlist.
   *
   * @param[in] i   The item to be insterted.
   */
  void insert(item& i);

  /**
   * @brief   Removes the latest item from the dlcdlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the dlcdlist was empty.
   */
  item* remove_latest();

  /**
   * @brief   Removes the oldest item from the dlcdlist.
   *
   * @return  Pointer to the removed item, or a nullpointer if the dlcdlist was empty.
   */
  item* remove_eldest();
};

} /* namespace dlist */

#include "dlist.tpp"

#endif /* _DLIST_HPP_ */
