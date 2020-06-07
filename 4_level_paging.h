#ifndef __4_LEVEL_PAGING_H__
#define __4_LEVEL_PAGING_H__

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


// by intel64 and IA32 SDM

// 4 level paging and 4kb paging size

#define MAXPHYADDR 48


// see table 4-12, 4 level paging no pcid
typedef struct _CR3_NO_PCIDE
{
    union {
        UINT64 value;
        struct
        {
            UINT64 ign0 : 3;                //[2:0]
            UINT64 pwt : 1;                 //[3], page level write-through
            UINT64 pcd : 1;                 //[4], page level cache disable
            UINT64 ign1 : 7;                //[11:5]
            UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12],  physical address of the 4KB aligned PML4 table used for linear address translation
            UINT64 rsvd0 : 64 - MAXPHYADDR; //[63:N], must be 0
        };
    };
} CR3_NO_PCIDE, *PCR3_NO_PCIDE;

// see table 4-13, 4 level paging have pcid
typedef struct _CR3_HAS_PCIDE_
{
    union {
        UINT64 value;
        struct
        {
            UINT64 pcid : 12;               //[11:0], pcid
            UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12],  physical address of the 4KB aligned PML4 table used for linear address translation
            UINT64 rsvd0 : 64 - MAXPHYADDR; //[63:N], must be 0
        };
    };
} CR3_HAS_PCIDE, *PCR3_HAS_PCIDE;


// see table 4-14,
typedef struct _PML4E
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0], Present, Must be 1,
            UINT64 rw : 1;                  //[1], ReadWrite, If 0, writes not allowed.
            UINT64 us : 1;                  //[2], UserSupervisor,If 0, user-mode accesses not allowed.
            UINT64 pwt : 1;                 //[3], PageWriteThrough, Determines the memory type used to access PDPT.
            UINT64 pcd : 1;                 //[4], PageCacheDisable, Determines the memory type used to access PDPT.
            UINT64 a : 1;                   //[5], Accessed, If 0, this entry has not been used for translation.
            UINT64 ign0 : 1;                //[6], Ignore 0
            UINT64 ps : 1;                  //[7], Must be 0 for PML4E.
            UINT64 ign1 : 4;                //[11:8]
            UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], physical address of 4KB aligned page directory pointer table referenced by this entry
            UINT64 rsvd0 : 52 - MAXPHYADDR; //[51:N], must be 0
            UINT64 ign2 : 11;               //[62:52]
            UINT64 xd : 1;                  // ExecuteDisable, If 1, instruction fetches not allowed.
        };
    };
} PML4E, *PPML4E;

// see table 4-15, pdpte: 1GB page
typedef struct _PDPTE_1G
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0]
            UINT64 rw : 1;                  //[1]
            UINT64 us : 1;                  //[2]
            UINT64 pwt : 1;                 //[3]
            UINT64 pcd : 1;                 //[4]
            UINT64 a : 1;                   //[5]
            UINT64 d : 1;                   //[6], dirty
            UINT64 ps : 1;                  //[7], must 1, this entry maps a 1GB page.
            UINT64 g : 1;                   //[8], Global
            UINT64 ign0 : 3;                //[11:9]
            UINT64 pat : 1;                 //[12]
            UINT64 rsvd0 : 17;              //[29:13], must be 0
            UINT64 pfa : MAXPHYADDR - 30;   //[N-1:30], physical address of the 1GB page referenced by this entry
            UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must be 0
            UINT64 ign1 : 7;                //[58:52]
            UINT64 pk : 4;                  //[62:59], protection key
            UINT64 xd : 1;                  //[63], If 1, instruction fetches not allowed.
        };
    };
} PDPTE_1G, *PPDPTE_1G;

// see table 4-16, pdpte: page directory
typedef struct _PDPTE_PD
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0]
            UINT64 rw : 1;                  //[1]
            UINT64 us : 1;                  //[2]
            UINT64 pwt : 1;                 //[3]
            UINT64 pcd : 1;                 //[4]
            UINT64 a : 1;                   //[5]
            UINT64 ign0 : 1;                //[6]
            UINT64 ps : 1;                  //[7], PageSize If 1, this entry maps a 1GB page.
            UINT64 ign1 : 4;                //[11:8]
            UINT64 pde : MAXPHYADDR - 12;   //[N-1:12], Address of page directory.
            UINT64 rsvd0 : 52 - MAXPHYADDR; //[51:N], must be 0
            UINT64 ign2 : 11;               //[62:52]
            UINT64 xd : 1;                  //[63], If 1, instruction fetches not allowed.
        };
    };
} PDPTE_PD, *PPDPTE_PD;

// see table 4-17, pde: 2MB page
typedef struct _PDE_2M
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0]
            UINT64 rw : 1;                  //[1]
            UINT64 us : 1;                  //[2]
            UINT64 pwt : 1;                 //[3]
            UINT64 pcd : 1;                 //[4]
            UINT64 a : 1;                   //[5]
            UINT64 d : 1;                   //[6], dirty
            UINT64 ps : 1;                  //[7], must 1, this entry maps a 2MB page.
            UINT64 g : 1;                   //[8], Global
            UINT64 ign0 : 3;                //[11:9]
            UINT64 pat : 1;                 //[12]
            UINT64 rsvd0 : 9;               //[20:13], must be 0
            UINT64 pfa : MAXPHYADDR - 21;   //[N-1:21], physical address of the 2MB page referenced by this entry
            UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must be 0
            UINT64 ign1 : 7;                //[58:52]
            UINT64 pk : 4;                  //[62:59], protection key
            UINT64 xd : 1;                  //[63], If 1, instruction fetches not allowed.
        };
    };
} PDE_2M, *PPDE_2M;

// see table 4-18, pde: page table
typedef struct _PDE_PT
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0], Must be 1,
            UINT64 rw : 1;                  //[1], If 0, writes not allowed.
            UINT64 us : 1;                  //[2],
            UINT64 pwt : 1;                 //[3]
            UINT64 pcd : 1;                 //[4]
            UINT64 a : 1;                   //[5], If 0, this entry has not been used for translation.
            UINT64 ign0 : 1;                //[6]
            UINT64 ps : 1;                  //[7], must be 0
            UINT64 ign1 : 4;                //[11:8]
            UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], Address of page table
            UINT64 rsvd0 : 52 - MAXPHYADDR; //[51:N], must be 0
            UINT64 ign2 : 11;
            UINT64 xd : 1; // If 1, instruction fetches not allowed.
        };
    };
} PDE_PT, *PPDE_PT;

// see table 4-19, pte: 4KB page
typedef struct _PTE
{
    union {
        UINT64 value;
        struct
        {
            UINT64 p : 1;                   //[0], Must be 1, region invalid if 0.
            UINT64 rw : 1;                  //[1]
            UINT64 us : 1;                  //[2]
            UINT64 pwt : 1;                 //[3]
            UINT64 pcd : 1;                 //[4]
            UINT64 a : 1;                   //[5]
            UINT64 d : 1;                   //[6], dirty, If 0, the memory backing this page has not been written to.
            UINT64 pat : 1;                 //[7], PageAccessType, Determines the memory type used to access the memory.
            UINT64 g : 1;                   //[8],Global, If 1 and the PGE bit of CR4 is set, translations are global.
            UINT64 ign0 : 3;                //[11:9]
            UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], physical address of the 4KB page referenced by this entry
            UINT64 rsvd0 : 52 - MAXPHYADDR; //[52:N], must be 0
            UINT64 ign1 : 7;                //[58:52]
            UINT64 pk : 4;                  //[62:59], ProtectionKey,If the PKE bit of CR4 is set, determines the protection key.
            UINT64 xd : 1;                  //[63], If 1, instruction fetches not allowed.
        };
    };
} PTE, *PPTE;

/**********EPT********** */

// see table 24-8
typedef union _EPTP {
    UINT64 value;
    struct
    {
        UINT64 mt : 3;                     //[2:0], memory type, 0 UC, 6 WB
        UINT64 pwl : 3;                    //[5:3], the value 1 less than page walk length
        UINT64 ad : 1;                     //[6], Setting this control to 1 enables accessed and dirty flags for EPT
        UINT64 sss : 1;                    //[7], ebable enforcement of access rights for supervisor shadow-stack pages
        UINT64 rsvd0 : 4;                  //[11:8]
        UINT64 ept_pml4 : MAXPHYADDR - 12; //[N-1:12], physical address of EPT PML4 table
        UINT64 rsvd1 : 64 - MAXPHYADDR;    //[63:M]
    } fields;
} EPTP, *PEPTP;

// see table 28-1
typedef union _EPT_PML4E {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                       //[0],read access
        UINT64 w : 1;                       //[1],write access
        UINT64 x : 1;                       //[2],0 indicates instruction fetches allowed; 1 indicate fetches allowed supervisor mode linear add
        UINT64 rsvd0 : 5;                   //[7:3], must be 0
        UINT64 a : 1;                       //[8], access flag
        UINT64 ign0 : 1;                    //[9],
        UINT64 xu : 1;                      //[10],executr access for user mode linear address,1 indicate instruction fetch allowed user mode linear add
        UINT64 ign1 : 1;                    //[11],
        UINT64 ept_pdpte : MAXPHYADDR - 12; //[(N-1):12], address of EPT page directory pointer table
        UINT64 rsvd1 : 52 - MAXPHYADDR;     //[51:N]
        UINT64 ign2 : 12;                   //[63:52]
    } fields;
} EPT_PML4E, *PEPT_PML4E;

// see table 28-2
typedef union _EPT_PDPTE_1G {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                   //[0]
        UINT64 w : 1;                   //[1]
        UINT64 x : 1;                   //[2]
        UINT64 mt : 3;                  //[5:3], must be 0
        UINT64 ipat : 1;                //[6], ignore PAT memory type for this 1GB page
        UINT64 ps : 1;                  //[7], must 1, maps 1GB page size, otherwise frference an EPT page directory
        UINT64 a : 1;                   //[8], access flag
        UINT64 d : 1;                   //[9], dirty flag
        UINT64 xu : 1;                  //[10], wheather instruction fetches are allowed from user mode linear address in the 1GB page
        UINT64 ign0 : 1;                // bit 11
        UINT64 rsvd0 : 18;              //[29:12], must be 0
        UINT64 pfa : MAXPHYADDR - 30;   //[N-1:30], physical address of the 1GB page  referenced by this entry
        UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must 0
        UINT64 ign1 : 8;                //[59:52]
        UINT64 sss : 1;                 //[60], supervisor shadow stack
        UINT64 ign2 : 2;                //[62:61],
        UINT64 sve : 1;                 //[63], suppress #VE
    } fields;
} EPT_PDPTE_1G, *PEPT_PDPTE_1G;

// see table 28-3
typedef union _EPT_PDPTE {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                   //[0]
        UINT64 w : 1;                   //[1]
        UINT64 x : 1;                   //[2]
        UINT64 rsvd0 : 5;               //[7:3], must be 0
        UINT64 a : 1;                   //[8]
        UINT64 ign0 : 1;                //[9]
        UINT64 xu : 1;                  //[10]
        UINT64 ign1 : 1;                //[11]
        UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], physical address of 4KB aligned EPT page directory referenced by this entry
        UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must be 0
        UINT64 ign2 : 12;               //[63:52]
    } fields;
} EPT_PDPTE, *PEPT_PDPTE;

// see table 28-4
typedef union _EPT_PDE_2M {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                   //[0]
        UINT64 w : 1;                   //[1]
        UINT64 x : 1;                   //[2]
        UINT64 mt : 3;                  //[5:3], memory type for this 2MB page
        UINT64 ipat : 1;                //[6], ignore PAT memory type fo this 2MB page
        UINT64 ps : 1;                  //[7], must be 1 otherwise references an EPT page table
        UINT64 a : 1;                   //[8]
        UINT64 d : 1;                   //[9]
        UINT64 xu : 1;                  //[10]
        UINT64 ign0 : 1;                //[11]
        UINT64 rsvd0 : 9;               //[20:12], must be 0
        UINT64 pfa : MAXPHYADDR - 21;   //[N-1:21], physical address of 2MB PAGE by this entry
        UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must be 0
        UINT64 ign1 : 8;                //[59:52]
        UINT64 sss : 1;                 //[60], supervisor shadow stack
        UINT64 ign2 : 2;                //[62:61]
        UINT64 sve : 1;                 //[63], suppress #VE
    } fields;
} EPT_PDE_2M, *PEPT_PDE_2M;

// see table 28-5
typedef union _EPT_PDE {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                   //[0]
        UINT64 w : 1;                   //[1]
        UINT64 x : 1;                   //[2]
        UINT64 rsvd0 : 4;               //[6:3], must be 0
        UINT64 ps : 1;                  //[7], must be 0
        UINT64 a : 1;                   //[8]
        UINT64 ign0 : 1;                //[9]
        UINT64 xu : 1;                  //[10]
        UINT64 ign1 : 1;                //[11]
        UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], physical address of 4KB aligned EPT page table referenced by this entry
        UINT64 rsvd1 : 52 - MAXPHYADDR; //[51:N], must be 0
        UINT64 ign2 : 12;               //[63:52]
    } fields;
} EPT_PDE, *PEPT_PDE;

// see table 28-6
typedef union _EPT_PTE {
    UINT64 value;
    struct
    {
        UINT64 r : 1;                   //[0]
        UINT64 w : 1;                   //[1]
        UINT64 x : 1;                   //[2]
        UINT64 mt : 3;                  //[5:3], EPT memory type
        UINT64 ipat : 1;                //[6], ignore PAT
        UINT64 ign0 : 1;                //[7]
        UINT64 a : 1;                   //[8]
        UINT64 d : 1;                   //[9]
        UINT64 xu : 1;                  //[10]
        UINT64 ign1 : 1;                //[11]
        UINT64 pfa : MAXPHYADDR - 12;   //[N-1:12], physical address of the 4KB page referenced by this entry
        UINT64 rsvd0 : 52 - MAXPHYADDR; //[51:N]
        UINT64 ign2 : 8;                //[59:52]
        UINT64 sss : 1;                 //[60], supervisor shadow stack
        UINT64 spp : 1;                 //[61], sub page write permissions
        UINT64 ign3 : 1;                //[62]
        UINT64 sve : 1;                 //[63], suppress #VE
    } fields;
} EPT_PTE, *PEPT_PTE;

#endif
