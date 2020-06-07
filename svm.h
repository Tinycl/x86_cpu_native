#ifndef __SVM_H__
#define __SVM_H__

typedef enum _SVM_VM_EXIT
{
    VMEXIT_CR0_READ = 0x0000,
    VMEXIT_CR1_READ = 0x0001,
    VMEXIT_CR2_READ = 0x0002,
    VMEXIT_CR3_READ = 0x0003,
    VMEXIT_CR4_READ = 0x0004,
    VMEXIT_CR5_READ = 0x0005,
    VMEXIT_CR6_READ = 0x0006,
    VMEXIT_CR7_READ = 0x0007,
    VMEXIT_CR8_READ = 0x0008,
    VMEXIT_CR9_READ = 0x0009,
    VMEXIT_CR10_READ = 0x000a,
    VMEXIT_CR11_READ = 0x000b,
    VMEXIT_CR12_READ = 0x000c,
    VMEXIT_CR13_READ = 0x000d,
    VMEXIT_CR14_READ = 0x000e,
    VMEXIT_CR15_READ = 0x000f,
    VMEXIT_CR0_WRITE = 0x0010,
    VMEXIT_CR1_WRITE = 0x0011,
    VMEXIT_CR2_WRITE = 0x0012,
    VMEXIT_CR3_WRITE = 0x0013,
    VMEXIT_CR4_WRITE = 0x0014,
    VMEXIT_CR5_WRITE = 0x0015,
    VMEXIT_CR6_WRITE = 0x0016,
    VMEXIT_CR7_WRITE = 0x0017,
    VMEXIT_CR8_WRITE = 0x0018,
    VMEXIT_CR9_WRITE = 0x0019,
    VMEXIT_CR10_WRITE = 0x001a,
    VMEXIT_CR11_WRITE = 0x001b,
    VMEXIT_CR12_WRITE = 0x001c,
    VMEXIT_CR13_WRITE = 0x001d,
    VMEXIT_CR14_WRITE = 0x001e,
    VMEXIT_CR15_WRITE = 0x001f,
    VMEXIT_DR0_READ = 0x0020,
    VMEXIT_DR1_READ = 0x0021,
    VMEXIT_DR2_READ = 0x0022,
    VMEXIT_DR3_READ = 0x0023,
    VMEXIT_DR4_READ = 0x0024,
    VMEXIT_DR5_READ = 0x0025,
    VMEXIT_DR6_READ = 0x0026,
    VMEXIT_DR7_READ = 0x0027,
    VMEXIT_DR8_READ = 0x0028,
    VMEXIT_DR9_READ = 0x0029,
    VMEXIT_DR10_READ = 0x002a,
    VMEXIT_DR11_READ = 0x002b,
    VMEXIT_DR12_READ = 0x002c,
    VMEXIT_DR13_READ = 0x002d,
    VMEXIT_DR14_READ = 0x002e,
    VMEXIT_DR15_READ = 0x002f,
    VMEXIT_DR0_WRITE = 0x0030,
    VMEXIT_DR1_WRITE = 0x0031,
    VMEXIT_DR2_WRITE = 0x0032,
    VMEXIT_DR3_WRITE = 0x0033,
    VMEXIT_DR4_WRITE = 0x0034,
    VMEXIT_DR5_WRITE = 0x0035,
    VMEXIT_DR6_WRITE = 0x0036,
    VMEXIT_DR7_WRITE = 0x0037,
    VMEXIT_DR8_WRITE = 0x0038,
    VMEXIT_DR9_WRITE = 0x0039,
    VMEXIT_DR10_WRITE = 0x003a,
    VMEXIT_DR11_WRITE = 0x003b,
    VMEXIT_DR12_WRITE = 0x003c,
    VMEXIT_DR13_WRITE = 0x003d,
    VMEXIT_DR14_WRITE = 0x003e,
    VMEXIT_DR15_WRITE = 0x003f,
    VMEXIT_EXCEPTION_DE = 0x0040,
    VMEXIT_EXCEPTION_DB = 0x0041,
    VMEXIT_EXCEPTION_NMI = 0x0042,
    VMEXIT_EXCEPTION_BP = 0x0043,
    VMEXIT_EXCEPTION_OF = 0x0044,
    VMEXIT_EXCEPTION_BR = 0x0045,
    VMEXIT_EXCEPTION_UD = 0x0046,
    VMEXIT_EXCEPTION_NM = 0x0047,
    VMEXIT_EXCEPTION_DF = 0x0048,
    VMEXIT_EXCEPTION_09 = 0x0049,
    VMEXIT_EXCEPTION_TS = 0x004a,
    VMEXIT_EXCEPTION_NP = 0x004b,
    VMEXIT_EXCEPTION_SS = 0x004c,
    VMEXIT_EXCEPTION_GP = 0x004d,
    VMEXIT_EXCEPTION_PF = 0x004e,
    VMEXIT_EXCEPTION_15 = 0x004f,
    VMEXIT_EXCEPTION_MF = 0x0050,
    VMEXIT_EXCEPTION_AC = 0x0051,
    VMEXIT_EXCEPTION_MC = 0x0052,
    VMEXIT_EXCEPTION_XF = 0x0053,
    VMEXIT_EXCEPTION_20 = 0x0054,
    VMEXIT_EXCEPTION_21 = 0x0055,
    VMEXIT_EXCEPTION_22 = 0x0056,
    VMEXIT_EXCEPTION_23 = 0x0057,
    VMEXIT_EXCEPTION_24 = 0x0058,
    VMEXIT_EXCEPTION_25 = 0x0059,
    VMEXIT_EXCEPTION_26 = 0x005a,
    VMEXIT_EXCEPTION_27 = 0x005b,
    VMEXIT_EXCEPTION_28 = 0x005c,
    VMEXIT_EXCEPTION_VC = 0x005d,
    VMEXIT_EXCEPTION_SX = 0x005e,
    VMEXIT_EXCEPTION_31 = 0x005f,
    VMEXIT_INTR = 0x0060,
    VMEXIT_NMI = 0x0061,
    VMEXIT_SMI = 0x0062,
    VMEXIT_INIT = 0x0063,
    VMEXIT_VINTR = 0x0064,
    VMEXIT_CR0_SEL_WRITE = 0x0065,
    VMEXIT_IDTR_READ = 0x0066,
    VMEXIT_GDTR_READ = 0x0067,
    VMEXIT_LDTR_READ = 0x0068,
    VMEXIT_TR_READ = 0x0069,
    VMEXIT_IDTR_WRITE = 0x006a,
    VMEXIT_GDTR_WRITE = 0x006b,
    VMEXIT_LDTR_WRITE = 0x006c,
    VMEXIT_TR_WRITE = 0x006d,
    VMEXIT_RDTSC = 0x006e,
    VMEXIT_RDPMC = 0x006f,
    VMEXIT_PUSHF = 0x0070,
    VMEXIT_POPF = 0x0071,
    VMEXIT_CPUID = 0x0072,
    VMEXIT_RSM = 0x0073,
    VMEXIT_IRET = 0x0074,
    VMEXIT_SWINT = 0x0075,
    VMEXIT_INVD = 0x0076,
    VMEXIT_PAUSE = 0x0077,
    VMEXIT_HLT = 0x0078,
    VMEXIT_INVLPG = 0x0079,
    VMEXIT_INVLPGA = 0x007a,
    VMEXIT_IOIO = 0x007b,
    VMEXIT_MSR = 0x007c,
    VMEXIT_TASK_SWITCH = 0x007d,
    VMEXIT_FERR_FREEZE = 0x007e,
    VMEXIT_SHUTDOWN = 0x007f,
    VMEXIT_VMRUN = 0x0080,
    VMEXIT_VMMCALL = 0x0081,
    VMEXIT_VMLOAD = 0x0082,
    VMEXIT_VMSAVE = 0x0083,
    VMEXIT_STGI = 0x0084,
    VMEXIT_CLGI = 0x0085,
    VMEXIT_SKINIT = 0x0086,
    VMEXIT_RDTSCP = 0x0087,
    VMEXIT_ICEBP = 0x0088,
    VMEXIT_WBINVD = 0x0089,
    VMEXIT_MONITOR = 0x008a,
    VMEXIT_MWAIT = 0x008b,
    VMEXIT_MWAIT_CONDITIONAL = 0x008c,
    VMEXIT_XSETBV = 0x008d,
    VMEXIT_EFER_WRITE_TRAP = 0x008f,
    VMEXIT_CR0_WRITE_TRAP = 0x0090,
    VMEXIT_CR1_WRITE_TRAP = 0x0091,
    VMEXIT_CR2_WRITE_TRAP = 0x0092,
    VMEXIT_CR3_WRITE_TRAP = 0x0093,
    VMEXIT_CR4_WRITE_TRAP = 0x0094,
    VMEXIT_CR5_WRITE_TRAP = 0x0095,
    VMEXIT_CR6_WRITE_TRAP = 0x0096,
    VMEXIT_CR7_WRITE_TRAP = 0x0097,
    VMEXIT_CR8_WRITE_TRAP = 0x0098,
    VMEXIT_CR9_WRITE_TRAP = 0x0099,
    VMEXIT_CR10_WRITE_TRAP = 0x009a,
    VMEXIT_CR11_WRITE_TRAP = 0x009b,
    VMEXIT_CR12_WRITE_TRAP = 0x009c,
    VMEXIT_CR13_WRITE_TRAP = 0x009d,
    VMEXIT_CR14_WRITE_TRAP = 0x009e,
    VMEXIT_CR15_WRITE_TRAP = 0x009f,
    VMEXIT_NPF = 0x0400,
    AVIC_INCOMPLETE_IPI = 0x0401,
    AVIC_NOACCEL = 0x0402,
    VMEXIT_VMGEXIT = 0x0403,
} SVM_VM_EXIT;

#endif