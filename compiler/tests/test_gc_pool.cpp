// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
#include "btest.h"
#include "catch2/catch.hpp"
#define GC_POOL_BLOCK_SIZE 1
#define private public
#include "utilities/gc_pool.h"
#undef private
using namespace yaksha;
struct test_object {
  test_object *next_{nullptr};
  test_object *prev_{nullptr};
  std::uint8_t mark_{0};
  void clean_state() {}
};
TEST_CASE("gc_pool: allocate") {
  gc_pool<test_object> pool{0};
  test_object *ptr = pool.allocate();
  REQUIRE(ptr != nullptr);
  REQUIRE(ptr->next_ == nullptr);
  REQUIRE(ptr->prev_ == nullptr);
  REQUIRE(ptr->mark_ == 4); /* 2^2 --> not-deleted */
  REQUIRE(get_bit(&ptr->mark_, GC_POOL_USED_BIT));
  REQUIRE(!get_bit(&ptr->mark_, GC_POOL_MARK_BIT));
  pool.mark(ptr);
  REQUIRE(ptr->mark_ == 6); /* 2^1 + 2^2 --> marked + not-deleted */
  REQUIRE(get_bit(&ptr->mark_, GC_POOL_USED_BIT));
  REQUIRE(get_bit(&ptr->mark_, GC_POOL_MARK_BIT));
  pool.free(ptr);
  REQUIRE(ptr->mark_ == 0); /* unmarked & deleted */
  REQUIRE(!get_bit(&ptr->mark_, GC_POOL_USED_BIT));
  REQUIRE(!get_bit(&ptr->mark_, GC_POOL_MARK_BIT));
}
TEST_CASE("gc_pool: starts with 100 free items") {
  size_t count = 0;
  gc_pool<test_object> pool{100};
  for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++count;
  }
  REQUIRE(count == 100);
}
TEST_CASE("gc_pool: mark and sweep") {
  gc_pool<test_object> pool{0};
  // it is initialized to 0 elements, and it will use 'new' to allocate new items
  size_t count = 0;
  for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++count;
  }
  REQUIRE(count == 0);
  test_object *o1 = pool.allocate();
  REQUIRE(o1 != nullptr);
  REQUIRE(o1->next_ == nullptr);
  REQUIRE(o1->prev_ == nullptr);
  REQUIRE(o1->mark_ == 4);
  test_object *o2 = pool.allocate();
  REQUIRE(o2 != nullptr);
  REQUIRE(o2->next_ == o1);
  REQUIRE(o2->prev_ == nullptr);
  REQUIRE(o2->mark_ == 4);
  REQUIRE(o1->next_ == nullptr);
  REQUIRE(o1->prev_ == o2);
  REQUIRE(o1->mark_ == 4);
  pool.initialize_mark_sweep();
  pool.mark(o1);
  pool.sweep();
  REQUIRE(o1->next_ == nullptr);
  REQUIRE(o1->prev_ == nullptr);
  // this does not get unmarked!
  REQUIRE(o1->mark_ == 6);
  REQUIRE(o2->next_ == nullptr);
  REQUIRE(o2->prev_ == nullptr);
  REQUIRE(o2->mark_ == false);
  REQUIRE(pool.m_used_doubly_linked_list_ == o1);
  REQUIRE(pool.m_free_doubly_linked_list_ == o2);
}
TEST_CASE("gc_pool: mark sweep with few freed") {
  gc_pool<test_object> pool{5};
  auto o1 = pool.allocate();
  auto o2 = pool.allocate();
  auto o3 = pool.allocate();
  auto o4 = pool.allocate();
  auto o5 = pool.allocate();
  REQUIRE(o5 != nullptr);
  auto o6 = pool.allocate();
  REQUIRE(o6 != nullptr);
  size_t count = 0;
  for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++count;
  }
  for (test_object *ptr = pool.m_used_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++count;
  }
  // --------
  auto ox = pool.allocate();
  pool.free(ox);
  ox = pool.allocate();
  pool.free(ox);
  ox = pool.allocate();
  pool.mark(ox);
  ox = pool.allocate();
  pool.mark(ox);
  pool.free(ox);
  // --------
  pool.mark(o1);
  pool.free(o2);
  pool.free(o3);
  pool.free(o1);
  pool.mark(o4);
  size_t mark_count = pool.sweep();
  REQUIRE(mark_count == 2);
  REQUIRE(pool.sweep() == 0);
  REQUIRE(pool.sweep() == 0);
  REQUIRE(pool.sweep() == 0);
  size_t full_count_after_sweep = 0;
  for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++full_count_after_sweep;
  }
  for (test_object *ptr = pool.m_used_doubly_linked_list_; ptr != nullptr;
       ptr = ptr->next_) {
    ++full_count_after_sweep;
  }
  REQUIRE(full_count_after_sweep == 8);
}
TEST_CASE("gc_pool: random test") {
  for (int i = 0; i < 80; i++) {
    size_t initial_size = 1 + rand() % 200;
    gc_pool<test_object> pool{initial_size};
    size_t count = 0;
    for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
         ptr = ptr->next_) {
      ++count;
    }
    REQUIRE(count == initial_size);
    size_t alloc_count = 1 + rand() % 200;
    size_t mark_count = 0;
    for (int j = 0; j < alloc_count - 1; j++) {
      test_object *ptr = pool.allocate();
      REQUIRE(ptr != nullptr);
      REQUIRE(ptr->mark_ == 4);
      bool marked = false;
      if (rand() % 3 == 0) {
        pool.mark(ptr);
        mark_count++;
        marked = true;
      }
      if (rand() % 5 == 0) {
        pool.free(ptr);
        if (marked) { mark_count--; }
      }
    }
    // why freed count should be at least 1, in case we marked all above :( or freed
    pool.allocate();
    REQUIRE(pool.sweep() >= 1);
    REQUIRE(pool.sweep() == 0);
    REQUIRE(pool.sweep() == 0);
    REQUIRE(pool.sweep() == 0);
    count = 0;
    for (test_object *ptr = pool.m_free_doubly_linked_list_; ptr != nullptr;
         ptr = ptr->next_) {
      ++count;
    }
    for (test_object *ptr = pool.m_used_doubly_linked_list_; ptr != nullptr;
         ptr = ptr->next_) {
      ++count;
    }
    REQUIRE(count == pool.num_allocated_);
  }
}
TEST_CASE("gc_pool: allocate/free") {
  gc_pool<test_object> pool{2};
  test_object *p1 = pool.allocate();
  test_object *p2 = pool.allocate();
  REQUIRE(p1 != nullptr);
  REQUIRE(p2 != nullptr);
  REQUIRE(pool.m_free_doubly_linked_list_ == nullptr);
  REQUIRE(pool.m_used_doubly_linked_list_ != nullptr);
  pool.free(p1);
  pool.free(p2);
  REQUIRE(pool.m_free_doubly_linked_list_ != nullptr);
  REQUIRE(pool.m_used_doubly_linked_list_ == nullptr);
}
TEST_CASE("gc_pool: clear") {
  gc_pool<test_object> pool{1};
  test_object *p1 = pool.allocate();
  REQUIRE(p1 != nullptr);
  test_object *p2 = pool.allocate();
  REQUIRE(p2 != nullptr);
  pool.clear();
  REQUIRE(pool.m_allocated_blocks_.empty());
  REQUIRE(pool.m_free_doubly_linked_list_ == nullptr);
  REQUIRE(pool.m_used_doubly_linked_list_ == nullptr);
  REQUIRE(pool.num_allocated_ == 0);
}
TEST_CASE("gc_pool: allocate more than initial size, check linked list") {
  gc_pool<test_object> pool{2};
  test_object *p1 = pool.allocate();
  test_object *p2 = pool.allocate();
  test_object *p3 = pool.allocate();
  REQUIRE(p1 != nullptr);
  REQUIRE(p2 != nullptr);
  REQUIRE(p3 != nullptr);
  REQUIRE(p1->next_ == nullptr);
  REQUIRE(p2->next_ == p1);
  REQUIRE(p3->next_ == p2);
}
