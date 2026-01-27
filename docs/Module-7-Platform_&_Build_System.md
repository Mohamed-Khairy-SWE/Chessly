1. Purpose of This Module

This module ensures that:

The same source tree builds on Linux and Windows

The same binary behavior exists on both

Dependencies are predictable

Packaging is realistic for sharing with friends

This module does not:

Add game features

Modify chess or networking logic

Change UI behavior

It only answers:

“How do we build, link, and ship this reliably?”

2. Cross-Platform Strategy (High Level)
One Codebase

No OS-specific forks

No platform-only features

Minimal Conditional Compilation

Avoid #ifdef _WIN32 in core logic

Contain platform differences to:

Build system

Entry points (if needed)

Networking setup (ASIO handles most)

If platform logic leaks into game logic → design failure.

3. Toolchain Choices (Intentional)
Build System

CMake

Single CMakeLists.txt

Generator-agnostic:

Ninja

Makefiles

Visual Studio

GUI Framework

Qt 6

Widgets module

Identical UI code on both platforms

Networking

Standalone ASIO

Header-only

OS socket differences abstracted away

4. Dependency Management Philosophy

Dependencies must be:

Explicit

Vendored where possible

Version-pinned

Your current structure is good:

ASIO vendored

JSON library vendored

Qt found via system install

Claude should not introduce:

Package managers

FetchContent magic

Hidden dependencies

5. Linux Build Expectations (Your Primary OS)

Target:

Ubuntu (but compatible with most distros)

Expectations:

Uses system Qt

Uses system pthreads

No root privileges required

Binary behavior:

Launches via terminal or desktop

Uses relative paths for resources (via Qt resources)

6. Windows Build Expectations

Target:

Windows 10 / 11

MSVC toolchain

Expectations:

Qt installed via official installer

Uses WinSock transparently (ASIO)

Produces .exe

Important:

Do not assume Unix filesystem behavior

Do not assume / paths

Do not rely on case-sensitive filesystems

7. Resource Management (Critical)

All assets:

Chess piece images

Icons

UI resources

Must be:

Bundled via Qt resource system

Never loaded via raw filesystem paths

This ensures:

Single executable portability

No “missing PNG” bugs

Identical behavior on Linux & Windows

8. Compiler & Language Standard Policy

C++20

No compiler-specific extensions

No undefined behavior

No reliance on GCC-only features

Warnings should be:

Treated seriously

Fixed, not ignored

This keeps MSVC happy.

9. ASIO Cross-Platform Considerations

ASIO handles:

WinSock initialization

POSIX sockets

Polling differences

However:

Threading model must be platform-neutral

No assumptions about socket error codes

Use ASIO abstractions only

10. Binary Distribution Strategy (Friends-Friendly)
Linux

Options:

Plain binary + README

AppImage (later)

Tarball

Windows

Options:

.zip containing .exe + Qt DLLs

Installer (later)

Initial goal:

“Unzip and run”

Not:

“Install toolchains”

11. Runtime Configuration Philosophy

No:

Registry usage

Environment variables

Config files (initially)

Everything:

In-memory

UI-driven

This avoids platform-specific bugs.

12. Testing Matrix (Mental Model)

Claude should assume:

Linux + GCC

Linux + Clang

Windows + MSVC

If code is portable across these, it’s solid.

15. Exit Criteria (Module 7 Complete)

This module is complete when:

✔ Same source builds on Linux & Windows
✔ No platform-specific hacks in core logic
✔ Qt resources load everywhere
✔ ASIO behaves identically
✔ Friends can play regardless of OS