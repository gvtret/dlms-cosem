#pragma once

#include "dlms/cosem/cosem_object.hpp"

namespace dlms {
namespace cosem {

class CosemDataObject : public ICosemObject
{
public:
  CosemDataObject(
    const CosemLogicalName& logicalName,
    const CosemByteBuffer& value,
    AttributeAccessMode valueAccess);

  CosemObjectDescriptor Descriptor() const;
  CosemAccessRights AccessRights() const;
  CosemStatus ReadAttribute(
    std::uint8_t attributeId,
    CosemByteBuffer& output) const;
  CosemStatus WriteAttribute(
    std::uint8_t attributeId,
    const CosemByteBuffer& input);
  CosemStatus InvokeMethod(
    std::uint8_t methodId,
    const CosemByteBuffer& input,
    CosemByteBuffer& output);

  const CosemByteBuffer& Value() const;
  void SetValue(const CosemByteBuffer& value);

private:
  CosemObjectDescriptor descriptor_;
  CosemByteBuffer value_;
  CosemAccessRights rights_;
};

class CosemRegisterObject : public ICosemObject
{
public:
  CosemRegisterObject(
    const CosemLogicalName& logicalName,
    const CosemByteBuffer& value,
    const CosemByteBuffer& scalerUnit,
    AttributeAccessMode valueAccess);

  CosemObjectDescriptor Descriptor() const;
  CosemAccessRights AccessRights() const;
  CosemStatus ReadAttribute(
    std::uint8_t attributeId,
    CosemByteBuffer& output) const;
  CosemStatus WriteAttribute(
    std::uint8_t attributeId,
    const CosemByteBuffer& input);
  CosemStatus InvokeMethod(
    std::uint8_t methodId,
    const CosemByteBuffer& input,
    CosemByteBuffer& output);

  const CosemByteBuffer& Value() const;
  const CosemByteBuffer& ScalerUnit() const;
  void SetValue(const CosemByteBuffer& value);
  void SetScalerUnit(const CosemByteBuffer& scalerUnit);

private:
  CosemObjectDescriptor descriptor_;
  CosemByteBuffer value_;
  CosemByteBuffer scalerUnit_;
  CosemAccessRights rights_;
};

} // namespace cosem
} // namespace dlms
