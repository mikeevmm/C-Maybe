#include <stdio.h>

#include "include/maybe.hh"

maybe::Maybe<int> find_in_array(int* arr, size_t size, int element) {
  for (int i = 0; i < size; ++i) {
    if (arr[i] == element) return maybe::some(arr[i]);
  }
  return maybe::none<int>();
}

int main(void) {
  int array[] = {1, 2, 5, 6};
  int to_find[] = {3, 6};
  for (int i = 0; i < 2; ++i) {
    // You can do it the functional way...
    find_in_array(array, 4, to_find[i])
        .map<int>([](int x) { return x * x; })
        .then([](int x) { printf("Squared is %i\n", x); });

    // ...Or the imperative way...
    auto found = find_in_array(array, 4, to_find[i]);
    if (found.is_some()) {
      auto squared = found.unwrap();
      printf("Cubed is %i\n", squared * squared * squared);
    }

    // But you can't ignore the fact that it might not return anything!
    //  error: no match for ‘operator*’ (operand types are ‘maybe::Maybe<int>’ and ‘maybe::Maybe<int>’)
    // auto x = find_in_array(array, 4, to_find[i]);
    // printf("Squared is %i\n", x*x);
  }
  return 0;
}
