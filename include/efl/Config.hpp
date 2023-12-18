//===- efl/Config.hpp -----------------------------------------------===//
//
// Copyright (C) 2023 Eightfold
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
//     limitations under the License.
//
//===----------------------------------------------------------------===//
//
//  This file acts as a source for in-language configuration.
//
//===----------------------------------------------------------------===//

#if !defined(EFL_CONFIG_SINGLE_HPP) && !defined(EFL_CONFIG)

// TODO: Remove these?
#include <efl/Undefs.hpp>
#define EFL_CONFIG
#define EFL_VERSION(name) EFL_ ## name ## _VERSION

#if defined(COMPILER_CUSTOM) || defined(PLATFORM_CUSTOM) || defined(ARCH_CUSTOM)
# error Custom config settings currently unsupported, check back later.
#endif

#if (defined(_MSC_VER) || defined(_MSVC_LANG)) && !defined(__MINGW32__)
# define EFLI_MSVC_ 1
#endif

#ifndef EFLI_MSVC_
# define EFL_COMPILER_PRAGMA(...) _Pragma(#__VA_ARGS__)
#else // MSVC
# define EFL_COMPILER_PRAGMA(...) __pragma(__VA_ARGS__)
#endif
#define EFL_PRAGMA_DEFER(...) EFL_COMPILER_PRAGMA(__VA_ARGS__)

#if defined(EFLI_MSVC_)
# define EFL_REGION_BEGIN(name) EFL_COMPILER_PRAGMA(region name)
# define EFL_REGION_CLOSE(comment) EFL_COMPILER_PRAGMA(endregion comment)
#elif defined(__CODEGEARC__)
# define EFL_REGION_BEGIN(name) EFL_COMPILER_PRAGMA(region name)
# define EFL_REGION_CLOSE(...) EFL_COMPILER_PRAGMA(end_region)
#else
# define EFL_REGION_BEGIN(...)
# define EFL_REGION_CLOSE(...)
#endif

#if defined(EFLI_MSVC_)
# include <sal.h>
#endif


/// Provides options for modifying default config settings
EFL_REGION_BEGIN("config.macro.opts")
// ---------------------------------------------------------------------------------------------------------------- //

#ifndef COMPILER_STRICT_CONFORMANCE
# if defined(__INTEL_COMPILER) || (defined(EFLI_MSVC_) && defined(_MSVC_TRADITIONAL))
#  define COMPILER_STRICT_CONFORMANCE 1
# else
#  define COMPILER_STRICT_CONFORMANCE 0
# endif
#endif

#ifndef COMPILER_DEBUG
# if defined(NDEBUG) || defined(_NDEBUG) || \
  defined(EFLI_NDEBUG_) || \
  (defined(EFLI_MSVC_) && !defined(_DEBUG)) || \
  (defined(__OPTIMIZE__) || defined(__OPTIMIZE_SIZE__))
#  define COMPILER_DEBUG 0
# else
#  define COMPILER_DEBUG 1
# endif
#endif

#if !defined(EFLI_NDEBUG_) && (COMPILER_DEBUG == 0)
# define EFLI_NDEBUG_ 1
#endif

#ifndef COMPILER_UNICODE_VERSION
/**
 * Determines which prefix will be used with `USTRIFY`.
 * Possible values: 8, 16, 32
 */
# define COMPILER_UNICODE_VERSION 8
#endif

#ifndef COMPILER_RESCAN_COUNT
/// Make sure you have a beefy pc for large values
# define COMPILER_RESCAN_COUNT 5
#endif

#ifndef COMPILER_FUNCTION_CLASSIC
/// If `COMPILER_FUNCTION` uses __func__ or pretty function
# define COMPILER_FUNCTION_CLASSIC 0
#endif

#ifndef COMPILER_UNDEF_CORE
/// If macros will be undefined in core
# define COMPILER_UNDEF_CORE 0
#endif

#undef COMPILER_BOOST_EXTEND
#define COMPILER_BOOST_EXTEND 0

#ifdef __has_include
# define EFLI_HAS_INCLUDE_ 1
#else
# define EFLI_HAS_INCLUDE_ 0
# define __has_include(...) 0
#endif // defined(__has_include)?

#ifdef __has_builtin
# define EFLI_HAS_BUILTIN_ 1
#else
# define EFLI_HAS_BUILTIN_ 0
# define __has_builtin(...) 0
#endif // defined(__has_builtin)?

#ifdef __has_attribute
# define EFLI_HAS_ATTRIBUTE_ 1
#else
# define EFLI_HAS_ATTRIBUTE_ 0
# define __has_attribute(...) 0
#endif // defined(__has_attribute)?

#ifdef __has_cpp_attribute
# define EFLI_HAS_CPP_ATTRIBUTE_ 1
#else
# define EFLI_HAS_CPP_ATTRIBUTE_ 0
# define __has_cpp_attribute(...) 0
#endif // defined(__has_cpp_attribute)?

#ifdef __has_declspec_attribute
# define EFLI_HAS_DECLSPEC_ATTRIBUTE_ 1
#else
# define EFLI_HAS_DECLSPEC_ATTRIBUTE_ 0
# define __has_declspec_attribute(...) 0
#endif // defined(__has_cpp_attribute)?

#ifdef __has_feature
# define EFLI_HAS_FEATURE_ 1
#else
# define EFLI_HAS_FEATURE_ 0
# define __has_feature(...) 0
#endif // defined(__has_feature)?

#ifdef __has_extension
# define EFLI_HAS_EXTENSION_ 1
#elif (EFLI_HAS_FEATURE_ == 1)
// Ancient Clang workaround
# define EFLI_HAS_EXTENSION_ 1
# define __has_extension __has_feature
#else
# define EFLI_HAS_EXTENSION_ 0
# define __has_extension(...) 0
#endif // defined(__has_extension)?

#if EFLI_HAS_CPP_ATTRIBUTE_ && defined(__cplusplus)
# define EFL_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
# define EFL_HAS_CPP_ATTRIBUTE(...) 0
#endif

#if defined(__is_identifier) && EFLI_HAS_BUILTIN_
// Required for some older Intel/Clang versions.
# define EFL_HAS_BUILTIN(x) (__has_builtin(x) || !__is_identifier(x))
#else
# define EFL_HAS_BUILTIN(x) __has_builtin(x)
#endif

#if defined(EFLI_MSVC_)
# define EFL_HAS_DECLSPEC(x) 1
#else
# define EFL_HAS_DECLSPEC(x) __has_declspec_attribute(x)
#endif

#ifdef __GNUC__
# define EFL_EXTENSION __extension__
#else
# define EFL_EXTENSION
#endif

EFL_REGION_CLOSE("config.macro.opts")


/*
 * Provides essential defines for the rest of config.
 * Contextless, only implements object-like macros
 */
EFL_REGION_BEGIN("config.macro.meta")
// ---------------------------------------------------------------------------------------------------------------- //

#define COMPILER_CPP97 199711L
#define COMPILER_CPP98 199711L
#define COMPILER_CPP11 201103L
#define COMPILER_CPP14 201402L
#define COMPILER_CPP17 201703L
#define COMPILER_CPP20 202002L
#define COMPILER_CPP23 202304L  /// Just a guess for now

#define CPPVER97_NEXT 11
#define CPPVER98_NEXT 11
#define CPPVER11_NEXT 14
#define CPPVER14_NEXT 17
#define CPPVER17_NEXT 20
#define CPPVER20_NEXT 23
#define CPPVER23_NEXT 26

/*
 * First 2 bits are used to identify the compiler supertype (01 for GNU, 10 for LLVM).
 * This is used because many "compiler dependent" features only vary between supertypes.
 * Other than MSVC, your average compiler will be based on GCC or LLVM.
 */

#define VCOMPILER_UNKNOWN   0b0000000000
#define VCOMPILER_GNU       0b0100000000
#define VCOMPILER_LLVM      0b1000000000
#define VCOMPILER_GCC       0b0100000001
#define VCOMPILER_CLANG     0b1000000010
#define VCOMPILER_MSVC      0b0000000100
#define VCOMPILER_ICC       0b0000001000
#define VCOMPILER_ICX       0b1000010010
#define VCOMPILER_MINGW     0b0100100001
#define VCOMPILER_NVCPP     0b0001000000
#define VCOMPILER_ELLCC     0b1010000000

/*
 * First 2 bits are used to identify variations of the compiler.
 * This is really only 16/32/64 bit modes.
 */

#define  VPLATFORM_UNKNOWN  0b0000000000
#define  VPLATFORM_WINDOWS  0b0000000001
# define VPLATFORM_WIN_16   0b0100000001
# define VPLATFORM_WIN_32   0b1000000001
# define VPLATFORM_WIN_64   0b1100000001
#define  VPLATFORM_LINUX    0b0000000010
#define  VPLATFORM_ANDROID  0b0000000100
#define  VPLATFORM_MACOS    0b0000001000
#define  VPLATFORM_IOS      0b0000010000
#define  VPLATFORM_HAIKU    0b0000100000
#define  VPLATFORM_SOLARIS  0b0001000000
#define  VPLATFORM_SUNOS    0b0010000000

/*
 * The following predefines the register size constants.
 * Defined as flags because of things like thumb on ARM.
 * It is unlikely 8/16 bit sizes will be fully supported.
 */

#define REG8    0b0001
#define REG16   0b0010
#define REG32   0b0100
#define REG64   0b1000

/// Number of supported C++ versions
#define COMPILER_VERSION_COUNT 6
/// Lowest supported C++ version
#define COMPILER_MIN_VERSION 97
/// Highest supported C++ version
#define COMPILER_MAX_VERSION 23
/// Number of bits in `VCOMPILER_...` macros
#define VCOMPILER_BIT_COUNT 10
/// Mask for `config.type`
#define VCOMPILER_SUPERTYPE_MASK 0b1100000000

#define COMPILER_ARITHMETIC_MAX 256
#define COMPILER_RESCAN_MAX 5

EFL_REGION_CLOSE("config.macro.meta")


/*
 * Defines commonly used function-like macros.
 * Examples include CAT, EAT, STRIFY, etc.
 */
EFL_REGION_BEGIN("config.macro.functions")
// ---------------------------------------------------------------------------------------------------------------- //

#define EFL_DEFER(...) EFLI_XDEFER_(__VA_ARGS__)
#define EFL_EXPAND(p) EFL_DEFER(EFLI_XEXPAND_ p)
#define EFL_EAT(...)

#define EFLI_XDEFER_(...) __VA_ARGS__
#define EFLI_XEXPAND_(...) __VA_ARGS__

/**
 * Various `CAT` function macros.
 * Allow for the concatenation of 2, 3, or 4 arguments
 */

#define EFL_CAT(x, y) EFLI_XCAT_(x, y)
#define EFL_TCAT(x, y, z) EFLI_XTCAT_(x, y, z)
#define EFL_QCAT(w, x, y, z) EFLI_XQCAT_(w, x, y, z)

#if !COMPILER_STRICT_CONFORMANCE
# define EFLI_XCAT_(x, y) x ## y
# define EFLI_XTCAT_(x, y, z) x ## y ## z
# define EFLI_XQCAT_(w, x, y, z) w ## x ## y ## z
#else
# define EFLI_XCAT_(x, y) EFLI_DCAT_(~, x ## y)
# define EFLI_XTCAT_(x, y, z) EFLI_DCAT_(~, x ## y ## z)
# define EFLI_XQCAT_(x, y, z) EFLI_DCAT_(~, w ## x ## y ## z)
# define EFLI_DCAT_(_, x) x
#endif

/*
 * Function macros used to convert random tokens to strings of various types.
 * Supports R, L, u8, u16, u32 prefixes.
 * The macro `COMPILER_UNICODE_VERSION` defined earlier
 * determines the type used for `USTRIFY`
 */

#define STRIFY(...)     EFLI_XSTRIFY_(__VA_ARGS__)
#define LSTRIFY(...)    EFLI_PXSTRIFY_(L, __VA_ARGS__)
#define RSTRIFY(...)    EFLI_PXSTRIFY_(R, __raw__(__VA_ARGS__)__raw__)
#define U8STRIFY(...)   EFLI_PXSTRIFY_(u8, __VA_ARGS__)
#define U16STRIFY(...)  EFLI_PXSTRIFY_(u, __VA_ARGS__)
#define U32STRIFY(...)  EFLI_PXSTRIFY_(U, __VA_ARGS__)
#define USTRIFY(...)    EFL_DEFER(EFLI_PUSTRIFY_ (__VA_ARGS__))

#define EFLI_XSTRIFY_(...) #__VA_ARGS__
#define EFLI_PUSTRIFY_ EFL_TCAT(U, COMPILER_UNICODE_VERSION, STRIFY)
#define EFLI_PXSTRIFY_(prefix, ...) EFLI_PXXSTRIFY_(prefix, #__VA_ARGS__)
#define EFLI_PXXSTRIFY_(prefix, text) prefix ## text

EFL_REGION_CLOSE("config.macro.functions")


/*
 * Defines several macro utilities for handling different C++ versions.
 * Also defines aliases for keywords/attributes, which are all caps versions
 * of the normal keywords (`noexcept` -> `NOEXCEPT`; `[[nodiscard]]` -> `NODISCARD`).
 * Also defines `FATTRIBUTE` macros for attributes with messages
 */
EFL_REGION_BEGIN("config.macro.cpp")
// ---------------------------------------------------------------------------------------------------------------- //

#if defined(_MSC_VER) || defined(_MSVC_LANG)
# define COMPILER_CPP_VERSION _MSVC_LANG
#elif defined(__cplusplus) && __cplusplus
# define COMPILER_CPP_VERSION __cplusplus
#else
# error This must be compiled with C++!
# define COMPILER_CPP_VERSION 0
#endif

#define CPPVER_NEXT(num) EFL_DEFER(EFL_TCAT(CPPVER, num, _NEXT))
#define CPPVER_LEAST(num) (COMPILER_CPP_VERSION >= EFL_CAT(COMPILER_CPP, num))
#define CPPVER_MOST(num) (COMPILER_CPP_VERSION < EFL_CAT(COMPILER_CPP, CPPVER_NEXT(num)))
#define CPPVER_MATCH(num) (CPPVER_LEAST(num) && CPPVER_MOST(num))

// TODO: Remove this? Can't remember why it's here...
#ifndef CPPVER
# define CPPVER(num) CPPVER_LEAST(num)
#endif

// TODO: Update these :P
#if CPPVER_LEAST(23)
# define ASSUME(...) [[assume(__VA_ARGS__)]]
#else
# define ASSUME(...)
#endif

#if CPPVER_LEAST(20)
# define CONSTEVAL consteval
# define FDEPRECATED(...) [[deprecated __VA_OPT__((__VA_ARGS__))]]
# define FNODISCARD(...) [[nodiscard __VA_OPT__((__VA_ARGS__))]]
# define LIKELY [[likely]]
# define NO_UNIQUE_ADDRESS [[no_unique_address]]
# define UNLIKELY [[unlikely]]
/// Constexpr virtual if C++20.
# define VCONSTEXPR constexpr
#else
# define CONSTEVAL constexpr
# define NO_UNIQUE_ADDRESS
/// Constexpr virtual if C++20.
# define VCONSTEXPR
#endif

#if CPPVER_LEAST(17)
# ifndef FNODISCARD
#  define FNODISCARD(...) [[nodiscard]]
# endif
# define FALLTHROUGH [[fallthrough]]
# define GLOBAL inline constexpr
# define MAYBE_UNUSED [[maybe_unused]]
# define NODISCARD [[nodiscard]]
#else
# define FNODISCARD(...) NODISCARD
# define GLOBAL constexpr
# define MAYBE_UNUSED
#endif

#if CPPVER_LEAST(14)
# ifndef FDEPRECATED
#  define FDEPRECATED(...) [[deprecated]]
# endif
# define DEPRECATED [[deprecated]]
#else
# define DEPRECATED
# define FDEPRECATED(...)
#endif

#if CPPVER_LEAST(11)
# define CARRIES_DEPENDENCY [[carries_dependency]]
# define NOEXCEPT noexcept
# define CNOEXCEPT const NOEXCEPT
# define NORETURN [[noreturn]]
# define THREAD_LOCAL thread_local
#else
# define CARRIES_DEPENDENCY
# define THREAD_LOCAL __thread
#endif

#if !CPPVER_LEAST(11)
# undef RSTRIFY
# undef U8STRIFY
# undef U16STRIFY
# undef U32STRIFY
# undef USTRIFY

# define U8STRIFY LSTRIFY
# define U16STRIFY LSTRIFY
# define U32STRIFY LSTRIFY
# define USTRIFY LSTRIFY
#endif

#ifdef __cplusplus
# define CONST const
# define PURE = 0
#endif

#if !defined(LIKELY) || !defined(LIKELY)
# if __has_cpp_attribute(likely) && \
  __has_cpp_attribute(unlikely)
#  define LIKELY [[likely]]
#  define UNLIKELY [[unlikely]]
# else
#  define LIKELY
#  define UNLIKELY
# endif
#endif

#ifndef FALLTHROUGH
# if __has_cpp_attribute(fallthrough)
#  define FALLTHROUGH [[fallthrough]]
# elif __has_cpp_attribute(gnu::fallthrough)
#  define FALLTHROUGH [[gnu::fallthrough]]
# elif __has_cpp_attribute(clang::fallthrough)
#  define FALLTHROUGH [[clang::fallthrough]]
# elif __has_attribute(fallthrough) || defined(__GNUC__)
#  define FALLTHROUGH __attribute__((fallthrough))
# else
#  define FALLTHROUGH
# endif
#endif

#ifndef NODISCARD
# if __has_cpp_attribute(gnu::warn_unused_result)
#  define NODISCARD [[gnu::warn_unused_result]]
# elif __has_attribute(warn_unused_result) || defined(__GNUC__)
#  define NODISCARD __attribute__((warn_unused_result))
# elif defined(EFLI_MSVC_) && (_MSC_VER >= 1700)
#  define NODISCARD _Check_return_
# else
#  define NODISCARD
# endif
#endif

#ifndef NOEXCEPT
# if __has_attribute(nothrow) || defined(__GNUC__)
#  define NOEXCEPT __attribute__((nothrow))
# else
#  define NOEXCEPT
# endif
#endif

#ifndef NORETURN
# if __has_attribute(noreturn) || defined(__GNUC__)
#  define NORETURN __attribute__((noreturn))
# elif defined(EFLI_MSVC_)
#  define NORETURN __declspec(noreturn)
# else
#  define NORETURN
# endif
#endif

/*
 * Used to determine the standard for the current C++ version.
 * The standard is the value of XX in `C++XX`
 */

#if CPPVER_MATCH(23)
# define COMPILER_STANDARD 23
#elif CPPVER_MATCH(20)
# define COMPILER_STANDARD 20
#elif CPPVER_MATCH(17)
# define COMPILER_STANDARD 17
#elif CPPVER_MATCH(14)
# define COMPILER_STANDARD 14
#elif CPPVER_MATCH(11)
# define COMPILER_STANDARD 11
#else
# define COMPILER_STANDARD 97
#endif

EFL_REGION_CLOSE("config.macro.cpp")


/// Defines macros for things specific to individual compilers
EFL_REGION_BEGIN("config.macro.compiler")
// ---------------------------------------------------------------------------------------------------------------- //

#ifndef COMPILER_CUSTOM
#if defined(__clang__)
# define COMPILER_LLVM "LLVM"
# if defined(__ELLCC__)
#  define COMPILER_ELLCC ELLCC
#  define COMPILER_CURR VCOMPILER_ELLCC
#  define COMPILER_TYPE COMPILER_ELLCC
# elif defined(__INTEL_LLVM_COMPILER)
#  define COMPILER_ICX ICX
#  define COMPILER_CLANG CLANG
#  define COMPILER_CURR VCOMPILER_ICX
#  define COMPILER_TYPE COMPILER_ICX
# else
#  define COMPILER_CLANG CLANG
#  define COMPILER_CURR VCOMPILER_CLANG
#  define COMPILER_TYPE COMPILER_CLANG
# endif
#elif defined(__INTEL_COMPILER)
# define COMPILER_GNU "GNU"
# define COMPILER_ICC ICC
# define COMPILER_CURR VCOMPILER_ICC
# define COMPILER_TYPE COMPILER_ICC
#elif defined(__GNUC__)
# define COMPILER_GNU "GNU"
# if defined(__MINGW32__)
#  define COMPILER_MINGW MINGW
#  define COMPILER_GCC GCC
#  define COMPILER_CURR VCOMPILER_MINGW
#  define COMPILER_TYPE COMPILER_MINGW
# elif defined(__NVCOMPILER)
#  define COMPILER_NVCPP NVCPP
#  define COMPILER_CURR VCOMPILER_NVCPP
#  define COMPILER_TYPE COMPILER_NVCPP
# else
#  define COMPILER_GCC GCC
#  define COMPILER_CURR VCOMPILER_GCC
#  define COMPILER_TYPE COMPILER_GCC
# endif
#elif defined(EFLI_MSVC_)
# define COMPILER_MSVC MSVC
# define COMPILER_CURR VCOMPILER_MSVC
# define COMPILER_TYPE COMPILER_MSVC
#else
# define COMPILER_UNKNOWN UNKNOWN
# define COMPILER_CURR VCOMPILER_UNKNOWN
# define COMPILER_TYPE COMPILER_UNKNOWN
# if COMPILER_STRICT_CONFORMANCE
#  error Your compiler is currently unsupported!
# endif
#endif
#endif // COMPILER_CUSTOM

#define EFL_COMPILER_NAME STRIFY(COMPILER_TYPE)

/**
 * This defines the keyword versions of some logical operators for C++17
 * and below on MSVC, since they forgot to do that for some reason
 */

#if CPPVER_MOST(17) && defined(COMPILER_MSVC)
# define not !
# define and &&
# define or ||
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
# define COMPILER_FUNCTION __PRETTY_FUNCTION__
#elif defined(COMPILER_MSVC)
# define COMPILER_FUNCTION __FUNCSIG__
#else
# define COMPILER_FUNCTION __func__
# undef  COMPILER_FUNCTION_CLASSIC
# define COMPILER_FUNCTION_CLASSIC 1
#endif

#if __has_builtin(__builtin_unreachable) || defined(__GNUC__)
# define EFLI_UNREACHABLE_() __builtin_unreachable()
#elif defined(COMPILER_MSVC)
# define EFLI_UNREACHABLE_() __assume(false)
#else
# if __has_builtin(__builtin_abort)
#  define EFLI_UNREACHABLE_() __builtin_abort()
# else
/// Requires <cstdlib>.
#  define EFLI_UNREACHABLE_() ::efl::config::H::abort()
#  define EFLI_INCLUDE_ABORT_ 1
# endif
#endif

/// `std::unreachable` in macro form.
#define EFL_UNREACHABLE(...) EFLI_UNREACHABLE_()


#if defined(COMPILER_CLANG)
# define EFL_MESSAGE(...) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"") \
  EFL_COMPILER_PRAGMA(message #__VA_ARGS__) \
  _Pragma("clang diagnostic pop")
#elif defined(COMPILER_GNU) || defined(COMPILER_LLVM)
# define EFL_MESSAGE(...) EFL_COMPILER_PRAGMA(message #__VA_ARGS__)
#elif defined(COMPILER_MSVC)
# define EFL_MESSAGE(...) EFL_COMPILER_PRAGMA(message(#__VA_ARGS__))
#else
# define EFL_MESSAGE(...)
# define EFL_TODO(...) EFL_COMPILER_PRAGMA(todo #__VA_ARGS__)
#endif

#ifndef EFL_TODO
# define EFL_TODO(...) EFL_MESSAGE("TODO: " #__VA_ARGS__)
#endif

#if __has_attribute(diagnose_if)
# define EFLI_DIAGNOSE_IF_(expr, msg, level) \
  __attribute__((diagnose_if(expr, msg, level)))
#else
# define EFLI_DIAGNOSE_IF_(...)
#endif

/// Prints a warning at parse-time if true.
#define EFL_WARN_IF(expr, msg) \
  EFLI_DIAGNOSE_IF_((expr), msg, "warning")
/// Errors at parse-time if true. 
#define EFL_ERROR_IF(expr, msg) \
  EFLI_DIAGNOSE_IF_((expr), msg, "error")

#if defined(COMPILER_MINGW)
# define CLRCALL __clrcall
# define STDCALL __stdcall
# define VECCALL
#elif defined(COMPILER_MSVC)
# define CLRCALL __clrcall
# define STDCALL __stdcall
# define VECCALL __vectorcall
#else
# define CDECL
# define CLRCALL
# define VECCALL
# define FASTCALL
#endif

#if defined(COMPILER_LLVM) || defined(COMPILER_MSVC)
# define RESTRICT __restrict
#elif defined(COMPILER_GNU)
# define RESTRICT __restrict__
#else
# define RESTRICT
#endif

#if __has_attribute(nonnull) || defined(__GNUC__)
# define NONNULL(...) __attribute__((nonnull))
#else
# define NONNULL(...)
#endif

#if __has_attribute(returns_nonnull) || defined(__GNUC__)
# define RETURNS_NONNULL __attribute__((returns_nonnull))
#elif defined(COMPILER_MSVC)
# define RETURNS_NONNULL _Ret_notnull_
#else
# define RETURNS_NONNULL
#endif

#ifndef FORCE_INLINE
// Keeping for backwards compat.
# define FORCE_INLINE EFL_MESSAGE( \
  This keyword has been deprecated. \
  Prefer "ALWAYS_INLINE".) inline
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
# if __has_cpp_attribute(gnu::always_inline)
#  if __has_cpp_attribute(gnu::artificial)
#   define EFLI_INLINE_ATTRS_ gnu::always_inline, gnu::artificial
#  else
#   define EFLI_INLINE_ATTRS_ gnu::always_inline
#  endif
#  define ALWAYS_INLINE [[EFLI_INLINE_ATTRS_]] inline
#  define EFLI_INLINE_TY_ 1
# else // GNU/LLVM, but no C++ style attribute.
#  define EFLI_INLINE_ATTRS_ always_inline
#  define ALWAYS_INLINE __attribute__((EFLI_INLINE_ATTRS_)) inline
#  define EFLI_INLINE_TY_ 0
# endif // always_inline
# define NOINLINE __attribute__((noinline))
#elif defined(COMPILER_NVCPP)
# define ALWAYS_INLINE __forceinline__ inline
# define NOINLINE __noinline__
#elif defined(COMPILER_MSVC)
# define ALWAYS_INLINE __forceinline
# define NOINLINE __declspec(noinline)
#else
# define ALWAYS_INLINE inline
# define NOINLINE
#endif // always_inline, noinline

#if defined(EFLI_INLINE_TY_)
# if __has_cpp_attribute(gnu::flatten) && (EFLI_INLINE_TY_ == 1)
/// Inlines and flattens the marked function.
#  define AGGRESSIVE_INLINE \
  [[EFLI_INLINE_ATTRS_, gnu::flatten]] inline
# elif (__has_attribute(flatten) || defined(__GNUC__)) && \
  (EFLI_INLINE_TY_ == 0)
/// Inlines and flattens the marked function.
#  define AGGRESSIVE_INLINE \
   __attribute__((EFLI_INLINE_ATTRS_, flatten)) inline
# else
#  define AGGRESSIVE_INLINE ALWAYS_INLINE
# endif // aggressive_inline
# undef EFLI_INLINE_TY_
#else
# define AGGRESSIVE_INLINE ALWAYS_INLINE
#endif

#if defined(COMPILER_MSVC)
/// Inlines the marked function.
# define HINT_INLINE __forceinline
#else
# define HINT_INLINE inline
#endif

#if defined(COMPILER_CLANG)
/// Like `static`, but applicable to classes.
# define COMPILER_HIDDEN [[clang::internal_linkage]]
#elif __has_attribute(internal_linkage)
/// Like `static`, but applicable to classes.
# define COMPILER_HIDDEN __attribute__((internal_linkage))
#else
# define COMPILER_HIDDEN
#endif

#if __has_cpp_attribute(gnu::malloc)
# define COMPILER_UNALIASED [[gnu::malloc]]
#elif __has_attribute(malloc)
# define COMPILER_UNALIASED __attribute__((malloc))
#elif __has_attribute(__malloc__) || defined(__GNUC__)
# define COMPILER_UNALIASED __attribute__((__malloc__))
#elif defined(COMPILER_MSVC)
# define COMPILER_UNALIASED __declspec(restrict)
#else
# define COMPILER_UNALIASED
#endif

#if __has_cpp_attribute(clang::no_sanitize)
# define NOSANITIZE(...) [[clang::no_sanitize(__VA_ARGS__)]]
#elif __has_attribute(no_sanitize)
# define NOSANITIZE(...) __attribute__((no_sanitize(__VA_ARGS__)))
#endif
#ifndef NOSANITIZE
# define NOSANITIZE(...)
#endif

#if CPPVER_LEAST(20) && (defined(__GNUC__) || defined(__clang__))
# if __has_cpp_attribute(clang::coro_wrapper) && \
  __has_cpp_attribute(clang::coro_return_type) && \
  __has_cpp_attribute(clang::coro_only_destroy_when_complete) && \
  __has_cpp_attribute(clang::coro_lifetimebound)
#  define CORO_ANALYZE [[clang::coro_return_type, clang::coro_lifetimebound]]
#  define CORO_COMPLETION_DTOR [[clang::coro_only_destroy_when_complete]]
#  define CORO_WRAPPER [[clang::coro_wrapper]]
#  define EFLI_CORO_ 1
# elif __has_attribute(coro_wrapper) && \
  __has_attribute(coro_return_type) && \
  __has_attribute(coro_only_destroy_when_complete) && \
  __has_attribute(coro_lifetimebound)
#  define CORO_ANALYZE __attribute__((coro_return_type, coro_lifetimebound))
#  define CORO_COMPLETION_DTOR __attribute__((coro_only_destroy_when_complete))
#  define CORO_WRAPPER __attribute__((coro_wrapper))
#  define EFLI_CORO_ 1
# endif
#endif
#ifndef EFLI_CORO_
# define CORO_ANALYZE
# define CORO_COMPLETION_DTOR
# define CORO_WRAPPER
#else
# undef EFLI_CORO_
#endif

#if __has_cpp_attribute(gsl::Owner)
# define GSL_OWNER [[gsl::Owner]]
#else
# define GSL_OWNER
#endif

#if __has_cpp_attribute(gsl::Pointer)
# define GSL_POINTER [[gsl::Pointer]]
#else
# define GSL_POINTER
#endif

#if __has_cpp_attribute(gnu::hot) && \
 __has_cpp_attribute(gnu::cold)
# define COMPILER_HOT [[gnu::hot]]
# define COMPILER_COLD [[gnu::cold]]
#elif (__has_attribute(hot) && __has_attribute(cold)) || defined(__GNUC__)
# define COMPILER_HOT __attribute__((hot))
# define COMPILER_COLD __attribute__((cold))
#else
# define COMPILER_HOT
# define COMPILER_COLD
#endif

#if defined(COMPILER_MSVC)
# define COMPILER_UUID(value) __declspec(COMPILER_UUID_I(value))
# define COMPILER_UUID_I(value) uuid(STRIFY(value))
#else
# define COMPILER_UUID(...)
#endif

#if defined(COMPILER_MSVC)
# define MSVC_EMPTY_BASES __declspec(empty_bases)
#else
# define MSVC_EMPTY_BASES
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
# define COMPILER_FUNCTION __PRETTY_FUNCTION__
#elif defined(COMPILER_MSVC)
# define COMPILER_FUNCTION __FUNCSIG__
#else
# define COMPILER_FUNCTION __func__
# undef  COMPILER_FUNCTION_CLASSIC
# define COMPILER_FUNCTION_CLASSIC 1
#endif

#if !EFLI_HAS_CPP_ATTRIBUTE_
# undef __has_cpp_attribute
#endif

/**
 * Defines wrappers around compiler specific diagnostics.
 * Makes things easier to read and less finicky in general
 */

#define EFLI_GENERIC_DIAG_(nm, sv, msg) \
 EFL_COMPILER_PRAGMA(nm diagnostic push) \
 EFL_COMPILER_PRAGMA(nm diagnostic sv msg)
#define EFLI_GENERIC_POP_(nm, type) \
 EFL_COMPILER_PRAGMA(nm type pop)

/**
 * Check out https://developer.arm.com/documentation/101754/0620/armclang-Reference/Compiler-specific-Pragmas
 * for more info on LLVM pragmas
 */
#ifdef COMPILER_LLVM
# define LLVM_DIAGNOSTIC(sv, msg)          \
  EFLI_GENERIC_DIAG_(clang, sv, msg)
# define LLVM_IGNORED(msg)                 \
  LLVM_DIAGNOSTIC(ignored, msg)
# define LLVM_WARNING(msg)                 \
  LLVM_DIAGNOSTIC(warning, msg)
# define LLVM_ERROR(msg)                   \
  LLVM_DIAGNOSTIC(error, msg)
# define LLVM_POP(type)                    \
  EFLI_GENERIC_POP_(clang, type)
#else
# define LLVM_DIAGNOSTIC(...)
# define LLVM_IGNORED(...)
# define LLVM_WARNING(...)
# define LLVM_ERROR(...)
# define LLVM_POP(...)
#endif

/**
 * Check out https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html for
 * more info on GNU pragmas
 */
#ifdef COMPILER_GNU
# define GNU_DIAGNOSTIC(sv, msg)           \
  EFLI_GENERIC_DIAG_(GCC, sv, msg)
# define GNU_IGNORED(msg)                  \
  GNU_DIAGNOSTIC(ignored, msg)
# define GNU_WARNING(msg)                  \
  GNU_DIAGNOSTIC(warning, msg)
# define GNU_ERROR(msg)                    \
  GNU_DIAGNOSTIC(error, msg)
# define GNU_POP(type)                     \
  EFLI_GENERIC_POP_(GCC, type)
#else
# define GNU_DIAGNOSTIC(...)
# define GNU_IGNORED(...)
# define GNU_WARNING(...)
# define GNU_ERROR(...)
# define GNU_POP(...)
#endif

/**
 * Defining these for consistency's sake, they aren't anything special
 */

#define COMPILER_FILE __FILE__
#define COMPILER_LINE __LINE__

#if COMPILER_DEBUG
# define DEBUG_ONLY(...) __VA_ARGS__
#else
# define DEBUG_ONLY(...)
#endif

LLVM_IGNORED("-Wkeyword-macro")
#if defined(__cplusplus) && !defined(COMPILER_MSVC)
/// Remove the deprecated `register` keyword
# define register
#endif
LLVM_POP(diagnostic)

EFL_REGION_CLOSE("config.macro.compiler")


/**
 * Defines macros for platform specific stuff.
 * Probably not perfect, but can generally detect
 * OS, architecture, etc.
 */
EFL_REGION_BEGIN("config.macro.platform")
// ---------------------------------------------------------------------------------------------------------------- //

/// Platform detection
#ifndef PLATFORM_CUSTOM
#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
# define PLATFORM_WINDOWS "WINDOWS"
# define PLATFORM_CURR VPLATFORM_WINDOWS
# if defined(_WIN16) || defined(__WINDOWS__)
#  define PLATFORM_WIN_16 WIN_16
#  define PLATFORM_TYPE PLATFORM_WIN_16
# elif defined(_WIN64)
#  define PLATFORM_WIN_64 WIN_64
#  define PLATFORM_TYPE PLATFORM_WIN_64
# else
#  define PLATFORM_WIN_32 WIN_32
#  define PLATFORM_TYPE PLATFORM_WIN_32
# endif // Windows subtype
#elif defined(__APPLE__)
# define PLATFORM_APPLE "APPLE"
# if defined(__MACH__)
#  define PLATFORM_MACOS MACOS
#  define PLATFORM_CURR VPLATFORM_MACOS
#  define PLATFORM_TYPE PLATFORM_MACOS
# else
#  define PLATFORM_IOS IOS
#  define PLATFORM_CURR VPLATFORM_IOS
#  define PLATFORM_TYPE PLATFORM_IOS
# endif // defined(__MACH__)
#elif defined(__HAIKU__)
# define PLATFORM_HAIKU HAIKU
# define PLATFORM_CURR VPLATFORM_HAIKU
# define PLATFORM_TYPE PLATFORM_HAIKU
#elif defined(__ANDROID__)
# define PLATFORM_ANDROID ANDROID
# define PLATFORM_CURR VPLATFORM_ANDROID
# define PLATFORM_TYPE PLATFORM_ANDROID
#elif defined(__linux__)
# define PLATFORM_LINUX LINUX
# define PLATFORM_CURR VPLATFORM_LINUX
# define PLATFORM_TYPE PLATFORM_LINUX
#elif defined(sun) || defined(__sun)
# if defined(__SVR4) || defined(__svr4__)
#  define PLATFORM_SOLARIS SOLARIS
#  define PLATFORM_CURR VPLATFORM_SOLARIS
#  define PLATFORM_TYPE PLATFORM_SOLARIS
# else
#  define PLATFORM_SUNOS SUNOS
#  define PLATFORM_CURR VPLATFORM_SUNOS
#  define PLATFORM_TYPE PLATFORM_SUNOS
# endif // Solaris check
#else
# define PLATFORM_UNKNOWN UNKNOWN
# define PLATFORM_CURR VPLATFORM_UNKNOWN
# define PLATFORM_TYPE PLATFORM_UNKNOWN
# if COMPILER_STRICT_CONFORMANCE
#  error Your platform is currently unsupported!
# endif
#endif
#endif // PLATFORM_CUSTOM

/// Architecture detection
#ifndef ARCH_CUSTOM
#if defined(__aarch64)
# define ARCH_ARM64 "ARM64"
# define EFL_ARCH_CURR REG64
# define ARCH_TYPE ARCH_ARM64
#elif defined(__arm__) || defined(__thumb__) || \
   defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT)
# define ARCH_ARM "ARM"
# if defined(__thumb__) || defined(_M_ARMT)
#  define ARCH_ARM_THUMB "ARM_THUMB"
#  define EFL_ARCH_CURR 0b0110 // REG16 | REG32
#  define ARCH_TYPE ARCH_ARM_THUMB
# else
#  define EFL_ARCH_CURR REG32
#  define ARCH_TYPE ARCH_ARM
# endif // Thumb detection
#elif defined (__amd64__) || defined(_M_AMD64)
# define ARCH_AMD "AMD"
# if defined(_LP32) || defined(__LP32__)
#  define ARCH_AMD32 "AMD32"
#  define EFL_ARCH_CURR REG32
#  define ARCH_TYPE ARCH_AMD32
# else
#  define ARCH_AMD64 "AMD64"
#  define EFL_ARCH_CURR REG64
#  define ARCH_TYPE ARCH_AMD64
# endif // 64 bit check
#elif defined(i386) || defined(__i386) || defined(__i386)  ||   \
  defined(__IA32__) || defined(_M_I86) || defined(_M_IX86) ||   \
  defined(_X86_) || defined(__I86__)
# define ARCH_x86 "x86"
# if defined(_M_I86) && !(defined(__386__) || defined(_M_I386))
#  define ARCH_x86_16 x86_16
#  define EFL_ARCH_CURR REG16
#  define ARCH_TYPE ARCH_x86_16
# else
#  define ARCH_x86_32 x86_32
#  define EFL_ARCH_CURR REG32
#  define ARCH_TYPE ARCH_x86_32
# endif // 16 bit check
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || \
  defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
# define ARCH_ITANIUM ITANIUM
# define EFL_ARCH_CURR REG64
# define ARCH_TYPE ARCH_ITANIUM
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__)
# define ARCH_M68k M68k
# define EFL_ARCH_CURR 0b0110 // REG16 | REG32
# define ARCH_TYPE ARCH_M68k
#elif defined(mips) || defined(__mips) || defined(__mips__)
# define ARCH_MIPS "MIPS"
# if (defined(_MIPS_ISA) && defined(_MIPS_ISA_MIPS1) || defined(_MIPS_ISA_MIPS2)) || \
    !(defined(__MIPS_ISA3__) || defined(__MIPS_ISA4__))                            || \
    (defined(__mips) && (__mips < 3))
#  define ARCH_MIPS32 MIPS32
#  define EFL_ARCH_CURR REG32
#  define ARCH_TYPE ARCH_MIPS32
# else
#  define ARCH_MIPS64 MIPS64
#  define EFL_ARCH_CURR REG64
#  define ARCH_TYPE ARCH_MIPS64
# endif // 32 bit ISA check
#else
# define ARCH_UNKNOWN UNKNOWN
# define EFL_ARCH_CURR 0b0000
# define ARCH_TYPE ARCH_UNKNOWN
# if COMPILER_STRICT_CONFORMANCE
#  error Your architecture is currently unsupported!
# endif
#endif
#endif // ARCH_CUSTOM

#ifndef MICROARCH_TYPE
#if defined(ARCH_x86)
// TODO: Microarchitecture Detection
// May not end up using this.
#endif
#endif // MICROARCH_TYPE

#define EFL_PLATFORM_NAME STRIFY(PLATFORM_TYPE)
#define EFL_ARCH_NAME STRIFY(ARCH_TYPE)

#if   (EFL_ARCH_CURR & REG64) != 0
# define EFL_ARCH_REGMAX 64
#elif (EFL_ARCH_CURR & REG32) != 0
# define EFL_ARCH_REGMAX 32
#elif (EFL_ARCH_CURR & REG16) != 0
# define EFL_ARCH_REGMAX 16
#elif (EFL_ARCH_CURR & REG8)  != 0
# define EFL_ARCH_REGMAX 8
#else
# error Could not determine ARCH_REGMAX!
#endif

#ifndef EFL_ARCH_BITS
# define EFL_ARCH_BITS CHAR_BIT
#endif

EFL_REGION_CLOSE("config.macro.platform")


/*
 * Checks the `COMPILER_BOOST_EXTEND` macro defined previously.
 * If it evaluates to true, BoostPP will be included,
 * and extension macros will be defined
 */
EFL_REGION_BEGIN("config.macro.extend")
// ---------------------------------------------------------------------------------------------------------------- //

/// TODO: Complete implementation? Maybe not.
#if COMPILER_BOOST_EXTEND
# include <boost/preprocessor/logical.hpp>
# define PP_BOOL(x) BOOST_PP_BOOL(x)
# define PP_NOT(x) BOOST_PP_NOT(x)
# define PP_AND(x, y) BOOST_PP_AND(x, y)
#else
# define PP_BOOL(x)        ~
# define PP_NOT(x)         ~
# define PP_AND(x, y)      ~
#endif

EFL_REGION_CLOSE("config.macro.extend")


/// Provides common macros that are used in source
EFL_REGION_BEGIN("config.macro.common")
// ---------------------------------------------------------------------------------------------------------------- //

/// Concise perfect forwarding, requires <utility>.
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

/**
 * Allows for generals compile failures for templates when instantiated.
 * Requires <type_traits>.
 */
#define COMPILE_FAILURE(type, message) \
 static_assert(std::is_same<type, struct Fail>::value, message);

EFL_REGION_CLOSE("config.macro.common")


/// Provides enums for use in switching behaviour
EFL_REGION_BEGIN("config.type.enum")
// ---------------------------------------------------------------------------------------------------------------- //
#ifndef _EFL_CONFIG_PERMANENT
#define _EFL_CONFIG_PERMANENT

#include <climits>
#ifdef EFLI_INCLUDE_ABORT_
# include <cstdlib>
#endif

namespace efl {

//=== Compiler Config ===//
namespace config {
enum class CompilerSuperType {
  NONE    =   VCOMPILER_UNKNOWN,
  GNU     =   VCOMPILER_GNU,
  LLVM    =   VCOMPILER_LLVM,
};

enum class CompilerType {
  UNKNOWN =   VCOMPILER_UNKNOWN,
  GCC     =   VCOMPILER_GCC,
  CLANG   =   VCOMPILER_CLANG,
  MSVC    =   VCOMPILER_MSVC,
  ICC     =   VCOMPILER_ICC,
  ICX     =   VCOMPILER_ICX,
  MINGW   =   VCOMPILER_MINGW,
  NVCPP   =   VCOMPILER_NVCPP,
  ELLCC   =   VCOMPILER_ELLCC,
};

enum class StandardType {
  CPP23   =   23,
  CPP20   =   20,
  CPP17   =   17,
  CPP14   =   14,
  CPP11   =   11,
  CPP97   =   97,
};

struct Compiler {
  static constexpr auto type = CompilerType::COMPILER_TYPE;
  static constexpr auto supertype = CompilerSuperType(COMPILER_CURR & VCOMPILER_SUPERTYPE_MASK);
  static constexpr auto standard = StandardType::EFL_CAT(CPP, COMPILER_STANDARD);
  static constexpr decltype(EFL_COMPILER_NAME) name = EFL_COMPILER_NAME;
};
} // namespace config

//=== Platform Config ===//
namespace config {
enum class PlatformType {
  UNKNOWN = VPLATFORM_UNKNOWN,
  WIN_16  = VPLATFORM_WIN_16,
  WIN_32  = VPLATFORM_WIN_32,
  WIN_64  = VPLATFORM_WIN_64,
  LINUX   = VPLATFORM_LINUX,
  ANDROID = VPLATFORM_ANDROID,
  MACOS   = VPLATFORM_MACOS,
  IOS     = VPLATFORM_IOS,
  HAIKU   = VPLATFORM_HAIKU,
  SOLARIS = VPLATFORM_SOLARIS,
  SUNOS   = VPLATFORM_SUNOS,
};

struct Platform {
  static constexpr PlatformType type = PlatformType::PLATFORM_TYPE;
  static constexpr decltype(EFL_PLATFORM_NAME) name = EFL_PLATFORM_NAME;
};
} // namespace config

//=== Architecture Config ===//
namespace config {
namespace H {
  typedef decltype(sizeof(0)) inl_szt_;
} // namespace detail_

struct Arch {
  static constexpr decltype(EFL_ARCH_NAME) name = EFL_ARCH_NAME;
  static constexpr H::inl_szt_ archMax = EFL_ARCH_REGMAX;
  static constexpr H::inl_szt_ bitCount = EFL_ARCH_BITS;
  static_assert((archMax / bitCount) == sizeof(void*),
    "Uneven `archMax`, try using a custom ARCH.");
};

template <typename T>
struct Bit {
  static constexpr auto count = Arch::bitCount;
  static constexpr auto size = sizeof(T) * count;
};

#ifdef EFLI_INCLUDE_ABORT_
namespace H { using ::std::abort; }
# undef EFLI_INCLUDE_ABORT_
#endif

NORETURN ALWAYS_INLINE 
void unreachable() NOEXCEPT 
{ EFL_UNREACHABLE(); }

#if CPPVER_LEAST(14)
template <typename T>
GLOBAL auto bitsizeof = Bit<T>::size;
#endif // CPPVER_LEAST(17)
} // namespace config

} // namespace efl

#endif // _EFL_CONFIG_PERMANENT
EFL_REGION_CLOSE("config.type.enum")

#endif  // EFL_CONFIG_SINGLE_HPP
