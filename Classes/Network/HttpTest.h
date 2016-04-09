#pragma once
#include "cocos2d.h"
#include "network\HttpClient.h"
USING_NS_CC;

class HttpTest
{
public:
	void onHttpRequest(std::string type, std::string url);
	void onHttpResponse(network::HttpClient* sender, network::HttpResponse* response);
};