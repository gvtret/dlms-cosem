#pragma once

#include "dlms/cosem/cosem_object.hpp"
#include "dlms/cosem/cosem_status.hpp"
#include "dlms/cosem/cosem_types.hpp"

#include <map>
#include <memory>
#include <vector>

namespace dlms {
namespace cosem {

class ObjectRegistry
{
public:
  CosemStatus Register(const std::shared_ptr<ICosemObject>& object);

  const ICosemObject* Find(const CosemObjectKey& key) const;
  bool Contains(const CosemObjectKey& key) const;
  std::vector<CosemObjectDescriptor> Descriptors() const;
  std::size_t Size() const;

private:
  std::map<CosemObjectKey, std::shared_ptr<ICosemObject> > objects_;
};

} // namespace cosem
} // namespace dlms
