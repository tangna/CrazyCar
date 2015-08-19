#include "cocos2d.h"

//网络连接
#include "network/HttpClient.h"

using namespace std;
using namespace cocos2d::network;

class Network
{
public:
	Network();
	Network(string url);

	//设置各个成员的值
	void setUrl(string url);
	void setUser(string user);
	void setName(string name);
	void setPwd(string pwd);
	void setUid(string uid);
	void setScore(string score);

	void initRegister(string operate, string user, string name, string pwd);
	void initLogin(string operate, string user, string pwd);
	void initRank(string opreate);
	void connectNetwork();
	void CallbackData(HttpClient *client, HttpResponse *response);
	vector<char>* getData();
	string getUrl();
	~Network();

private:
	HttpRequest* request;
	vector<char> *data;

	string url; //网站基址
	string user;
	string name;
	string pwd;
	string uid;
	string score;
};