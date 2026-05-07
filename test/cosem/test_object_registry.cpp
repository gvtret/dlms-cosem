#include "dlms/cosem/cosem.hpp"

#include <gtest/gtest.h>

namespace {

class TestObject : public dlms::cosem::ICosemObject
{
public:
  explicit TestObject(const dlms::cosem::CosemObjectKey& key)
  {
    descriptor_.key = key;
  }

  dlms::cosem::CosemObjectDescriptor Descriptor() const
  {
    return descriptor_;
  }

private:
  dlms::cosem::CosemObjectDescriptor descriptor_;
};

dlms::cosem::CosemObjectKey MakeKey(
  std::uint16_t classId,
  std::uint8_t version,
  std::uint8_t c)
{
  dlms::cosem::CosemObjectKey key;
  key.classId = classId;
  key.version = version;
  key.logicalName = dlms::cosem::CosemLogicalName(1, 0, c, 8, 0, 255);
  return key;
}

std::shared_ptr<dlms::cosem::ICosemObject> MakeObject(
  const dlms::cosem::CosemObjectKey& key)
{
  return std::shared_ptr<dlms::cosem::ICosemObject>(
    new TestObject(key));
}

TEST(CosemTypes, LogicalNameStoresSixBytes)
{
  const dlms::cosem::CosemLogicalName name(0, 0, 40, 0, 0, 255);

  ASSERT_EQ(6u, name.Size());
  EXPECT_EQ(0u, name[0]);
  EXPECT_EQ(0u, name[1]);
  EXPECT_EQ(40u, name[2]);
  EXPECT_EQ(0u, name[3]);
  EXPECT_EQ(0u, name[4]);
  EXPECT_EQ(255u, name[5]);
  EXPECT_EQ(0u, name[6]);
  EXPECT_FALSE(name.IsEmpty());
}

TEST(CosemTypes, EmptyDescriptorIsInvalid)
{
  const dlms::cosem::CosemObjectDescriptor descriptor =
    dlms::cosem::EmptyCosemObjectDescriptor();

  EXPECT_EQ(dlms::cosem::CosemStatus::InvalidArgument,
            dlms::cosem::ValidateObjectDescriptor(descriptor));
}

TEST(CosemTypes, ObjectKeyUsesClassVersionAndLogicalName)
{
  const dlms::cosem::CosemObjectKey base = MakeKey(1u, 0u, 1u);
  dlms::cosem::CosemObjectKey same = MakeKey(1u, 0u, 1u);
  dlms::cosem::CosemObjectKey differentVersion = MakeKey(1u, 1u, 1u);
  dlms::cosem::CosemObjectKey differentName = MakeKey(1u, 0u, 2u);

  EXPECT_EQ(base, same);
  EXPECT_NE(base, differentVersion);
  EXPECT_NE(base, differentName);
  EXPECT_TRUE(base < differentVersion);
  EXPECT_TRUE(base < differentName);
}

TEST(ObjectRegistry, RejectsNullInvalidAndDuplicateObjects)
{
  dlms::cosem::ObjectRegistry registry;
  const dlms::cosem::CosemObjectKey validKey = MakeKey(1u, 0u, 1u);

  EXPECT_EQ(dlms::cosem::CosemStatus::NullObject,
            registry.Register(std::shared_ptr<dlms::cosem::ICosemObject>()));
  EXPECT_EQ(dlms::cosem::CosemStatus::InvalidArgument,
            registry.Register(MakeObject(dlms::cosem::EmptyCosemObjectKey())));
  EXPECT_EQ(dlms::cosem::CosemStatus::Ok,
            registry.Register(MakeObject(validKey)));
  EXPECT_EQ(dlms::cosem::CosemStatus::AlreadyExists,
            registry.Register(MakeObject(validKey)));
  EXPECT_EQ(1u, registry.Size());
}

TEST(ObjectRegistry, FindsRegisteredObjectByKey)
{
  dlms::cosem::ObjectRegistry registry;
  const dlms::cosem::CosemObjectKey key = MakeKey(3u, 0u, 10u);
  const std::shared_ptr<dlms::cosem::ICosemObject> object = MakeObject(key);

  ASSERT_EQ(dlms::cosem::CosemStatus::Ok, registry.Register(object));

  EXPECT_TRUE(registry.Contains(key));
  EXPECT_EQ(object.get(), registry.Find(key));
  EXPECT_EQ(0, registry.Find(MakeKey(3u, 0u, 11u)));
}

TEST(ObjectRegistry, ReturnsDescriptorsInKeyOrder)
{
  dlms::cosem::ObjectRegistry registry;
  const dlms::cosem::CosemObjectKey second = MakeKey(7u, 0u, 2u);
  const dlms::cosem::CosemObjectKey first = MakeKey(1u, 0u, 1u);

  ASSERT_EQ(dlms::cosem::CosemStatus::Ok, registry.Register(MakeObject(second)));
  ASSERT_EQ(dlms::cosem::CosemStatus::Ok, registry.Register(MakeObject(first)));

  const std::vector<dlms::cosem::CosemObjectDescriptor> descriptors =
    registry.Descriptors();

  ASSERT_EQ(2u, descriptors.size());
  EXPECT_EQ(first, descriptors[0].key);
  EXPECT_EQ(second, descriptors[1].key);
}

TEST(CosemStatus, NamesStableValues)
{
  EXPECT_STREQ(
    "AlreadyExists",
    dlms::cosem::CosemStatusName(dlms::cosem::CosemStatus::AlreadyExists));
}

} // namespace
