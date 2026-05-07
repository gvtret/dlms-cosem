#include "dlms/cosem/cosem_status.hpp"

namespace dlms {
namespace cosem {

const char* CosemStatusName(CosemStatus status)
{
  switch (status) {
  case CosemStatus::Ok:
    return "Ok";
  case CosemStatus::InvalidArgument:
    return "InvalidArgument";
  case CosemStatus::AlreadyExists:
    return "AlreadyExists";
  case CosemStatus::NotFound:
    return "NotFound";
  case CosemStatus::NullObject:
    return "NullObject";
  case CosemStatus::InternalError:
    return "InternalError";
  }

  return "Unknown";
}

} // namespace cosem
} // namespace dlms
