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

#include <iostream>

#include <dlist.hpp>

using namespace std;
using namespace dlist;

bool my_cmp(const uint32_t& a, const uint32_t& b) {
  return (a < b);
}

void slitem_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  slitem<uint32_t> item_a(data_a);
  slitem<uint32_t> item_b(data_b);
  slitem<uint32_t> item_c(data_c);

  _item<uint32_t>* _item_a(&item_a);
  _item<uint32_t>* _item_b(&item_b);
  _item<uint32_t>* _item_c(&item_c);

  _slitem* _slitem_a(&item_a);
  _slitem* _slitem_b(&item_b);
  _slitem* _slitem_c(&item_c);

  assert(*item_a == 1);
  assert(*item_b == 2);
  assert(*item_c == 2);

  assert((item_a.operator->()) == &data_a);
  assert((item_b.operator->()) == &data_b);
  assert((item_c.operator->()) == &data_c);

  assert(item_a.attached() == false);
  assert(item_b.attached() == false);
  assert(item_c.attached() == false);

  assert(slitem<uint32_t>::identical(item_a, item_a) == true);
  assert(slitem<uint32_t>::identical(item_a, item_b) == false);
  assert(slitem<uint32_t>::identical(item_a, item_c) == false);
  assert(slitem<uint32_t>::identical(item_b, item_a) == false);
  assert(slitem<uint32_t>::identical(item_b, item_b) == true);
  assert(slitem<uint32_t>::identical(item_b, item_c) == false);
  assert(slitem<uint32_t>::identical(item_c, item_a) == false);
  assert(slitem<uint32_t>::identical(item_c, item_b) == false);
  assert(slitem<uint32_t>::identical(item_c, item_c) == true);

  assert((item_a == item_a) == true);
  assert((item_a == item_b) == false);
  assert((item_a == item_c) == false);
  assert((item_b == item_a) == false);
  assert((item_b == item_b) == true);
  assert((item_b == item_c) == false);
  assert((item_c == item_a) == false);
  assert((item_c == item_b) == false);
  assert((item_c == item_c) == true);

  assert((item_a != item_a) == false);
  assert((item_a != item_b) == true);
  assert((item_a != item_c) == true);
  assert((item_b != item_a) == true);
  assert((item_b != item_b) == false);
  assert((item_b != item_c) == true);
  assert((item_c != item_a) == true);
  assert((item_c != item_b) == true);
  assert((item_c != item_c) == false);

  assert(_slitem::identical(item_a, item_a) == true);
  assert(_slitem::identical(item_a, item_b) == true);
  assert(_slitem::identical(item_a, item_c) == true);
  assert(_slitem::identical(item_b, item_a) == true);
  assert(_slitem::identical(item_b, item_b) == true);
  assert(_slitem::identical(item_b, item_c) == true);
  assert(_slitem::identical(item_c, item_a) == true);
  assert(_slitem::identical(item_c, item_b) == true);
  assert(_slitem::identical(item_c, item_c) == true);

  assert((*_slitem_a == *_slitem_a) == true);
  assert((*_slitem_a == *_slitem_b) == false);
  assert((*_slitem_a == *_slitem_c) == false);
  assert((*_slitem_b == *_slitem_a) == false);
  assert((*_slitem_b == *_slitem_b) == true);
  assert((*_slitem_b == *_slitem_c) == false);
  assert((*_slitem_c == *_slitem_a) == false);
  assert((*_slitem_c == *_slitem_b) == false);
  assert((*_slitem_c == *_slitem_c) == true);

  assert((*_slitem_a != *_slitem_a) == false);
  assert((*_slitem_a != *_slitem_b) == true);
  assert((*_slitem_a != *_slitem_c) == true);
  assert((*_slitem_b != *_slitem_a) == true);
  assert((*_slitem_b != *_slitem_b) == false);
  assert((*_slitem_b != *_slitem_c) == true);
  assert((*_slitem_c != *_slitem_a) == true);
  assert((*_slitem_c != *_slitem_b) == true);
  assert((*_slitem_c != *_slitem_c) == false);

  assert(_item<uint32_t>::identical(item_a, item_a) == true);
  assert(_item<uint32_t>::identical(item_a, item_b) == false);
  assert(_item<uint32_t>::identical(item_a, item_c) == false);
  assert(_item<uint32_t>::identical(item_b, item_a) == false);
  assert(_item<uint32_t>::identical(item_b, item_b) == true);
  assert(_item<uint32_t>::identical(item_b, item_c) == false);
  assert(_item<uint32_t>::identical(item_c, item_a) == false);
  assert(_item<uint32_t>::identical(item_c, item_b) == false);
  assert(_item<uint32_t>::identical(item_c, item_c) == true);

  assert((*_item_a == *_item_a) == true);
  assert((*_item_a == *_item_b) == false);
  assert((*_item_a == *_item_c) == false);
  assert((*_item_b == *_item_a) == false);
  assert((*_item_b == *_item_b) == true);
  assert((*_item_b == *_item_c) == false);
  assert((*_item_c == *_item_a) == false);
  assert((*_item_c == *_item_b) == false);
  assert((*_item_c == *_item_c) == true);

  assert((*_item_a != *_item_a) == false);
  assert((*_item_a != *_item_b) == true);
  assert((*_item_a != *_item_c) == true);
  assert((*_item_b != *_item_a) == true);
  assert((*_item_b != *_item_b) == false);
  assert((*_item_b != *_item_c) == true);
  assert((*_item_c != *_item_a) == true);
  assert((*_item_c != *_item_b) == true);
  assert((*_item_c != *_item_c) == false);

  return;
}

void dlitem_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  dlitem<uint32_t> item_a(data_a);
  dlitem<uint32_t> item_b(data_b);
  dlitem<uint32_t> item_c(data_c);

  _item<uint32_t>* _item_a(&item_a);
  _item<uint32_t>* _item_b(&item_b);
  _item<uint32_t>* _item_c(&item_c);

  _dlitem* _dlitem_a(&item_a);
  _dlitem* _dlitem_b(&item_b);
  _dlitem* _dlitem_c(&item_c);

  assert(*item_a == 1);
  assert(*item_b == 2);
  assert(*item_c == 2);

  assert((item_a.operator->()) == &data_a);
  assert((item_b.operator->()) == &data_b);
  assert((item_c.operator->()) == &data_c);

  assert(item_a.attached() == false);
  assert(item_b.attached() == false);
  assert(item_c.attached() == false);

  assert(dlitem<uint32_t>::identical(item_a, item_a) == true);
  assert(dlitem<uint32_t>::identical(item_a, item_b) == false);
  assert(dlitem<uint32_t>::identical(item_a, item_c) == false);
  assert(dlitem<uint32_t>::identical(item_b, item_a) == false);
  assert(dlitem<uint32_t>::identical(item_b, item_b) == true);
  assert(dlitem<uint32_t>::identical(item_b, item_c) == false);
  assert(dlitem<uint32_t>::identical(item_c, item_a) == false);
  assert(dlitem<uint32_t>::identical(item_c, item_b) == false);
  assert(dlitem<uint32_t>::identical(item_c, item_c) == true);

  assert((item_a == item_a) == true);
  assert((item_a == item_b) == false);
  assert((item_a == item_c) == false);
  assert((item_b == item_a) == false);
  assert((item_b == item_b) == true);
  assert((item_b == item_c) == false);
  assert((item_c == item_a) == false);
  assert((item_c == item_b) == false);
  assert((item_c == item_c) == true);

  assert((item_a != item_a) == false);
  assert((item_a != item_b) == true);
  assert((item_a != item_c) == true);
  assert((item_b != item_a) == true);
  assert((item_b != item_b) == false);
  assert((item_b != item_c) == true);
  assert((item_c != item_a) == true);
  assert((item_c != item_b) == true);
  assert((item_c != item_c) == false);

  assert(_dlitem::identical(item_a, item_a) == true);
  assert(_dlitem::identical(item_a, item_b) == true);
  assert(_dlitem::identical(item_a, item_c) == true);
  assert(_dlitem::identical(item_b, item_a) == true);
  assert(_dlitem::identical(item_b, item_b) == true);
  assert(_dlitem::identical(item_b, item_c) == true);
  assert(_dlitem::identical(item_c, item_a) == true);
  assert(_dlitem::identical(item_c, item_b) == true);
  assert(_dlitem::identical(item_c, item_c) == true);

  assert((*_dlitem_a == *_dlitem_a) == true);
  assert((*_dlitem_a == *_dlitem_b) == false);
  assert((*_dlitem_a == *_dlitem_c) == false);
  assert((*_dlitem_b == *_dlitem_a) == false);
  assert((*_dlitem_b == *_dlitem_b) == true);
  assert((*_dlitem_b == *_dlitem_c) == false);
  assert((*_dlitem_c == *_dlitem_a) == false);
  assert((*_dlitem_c == *_dlitem_b) == false);
  assert((*_dlitem_c == *_dlitem_c) == true);

  assert((*_dlitem_a != *_dlitem_a) == false);
  assert((*_dlitem_a != *_dlitem_b) == true);
  assert((*_dlitem_a != *_dlitem_c) == true);
  assert((*_dlitem_b != *_dlitem_a) == true);
  assert((*_dlitem_b != *_dlitem_b) == false);
  assert((*_dlitem_b != *_dlitem_c) == true);
  assert((*_dlitem_c != *_dlitem_a) == true);
  assert((*_dlitem_c != *_dlitem_b) == true);
  assert((*_dlitem_c != *_dlitem_c) == false);

  assert(_item<uint32_t>::identical(item_a, item_a) == true);
  assert(_item<uint32_t>::identical(item_a, item_b) == false);
  assert(_item<uint32_t>::identical(item_a, item_c) == false);
  assert(_item<uint32_t>::identical(item_b, item_a) == false);
  assert(_item<uint32_t>::identical(item_b, item_b) == true);
  assert(_item<uint32_t>::identical(item_b, item_c) == false);
  assert(_item<uint32_t>::identical(item_c, item_a) == false);
  assert(_item<uint32_t>::identical(item_c, item_b) == false);
  assert(_item<uint32_t>::identical(item_c, item_c) == true);

  assert((*_item_a == *_item_a) == true);
  assert((*_item_a == *_item_b) == false);
  assert((*_item_a == *_item_c) == false);
  assert((*_item_b == *_item_a) == false);
  assert((*_item_b == *_item_b) == true);
  assert((*_item_b == *_item_c) == false);
  assert((*_item_c == *_item_a) == false);
  assert((*_item_c == *_item_b) == false);
  assert((*_item_c == *_item_c) == true);

  assert((*_item_a != *_item_a) == false);
  assert((*_item_a != *_item_b) == true);
  assert((*_item_a != *_item_c) == true);
  assert((*_item_b != *_item_a) == true);
  assert((*_item_b != *_item_b) == false);
  assert((*_item_b != *_item_c) == true);
  assert((*_item_c != *_item_a) == true);
  assert((*_item_c != *_item_b) == true);
  assert((*_item_c != *_item_c) == false);

  return;
}

void sldlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  sldlist<uint32_t>::item item_a(data_a);
  sldlist<uint32_t>::item item_b(data_b);
  sldlist<uint32_t>::item item_c(data_c);

  sldlist<uint32_t> list_a;
  sldlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_b) == true);
  assert((list_a != list_b) == false);

  list_a.push_back(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.push_back(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.push_front(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  sldlist<uint32_t>::iterator it_a;
  sldlist<uint32_t>::iterator it_b(list_a.front());
  sldlist<uint32_t>::iterator it_c;
  it_c = list_a.back();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_a);
  assert(*it_b == data_a);
  assert(it_b.peek(0) == &data_a);
  assert(it_b.peek(1) == &data_b);
  assert(it_b.peek(2) == &data_c);
  assert(it_b.peek(3) == nullptr);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_c);
  assert(*it_c == data_c);
  assert(it_c.peek(0) == &data_c);
  assert(it_c.peek(1) == nullptr);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == false);

  it_a = list_a.front();
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);
  ++it_a;
  assert(it_a.operator->() == nullptr);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.push_back(item_a);
  list_a.push_back(item_b);
  list_a.push_back(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.pop_front() == &item_a);
  assert(list_a.pop_back() == &item_c);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  return;
}

void slodlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  slodlist<uint32_t>::item item_a(data_a);
  slodlist<uint32_t>::item item_b(data_b);
  slodlist<uint32_t>::item item_c(data_c);

  slodlist<uint32_t> list_a(my_cmp);
  slodlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_a) == true);
  assert((list_b == list_b) == true);
  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);
  assert(*list_a.min() == data_c);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);

  list_a.insert(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);
  assert(*list_a.min() == data_a);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);

  list_a.insert(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);
  assert(*list_a.min() == data_a);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  slodlist<uint32_t>::iterator it_a;
  slodlist<uint32_t>::iterator it_b(list_a.min());
  slodlist<uint32_t>::iterator it_c;
  it_c = list_a.max();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_a);
  assert(*it_b == data_a);
  assert(it_b.peek(0) == &data_a);
  assert(it_b.peek(1) == &data_b);
  assert(it_b.peek(2) == &data_c);
  assert(it_b.peek(3) == nullptr);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_c);
  assert(*it_c == data_c);
  assert(it_c.peek(0) == &data_c);
  assert(it_c.peek(1) == nullptr);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == false);

  it_a = list_a.min();
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);
  ++it_a;
  assert(it_a.operator->() == nullptr);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.removeMin() == &item_a);
  assert(list_a.removeMax() == &item_b);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  data_a = 10;
  assert((*list_a.min() <= *list_a.max()) == false);
  list_a.sort();
  assert((*list_a.min() <= *list_a.max()) == true);

  return;
}

void slcdlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  slcdlist<uint32_t>::item item_a(data_a);
  slcdlist<uint32_t>::item item_b(data_b);
  slcdlist<uint32_t>::item item_c(data_c);

  slcdlist<uint32_t> list_a;
  slcdlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_b) == true);
  assert((list_a != list_b) == false);

  list_a.insert(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);
  assert(*list_a.latest() == data_a);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);
  assert(*list_a.latest() == data_b);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);
  assert(*list_a.latest() == data_c);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  slcdlist<uint32_t>::iterator it_a;
  slcdlist<uint32_t>::iterator it_b(list_a.latest());
  slcdlist<uint32_t>::iterator it_c;
  it_c = list_a.eldest();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_c);
  assert(*it_b == data_c);
  assert(it_b.peek(0) == &data_c);
  assert(it_b.peek(1) == &data_a);
  assert(it_b.peek(2) == &data_b);
  assert(it_b.peek(3) == &data_c);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_a);
  assert(*it_c == data_a);
  assert(it_c.peek(0) == &data_a);
  assert(it_c.peek(1) == &data_b);
  assert(it_c.peek(2) == &data_c);
  assert(it_c.peek(3) == &data_a);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == true);

  it_a = list_a.latest();
  assert(*it_a == data_c);
  ++it_a;
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.remove_eldest() == &item_a);
  assert(list_a.removeLatest() == &item_c);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  return;
}

void dldlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  dldlist<uint32_t>::item item_a(data_a);
  dldlist<uint32_t>::item item_b(data_b);
  dldlist<uint32_t>::item item_c(data_c);

  dldlist<uint32_t> list_a;
  dldlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_b) == true);
  assert((list_a != list_b) == false);

  list_a.push_back(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.push_back(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.push_front(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  dldlist<uint32_t>::iterator it_a;
  dldlist<uint32_t>::iterator it_b(list_a.front());
  dldlist<uint32_t>::iterator it_c;
  it_c = list_a.back();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_a);
  assert(*it_b == data_a);
  assert(it_b.peek(-1) == nullptr);
  assert(it_b.peek(0) == &data_a);
  assert(it_b.peek(1) == &data_b);
  assert(it_b.peek(2) == &data_c);
  assert(it_b.peek(3) == nullptr);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_c);
  assert(*it_c == data_c);
  assert(it_c.peek(-3) == nullptr);
  assert(it_c.peek(-2) == &data_a);
  assert(it_c.peek(-1) == &data_b);
  assert(it_c.peek(0) == &data_c);
  assert(it_c.peek(1) == nullptr);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == true);

  it_a = list_a.front();
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);
  ++it_a;
  assert(it_a.operator->() == nullptr);

  it_a = list_a.back();
  assert(*it_a == data_c);
  --it_a;
  assert(*it_a == data_b);
  --it_a;
  assert(*it_a == data_a);
  --it_a;
  assert(it_a.operator->() == nullptr);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.push_back(item_a);
  list_a.push_back(item_b);
  list_a.push_back(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.pop_front() == &item_a);
  assert(list_a.pop_back() == &item_c);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  return;
}

void dlodlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  dlodlist<uint32_t>::item item_a(data_a);
  dlodlist<uint32_t>::item item_b(data_b);
  dlodlist<uint32_t>::item item_c(data_c);

  dlodlist<uint32_t> list_a(my_cmp);
  dlodlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_a) == true);
  assert((list_b == list_b) == true);
  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);
  assert(*list_a.min() == data_c);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);

  list_a.insert(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);
  assert(*list_a.min() == data_a);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);

  list_a.insert(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);
  assert(*list_a.min() == data_a);
  assert(*list_a.max() == data_c);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  dlodlist<uint32_t>::iterator it_a;
  dlodlist<uint32_t>::iterator it_b(list_a.min());
  dlodlist<uint32_t>::iterator it_c;
  it_c = list_a.max();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_a);
  assert(*it_b == data_a);
  assert(it_b.peek(-1) == nullptr);
  assert(it_b.peek(0) == &data_a);
  assert(it_b.peek(1) == &data_b);
  assert(it_b.peek(2) == &data_c);
  assert(it_b.peek(3) == nullptr);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_c);
  assert(*it_c == data_c);
  assert(it_c.peek(-3) == nullptr);
  assert(it_c.peek(-2) == &data_a);
  assert(it_c.peek(-1) == &data_b);
  assert(it_c.peek(0) == &data_c);
  assert(it_c.peek(1) == nullptr);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == true);

  it_a = list_a.min();
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);
  ++it_a;
  assert(it_a.operator->() == nullptr);

  it_a = list_a.max();
  assert(*it_a == data_c);
  --it_a;
  assert(*it_a == data_b);
  --it_a;
  assert(*it_a == data_a);
  --it_a;
  assert(it_a.operator->() == nullptr);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.removeMin() == &item_a);
  assert(list_a.removeMax() == &item_b);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  data_a = 10;
  assert((*list_a.min() <= *list_a.max()) == false);
  list_a.sort();
  assert((*list_a.min() <= *list_a.max()) == true);

  return;
}

void dlcdlist_test()
{
  uint32_t data_a = 1;
  uint32_t data_b = 2;
  uint32_t data_c = 2;

  dlcdlist<uint32_t>::item item_a(data_a);
  dlcdlist<uint32_t>::item item_b(data_b);
  dlcdlist<uint32_t>::item item_c(data_c);

  dlcdlist<uint32_t> list_a;
  dlcdlist<uint32_t> list_b;

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);

  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert(list_a.clear() == 0);

  assert(list_a.remove(data_a) == nullptr);
  assert(list_a.remove(data_b) == nullptr);
  assert(list_a.remove(data_c) == nullptr);

  assert((list_a == list_b) == true);
  assert((list_a != list_b) == false);

  list_a.insert(item_a);

  assert(list_a.empty() == false);
  assert(list_a.size() == 1);
  assert(*list_a.latest() == data_a);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_b);

  assert(list_a.empty() == false);
  assert(list_a.size() == 2);
  assert(*list_a.latest() == data_b);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == false);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  list_a.insert(item_c);

  assert(list_a.empty() == false);
  assert(list_a.size() == 3);
  assert(*list_a.latest() == data_c);
  assert(*list_a.eldest() == data_a);

  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == true);
  assert(list_a.contains(data_c) == true);

  assert((list_a == list_b) == false);
  assert((list_a != list_b) == true);

  dlcdlist<uint32_t>::iterator it_a;
  dlcdlist<uint32_t>::iterator it_b(list_a.latest());
  dlcdlist<uint32_t>::iterator it_c;
  it_c = list_a.eldest();

  assert(it_a.valid() == false);
  assert(it_a.operator->() == nullptr);
  assert(it_a.peek() == nullptr);

  assert(it_b.valid() == true);
  assert(it_b.operator->() == &data_c);
  assert(*it_b == data_c);
  assert(it_b.peek(-3) == &data_c);
  assert(it_b.peek(-2) == &data_a);
  assert(it_b.peek(-1) == &data_b);
  assert(it_b.peek(0) == &data_c);
  assert(it_b.peek(1) == &data_a);
  assert(it_b.peek(2) == &data_b);
  assert(it_b.peek(3) == &data_c);

  assert(it_c.valid() == true);
  assert(it_c.operator->() == &data_a);
  assert(*it_c == data_a);
  assert(it_c.peek(-3) == &data_a);
  assert(it_c.peek(-2) == &data_b);
  assert(it_c.peek(-1) == &data_c);
  assert(it_c.peek(0) == &data_a);
  assert(it_c.peek(1) == &data_b);
  assert(it_c.peek(2) == &data_c);
  assert(it_c.peek(3) == &data_a);

  assert((*it_b == *it_c) == false);
  assert((*(it_b.peek()) == *it_c) == true);

  assert((it_a == it_a) == true);
  assert((it_a == it_b) == false);
  assert((it_a == it_c) == false);
  assert((it_b == it_a) == false);
  assert((it_b == it_b) == true);
  assert((it_b == it_c) == false);
  assert((it_c == it_a) == false);
  assert((it_c == it_b) == false);
  assert((it_c == it_c) == true);

  assert((it_a != it_a) == false);
  assert((it_a != it_b) == true);
  assert((it_a != it_c) == true);
  assert((it_b != it_a) == true);
  assert((it_b != it_b) == false);
  assert((it_b != it_c) == true);
  assert((it_c != it_a) == true);
  assert((it_c != it_b) == true);
  assert((it_c != it_c) == false);

  assert(item_a.attached() == true);
  assert(item_b.attached() == true);
  assert(item_c.attached() == true);

  it_a = list_a.latest();
  assert(*it_a == data_c);
  ++it_a;
  assert(*it_a == data_a);
  ++it_a;
  assert(*it_a == data_b);
  ++it_a;
  assert(*it_a == data_c);
  --it_a;
  assert(*it_a == data_b);
  --it_a;
  assert(*it_a == data_a);
  --it_a;
  assert(*it_a == data_c);

  assert(list_a.remove(data_b) == &item_b);
  assert(list_a.size() == 2);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == true);
  assert(list_a.remove(data_b) == nullptr);

  assert(list_a.remove(data_c) == &item_c);
  assert(list_a.size() == 1);
  assert(list_a.contains(data_a) == true);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_c) == nullptr);

  assert(list_a.clear() == 1);
  assert(list_a.size() == 0);
  assert(list_a.contains(data_a) == false);
  assert(list_a.contains(data_b) == false);
  assert(list_a.contains(data_c) == false);
  assert(list_a.remove(data_a) == nullptr);

  assert(list_a.empty() == true);
  assert(list_a.size() == 0);
  list_a.insert(item_a);
  list_a.insert(item_b);
  list_a.insert(item_c);
  assert(list_a.empty() == false);
  assert(list_a.size() == 3);

  assert(list_a.remove_eldest() == &item_a);
  assert(list_a.removeLatest() == &item_c);
  assert(list_a.clear() == 1);
  assert(list_a.empty() == true);

  return;
}

int main(int argc, char *argv[])
{
  cout << "Welcome to the dlist library test suite." << endl;
  cout << "The version of the library is " << DLIST_VERSION_MAJOR << '-' << DLIST_VERSION_MINOR << '-'<< DLIST_VERSION_PATCH << '.' << endl;

  cout << "testing slitem..." << flush;
  slitem_test();
  cout << "\tsuccess" << endl;

  cout << "testing dlitem..." << flush;
  dlitem_test();
  cout << "\tsuccess" << endl;

  cout << "testing sldlist..." << flush;
  sldlist_test();
  cout << "\tsuccess" << endl;

  cout << "testing slodlist..." << flush;
  slodlist_test();
  cout << "\tsuccess" << endl;

  cout << "testing slcdlist..." << flush;
  slcdlist_test();
  cout << "\tsuccess" << endl;

  cout << "testing dldlist..." << flush;
  dldlist_test();
  cout << "\tsuccess" << endl;

  cout << "testing dlodlist..." << flush;
  dlodlist_test();
  cout << "\tsuccess" << endl;

  cout << "testing dlcdlist..." << flush;
  dlcdlist_test();
  cout << "\tsuccess" << endl;

  return 0;
}
