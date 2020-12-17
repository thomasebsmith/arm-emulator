#ifndef __SRC_UTILS_BIT_UTILS_H__
#define __SRC_UTILS_BIT_UTILS_H__

#include <cassert>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Utils::BitUtils {
  bool is_correct_endianness();

  template <typename T>
  void flip_endianness(T &num) {
    static_assert(sizeof(T) > 0, "Cannot flip endianness of empty type");
    char *begin = reinterpret_cast<char *>(num);
    char *end = begin + sizeof(T) - 1;
    while (begin != end) {
      std::swap(*begin, *end);
      ++begin;
      --end;
    }
  }

  template <typename T>
  T convert_endianness(T num) {
    if (!is_correct_endianness()) {
      flip_endianness(num);
    }
    return num;
  }

  template <typename T, typename U>
  constexpr auto extract_bits(T data, U offset) {
    return std::tuple<T>{data >> offset};
  }

  template <typename T, typename U, typename... Args>
  constexpr auto extract_bits(T data, U offset, U next_offset, Args... args) {
    static_assert(
      std::is_unsigned_v<T>,
      "Cannot extract bits from signed numbers"
    );
    static_assert(
      std::is_unsigned_v<U>,
      "Cannot extract bits using signed offsets"
    );
    assert(next_offset > offset && "Successive offsets must increase");
    auto result = (
      (data >> offset) &
      ~(~static_cast<T>(0) << (next_offset - offset))
    );
    return std::tuple_cat(
      std::tuple<T>{result},
      extract_bits(data, next_offset, args...)
    );
  }
}

#endif
