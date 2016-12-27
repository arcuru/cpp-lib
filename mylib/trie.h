#pragma once

#include <map>
#include <string>

/**
 * Simple Trie container for storing and looking up string objects.
 *
 * This container is NOT compressed.
 */
class trie {
  struct Node {
    std::map<char, Node> table; // TODO: Replace with flat_map
    bool end = false;
  };
  Node root;

  /**
   * Recursively erase a word from the trie, freeing memory as we go
   * @param ptr Pointer to current traversal node.
   * @param s   Word to erase.
   * @param i   Iteration index.
   */
  void erase(Node *ptr, const std::string &s, size_t i) {
    if (s.size() == i) {
      ptr->end = false;
    } else {
      const auto it = ptr->table.find(s.at(i));
      if (it == ptr->table.end()) {
        return;
      }
      const auto next = &it->second;
      erase(next, s, i + 1);
      // Erase the next node if it is empty
      if (!next->end && next->table.empty()) {
        ptr->table.erase(it);
      }
    }
  }

public:
  /**
   * Insert a new string into the container.
   * @param s String to insert
   */
  void insert(const std::string &s) {
    auto ptr = &root;
    for (const auto c : s)
      ptr = &ptr->table[c];
    ptr->end = true;
  }

  /**
   * Test if a string is present in the container.
   * @param  s String to test
   * @return   Returns true if found
   */
  bool find(const std::string &s) const {
    auto ptr = &root;
    for (const auto c : s) {
      const auto it = ptr->table.find(c); // TODO: const auto
      if (it == ptr->table.end()) {
        return false;
      }
      ptr = &it->second;
    }
    return ptr->end;
  }

  /**
   * Remove a word from the trie.
   * @param s Word to remove
   */
  void erase(const std::string &s) { erase(&root, s, 0); }
};
