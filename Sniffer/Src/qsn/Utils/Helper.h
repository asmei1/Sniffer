#pragma once
#include <type_traits>

namespace qsn
{
   template <typename E>
   constexpr auto ec2Int(E e) noexcept
   {
      return static_cast<std::underlying_type_t<E>>(e);
   }
}