#ifndef _NET_CONNECTION_H_  
#define _NET_CONNECTION_H_  
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include <cocos2d.h>  

USING_NS_CC;
using namespace network;

class NetConnect : public Ref
{
public:
	//static NetConnect* getInstance();

	CREATE_FUNC(NetConnect);

	virtual bool init();

	void getData();
	
	//µÇÂ½
	bool checkLogin(std::string user,std::string password);
	std::string getUid(){ return _uid; };
	void loginNetworkCallback(HttpClient *client,HttpResponse *response);
	//×¢²á
	bool registerNewUser(std::string user,std::string password,std::string repwd);
	void registerCallback(HttpClient *client,HttpResponse *response);
	//·¢ËÍrank
	bool sendRank(std::string uid,int rank);
	void sendRankCallback(HttpClient *client, HttpResponse *response);
	//»ñµÃrank
	bool getRank();
	void getRankCallback(HttpClient *client, HttpResponse *response);

	void httpReqFinished(CCNode* node, void* obj);

	//static NetConnect* _net;
private:
	//NetConnect();

	int _loginCode;
	std::string _uid;

	int _registerCode;
	int _sendRankCode;
	int _getRankCode;

};

//NetConnect* NetConnect::_net = new NetConnect();

#endif  