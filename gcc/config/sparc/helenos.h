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

/* On Linux, the combination sparc64-* --with-cpu=v8 is supported and
   selects a 32-bit compiler.  */
#if defined(TARGET_64BIT_DEFAULT) && TARGET_CPU_DEFAULT >= TARGET_CPU_v9
#undef TARGET_DEFAULT
#define TARGET_DEFAULT \
  (MASK_V9 + MASK_PTR64 + MASK_64BIT + MASK_STACK_BIAS + \
   MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)
#endif

/* This must be v9a not just v9 because by default we enable
   -mvis.  */
#undef ASM_CPU64_DEFAULT_SPEC
#define ASM_CPU64_DEFAULT_SPEC "-Av9a"

/* The default code model.  */
#undef SPARC_DEFAULT_CMODEL
#define SPARC_DEFAULT_CMODEL CM_MEDLOW

/* Define for support of TFmode long double.
   SPARC ABI says that long double is 4 words.  */
#undef LONG_DOUBLE_TYPE_SIZE
#define LONG_DOUBLE_TYPE_SIZE (TARGET_LONG_DOUBLE_128 ? 128 : 64)

#undef LINK_SPEC
#define LINK_SPEC "-m elf64_sparc -Y P,%R/lib %{shared:-shared} \
  %{!shared: \
    %{!static: \
      %{rdynamic:-export-dynamic} \
      -dynamic-linker " HELENOS_DYNAMIC_LINKER64 "} \
    %{static:-static}} \
%{!mno-relax:%{!r:-relax}} \
"

/* It's safe to pass -s always, even if -g is not used.  */
#undef ASM_SPEC
#define ASM_SPEC "\
-s \
%{" FPIE_OR_FPIC_SPEC ":-K PIC} \
%{!.c:%{findirect-dispatch:-K PIC}} \
%(asm_cpu) %(asm_arch) %(asm_relax)"

#undef ASM_OUTPUT_ALIGNED_LOCAL
#define ASM_OUTPUT_ALIGNED_LOCAL(FILE, NAME, SIZE, ALIGN)		\
do {									\
  fputs ("\t.local\t", (FILE));		\
  assemble_name ((FILE), (NAME));					\
  putc ('\n', (FILE));							\
  ASM_OUTPUT_ALIGNED_COMMON (FILE, NAME, SIZE, ALIGN);			\
} while (0)

#undef COMMON_ASM_OP
#define COMMON_ASM_OP "\t.common\t"

#undef  LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX  "."

/* DWARF bits.  */

/* Follow Irix 6 and not the Dwarf2 draft in using 64-bit offsets.
   Obviously the Dwarf2 folks haven't tried to actually build systems
   with their spec.  On a 64-bit system, only 64-bit relocs become
   RELATIVE relocations.  */

/* #define DWARF_OFFSET_SIZE PTR_SIZE */

#undef DITF_CONVERSION_LIBFUNCS
#define DITF_CONVERSION_LIBFUNCS 1

#ifdef HAVE_AS_TLS
#undef TARGET_SUN_TLS
#undef TARGET_GNU_TLS
#define TARGET_SUN_TLS 0
#define TARGET_GNU_TLS 1
#endif

/* We use GNU ld so undefine this so that attribute((init_priority)) works.  */
#undef CTORS_SECTION_ASM_OP
#undef DTORS_SECTION_ASM_OP

/* Static stack checking is supported by means of probes.  */
#define STACK_CHECK_STATIC_BUILTIN 1

/* Define if long doubles should be mangled as 'g'.  */
#define TARGET_ALTERNATE_LONG_DOUBLE_MANGLING

/* We use glibc _mcount for profiling.  */
#undef NO_PROFILE_COUNTERS
#define NO_PROFILE_COUNTERS	1
