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
 WORD wsVersion = MAKEWORD(2,0); //socket�İ汾 
 WSADATA wsaData;    //����ṹ�������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�������Winsock.dll ִ�е����ݡ� 
 struct sockaddr_in sin;   //sockaddr_in�ṹ,��ʾsocket address and internet style
 uint BeginPort;     //��ʼ�˿� 
 uint EndPort;     //�����˿� 
 uint CurrentPort;    //����ɨ��Ķ˿� 
 uint i=0;

 char HostName[256];    //Ҫɨ������� 


 SOCKET s;      //���洴��socketʱ�ķ���ֵ /////////////////////////
 ////////////////////����һ���׽ӿڡ� ����#include <winsock.h> SOCKET PASCAL FAR socket( int af, int type, int protocol);
 //af��һ����ַ������Ŀǰ��֧��AF_INET��ʽ��Ҳ����˵ARPA Internet��ַ��ʽtype�����׽ӿڵ�����������
 //protocol���׽ӿ����õ�Э�顣������߲���ָ��������0�� 

 ///////�ú���������óɹ��ͷ����´������׽��ֵ�������


 int OpenPort;     //���Ŷ˿ڸ��� 
 OpenPort = 0;


 cout<<"Please input the HostName:";
 cin>>HostName;
 cout<<"Input the Begin Port:";
 cin>>BeginPort;
 cout<<"Input the End port:";
 cin>>EndPort;

 //���û�����Ķ˿ڽ����ж� 
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

 //ѭ���жϷ�Χ�ڵĶ˿ڣ����ж϶˿��Ƿ񿪷� ������¼���
 for(CurrentPort=BeginPort; CurrentPort<=EndPort;++CurrentPort) 
 { 
    s = socket(AF_INET,SOCK_STREAM,0); //s������¼socket�ķ���ֵ��
    if(s == INVALID_SOCKET) 
    { 
   cout<<"Establish Socket Failed."<<endl;  WSACleanup();   
    } 
  
    //���ṹ��Ա��ֵ 
    sin.sin_family = AF_INET;//������Ӳ����ַ����
    sin.sin_port = htons(CurrentPort); //��ǰɨ��Ķ˿ں�
    sin.sin_addr.S_un.S_addr = inet_addr(HostName); //����ip��ַ�õ�
    //�������� 



    if(connect(s,(struct sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR) 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Not open."<<endl;
		 closesocket(s);//����ʧ��
    } 
    else 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Opened."<<endl;
		 OpenPort ++;  
		 v.push_back(CurrentPort);//������ֵ���Զ����� vector��uint�� v
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
                         

