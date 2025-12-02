# Code quality observations

This document highlights potentially deprecated or poor-practice patterns spotted in the current codebase. The aim is to guide future refactors toward safer and more idiomatic C++.

## Excess copying and missing const-correctness
- Geometry helpers and the framebuffer expose getters that return mutable data by value without being `const`, leading to needless copies and preventing use on `const` instances. Examples include `FrameBuffer::getImg`, `FrameBuffer::getW`, and similar accessors across geometry types that should be `const` and return references or values without copying the entire buffer.

## Unnecessary ownership declarations and manual destruction
- Several geometry classes manually clear `std::vector` members inside destructors (`~Circle`, `~Rectangle`, `~Triangle`, `~Line`) even though the rule of zero would handle cleanup automatically. The explicit clears add noise and risk double-work if future ownership logic changes.

## Header dependencies that bloat compile times
- `include/geo-prims.h` pulls in `<iostream>` even though the header only declares data containers and geometry helpers. Removing unused heavy headers reduces rebuild costs and keeps interfaces cleaner.

## Public data members that bypass invariants
- `FrameBuffer::img` and the map dimensions (`Map::w`/`Map::h`) are public, allowing external code to mutate state without bounds checks or resize synchronization. Encapsulating these fields behind accessors would protect invariants like buffer size matching width/height.

## Copy-returned coordinate buffers
- Geometry `getCoords` methods currently return `std::vector<int>` by value, forcing allocations each time coordinates are fetched. Returning `const std::vector<int>&` (or views) would avoid repeated copies when primitives are reused across frames.
