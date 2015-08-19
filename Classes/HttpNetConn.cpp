#include "HttpNetConn.h"


#include "json/document.h"
#include "json/rapidjson.h"



using namespace rapidjson;

bool NetConnect::init()
{
	return true;
}
/*
NetConnect* NetConnect::getInstance()
{
	if (_net==NULL)
	{
		_net = new NetConnect();
		//return _net;
	}
	return _net;

}
*/
/*
bool NetConnect::init()
{
	_loginCode = -2;
}*/

void NetConnect::getData()
{
	auto httpCilent = HttpClient::getInstance();
	auto request = new HttpRequest();

	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl("http://www.mdnt-cn.com/api/crazycar/RankList.php");
	request->setResponseCallback(this, callfuncND_selector(NetConnect::httpReqFinished));

	request->setTag("AAnet");

	httpCilent->setTimeoutForConnect(30);
	httpCilent->send(request);

	request->release();
}

void NetConnect::httpReqFinished(CCNode* node, void* obj)
{
	HttpResponse* response = (HttpResponse*)obj;
	if (!response->isSucceed())
	{
		//CCLOG("Receive Error! %s\n", response->getErrorBuffer());
		return;
	}

	const char* tag = response->getHttpRequest()->getTag();

	if (0 == strcmp("AAnet", tag))
	{
		std::vector<char>*data = response->getResponseData();
		int data_length = data->size();

		std::string res;
		for (int i = 0; i < data_length; ++i)
		{
			res += (*data)[i];
		}
		res += '\0';
		//CCLOG("%s", res.c_str());
	}
}

//登陆
bool NetConnect::checkLogin(std::string user, std::string password) 
{
	std::string urlBase = "http://www.mdnt-cn.com/api/crazycar/";
	urlBase = urlBase.append("Login.php?User=");
	urlBase = urlBase.append(user);
	urlBase = urlBase.append("&Pin=");
	urlBase = urlBase.append(password);


	//CCLOG("%s", urlBase.c_str());

	HttpRequest *request = new HttpRequest();
	request->setUrl(urlBase.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	
	request->setResponseCallback(CC_CALLBACK_2(NetConnect::loginNetworkCallback, this));
	
	HttpClient::getInstance()->send(request);

	return (_loginCode == 0);
}

void NetConnect::loginNetworkCallback(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	std::vector<char> *data = response->getResponseData();
	data->push_back('\0');

	char *json = nullptr;
	json = (char *)malloc(data->size() + 1);
	memccpy(json, data->data(), 0, data->size() + 1);

	Document jsonDocment;
	jsonDocment.Parse<0>(json);

	int statusCode = jsonDocment["StatusCode"].GetInt();
	_loginCode = statusCode;
	const char* message = jsonDocment["Message"].GetString();

	//CCLOG("StatusCode:%d Message:%s", statusCode, message);

	//const char* name = jsonDocment["Body"]["Login"]["User"].GetString();

	//返回参数，用户Uid
	if (_loginCode==0)
	{
		const char* uid = jsonDocment["Body"]["Uid"].GetString();
		_uid = uid;
		//CCLOG("Uid:%d", uid);
	}
	
}

//注册
bool NetConnect::registerNewUser(std::string user, std::string password, std::string repwd)
{
	if (password==repwd&&user.length()>0)
	{
		std::string urlBase = "http://www.mdnt-cn.com/api/crazycar/";
		urlBase = urlBase.append("Register.php?User=");
		urlBase = urlBase.append(user);
		//urlBase = urlBase.append("&Name=");
		//urlBase = urlBase.append(Name);
		urlBase = urlBase.append("&Pin=");
		urlBase = urlBase.append(password);


		//CCLOG("%s", urlBase.c_str());

		HttpRequest *request = new HttpRequest();
		request->setUrl(urlBase.c_str());
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(NetConnect::registerCallback, this));

		HttpClient::getInstance()->send(request);
	}
	return false;
}

void NetConnect::registerCallback(HttpClient *client, HttpResponse *response)
{
	std::vector<char> *data = response->getResponseData();
	data->push_back('\0');
	char *json = nullptr;
	json = (char *)malloc(data->size() + 1);
	memccpy(json, data->data(), 0, data->size() + 1);

	Document jsonDocment;
	jsonDocment.Parse<0>(json);
	int statusCode = jsonDocment["StatusCode"].GetInt();
	_registerCode = statusCode;
	const char* message = jsonDocment["Message"].GetString();
	//CCLOG("StatusCode:%d Message:%s", statusCode, message);

	if (_registerCode==0)
	{
		const char* uid = jsonDocment["Body"]["Uid"].GetString();

		_uid = uid;
		///CCLOG("Uid:%d", uid);
	}
	

}

//发送rank
bool NetConnect::sendRank(std::string uid,int rank)
{
	std::string urlBase = "http://www.mdnt-cn.com/api/crazycar/";
	urlBase = urlBase.append("Sumit.php?Uid=");
	urlBase = urlBase.append(uid);
	//urlBase = urlBase.append("&Name=");
	//urlBase = urlBase.append(Name);
	urlBase = urlBase.append("&Score=");
	urlBase = urlBase.append(StringUtils::format("%d",rank));


	//CCLOG("%s", urlBase.c_str());

	HttpRequest *request = new HttpRequest();
	request->setUrl(urlBase.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(NetConnect::registerCallback, this));

	HttpClient::getInstance()->send(request);

	return (_sendRankCode==0);
}

void NetConnect::sendRankCallback(HttpClient *client, HttpResponse *response)
{
	std::vector<char> *data = response->getResponseData();
	data->push_back('\0');
	char *json = nullptr;
	json = (char *)malloc(data->size() + 1);
	memccpy(json, data->data(), 0, data->size() + 1);

	Document jsonDocment;
	jsonDocment.Parse<0>(json);
	int statusCode = jsonDocment["StatusCode"].GetInt();

	const char* message = jsonDocment["Message"].GetString();
	//CCLOG("StatusCode:%d Message:%s", statusCode, message);
	_sendRankCode = statusCode;
}

bool NetConnect::getRank()
{
	std::string urlBase = "http://www.mdnt-cn.com/api/crazycar/RankList.php";
	//CCLOG("%s", urlBase.c_str());

	HttpRequest *request = new HttpRequest();
	request->setUrl(urlBase.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(NetConnect::registerCallback, this));

	HttpClient::getInstance()->send(request);

	return true;
}

void NetConnect::getRankCallback(HttpClient *client, HttpResponse *response)
{
	std::vector<char> *data = response->getResponseData();
	data->push_back('\0');
	char *json = nullptr;
	json = (char *)malloc(data->size() + 1);
	memccpy(json, data->data(), 0, data->size() + 1);

	Document jsonDocment;
	jsonDocment.Parse<0>(json);
	int statusCode = jsonDocment["StatusCode"].GetInt();
	_getRankCode = statusCode;
	const char* message = jsonDocment["Message"].GetString();
	//CCLOG("StatusCode:%d Message:%s", statusCode, message);
	
}