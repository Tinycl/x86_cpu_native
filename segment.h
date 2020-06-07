#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#ifndef UINT64
#define UINT64 unsigned long long
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef UINT8
#define UINT8 unsigned char
#endif

#pragma pack(8)
typedef struct _UINT128
{
    unsigned long long lo;
    unsigned long long hi;
} UINT128;
#pragma pack()

// see figure 2-1 x86 system level registers and data structures
// see figure 3-2 x64 mode execution environment




/* see figure 3-1 segmentation and paging
* segment selector -> segment descriptor (gdt) -> linear address -> paging -> physical address
*
*/



/* see figure 5-10 call gate mechanism
* call gate descriptor in the gdt, ldt
* far pointer(segment selector) -> gdt/ldt -> call gate descriptor -> code segment descriptor
*
*/

/* see figure 6-1 relationship of the IDTR and IDT
*
*/

/* see figure 6-3 interrupt procedure call
*  interrupt vector -> IDT(interrupt or trap gate descriptor, offset) -> GDT/LDT(segment descriptor, base) -> linear address 
*/

/* see figure 6-6 interrupt task switch
* interrupt vector -> IDT(task gate descriptor) -> GDT(TSS descriptor, base) -> TSS base address
*/


/* see figure 7-1 structure of a task
*  see figure 7-5 task register
*  tr.selector -> GDT(TSS descriptor, base, limit) -> tss
*
* task gate descriptor in the GDT, LDT, IDT; only available in x86 mode, not valid in x64 mode。 
* see figure 7-7 task gate referencing the same task
* LDT/IDT/GDT(task gate descriptor) -> GDT(TSS descriptor) -> tss
*
*
*/


//see figure 3-7, segment registers, cs, ss, ds, es, fs, gs, tr, ldtr
typedef struct _SEGMENTR{
    UINT16 visible; // segment selector
    UINT64 hidden;  // base address, limit, access information
}SEGMENTR;

// descriptor table register, gdtr, idtr, ldtr, tr
// lgdt,sdft,lidt,sidt,lldt,sldt,ltr,str
// ldtr tr load/store descriptor,  ldtr descruptor in the gdt, tr descriptor in the gdt
// see figure 3-11, figure 2-6
typedef struct _X86_GDTR{
    UINT16 limit;
    UINT32 baseaddr;
}x86_GDTR;
typedef struct _X64_GDTR{
    UINT16 limit;
    UINT64 baseaddr;
}X64_GDTR;
typedef struct _X86_IDTR{
    UINT16 limit;
    UINT32 baseaddr;
}x86_IDTR;
typedef struct _X64_IDTR{
    UINT16 limit;
    UINT64 baseaddr;
}X64_IDTR;




// see figure 3-6, segment register-> visiable, cs,ds,es,fs,gs,tr,ldtr, (visable selector)
typedef union _SELECTOR {
    UINT16 value;
    struct
    {
        UINT16 rpl : 2; //[1:0], rpl
        UINT16 ti : 1;  //[2], 0 is GDT, 1 is LDT
        UINT16 si : 13; //[15:3],
    } fields;
} SELECTOR, *PSELECTOR;

// see figure 3-8
typedef union _X86_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40], type
        UINT64 s : 1;           //[44], 0 is system segment LDT/TSS/GATE, 1 is user segment CODE/DATA
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52], avaiable to software bit
        UINT64 l : 1;           //[53], 64 bit flag
        UINT64 db : 1;          //[54], default operation size/stack pointer/upper bound flag
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_DESCRIPTOR, *P_X86_DESCRIPTOR;

// see figure 5-1
typedef union _X86_CODE_DESCRIPTOR {
    UINT64 Value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type_a : 1;      //[40], see table 3-1
        UINT64 type_r : 1;      //[41]
        UINT64 type_c : 1;      //[42]
        UINT64 type_3 : 1;      //[43], must be 1
        UINT64 s : 1;           //[44], must be 1
        UINT64 dpl : 2;         //[46:45]
        UINT64 p : 1;           //[47]
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52], avaiable to software bit
        UINT64 l : 1;           //[53], 64 bit flag, must be 0
        UINT64 db : 1;          //[54], default operation size/stack pointer/upper bound flag
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_CODE_DESCRIPTOR, *PX86_CODE_DESCRIPTOR;

//see figure 5-2
typedef union _X64_CODE_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 ign0 : 16;  //[15:0], segment limit[15:0]
        UINT64 ign1 : 16;  //[31:16], base address[15:0]
        UINT64 ign2 : 8;   //[39:32], base address[23:16]
        UINT64 type_a : 1; //[40],type_a, see table 3-1
        UINT64 type_r : 1; //[41], type_r
        UINT64 type_c : 1; //[42]
        UINT64 type_3 : 1; //[43], ,must be 1
        UINT64 s : 1;      //[44],s, must be 1
        UINT64 dpl : 2;    //[46:45]
        UINT64 p : 1;      //[47]
        UINT64 ign3 : 4;   //[51:48], segment limit[19:16]
        UINT64 avl : 1;    //[52], avaiable to software bit
        UINT64 l : 1;      //[53], 64 bit flag, must be 0
        UINT64 db : 1;     //[54], default operation size/stack pointer/upper bound flag
        UINT64 g : 1;      //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 ign4 : 8;   //[63:56], base address[31:24]
    } fields;
} X64_CODE_DESCRIPTOR, *PX64_CODE_DESCRIPTOR;

typedef union _X86_DATA_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type_a : 1;      //[40], see table 3-1
        UINT64 type_w : 1;      //[41]
        UINT64 type_e : 1;      //[42]
        UINT64 type_3 : 1;      //[43], must be 0
        UINT64 s : 1;           //[44], must be 1
        UINT64 dpl : 2;         //[46:45]
        UINT64 p : 1;           //[47]
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52], avaiable to software bit
        UINT64 l : 1;           //[53], 64 bit flag, must be 0
        UINT64 db : 1;          //[54], default operation size/stack pointer/upper bound flag
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_DATA_DESCRIPTOR, *PX86_DATA_DESCRIPTOR;

typedef union _X64_DATA_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 ign0 : 16;  //[15:0], segment limit[15:0]
        UINT64 ign1 : 16;  //[31:16], base address[15:0]
        UINT64 ign2 : 8;   //[39:32], base address[23:16]
        UINT64 type_a : 1; //[40], type_a,see table 3-1
        UINT64 type_w : 1; //[41], type_w,
        UINT64 type_e : 1; //[42], type_e
        UINT64 TYPE_3 : 1; //[43], type_3,must be 0
        UINT64 s : 1;      //[44],S, must be 1
        UINT64 dpl : 2;    //[46:45]
        UINT64 p : 1;      //[47]
        UINT64 ign3 : 4;   //[51:48], segment limit[19:16]
        UINT64 avl : 1;    //[52], avaiable to software bit
        UINT64 l : 1;      //[53], 64 bit flag, must be 1
        UINT64 db : 1;     //[54], default operation size/stack pointer/upper bound flag
        UINT64 g : 1;      //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 ign4 : 8;   //[63:56], base address[31:24]
    } fields;
} X64_DATA_DESCRIPTOR, *PX64_DATA_DESCRIPTOR;

typedef union _X86_SYSTEM_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40], see table 3-2
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 ign0 : 1;        //[52],
        UINT64 l : 1;           //[53], must be 0
        UINT64 ign1 : 1;        //[54]
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_SYSTEM_DESCRIPTOR, *P_X86_SYSTEM_DESCRIPTOR;

typedef union _X64_SYSTEM_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type0 : 4;       //[43:40], see table 3-2
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52],
        UINT64 l : 1;           //[53], must be 0
        UINT64 ign0 : 1;        //[54]
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
        UINT64 base_63_32 : 32; //[95:64], base address[63:32]
        UINT64 rsvd0 : 8;       //[103:96],
        UINT64 type1 : 5;       //[108:104], must be 0
        UINT64 rsvd1 : 19;      //[127:109]
    } fields;
} X64_SYSTEM_DESCRIPTOR, *P_X64_SYSTEM_DESCRIPTOR;

//see figure 5-8
typedef union _X86_CALLGATE_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], offset in segment[15:0]
        UINT64 selector : 16;     //[31:16], segment selector[15:0]
        UINT64 paramcount : 5;    //[36:32], param count[4:0]
        UINT64 rsvd0 : 3;         //[39:37], must be 0
        UINT64 type : 4;          //[43:40], see table 3-2, 1100b
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 16; //[63:48], offset in segment[31:16]
    } fields;
} X86_CALLGATE_DESCRIPTOR, *P_X86_CALLGATE_DESCRIPTOR;
//see figure 5-9
typedef union _X64_CALLGATE_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], segment offset[15:0]
        UINT64 selector : 16;     //[31:16], selector[15:0]
        UINT64 rsvd0 : 8;         //[39:32], must be 0
        UINT64 type0 : 4;         //[43:40], must be 1100b
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 4;  //[63:48], offset[31:16]
        UINT64 offset_63_32 : 32; //[95:64], offset[63:32]
        UINT64 rsvd0 : 8;         //[103:96],
        UINT64 type1 : 5;         //[108:104], must be 0
        UINT64 rsvd1 : 19;        //[127:109]
    } fields;
} X64_CALLGATE_DESCRIPTOR, *P_X64_CALLGATE_DESCRIPTOR;

typedef union _X86_INTERRUPTGATE_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], offset[15:0]
        UINT64 selector : 16;     //[31:16], segment selector[15:0]
        UINT64 ign0 : 5;          //[36:32],
        UINT64 rsvd0 : 3;         //[39:37], must be 0
        UINT64 type : 4;          //[43:40], see table 3-2,  D110b, D is 0 16 bits, 1 is 32 bits
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 16; //[63:48], offset[31:16]
    } fields;
} X86_INTERRUPTGATE_DESCRIPTOR, *P_X86_INTERRUPTGATE_DESCRIPTOR;

// see figure 6-8
typedef union _X64_INTERRUPTGATE_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], segment offset[15:0]
        UINT64 selector : 16;     //[31:16], selector[15:0]
        UINT64 ist : 3;           //[34:32], interrupt stack table
        UINT64 rsvd0 : 5;         //[39:35], must be 0
        UINT64 type : 4;          //[43:40],
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 4;  //[63:48], offset[31:16]
        UINT64 offset_63_32 : 32; //[95:64], offset[63:32]
        UINT64 rsvd1 : 32;        //[127:96],
    } fields;
} X64_INTERRUPTGATE_DESCRIPTOR, *P_X64_INTERRUPTGATE_DESCRIPTOR;

typedef union _X86_TRAPGATE_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], offset[15:0]
        UINT64 selector : 16;     //[31:16], segment selector[15:0]
        UINT64 ign0 : 5;          //[36:32],
        UINT64 rsvd0 : 3;         //[39:37], must be 0
        UINT64 type : 4;          //[43:40], see table 3-2,  D111b, D is 0 16 bits, 1 is 32 bits
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 16; //[63:48], offset[31:16]
    } fields;
} X86_TRAPGATE_DESCRIPTOR, *P_X86_TRAPGATE_DESCRIPTOR;

typedef union _X64_TRAPGATE_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 offset_15_0 : 16;  //[15:0], segment offset[15:0]
        UINT64 selector : 16;     //[31:16], selector[15:0]
        UINT64 ist : 3;           //[34:32], interrupt stack table
        UINT64 rsvd0 : 5;         //[39:35], must be 0
        UINT64 type : 4;          //[43:40],
        UINT64 s : 1;             //[44], must be 0
        UINT64 dpl : 2;           //[46:45], dpl
        UINT64 p : 1;             //[47], present
        UINT64 offset_31_16 : 4;  //[63:48], offset[31:16]
        UINT64 offset_63_32 : 32; //[95:64], offset[63:32]
        UINT64 rsvd1 : 32;        //[127:96],
    } fields;
} X64_TRAPGATE_DESCRIPTOR, *P_X64_TRAPGATE_DESCRIPTOR;

typedef union _X86_LDT_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40], see table 3-2
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 ign0 : 1;        //[52]
        UINT64 l : 1;           //[53], 64 bit flag, must be 0
        UINT64 ign1 : 1;        //[54],
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_LDT_DESCRIPTOR, *P_X86_LDT_DESCRIPTOR;

//see figure 7-4
typedef union _X64_LDT_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40],  10B1b B is busy flag
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52],
        UINT64 ign0 : 1;        //[53],  0
        UINT64 ign1 : 1;        //[54], must be 0
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
        UINT64 base_63_32 : 32; //[95:64], base address[63:32]
        UINT64 rsvd0 : 8;       //[103:96]
        UINT64 type1 : 5;       //[108:104], must be 0
        UINT64 rsvd1 : 19;      //[127:109]
    } fields;
} X64_LDT_DESCRIPTOR, *P_X64_LDT_DESCRIPTOR;

// see figure 7-5,  task register(selector, base address, limit) -> GDT(TSS descriptor)-> TSS
//see figure 7-3
typedef union _X86_TSS_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40],  10B1b B is busy flag
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52],
        UINT64 ign0 : 1;        //[53], must be 0
        UINT64 ign1 : 1;        //[54], must be 0
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
    } fields;
} X86_TSS_DESCRIPTOR, *P_X86_TSS_DESCRIPTOR;

//see figure 7-4
typedef union _X64_TSS_DESCRIPTOR {
    UINT128 value;
    struct
    {
        UINT64 limit_15_0 : 16; //[15:0], segment limit[15:0]
        UINT64 base_15_0 : 16;  //[31:16], base address[15:0]
        UINT64 base_23_16 : 8;  //[39:32], base address[23:16]
        UINT64 type : 4;        //[43:40],  10B1b B is busy flag
        UINT64 s : 1;           //[44], must be 0
        UINT64 dpl : 2;         //[46:45], dpl
        UINT64 p : 1;           //[47], present
        UINT64 limit_19_16 : 4; //[51:48], segment limit[19:16]
        UINT64 avl : 1;         //[52],
        UINT64 ign0 : 1;        //[53],  0
        UINT64 ign1 : 1;        //[54], must be 0
        UINT64 g : 1;           //[55], granularity flag, 0 is byte, 1 is 4KB
        UINT64 base_31_24 : 8;  //[63:56], base address[31:24]
        UINT64 base_63_32 : 32; //[95:64], base address[63:32]
        UINT64 rsvd0 : 8;       //[103:96]
        UINT64 type1 : 5;       //[108:104], must be 0
        UINT64 rsvd1 : 19;      //[127:109]
    } fields;
} X64_TSS_DESCRIPTOR, *P_X64_TSS_DESCRIPTOR;

// see figure 7-2 task state segment
#pragma pack(2)
typedef struct _X86_TSS
{
    UINT16 ptl; // previous task link
    UINT16 rsvd0;

    UINT32 esp0; //offset for ring0

    UINT16 ss0; //segment selector for ring0
    UINT16 rsvd1;

    UINT32 esp1;

    UINT16 ss1;
    UINT16 rsvd2;

    UINT32 esp2;

    UINT16 ss2;
    UINT16 rsvd3;

    UINT32 cr3;

    UINT32 eip;

    UINT32 eflags;

    UINT32 eax;

    UINT32 ecx;

    UINT32 edx;

    UINT32 ebx;

    UINT32 esp;

    UINT32 ebp;

    UINT32 esi;

    UINT32 edi;

    UINT16 es;
    UINT16 rsvd;

    UINT16 cs;
    UINT16 rsvd5;

    UINT16 ss;
    UINT16 rsvd6;

    UINT16 ds;
    UINT16 rsvd7;

    UINT16 fs;
    UINT16 rsvd8;

    UINT16 gs;
    UINT16 rsvd9;

    UINT16 ldtss; // ldt segment selector
    UINT16 rsvd10;

    UINT16 t;     //debug trap, [15:1] must be 0
    UINT16 iomap; //io map base address

    UINT32 ssp; //SHADOW STACK POINTER
} x86_TSS;
#pragma pack()

// see figure 7-11
#pragma pack(2)
typedef struct _X64_TSS
{
    UINT32 rsvd0;
    UINT32 rsp0_lo;
    UINT32 rsp0_hi;
    UINT32 rsp1_lo;
    UINT32 rsp1_hi;
    UINT32 rsp2_lo;
    UINT32 rsp2_hi;
    UINT32 rsvd1;
    UINT32 rsvd2;
    UINT32 ist1_lo;
    UINT32 ist1_hi;
    UINT32 ist2_lo;
    UINT32 ist2_hi;
    UINT32 ist3_lo;
    UINT32 ist3_hi;
    UINT32 ist4_lo;
    UINT32 ist4_hi;
    UINT32 ist5_lo;
    UINT32 ist5_hi;
    UINT32 ist6_lo;
    UINT32 ist6_hi;
    UINT32 ist7_lo;
    UINT32 ist7_hi;
    UINT32 rsvd3;
    UINT32 rsvd4;
    UINT16 rsvd5;
    UINT32 iomap; // io map base address
} X64_TSS;
#pragma pack()

//see figure 7-10
#pragma pack(1)
typedef struct _X16_TSS
{
    UINT8 ptl; // previous task link
    UINT8 sp0;
    UINT8 ss0;
    UINT8 sp1;
    UINT8 ss1;
    UINT8 sp2;
    UINT8 ss2;
    UINT8 ip;
    UINT8 flag;
    UINT8 ax;
    UINT8 cx;
    UINT8 dx;
    UINT8 bx;
    UINT8 sp;
    UINT8 bp;
    UINT8 si;
    UINT8 di;
    UINT8 es;
    UINT8 cs;
    UINT8 ss;
    UINT8 ds;
    UINT8 ldtss; //task ldt selector
} X16_TSS;
#pragma pack()

//see figure 6-2, task gate descriptor only available in x86 mode 
typedef union _X86_TASKGATE_DESCRIPTOR {
    UINT64 value;
    struct
    {
        UINT64 ign0 : 16;     //[15:0],
        UINT64 selector : 16; //[31:16], tss segment selector[15:0]
        UINT64 ign1 : 8;      //[39:32],
        UINT64 type : 4;      //[43:40], see table 3-2, 0101b
        UINT64 s : 1;         //[44], must be 0
        UINT64 dpl : 2;       //[46:45], dpl
        UINT64 p : 1;         //[47], present
        UINT64 ign2 : 16;     //[63:48],
    } fields;
} X86_TASKGATE_DESCRIPTOR, *P_X86_TASKGATE_DESCRIPTOR;

// see figure 6-10
typedef struct _IA32_INTERRUPT_SSP_TABLE
{
    UINT64 notuse;
    UINT64 ist1;
    UINT64 ist2;
    UINT64 ist3;
    UINT64 ist4;
    UINT64 ist5;
    UINT64 ist6;
    UINT64 ist7;
} IA32_INTERRUPT_SSP_TABLE;



#endif