#if 0
// string ���ʵ��
#include <iostream>
#include <cstring>

using namespace std;

class String
{
public:
	String(const char*);
	String(const String& ref);
	String& operator = (const String& other);
	String& operator += (const String& left);
	int operator < (const String& left);
	void Print();
	~String();

private:
	char* m_data;
};

String::String(const char* str)
{
	if (NULL == str)
	{
		m_data = new char[1];
		m_data[0] = '\0';
	}
	else
	{
		m_data = new char[strlen(str) + 1];
		strncpy(m_data, str, strlen(str) + 1);
	}
}

String::~String()
{
	if (m_data != NULL)
	{
		delete[] m_data;
		m_data == NULL;
	}
}

void String::Print()
{
	cout << m_data << endl;
}

String::String(const String& ref)
{
	m_data = new char[strlen(ref.m_data) + 1];
	strncpy(m_data, ref.m_data, strlen(ref.m_data) + 1);
}

String& String::operator = (const String& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_data != NULL)
		delete[] m_data;

	m_data = new char[strlen(other.m_data) + 1];
	strcpy_s(m_data, strlen(other.m_data) + 1, other.m_data);
	return *this;
}

String& String::operator += (const String& left)
{
	char* data = m_data;
	m_data = new char[strlen(m_data) + strlen(left.m_data) + 1];
	memset(m_data, 0, sizeof(m_data));
	strcpy_s(m_data, strlen(data) + 1, data);
	strcat_s(m_data, strlen(m_data) + strlen(left.m_data) + 1, left.m_data);
	return *this;
}

int String::operator < (const String& left)
{
	return strcmp(m_data, left.m_data);
}

int main()
{
	String s("asdfadf");
	//s += String("    asdadasdasdas");
	//cout << (s < String("asd")) << endl;
	String ss("zxczczx");
	s = ss;
	s.Print();

	return 0;
}

#endif

#if 0
// ʵ��strcpy����
#include <iostream>
#include <cassert>
using namespace std;

char* strcpy(char* strDest, const char* strSrc)
{
	assert((strDest != NULL) && (strSrc != NULL)); // 2��
	char* address = strDest; // 2��
	while ((*strDest++ = *strSrc++) != '\0') // 2��
		NULL;
	return address; // 2��
}

void* my_memcpy(void* dst, const void* src, unsigned int count)
{
	assert(dst);
	assert(src);
	void* ret = dst;
	if (dst <= src || (char*)dst >= ((char*)src + count))//Դ��ַ��Ŀ�ĵ�ַ���ص������ֽ�����ֽڿ���  
	{
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else                       //Դ��ַ��Ŀ�ĵ�ַ�ص������ֽ�����ֽڿ���  
	{
		dst = (char*)dst + count - 1;
		src = (char*)src + count - 1;
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return ret;
}

int main()
{
	return 0;
}
#endif

#if 0
#include <iostream>
using namespace std;

// KMP
int main()
{
	return 0;
}
#endif

