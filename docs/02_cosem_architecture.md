# dlms-cosem Architecture

## 1. Layer Position

```mermaid
flowchart TD
  Server["Future dlms-server"]
  XDlms["lib/dlms-xdlms"]
  Cosem["lib/dlms-cosem"]
  Security["Future dlms-security"]

  Server --> XDlms
  Server --> Cosem
  XDlms --> Cosem
  Cosem -. access policy may consult .-> Security
```

`dlms-cosem` is below the server dispatcher and the xDLMS service layer. It
does not decode APDUs. It receives already resolved COSEM descriptors and
returns encoded xDLMS data bytes plus COSEM status values.

## 2. Read Attribute Flow

```mermaid
sequenceDiagram
  participant Server as dlms-server or dlms-xdlms
  participant Device as LogicalDevice
  participant Registry as ObjectRegistry
  participant Object as ICosemObject

  Server->>Device: ReadAttribute(descriptor)
  Device->>Registry: ReadAttribute(descriptor)
  Registry->>Registry: Find object by class id + logical name
  Registry->>Registry: Check attribute access
  Registry->>Object: ReadAttribute(attributeId)
  Object-->>Registry: encoded xDLMS data
  Registry-->>Device: CosemStatus + data
  Device-->>Server: CosemStatus + data
```

## 3. Association View Flow

```mermaid
sequenceDiagram
  participant Server as dlms-server
  participant Device as LogicalDevice
  participant Registry as ObjectRegistry

  Server->>Device: BuildAssociationView()
  Device->>Registry: Enumerate visible objects
  Registry-->>Device: descriptors + access rights
  Device-->>Server: association view
```

## 4. Class Interaction

```mermaid
classDiagram
  class PhysicalDevice {
    -vector logicalDevices
    +AddLogicalDevice()
    +FindLogicalDevice()
  }

  class LogicalDevice {
    -uint16 sap
    -ObjectRegistry registry
    +RegisterObject()
    +ReadAttribute()
    +WriteAttribute()
    +InvokeMethod()
    +BuildAssociationView()
  }

  class ObjectRegistry {
    -vector objectRefs
    +Register()
    +Find()
    +ForEach()
  }

  class ICosemObject {
    +Descriptor()
    +AccessRights()
    +ReadAttribute()
    +WriteAttribute()
    +InvokeMethod()
  }

  class AssociationView {
    +objects
  }

  PhysicalDevice --> LogicalDevice
  LogicalDevice --> ObjectRegistry
  LogicalDevice --> AssociationView
  ObjectRegistry --> ICosemObject
```

## 5. Ownership

The first implementation uses non-owning object references. Application or
server code owns concrete object instances. This keeps the registry simple and
avoids prescribing allocation policy before persistent object storage exists.

## 6. Error Model

The layer returns status codes only. Runtime API paths do not throw exceptions.
Object implementation failures are normalized to `ObjectError` unless they map
to a specific COSEM status.
