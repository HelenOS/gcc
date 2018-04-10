/* Definitions for HelenOS.
   Copyright (C) 1996-2017 Free Software Foundation, Inc.
   Copyright (C) 2017 CZ.NIC, z.s.p.o.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* We reuse definitions from gnu-user.h, with minor modifications.
 *
 * Anything that can be defined using a regular specfile is done there,
 * because they are easier to debug and modify.
 * Only do things here that cannot be done in a specfile, or must be available
 * for libgcc build.
 */


/* XXX: We defer these to the textual specfiles. */
#undef  STARTFILE_SPEC
#define STARTFILE_SPEC ""
#undef  ENDFILE_SPEC
#define ENDFILE_SPEC ""
#undef  LIB_SPEC
#define LIB_SPEC ""

#undef LINK_EH_SPEC
#define LINK_EH_SPEC "%{!static:--eh-frame-hdr} "

#undef CPLUSPLUS_CPP_SPEC
#define CPLUSPLUS_CPP_SPEC "%(cpp)"

#ifndef HELENOS_ARCH_CPP_SPEC
#define HELENOS_ARCH_CPP_SPEC
#endif

#undef CPP_SPEC
#define CPP_SPEC "-D_REENTRANT"

/* SUBTARGET_FRAME_POINTER_REQUIRED somehow doesn't work on i386.
 * Am I doing this right?
 */
#define HELENOS_DRIVER_COMMON_SPECS "-fno-omit-frame-pointer"

#ifndef HELENOS_DRIVER_ARCH_SPECS
#define HELENOS_DRIVER_ARCH_SPECS ""
#endif

#undef  DRIVER_SELF_SPECS
#define DRIVER_SELF_SPECS  HELENOS_DRIVER_COMMON_SPECS, HELENOS_DRIVER_ARCH_SPECS

/* Don't assume anything about the header files.  */
#define NO_IMPLICIT_EXTERN_C

/* Use --as-needed -lgcc_s for eh support.  */
#ifdef HAVE_LD_AS_NEEDED
#define USE_LD_AS_NEEDED 1
#endif

/* HelenOS doesn't support executable stack,
 * and doesn't understand PT_GNU_STACK header.
 */
#undef NEED_INDICATE_EXEC_STACK
#define NEED_INDICATE_EXEC_STACK 0

/* Pretend we have everything glibc has. */
#undef TARGET_LIBC_HAS_FUNCTION
#define TARGET_LIBC_HAS_FUNCTION gnu_libc_has_function

/* FIXME: Not sure what this does or why we want this. */
#undef TARGET_POSIX_IO

#define HELENOS_DYNAMIC_LINKER "/lib/ld.so.0"
#define HELENOS_DYNAMIC_LINKER32 "/lib/ld.so.0"
#define HELENOS_DYNAMIC_LINKER64 "/lib/ld64.so.0"
#define HELENOS_DYNAMIC_LINKERX32 "/lib/ldx32.so.0"

#define HELENOS_CPP_BUILTINS()						\
    do {								\
	builtin_define ("__helenos__");					\
	builtin_assert ("system=helenos");				\
    } while (0)

#ifndef HELENOS_ARCH_OS_CPP_BUILTINS
#define HELENOS_ARCH_OS_CPP_BUILTINS()
#endif

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()				\
  do								\
    {								\
	HELENOS_CPP_BUILTINS();					\
	HELENOS_ARCH_OS_CPP_BUILTINS();				\
    }								\
  while (0)

/* Some architectures need frame pointer, so I'm trying to be lazy here. */
#undef  SUBTARGET_FRAME_POINTER_REQUIRED
#define SUBTARGET_FRAME_POINTER_REQUIRED 1

/* Not supported (yet?).  */
#undef TARGET_THREAD_SSP_OFFSET
#undef TARGET_CAN_SPLIT_STACK
#undef TARGET_THREAD_SPLIT_STACK_OFFSET
#undef STACK_CHECK_MOVING_SP
#undef STACK_CHECK_STATIC_BUILTIN

#ifdef __cplusplus__
extern "C" {
#endif
extern void __helenos_clear_icache(void *begin, void *end);
#ifdef __cplusplus__
}
#endif

/* Emit on all architectures and let libc sort it out. */
#define CLEAR_INSN_CACHE(begin, end) __helenos_clear_icache(begin, end)

/* There is little reason for basic types to be inconsistent across architectures. */

#undef DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR 1

#undef WCHAR_TYPE
#define WCHAR_TYPE "int"
#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32
#undef  WINT_TYPE
#define WINT_TYPE "int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE INTPTR_TYPE
#undef SIZE_TYPE
#define SIZE_TYPE UINTPTR_TYPE

