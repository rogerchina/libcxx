//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
// UNSUPPORTED: c++98, c++03

// This test is designed to cause and allow TSAN to detect a race condition
// in std::async, as reported in https://bugs.llvm.org/show_bug.cgi?id=38682.

#include <cassert>
#include <functional>
#include <future>
#include <numeric>
#include <vector>


static int worker(std::vector<int> const& data) {
  return std::accumulate(data.begin(), data.end(), 0);
}

static int& worker_ref(int& i) { return i; }

static void worker_void() { }

int main() {
  // future<T>
  {
    std::vector<int> const v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i != 20; ++i) {
      std::future<int> fut = std::async(std::launch::async, worker, v);
      int answer = fut.get();
      assert(answer == 55);
    }
  }

  // future<T&>
  {
    for (int i = 0; i != 20; ++i) {
      std::future<int&> fut = std::async(std::launch::async, worker_ref, std::ref(i));
      int& answer = fut.get();
      assert(answer == i);
    }
  }

  // future<void>
  {
    for (int i = 0; i != 20; ++i) {
      std::future<void> fut = std::async(std::launch::async, worker_void);
      fut.get();
    }
  }
}
