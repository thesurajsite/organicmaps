#pragma once

#include "base/assert.hpp"

#include <string>

namespace ads
{
struct Banner
{
  enum class Place : uint8_t
  {
    Search = 0,
    Poi = 1,
  };

  enum class Type : uint8_t
  {
    None = 0,
    Facebook = 1,
    RB = 2,
    Mopub = 3,
  };

  Banner() = default;
  Banner(Type t, std::string const & value) : m_type(t), m_value(value) {}

  Type m_type = Type::None;
  std::string m_value;
};

inline std::string DebugPrint(Banner::Type type)
{
  switch (type)
  {
  case Banner::Type::None: return "None";
  case Banner::Type::Facebook: return "Facebook";
  case Banner::Type::RB: return "RB";
  case Banner::Type::Mopub: return "Mopub";
  }
  UNREACHABLE();
}
}  // namespace ads
