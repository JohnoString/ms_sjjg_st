#if 0
#include <iostream>
#include <string>
using namespace std;

bool GetPortFromUrl(std::string url, uint32_t& port)
{
	if (url.empty())
	{
		return false;
	}

	// 判断下协议头是不是正确
	std::string prot = "";
	uint32_t default_port = 0;
	uint32_t http_pos = url.find("http://");
	uint32_t https_pos = url.find("https://");
	if (http_pos == 0)
	{
		prot = "http://";
		default_port = 80;
	}
	else if (https_pos == 0)
	{
		prot = "https://";
		default_port = 443;
	}
	else
	{
		return false;
	}

	uint32_t uri_pos = url.find("/", prot.size());
	uint32_t host_len = 0;
	if (uri_pos == -1)
	{
		host_len = url.size() - prot.size();
	}
	else
	{
		host_len = uri_pos - prot.size();
	}

	std::string host = url.substr(prot.size(), host_len);
	uint32_t port_pos = host.find(":");
	if (port_pos == -1)
	{
		port = default_port;
		return true;
	}

	port_pos++;

	std::string port_str = host.substr(port_pos, host.size() - port_pos);
	port = atoi(port_str.c_str());

	return true;
}

void MyParseURL2(const char* URL, char** host, unsigned int* port, char** uri, int withArgs)
{
	char* url_dup = nullptr;
	char* p_slash = nullptr;//主机后第一个斜杠的位置  
	char* p_colon = nullptr;//主机后第一个冒号的位置  
	char* start = 0;    //记录www开始的位置 
	char* pEnd = nullptr;
	int len = 0;


	if (URL == nullptr)
		return;

	url_dup = strdup(URL);
	url_dup = strlwr(url_dup);

	if (withArgs == 0)
	{
		// 去掉url里的参数
		pEnd = strchr(url_dup, '?');
		if (pEnd)
		{
			*pEnd = '\0';
		}
	}

	if (strncmp(url_dup, "https", 5) == 0)
	{
		*port = 443;
		start = url_dup + 5 + 3;
	}
	else if (strncmp(url_dup, "http", 4) == 0)
	{
		*port = 80;
		start = url_dup + 4 + 3;
	}
	else
	{
		*port = 80;
		start = url_dup;
	}

	p_slash = strchr(start, '/');
	if (p_slash != nullptr)
	{
		*uri = strdup(p_slash);
		len = (int)strlen(*uri);
		// *uri = /xx.php/ ,要去除最后的/
		if (len > 1 && (*uri)[len - 1] == '/' || (*uri)[len - 1] == '\\')
		{
			(*uri)[len - 1] = '\0';
		}
		*p_slash = '\0';

	}
	else
	{
		*uri = strdup("/");
	}
	p_colon = strchr(start, ':');
	if (p_colon != nullptr)
	{
		*port = atoi(p_colon + 1);
		*p_colon = '\0';
	}

	*host = strdup(start);

	if (url_dup != nullptr)
	{
		free(url_dup);
		url_dup = nullptr;
	}
}

int main()
{
	string str = "http://360.net:80/hello/out.html";
	uint32_t port = 0;
	if (GetPortFromUrl(str, port))
	{
		//cout << "success, port=" << port << endl;
	}

	char* host = nullptr;
	char* uri = nullptr;
	unsigned int port1 = 0;
	MyParseURL2(str.c_str(), &host, &port1, &uri, 0);

	cout << "NetDrvCallBack strMacth url=" << str.c_str() << " host=" << host << " uri=" << uri << " port=" << port1 << endl;
	return 0;
}
#endif