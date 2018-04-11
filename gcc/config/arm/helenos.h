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

#undef  HELENOS_ARCH_OS_CPP_BUILTINS
#define HELENOS_ARCH_OS_CPP_BUILTINS() TARGET_BPABI_CPP_BUILTINS()

#undef  FPUTYPE_DEFAULT
#define FPUTYPE_DEFAULT "vfp"

#undef  TARGET_DEFAULT_FLOAT_ABI
#define TARGET_DEFAULT_FLOAT_ABI ARM_FLOAT_ABI_SOFT

/* We default to the "aapcs-linux" ABI so that enums are int-sized by
   default.  */
#undef  ARM_DEFAULT_ABI
#define ARM_DEFAULT_ABI ARM_ABI_AAPCS_LINUX

#define TARGET_ENDIAN_OPTION     "mlittle-endian"
#define TARGET_LINKER_EMULATION  "armelf_helenos"

#undef  SUBTARGET_EXTRA_LINK_SPEC
#define SUBTARGET_EXTRA_LINK_SPEC " -m " TARGET_LINKER_EMULATION

#undef LINK_SPEC
#define LINK_SPEC EABI_LINK_SPEC "%{h*} \
   %{static:-Bstatic} \
   %{shared:-shared} \
   %{symbolic:-Bsymbolic} \
   %{!static: \
     %{rdynamic:-export-dynamic} \
     %{!shared:-no-dynamic-linker}} \
   -X \
   -EL" \
   SUBTARGET_EXTRA_LINK_SPEC

#undef MULTILIB_DEFAULTS

#undef LIBGCC_SPEC

// TODO: We currently use APCS frame, but eventually we want to switch to
// a dwarf-based unwinder.
#undef  TARGET_DEFAULT
#define TARGET_DEFAULT (MASK_APCS_FRAME | MASK_INTERWORK | TARGET_ENDIAN_DEFAULT)

/* Call the function profiler with a given profile label.  */
#undef  ARM_FUNCTION_PROFILER
#define ARM_FUNCTION_PROFILER(STREAM, LABELNO)  			\
{									\
  fprintf (STREAM, "\tbl\tmcount%s\n",					\
	   (TARGET_ARM && NEED_PLT_RELOC) ? "(PLT)" : "");		\
}

/* Uninitialized common symbols in non-PIE executables, even with
   strong definitions in dependent shared libraries, will resolve
   to COPY relocated symbol in the executable.  See PR65780.  */
#undef TARGET_BINDS_LOCAL_P
#define TARGET_BINDS_LOCAL_P default_binds_local_p_2

/* Define this to be nonzero if static stack checking is supported.  */
#define STACK_CHECK_STATIC_BUILTIN 1

#undef  SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC ""

#undef ARM_TARGET2_DWARF_FORMAT
#define ARM_TARGET2_DWARF_FORMAT (DW_EH_PE_pcrel | DW_EH_PE_indirect)

/* Additional HelenOS flags.
 * Fix r9 for use by runtime libraries.
 * Set soft model for thread-local storage.
 */
#define HELENOS_DRIVER_ARCH_SPECS \
    MCPU_MTUNE_NATIVE_SPECS TARGET_MODE_SPECS "-ffixed-r9 -mtp=soft"

