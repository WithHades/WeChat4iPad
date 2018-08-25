#include "stdafx.h"
#include "wars.h"




wars& wars::Instance()
{
	static wars instance_;
	return instance_;
}
