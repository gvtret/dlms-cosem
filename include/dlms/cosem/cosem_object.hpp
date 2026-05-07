#pragma once

#include "dlms/cosem/cosem_types.hpp"

namespace dlms {
namespace cosem {

class ICosemObject
{
public:
  virtual ~ICosemObject();

  virtual CosemObjectDescriptor Descriptor() const = 0;
};

} // namespace cosem
} // namespace dlms
