int ports[] = {0x01,0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int input[9];
#include "hitechnic-protoboard.h"

void getdata(int rob){
	input[rob]=HTPBreadIO(HTPB, ports[rob]);
}

void getalldata (){
	for(int rob=1; rob<8; rob++){
		if(HTPBreadIO(HTPB, ports[rob])==0) input[rob]=0;
		else input[rob]=1;
	}
}
