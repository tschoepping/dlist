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

////////////////////////////////////////////////////////////////////////////////
// VERSION INFORMATION                                                        //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Dlist identification macro.
 */
#define _DLIST_

/**
 * @brief   The dlist major version.
 * @note    Changes of the major version imply incompatibilities.
 */
#define DLIST_VERSION_MAJOR   1

/**
 * @brief   The dlist minor version.
 * @note    A higher minor version implies new functionalty, but all old interfaces are still available.
 */
#define DLIST_VERSION_MINOR   0

/**
 * @brief   The periphery abstraction layer interface patch level.
 */
#define DLIST_VERSION_PATCH   0

namespace dlist {

////////////////////////////////////////////////////////////////////////////////
// TEMPLATE ENUMERATORS AND STATIC FUNCTIONS                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Enumerator to differentiate between singly and doubly linked dlists.
 */
enum linked_t {
  SINGLY_LINKED,  /**< Identifier for singly linked dlists. */
  DOUBLY_LINKED,  /**< Identifier for doubly linked dlists. */
};

/**
 * @brief   Enumerator to differentiate between standard, ordered, and circular dlists.
 */
enum property_t {
  NONE,       /**< Identifier for standard dlists. */
  ORDERED,    /**< Identifier for ordered dlists. */
  CIRCULAR,   /**< Identifier for circular dlists. */
};

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS                                                       //
////////////////////////////////////////////////////////////////////////////////

class _slitem;
class _dlitem;
template<typename T> class _item;
template<typename T> class slitem;
template<typename T> class dlitem;
template<typename T> class sliterator;
template<typename T> class dliterator;
template<linked_t LINKED, property_t PROPERTY, typename T> class _dlist;
template<property_t PROPERTY, typename T> class _sldlist;
template<property_t PROPERTY, typename T> class _dldlist;
template<typename T> class sldlist;
template<typename T> class slodlist;
template<typename T> class slcdlist;
template<typename T> class dldlist;
template<typename T> class dlodlist;
template<typename T> class dlcdlist;

////////////////////////////////////////////////////////////////////////////////
// STATIC FUNCTIONS                                                           //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Default compare function for ordered dlists.
 *
 * @tparam T  Argument type of objects to compare.
 *
 * @param[in] a   First object to compare.
 * @param[in] b   Second object to compare.
 *
 * @return    true, if a is smaller than b.
 */
template<typename T> static inline bool _defaultCmp(const T& a, const T& b);

////////////////////////////////////////////////////////////////////////////////
// ITEMS                                                                      //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Base class for dlsit singly linked items.
 */
class _slitem
{
protected:
  /**
   * @brief   Pointer to the next item in the dlist.
   */
  _slitem* m_next;

private:
  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  _slitem(const _slitem&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  _slitem& operator=(const _slitem&);

public:
  /**
   * @brief   The default constructor.
   */
  _slitem();

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @note    The result of the function may be false negative.
   *
   * @return  true, if the item is attached to a dlist.
   *
   * @retval true   The _slitem is attached to a dlist.
   * @retval false  The _slitem is either not attached to a dlist, or is the last item in a non-circular list.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _slitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  virtual bool operator==(const _slitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _slitem to compare.
   *
   * @return    true, if the argument is not identical.
   */
  virtual bool operator!=(const _slitem& i) const;

  /**
   * @brief   Checks whether the given _slitems are identical.
   *
   * @param[in] a   The first _slitem to compare.
   * @param[in] b   The second _slitem to compare.
   *
   * @return    true, if the both _slitems are identical.
   */
  static bool identical(const _slitem& a, const _slitem& b);
};

/**
 * @brief   Base class for dlsit doubly linked items.
 */
class _dlitem
{
protected:
  /**
   * @brief   Pointer to the previous item in the dlist.
   */
  _dlitem* m_prev;

  /**
   * @brief   Pointer to the next item in the dlist.
   */
  _dlitem* m_next;

private:
  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  _dlitem(const _dlitem&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  _dlitem& operator=(const _dlitem&);

public:
  /**
   * @brief   The default constructor.
   */
  _dlitem();

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @return  true, if the item is attached to a dlist.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _dlitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  virtual bool operator==(const _dlitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _dlitem to compare.
   *
   * @return    true, if the argument is not identical.
   */
  virtual bool operator!=(const _dlitem& i) const;

  /**
   * @brief   Checks whether the given _dlitems are identical.
   *
   * @param[in] a   The first _dlitem to compare.
   * @param[in] b   The second _dlitem to compare.
   *
   * @return    true, if the both _dlitems are identical.
   */
  static bool identical(const _dlitem& a, const _dlitem& b);
};

/**
 * @brief   Base class for dlist items.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class _item
{
protected:
  /**
   * @brief   Content/payload of the item.
   */
  T& m_data;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  _item();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  _item(const _item&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  _item& operator=(const _item&);

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the _item.
   */
  _item(T& d);

  /**
   * @brief   Indirection operator.
   *
   * @return  Reference to the content/payload.
   */
  T& operator*();

  /**
   * @brief   Dereference operator.
   *
   * @return  Pointer to the content/payload.
   */
  T* operator->();

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is identical.
   */
  virtual bool operator==(const _item& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is not identical.
   */
  virtual bool operator!=(const _item& i) const;

  /**
   * @brief   Checks whether the given _items are identical.
   *
   * @param[in] a   The first _item to compare.
   * @param[in] b   The second _item to compare.
   *
   * @return    true, if the both _items are identical.
   */
  static bool identical(const _item& a, const _item& b);

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
class slitem : public _slitem, public _item<T>
{
friend class sliterator<T>;
friend class sldlist<T>;
friend class slodlist<T>;
friend class slcdlist<T>;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  slitem();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  slitem(const slitem&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  slitem& operator=(const slitem&);

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the slitem.
   */
  slitem(T& d);

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @note    The result of the function may be false negative.
   *
   * @return  true, if the item is attached to a dlist.
   *
   * @retval true   The slitem is attached to a dlist.
   * @retval false  The slitem is either not attached to a dlist, or is the last item in a non-circular list.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _slitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const _slitem& i) const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const _item<T>& i) const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The slitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const slitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _slitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator!=(const _slitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator!=(const _item<T>& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The slitem to compare.
   *
   * @return    true, if the argument is not identical.
   */
  bool operator!=(const slitem& i) const;

  /**
   * @brief   Checks whether the given slitems are identical.
   *
   * @param[in] a   The first slitem to compare.
   * @param[in] b   The second slitem to compare.
   *
   * @return    true, if the both slitems are identical.
   */
  static bool identical(const slitem& a, const slitem& b);
};

/**
 * @brief   Doubly linked dlsit item class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class dlitem : public _dlitem, public _item<T>
{
friend class dliterator<T>;
friend class dldlist<T>;
friend class dlodlist<T>;
friend class dlcdlist<T>;

private:
  /**
   * @brief   The default constructor is prohibited and must not be implemented.
   */
  dlitem();

  /**
   * @brief   The copy constructor is prohibited and must not be implemented.
   */
  dlitem(const dlitem&);

  /**
   * @brief   The copy operator is prohibited and must not be implemented.
   */
  dlitem& operator=(const dlitem&);

public:
  /**
   * @brief   The only constructor with payload as argument.
   *
   * @param[in] d   The payload to set for the dlitem.
   */
  dlitem(T& d);

  /**
   * @brief   Checks whether the item is attached to a dlist.
   *
   * @return  true, if the item is attached to a dlist.
   */
  bool attached() const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _dlitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const _dlitem& i) const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const _item<T>& i) const;

  /**
   * @brief   Equality operator.
   *
   * @param[in] i   The dlitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator==(const dlitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _dlitem to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator!=(const _dlitem& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The _item to compare.
   *
   * @return    true, if the argument is identical.
   */
  bool operator!=(const _item<T>& i) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] i   The dlitem to compare.
   *
   * @return    true, if the argument is not identical.
   */
  bool operator!=(const dlitem& i) const;

  /**
   * @brief   Checks whether the given dlitems are identical.
   *
   * @param[in] a   The first dlitem to compare.
   * @param[in] b   The second dlitem to compare.
   *
   * @return    true, if the both dlitems are identical.
   */
  static bool identical(const dlitem& a, const dlitem& b);
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
class sliterator : public std::iterator<std::forward_iterator_tag, slitem<T>, size_t>
{
friend class sldlist<T>;
friend class slodlist<T>;
friend class slcdlist<T>;

public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef slitem<T> item;

private:
  /**
   * @brief   Pointer to the associated slitem or a nullpointer.
   */
  item* m_item;

public:
  /**
   * @brief   Default constructor.
   */
  sliterator();

  /**
   * @brief   Copy constructor.
   *
   * @param[in] it  Iterator to be copied.
   */
  sliterator(const sliterator& it);

  /**
   * @brief   Copy operator.
   *
   * @param[in] it  Iterator to be copied.
   *
   * @return  Reference to the resulting iterator.
   */
  sliterator& operator=(const sliterator& it);

  /**
   * @brief   Equality operator.
   *
   * @param[in] it  The sliterator to compare.
   *
   * @return    true, if the sliterators are equal.
   */
  bool operator==(const sliterator& it) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] it  The sliterator to sompare.
   *
   * @return    true, if the sliterators are not equal.
   */
  bool operator!=(const sliterator& it) const;

  /**
   * @brief   Increment operator.
   * @details The pointer to the associated item m_item is altered to point to the next item in the dlist.
   *          If there is no next item in the list, m_item will become a nullpointer.
   *          If m_item is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  sliterator& operator++();

  /**
   * @brief   Indirection operator.
   *
   * @note    Function call will fail if no item is associated to the sliterator.
   *
   * @return  Refeerence to the payload of the associated slitem.
   */
  T& operator*();

  /**
   * @brief   Dereference iterator.
   *
   * @return  Pointer to the the payload of the associated slitem or a nullpointer of no item is associated.
   */
  T* operator->();

  /**
   * @brief   Peeks an arbitrary number of steps ahead in the dlist.
   *
   * @details If no slitem is associated to the sliterator, or the slitem is not attached, or the given arguments exceeds the list, a nullpointer is returned.
   *
   * @param[in] n   Number of steps to peek ahead.
   *
   * @return  Pointer to the payload of the according slitem or a nullpointer.
   */
  T* peek(const unsigned int n = 1) const;

  /**
   * @brief   Checks whether the iterator is pointing to an item.
   *
   * @note    Alternatively the peek() function can be used with argument 0.
   *
   * @return  true, if an item is associated to the iterator.
   */
  bool valid() const;
};

/**
 * @brief   Doubly linked dlist iterator class.
 *
 * @tparam T  Data type of content/payload.
 */
template<typename T>
class dliterator : public std::iterator<std::bidirectional_iterator_tag, dlitem<T>, size_t>
{
friend class dldlist<T>;
friend class dlodlist<T>;
friend class dlcdlist<T>;

public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef dlitem<T> item;

private:
  /**
   * @brief   Pointer to the associated dlitem or a nullpointer.
   */
  item* m_item;

public:
  /**
   * @brief   Default constructor.
   */
  dliterator();

  /**
   * @brief   Copy constructor.
   *
   * @param[in] it  Iterator to be copied.
   */
  dliterator(const dliterator& it);

  /**
   * @brief   Copy operator.
   *
   * @param[in] it  Iterator to be copied.
   *
   * @return  Reference to the resulting iterator.
   */
  dliterator& operator=(const dliterator& it);

  /**
   * @brief   Equality operator.
   *
   * @param[in] it  The dliterator to compare.
   *
   * @return    true, if the dliterators are equal.
   */
  bool operator==(const dliterator& it) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] it  The dliterator to sompare.
   *
   * @return    true, if the dliterators are not equal.
   */
  bool operator!=(const dliterator& it) const;

  /**
   * @brief   Increment operator.
   * @details The pointer to the associated item m_item is altered to point to the next item in the dlist.
   *          If there is no next item in the list, m_item will become a nullpointer.
   *          If m_item is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  dliterator& operator++();

  /**
   * @brief   Decrement operator.
   * @details The pointer to the associated item m_item is altered to point to the previous item in the dlist.
   *          If there is no previous item in the list, m_item will become a nullpointer.
   *          If m_item is a nullpointer, the iterator will remain unchainged.
   *
   * @return  Reference to the resulting iterator.
   */
  dliterator& operator--();

  /**
   * @brief   Indirection operator.
   *
   * @note    Function call will fail if no item is associated to the dliterator.
   *
   * @return  Refeerence to the payload of the associated dlitem.
   */
  T& operator*();

  /**
   * @brief   Dereference iterator.
   *
   * @return  Pointer to the the payload of the associated dlitem or a nullpointer of no item is associated.
   */
  T* operator->();

  /**
   * @brief   Peeks an arbitrary number of steps ahead/behind in the dlist.
   *
   * @details If no dlitem is associated to the dliterator, or the dlitem is not attached, or the given arguments exceeds the list, a nullpointer is returned.
   *
   * @param[in] n   Number of steps to peek ahead (positive) or behind (negative).
   *
   * @return  Pointer to the payload of the according dlitem or a nullpointer.
   */
  T* peek(const int n = 1) const;

  /**
   * @brief   Checks whether the iterator is pointing to an item.
   *
   * @note    Alternatively the peek() function can be used with argument 0.
   *
   * @return  true, if an item is associated to the iterator.
   */
  bool valid() const;
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
class _dlist
{
public:
  /**
   * @brief   Default constructor.
   */
  _dlist();

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
class _sldlist : public _dlist<SINGLY_LINKED, PROPERTY, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef slitem<T> item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef sliterator<T> iterator;

public:
  /**
   * @brief   Default constructor.
   */
  _sldlist();

  /**
   * @brief   Removes a specific object from the list.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed slitem or a nullpointer if the list does not contain the specified object.
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
class _dldlist : public _dlist<DOUBLY_LINKED, PROPERTY, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef dlitem<T> item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef dliterator<T> iterator;

public:
  /**
   * @brief   Default constructor.
   */
  _dldlist();

  /**
   * @brief   Removes a specific object from the list.
   *
   * @param[in] rm  The payload object to remove.
   *
   * @return  Pointer to the removed dlitem or a nullpointer if the list does not contain the specified object.
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
class sldlist : public _sldlist<NONE, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _sldlist<NONE, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _sldlist<NONE, T>::iterator iterator;

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
  bool operator==(const sldlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const sldlist& l) const;

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
class slodlist : public _sldlist<ORDERED, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _sldlist<ORDERED, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _sldlist<ORDERED, T>::iterator iterator;

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
  iterator m_min;

  /**
   * @brief   Iterator pointing to the maximum item in the slodlist.
   */
  iterator m_max;

  /**
   * @brief   Reference to a compare function.
   */
  const cmp_f& m_cmp;

public:
  /**
   * @brief   Standard constructor.
   *
   * @param[in] cmp   Reference to a compare function.
   */
  slodlist(cmp_f& cmp = _defaultCmp);

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
  bool operator==(const slodlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const slodlist& l) const;

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
  item* removeMin();

  /**
   * @brief   Removes the maximum item from the slodlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the slodlist was empty.
   */
  item* removeMax();

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
class slcdlist : public _sldlist<CIRCULAR, T>
{
public:
  /**
   * @brief   Alias for singly linked dlist item type with according payload type.
   */
  typedef typename _sldlist<CIRCULAR, T>::item item;

  /**
   * @brief   Alias for singly linked dlist iterator type with according payload type.
   */
  typedef typename _sldlist<CIRCULAR, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the most recently inserted item in the slcdlist.
   */
  iterator m_latest;

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
  bool operator==(const slcdlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const slcdlist& l) const;

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
  item* removeLatest();

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
class dldlist : public _dldlist<NONE, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _dldlist<NONE, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _dldlist<NONE, T>::iterator iterator;

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
  bool operator==(const dldlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const dldlist& l) const;

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
class dlodlist : public _dldlist<ORDERED, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _dldlist<ORDERED, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _dldlist<ORDERED, T>::iterator iterator;

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
  iterator m_min;

  /**
   * @brief   Iterator pointing to the maximum item in the dlodlist.
   */
  iterator m_max;

  /**
   * @brief   Reference to a compare function.
   */
  const cmp_f& m_cmp;

public:
  /**
   * @brief   Standard constructor.
   *
   * @param[in] cmp   Reference to a compare function.
   */
  dlodlist(cmp_f& cmp = _defaultCmp);

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
  bool operator==(const dlodlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const dlodlist& l) const;

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
  item* removeMin();

  /**
   * @brief   Removes the maximum item from the dlodlist
   *
   * @return  Pointer to the removed item, or a nullpointer if the dlodlist was empty.
   */
  item* removeMax();

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
class dlcdlist : public _dldlist<CIRCULAR, T>
{
public:
  /**
   * @brief   Alias for doubly linked dlist item type with according payload type.
   */
  typedef typename _dldlist<CIRCULAR, T>::item item;

  /**
   * @brief   Alias for doubly linked dlist iterator type with according payload type.
   */
  typedef typename _dldlist<CIRCULAR, T>::iterator iterator;

private:
  /**
   * @brief   Iterator pointing to the most recently inserted item in the dlcdlist.
   */
  iterator m_latest;

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
  bool operator==(const dlcdlist& l) const;

  /**
   * @brief   Unequality operator.
   *
   * @param[in] l   List to compare.
   *
   * @return  true, if both lists are not equal.
   */
  bool operator!=(const dlcdlist& l) const;

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
  item* removeLatest();

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
