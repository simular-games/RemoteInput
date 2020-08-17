/* Copyright (c) 2020 Simular Games, LLC.
 * -------------------------------------------------------------------------------------------------
 *
 * MIT License
 * -------------------------------------------------------------------------------------------------
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * -------------------------------------------------------------------------------------------------
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * \file
 * \brief   This file describes the macros and compile time variables for which platform, processor,
 *          compiler, and even which language we are currently compiling for.
 * \details This file is in-part attributed to Electronic Arts and their EASTL, more specifically
 *          their EABase module, as it's a rather robust detection macro set. There are changes here
 *          and there, omissions, additions, but there is practically no difference except naming.
 *          It was easier to do it this way rather than having to try and figure out all the
 *          combinations of things ourselves.
 */
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//                                    Platform Detection                                         //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Check if CygWin is available.
#if defined(__CYGWIN__)
#  define SIMULAR_CYGWIN_PLATFORM 1
#  define SIMULAR_DESKTOP 1
#endif

// Check if MinGW is available.
#if defined(__MINGW32__) || defined(__MINGW64__)
#  define SIMULAR_MINGW_PLATFORM 1
#  define SIMULAR_DESKTOP 1
#endif

// Check operating system and processor.
#if defined(SIMULAR_ANDROID_PLATFORM) || defined(__ANDROID__)
#  undef SIMULAR_ANDROID_PLATFORM
#  define SIMULAR_ANDROID_PLATFORM 1
#  define SIMULAR_LINUX_PLATFORM 1
#  define SIMULAR_UNIX_PLATFORM 1
#  define SIMULAR_POSIX_PLATFORM 1
#  define SIMULAR_PLATFORM_NAME "Android"
#  define SIMULAR_MOBILE 1
#  if defined(__arm__)
#    define SIMULAR_ARM32_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Android on ARM"
#  elif defined(__aarch64__)
#    define SIMULAR_ARM64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Android on ARM64"
#  elif defined(__i386__)
#    define SIMULAR_X86_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Android on x86"
#  elif defined(__x86_64__)
#    define SIMULAR_X64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Android on x64"
#  else
#    error "Unknown Processor"
#  endif
#  if !defined(SIMULAR_BIG_ENDIAN) && !defined(SIMULAR_LITTLE_ENDIAN)
#    define SIMULAR_LITTLE_ENDIAN 1
#  endif
#elif defined(__APPLE__) && __APPLE__
#  include <TargetConditionals.h>
#  define SIMULAR_APPLE_PLATFORM 1
#  define SIMULAR_POSIX_PLATFORM 1
#  if defined(SIMULAR_IPHONE_PLATFORM) || defined(__IPHONE__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE) || (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR)
#    undef SIMULAR_IPHONE_PLATFORM
#    define SIMULAR_IPHONE_PLATFORM 1
#    define SIMULAR_PLATFORM_NAME "iPhone"
#    define SIMULAR_POSIX_THREADS_AVAILABLE 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_MOBILE 1
#    if defined(__arm__)
#      define SIMULAR_ARM32_PROCESSOR 1
#      define SIMULAR_PLATFORM_DESC "iPhone on ARM"
#    elif defined(__aarch64__) || defined(__AARCH64)
#      define SIMULAR_ARM64_PROCESSOR 1
#      define SIMULAR_PLATFORM_DESC "iPhone on ARM64"
#    elif defined(__i386__)
#      define SIMULAR_IPHONE_SIMULATOR_PLATFORM 1
#      define SIMULAR_X86_PROCESSOR 1
#      define SIMULAR_PLATFORM_DESC "iPhone simulator on x86"
#    elif defined(__x86_64__) || defined(__amd64)
#      define SIMULAR_IPHONE_SIMULATOR_PLATFORM 1
#      define SIMULAR_X64_PROCESSOR 1
#      define SIMULAR_PLATFORM_DESC "iPhone simulator on x64"
#    else
#      error "Unknown Processor"
#    endif
#  elif defined(SIMULAR_OSX_PLATFORM) || defined(__MACH__) || (defined(__MSL__) && (__dest_os == __mac_os_x))
#    undef SIMULAR_OSX_PLATFORM
#    define SIMULAR_OSX_PLATFORM 1
#    define SIMULAR_UNIX_PLATFORM 1
#    define SIMULAR_PLATFORM_NAME "OSX"
#    define SIMULAR_DESKTOP 1
#    if defined(__i386__) || defined(__intel__)
#      define SIMULAR_X86_PROCESSOR 1
#      define SIMULAR_LITTLE_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on x86"
#    elif defined(__x86_64__) || defined(__amd64)
#      define SIMULAR_X64_PROCESSOR 1
#      define SIMULAR_LITTLE_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on x64"
#    elif defined(__arm__)
#      define SIMULAR_ARM32_PROCESSOR 1
#      define SIMULAR_LITTLE_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on ARM"
#    elif defined(__aarch64__) || defined(__AARCH64)
#      define SIMULAR_ARM64_PROCESSOR 1
#      define SIMULAR_LITTLE_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on ARM64"
#    elif defined(__POWERPC64__) || defined(__powerpc64__)
#      define SIMULAR_POWERPC64_PROCESSOR 1
#      define SIMULAR_BIG_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on PowerPC 64"
#    elif defined(__POWERPC__) || defined(__powerpc__)
#      define SIMULAR_POWERPC32_PROCESSOR 1
#      define SIMULAR_BIG_ENDIAN 1
#      define SIMULAR_PLATFORM_DESC "OSX on PowerPC"
#    else
#      error "Unknown Processor"
#    endif
#  else
#    error "Unknown Apple platform"
#  endif
#elif defined(SIMULAR_LINUX_PLATFORM) || (defined(__linux) || defined(__linux__))
#  undef SIMULAR_LINUX_PLATFORM
#  define SIMULAR_LINUX_PLATFORM 1
#  define SIMULAR_UNIX_PLATFORM 1
#  define SIMULAR_POSIX_PLATFORM 1
#  define SIMULAR_PLATFORM_NAME "Linux"
#  define SIMULAR_DESKTOP 1
#  if defined(__i386__) || defined(__intel__) || defined(_M_IX86)
#    define SIMULAR_X86_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "Linux on x86"
#  elif defined(__ARM_ARCH_7A__) || defined(__ARM_EABI__)
#    define SIMULAR_ARM32_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "Linux on ARM 6/7 32-bits"
#  elif defined(__aarch64__) || defined(__AARCH64)
#    define SIMULAR_ARM64_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "Linux on ARM64"
#  elif defined(__x86_64__)
#    define SIMULAR_X64_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFOMR_DESC "Linux on x64"
#  elif defined(__powerpc64__)
#    define SIMULAR_POWERPC64_PROCESSOR 1
#    define SIMULAR_BIG_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "Linux on PowerPC 64"
#  elif defined(__powerpc__)
#    define SIMULAR_POWERPC32_PROCESSOR 1
#    define SIMULAR_BIG_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "Linux on PowerPC"
#  else
#    error "Unknown Processor"
#  endif
#elif defined(SIMULAR_BSD_PLATFORM) || (defined(__BSD__) || defined(__FreeBSD__))
#  undef SIMULAR_BSD_PLATFORM
#  define SIMULAR_BSD_PLATFORM 1
#  define SIMULAR_UNIX_PLATFORM 1
#  define SIMULAR_POSIX_PLATFORM 1
#  define SIMULAR_PLATFORM_NAME "BSD Unix"
#  if defined(__i386__) || defined(__intel__)
#    define SIMULAR_X86_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "BSD on x86"
#  elif defined(__x86_64__)
#    define SIMULAR_X64_PROCESSOR 1
#    define SIMULAR_LITTLE_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "BSD on x64"
#  elif defined(__powerpc64__)
#    define SIMULAR_POWERPC64_PROCESSOR 1
#    define SIMULAR_BIG_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "BSD on PowerPC 64"
#  elif defined(__powerpc__)
#    define SIMULAR_POWERPC32_PROCESSOR 1
#    define SIMULAR_BIG_ENDIAN 1
#    define SIMULAR_PLATFORM_DESC "BSD on PowerPC"
#  else
#    error "Unknown Processor"
#  endif
#  if !defined(SIMULAR_FREEBSD_PLATFORM) && defined(__FreeBSD__)
#    define SIMULAR_FREEBSD_PLATFORM 1
#  endif
#elif defined(SIMULAR_WINDOWS_PHONE_PLATFORM)
#  undef SIMULAR_WINDOWS_PHONE_PLATFORM
#  define SIMULAR_WINDOWS_PHONE_PLATFORM 1
#  define SIMULAR_MICROSOFT_PLATFORM 1
#  define SIMULAR_PLATFORM_NAME "Windows Phone"
#  define SIMULAR_LITTLE_ENDIAN 1
#  define SIMULAR_MOBILE 1
#  if defined(_M_AMD64) || defined(_AMD64_) || defined(__x86_64__)
#    define SIMULAR_X64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows Phone on x64"
#  elif defined(_M_IX86) || defined(_X86_)
#    define SIMULAR_X86_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows Phone on x86"
#  elif defined(_M_ARM)
#    define SIMULAR_ARM32_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows Phone on ARM"
#  else
#    error "Unknown Processor"
#  endif
#  define SIMULAR_WINAPI_FAMILY_APP 1
#  define SIMULAR_WINAPI_FAMILY_DESKTOP_APP 2
#  define SIMULAR_WINAPI_FAMILY_PHONE_APP 3
#  if defined(WINAPI_FAMILY)
#    include <winapifamily.h>
#    if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#      define SIMULAR_WINAPI_FAMILY
#    else
#      error "Unsupported WINAPI_FAMILY for Windows Phone"
#    endif
#  else
#    error "WINAPI_FAMILY should always be defined on Windows Phone"
#  endif
#  define SIMULAR_WINAPI_FAMILY_PARTITION(partition) (partition)
#  if SIMULAR_WINAPI_FAMILY == SIMULAR_WINAPI_FAMILY_PHONE_APP
#    define SIMULAR_WINAPI_PARTITION_CORE 1
#    define SIMULAR_WINAPI_PARTITION_PHONE 1
#    define SIMULAR_WINAPI_PARTITION_APP 1
#  else
#    error "Unsupported WINAPI_FAMILY for Windows Phone"
#  endif
#elif (defined(SIMULAR_WINDOWS_PLATFORM) || (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64))) && !defined(CS_UNDEFINED_STRING)
#  undef SIMULAR_WINDOWS_PLATFORM
#  define SIMULAR_MICROSOFT_PLATFORM 1
#  define SIMULAR_WINDOWS_PLATFORM 1
#  define SIMULAR_PLATFORM_NAME "Windows"
#  define SIMULAR_LITTLE_ENDIAN 1
#  define SIMULAR_DESKTOP 1
#  if defined(_WIN64)
#    define SIMULAR_WIN64_PLATFORM 1
#  else
#    define SIMULAR_WIN32_PLATFORM 1
#  endif
#  if defined(_M_AMD64) || defined(_AMD64_) || defined(__x86_64__)
#    define SIMULAR_X64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows on x64"
#  elif defined(_M_IX86) || defined(_X86_)
#    define SIMULAR_X86_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows on x86"
#  elif defined(_M_IA64) || defined(_IA64_)
#    define SIMULAR_IA64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows on IA-64"
#  elif defined(_M_ARM)
#    define SIMULAR_ARM32_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows on ARM"
#  elif defined(_M_ARM64)
#    define SIMULAR_ARM64_PROCESSOR 1
#    define SIMULAR_PLATFORM_DESC "Windows on ARM64"
#  else
#    error "Unknown Processor"
#  endif
#  define SIMULAR_WINAPI_FAMILY_APP 1000
#  define SIMULAR_WINAPI_FAMILY_DESKTOP_APP 1001
#  define SIMULAR_WINAPI_FAMILY_GAMES 1002
#  if defined(WINAPI_FAMILY)
#    if defined(_MSC_VER)
#      pragma warning(push, 0)
#    endif
#    include <winapifamily.h>
#    if defined(_MSC_VER)
#      pragma warning(pop)
#    endif
#    if defined(WINAPI_FAMILY_DESKTOP_APP) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
#      define SIMULAR_WINAPI_FAMILY SIMULAR_WINAPI_FAMILY_DESKTOP_APP
#    elif defined(WINAPI_FAMILY_APP) && WINAPI_FAMILY == WINAPI_FAMILY_APP
#      define SIMULAR_WINAPI_FAMILY SIMULAR_WINAPI_FAMILY_APP
#    elif defined(WINAPI_FAMILY_GAMES) && WINAPI_FAMILY == WINAPI_FAMILY_GAMES
#      define SIMULAR_WINAPI_FAMILY SIMULAR_WINAPI_FAMILY_GAMES
#    else
#      error "Unsupported WINAPI_FAMILY"
#    endif
#  endif
#  define SIMULAR_WINAPI_FAMILY_PARTITION(partition) (partition)
#  define SIMULAR_WINAPI_PARTITION_DESKTOP 1
#  define SIMULAR_WINAPI_PARTITION_APP 1
#  define SIMULAR_WINAPI_PARTITION_GAMES (SIMULAR_WINAPI_FAMILY == SIMULAR_WINAPI_FAMILY_GAMES)
#  if defined(__cplusplus_winrt)
#    define SIMULAR_WINRT_PLATFORM 1
#  endif
#else
#  error "Unknown Platform"
#endif

// Make sure this gets defined.
#if !defined(SIMULAR_ARM_PROCESSOR)
#  if defined(SIMULAR_ARM32_PROCESSOR) || defined(SIMULAR_ARM64_PROCESSOR) || defined(SIMULAR_ARM7_PROCESSOR)
#    define SIMULAR_ARM_PROCESSOR 1
#  endif
#endif

// Make sure this gets defined.
#if !defined(SIMULAR_POWERPC_PROCESSOR)
#  if defined(SIMULAR_POWERPC64_PROCESSOR) || defined(SIMULAR_POWERPC32_PROCESSOR)
#    define SIMULAR_POWERPC_PROCESSOR 1
#  endif
#endif

// Check pointer size.
#if !defined(SIMULAR_PROCESSOR_PTR_SIZE)
#  if defined(__WORDSIZE)
#    define SIMULAR_PROCESSOR_PTR_SIZE ((__WORDSIZE) / 8)
#  elif defined(_WIN64) || defined(__LP64__) || defined(_M_IA64) || defined(__ia64__) || defined(__arch64__) || defined(__aarch64__) || defined(__mips64__) || defined(__64BIT__) || defined(__Ptr_Is_64)
#    define SIMULAR_PROCESSOR_PTR_SIZE 8
#  elif defined(__CC_ARM) && (__sizeof_ptr == 8)
#    define SIMULAR_PROCESSOR_PTR_SIZE 8
#  else
#    define SIMULAR_PROCESSOR_PTR_SIZE 4
#  endif
#endif

// Check word size.
#if !defined(SIMULAR_PROCESSOR_WORD_SIZE)
#  define SIMULAR_PROCESSOR_WORD_SIZE SIMULAR_PROCESSOR_PTR_SIZE
#endif

// Check min allocation alignment.
#if !defined(SIMULAR_PROCESSOR_MIN_MALLOC_ALIGNMENT)
#  if defined(SIMULAR_APPLE_PLATFORM)
#    define SIMULAR_PROCESSOR_MIN_MALLOC_ALIGNMENT 16
#  elif defined(SIMULAR_ANDROID_ALIGNMENT) && defined(SIMULAR_ARM_PROCESSOR)
#    define SIMULAR_PROCESSOR_MIN_MALLOC_ALIGNMENT 8
#  elif defined(SIMULAR_ANDROID_ALIGNMENT) && defined(SIMULAR_X86_PROCESSOR)
#    define SIMULAR_PROCESSOR_MIN_MALLOC_ALIGNMENT 8
#  else
#    define SIMULAR_PROCESSOR_MIN_MALLOC_ALIGNMENT (SIMULAR_PROCESSOR_PTR_SIZE * 2)
#  endif
#endif

// Can the processor read and write built-in types that aren't naturally aligned?
#if !defined(SIMULAR_PROCESSOR_MISALIGNED_SUPPORT_LEVEL)
#  if defined(SIMULAR_X64_PROCESSOR)
#    define SIMULAR_PROCESSOR_MISALIGNED_SUPPORT_LEVEL 2
#  else
#    define SIMULAR_PROCESSOR_MISALIGNED_SUPPORT_LEVEL 0
#  endif
#endif

// Disable Windows API partition if not defined or on another platform.
#if !defined(SIMULAR_WINAPI_FAMILY_PARTITION)
#  define SIMULAR_WINAPI_FAMILY_PARTITION(partition) (0)
#endif

// Best guess at cache line sizes at compile time.
#if !defined(SIMULAR_PROCESSOR_CACHE_LINE_SIZE)
#  if defined(SIMULAR_X86_PROCESSOR)
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 32
#  elif defined(SIMULAR_X64_PROCESSOR)
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 64
#  elif defined(SIMULAR_ARM32_PROCESSOR)
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 32
#  elif defined(SIMULAR_ARM64_PROCESSOR)
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 64
#  elif (SIMULAR_PROCESSOR_WORD_SIZE == 4)
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 32
#  else
#    define SIMULAR_PROCESSOR_CACHE_LINE_SIZE 64
#  endif
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//                                    Compiler Detection                                         //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Check for this.
#if !defined(INTERNAL_STRINGIZE)
#  define INTERNAL_STRINGIZE(x) INTERNAL_PRIMITIVE_STRINGIZE(x)
#endif

// Check for this too.
#if !defined(INTERNAL_PRIMITIVE_STRINGIZE)
#  define INTERNAL_PRIMITIVE_STRINGIZE(x) #x
#endif

// Used to check for feature on Clang.
#if !defined(SIMULAR_COMPILER_HAS_FEATURE)
#  if defined(__clang__)
#    define SIMULAR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#  else
#    define SIMULAR_COMPILER_HAS_FEATURE(x) 0
#  endif
#endif

// Used to check for builtin on Clang.
#if !defined(SIMULAR_COMPILER_HAS_BUILTIN)
#  if defined(__clang__)
#    define SIMULAR_COMPILER_HAS_BUILTIN(x) __has_builtin(x)
#  else
#    define SIMULAR_COMPILER_HAS_BUILTIN(x) 0
#  endif
#endif

// EDG compiler front-end, used by other compilers such as SN.
#if defined(__EDG_VERSION__)
#  define SIMULAR_EDG_COMPILER 1
#  if defined(_MSC_VER)
#    define SIMULAR_EDG_VC_MODE 1
#  endif
#  if defined(__GNUC__)
#    define SIMULAR_EDG_GCC_MODE 1
#  endif
#endif

// Check for WinRTCX.
#if !defined(SIMULAR_WINRTCX_ENABLED) && defined(__cpluplus_winrt)
#  define SIMULAR_WINRTCX_ENABLED 1
#endif

// Check for C++11 support.
#if !defined(SIMULAR_CPP11_ENABLED) && defined(__cplusplus)
#  if (__cplusplus >= 201103L)
#    define SIMULAR_CPP11_ENABLED 1
#  elif defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define SIMULAR_CPP11_ENABLED 1
#  elif defined(_MSV_VER) && (_MSC_VER >= 1600)
#    define SIMULAR_CPP11_ENABLED 1
#  endif
#endif

// Check for C++14 support.
#if !defined(SIMULAR_CPP14_ENABLED) && defined(__cplusplus)
#  if (__cplusplus >= 201402L)
#    define SIMULAR_CPP14_ENABLED 1
#  elif defined(_MSC_VER) && (_MSC_VER >= 1900)
#    define SIMULAR_CPP14_ENABLED 1
#  endif
#endif

// Check for C++17 support.
#if !defined(SIMULAR_CPP17_ENABLED) && defined(__cplusplus)
#  if (__cplusplus >= 201703L)
#    define SIMULAR_CPP17_ENABLED 1
#  elif defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L)
#    define SIMULAR_CPP17_ENABLED 1
#  endif
#endif

// Check for C++20 support.
#if !defined(SIMULAR_CPP20_ENABLED) && defined(__cplusplus)
// #  if (__cplusplus >= 202003L)
// #    define SIMULAR_CPP20_ENABLED 1
// #  elif defined(_MSVC_LANG) && (_MSVC_LANG >= 202003L)
// #    define SIMULAR_CPP20_ENABLED 1
// #  endif
#endif

// Don't allow a compiler that doesn't support C++14 or earlier.
#if !defined(SIMULAR_CPP17_ENABLED)
#  error "We request that you kindly at least use a compile which supports, and has enabled, C++17."
#endif

// Detect different compilers.
#if defined(__ARMCC_VERSION)
#  define SIMULAR_RVCT_COMPILER 1
#  define SIMULAR_ARM_COMPILER 1
#  define SIMULAR_COMPILER_VERSION __ARMCC_VERSION
#  define SIMULAR_COMPILER_NAME "RVCT"
#elif defined(__clang__) && !defined(_MSC_VER)
#  define SIMULAR_CLANG_COMPILER 1
#  define SIMULAR_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
#  define SIMULAR_COMPILER_NAME "Clang"
#  define SIMULAR_COMPILER_DESC "Clang " __clang_version__
#elif defined(__GNUC__)
#  define SIMULAR_GNUC_COMPILER 1
#  define SIMULAR_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#  define SIMULAR_COMPILER_NAME "GCC"
#  define SIMULAR_COMPILER_DESC "GCC compiler, version " INTERNAL_STRINIZE(__GNUC__) "." INTERNAL_STRINGIZE(__GNUC_MINOR__)
#  if (__GNUC__ == 2) && (__GNUC_MINOR__ < 95)
#    define SIMULAR_NO_MEMBER_TEMPLATES 1
#  endif
#  if (__GNUC__ == 2) && (__GNUC_MINOR__ < 97)
#    define SIMULAR_NO_MEMBER_TEMPLATE_FRIENDS 1
#  endif
#  if (__GNUC__ == 3) && ((__GNUC_MINOR == 1) || (__GNUC_MINOR__ == 2))
#    define SIMULAR_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS 1
#  endif
#elif defined(__BORLANDC__)
#  define SIMULAR_BORLANDC_COMPILER 1
#  define SIMULAR_COMPILER_VERSION __BORLANDC__
#  define SIMULAR_COMPILER_NAME "Borland C"
#  if (__BORLANDC__ <= 0x0550)
#    define SIMULAR_NO_MEMBER_TEMPLATE_FRIENDS 1
#  endif
#  if (__BORLANDC__ <= 0x0561) && (__BORLANDC__ < 0x0600)
#    define SIMULAR_NO_MEMBER_FUNCTION_SPECIALIZATION 1
#  endif
#elif defined(__ICL) || defined(__ICC)
#  define SIMULAR_INTEL_COMPILER 1
#  if defined(_MSC_VER)
#    define SIMULAR_MSVC_COMPILER 1
#    define SIMULAR_MICROSOFT_COMPILER 1
#  elif defined(__GNUC__)
#    define SIMULAR_GNUC_COMPILER 1
#  endif
#  if defined(__ICL)
#    define SIMULAR_COMPILER_VERSION __ICL
#  elif defined(__ICC)
#    define SIMULAR_COMPILER_VERSION __ICC
#  endif
#  define SIMULAR_COMPILER_NAME "Intel C++"
#  if defined(_MSC_VER)
#    define SIMULAR_COMPILER_DESC "Intel C++ compiler, version " INTERNAL_STRINGIZE(SIMULAR_COMPILER_VERSION) ", EDG version " INTERNAL_STRINGIZE(__EDG_VERSION__) ", VC++ version " INTERNAL_STRINGIZE(_MSC_VER)
#  elif defined(__GNUC__)
#    define SIMULAR_COMPILER_DESC "Intel C++ compiler, version " INTERNAL_STRINGIZE(SIMULAR_COMPILER_VERSION) ", EDG version " INTERNAL_STRINGIZE(__EDG_VERSION__) ", GCC version " INTERNAL_STRINGIZE(__GNUC__)
#  else
#    define SIMULAR_COMPILER_DESC "Intel C++ compiler, version " INTERNAL_STRINGIZE(SIMULAR_COMPILER_VERSION) ", EDG version " INTERNAL_STRINGIZE(__EDG_VERSION__)
#  endif
#elif defined(_MSC_VER)
#  define SIMULAR_MSVC_COMPILER 1
#  define SIMULAR_MICROSOFT_COMPILER 1
#  define SIMULAR_COMPILER_VERSION _MSC_VER
#  define SIMULAR_COMPILER_NAME "Microsoft Visual C++"
#  if defined(__clang__)
#    define SIMULAR_CLANG_CL_COMPILER 1
#  endif
#  define SIMULAR_MSVC_STANDARD_LIB 1
#  define SIMULAR_MICROSOFT_STANDARD_LIB 1
#  if (_MSC_VER <= 1200)
#    if (_MSC_VER < 1200)
#      define SIMULAR_MSVCOLD_COMPILER 1
#    else
#      define SIMULAR_MSVC6_COMPILER 1
#    endif
#    if (_MSC_VER < 1200)
#      define SIMULAR_NO_TEMPLATE_SPECIALIZATION 1
#    endif
#    define SIMULAR_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS 1
#    define SIMULAR_NO_VOID_RETURNS 1
#    define SIMULAR_NO_EXCEPTION_STD_NAMESPACE 1
#    define SIMULAR_NO_DEDUCED_TYPENAME 1
#    define SIMULAR_NO_STATIC_CONSTANTS 1
#    define SIMULAR_NO_COVARIANT_RETURN_TYPE 1
#    define SIMULAR_NO_ARGUMENT_DEPENDENT_LOOKUP 1
#    define SIMULAR_NO_TEMPLATE_TEMPLATES 1
#    define SIMULAR_NO_TEMPLATE_PARTIAL_SPECIALIZATION 1
#    define SIMULAR_NO_MEMBER_TEMPLATE_FRIENDS 1
#  elif (_MSC_VER <= 1300)
#    define SIMULAR_MSVC7_COMPILER 1
#    define SIMULAR_NO_COVARIANT_RETURN_TYPE 1
#    define SIMULAR_NO_ARGUMENT_DEPENDENT_LOOKUP 1
#    define SIMULAR_NO_TEMPLATE_TEMPLATES 1
#    define SIMULAR_NO_TEMPLATE_PARTIAL_SPECIALIZATION 1
#    define SIMULAR_NO_MEMBER_TEMPLATE_FRIENDS 1
#    define SIMULAR_NO_MEMBER_FUNCTION_SPECIALIZATION 1
#  elif (_MSC_VER <= 1400)
#    define SIMULAR_MSVC7_2003_COMPILER 1
#    define SIMULAR_MSVC7_COMPILER 1
#  elif (_MSC_VER <= 1500)
#    define SIMULAR_MSVC8_2005_COMPILER 1
#    define SIMULAR_MSVC8_COMPILER 1
#  elif (_MSC_VER <= 1600)
#    define SIMULAR_MSVC9_2008_COMPILER 1
#    define SIMULAR_MSVC9_COMPILER 1
#  elif (_MSC_VER <= 1700)
#    define SIMULAR_MSVC10_2010_COMPILER 1
#    define SIMULAR_MSVC10_COMPILER 1
#  elif (_MSC_VER <= 1800)
#    define SIMULAR_MSVC11_2011_COMPILER 1
#    define SIMULAR_MSVC12_2012_COMPILER 1
#    define SIMULAR_MSVC11_COMPILER 1
#    define SIMULAR_MSVC12_COMPILER 1
#  elif (_MSC_VER <= 1900)
#    define SIMULAR_MSVC13_2013_COMPILER 1
#    define SIMULAR_MSVC13_COMPILER 1
#  elif (_MSC_VER <= 1910)
#    define SIMULAR_MSVC14_2015_COMPILER 1
#    define SIMULAR_MSVC14_COMPILER 1
#  elif (_MSC_VER <= 1911)
#    define SIMULAR_MSVC15_2017_COMPILER 1
#    define SIMULAR_MSVC15_COMPILER 1
#  endif
#elif defined(__xlC__)
#  define SIMULAR_IBM_COMPILER 1
#  define SIMULAR_COMPILER_VERSION __xlC__
#  define SIMULAR_COMPILER_NAME "IBM XL C"
#else
#  define SIMULAR_COMPILER_VERSION 0
#  define SIMULAR_COMPILER_NAME "Unknown"
#endif

// Define compiler description if not already.
#if !defined(SIMULAR_COMPILER_DESC)
#  define SIMULAR_COMPILER_DESC SIMULAR_COMPILER_NAME " compiler, version " INTERNAL_STRINGIZE(SIMULAR_COMPILER_VERSION)
#endif

// Described as deprecated definitions for backwards compatibility by EABase.
// Since we're practically copying the implemenation, we should include these.
#if !defined(SIMULAR_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#  define SIMULAR_PARTIAL_TEMPLATE_SPECIALIZATION 1
#endif
#if !defined(SIMULAR_NO_TEMPLATE_SPECIALIZATION)
#  define SIMULAR_TEMPLATE_SPECIALIZATION 1
#endif
#if !defined(SIMULAR_NO_MEMBER_TEMPLATES)
#  define SIMULAR_MEMBER_TEMPLATES 1
#endif
#if !defined(SIMULAR_NO_MEMBER_TEMPLATE_SPECIALIZATION)
#  define SIMULAR_MEMBER_TEMPLATE_SPECIALIZATION 1
#endif

// Check if RTTI is enabled.
#if defined(__EDG_VERSION__) && !defined(__RTTI)
#  define SIMULAR_NO_RTTI 1
#elif defined(__clang__) && !defined(cxx_rtti)
#  define SIMULAR_NO_RTTI 1
#elif defined(__IBMCPP__) && !defined(__RTTI_ALL__)
#  define SIMULAR_NO_RTTI 1
#elif defined(__GXX_ABI_VERSION__) && !defined(__GXX_RTTI)
#  define SIMULAR_NO_RTTI 1
#elif defined(_MSC_VER) && !defined(_CPPRTTI)
#  define SIMULAR_NO_RTTI 1
#elif defined(__ARMCC_VERSION) && defined(__TARGET_CPU_MPCORE) && !defined(__RTTI)
#  define SIMULAR_NO_RTTI 1
#endif

// Check if exceptions/unwind is enabled.
#if !defined(SIMULAR_NO_EXCEPTIONS) && !defined(SIMULAR_NO_UNWIND)
#  if defined(SIMULAR_GNUC_COMPILER) && defined(_NO_EX)
#    define SIMULAR_NO_EXCEPTIONS 1
#  elif (defined(SIMULAR_CLANG_COMPILER) || defined(SIMULAR_GNUC_COMPILER) || defined(SIMULAR_INTEL_COMPILER) || defined(SIMULAR_RVCT_COMPILER)) && !defined(__EXCEPTIONS)
#    define SIMULAR_NO_EXCEPTIONS 1
#  elif defined(SIMULAR_MSVC_COMPILER) && !defined(_CPPUNWIND)
#    define SIMULAR_NO_UNWIND 1
#  endif
#endif

// Check for Dinkumware standard lib.
#if !defined(SIMULAR_HAS_DINKUMWARE_CPP_LIB) && !defined(SIMULAR_NO_DINKUMWARE_CPP_LIB)
#  if defined(__cplusplus)
#    include <cstddef>
#  endif
#  if defined(__cplusplus) && defined(_CPPLIB_VER)
#    define SIMULAR_HAS_DINKUMWARE_CPP_LIB 1
#  else
#    define SIMULAR_NO_DINKUMWARE_CPP_LIB 1
#  endif
#endif

// Check if aligned new is enabled.
#if !defined(SIMULAR_NO_ALIGNED_NEW)
#  if !(defined(_HAS_ALIGNED_NEW) && _HAS_ALIGNED_NEW) && !defined(SIMULAR_CPP17_ENABLED)
#    define SIMULAR_NO_ALIGNED_NEW 1
#  endif
#endif

// Android doesn't support standard lib.
#if defined(SIMULAR_PLATFORM_ANDROID)
#  define SIMULAR_NO_STANDARD_CPP_LIB 1
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//                                      Compiler Traits                                          //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// C++?
#if defined(__cplusplus)
#  define SIMULAR_COMPILER_IS_CPP 1
#else
#  error "__cplusplus not defined, please make sure you compiler is a C++ compliant compiler or you have enabled necessary options."
#endif

// Is this managed?
#if defined(SIMULAR_MSVC_COMPILER) && (SIMULAR_COMPILER_VERSION >= 1300) && defined(_MANAGED)
#  define SIMULAR_COMPILER_MANAGED_CPP 1
#endif

// INTMAX_SIZE? Treated in bytes.
#if defined(SIMULAR_GNUC_COMPILER) && defined(SIMULAR_X64_PROCESSOR)
#  define SIMULAR_INTMAX_SIZE 16
#else
#  define SIMULAR_INTMAX_SIZE 8
#endif

// Likely/Unlikely
#if !defined(SIMULAR_LIKELY)
#  if defined(SIMULAR_GNUC_COMPILER) || defined(SIMULAR_CLANG_COMPILER)
#    if defined(SIMULAR_COMPILER_IS_CPP)
#      define SIMULAR_LIKELY(x)   __builtin_expects(!!(x), true)
#      define SIMULAR_UNLIKELY(x) __builtin_expects(!!(x), false)
#    else
#      define SIMULAR_LIKELY(x)   __builtin_expects(!!(x), 1)
#      define SIMULAR_UNLIKELY(x) __builtin_expects(!!(x), 0)
#    endif
#  else
#    define SIMULAR_LIKELY(x)   (x)
#    define SIMULAR_UNLIKELY(x) (x)
#  endif
#endif

// Deprecated
#if !defined(SIMULAR_DEPRECATED)
#  define SIMULAR_DEPRECATED [[deprecated]]
#endif
#if !defined(SIMULAR_DEPRECATED_MESSAGE)
#  define SIMULAR_DEPRECATED_MESSAGE(msg) [[deprecated(#msg)]]
#endif

// Import and export
#if !defined(SIMULAR_IMPORT) && defined(SIMULAR_MSVC_COMPILER)
#  define SIMULAR_IMPORT __declspec(dllimport)
#else
#  define SIMULAR_IMPORT
#endif
#if !defined(SIMULAR_EXPORT) && defined(SIMULAR_MSVC_COMPILER)
#  define SIMULAR_EXPORT __declspec(dllexport)
#else
#  define SIMULAR_EXPORT __attribute__((visibility("default")))
#endif

// Big bad, no do.
#if defined(SIMULAR_BUILD_SHARED) && defined(SIMULAR_USE_SHARED)
#  error "Both of SIMULAR_BUILD_SHARED and SIMULAR_USE_SHARED defined, please make up your mind."
#endif

// Shared build?
#if defined(SIMULAR_WINDOWS_PLATFORM) && defined(SIMULAR_MSVC_COMPILER)
#  if defined(SIMULAR_BUILD_SHARED)
#    define SIMULARAPI __declspec(dllexport)
#  else
#    define SIMULARAPI __declspec(dllimport)
#  endif
#  if !defined(SIMULARCALL)
#    define SIMULARCALL __stdcall
#  endif
#else
#  if defined(SIMULAR_BUILD_SHARED)
#    define SIMULARAPI __attribute__((visibility("default")))
#  else
#    define SIMULARAPI
#  endif
#  if !defined(SIMULARCALL)
#    define SIMULARCALL __cdecl
#  endif
#endif

// Make sure these don't exist anymore.
#undef INTERNAL_STRINGIZE
#undef INTERNAL_PRIVATE_STRINGIZE
