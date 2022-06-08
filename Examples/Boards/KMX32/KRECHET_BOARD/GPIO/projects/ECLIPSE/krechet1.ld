/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-kmx32","elf32-kmx32","elf32-kmx32")
OUTPUT_ARCH(kmx32)
ENTRY(_entry)
MEMORY
{
  rom		: ORIGIN = 0x80001000,  LENGTH = 64K
  rom_data	: ORIGIN = 0x80001000,  LENGTH = 64K
  ram		: ORIGIN = 0,	        LENGTH = 32K
  ram_flash	: ORIGIN = 0x40000000,	LENGTH = 0
}
SECTIONS
{
	PROVIDE (__start_of_rom = 0x80001000) ;
  /* Read-only sections, merged into text segment: */
  .hash          : { *(.hash)		}
  .dynsym        : { *(.dynsym)		}
  .dynstr        : { *(.dynstr)		}
  .gnu.version   : { *(.gnu.version)	}
  .gnu.version_d   : { *(.gnu.version_d)	}
  .gnu.version_r   : { *(.gnu.version_r)	}
  .rel.init      : { *(.rel.init)	}
  .rela.init     : { *(.rela.init) }
  .rel.text      :
    {
      *(.rel.text)
      *(.rel.text.*)
      *(.rel.gnu.linkonce.t*)
    }
  .rela.text     :
    {
      *(.rela.text)
      *(.rela.text.*)
      *(.rela.gnu.linkonce.t*)
    }
  .rel.fini      : { *(.rel.fini)	}
  .rela.fini     : { *(.rela.fini) }
  .rel.rodata    :
    {
      *(.rel.rodata)
      *(.rel.rodata.*)
      *(.rel.gnu.linkonce.r*)
    }
  .rela.rodata   :
    {
      *(.rela.rodata)
      *(.rela.rodata.*)
      *(.rela.gnu.linkonce.r*)
    }
  .rel.data      :
    {
      *(.rel.data)
      *(.rel.data.*)
      *(.rel.gnu.linkonce.d*)
    }
  .rela.data     :
    {
      *(.rela.data)
      *(.rela.data.*)
      *(.rela.gnu.linkonce.d*)
    }
  .rel.ctors     : { *(.rel.ctors)	}
  .rela.ctors    : { *(.rela.ctors)	}
  .rel.dtors     : { *(.rel.dtors)	}
  .rela.dtors    : { *(.rela.dtors)	}
  .rel.got       : { *(.rel.got)		}
  .rela.got      : { *(.rela.got)		}
  .rel.bss       : { *(.rel.bss)		}
  .rela.bss      : { *(.rela.bss)		}
  .rel.plt       : { *(.rel.plt)		}
  .rela.plt      : { *(.rela.plt)		}
  /* Internal text space */
  .text :
  {
    *(.init)
    *(.text)
    *(.text.*)
    *(.fini)
     _etext = . ;
    . = ALIGN(4);
     __ctors_start = . ;
     KEEP (*(SORT(.ctors.*)))
     KEEP (*(.ctors))
     __ctors_end = . ;
     __dtors_start = . ;
     KEEP (*(SORT(.dtors.*)))
     KEEP (*(.dtors))
     __dtors_end = . ;
    . = ALIGN(4);
  }  > rom
  __flbr = .;
/*  .rodata    :  AT(__flbr)*/
/*  .rodata    : AT(ADDR(.text) + SIZEOF(.text))*/
/*  .rodata   MAX(SIZEOF(.text), 0x5000) + 0x100000 : AT(ADDR(.text) + MAX(SIZEOF(.text), 0x5000))*/
  .rodata   SIZEOF(.text) + __start_of_rom : AT(ADDR(.text) + SIZEOF(.text))
  {
     PROVIDE (_srodata = .) ;
    *(.gnu.linkonce.d*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata.*)
    . = ALIGN(4);
    *(.gnu.linkonce.r*)
    . = ALIGN(4);
/*    KEEP (*(.eh_frame)) */
    *(.gcc_except_table)
    . = ALIGN(4);
     _erodata = . ;
    . = ALIGN(4);
  }  > rom_data
  /* Start of the data section image in ROM.  */
  __data_image = .;
  .flash : AT(ADDR(.text) + 64K)
  {
    *(.flash)
    . = ALIGN(4);
    *(.flash.*)
  } > ram_flash
  /* All read-only sections that normally go in PROM must be above.
     We construct the DATA image section in PROM at end of all these
     read-only sections.  The data image must be copied at init time.
     Refer to GNU ld, Section 3.6.8.2 Output Section LMA.  */
  .data    : AT (LOADADDR(.rodata) + SIZEOF(.rodata))
  {
     PROVIDE (_sdata = .) ;
    *(.data)
    . = ALIGN(4);
    *(.data.*)
    . = ALIGN(4);
     _edata = . ;
    . = ALIGN(4);
  }  > ram
  . = ALIGN(4);
  .bss  SIZEOF(.data) + ADDR(.data) :
  {
     PROVIDE (_sbss = .) ;
    *(.bss)
    . = ALIGN(4);
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
     PROVIDE (_ebss = .) ;
  }  > ram
  . = ALIGN(4);
  end = .;
  PROVIDE (end = .);
  /* Stabs debugging sections.  */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) *(.gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
/* ALIGN(exp) equals (. + exp - 1) & ~(exp - 1) */
  __end_of_rom = __data_image + SIZEOF(.data) ;
  __imbs_temp = (__end_of_rom >> 14) ;
  __imbs7 = (__imbs_temp >> 6) & 1 ;
  __imbs6 = (__imbs_temp >> 5) & 1 ;
  __imbs5 = (__imbs_temp >> 4) & 1 ;
  __imbs4 = (__imbs_temp >> 3) & 1 ;
  __imbs3 = (__imbs_temp >> 2) & 1 ;
  __imbs2 = (__imbs_temp >> 1) & 1 ;
  __imbs1 = __imbs_temp & 1 ;
  __auto_imbs = __imbs7*7 + !__imbs7*(__imbs6*6 + !__imbs6*(__imbs5*5 + !__imbs5*(__imbs4*4 + !__imbs4*(__imbs3*3 + !__imbs3*(__imbs2*2 + !__imbs2*__imbs1)))));
  PROVIDE (__user_rom = (__end_of_rom + (1 << (6 + __auto_imbs)) - 1) & ~((1 << (6 + __auto_imbs)) - 1)) ;
  __auto_umbr = ABSOLUTE(__user_rom >> (6 + __auto_imbs)) ;
  __auto_cmbr = ABSOLUTE((__auto_umbr << 4) + __auto_imbs) ;
/*  __auto_flbr = (__flbr >> 8) ;*/
/*  __auto_flbr = (64K - 0x5000) & ~0x1ff ;*/
  __auto_flbr = (LENGTH(rom) - 0x5000) & 0xfffffe00 ;
  __end_of_ram = ADDR(.bss) + SIZEOF(.bss) ;
  PROVIDE (__user_ram = (__end_of_ram + (1 << 6) - 1) & ~((1 << 6) - 1)) ;
  __auto_dmbr = (__user_ram >> 6) ;
  PROVIDE (__stack = 32K) ;
/* Now constants __ctors/__dtors already contain __start_of_rom.
	__ctors_start += __start_of_rom ;
	__ctors_end += __start_of_rom ;
	__dtors_start += __start_of_rom ;
	__dtors_end += __start_of_rom ;
*/
}
