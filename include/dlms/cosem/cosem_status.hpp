#pragma once

namespace dlms {
namespace cosem {

enum class CosemStatus
{
  Ok,
  InvalidArgument,
  AlreadyExists,
  NotFound,
  NullObject,
  InternalError
};

const char* CosemStatusName(CosemStatus status);

} // namespace cosem
} // namespace dlms
