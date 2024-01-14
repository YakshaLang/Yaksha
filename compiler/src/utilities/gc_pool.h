// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
// gc_pool.h
#ifndef GC_POOL_H
#define GC_POOL_H
#include "cpp_util.h"
#include <iostream>
#include <list>
#include <memory>
/**
 * A simple object pool that uses 2 doubly linked lists to keep track of free and used
 * objects. The pool is not thread safe.
 * each allocation is done as block of size GC_POOL_BLOCK_SIZE (this is tracked in m_allocated_blocks_)
 *
 * free objects are kept in a doubly linked list (m_free_doubly_linked_list_)
 * used objects are kept in a doubly linked list (m_used_doubly_linked_list_)
 * m_allocated_blocks_ (std::list<T *>) tracks blocks (T*) that are allocated by the pool,
 * individual objects are tracked in m_free_doubly_linked_list_ and m_used_doubly_linked_list_.
 *
 * If you allocate an item using gc_pool, you must free it using gc_pool::free
 *
 * @tparam T The type of object to pool (must have a next_/prev_ member(T*), a mark_ member (std::uint8_t) and clean_state())
 */
#ifndef GC_POOL_BLOCK_SIZE
#define GC_POOL_BLOCK_SIZE 100
#endif
#ifndef GC_POOL_INITIAL_BLOCK_COUNT
#define GC_POOL_INITIAL_BLOCK_COUNT 1
#endif
namespace yaksha {
  static inline void set_bit(std::uint8_t *x, int bit_number) {
    *x |= (1L << bit_number);
  }
  static inline void clear_bit(std::uint8_t *x, int bit_number) {
    *x &= ~((1) << (bit_number));
  }
  static inline bool get_bit(const std::uint8_t *x, int bit_number) {
    return 1 == ((*x >> bit_number) & 1);
  }
  static const int GC_POOL_MARK_BIT = 1;// 2
  static const int GC_POOL_USED_BIT = 2;// 4
  //  static const int GC_RESERVED1_BIT = 3; // 8
  //  static const int GC_RESERVED2_BIT = 4; // 16
  //  static const int GC_RESERVED3_BIT = 5; // 32
  //  static const int GC_RESERVED4_BIT = 6; // 64
  template<typename T>
  struct gc_pool {
    /**
     * Create a new pool
     * @param block_count number of blocks to allocate
     */
    explicit gc_pool(size_t block_count = GC_POOL_INITIAL_BLOCK_COUNT) noexcept(
        false);
    // disable copy/move
    gc_pool(const gc_pool &) = delete;
    gc_pool(gc_pool &&) = delete;
    gc_pool &operator=(const gc_pool &) = delete;
    gc_pool &operator=(gc_pool &&) = delete;
    /**
     * Destroy the pool and free all allocated memory
     */
    ~gc_pool() noexcept;
    /**
     * Allocate an object from the pool
     * @return
     */
    T *allocate();
    /**
     * Free an object allocated from the pool
     * @param ptr
     */
    void free(T *ptr);
    /**
     * Unmark all objects in the pool
     */
    void initialize_mark_sweep();
    /**
     * Mark an object as used
     * @param ptr
     */
    void mark(T *ptr);
    /**
     * Sweep the pool and free all unmarked objects
     * @return number of objects freed
     */
    size_t sweep();
    /**
     * Clear the pool and free all allocated memory
     */
    void clear();
    size_t allocated_{0};

private:
    /**
     * Doubly linked list of free objects
     */
    T *m_free_doubly_linked_list_;
    /**
     * Doubly linked of used objects
     */
    T *m_used_doubly_linked_list_;
    /**
     * Number of objects allocated by the pool
     */
    size_t num_allocated_{0};
    /**
     * Allocate block(s) of memory for the pool,
     * and add elements to m_free_doubly_linked_list_
     * @param block_count number of blocks to allocate
     */
    void allocate_items(size_t block_count);
    /**
     * Allocate a single block of memory for the pool
     * @param item_count number of items to allocate
     * @return pointer to the allocated block
     */
    T *allocate_block(size_t item_count);
    /**
     * Free a block of memory allocated by the pool
     * @param ptr
     */
    void free_block(T *ptr);
    /**
     * List of blocks allocated by the pool
     */
    std::list<T *> m_allocated_blocks_{};
  };
  template<typename T>
  void gc_pool<T>::clear() {
    m_free_doubly_linked_list_ = nullptr;
    m_used_doubly_linked_list_ = nullptr;
    num_allocated_ = 0;
    for (auto ptr : m_allocated_blocks_) { free_block(ptr); }
    m_allocated_blocks_.clear();
  }
  // ==================== Implementation ====================
  template<typename T>
  void gc_pool<T>::free_block(T *ptr) {
    delete[] (ptr);
  }
  template<typename T>
  T *gc_pool<T>::allocate_block(size_t item_count) {
    T *ptr = new T[item_count];
    if (ptr == nullptr) {
      throw std::runtime_error("gc_pool: failed to allocate memory");
    }
    num_allocated_ += item_count;
    m_allocated_blocks_.push_back(ptr);
    return ptr;
  }
  template<typename T>
  gc_pool<T>::~gc_pool() noexcept {
    clear();
  }
  template<typename T>
  gc_pool<T>::gc_pool(size_t block_count) noexcept(false)
      : m_free_doubly_linked_list_(nullptr),
        m_used_doubly_linked_list_(nullptr) {
    allocate_items(block_count);
  }
  template<typename T>
  void gc_pool<T>::allocate_items(size_t block_count) {
    for (size_t j = 0; j < block_count; j++) {
      T *block = allocate_block(GC_POOL_BLOCK_SIZE);
      for (size_t i = 0; i < GC_POOL_BLOCK_SIZE; i++) {
        T *ptr = reinterpret_cast<T *>(block++);
        ptr->prev_ = nullptr;
        ptr->next_ = m_free_doubly_linked_list_;
        if (m_free_doubly_linked_list_ != nullptr) {
          m_free_doubly_linked_list_->prev_ = ptr;
        }
        ptr->mark_ = 0;// both deleted & unmarked
        m_free_doubly_linked_list_ = ptr;
      }
    }
  }
  template<typename T>
  size_t gc_pool<T>::sweep() {
    size_t freed = 0;
    T *ptr = m_used_doubly_linked_list_;
    while (ptr != nullptr) {
      T *next = ptr->next_;
      // sweep unmarked
      if (!get_bit(&ptr->mark_, GC_POOL_MARK_BIT)) {
#ifdef GC_POOL_DEBUG
        if (!get_bit(&ptr->mark_, GC_POOL_USED_BIT)) {
          // we are deleting something that we have deleted?
          std::cout << "REDELETED:   " << ptr << std::endl;
        } else {
          std::cout << "DELETED:   " << ptr << std::endl;
        }
#endif
        this->free(ptr);
        freed++;
      }
      ptr = next;
    }
    return freed;
  }
  template<typename T>
  T *gc_pool<T>::allocate() {
    if (m_free_doubly_linked_list_ == nullptr) { allocate_items(1); }
    // In order for the pool to work, we must remove the object from the free
    // list and add it to the used list, ensuring prev_ and next_ are properly set
    T *ptr = m_free_doubly_linked_list_;
    m_free_doubly_linked_list_ = ptr->next_;
    if (m_free_doubly_linked_list_ != nullptr) {
      m_free_doubly_linked_list_->prev_ = nullptr;
    }
    // add to used
    ptr->prev_ = nullptr;
    ptr->next_ = m_used_doubly_linked_list_;
    if (m_used_doubly_linked_list_ != nullptr) {
      m_used_doubly_linked_list_->prev_ = ptr;
    }
    m_used_doubly_linked_list_ = ptr;
    ptr->mark_ = 0;                        // unmarked + deleted
    set_bit(&ptr->mark_, GC_POOL_USED_BIT);// unmarked + not-deleted
    allocated_++;
    ptr->clean_state();
    return ptr;
  }
  template<typename T>
  void gc_pool<T>::initialize_mark_sweep() {
    for (T *cur = m_used_doubly_linked_list_; cur != nullptr;
         cur = cur->next_) {
      clear_bit(&cur->mark_, GC_POOL_MARK_BIT);// unmarked
    }
    // Unmark free list as well?
    for (T *cur = m_free_doubly_linked_list_; cur != nullptr;
         cur = cur->next_) {
      clear_bit(&cur->mark_, GC_POOL_MARK_BIT);// unmarked
    }
  }
  template<typename T>
  void gc_pool<T>::mark(T *ptr) {
#ifdef GC_POOL_DEBUG
    std::cout << "MARKED: " << ptr << std::endl;
#endif
    set_bit(&ptr->mark_, GC_POOL_MARK_BIT);// marked
  }
  template<typename T>
  void gc_pool<T>::free(T *ptr) {
    ptr->mark_ = 0;// unmarked + deleted
    if (ptr->prev_ != nullptr) { ptr->prev_->next_ = ptr->next_; }
    if (ptr->next_ != nullptr) { ptr->next_->prev_ = ptr->prev_; }
    if (ptr == m_used_doubly_linked_list_) {
      m_used_doubly_linked_list_->prev_ = nullptr;
      m_used_doubly_linked_list_ = ptr->next_;
    }
    ptr->prev_ = nullptr;
    ptr->next_ = m_free_doubly_linked_list_;
    if (m_free_doubly_linked_list_ != nullptr) {
      m_free_doubly_linked_list_->prev_ = ptr;
    }
    m_free_doubly_linked_list_ = ptr;
    if (allocated_ > 0) { allocated_--; }
  }
}// namespace yaksha
#endif
