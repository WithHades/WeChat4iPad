#pragma once



#include "WxUser.h"
#include "PbHead.h"
#include <string>



std::string PB_GetLoginQRCode(void*Auth);
std::string PB_CheckLoginQRCode(void*Auth);

std::string PB_RsaLoginPart(void*);
std::string PB_AESLoginPart(void*);
std::string PB_NewInit(void*,string);
std::string PB_NewSync(std::string&synckey);
