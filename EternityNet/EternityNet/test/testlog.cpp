#include"LogUtil.h"
using namespace ety;

int main()
{
	StartLog("EFTest");
	EnablePrintLog();

	WriteLog("%s,%s", "Tender is the", "night");
	WriteErrLog("Let people say what they want%d s", 5);
	WriteDetailLog(__FILE__, __LINE__, "So easy _ %s", "EF");
	WriteFatalLog(__FILE__, __LINE__, "Whatever is worth doing is worth doing well");

	WriteLog("%s,%s", "Tender is the", "night");
	WriteErrLog("Let people say what they want%d s", 5);
	WriteDetailLog(__FILE__, __LINE__, "So easy _ %s", "EF");
	WriteFatalLog(__FILE__, __LINE__, "Whatever is worth doing is worth doing well");
	
return 0;
}
