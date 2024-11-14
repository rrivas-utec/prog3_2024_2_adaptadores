#include <iostream>
#include <deque>
#include <vector>
#include <stack>  // stack
#include <queue>  // queue y el priority queue

void ejemplo_stack_1() {
  std::stack<int> st1;
  st1.push(10);
  st1.emplace(12);
  st1.push(13);
  st1.push(14);
  while(st1.size() != 0) {      // !st1.empty()
    std::cout << st1.top() << std::endl;
    st1.pop();
  }
  std::cout << "tamaño: " << st1.size() << std::endl;
}

// copiar valores de un vector hacia un stack
void ejemplo_stack_2() {
  std::vector<int> v1 = {10, 20, 30, 40};
  std::deque<int> d1 = {10, 20, 30, 40};
  std::stack<int> st1;                  // Constructor por default
  std::stack<int> st2(st1);             // Constructor copia
  std::stack<int> st3(std::move(st1));  // Constructor move
  std::stack<int> st4(d1);              // Constructor por parametros copia
  std::stack<int> st5(std::move(d1));   // Constructor por parametros move
  
  std::stack<int, std::vector<int>> st6(v1);              // Constructor por parametros copia
  std::stack<int, std::vector<int>> st7(std::move(v1));   // Constructor por parametros move
}

template <typename T, typename Adapter = std::stack<T>>
Adapter merge_stacks(Adapter a, Adapter b) {
  auto min_sz = std::min(a.size(), b.size());
  Adapter rev_result;
  while(min_sz > 0) {
    rev_result.push(b.top());
    rev_result.push(a.top());
    b.pop();
    a.pop();
    --min_sz;
  }
  while(!a.empty()) {
    rev_result.push(a.top());
    a.pop();
  }
  while(!b.empty()) {
    rev_result.push(b.top());
    b.pop();
  }
  Adapter result;
  while(!rev_result.empty()) {
    result.push(rev_result.top());
    rev_result.pop();
  }
  return result;
}

template <typename AdapterType>
void print_adapter(AdapterType adapter) {
  while (!adapter.empty()) {
    std::cout << adapter.top() << " ";
    adapter.pop();
  }
  std::cout << std::endl;
}

void ejemplo_stack_3() {
  std::deque d1 = {1, 5, 4, 2};
  std::deque d2 = {100, 200, 300, 40, 10, 50, 40, 20};
  std::stack<int> a(d1);
  std::stack<int> b(d2);
  auto c = merge_stacks<int>(a, b);
  print_adapter(c);
}

namespace utec {
  template <typename T, typename Container = std::deque<T>>
  class Pila {
    Container cnt;
  public:
    Pila() = default;
    explicit Pila(const Container& cnt):cnt(cnt) {}
    explicit Pila(Container&& cnt) noexcept :cnt(std::move(cnt)) {}
    template <typename Iterator>
    explicit Pila(Iterator start, Iterator stop): cnt(start, stop) { }
    void push(T value) { cnt.push_back(value); }
    template <typename ...Args>
    void emplace(Args... args) { cnt.emplace_back(args...); }
    void pop() { cnt.pop_back(); }
    auto size() { return cnt.size(); }
    auto top() { return cnt.back(); }
    bool empty() { return cnt.size() == 0; }
  };
}

void ejemplo_stack_4() {
  std::vector<int> v1 = {10, 20, 30, 40};
  std::deque<int> d1 = {10, 20, 30, 40};
  utec::Pila<int> st1;                  // Constructor por default
  utec::Pila<int> st2(st1);             // Constructor copia
  utec::Pila<int> st3(std::move(st1));  // Constructor move
  utec::Pila<int> st4(d1);              // Constructor por parametros copia
  utec::Pila<int> st5(std::move(d1));   // Constructor por parametros move
  utec::Pila<int, std::vector<int>> st6(v1);              // Constructor por parametros copia
  utec::Pila<int, std::vector<int>> st7(std::move(v1));   // Constructor por parametros move

  print_adapter(st1);
  print_adapter(st2);
  print_adapter(st3);
  print_adapter(st4);
  print_adapter(st5);
  print_adapter(st6);

}

void ejemplo_stack_5() {
  std::vector d1 = {1, 5, 4, 2};
  std::vector d2 = {100, 200, 300, 40, 10, 50, 40, 20};
  utec::Pila<int> a(d1.begin(), d1.end());
  utec::Pila<int> b(d2.begin(), d2.end());
  auto c = merge_stacks<int, utec::Pila<int>>(a, b);
  print_adapter(c);
}

int main() {
//  ejemplo_stack_1();
//  ejemplo_stack_3();
//ejemplo_stack_4();
  ejemplo_stack_5();
  return 0;
}
