#include "dlms/cosem/object_registry.hpp"

namespace dlms {
namespace cosem {

ICosemObject::~ICosemObject()
{
}

CosemStatus ObjectRegistry::Register(
  const std::shared_ptr<ICosemObject>& object)
{
  if (!object) {
    return CosemStatus::NullObject;
  }

  const CosemObjectDescriptor descriptor = object->Descriptor();
  const CosemStatus status = ValidateObjectDescriptor(descriptor);
  if (status != CosemStatus::Ok) {
    return status;
  }

  if (objects_.find(descriptor.key) != objects_.end()) {
    return CosemStatus::AlreadyExists;
  }

  objects_[descriptor.key] = object;
  return CosemStatus::Ok;
}

const ICosemObject* ObjectRegistry::Find(
  const CosemObjectKey& key) const
{
  if (ValidateObjectKey(key) != CosemStatus::Ok) {
    return 0;
  }

  std::map<CosemObjectKey, std::shared_ptr<ICosemObject> >::const_iterator it =
    objects_.find(key);
  return it == objects_.end() ? 0 : it->second.get();
}

bool ObjectRegistry::Contains(const CosemObjectKey& key) const
{
  return Find(key) != 0;
}

std::vector<CosemObjectDescriptor> ObjectRegistry::Descriptors() const
{
  std::vector<CosemObjectDescriptor> descriptors;
  for (std::map<CosemObjectKey, std::shared_ptr<ICosemObject> >::const_iterator
       it = objects_.begin();
       it != objects_.end();
       ++it) {
    descriptors.push_back(it->second->Descriptor());
  }
  return descriptors;
}

std::size_t ObjectRegistry::Size() const
{
  return objects_.size();
}

} // namespace cosem
} // namespace dlms
