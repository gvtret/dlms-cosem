#pragma once

#include "dlms/cosem/cosem_status.hpp"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace dlms {
namespace cosem {

typedef std::vector<std::uint8_t> CosemByteBuffer;

class CosemLogicalName
{
public:
  CosemLogicalName();
  CosemLogicalName(
    std::uint8_t a,
    std::uint8_t b,
    std::uint8_t c,
    std::uint8_t d,
    std::uint8_t e,
    std::uint8_t f);

  const std::uint8_t* Data() const;
  std::size_t Size() const;
  bool IsEmpty() const;
  std::uint8_t operator[](std::size_t index) const;

private:
  std::uint8_t bytes_[6];
};

struct CosemObjectKey
{
  std::uint16_t classId;
  std::uint8_t version;
  CosemLogicalName logicalName;
};

struct CosemObjectDescriptor
{
  CosemObjectKey key;
};

CosemObjectKey EmptyCosemObjectKey();
CosemObjectDescriptor EmptyCosemObjectDescriptor();
CosemStatus ValidateObjectKey(const CosemObjectKey& key);
CosemStatus ValidateObjectDescriptor(
  const CosemObjectDescriptor& descriptor);

bool operator==(
  const CosemLogicalName& lhs,
  const CosemLogicalName& rhs);
bool operator!=(
  const CosemLogicalName& lhs,
  const CosemLogicalName& rhs);
bool operator<(
  const CosemLogicalName& lhs,
  const CosemLogicalName& rhs);
bool operator==(
  const CosemObjectKey& lhs,
  const CosemObjectKey& rhs);
bool operator!=(
  const CosemObjectKey& lhs,
  const CosemObjectKey& rhs);
bool operator<(
  const CosemObjectKey& lhs,
  const CosemObjectKey& rhs);

} // namespace cosem
} // namespace dlms
