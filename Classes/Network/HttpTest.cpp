#include "HttpTest.h"

void HttpTest::onHttpRequest(std::string type, std::string url)
{
	network::HttpRequest *request = new network::HttpRequest();
	if (type == "get")
	{
		request->setRequestType(network::HttpRequest::Type::GET);
	}
	else if (type == "post")
	{
		request->setRequestType(network::HttpRequest::Type::POST);
		std::string data = "hello world!";
		request->setRequestData(data.c_str(), data.length());
	}
	request->setUrl(url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(HttpTest::onHttpResponse, this));
	network::HttpClient::getInstance()->send(request);
	request->release();
}

void HttpTest::onHttpResponse(network::HttpClient* sender, network::HttpResponse* response)
{
	if (!response)
	{
		CCLOG("no response");
		return;
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code:%d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLOG("response code: %s",statusString);

	if (!response->isSucceed())
	{
		CCLOG("response failed");
		CCLOG("error buffer: %s", response->getErrorBuffer());
		return;
	}
	std::vector<char> *v = response->getResponseData();
	for (int i = 0; i < v->size(); i++)
	{
		printf("%c", v->at(i));
	}
}