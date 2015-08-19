#include "Network.h"
#include "network/HttpClient.h"

Network::Network()
{
}

Network::Network(string url)
{
	//进行网络连接
	url = "http://www.mdnt-cn.com/api/crazycar/";
}

//设置参数值
void Network::setUrl(string url)
{
	this->url = url;
}

void Network::setUser(string user)
{
	this->user = user;
}

void Network::setName(string name)
{
	this->name = name;
}
void Network::setPwd(string pwd)
{
	this->pwd = pwd;
}

void Network::setUid(string uid)
{
	this->uid = uid;
}

void Network::setScore(string score)
{
	this->score = score;
}

void Network::initRegister(string operate, string user, string name, string pwd)
{
	/*this->setUser(user);
	this->setName(name);
	this->setPwd(pwd);*/

	url.append(operate);
	url.append("?User=" + user);
	url.append("&Name=");
	url.append("&Pin=" + pwd);
}

void Network::initLogin(string operate, string user, string pwd)
{
	/*this->setUser(user);
	this->setName(name);
	this->setPwd(pwd);*/

	url.append(operate);
	url.append("?User=" + user);
	url.append("&Pin=" + pwd);
}

void Network::initRank(string opreate)
{
	url.append(opreate);
}

void Network::connectNetwork()
{
	request = new HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(Network::CallbackData, this));
	HttpClient::getInstance()->send(request);
}

string Network::getUrl()
{
	return this->url;
}

void Network::CallbackData(HttpClient *client, HttpResponse *response)
{
	this->data = response->getResponseData();
	this->data->push_back('\0');
}

vector<char>* Network::getData()
{
	return this->data;
}

Network::~Network()
{
	//delete[] request;
}