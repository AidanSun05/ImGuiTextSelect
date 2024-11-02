# ImGuiTextSelect Changelog

This document tracks the changes between ImGuiTextSelect versions. Dates are written in the MM/DD/YYYY format.

## 1.1.3 (11/02/2024)

### Improvements

- Added the missing `#pragma once` in the header file.
- Changed uses of `size_t` to `std::size_t`.
- Removed dependency on `std::pair` and `<utility>`.
- Improved word boundary detection: double-clicking a sequence of boundary characters now selects all of them instead of just one.

## 1.1.2 (08/09/2024)

### Removals

- Removed support for Dear ImGui versions older than v1.90.7. (`ImGuiMod_Shortcut` was replaced with `ImGuiMod_Ctrl`)

## 1.1.1 (05/31/2024)

This is a patch release which addresses the breaking changes in Dear ImGui v1.90.7. It is backwards compatible with previous Dear ImGui versions.

### Improvements

- Updated the use of `ImGui::Shortcut()` and `ImGuiMod_Ctrl`.

## 1.1.0 (05/24/2024)

### Additions

- Added a full example program.
- Added automatic newline insertion for multiline copying.
  - The lines that you pass to ImGuiTextSelect no longer need to end with newlines for multiline copying to work.

### Improvements

- Removed `#include <string>` from the header file.

### Bug Fixes

- Fixed a crash when compiling on the debug configuration with MSVC (#2). Thanks @taki640!

## 1.0.0 (01/08/2024)

Initial release of ImGuiTextSelect.
