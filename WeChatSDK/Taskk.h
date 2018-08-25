#pragma once
#include "WeChatProto.h"
#include "curl/curl.h"
#include "TT.h"


//void task_Start(WeChatProto*W, WxUser*Auth);3

CURLcode curl_post_req(const string &url, const string &postParams, string &response);

std::string mm_post(std::string url_post, std::string postParams);
