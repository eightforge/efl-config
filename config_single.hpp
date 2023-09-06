#if !defined(EIGHTFOLD_CONFIG_SINGLE_HPP) && !defined(EIGHTFOLD_CONFIG)
#define EIGHTFOLD_CONFIG_SINGLE_HPP
#define EIGHTFOLD_CONFIG

#define COMPILER_PRAGMA(...) _Pragma(#__VA_ARGS__)

#if defined(_MSC_VER) || defined(_MSVC_LANG)
#  define REGION_BEGIN(name) COMPILER_PRAGMA(region name)
#  define REGION_CLOSE(comment) COMPILER_PRAGMA(endregion comment)
#elif defined(__CODEGEARC__)
#  define REGION_BEGIN(name) COMPILER_PRAGMA(region name)
#  define REGION_CLOSE(...) COMPILER_PRAGMA(end_region)
#else
#  define REGION_BEGIN(...)
#  define REGION_CLOSE(...)
#endif


/// Provides options for modifying default config settings
REGION_BEGIN("config.macro.opts")
// ---------------------------------------------------------------------------------------------------------------- //

#ifndef COMPILER_STRICT_CONFORMANCE
#  if defined(__INTEL_COMPILER) || (defined(_MSC_VER) && defined(_MSVC_TRADITIONAL))
#    define COMPILER_STRICT_CONFORMANCE 1
#  else
#    define COMPILER_STRICT_CONFORMANCE 0
#  endif
#endif

#ifdef NDEBUG
#  undef COMPILER_DEBUG
#  define COMPILER_DEBUG 0
#elif !defined(COMPILER_DEBUG)
#  define COMPILER_DEBUG 0
#endif

#ifndef COMPILER_UNICODE_VERSION
/**
 * Determines which prefix will be used with `USTRINGIFY`.
 * Possible values: 8, 16, 32
 */
#  define COMPILER_UNICODE_VERSION 8
#endif

#ifndef COMPILER_RESCAN_COUNT
/// Make sure you have a beefy pc for large values
#  define COMPILER_RESCAN_COUNT 5
#endif

#ifndef COMPILER_FUNCTION_CLASSIC
/// If `COMPILER_FUNCTION` uses __func__ or pretty function
#  define COMPILER_FUNCTION_CLASSIC 0
#endif

#ifndef COMPILER_UNDEF_CORE
/// If macros will be undefined in core
#  define COMPILER_UNDEF_CORE 0
#endif

/// Allows `Boost.Preprocessor` to be used for more advanced macros
#ifndef COMPILER_BOOST_EXTEND
#  if defined(__has_include) && __has_include(<boost/preprocessor.hpp>)
#    define COMPILER_BOOST_EXTEND 1
#  else
#    define COMPILER_BOOST_EXTEND 0
#  endif
#endif

REGION_CLOSE("config.macro.opts")


/**
 * Provides essential defines for the rest of config.
 * Contextless, only implements object-like macros
 */
REGION_BEGIN("config.macro.meta")
// ---------------------------------------------------------------------------------------------------------------- //

#if COMPILER_UNDEF_CORE
#  undef COMPILER_USTRINGIFY_VER
#  undef XCAT
#  undef CAT
#  undef TRICAT
#  undef EXPAND
#  undef EAT
#  undef XSTRINGIFY
#  undef STRINGIFY
#  undef LSTRINGIFY
#  undef RSTRINGIFY
#  undef U8STRINGIFY
#  undef U16STRINGIFY
#  undef U32STRINGIFY
#  undef USTRINGIFY
#  undef COMPILER_CPP97
#  undef COMPILER_CPP98
#  undef COMPILER_CPP11
#  undef COMPILER_CPP14
#  undef COMPILER_CPP17
#  undef COMPILER_CPP20
#  undef COMPILER_CPP23
#  undef CPPVER97_NEXT
#  undef CPPVER98_NEXT
#  undef CPPVER11_NEXT
#  undef CPPVER14_NEXT
#  undef CPPVER17_NEXT
#  undef CPPVER20_NEXT
#  undef CPPVER23_NEXT
#  undef VCOMPILER_UNKNOWN
#  undef VCOMPILER_GNU
#  undef VCOMPILER_LLVM
#  undef VCOMPILER_GCC
#  undef VCOMPILER_CLANG
#  undef VCOMPILER_MSVC
#  undef VCOMPILER_ICC
#  undef VCOMPILER_ICX
#  undef VCOMPILER_MINGW
#  undef VCOMPILER_NVCPP
#  undef VCOMPILER_ELLCC
#  undef VCOMPILER_BIT_COUNT
#  undef COMPILER_ELLCC
#  undef COMPILER_CURR
#  undef COMPILER_NAME
#  undef COMPILER_ICX
#  undef COMPILER_CLANG
#  undef COMPILER_LLVM
#  undef COMPILER_ICC
#  undef COMPILER_GNU
#  undef COMPILER_MINGW
#  undef COMPILER_GCC
#  undef COMPILER_NVCPP
#  undef COMPILER_MSVC
#  undef COMPILER_UNKNOWN
#  undef COMPILER_CPP_VERSION
#  undef CPPVER_LEAST
#  undef CPPVER_NEXT
#  undef CPPVER_MATCH
#  undef UNREACHABLE_I
#  undef FORCE_INLINE
#  undef UNREACHABLE
#  undef CLRCALL
#  undef STDCALL
#  undef VECCALL
#  undef RESTRICT
#  undef COMPILER_UUID_I
#  undef COMPILER_UUID
#  undef ASSUME
#  undef CONSTEVAL
#  undef FDEPRECATED
#  undef FNODISCARD
#  undef LIKELY
#  undef NO_UNIQUE_ADDRESS
#  undef UNLIKELY
#  undef FALLTHROUGH
#  undef GLOBAL
#  undef MAYBE_UNUSED
#  undef NODISCARD
#  undef DEPRECATED
#  undef CARRIES_DEPENDENCY
#  undef CNOEXCEPT
#  undef NOEXCEPT
#  undef NORETURN
#  undef PURE
#  undef COMPILER_FILE
#  undef COMPILER_LINE
#  undef COMPILER_FUNCTION
#  undef DEBUG_ONLY
#  undef CHAIN_HEAD
#endif

#define COMPILER_CPP97 199711L
#define COMPILER_CPP98 199711L
#define COMPILER_CPP11 201103L
#define COMPILER_CPP14 201402L
#define COMPILER_CPP17 201703L
#define COMPILER_CPP20 202002L
#define COMPILER_CPP23 202304L           /// Just a guess for now

#define CPPVER97_NEXT 11
#define CPPVER98_NEXT 11
#define CPPVER11_NEXT 14
#define CPPVER14_NEXT 17
#define CPPVER17_NEXT 20
#define CPPVER20_NEXT 23
#define CPPVER23_NEXT 26

/**
 * First 2 bits are used to identify the compiler supertype (0b01 for GNU, 0b10 for LLVM).
 * This is used because many "compiler dependent" features only vary between supertypes.
 * Other than MSVC, your average compiler will be based on GCC or LLVM
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

REGION_CLOSE("config.macro.meta")


/**
 * Defines commonly used function-like macros.
 * Examples include CAT, EAT, STRINGIFY, etc.
 */
REGION_BEGIN("config.macro.functions")
// ---------------------------------------------------------------------------------------------------------------- //

#define PP_DEFER(...) PP_DEFER_I(__VA_ARGS__)
#define PP_DEFER_I(...) __VA_ARGS__

#define PP_EXPAND(p) PP_DEFER(PP_EXPAND_I p)
#define PP_EXPAND_I(...) __VA_ARGS__

#define PP_EAT(...)

/**
 * Various `CAT` function macros.
 * Allow for the concatenation of 2, 3, or 4 arguments
 */

#define QUADCAT(w, x, y, z) CAT(CAT(w, x), CAT(y, z))
#define TRICAT(x, y, z) CAT(x, CAT(y, z))
#define CAT(x, y) XCAT(x, y)

#if !COMPILER_STRICT_CONFORMANCE
#  define XCAT(x, y) x ## y
#else
#  define XCAT(x, y) XCAT_I(~, x ## y)
#  define XCAT_I(_, x) x
#endif

/**
 * Function macros used to convert random tokens to strings of various types.
 * Supports R, L, u8, u16, u32 prefixes.
 * The macro `COMPILER_UNICODE_VERSION` defined earlier
 * determines the type used for `USTRINGIFY`
 */

#define STRINGIFY(...) XSTRINGIFY(__VA_ARGS__)
#define XSTRINGIFY(...) #__VA_ARGS__

#define LSTRINGIFY(...)    P_XSTRINGIFY(L, __VA_ARGS__)
#define RSTRINGIFY(...)    P_XSTRINGIFY(R, __raw__(__VA_ARGS__)__raw__)
#define U8STRINGIFY(...)   P_XSTRINGIFY(u8, __VA_ARGS__)
#define U16STRINGIFY(...)  P_XSTRINGIFY(u, __VA_ARGS__)
#define U32STRINGIFY(...)  P_XSTRINGIFY(U, __VA_ARGS__)
#define USTRINGIFY(...)    PP_DEFER(P_USTRINGIFY (__VA_ARGS__))

#define P_USTRINGIFY TRICAT(U, COMPILER_UNICODE_VERSION, STRINGIFY)
#define P_XSTRINGIFY(prefix, ...) P_XSTRINGIFY_I(prefix, #__VA_ARGS__)
#define P_XSTRINGIFY_I(prefix, text) prefix ## text

REGION_CLOSE("config.macro.functions")


/**
 * Defines several macro utilities for handling different C++ versions.
 * Also defines aliases for keywords/attributes, which are all caps versions
 * of the normal keywords (`noexcept` -> `NOEXCEPT`; `[[nodiscard]]` -> `NODISCARD`).
 * Also defines `FATTRIBUTE` macros for attributes with messages
 */
REGION_BEGIN("config.macro.cpp")
// ---------------------------------------------------------------------------------------------------------------- //

#if defined(_MSC_VER) || defined(_MSVC_LANG)
#  define COMPILER_CPP_VERSION _MSVC_LANG
#elif defined(__cplusplus) && __cplusplus
#  define COMPILER_CPP_VERSION __cplusplus
#else
#  error This must be compiled with C++!
#endif

#define CPPVER_NEXT(num) PP_DEFER(TRICAT(CPPVER, num, _NEXT))
#define CPPVER_LEAST(num) (COMPILER_CPP_VERSION >= CAT(COMPILER_CPP, num))
#define CPPVER_MOST(num) (COMPILER_CPP_VERSION < CAT(COMPILER_CPP, CPPVER_NEXT(num)))
#define CPPVER_MATCH(num) (CPPVER_LEAST(num) && CPPVER_MOST(num))

#ifndef CPPVER
#  define CPPVER(num) CPPVER_LEAST(num)
#endif

#if CPPVER_LEAST(23)
#  define ASSUME(...) [[assume(__VA_ARGS__)]]
#else
#  define ASSUME(...)
#endif

#if CPPVER_LEAST(20)
#  define CONSTEVAL consteval
#  define VCONSTEXPR constexpr
#  define FDEPRECATED(...) [[deprecated __VA_OPT__((__VA_ARGS__))]]
#  define FNODISCARD(...) [[nodiscard __VA_OPT__((__VA_ARGS__))]]
#  define LIKELY [[likely]]
#  define NO_UNIQUE_ADDRESS [[no_unique_address]]
#  define UNLIKELY [[unlikely]]
#else
#  define CONSTEVAL constexpr
#  define VCONSTEXPR
#  define LIKELY
#  define NO_UNIQUE_ADDRESS
#  define UNLIKELY
#endif

#if CPPVER_LEAST(17)
#  ifndef FNODISCARD
#    define FNODISCARD(...) [[nodiscard]]
#  endif
#  define FALLTHROUGH [[fallthrough]]
#  define GLOBAL inline constexpr
#  define MAYBE_UNUSED [[maybe_unused]]
#  define NODISCARD [[nodiscard]]
#else
#  define FALLTHROUGH
#  define FNODISCARD(...)
#  define GLOBAL
#  define MAYBE_UNUSED
#  define NODISCARD
#endif

#if CPPVER_LEAST(14)
#  ifndef FDEPRECATED
#    define FDEPRECATED(...) [[deprecated]]
#  endif
#  define DEPRECATED [[deprecated]]
#else
#  define DEPRECATED
#  define FDEPRECATED(...)
#endif

#if CPPVER_LEAST(11)
#  define CARRIES_DEPENDENCY [[carries_dependency]]
#  define NOEXCEPT noexcept
#  define CNOEXCEPT const NOEXCEPT
#  define NORETURN [[noreturn]]
#  define THREAD_LOCAL thread_local
#else
#  define CARRIES_DEPENDENCY
#  define NOEXCEPT
#  define NORETURN
#  define THREAD_LOCAL
#endif

#if !CPPVER_LEAST(11)
#  undef RSTRINGIFY
#  undef U8STRINGIFY
#  undef U16STRINGIFY
#  undef U32STRINGIFY
#  undef USTRINGIFY

#  define U8STRINGIFY LSTRINGIFY
#  define U16STRINGIFY LSTRINGIFY
#  define U32STRINGIFY LSTRINGIFY
#  define USTRINGIFY LSTRINGIFY
#endif

#ifdef __cplusplus
#  define PURE = 0
#endif

#if COMPILER_DEBUG
#  undef NOEXCEPT
/// Forces accurate stack frames when handling exceptions
#  define NOEXCEPT
#endif

/**
 * Used to determine the standard for the current C++ version.
 * The standard is the value of XX in `C++XX`
 */

#if CPPVER_MATCH(23)
#  define COMPILER_STANDARD 23
#elif CPPVER_MATCH(20)
#  define COMPILER_STANDARD 20
#elif CPPVER_MATCH(17)
#  define COMPILER_STANDARD 17
#elif CPPVER_MATCH(14)
#  define COMPILER_STANDARD 14
#elif CPPVER_MATCH(11)
#  define COMPILER_STANDARD 11
#else
#  define COMPILER_STANDARD 97
#endif

REGION_CLOSE("config.macro.cpp")


/// Defines macros for things specific to individual compilers
REGION_BEGIN("config.macro.compiler")
// ---------------------------------------------------------------------------------------------------------------- //

#if defined(__clang__)
#  define COMPILER_LLVM "LLVM"
#  if defined(__ELLCC__)
#    define COMPILER_ELLCC ELLCC
#    define COMPILER_CURR VCOMPILER_ELLCC
#    define COMPILER_TYPE COMPILER_ELLCC
#  elif defined(__INTEL_LLVM_COMPILER)
#    define COMPILER_ICX ICX
#    define COMPILER_CLANG CLANG
#    define COMPILER_CURR VCOMPILER_ICX
#    define COMPILER_TYPE COMPILER_ICX
#  else
#    define COMPILER_CLANG CLANG
#    define COMPILER_CURR VCOMPILER_CLANG
#    define COMPILER_TYPE COMPILER_CLANG
#  endif
#elif defined(__INTEL_COMPILER)
#  define COMPILER_GNU "GNU"
#  define COMPILER_ICC ICC
#  define COMPILER_CURR VCOMPILER_ICC
#  define COMPILER_TYPE COMPILER_ICC
#elif defined(__GNUC__)
#  define COMPILER_GNU "GNU"
#  if defined(__MINGW32__)
#    define COMPILER_MINGW MINGW
#    define COMPILER_GCC GCC
#    define COMPILER_CURR VCOMPILER_MINGW
#    define COMPILER_TYPE COMPILER_MINGW
#  elif defined(__NVCOMPILER)
#    define COMPILER_NVCPP NVCPP
#    define COMPILER_CURR VCOMPILER_NVCPP
#    define COMPILER_TYPE COMPILER_NVCPP
#  else
#    define COMPILER_GCC GCC
#    define COMPILER_CURR VCOMPILER_GCC
#    define COMPILER_TYPE COMPILER_GCC
#  endif
#elif defined(_MSC_VER) || defined(_MSVC_LANG)
#  define COMPILER_MSVC MSVC
#  define COMPILER_CURR VCOMPILER_MSVC
#  define COMPILER_TYPE COMPILER_MSVC
#else
#  define COMPILER_UNKNOWN UNKNOWN
#  define COMPILER_CURR VCOMPILER_UNKNOWN
#  define COMPILER_TYPE COMPILER_UNKNOWN
#  if COMPILER_STRICT_CONFORMANCE
#    error Your compiler is currently unsupported!
#  endif
#endif

#define COMPILER_NAME STRINGIFY(COMPILER_TYPE)

/**
 * This defines the keyword versions of some logical operators for C++17
 * and below on MSVC, since they forgot to do that for some reason
 */

#if CPPVER_MOST(17) && defined(COMPILER_MSVC)
#  define not !
#  define and &&
#  define or ||
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
#  define COMPILER_FUNCTION __PRETTY_FUNCTION__
#elif defined(COMPILER_MSVC)
#  define COMPILER_FUNCTION __FUNCSIG__
#else
#  define COMPILER_FUNCTION __func__
#  undef  COMPILER_FUNCTION_CLASSIC
#  define COMPILER_FUNCTION_CLASSIC 1
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
#  define UNREACHABLE_I __builtin_unreachable()
#  define FORCE_INLINE inline __attribute__((always_inline))
#elif defined(COMPILER_MSVC)
#  define UNREACHABLE_I __assume(0)
#  define FORCE_INLINE __forceinline
#else
#  define UNREACHABLE_I void(0)
#  define FORCE_INLINE inline
#endif

#define UNREACHABLE(...) UNREACHABLE_I

#if defined(COMPILER_MINGW)
#  define CLRCALL __clrcall
#  define STDCALL __stdcall
#  define VECCALL
#elif defined(COMPILER_MSVC)
#  define CLRCALL __clrcall
#  define STDCALL __stdcall
#  define VECCALL __vectorcall
#else
#  define CDECL
#  define CLRCALL
#  define VECCALL
#  define FASTCALL
#endif

#if defined(COMPILER_LLVM) || defined(COMPILER_MSVC)
#  define RESTRICT __restrict
#elif defined(COMPILER_GNU)
#  define RESTRICT __restrict__
#else
#  define RESTRICT
#endif

#ifdef COMPILER_MSVC
#  define COMPILER_UUID(value) __declspec(COMPILER_UUID_I(value))
#  define COMPILER_UUID_I(value) uuid(STRINGIFY(value))
#else
#  define COMPILER_UUID(...)
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
#  define COMPILER_FUNCTION __PRETTY_FUNCTION__
#elif defined(COMPILER_MSVC)
#  define COMPILER_FUNCTION __FUNCSIG__
#else
#  define COMPILER_FUNCTION __func__
#  undef  COMPILER_FUNCTION_CLASSIC
#  define COMPILER_FUNCTION_CLASSIC 1
#endif

/**
 * Defines wrappers around compiler specific diagnostics.
 * Makes things easier to read and less finicky in general
 */

#define GENERIC_DIAGNOSTIC(nm, sv, msg)     \
   COMPILER_PRAGMA(nm diagnostic push)      \
   COMPILER_PRAGMA(nm diagnostic sv msg)
#define GENERIC_POP(nm, type)               \
   COMPILER_PRAGMA(nm type pop)

/**
 * Check out https://developer.arm.com/documentation/101754/0620/armclang-Reference/Compiler-specific-Pragmas
 * for more info on LLVM pragmas
 */
#ifdef COMPILER_LLVM
#  define LLVM_DIAGNOSTIC(sv, msg)          \
     GENERIC_DIAGNOSTIC(clang, sv, msg)
#  define LLVM_IGNORED(msg)                 \
     LLVM_DIAGNOSTIC(ignored, msg)
#  define LLVM_WARNING(msg)                 \
     LLVM_DIAGNOSTIC(warning, msg)
#  define LLVM_ERROR(msg)                   \
     LLVM_DIAGNOSTIC(error, msg)
#  define LLVM_POP(type)                    \
     GENERIC_POP(clang, type)
#else
#  define LLVM_DIAGNOSTIC(...)
#  define LLVM_IGNORED(...)
#  define LLVM_WARNING(...)
#  define LLVM_ERROR(...)
#  define LLVM_POP(...)
#endif

/**
 * Check out https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html for
 * more info on GNU pragmas
 */
#ifdef COMPILER_GNU
#  define GNU_DIAGNOSTIC(sv, msg)           \
     GENERIC_DIAGNOSTIC(GCC, sv, msg)
#  define GNU_IGNORED(msg)                  \
     GNU_DIAGNOSTIC(ignored, msg)
#  define GNU_WARNING(msg)                  \
     GNU_DIAGNOSTIC(warning, msg)
#  define GNU_ERROR(msg)                    \
     GNU_DIAGNOSTIC(error, msg)
#  define GNU_POP(type)                     \
     GENERIC_POP(GCC, type)
#else
#  define GNU_DIAGNOSTIC(...)
#  define GNU_IGNORED(...)
#  define GNU_WARNING(...)
#  define GNU_ERROR(...)
#  define GNU_POP(...)
#endif

/**
 * Defining these for consistency's sake, they aren't anything special
 */

#define COMPILER_FILE __FILE__
#define COMPILER_LINE __LINE__

#if COMPILER_DEBUG
#  define DEBUG_ONLY(...) __VA_ARGS__
#else
#  define DEBUG_ONLY(...)
#endif

LLVM_IGNORED("-Wkeyword-macro")
#ifdef __cplusplus
/// Remove the deprecated `register` keyword
#  define register
#endif
LLVM_POP(diagnostic)

REGION_CLOSE("config.macro.compiler")


/**
 * Checks the `COMPILER_BOOST_EXTEND` macro defined previously.
 * If it evaluates to true, BoostPP will be included,
 * and extension macros will be defined
 */
REGION_BEGIN("config.macro.extend")
// ---------------------------------------------------------------------------------------------------------------- //

/// TODO: Complete implementation
#if COMPILER_BOOST_EXTEND
#  include <boost/preprocessor/logical.hpp>
#  define PP_BOOL(x) BOOST_PP_BOOL(x)
#  define PP_NOT(x) BOOST_PP_NOT(x)
#  define PP_AND(x, y) BOOST_PP_AND(x, y)
#else
#  define PP_BOOL(x)        ~
#  define PP_NOT(x)         ~
#  define PP_AND(x, y)      ~
#endif

REGION_CLOSE("config.macro.extend")



/// Provides enums for use in switching behaviour
REGION_BEGIN("config.type.enum")
// ---------------------------------------------------------------------------------------------------------------- //


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
        CPP23 = 23,
        CPP20 = 20,
        CPP17 = 17,
        CPP14 = 14,
        CPP11 = 11,
        CPP97 = 97,
    };
    
    struct Compiler {
        static constexpr auto type = CompilerType::COMPILER_TYPE;
        static constexpr auto supertype = CompilerSuperType(COMPILER_CURR & VCOMPILER_SUPERTYPE_MASK);
        static constexpr auto standard = StandardType::CAT(CPP, COMPILER_STANDARD);
        static constexpr decltype(COMPILER_NAME) name = COMPILER_NAME;
    };
}

REGION_CLOSE("config.type.enum")

#endif // EIGHTFOLD_CONFIG_SINGLE_HPP
