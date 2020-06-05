#include <stdlib.h>
#include <stdio.h>
#include "4_level_paging.h"
#include "segment.h"

int main()
{

	PML4E pml4e;
	pml4e.Value = 0;
	pml4e.P = 1;
	EPTP eptp;
	eptp.Value = 0;
	eptp.Fields.MT = 3;
	printf("pml4  is 0x%llx \n", eptp.Value);

	X64_SYSTEM_DESCRIPTOR x64_system_des;
	x64_system_des.Value.hi = 0x0;
	x64_system_des.Value.lo = 0x0;
	x64_system_des.Fields.limit_15_0 = 0x01;
	x64_system_des.Fields.base_63_32 = 0xff;
	printf("x64_system_descriptor low is 0x%llx, high is 0x%llx\n", x64_system_des.Value.lo ,x64_system_des.Value.hi );
	return 0;
}
