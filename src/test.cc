#include <gtest/gtest.h>

#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

// Array start

TEST(array_test, array_constructor_test) {
  s21::array<int, 0> arr = s21::array<int, 0>();
  ASSERT_EQ(arr.empty(), true);
}

TEST(array_test, array_constructor_test_2) {
  s21::array<int, 10> arr = s21::array<int, 10>();
  ASSERT_EQ(arr.empty(), false);
}

TEST(array_test, array_constructor_init_value_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.empty(), false);
}

TEST(array_test, array_constructor_copy_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = s21::array<int, 4>(arr);
  ASSERT_EQ(arr2.size(), arr.size());
  ASSERT_EQ(arr2.empty(), false);
}

TEST(array_test, array_constructor_move_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = std::move(arr);
  ASSERT_EQ(arr2.empty(), false);
}

TEST(array_test, array_constructor_operator_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = arr;
  ASSERT_EQ(arr2.empty(), false);
}

TEST(array_test, array_at_test) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);
  ASSERT_EQ(arr.at(2), 3);
}

TEST(array_test_THROW, array_at_test_2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_ANY_THROW(arr.at(10));
  EXPECT_THROW((arr.at(10)), std::out_of_range);
}

TEST(array_test_THROW, array_at_test_3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_ANY_THROW(arr.at(-10));
}

TEST(array_test_THROW, array_at_test_4) {
  s21::array<int, 0> arr = s21::array<int, 0>();
  EXPECT_ANY_THROW(arr.at(0));
}

TEST(array_test, array_square_operator_test) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);
  ASSERT_EQ(arr[2], 3);
}

TEST(array_test, array_square_operator_test_2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_NO_THROW(arr[10]);
}

TEST(array_test_THROW, array_square_operator_test_3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_NO_THROW(arr[-10]);
}

TEST(array_test, array_front_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.front(), 1);
}

TEST(array_test, array_back_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.back(), 4);
}

TEST(array_test, array_data_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  auto dt = arr.data();
  ASSERT_EQ(dt[0], 1);
}

TEST(array_test, array_begin_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  auto dt = arr.begin();
  ASSERT_EQ(*dt, 1);
}

TEST(array_test, array_empty_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.empty(), false);
}

TEST(array_test, array_size_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.size(), 4);
}

TEST(array_test, array_max_size_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.max_size(), 4);
}

TEST(array_test, max_size) {
  std::array<int, 5> std_int;
  s21::array<int, 5> s21_int;
  std::array<double, 5> std_double;
  s21::array<double, 5> s21_double;

  ASSERT_EQ(std_int.max_size(), s21_int.max_size());
  ASSERT_EQ(std_double.max_size(), s21_double.max_size());
}

TEST(array_test, array_fill_test) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(8);
  ASSERT_EQ(arr.back(), 8);
}

TEST(array_test, array_swap_test) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = s21::array<int, 4>();
  arr2.fill(7);
  arr.swap(arr2);
  ASSERT_EQ(*arr.begin(), 7);
}

// Array end

// List start

template <typename T>
testing::AssertionResult compare_list(std::list<T> og, s21::list<T> copy) {
  testing::AssertionResult res = testing::AssertionSuccess() << "List match";
  if (og.size() != copy.size()) {
    res = testing::AssertionFailure()
          << "Sizes do not match " << og.size() << " != " << copy.size();
  } else {
    bool pass = true;
    while (pass && !og.empty()) {
      if (og.front() != copy.front()) {
        pass = false;
        res = testing::AssertionFailure()
              << og.front() << " != " << copy.front();
      }
      og.pop_front();
      copy.pop_front();
    }
  }
  return res;
}

TEST(list_test, list_constructor_default_test) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.empty(), true);
}

TEST(list_test, list_constructor_value_test) {
  s21::list<int> lst = s21::list<int>(3);
  ASSERT_EQ(lst.empty(), false);
}

TEST(list_test, list_constructor_copy_test) {
  s21::list<int> lst({3, 4, 3});
  s21::list<int> lst2 = s21::list<int>(lst);
  std::list<int> og({3, 4, 3});
  ASSERT_EQ(lst2.size(), 3);
  EXPECT_TRUE(compare_list(og, lst2));
}

TEST(list_test, list_constructor_move_test) {
  s21::list<int> lst({3, 4, 3});
  s21::list<int> lst2 = std::move(lst);
  ASSERT_EQ(lst2.size(), 3);
  ASSERT_EQ(lst.size(), 0);
  EXPECT_TRUE(lst.empty());
  std::list<int> og({3, 4, 3});
  EXPECT_TRUE(compare_list(og, lst2));
}

TEST(list_test, list_back_test) {
  s21::list<int> lst = s21::list<int>(3);
  lst.push_back(5);
  ASSERT_EQ(lst.back(), 5);
}

TEST(list_test_THROW, list_back_test_2) {
  s21::list<int> lst = s21::list<int>();
  EXPECT_THROW(lst.back(), std::exception);
}

TEST(list_test, list_front_test) {
  s21::list<int> lst({3});
  lst.push_back(5);
  ASSERT_EQ(lst.front(), 3);
}

TEST(list_test_THROW, list_front_test_2) {
  s21::list<int> lst = s21::list<int>();
  EXPECT_THROW(lst.front(), std::exception);
}

TEST(list_test, list_empty_test) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.empty(), true);
}

TEST(list_test, list_size_test) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.size(), 0);
}

TEST(list_test, list_size_test_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_front(4);
  lst.push_back(4);
  lst.push_back(3);
  lst.push_back(2);
  lst.pop_back();
  lst.pop_front();
  ASSERT_EQ(lst.size(), 3);
}

TEST(list_test, list_clear_test) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_front(4);
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
}

TEST(list_test, list_clear_test_2) {
  s21::list<int> lst = s21::list<int>();
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
}

TEST(list_test, list_insert_test) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.begin(), 1);

  std::list<int> og;
  og.push_back(10);
  og.push_back(12);
  og.insert(og.begin(), 1);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_insert_test_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(10);
  lst.push_back(12);
  lst.push_back(12);
  auto it = lst.begin();
  lst.insert(it, 12);
  ASSERT_EQ(lst.size(), 4);
}

TEST(list_test, list_insert_test_3) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  auto it = lst.begin();
  auto it2 = lst.begin();
  ++it;
  it++;
  --it;
  it--;
  lst.insert(it, 4);
  EXPECT_TRUE(it == it2);
  ++it2;
  EXPECT_TRUE(it != it2);
}

TEST(list_test, list_insert_test_5) {
  s21::list<int> lst = s21::list<int>();
  auto it = lst.begin();
  lst.insert(it, 0);
  ASSERT_EQ(lst.size(), 1);
}

TEST(list_test, list_insert_test_end) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.end(), 1);

  std::list<int> og;
  og.push_back(10);
  og.push_back(12);
  og.insert(og.end(), 1);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_insert_test_begin) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.begin(), 1);

  std::list<int> og;
  og.push_back(10);
  og.push_back(12);
  og.insert(og.begin(), 1);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_insert_test_begin_empty) {
  s21::list<int> lst;
  lst.insert(lst.begin(), 1);
  lst.push_back(10);
  lst.push_back(12);

  std::list<int> og;
  og.insert(og.begin(), 1);
  og.push_back(10);
  og.push_back(12);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_erase_test_1) {
  s21::list<int> lst;
  auto it = lst.begin();
  lst.insert(it, 0);
  lst.push_back(12);
  lst.push_back(34);
  it = lst.begin();
  lst.erase(++it);
  ASSERT_EQ(lst.size(), 2);

  std::list<int> og;
  auto og_it = og.begin();
  og.insert(og_it, 0);
  og.push_back(12);
  og.push_back(34);
  og_it = og.begin();
  og.erase(++og_it);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test_THROW, list_erase_test_2) {
  s21::list<int> lst = s21::list<int>();
  auto it = lst.begin();
  EXPECT_THROW(lst.erase(it), std::exception);
}

TEST(list_test, list_erase_test_3) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  auto it = lst.begin();
  lst.erase(it);

  std::list<int> og;
  og.push_back(1);
  og.push_back(2);
  og.push_back(3);
  og.push_back(4);
  auto og_it = og.begin();
  og.erase(og_it);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_push_back_test_1) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  ASSERT_EQ(lst.front(), 5);
}

TEST(list_test, list_push_back_test_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(54);
  ASSERT_EQ(lst.front(), 5);
}

TEST(list_test, list_push_back_test_3) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(54);
  ASSERT_EQ(lst.back(), 54);
}

TEST(list_test, list_push_front_test) {
  s21::list<int> lst = s21::list<int>();
  lst.push_front(54);
  lst.push_front(32);
  lst.push_front(12);
  ASSERT_EQ(lst.front(), 12);
}

TEST(list_test, list_pop_front_test) {
  s21::list<int> lst = s21::list<int>();
  lst.push_front(54);
  lst.push_front(32);
  lst.push_front(12);
  lst.pop_front();
  ASSERT_EQ(lst.front(), 32);
}

TEST(list_test, list_pop_back_test_1) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(45);
  lst.pop_back();
  ASSERT_EQ(lst.back(), 5);
}

TEST(list_test_THROW, list_pop_back_test_4) {
  s21::list<int> lst = s21::list<int>();
  EXPECT_THROW(lst.pop_back(), std::exception);
}

TEST(list_test_THROW, list_pop_front_test_4) {
  s21::list<int> lst = s21::list<int>();
  EXPECT_THROW(lst.pop_front(), std::exception);
}

TEST(list_test, list_merge_test) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(40);
  lst2.push_back(50);
  lst2.push_back(60);
  lst.merge(lst2);
  std::list<int> og = std::list<int>();
  og.push_back(10);
  og.push_back(20);
  og.push_back(30);
  og.push_back(40);
  og.push_back(50);
  og.push_back(60);

  ASSERT_EQ(lst.size(), 6);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_merge_test2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(40);
  lst2.push_back(50);
  lst2.push_back(60);
  lst2.merge(lst);
  std::list<int> og = std::list<int>();
  og.push_back(10);
  og.push_back(20);
  og.push_back(30);
  og.push_back(40);
  og.push_back(50);
  og.push_back(60);

  ASSERT_EQ(lst2.size(), 6);
  EXPECT_TRUE(compare_list(og, lst2));
}

TEST(list_test, list_merge_test3) {
  s21::list<int> lst({4, 5, 6, 10, 11, 12, 16, 17, 18});
  s21::list<int> lst2({1, 2, 3, 7, 8, 9, 13, 14, 15, 19, 20, 21});
  std::list<int> og({1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                     12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
  lst.merge(lst2);

  ASSERT_EQ(lst.size(), 21);
  ASSERT_EQ(lst2.size(), 0);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_swap_test) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(15);
  lst.push_back(32);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(81);
  lst2.push_back(71);

  lst.swap(lst2);

  ASSERT_EQ(lst.front(), 81);
  ASSERT_EQ(lst2.front(), 15);
}

TEST(list_test, list_reverse_test) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(534);
  lst.push_back(213);
  lst.push_back(954);
  lst.reverse();

  ASSERT_EQ(lst.front(), 954);
}

TEST(list_test, list_splice_test_1) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(4);
  lst2.push_back(5);
  auto it = lst.begin();
  lst.splice(it, lst2);
  ASSERT_EQ(lst.size(), 5);
}

TEST(list_test, list_splice_test_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(4);
  lst2.push_back(5);
  auto it = lst.begin();
  lst.splice(it, lst2);
  ASSERT_EQ(lst.front(), 4);
}

TEST(list_test, list_splice_test_3) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(4);
  lst2.push_back(5);
  auto it = lst.begin();
  ++it;
  lst.splice(it, lst2);
  ASSERT_EQ(lst.front(), 1);
}

TEST(list_test, list_unique_test) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(43);
  lst.push_back(43);
  lst.push_back(123);
  lst.push_back(348);
  lst.push_back(439);

  std::list<int> og = std::list<int>();

  og.push_back(43);
  og.push_back(43);
  og.push_back(123);
  og.push_back(348);
  og.push_back(439);

  lst.unique();
  og.unique();

  ASSERT_EQ(lst.size(), 4);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_sort_test) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(5);
  lst.push_back(4);
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(1);

  lst.sort();

  ASSERT_EQ(lst.front(), 1);
  std::list<int> og({1, 2, 3, 4, 5});
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_sort_test2) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  lst.push_back(5);

  lst.sort();

  std::list<int> og({1, 2, 3, 4, 5});

  ASSERT_EQ(lst.front(), 1);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_sort_test3) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(830145);
  lst.push_back(1908);
  lst.push_back(-1435);
  lst.push_back(6789);
  lst.push_back(-12);
  lst.push_back(8301345);

  std::list<int> og = std::list<int>();

  og.push_back(830145);
  og.push_back(1908);
  og.push_back(-1435);
  og.push_back(6789);
  og.push_back(-12);
  og.push_back(8301345);

  lst.sort();
  og.sort();

  ASSERT_EQ(lst.front(), -1435);
  EXPECT_TRUE(compare_list(og, lst));
}

TEST(list_test, list_test_begin) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  ASSERT_EQ(3, lst.front());
}

TEST(list_test, list_test_end) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  ASSERT_EQ(5, lst.back());
}

TEST(list_test, list_emplace_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(10);
  auto it = lst.begin();
  lst.emplace(it, 1, 2, 3, 4, 5);
  ASSERT_EQ(1, lst.front());
  ASSERT_EQ(7, lst.size());
}

TEST(list_test, list_test_emplace_back) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  lst.emplace_back(6, 7, 8, 9, 10);
  ASSERT_EQ(10, lst.back());
  ASSERT_EQ(10, lst.size());
}

TEST(list_test, list_test_emplace_front) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  lst.emplace_front(6, 7, 8, 9, 10);
  ASSERT_EQ(10, lst.front());
  ASSERT_EQ(10, lst.size());
}

TEST(list_test, max_size) {
  std::list<int> std_int;
  s21::list<int> s21_int;
  std::list<double> std_double;
  s21::list<double> s21_double;

  ASSERT_EQ(std_int.max_size(), s21_int.max_size());
  ASSERT_EQ(std_double.max_size(), s21_double.max_size());
}

// List end

// Queue start

template <typename T>
testing::AssertionResult compare_queue(std::queue<T> og, s21::queue<T> test) {
  testing::AssertionResult res = testing::AssertionSuccess() << "Queues match";
  if (og.size() != test.size()) {
    res = testing::AssertionFailure()
          << "Sizes don't match " << og.size() << " != " << test.size();
  } else {
    bool pass = true;
    while (pass && !og.empty()) {
      if (og.front() != test.front()) {
        pass = false;
        res = testing::AssertionFailure()
              << og.front() << " != " << test.front();
      }
      og.pop();
      test.pop();
    }
  }
  return res;
}

TEST(queue_suite, push_one) {
  s21::queue<int> test;
  test.push(10);
  EXPECT_EQ(test.front(), 10);
  EXPECT_EQ(test.back(), 10);
  EXPECT_FALSE(test.empty());
}

TEST(queue_suite_THROW, empty) {
  s21::queue<int> test;
  EXPECT_ANY_THROW(test.front());
  EXPECT_ANY_THROW(test.back());
  EXPECT_EQ(test.size(), 0);
  EXPECT_TRUE(test.empty());
}

TEST(queue_suite, push_multiple) {
  s21::queue<int> test;
  std::queue<int> og;
  test.push(10);
  test.push(20);
  test.push(-30);
  og.push(10);
  og.push(20);
  og.push(-30);
  EXPECT_TRUE(compare_queue(og, test));
  EXPECT_EQ(test.front(), 10);
  EXPECT_EQ(test.back(), -30);
  EXPECT_EQ(og.front(), 10);
  EXPECT_EQ(og.back(), -30);
}

TEST(queue_suite_THROW, pop) {
  s21::queue<double> test;
  test.push(10);
  test.push(20.5);
  test.push(-30.21);

  for (int i = 0; i < 3; i++) {
    test.pop();
  }
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_ANY_THROW(test.front());
  EXPECT_ANY_THROW(test.back());
}

TEST(queue_suite, swap) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> a_og({1, 2, 3, 4});
  s21::queue<int> b({-1, -2, -3});
  std::queue<int> b_og({-1, -2, -3});
  a.swap(b);
  EXPECT_TRUE(compare_queue(b_og, a));
  EXPECT_TRUE(compare_queue(a_og, b));
  b.swap(a);
  EXPECT_TRUE(compare_queue(a_og, a));
  EXPECT_TRUE(compare_queue(b_og, b));
}

TEST(queue_suite, move_init) {
  s21::queue<int> a({5, 3, 2, 7});
  s21::queue<int> b(std::move(a));
  std::queue<int> og({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(og, b));
  EXPECT_TRUE(a.empty());
}

TEST(queue_suite, move_overload) {
  s21::queue<int> a({5, 3, 2, 7});
  s21::queue<int> b = std::move(a);
  std::queue<int> og({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(og, b));
  EXPECT_TRUE(a.empty());
}

TEST(queue_suite, test) {
  s21::queue<int> a({5, 3, 2, 7});
  s21::queue<int> b = a;
  std::queue<int> og({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(og, a));
  EXPECT_TRUE(compare_queue(og, b));
}

TEST(queue_suite, test_empty) {
  s21::queue<int> a;
  s21::queue<int> b = a;
  EXPECT_TRUE(a.empty());
  EXPECT_TRUE(b.empty());
}

TEST(queue_suite, initialize_list) {
  s21::queue<int> test({-5, 0, 6, 7, 8124});
  std::queue<int> og({-5, 0, 6, 7, 8124});
  EXPECT_TRUE(compare_queue(og, test));
}

TEST(queue_suite, emplace_back) {
  s21::queue<int> test = s21::queue<int>();
  test.emplace_back(1, 2, 3, 4, 5);
  std::queue<int> og = std::queue<int>();
  og.push(1);
  og.push(2);
  og.push(3);
  og.push(4);
  og.push(5);
  EXPECT_TRUE(compare_queue(og, test));
}

// Queue end

// Stack start

void compare_stacks(s21::stack<int> &stack, std::stack<int> &ctrl) {
  while (stack.size() || ctrl.size()) {
    ASSERT_EQ(stack.top(), ctrl.top());
    stack.pop();
    ctrl.pop();
  }
}

TEST(stack, empty) {
  s21::stack<int> test;
  std::stack<int> orgn;
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
}

TEST(stack, init) {
  s21::stack<int> test({1, 2, 3});
  std::stack<int> orgn({1, 2, 3});
  EXPECT_EQ(test.size(), orgn.size());
  compare_stacks(test, orgn);
}

TEST(stack, init_empty) {
  s21::stack<int> test{};
  std::stack<int> orgn{};
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
}

TEST(stack, copy) {
  s21::stack<int> test({1, 2, 3});
  s21::stack<int> test_copy(test);
  std::stack<int> orgn({1, 2, 3});
  std::stack<int> orgn_copy(orgn);
  EXPECT_EQ(test.size(), orgn.size());
  compare_stacks(test, orgn);
  compare_stacks(test_copy, orgn_copy);
}

TEST(stack, copy_empty) {
  s21::stack<int> test{};
  s21::stack<int> test_copy(test);
  std::stack<int> orgn{};
  std::stack<int> orgn_copy(orgn);
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
  EXPECT_TRUE(test_copy.empty());
}

TEST(stack, move) {
  s21::stack<int> test({1, 2, 3});
  s21::stack<int> test_copy(std::move(test));
  std::stack<int> orgn({1, 2, 3});
  std::stack<int> orgn_copy(std::move(orgn));
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
  compare_stacks(test_copy, orgn_copy);
}

TEST(stack, move_empty) {
  s21::stack<int> test{};
  s21::stack<int> test_copy(std::move(test));
  std::stack<int> orgn{};
  std::stack<int> orgn_copy(std::move(orgn));
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
  EXPECT_TRUE(test_copy.empty());
}

TEST(stack, operator) {
  s21::stack<int> test({1, 2, 3});
  s21::stack<int> test_copy = std::move(test);
  std::stack<int> orgn({1, 2, 3});
  std::stack<int> orgn_copy = std::move(orgn);
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_TRUE(test.empty());
  compare_stacks(test_copy, orgn_copy);
}

TEST(stack, top_pop) {
  s21::stack<int> test({1, 2, 3});
  std::stack<int> orgn({1, 2, 3});
  EXPECT_EQ(test.top(), orgn.top());
  test.pop();
  orgn.pop();
  EXPECT_EQ(test.top(), orgn.top());
  test.pop();
  orgn.pop();
  EXPECT_EQ(test.top(), orgn.top());
  test.pop();
  orgn.pop();
  EXPECT_TRUE(test.empty());
}

TEST(stack, push) {
  s21::stack<int> test;
  std::stack<int> orgn;
  test.push(1);
  orgn.push(1);
  test.push(2);
  orgn.push(2);
  EXPECT_EQ(test.size(), orgn.size());
  compare_stacks(test, orgn);
}

TEST(stack, swap) {
  s21::stack<int> test({1, 2, 3});
  s21::stack<int> test_swap({3, 1, 2});
  test_swap.swap(test);
  std::stack<int> orgn({1, 2, 3});
  std::stack<int> orgn_swap({3, 1, 2});
  orgn_swap.swap(orgn);
  EXPECT_EQ(test.size(), orgn.size());
  EXPECT_EQ(test_swap.size(), orgn_swap.size());
  compare_stacks(test_swap, orgn_swap);
  compare_stacks(test, orgn);
}

TEST(stack_test, stack_constructor_test) {
  s21::stack<int> stack = s21::stack<int>();

  ASSERT_EQ(stack.empty(), true);
}

TEST(stack_test, stack_constructor_initiazlizer_list_test) {
  s21::stack<int> stack = s21::stack<int>{10, 20};
  ASSERT_EQ(stack.empty(), false);
  ASSERT_EQ(stack.top(), 20);
}

TEST(stack_test, stack_constructor_copy_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.push(12);
  s21::stack<int> stack2 = s21::stack<int>(stack);
  ASSERT_EQ(stack2.empty(), false);
  ASSERT_EQ(stack2.top(), 12);
}

TEST(stack_test, stack_constructor_move_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.push(12);
  s21::stack<int> stack2 = std::move(stack);
  ASSERT_EQ(stack2.empty(), false);
  ASSERT_EQ(stack2.top(), 12);
}

TEST(stack_test, stack_empty_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  ASSERT_EQ(stack.empty(), false);
}

TEST(stack_test, stack_push_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  ASSERT_EQ(stack.top(), 10);
}

TEST(stack_test, stack_pop_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.pop();
  ASSERT_EQ(stack.top(), 5);
}

TEST(stack_test, stack_size_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack.push(21);
  stack.push(456);
  stack.pop();
  ASSERT_EQ(stack.size(), 3);
}

TEST(stack_test, stack_top_test) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack.pop();
  ASSERT_EQ(stack.top(), 52);
}

TEST(stack_test, stack_swap_test) {
  s21::stack<int> stack = s21::stack<int>();
  s21::stack<int> stack2 = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack2.push(12);
  stack2.push(11);
  stack.swap(stack2);
  ASSERT_EQ(stack.top(), 11);
  ASSERT_EQ(stack2.top(), 3);
}

TEST(stack_test, stack_emplace_test) {
  s21::stack<int> stack = s21::stack<int>();

  stack.emplace_front(1, 2, 3, 4, 5, 11);

  ASSERT_EQ(stack.top(), 11);
  ASSERT_EQ(stack.size(), 6);
}

// Stack end

// Vector start

template <typename T>
testing::AssertionResult compare_vector(const std::vector<T> &og,
                                        const s21::vector<T> copy) {
  bool pass = true;
  testing::AssertionResult res = testing::AssertionSuccess() << "Vectors match";
  for (int i = 0; pass && i < (int)og.size(); ++i) {
    if (og[i] != copy[i]) {
      pass = false;
      res = testing::AssertionFailure()
            << og[i] << " != " << copy[i] << " at " << i;
    }
  }

  return res;
}

TEST(vector_suite, empty) {
  s21::vector<int> test;
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  int *start = test.begin();
  int *end = test.end();
  EXPECT_EQ(start, end);
}

TEST(vector_suite, pushback) {
  s21::vector<int> test;
  std::vector<int> og;
  test.push_back(420);
  test.push_back(123);
  test.push_back(-1245);
  test.push_back(-1024);
  og.push_back(420);
  og.push_back(123);
  og.push_back(-1245);
  og.push_back(-1024);
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
}

TEST(vector_suite, init_list) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> og({1, 2, -6, 5, 256, 1026});
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
}

TEST(vector_suite, init_list_empty) {
  s21::vector<int> test({});
  std::vector<int> og({});
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
}

TEST(vector_suite_THROW, access_tests) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> og({1, 2, -6, 5, 256, 1026});
  EXPECT_EQ(test.back(), og.back());
  EXPECT_EQ(test.front(), og.front());
  EXPECT_EQ(test.at(3), og.at(3));
  EXPECT_EQ(test[3], og[3]);
  EXPECT_ANY_THROW(test.at(12597));
  EXPECT_ANY_THROW(test.at(-124));
  int *test_begin = test.begin();
  int *test_end = test.end() - 1;
  int *test_data = test.data();
  auto og_begin = og.begin();
  auto og_end = og.end() - 1;
  auto og_data = og.data();
  EXPECT_EQ(*test_begin, *og_begin);
  EXPECT_EQ(*test_end, *og_end);
  EXPECT_EQ(test_begin, test_data);
  test_data++;
  og_data++;
  EXPECT_EQ(*test_data, *og_data);
}

TEST(vector_suite, max_size) {
  s21::vector<int> test_int;
  std::vector<int> og_int;
  EXPECT_EQ(test_int.max_size(), og_int.max_size());
  s21::vector<double> test_double;
  std::vector<double> og_double;
  EXPECT_EQ(test_double.max_size(), og_double.max_size());
}

TEST(vector_suite, popback_shrink_and_clear) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> og({1, 2, -6, 5, 256, 1026});
  test.pop_back();
  og.pop_back();
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
  test.pop_back();
  og.pop_back();
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
  test.shrink_to_fit();
  og.shrink_to_fit();
  EXPECT_TRUE(compare_vector(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
  test.clear();
  og.clear();
  EXPECT_TRUE(test.empty());
  EXPECT_TRUE(og.empty());
  EXPECT_EQ(test.size(), og.size());
  EXPECT_EQ(test.capacity(), og.capacity());
}

TEST(vector_suite, copy_construct) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  s21::vector<double> copy(test);
  for (size_t i = 0; i < test.size(); ++i) {
    EXPECT_EQ(test[i], copy[i]);
  }
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_EQ(copy.capacity(), 4);
}

TEST(vector_suite, copy_construct_empty) {
  s21::vector<double> test;
  s21::vector<double> copy(test);
  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_EQ(test.capacity(), copy.capacity());
}

TEST(vector_suite, move_construct) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  size_t size = test.size();
  size_t capacity = test.capacity();
  s21::vector<double> other(std::move(test));

  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(other.size(), size);
  EXPECT_EQ(other.capacity(), capacity);
  EXPECT_TRUE(compare_vector(og, other));
}

TEST(vector_suite, move_construct_empty) {
  s21::vector<double> test;
  size_t size = test.size();
  size_t capacity = test.capacity();
  s21::vector<double> other(std::move(test));

  EXPECT_TRUE(test.empty());
  EXPECT_TRUE(other.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(other.size(), size);
  EXPECT_EQ(other.capacity(), capacity);
}

TEST(vector_suite, move_construct_operator) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  size_t size = test.size();
  size_t capacity = test.capacity();
  s21::vector<double> other = std::move(test);

  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(other.size(), size);
  EXPECT_EQ(other.capacity(), capacity);
  EXPECT_TRUE(compare_vector(og, other));
}

TEST(vector_suite, swap) {
  s21::vector<double> a({5, 4.534, 123, 4554.43});
  std::vector<double> og_a({5, 4.534, 123, 4554.43});
  s21::vector<double> b({1245, 4.412412, 0.123});
  std::vector<double> og_b({1245, 4.412412, 0.123});
  a.swap(b);
  EXPECT_TRUE(compare_vector(og_a, b));
  EXPECT_TRUE(compare_vector(og_b, a));
}

TEST(vector_suite, swap_empty) {
  s21::vector<double> a({5, 4.534, 123, 4554.43});
  std::vector<double> og_a({5, 4.534, 123, 4554.43});
  s21::vector<double> b;
  std::vector<double> og_b;
  a.swap(b);
  EXPECT_TRUE(compare_vector(og_a, b));
  EXPECT_TRUE(compare_vector(og_b, a));
}

TEST(vector_suite, erase) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  auto test_ptr = test.begin() + 2;
  auto og_ptr = og.begin() + 2;
  test.erase(test_ptr);
  og.erase(og_ptr);
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, insert) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  auto test_ptr = test.begin() + 2;
  auto og_ptr = og.begin() + 2;
  auto test_new_ptr = test.insert(test_ptr, 69.42);
  auto og_new_ptr = og.insert(og_ptr, 69.42);
  EXPECT_EQ(*test_new_ptr, *og_new_ptr);
  EXPECT_EQ(*test_new_ptr, 69.42);
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, insert_end) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  auto test_ptr = test.end();
  auto og_ptr = og.end();
  auto test_new_ptr = test.insert(test_ptr, 69.42);
  auto og_new_ptr = og.insert(og_ptr, 69.42);
  EXPECT_EQ(*test_new_ptr, *og_new_ptr);
  EXPECT_EQ(*test_new_ptr, 69.42);
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, insert_empty) {
  s21::vector<double> test;
  std::vector<double> og;
  auto test_ptr = test.begin();
  auto og_ptr = og.begin();
  auto test_new_ptr = test.insert(test_ptr, 69.42);
  auto og_new_ptr = og.insert(og_ptr, 69.42);
  EXPECT_EQ(*test_new_ptr, *og_new_ptr);
  EXPECT_EQ(*test_new_ptr, 69.42);
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, reserve) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  test.reserve(15);
  og.reserve(15);
  EXPECT_EQ(test.capacity(), og.capacity());
  EXPECT_EQ(test.size(), og.size());
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, reserve_less) {
  s21::vector<double> test({5, 4.534, 123, 4554.43});
  std::vector<double> og({5, 4.534, 123, 4554.43});
  test.reserve(3);
  og.reserve(3);
  EXPECT_EQ(test.capacity(), og.capacity());
  EXPECT_EQ(test.size(), og.size());
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, reserve_empty) {
  s21::vector<double> test;
  std::vector<double> og;
  test.reserve(15);
  og.reserve(15);
  EXPECT_EQ(test.capacity(), og.capacity());
  EXPECT_EQ(test.size(), og.size());
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, construct_reserve) {
  s21::vector<double> test(20);
  std::vector<double> og(20);
  EXPECT_EQ(test.capacity(), og.capacity());
  EXPECT_EQ(test.size(), og.size());
}

TEST(vector_suite, emplace_back_empty) {
  s21::vector<int> test;
  std::vector<int> og;
  test.emplace_back(1, 2, 3, 4, 5);
  og.push_back(1);
  og.push_back(2);
  og.push_back(3);
  og.push_back(4);
  og.push_back(5);
  EXPECT_TRUE(compare_vector(og, test));
}

TEST(vector_suite, emplace_back) {
  s21::vector<int> test({1, 2, 3, 4, 1, 0});
  std::vector<int> og({1, 2, 3, 4, 1, 0});
  test.emplace_back(11, 2, 5, 1);
  og.emplace_back(11);
  og.emplace_back(2);
  og.emplace_back(5);
  og.emplace_back(1);
  EXPECT_TRUE(compare_vector(og, test));
}

// Vector

TEST(vector, empty) {
  s21::vector<int> test;
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(test.data(), nullptr);
  EXPECT_EQ(test.begin(), test.end());
}

TEST(vector, empty_zero) {
  s21::vector<int> test(0);
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(test.data(), nullptr);
  EXPECT_EQ(test.begin(), test.end());
}

TEST(vector_THROW, invalid) {
  EXPECT_THROW(s21::vector<int> test(-13), std::length_error);
  EXPECT_THROW(s21::vector<int> test(SIZE_MAX), std::length_error);
}

TEST(vector, init) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  EXPECT_FALSE(test.empty());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(*test.data(), *org.data());
}

TEST(vector, init_empty) {
  s21::vector<int> test({});
  std::vector<int> org({});
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.data(), nullptr);
  EXPECT_EQ(org.data(), nullptr);
}

TEST(vector, copy) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  s21::vector<int> copy(test);
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  std::vector<int> copy_org(org);
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_EQ(test.capacity(), copy.capacity());
  EXPECT_EQ(*test.data(), *copy.data());
  EXPECT_EQ(copy_org.size(), copy.size());
  EXPECT_EQ(copy_org.capacity(), copy.capacity());
  EXPECT_EQ(*copy_org.data(), *copy.data());
  EXPECT_FALSE(test.empty());
}

TEST(vector, copy_empty) {
  s21::vector<int> test({});
  s21::vector<int> copy(test);
  std::vector<int> org({});
  std::vector<int> copy_org(org);
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_EQ(test.size(), copy.capacity());
  EXPECT_EQ(test.data(), copy.data());
  EXPECT_EQ(copy_org.size(), copy.size());
  EXPECT_EQ(copy_org.capacity(), copy.capacity());
  EXPECT_EQ(copy_org.data(), copy.data());
  EXPECT_TRUE(test.empty());
}

TEST(vector, move) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  s21::vector<int> move(std::move(test));
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  std::vector<int> move_org(std::move(org));
  EXPECT_EQ(move.size(), move_org.size());
  EXPECT_EQ(move.capacity(), move_org.capacity());
  EXPECT_EQ(*move.data(), *move_org.data());
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.capacity(), 0);
  EXPECT_EQ(test.data(), nullptr);
  EXPECT_TRUE(test.empty());
  EXPECT_FALSE(move.empty());
}

TEST(vector, move_empty) {
  s21::vector<int> test({});
  s21::vector<int> move(std::move(test));
  std::vector<int> org({});
  std::vector<int> move_org(std::move(org));
  EXPECT_EQ(move.size(), move_org.size());
  EXPECT_EQ(move.capacity(), move_org.capacity());
  EXPECT_EQ(move.data(), move_org.data());
  EXPECT_TRUE(test.empty());
  EXPECT_TRUE(move.empty());
}

TEST(vector, operator_assignment) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  s21::vector<int> oper_assig = std::move(test);
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  std::vector<int> oper_assig_org = std::move(org);
  EXPECT_EQ(oper_assig.size(), oper_assig_org.size());
  EXPECT_EQ(oper_assig.capacity(), oper_assig_org.capacity());
  EXPECT_EQ(*oper_assig.data(), *oper_assig_org.data());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.data(), org.data());
  EXPECT_TRUE(test.empty());
}

TEST(vector, at) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  EXPECT_EQ(test.at(0), org.at(0));
  EXPECT_EQ(test.at(5), org.at(5));
  EXPECT_EQ(test[0], org[0]);
  EXPECT_EQ(test[5], org[5]);
}

TEST(vector_THROW, at) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  EXPECT_THROW(test.at(6), std::out_of_range);
}

TEST(vector, front_back) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  EXPECT_EQ(test.front(), org.front());
  EXPECT_EQ(test.back(), org.back());
}

TEST(vector, begin_end) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  s21::vector<int>::iterator test_it_b = test.begin();
  std::vector<int>::iterator org_it_b = org.begin();
  EXPECT_EQ(*test_it_b, *org_it_b);
  EXPECT_EQ(*++test_it_b, *++org_it_b);
  s21::vector<int>::iterator test_it_e = test.end();
  std::vector<int>::iterator org_it_e = org.end();
  EXPECT_EQ(*--test_it_e, *--org_it_e);
  EXPECT_EQ(*--test_it_e, *--org_it_e);
}

TEST(vector, swap) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  s21::vector<int> swap({8, 7, 5, 2, 18});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  std::vector<int> org_swap({8, 7, 5, 2, 18});
  test.swap(swap);
  org.swap(org_swap);
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_EQ(org_swap.size(), swap.size());
  EXPECT_EQ(org_swap.capacity(), swap.capacity());
  EXPECT_EQ(*org_swap.data(), *swap.data());
}

TEST(vector, swap_empty) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  s21::vector<int> swap({});
  std::vector<int> org({1, 2, -6, 5, 256, 1026});
  std::vector<int> org_swap({});
  test.swap(swap);
  org.swap(org_swap);
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.data(), org.data());
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(org_swap.size(), swap.size());
  EXPECT_EQ(org_swap.capacity(), swap.capacity());
  EXPECT_EQ(*org_swap.data(), *swap.data());
}

TEST(vector, max_size) {
  s21::vector<int> test;
  std::vector<int> org;
  EXPECT_EQ(test.max_size(), org.max_size());
}

TEST(vector, reserve) {
  s21::vector<int> test({3, 2, 1});
  std::vector<int> org({3, 2, 1});
  test.reserve(2);
  org.reserve(2);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  test.reserve(6);
  org.reserve(6);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  test.reserve(0);
  org.reserve(0);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_FALSE(test.empty());
}

TEST(vector, reserve_empty) {
  s21::vector<int> test;
  std::vector<int> org;
  test.reserve(2);
  org.reserve(2);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
}

TEST(vector_THROW, reserve) {
  s21::vector<int> test({3, 2, 1});
  std::vector<int> org({3, 2, 1});
  EXPECT_THROW(test.reserve(SIZE_MAX / sizeof(int)), std::length_error);
  EXPECT_THROW(org.reserve(SIZE_MAX / sizeof(int)), std::length_error);
}

TEST(vector, shrink_to_fit) {
  s21::vector<int> test({3, 2, 1});
  std::vector<int> org({3, 2, 1});
  test.reserve(5);
  org.reserve(5);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  test.shrink_to_fit();
  org.shrink_to_fit();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
}

TEST(vector, shrink_to_fit_empty) {
  s21::vector<int> test;
  std::vector<int> org;
  test.reserve(3);
  org.reserve(3);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
  test.shrink_to_fit();
  org.shrink_to_fit();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
}

TEST(vector, clean) {
  s21::vector<int> test({3, 2});
  std::vector<int> org({3, 2});
  test.clear();
  org.clear();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
  test.clear();
  org.clear();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
}

TEST(vector, insert) {
  s21::vector<int> test({3, 2, 3});
  std::vector<int> org({3, 2, 3});
  s21::vector<int>::iterator test_it2 = test.insert(test.begin() + 2, 4);
  std::vector<int>::iterator org_it2 = org.insert(org.begin() + 2, 4);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_EQ(*test_it2, *org_it2);
  s21::vector<int>::iterator test_it3 = test.insert(test.begin(), 3);
  std::vector<int>::iterator org_it3 = org.insert(org.begin(), 3);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_EQ(*test_it3, *org_it3);
}

TEST(vector, insert_empty) {
  s21::vector<int> test;
  std::vector<int> org;
  test.insert(test.end(), 2);
  org.insert(org.end(), 2);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_EQ(*test.begin(), *org.begin());
}

TEST(vector, erase) {
  s21::vector<int> test({3, 2});
  std::vector<int> org({3, 2});
  test.erase(test.begin() + 1);
  org.erase(org.begin() + 1);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  test.erase(test.begin());
  org.erase(org.begin());
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(*test.data(), *org.data());
  EXPECT_EQ(*test.begin(), *test.end());
}

TEST(vector, push_back) {
  s21::vector<int> test({3, 2, 4});
  std::vector<int> org({3, 2, 4});
  test.push_back(1);
  org.push_back(1);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test[test.size() - 1], org[org.size() - 1]);
  EXPECT_TRUE(compare_vector(org, test));
  test.clear();
  org.clear();
  test.push_back(1);
  org.push_back(1);
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test[test.size() - 1], org[org.size() - 1]);
  EXPECT_TRUE(compare_vector(org, test));
}

TEST(vector, pop_back) {
  s21::vector<int> test({3, 2});
  std::vector<int> org({3, 2});
  test.pop_back();
  org.pop_back();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_EQ(test[test.size() - 1], org[org.size() - 1]);
  test.pop_back();
  org.pop_back();
  EXPECT_EQ(test.capacity(), org.capacity());
  EXPECT_EQ(test.size(), org.size());
  EXPECT_TRUE(test.empty());
}

TEST(vector_suite, emplace) {
  s21::vector<int> test({1, 2, 3, 4, 1, 0});
  std::vector<int> og({1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 0});
  test.emplace(test.begin(), 1, 2, 3, 4, 5);
  EXPECT_TRUE(compare_vector(og, test));
}

// Vector end

// Map start

template <class Key, class T>
testing::AssertionResult compare_maps(std::map<Key, T> og,
                                      s21::map<Key, T> copy) {
  bool pass = true;
  testing::AssertionResult res = testing::AssertionSuccess() << "Maps match";
  if (og.size() != copy.size()) {
    res = testing::AssertionFailure()
          << "Sizes do not match " << og.size() << " != " << copy.size();
  }
  typename std::map<Key, T>::iterator iter = og.begin();
  typename std::map<Key, T>::iterator iter_end = og.end();
  while (pass && iter != iter_end) {
    if (copy.at(iter->first) != iter->second) {
      pass = false;
      res = testing::AssertionFailure()
            << " != " << iter->second << copy.at(iter->first) << " at "
            << iter->first;
    }
    ++iter;
  }
  return res;
}

TEST(map_suite, insert) {
  s21::map<int, double> test;
  test.insert(std::make_pair(2, 21.56));
  test.insert(1, 523.5);
  EXPECT_TRUE(test.insert(4, 3.241).second);
  EXPECT_FALSE(test.insert(1, 69).second);
  std::map<int, double> og;
  og.insert(std::make_pair(2, 21.56));
  og.insert(std::make_pair(1, 523.5));
  og.insert(std::make_pair(4, 3.241));
  EXPECT_TRUE(compare_maps(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_FALSE(test.empty());
}

TEST(map_suite, insert_or_assign) {
  s21::map<int, double> test;
  test.insert(std::make_pair(2, 21.56));
  test.insert(1, 523.5);
  EXPECT_TRUE(test.insert_or_assign(4, 3.241).second);
  test.insert_or_assign(1, 69);
  std::map<int, double> og;
  og.insert(std::make_pair(2, 21.56));
  og.insert(std::make_pair(1, 69));
  og.insert(std::make_pair(4, 3.241));
  EXPECT_TRUE(compare_maps(og, test));
  EXPECT_EQ(test.size(), og.size());
  EXPECT_FALSE(test.empty());
}

TEST(map_suite, init_list) {
  s21::map<int, double> test{
      {1, 12.34},
      {-2, 8923.23},
      {4, 847956},
      {4, 100},
  };
  std::map<int, double> og{
      {1, 12.34},
      {-2, 8923.23},
      {4, 847956},
      {4, 100},
  };
  EXPECT_TRUE(compare_maps(og, test));
  EXPECT_EQ(og.size(), test.size());
}

TEST(map_suite, at) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  EXPECT_EQ(og[15], test[15]);
  EXPECT_EQ(og[-2], test[-2]);
  EXPECT_EQ(og[3], test[3]);
  EXPECT_EQ(og.at(1), test.at(1));
  EXPECT_EQ(og.at(10), test.at(10));
}

TEST(map_suite_THROW, at2) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  EXPECT_THROW(test.at(6), std::out_of_range);
}

TEST(map_suite, copy_constructor) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> copy(test);
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_FALSE(copy.empty());
  EXPECT_TRUE(compare_maps(og, copy));
}

TEST(map_suite, move_constructor) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> copy(std::move(test));
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(copy.size(), og.size());
  EXPECT_TRUE(test.empty());
  EXPECT_FALSE(copy.empty());
  EXPECT_TRUE(compare_maps(og, copy));
}

TEST(map_suite, move_operator) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> copy = std::move(test);
  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(copy.size(), og.size());
  EXPECT_TRUE(test.empty());
  EXPECT_FALSE(copy.empty());
  EXPECT_TRUE(compare_maps(og, copy));
}

TEST(map_suite, contains) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  EXPECT_TRUE(test.contains(1));
  EXPECT_TRUE(test.contains(-2));
  EXPECT_TRUE(test.contains(10));
  EXPECT_TRUE(test.contains(5));
  EXPECT_FALSE(test.contains(0));
  EXPECT_FALSE(test.contains(29867));
  EXPECT_FALSE(test.contains(7));
}

TEST(map_suite, find) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  auto it_st = test.find(12);
  ASSERT_EQ(it_st, test.end());
}

TEST(map_suite, swap) {
  s21::map<int, double> test1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> test2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 847956}, {10, 1256},
  };
  std::map<int, double> og2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 847956}, {10, 1256},
  };
  test1.swap(test2);
  EXPECT_TRUE(compare_maps(og1, test2));
  EXPECT_TRUE(compare_maps(og2, test1));
}

TEST(map_suite, swap_with_self) {
  s21::map<int, double> test1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  test1.swap(test1);
  EXPECT_TRUE(compare_maps(og1, test1));
}

TEST(map_suite, swap_empty) {
  s21::map<int, double> test1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> test2;
  test1.swap(test2);
  EXPECT_TRUE(compare_maps(og1, test2));
  EXPECT_TRUE(test1.empty());
}

TEST(map_suite, merge1) {
  s21::map<int, double> test1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> test2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 42455}, {10, 111},
  };
  std::map<int, double> og1{
      {-2, 8923.23}, {1, 12.34},  {3, 333.33}, {4, 847956}, {5, 124.124},
      {6, 321.47},   {7, 651483}, {8, -512.3}, {10, 1256},
  };
  std::map<int, double> og2{
      {4, 42455},
      {10, 111},
  };
  test1.merge(test2);
  EXPECT_TRUE(compare_maps(og1, test1));
  EXPECT_TRUE(compare_maps(og2, test2));
  EXPECT_EQ(test1.size(), og1.size());
  EXPECT_EQ(test2.size(), og2.size());
  EXPECT_FALSE(test2.empty());
}

TEST(map_suite, merge_with_duplicates) {
  s21::map<int, double> test1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og1{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  s21::map<int, double> test2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 42455}, {10, 111},
  };
  std::map<int, double> og2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 42455}, {10, 111},
  };
  test1.merge(test2);
  og1.merge(og2);
  EXPECT_TRUE(compare_maps(og1, test1));
  EXPECT_TRUE(compare_maps(og2, test2));
  EXPECT_EQ(test1.size(), og1.size());
  EXPECT_EQ(test2.size(), og2.size());
  EXPECT_FALSE(test2.empty());
}

TEST(map_suite, merge_without_duplicates) {
  s21::map<int, double> test1{
      {1, 12.34},
      {-2, 8923.23},
      {5, 124.124},
      {3, 333.33},
  };
  std::map<int, double> og1{
      {1, 12.34},
      {-2, 8923.23},
      {5, 124.124},
      {3, 333.33},
  };
  s21::map<int, double> test2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 42455}, {10, 111},
  };
  std::map<int, double> og2{
      {7, 651483}, {6, 321.47}, {8, -512.3}, {4, 42455}, {10, 111},
  };
  test1.merge(test2);
  og1.merge(og2);
  EXPECT_TRUE(compare_maps(og1, test1));
  EXPECT_EQ(test1.size(), og1.size());
  EXPECT_EQ(test2.size(), og2.size());
  EXPECT_TRUE(test2.empty());
}

TEST(map_suite, clear) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  test.clear();
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(test.size(), 0);
}

TEST(map_suite, erase_and_iterators) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  test.erase(test.begin());
  og.erase(og.begin());
  auto iter = test.begin();
  auto og_iter = og.begin();
  ++iter;
  ++iter;
  ++og_iter;
  ++og_iter;
  test.erase(iter);
  og.erase(og_iter);
  iter = test.end();
  og_iter = og.end();
  --iter;
  --og_iter;
  test.erase(iter);
  og.erase(og_iter);
  EXPECT_TRUE(compare_maps(og, test));
}

TEST(map_suite, erase_2) {
  s21::map<int, double> test{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  std::map<int, double> og{
      {1, 12.34}, {-2, 8923.23}, {4, 847956},
      {10, 1256}, {5, 124.124},  {3, 333.33},
  };
  test.erase(test.begin());
  og.erase(og.begin());
  auto iter = test.begin();
  auto og_iter = og.begin();
  ++iter;
  ++iter;
  ++iter;
  ++og_iter;
  ++og_iter;
  ++og_iter;
  test.erase(iter);
  og.erase(og_iter);
  EXPECT_TRUE(compare_maps(og, test));
}

TEST(map_suite, operator_minus) {
  s21::map<int, double> test{
      {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6},
  };
  auto iter = test.end();
  --iter;
  int count = 6;
  while (iter != test.begin()) {
    EXPECT_EQ(*iter, test[count]);
    --count;
    --iter;
  }
}

TEST(map_suite, max_size) {
  std::map<int, int> std_int;
  s21::map<int, int> s21_int;
  std::map<double, double> std_double;
  s21::map<double, double> s21_double;

  ASSERT_EQ(std_int.max_size(), s21_int.max_size());
  ASSERT_EQ(std_double.max_size(), s21_double.max_size());
}

TEST(map_suite, emplace) {
  s21::map<int, int> test = s21::map<int, int>();

  auto res = test.emplace(std::pair<int, int>(1, 1), std::pair<int, int>(2, 15),
                          std::pair<int, int>(3, 12), std::pair<int, int>(4, 4),
                          std::pair<int, int>(1, 245));
  ASSERT_EQ(test.size(), 4);
  ASSERT_EQ(test.contains(1), true);
  EXPECT_FALSE(res[4].second);
  EXPECT_TRUE(res[1].second);
  EXPECT_EQ(*(res[1].first), 15);
}

// Map end

// Set start

template <class T>
testing::AssertionResult compare_sets(std::set<T> og, s21::set<T> copy) {
  bool pass = true;
  testing::AssertionResult res = testing::AssertionSuccess() << "Keys match";
  if (og.size() != copy.size()) {
    res = testing::AssertionFailure()
          << "Sizes do not match " << og.size() << " != " << copy.size();
  }
  typename std::set<T>::iterator iter = og.begin();
  typename std::set<T>::iterator iter_end = og.end();
  while (pass && iter != iter_end) {
    if (!copy.contains(*iter)) {
      pass = false;
      res = testing::AssertionFailure() << *iter << " Not found in s21_set";
    }
    ++iter;
  }
  return res;
}

TEST(set_test, set_constructor_test) {
  s21::set<int> st = s21::set<int>();

  ASSERT_EQ(st.empty(), true);
}

TEST(set_test, set_constructor_value_item_test) {
  s21::set<int> st = s21::set<int>({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  std::set<int> og = std::set<int>({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});

  EXPECT_FALSE(st.empty());
  ASSERT_EQ(st.size(), og.size());
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_constructor_copy_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og = std::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = s21::set<int>(st);

  EXPECT_TRUE(compare_sets(og, st2));
  EXPECT_FALSE(st2.empty());
  ASSERT_EQ(st2.size(), st.size());
}

TEST(set_test, set_constructor_move_operator) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og = std::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = std::move(st);

  EXPECT_FALSE(st2.empty());
  EXPECT_TRUE(st.empty());
  EXPECT_TRUE(compare_sets(og, st2));
}

TEST(set_test, set_constructor_move_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og = std::set<int>({1, 2, 3, 4});
  s21::set<int> st2(std::move(st));

  EXPECT_FALSE(st2.empty());
  EXPECT_TRUE(st.empty());
  EXPECT_TRUE(compare_sets(og, st2));
}

TEST(set_test, set_operator_assignment_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = st;

  ASSERT_EQ(st2.empty(), false);
}

TEST(set_test, set_iterator_begin_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  auto it = st.end();
  --it;
  --it;
  --it;
  --it;

  ASSERT_EQ(it.ptr_, st.begin().ptr_);
}

TEST(set_test, set_iterator_end_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  auto it = st.begin();
  ++it;
  ++it;
  ++it;
  ++it;

  ASSERT_EQ(it.ptr_, st.end().ptr_);
}

TEST(set_test, set_empty_test) {
  s21::set<int> st = s21::set<int>({});

  ASSERT_EQ(st.empty(), true);
}

TEST(set_test, set_size_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  ASSERT_EQ(st.size(), 4);
}

TEST(set_test, set_insert_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og({1, 2, 3, 4});

  st.insert(7);
  og.insert(7);
  st.insert(69);
  og.insert(69);
  st.insert(7);
  og.insert(7);
  auto st_res = st.insert(420);
  auto og_res = og.insert(420);
  ASSERT_EQ(st.size(), og.size());
  EXPECT_EQ(*st_res.first, *og_res.first);
  EXPECT_TRUE(st_res.second);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_insert_test_2) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  auto res = st.insert(1);
  EXPECT_EQ(*res.first, 1);
  EXPECT_FALSE(res.second);
}

TEST(set_test, set_insert_empty) {
  s21::set<int> st;
  std::set<int> og;
  auto res = st.insert(1);
  auto res_og = og.insert(1);
  EXPECT_EQ(*res.first, *res_og.first);
  EXPECT_EQ(res.second, res_og.second);
  st.insert(135);
  og.insert(135);
  st.insert(54);
  og.insert(54);
  og.insert(-10);
  st.insert(-10);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7});
  auto iter = st.begin();
  st.erase(iter);

  std::set<int> og({1, 2, 3, 4, 5, 6, 7});
  auto og_it = og.begin();
  og.erase(og_it);
  compare_sets(og, st);
}

TEST(set_test, set_erase_test2) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4, 5, 6, 7});
  auto iter = st.begin();
  ++iter;
  st.erase(iter);
  ASSERT_EQ(st.size(), 6);

  std::set<int> og({1, 2, 3, 4, 5, 6, 7});
  auto og_it = og.begin();
  ++og_it;
  og.erase(og_it);
  compare_sets(og, st);
}

TEST(set_test, set_erase_test3) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7, 8});
  auto it = st.end();
  --it;
  --it;
  --it;
  --it;
  --it;
  --it;
  st.erase(it);

  std::set<int> og({1, 2, 3, 4, 5, 6, 7, 8});
  auto og_it = og.end();
  --og_it;
  --og_it;
  --og_it;
  --og_it;
  --og_it;
  --og_it;
  og.erase(og_it);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test4) {
  s21::set<int> st({1, 2, 3, 4, 5, 1, 2, 3});
  auto it1 = st.begin();
  ++it1;
  ++it1;
  ++it1;
  st.erase(it1);

  auto it2 = st.begin();
  st.erase(it2);

  auto it3 = st.begin();
  ++it3;
  st.erase(it3);

  auto it4 = st.begin();
  ++it4;
  st.erase(it4);

  std::set<int> og({1, 2, 3, 4, 5, 1, 2, 3});
  auto og_it1 = og.begin();
  ++og_it1;
  ++og_it1;
  ++og_it1;
  og.erase(og_it1);

  auto og_it2 = og.begin();
  og.erase(og_it2);

  auto og_it3 = og.begin();
  ++og_it3;
  og.erase(og_it3);

  auto og_it4 = og.begin();
  ++og_it4;
  og.erase(og_it4);

  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test5) {
  s21::set<int> st({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto it = st.begin();
  ++it;
  ++it;
  ++it;

  st.erase(it);

  std::set<int> og({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto og_it = og.begin();
  ++og_it;
  ++og_it;
  ++og_it;

  og.erase(og_it);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test6) {
  s21::set<int> st({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto it = st.begin();
  ++it;
  ++it;
  ++it;
  ++it;

  st.erase(it);

  std::set<int> og({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto og_it = og.begin();
  ++og_it;
  ++og_it;
  ++og_it;
  ++og_it;

  og.erase(og_it);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test7) {
  s21::set<int> st({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto it = st.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;

  st.erase(it);

  std::set<int> og({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20});
  auto og_it = og.begin();
  ++og_it;
  ++og_it;
  ++og_it;
  ++og_it;
  ++og_it;

  og.erase(og_it);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_erase_test8) {
  s21::set<int> st({10, 15, 5, 3, 4, 17, 19, 16, 2, 1, 20, 13, 11, 12, 14});

  st.erase(st.find(5));
  st.erase(st.find(1));
  st.erase(st.find(16));
  st.erase(st.find(20));
  st.erase(st.find(3));
  st.erase(st.find(4));
  st.erase(st.find(17));
  st.erase(st.find(15));
  st.erase(st.find(19));
  st.erase(st.find(10));
  st.erase(st.find(12));
  st.erase(st.find(13));
  st.erase(st.find(2));
  st.erase(st.find(11));
  st.erase(st.find(14));

  ASSERT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
}

TEST(set_test, set_clear_test) {
  s21::set<int> st({1, 2, 3, 4});

  st.clear();

  ASSERT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
}

TEST(set_test, set_swap_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = s21::set<int>({1, 2, 3, 4, 5, 6, 7});
  std::set<int> og = std::set<int>({1, 2, 3, 4});
  std::set<int> og2 = std::set<int>({1, 2, 3, 4, 5, 6, 7});

  st.swap(st2);

  ASSERT_EQ(st.size(), og2.size());
  ASSERT_EQ(st2.size(), og.size());
  EXPECT_TRUE(compare_sets(og, st2));
  EXPECT_TRUE(compare_sets(og2, st));
}

TEST(set_test, set_swap_self) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og({1, 2, 3, 4});
  st.swap(st);

  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_merge_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = s21::set<int>({5, 6, 7});

  std::set<int> og = std::set<int>({1, 2, 3, 4});
  std::set<int> og2 = std::set<int>({5, 6, 7});

  st.merge(st2);
  og.merge(og2);

  EXPECT_TRUE(st2.empty());
  ASSERT_EQ(st.size(), og.size());
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_merge_test2) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = s21::set<int>({1, 3, 9, 8});

  std::set<int> og = std::set<int>({1, 2, 3, 4});
  std::set<int> og2 = std::set<int>({1, 3, 9, 8});

  st.merge(st2);
  og.merge(og2);

  ASSERT_EQ(st.size(), og.size());
  ASSERT_EQ(st2.size(), og2.size());
  EXPECT_TRUE(compare_sets(og, st));
  EXPECT_TRUE(compare_sets(og2, st2));
}

TEST(set_test, set_merge_self) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  std::set<int> og = std::set<int>({1, 2, 3, 4});

  st.merge(st);
  ASSERT_EQ(st.size(), og.size());
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_merge_test3) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  s21::set<int> st2 = s21::set<int>({1, 3, 9, 8});

  std::set<int> og = std::set<int>({1, 2, 3, 4, 8, 9});
  std::set<int> og2 = std::set<int>({1, 3});

  st.merge(st2);

  ASSERT_EQ(st.size(), og.size());
  ASSERT_EQ(st2.size(), og2.size());
  EXPECT_TRUE(compare_sets(og, st));
  EXPECT_TRUE(compare_sets(og2, st2));
}

TEST(set_test, set_merge_test4) {
  s21::set<int> st = s21::set<int>({1, 2, 5, 6});
  s21::set<int> st2 = s21::set<int>({3, 4, 9, 8});

  std::set<int> og = std::set<int>({1, 2, 3, 4, 5, 6, 8, 9});
  std::set<int> og2 = std::set<int>({});

  st.merge(st2);

  ASSERT_EQ(st.size(), og.size());
  ASSERT_EQ(st2.size(), og2.size());
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_find_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  auto it = st.find(1);

  ASSERT_EQ(it.ptr_, st.begin().ptr_);
  ASSERT_EQ(*it, 1);
}

TEST(set_test, set_find_test_2) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});
  auto it_st = st.find(12);
  ASSERT_EQ(it_st, st.end());
}

TEST(set_test, set_contains_test) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  ASSERT_EQ(st.contains(1), true);
}

TEST(set_test, set_contains_test_2) {
  s21::set<int> st = s21::set<int>({1, 2, 3, 4});

  ASSERT_EQ(st.contains(56), false);
}

TEST(set_test, max_size) {
  std::set<int> std_int;
  s21::set<int> s21_int;
  std::set<double> std_double;
  s21::set<double> s21_double;

  ASSERT_EQ(std_int.max_size(), s21_int.max_size());
  ASSERT_EQ(std_double.max_size(), s21_double.max_size());
}

TEST(set_test, set_emplace_empty) {
  s21::set<int> st = s21::set<int>();
  auto test = st.emplace(1, 2, 3, 4, 1);

  std::set<int> og({1, 2, 3, 4});

  ASSERT_EQ(st.size(), 4);
  ASSERT_EQ(st.contains(4), true);
  EXPECT_TRUE(test[0].second);
  EXPECT_FALSE(test[4].second);
  EXPECT_EQ(*test[1].first, 2);
  EXPECT_TRUE(compare_sets(og, st));
}

TEST(set_test, set_emplace) {
  s21::set<int> st({1, 2, 8, 4, 5});
  auto test = st.emplace(1, 2, 3, 4, 5, 6, 7);

  std::set<int> og({1, 2, 8, 4, 5, 3, 6, 7});

  ASSERT_EQ(st.size(), 8);
  ASSERT_EQ(st.contains(7), true);
  EXPECT_FALSE(test[1].second);
  EXPECT_TRUE(test[2].second);
  EXPECT_EQ(*test[1].first, 2);
  EXPECT_TRUE(compare_sets(og, st));
}

// Set end

// Multiset start

template <class T>
testing::AssertionResult compare_multisets(std::multiset<T> og,
                                           s21::multiset<T> copy) {
  testing::AssertionResult res = testing::AssertionSuccess() << "Keys match";
  typename std::multiset<T>::iterator iter = og.begin();
  typename std::multiset<T>::iterator iter_end = og.end();
  if (og.size() != copy.size()) {
    res = testing::AssertionFailure()
          << "Sizes differ " << og.size() << " != " << copy.size();
  } else {
    bool pass = true;
    while (pass && iter != iter_end) {
      if (copy.count(*iter) != og.count(*iter)) {
        pass = false;
        res = testing::AssertionFailure()
              << *iter << " Not found in s21_multiset";
      }
      ++iter;
    }
  }
  return res;
}

TEST(multiset_test, set_erase_test4) {
  s21::multiset<int> st({1, 2, 3, 4, 5, 1, 2, 3, 3, 3, 3, 3, 3});

  st.erase(st.find(3));
  st.erase(st.find(1));
  st.erase(st.find(4));
  st.erase(st.find(2));
  st.erase(st.find(2));
  st.erase(st.find(3));
  st.erase(st.find(3));
  st.erase(st.find(3));
  st.erase(st.find(3));
  st.erase(st.find(3));
  st.erase(st.find(3));
  st.erase(st.find(5));
  st.erase(st.find(1));

  ASSERT_EQ(st.empty(), true);
}

TEST(multiset_test, multiset_constructor_test) {
  s21::multiset<int> mst = s21::multiset<int>();

  ASSERT_EQ(mst.empty(), true);
}

TEST(multiset_test, multiset_constructor_value_test) {
  s21::multiset<int> mst = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});

  EXPECT_FALSE(mst.empty());
  ASSERT_EQ(mst.size(), og.size());
  EXPECT_TRUE(compare_multisets(og, mst));
}

TEST(multiset_test, same_values_init) {
  s21::multiset<int> mst({1, 1, 1, 4});
  std::multiset<int> og({1, 1, 1, 4});

  EXPECT_FALSE(mst.empty());
  EXPECT_TRUE(compare_multisets(og, mst));
}

TEST(multiset_test, same_values_insert) {
  s21::multiset<int> mst;
  std::multiset<int> og;

  mst.insert(1);
  mst.insert(3);
  auto it1 = mst.insert(0);
  mst.insert(5);
  mst.insert(0);
  auto it2 = mst.insert(0);

  size_t count = 0;
  while (*it1 == 0) {
    ++count;
    ++it1;
  }
  EXPECT_EQ(count, 3);
  EXPECT_EQ(*it2, 0);

  og.insert(1);
  og.insert(3);
  og.insert(0);
  og.insert(5);
  og.insert(0);
  og.insert(0);

  EXPECT_FALSE(mst.empty());
  EXPECT_TRUE(compare_multisets(og, mst));
}

TEST(multiset_test, low_up_bound) {
  s21::multiset<int> mst({0, 0, 0, 1, 3, 3, 3, 5});
  std::multiset<int> og({0, 0, 0, 1, 3, 3, 3, 5});

  auto mst_low = mst.lower_bound(3);
  auto mst_up = mst.upper_bound(3);

  auto og_low = og.lower_bound(3);
  auto og_up = og.upper_bound(3);

  EXPECT_EQ(*mst_low, *og_low);
  EXPECT_EQ(*mst_up, *og_up);

  ++mst_low;
  ++og_low;
  EXPECT_EQ(*mst_low, *og_low);
  ++mst_low;
  ++og_low;
  EXPECT_EQ(*mst_low, *og_low);
  ++mst_low;
  ++og_low;
  EXPECT_EQ(*mst_low, *og_low);
  --mst_up;
  --og_up;
  EXPECT_EQ(*mst_up, *og_up);
  --mst_up;
  --og_up;
  EXPECT_EQ(*mst_up, *og_up);
  --mst_up;
  --og_up;
  EXPECT_EQ(*mst_up, *og_up);
  --mst_up;
  --og_up;
  EXPECT_EQ(*mst_up, *og_up);
}

TEST(multiset_test, low_up_bound_ne) {
  s21::multiset<int> mst;
  std::multiset<int> og;

  mst.insert(1);
  mst.insert(3);
  mst.insert(0);
  mst.insert(5);
  mst.insert(0);
  mst.insert(0);

  og.insert(1);
  og.insert(3);
  og.insert(0);
  og.insert(5);
  og.insert(0);
  og.insert(0);

  auto mst_low = mst.lower_bound(7);
  auto mst_up = mst.upper_bound(7);

  auto og_low = og.lower_bound(7);
  auto og_up = og.upper_bound(7);

  --mst_low;
  --og_low;

  EXPECT_EQ(*mst_low, *og_low);
  --mst_up;
  --og_up;
  EXPECT_EQ(*mst_up, *og_up);
}

TEST(multiset_test, equal_range) {
  s21::multiset<int> mst;

  mst.insert(1);
  mst.insert(3);
  mst.insert(0);
  mst.insert(5);
  mst.insert(0);
  mst.insert(0);

  auto iters = mst.equal_range(0);

  size_t count = 0;
  while (*iters.first == 0) {
    ++count;
    ++iters.first;
  }
  EXPECT_EQ(count, 3);

  EXPECT_EQ(*iters.second, 1);
  --iters.second;
  EXPECT_EQ(*iters.second, 0);
}

TEST(multiset_test, equal_range_non_existing) {
  s21::multiset<int> mst;
  std::multiset<int> og;

  mst.insert(1);
  mst.insert(3);
  mst.insert(0);
  mst.insert(5);
  mst.insert(0);
  mst.insert(0);

  og.insert(1);
  og.insert(3);
  og.insert(0);
  og.insert(5);
  og.insert(0);
  og.insert(0);

  auto mst_it = mst.equal_range(9867234);
  auto og_it = og.equal_range(9867234);
  --mst_it.first;
  --mst_it.second;
  --og_it.first;
  --og_it.second;
  EXPECT_EQ(*mst_it.first, *og_it.first);
  EXPECT_EQ(*mst_it.second, *og_it.second);
}

TEST(multiset_test, count) {
  s21::multiset<int> mst({1, 1, 1, 6, 3, 6, 9});
  std::multiset<int> og({1, 1, 1, 6, 3, 6, 9});

  EXPECT_EQ(mst.count(1), og.count(1));
  EXPECT_EQ(mst.count(6), og.count(6));
  EXPECT_EQ(mst.count(9), og.count(9));
  EXPECT_EQ(mst.count(69), og.count(69));
}

TEST(multiset_test, count_empty) {
  s21::multiset<int> mst;
  std::multiset<int> og;

  EXPECT_EQ(mst.count(1), og.count(1));
  EXPECT_EQ(mst.count(6), og.count(6));
  EXPECT_EQ(mst.count(9), og.count(9));
  EXPECT_EQ(mst.count(69), og.count(69));
}

TEST(multiset_test, set_constructor_test) {
  s21::multiset<int> st = s21::multiset<int>();

  ASSERT_EQ(st.empty(), true);
}

TEST(multiset_test, set_constructor_value_item_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});

  EXPECT_FALSE(st.empty());
  ASSERT_EQ(st.size(), og.size());
  EXPECT_TRUE(compare_multisets(og, st));
}

TEST(multiset_test, set_constructor_copy_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = s21::multiset<int>(st);

  EXPECT_TRUE(compare_multisets(og, st2));
  EXPECT_FALSE(st2.empty());
  ASSERT_EQ(st2.size(), st.size());
}

TEST(multiset_test, set_constructor_move_operator) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = std::move(st);

  EXPECT_FALSE(st2.empty());
  EXPECT_TRUE(st.empty());
  EXPECT_TRUE(compare_multisets(og, st2));
}

TEST(multiset_test, set_constructor_move_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2(std::move(st));

  EXPECT_FALSE(st2.empty());
  EXPECT_TRUE(st.empty());
  EXPECT_TRUE(compare_multisets(og, st2));
}

TEST(multiset_test, set_operator_assignment_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = st;

  ASSERT_EQ(st2.empty(), false);
}

TEST(multiset_test, set_iterator_begin_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  auto it = st.end();
  --it;
  --it;
  --it;
  --it;

  ASSERT_EQ(it.ptr_, st.begin().ptr_);
}

TEST(multiset_test, set_iterator_end_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  auto it = st.begin();
  ++it;
  ++it;
  ++it;
  ++it;

  ASSERT_EQ(it.ptr_, st.end().ptr_);
}

TEST(multiset_test, set_empty_test) {
  s21::multiset<int> st = s21::multiset<int>();

  ASSERT_EQ(st.empty(), true);
}

TEST(multiset_test, set_size_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  ASSERT_EQ(st.size(), 4);
}

TEST(multiset_test, set_insert_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og({1, 2, 3, 4});

  st.insert(7);
  og.insert(7);
  st.insert(69);
  og.insert(69);
  auto st_res = st.insert(420);
  auto og_res = og.insert(420);
  ASSERT_EQ(st.size(), og.size());
  EXPECT_EQ(*st_res, *og_res);
  EXPECT_TRUE(compare_multisets(og, st));
}

TEST(multiset_test, set_insert_test_2) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  auto res = st.insert(1);
  EXPECT_EQ(*res, 1);
}

TEST(multiset_test, set_insert_empty) {
  s21::multiset<int> st;
  std::multiset<int> og;
  auto res = st.insert(1);
  auto res_og = og.insert(1);
  EXPECT_EQ(*res, *res_og);
  st.insert(135);
  og.insert(135);
  st.insert(54);
  og.insert(54);
  og.insert(-10);
  st.insert(-10);
  EXPECT_TRUE(compare_multisets(og, st));
}

TEST(multiset_test, set_erase_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4, 5, 6, 7});
  auto iter = st.begin();
  ++iter;
  st.erase(iter);
  ASSERT_EQ(st.size(), 6);
}

TEST(multiset_test, set_clear_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  st.clear();

  ASSERT_EQ(st.size(), 0);
  EXPECT_TRUE(st.empty());
}

TEST(multiset_test, set_swap_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = s21::multiset<int>({1, 2, 3, 4, 5, 6, 7});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og2 = std::multiset<int>({1, 2, 3, 4, 5, 6, 7});

  st.swap(st2);

  ASSERT_EQ(st.size(), og2.size());
  ASSERT_EQ(st2.size(), og.size());
  EXPECT_TRUE(compare_multisets(og, st2));
  EXPECT_TRUE(compare_multisets(og2, st));
}

TEST(multiset_test, set_swap_self) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og({1, 2, 3, 4});
  st.swap(st);

  EXPECT_TRUE(compare_multisets(og, st));
}

TEST(multiset_test, set_merge_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = s21::multiset<int>({5, 6, 7});

  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og2 = std::multiset<int>({5, 6, 7});

  st.merge(st2);
  og.merge(og2);

  EXPECT_TRUE(st2.empty());
  ASSERT_EQ(st.size(), og.size());
  EXPECT_TRUE(compare_multisets(og, st));
}

TEST(multiset_test, set_merge_test2) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  s21::multiset<int> st2 = s21::multiset<int>({1, 3, 9, 8});

  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og2 = std::multiset<int>({1, 3, 9, 8});

  st.merge(st2);
  og.merge(og2);

  ASSERT_EQ(st.size(), og.size());
  ASSERT_EQ(st2.size(), og2.size());
  EXPECT_TRUE(compare_multisets(og, st));
  EXPECT_TRUE(st2.empty());
}

TEST(multiset_test, set_find_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});
  std::multiset<int> og = std::multiset<int>({1, 2, 3, 4});

  auto it_st = st.find(5);
  --it_st;
  auto it_og = og.find(5);
  --it_og;
  ASSERT_EQ(*it_st, *it_og);

  auto it = st.find(1);

  ASSERT_EQ(it.ptr_, st.begin().ptr_);
  ASSERT_EQ(*it, 1);
}

TEST(multiset_test, set_contains_test) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  ASSERT_EQ(st.contains(1), true);
}

TEST(multiset_test, set_contains_test_2) {
  s21::multiset<int> st = s21::multiset<int>({1, 2, 3, 4});

  ASSERT_EQ(st.contains(56), false);
}

TEST(multiset_test, max_size) {
  std::multiset<int> std_int;
  s21::multiset<int> s21_int;
  std::multiset<double> std_double;
  s21::multiset<double> s21_double;

  ASSERT_EQ(std_int.max_size(), s21_int.max_size());
  ASSERT_EQ(std_double.max_size(), s21_double.max_size());
}

TEST(multiset_test, set_emplace_empty) {
  s21::multiset<int> st = s21::multiset<int>();
  auto test = st.emplace(1, 2, 3, 4, 1);

  std::multiset<int> og({1, 2, 3, 4, 1});

  ASSERT_EQ(st.size(), 5);
  ASSERT_EQ(st.contains(4), true);
  EXPECT_TRUE(test[0].second);
  EXPECT_TRUE(test[4].second);
  EXPECT_EQ(*test[1].first, 2);
  EXPECT_TRUE(compare_multisets(og, st));
}

// Multiset end

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
