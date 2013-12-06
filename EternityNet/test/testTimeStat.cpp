
#include"../utilities/TimeStat.h"
using namespace ety;

int main(int arg, char** argv)
{
	
	TimeStat ts = TimeStat::now();

	printf("new time : %s\n", ts.toFormatString().c_str() );

	printf("test < result = %d \n", ts < TimeStat::now() );
	sleep(2);
	ts = TimeStat::now();

	printf("changed time : %s\n", ts.toFormatString().c_str() );
}
