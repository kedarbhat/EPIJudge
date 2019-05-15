#include <list>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

struct BookType {
  int isbn;
  int price;
  bool operator==(const BookType& rhs) const {
    if (std::addressof(rhs) == this) {
      return true;
    }
    return rhs.isbn == isbn && rhs.price == price;
  }
};

class LruCache {
private:
  std::list<BookType> isbnList_;
  std::size_t capacity_;

 public:
  explicit LruCache(size_t capacity) : capacity_(capacity) {}
  int Lookup(int isbn) {
    auto iter = std::find_if(std::cbegin(isbnList_), std::cend(isbnList_), [isbn](auto&& book) { return book.isbn == isbn; });
    if (iter == std::cend(isbnList_)) {
      return -1;
    } else {
      const auto& book = *iter;
      isbnList_.erase(iter);
      isbnList_.push_front(book);
      return book.price;
    }
  }

  void Insert(int isbn, int price) {
    const BookType& bookArg{isbn, price};
    auto iter = std::find_if(std::cbegin(isbnList_), std::cend(isbnList_), [isbn](auto&& book) { return book.isbn == isbn; });
    if (iter != std::cend(isbnList_)) {
      const auto &storedBook = *iter;
      isbnList_.erase(iter);
      isbnList_.push_front(storedBook);
    } else {
      if (isbnList_.size() == capacity_) {
        isbnList_.pop_back();
      }
      isbnList_.push_front(bookArg);
    }
    assert(isbnList_.size() <= capacity_);
  }

  bool Erase(int isbn) {
    auto iter = std::find_if(std::cbegin(isbnList_), std::cend(isbnList_), [isbn](auto&& book) { return book.isbn == isbn; });
    if (iter == std::cend(isbnList_)) {
      return false;
    }
    isbnList_.erase(iter);
    return true;
  }
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
