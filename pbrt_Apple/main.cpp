#include "unittest.h"

void UnitTest()
{
	Vector_UnitTest();
	Point_UnitTest();
	Normal_UnitTest();
	Ray_UnitTest();
}
int main()
{
	UnitTest();
	return 0;
}