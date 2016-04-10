#ifndef _MMU_H_
#define _MMU_H_
#include "type.h"
/* Eflags register */
#define FL_CF            0x00000001    // Carry Flag
#define FL_PF            0x00000004    // Parity Flag
#define FL_AF            0x00000010    // Auxiliary carry Flag
#define FL_ZF            0x00000040    // Zero Flag
#define FL_SF            0x00000080    // Sign Flag
#define FL_TF            0x00000100    // Trap Flag
#define FL_IF            0x00000200    // Interrupt Flag
#define FL_DF            0x00000400    // Direction Flag
#define FL_OF            0x00000800    // Overflow Flag
#define FL_IOPL_MASK    0x00003000    // I/O Privilege Level bitmask
#define FL_IOPL_0        0x00000000    //   IOPL == 0
#define FL_IOPL_1        0x00001000    //   IOPL == 1
#define FL_IOPL_2        0x00002000    //   IOPL == 2
#define FL_IOPL_3        0x00003000    //   IOPL == 3
#define FL_NT            0x00004000    // Nested Task
#define FL_RF            0x00010000    // Resume Flag
#define FL_VM            0x00020000    // Virtual 8086 mode
#define FL_AC            0x00040000    // Alignment Check
#define FL_VIF            0x00080000    // Virtual Interrupt Flag
#define FL_VIP            0x00100000    // Virtual Interrupt Pending
#define FL_ID            0x00200000    // ID flag

/* Application segment type bits */
#define STA_X            0x8            // Executable segment
#define STA_E            0x4            // Expand down (non-executable segments)
#define STA_C            0x4            // Conforming code segment (executable only)
#define STA_W            0x2            // Writeable (non-executable segments)
#define STA_R            0x2            // Readable (executable segments)
#define STA_A            0x1            // Accessed

/* System segment type bits */
#define STS_T16A        0x1            // Available 16-bit TSS
#define STS_LDT            0x2            // Local Descriptor Table
#define STS_T16B        0x3            // Busy 16-bit TSS
#define STS_CG16        0x4            // 16-bit Call Gate
#define STS_TG            0x5            // Task Gate / Coum Transmitions
#define STS_IG16        0x6            // 16-bit Interrupt Gate
#define STS_TG16        0x7            // 16-bit Trap Gate
#define STS_T32A        0x9            // Available 32-bit TSS
#define STS_T32B        0xB            // Busy 32-bit TSS
#define STS_CG32        0xC            // 32-bit Call Gate
#define STS_IG32        0xE            // 32-bit Interrupt Gate
#define STS_TG32        0xF            // 32-bit Trap Gate

/* task state segment format (as described by the Pentium architecture book) */
struct taskstate {
    uint32_t ts_link;        // old ts selector
    uintptr_t ts_esp0;        // stack pointers and segment selectors
    uint16_t ts_ss0;        // after an increase in privilege level
    uint16_t ts_padding1;
    uintptr_t ts_esp1;
    uint16_t ts_ss1;
    uint16_t ts_padding2;
    uintptr_t ts_esp2;
    uint16_t ts_ss2;
    uint16_t ts_padding3;
    uintptr_t ts_cr3;        // page directory base
    uintptr_t ts_eip;        // saved state from last task switch
    uint32_t ts_eflags;
    uint32_t ts_eax;        // more saved state (registers)
    uint32_t ts_ecx;
    uint32_t ts_edx;
    uint32_t ts_ebx;
    uintptr_t ts_esp;
    uintptr_t ts_ebp;
    uint32_t ts_esi;
    uint32_t ts_edi;
    uint16_t ts_es;            // even more saved state (segment selectors)
    uint16_t ts_padding4;
    uint16_t ts_cs;
    uint16_t ts_padding5;
    uint16_t ts_ss;
    uint16_t ts_padding6;
    uint16_t ts_ds;
    uint16_t ts_padding7;
    uint16_t ts_fs;
    uint16_t ts_padding8;
    uint16_t ts_gs;
    uint16_t ts_padding9;
    uint16_t ts_ldt;
    uint16_t ts_padding10;
    uint16_t ts_t;            // trap on task switch
    uint16_t ts_iomb;        // i/o map base address
};

#endif


