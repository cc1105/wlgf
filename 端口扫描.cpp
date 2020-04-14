#include <winsock2.h> 
#include <windef.h>
#include <iostream> 
#include <vector>
#pragma comment(lib,"ws2_32")

using namespace std;


typedef unsigned int uint;
vector<uint> v;



int 
main() 
{ 
 WORD wsVersion = MAKEWORD(2,0); //socket的版本 
 WSADATA wsaData;    //这个结构被用来存储被WSAStartup函数调用后返回的Windows Sockets数据。它包含Winsock.dll 执行的数据。 
 struct sockaddr_in sin;   //sockaddr_in结构,表示socket address and internet style
 uint BeginPort;     //开始端口 
 uint EndPort;     //结束端口 
 uint CurrentPort;    //正在扫描的端口 
 uint i=0;

 char HostName[256];    //要扫描的主机 


 SOCKET s;      //保存创建socket时的返回值 /////////////////////////
 ////////////////////创建一个套接口。 　　#include <winsock.h> SOCKET PASCAL FAR socket( int af, int type, int protocol);
 //af：一个地址描述。目前仅支持AF_INET格式，也就是说ARPA Internet地址格式type：新套接口的类型描述。
 //protocol：套接口所用的协议。如调用者不想指定，可用0。 

 ///////该函数如果调用成功就返回新创建的套接字的描述符


 int OpenPort;     //开放端口个数 
 OpenPort = 0;


 cout<<"Please input the HostName:";
 cin>>HostName;
 cout<<"Input the Begin Port:";
 cin>>BeginPort;
 cout<<"Input the End port:";
 cin>>EndPort;

 //对用户输入的端口进行判断 
 while((BeginPort > EndPort || BeginPort < 0 || BeginPort >65535 || EndPort <0 || EndPort >65535))
 { 
	  cout<<"You have input some wrong paramters.Try again."<<endl;
	  cout<<"Please input the HostName:";
	  cin>>HostName;
	  cout<<"Input the Begin Port:";
	  cin>>BeginPort;
	  cout<<"Input the End port:";
	  cin>>EndPort;
 }

 if(WSAStartup(wsVersion,&wsaData)) 
 { 
	cout<<"Initial Failed!"<<endl;  return -1;
 } 
 cout<<endl<<"Now Scan "<<HostName<<"'s Specified Ports Status."<<endl<<endl;

 //循环判断范围内的端口，以判断端口是否开放 ，并记录结果
 for(CurrentPort=BeginPort; CurrentPort<=EndPort;++CurrentPort) 
 { 
    s = socket(AF_INET,SOCK_STREAM,0); //s用来记录socket的返回值。
    if(s == INVALID_SOCKET) 
    { 
   cout<<"Establish Socket Failed."<<endl;  WSACleanup();   
    } 
  
    //给结构成员赋值 
    sin.sin_family = AF_INET;//可能是硬件地址。。
    sin.sin_port = htons(CurrentPort); //当前扫描的端口号
    sin.sin_addr.S_un.S_addr = inet_addr(HostName); //输入ip地址用的
    //建立连结 



    if(connect(s,(struct sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR) 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Not open."<<endl;
		 closesocket(s);//连接失败
    } 
    else 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Opened."<<endl;
		 OpenPort ++;  
		 v.push_back(CurrentPort);//用于数值的自动增加 vector（uint） v
		 closesocket(s); 
    }   
  }

  cout<<endl<<"Resaults: Host "<<HostName<<" has opened "<<OpenPort<<" port.Opened port as follow:"<<endl; 
 cout<<"===================================================================="<<endl;
  for(i=0;i<v.size();++i)
  {
  cout<<v.at(i)<<" ";
  if((i+1)%10==0)cout<<endl;
  }
  cout<<endl;
  cout<<"===================================================================="<<endl;
  closesocket(s);
     WSACleanup();

  return 0; 
}
                         

