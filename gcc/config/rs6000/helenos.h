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

/* XXX: Most of this file is "borrowed" from elsewhere, as are the comments. */

#undef ASM_APP_ON
#define ASM_APP_ON "#APP\n"

#undef ASM_APP_OFF
#define ASM_APP_OFF "#NO_APP\n"

/* FIXME: Does HelenOS support saving and restoring 64-bit regs in a 32-bit
   process?  */
#define OS_MISSING_POWERPC64 1

#define NO_PROFILE_COUNTERS 1

#undef HELENOS_ARCH_CPP_SPEC
#define HELENOS_ARCH_CPP_SPEC()			\
  do						\
    {						\
      builtin_define_std ("PPC");		\
      builtin_define_std ("powerpc");		\
      builtin_assert ("cpu=powerpc");		\
      builtin_assert ("machine=powerpc");	\
    }						\
  while (0)

#undef  DEFAULT_ASM_ENDIAN
#if (TARGET_DEFAULT & MASK_LITTLE_ENDIAN)
#define DEFAULT_ASM_ENDIAN " -mlittle"
#else
#define DEFAULT_ASM_ENDIAN " -mbig"
#endif

#undef LINK_SPEC
#define LINK_SPEC " -m elf32ppc %{!shared: %{!static: \
  %{rdynamic:-export-dynamic} \
  -no-dynamic-linker }}"

/* For backward compatibility.  */
#undef  DRAFT_V4_STRUCT_RET
#define DRAFT_V4_STRUCT_RET 1

/* We are 32-bit all the time, so optimize a little.  */
#undef TARGET_64BIT
#define TARGET_64BIT 0

/* We don't need to generate entries in .fixup, except when
   -mrelocatable or -mrelocatable-lib is given.  */
#undef RELOCATABLE_NEEDS_FIXUP
#define RELOCATABLE_NEEDS_FIXUP \
  (rs6000_isa_flags & rs6000_isa_flags_explicit & OPTION_MASK_RELOCATABLE)

#undef TARGET_THREAD_SSP_OFFSET

/* ppc linux has 128-bit long double support in glibc 2.4 and later.  */
#ifdef TARGET_DEFAULT_LONG_DOUBLE_128
#define RS6000_DEFAULT_LONG_DOUBLE_SIZE 128
#endif

/* Additional HelenOS flags. */
#define HELENOS_DRIVER_ARCH_SPECS  "%{mfpu=none: %<mfpu=* \
 	%<msingle-float %<mdouble-float}", "-mcpu=powerpc", "-msoft-float"

/* Static stack checking is supported by means of probes.  */
#define STACK_CHECK_STATIC_BUILTIN 1

/* Dummies to keep sysv4.h happy. */
#define FBSD_DYNAMIC_LINKER ""
#define FBSD_STARTFILE_SPEC ""
#define FBSD_ENDFILE_SPEC ""
#define FBSD_LIB_SPEC ""
