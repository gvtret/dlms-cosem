# dlms-cosem Implementation Plan

## Phase 0. Documentation

Deliverables:

- requirements;
- API contract;
- architecture diagrams;
- test plan;
- implementation plan;
- empty standalone repository registered as root submodule.

Commit message:

```text
docs(cosem): define object model layer
```

## Phase 1. Object Identity And Registry

Deliverables:

- CMake project and GoogleTest harness;
- `CosemStatus`;
- `CosemLogicalName`;
- `CosemObjectKey`;
- `CosemObjectDescriptor`;
- `CosemByteBuffer`;
- `ObjectRegistry`;
- `ICosemObject` descriptor-only registration;
- tests for identity, validation, duplicate rejection, and lookup.

Commit message:

```text
feat(cosem): add object identity registry
```

## Phase 2. Attribute And Method Access

Deliverables:

- attribute access modes;
- method access modes;
- `CosemAccessRights`;
- read/write/invoke dispatch through `ICosemObject`;
- access checks before callback invocation;
- tests for granted, denied, missing, and object-error paths.

Commit message:

```text
feat(cosem): add object access dispatch
```

## Phase 3. Logical Device And Association View

Deliverables:

- `LogicalDevice`;
- minimal `PhysicalDevice`;
- association-view object list model;
- SAP assignment metadata model;
- Association LN metadata model;
- tests for visible object list and logical-device lookup.

Commit message:

```text
feat(cosem): add logical device association view
```

## Phase 4. Root Integration

Deliverables:

- root CMake subdirectory wiring;
- root submodule pointer update;
- root integration smoke test once `dlms-server` exists.

Commit message:

```text
build: add dlms-cosem submodule
```
