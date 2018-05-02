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

#define GNU_USER_LINK_EMULATION32 "elf32%{EB:b}%{EL:l}tsmip"
#define GNU_USER_LINK_EMULATION64 "elf64%{EB:b}%{EL:l}tsmip"
#define GNU_USER_LINK_EMULATIONN32 "elf32%{EB:b}%{EL:l}tsmipn32"

#undef  SUBTARGET_CC1_SPEC
#define SUBTARGET_CC1_SPEC ""

#undef  CC1PLUS_SPEC
#define CC1PLUS_SPEC ""

/* Define this to be nonzero if static stack checking is supported.  */
#define STACK_CHECK_STATIC_BUILTIN 1

/* The default value isn't sufficient in 64-bit mode.  */
#define STACK_CHECK_PROTECT (TARGET_64BIT ? 16 * 1024 : 12 * 1024)

#undef ASM_DECLARE_OBJECT_NAME
#define ASM_DECLARE_OBJECT_NAME mips_declare_object_name

/* If we don't set MASK_ABICALLS, we can't default to PIC.  */
#undef TARGET_DEFAULT
#define TARGET_DEFAULT MASK_ABICALLS

/* -G is incompatible with -KPIC which is the default, so only allow objects
   in the small data section if the user explicitly asks for it.  */
#undef MIPS_DEFAULT_GVALUE
#define MIPS_DEFAULT_GVALUE 0

#undef LINK_SPEC
#define LINK_SPEC "\
  %{G*} %{EB} %{EL} %{mips*} %{shared} \
  %{!shared: \
    %{!static: \
      %{rdynamic:-export-dynamic} \
      -no-dynamic-linker} \
    %{static}} \
  %{mabi=n32:-m" GNU_USER_LINK_EMULATIONN32 "} \
  %{mabi=64:-m" GNU_USER_LINK_EMULATION64 "} \
  %{mabi=32:-m" GNU_USER_LINK_EMULATION32 "}"

#undef SUBTARGET_ASM_SPEC
#define SUBTARGET_ASM_SPEC \
  "%{!mno-abicalls:%{mplt:-call_nonpic;:-KPIC}}"

/* The MIPS assembler has different syntax for .set. We set it to
   .dummy to trap any errors.  */
#undef SET_ASM_OP
#define SET_ASM_OP "\t.dummy\t"

#undef ASM_OUTPUT_DEF
#define ASM_OUTPUT_DEF(FILE,LABEL1,LABEL2)				\
 do {									\
	fputc ( '\t', FILE);						\
	assemble_name (FILE, LABEL1);					\
	fputs ( " = ", FILE);						\
	assemble_name (FILE, LABEL2);					\
	fputc ( '\n', FILE);						\
 } while (0)

/* The glibc _mcount stub will save $v0 for us.  Don't mess with saving
   it, since ASM_OUTPUT_REG_PUSH/ASM_OUTPUT_REG_POP do not work in the
   presence of $gp-relative calls.  */
#undef ASM_OUTPUT_REG_PUSH
#undef ASM_OUTPUT_REG_POP

#ifdef HAVE_AS_NO_SHARED
/* Default to -mno-shared for non-PIC.  */
# define NO_SHARED_SPECS \
  " %{mshared|mno-shared:;:%{" NO_FPIE_AND_FPIC_SPEC ":-mno-shared}}"
#else
# define NO_SHARED_SPECS ""
#endif

/* -march=native handling only makes sense with compiler running on
   a MIPS chip.  */
#if defined(__mips__)
extern const char *host_detect_local_cpu (int argc, const char **argv);
# define EXTRA_SPEC_FUNCTIONS \
  { "local_cpu_detect", host_detect_local_cpu },

# define MARCH_MTUNE_NATIVE_SPECS				\
  " %{march=native:%<march=native %:local_cpu_detect(arch)}"	\
  " %{mtune=native:%<mtune=native %:local_cpu_detect(tune)}"
#else
# define MARCH_MTUNE_NATIVE_SPECS ""
#endif

#define LINUX_DRIVER_SELF_SPECS \
  NO_SHARED_SPECS							\
  MARCH_MTUNE_NATIVE_SPECS,						\
  /* -mplt has no effect without -mno-shared.  Simplify later		\
     specs handling by removing a redundant option.  */			\
  "%{!mno-shared:%<mplt}",						\
  /* -mplt likewise has no effect for -mabi=64 without -msym32.  */	\
  "%{mabi=64:%{!msym32:%<mplt}}",					\
  "%{!EB:%{!EL:%(endian_spec)}}",					\
  "%{!mabi=*: -" MULTILIB_ABI_DEFAULT "}"

/* Additional HelenOS flags. */
#define HELENOS_DRIVER_ARCH_SPECS  \
  MIPS_ISA_LEVEL_SPEC, \
  BASE_DRIVER_SELF_SPECS, \
  LINUX_DRIVER_SELF_SPECS, \
  "-msoft-float", "-mabi=32"

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX (TARGET_OLDABI ? "$" : ".")
