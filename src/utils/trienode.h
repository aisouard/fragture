/*
 * Copyright 2018 Axel Isouard <axel@isouard.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef UTILS_TRIENODE_H_
#define UTILS_TRIENODE_H_

#include <map>
#include "common/types/ustring.h"

using Common::Types::UString;

namespace Utils {
template <typename T>
class TrieNode {
  typedef std::map<UChar, TrieNode *> TrieNodeMap;
  typedef typename TrieNodeMap::iterator TrieNodeMapIterator;

 public:
  TrieNode() : _value(NULL) {
  }

  ~TrieNode() {
    if (_value) {
      _value = NULL;
    }

    TrieNodeMapIterator it = _children.begin();
    while (it != _children.end()) {
      delete (*it).second;
      ++it;
    }

    _children.clear();
  }

  T GetValue() {
    return _value;
  }

  void SetValue(T value) {
    _value = value;
  }

  void Insert(const UString &key, T value) {
    if (!key.length()) {
      _value = value;
      return;
    }

    UChar c = key[0];
    TrieNodeMapIterator result = _children.find(c);
    if (result == _children.end()) {
      _children[c] = new TrieNode<T>();
    }

    UString next;
    key.extract(1, key.length(), next);
    _children[c]->Insert(next, value);
  }

  TrieNode *Find(const UString &key) {
    if (!key.length()) {
      return this;
    }

    UChar c = key[0];
    TrieNodeMapIterator result = _children.find(c);
    if (result == _children.end()) {
      return NULL;
    }

    UString next;
    key.extract(1, key.length(), next);
    return _children[c]->Find(next);
  }

  void Delete(const UString &key) {
    if (!key.length()) {
      return;
    }

    UChar c = key[0];
    TrieNodeMapIterator result = _children.find(c);
    if (result == _children.end()) {
      return;
    }

    UString next;
    key.extract(1, key.length(), next);
    if (!next.length()) {
      delete (*result).second;
      _children.erase(result);
      return;
    }

    _children[c]->Delete(next);
  }

 private:
  T _value;
  TrieNodeMap _children;
};
}  // namespace Utils

#endif  // UTILS_TRIENODE_H_
