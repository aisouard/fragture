#ifndef TRIENODE_H
#define TRIENODE_H

#include <map>
#include "public/ustring.h"

using Public::UString;

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
}

#endif //TRIENODE_H
