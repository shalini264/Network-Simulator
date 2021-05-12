#include<bits/stdc++.h>
using namespace std;
class endDevice
{
    public:string ip_addr;
           string mac;
           string add;
           int port;
};
class Switch{
 public:   int ports;
           vector< pair< int,string > >vec;
           endDevice e1[5];
           Switch(int p)
           {
               ports=p;

           }
           void GoBackN();
           void StopNWait();
           void getInput();

};
void Switch::getInput()
{
    for(int i=0;i<5;i++)
    {
        cout<<"Enter info for "<<(i+1)<<" end devices\n";
        cin>>e1[i].ip_addr>>e1[i].mac>>e1[i].port;
    }
}
void Switch::StopNWait()
{
   int nf,N;
 int no_tr=0;
 srand(time(NULL));
 cout<<"Enter the number of frames : ";
 cin>>nf;
 N=1;
 int i=1;
 while(i<=nf)
 {
     int x=0;
     for(int j=i;j<i+N && j<=nf;j++)
     {
         cout<<"Sent Frame "<<j<<endl;
         no_tr++;
     }
     for(int j=i;j<i+N && j<=nf;j++)
     {
         int flag = rand()%2;
         if(!flag)
             {
                 cout<<"Acknowledgment for Frame "<<j<<endl;
                 x++;
             }
         else
             {   cout<<"Frame "<<j<<" Not Received"<<endl;
                 cout<<"Retransmitting Window"<<endl;
                 break;
             }
     }
     cout<<endl;
     i+=x;
 }
 cout<<"Total number of transmissions : "<<no_tr<<endl;
}
void Switch::GoBackN()
{
    int nf,N;
 int no_tr=0;
 srand(time(NULL));
 cout<<"Enter the number of frames : ";
 cin>>nf;
 cout<<"Enter the Window Size : ";
 cin>>N;
 int i=1;
 while(i<=nf)
 {
     int x=0;
     for(int j=i;j<i+N && j<=nf;j++)
     {
         cout<<"Sent Frame "<<j<<endl;
         no_tr++;
     }
     for(int j=i;j<i+N && j<=nf;j++)
     {
         int flag = rand()%2;
         if(!flag)
             {
                 cout<<"Acknowledgment for Frame "<<j<<endl;
                 x++;
             }
         else
             {   cout<<"Frame "<<j<<" Not Received"<<endl;
                 cout<<"Retransmitting Window"<<endl;
                 break;
             }
     }
     cout<<endl;
     i+=x;
 }
 cout<<"Total number of transmissions : "<<no_tr<<endl;
}
class Hub{
public:
    int num;
    int ports=4;
    endDevice e1[5];
    Hub(int no)
    {
        num=no;
    }
    void getData(int n);
};
void Hub::getData(int n)
{   for(int i=0;i<n;i++)
    {cout<<"Enter info for device"<<(i+1)<<"\n";
    cin>>e1[i].ip_addr>>e1[i].mac>>e1[i].port;}
}
class Bridge{
public:
    int num;
    int ports=4;
    endDevice e1[2];
    Bridge(int no)
    {
        num=no;
    }
    void getData(int n);
};
void Bridge::getData(int n)
{   for(int i=0;i<n;i++)
    {cout<<"Enter info for device"<<(i+1)<<"\n";
    cin>>e1[i].ip_addr>>e1[i].mac>>e1[i].port;}
}

void create_table(vector< pair<int, string> >&vec,Hub h1,Hub h2,int n)
{
    for(int i=0;i<n;i++)
    {
        vec.push_back({1,h1.e1[i].mac});
       // cout<<h1.e1[i].mac<<"\n";
    }
    for(int i=0;i<n;i++)
    {
       vec.push_back({2,h2.e1[i].mac});
      // cout<<h2.e1[i].mac<<"\n";
    }
   for(int i=0;i<vec.size();i++)
    cout<<vec[i].first<<"    |   "<<vec[i].second<<"\n";
}
void create_table(vector< pair<int, string> >&vec,Switch s)
{
    for(int i=0;i<5;i++)
    {
        vec.push_back({s.e1[i].port,s.e1[i].mac});
    }
    for(int i=0;i<vec.size();i++)
    cout<<vec[i].first<<"    |   "<<vec[i].second<<"\n";
}
class destination{
    public:string mac;
           string msg;
           destination(string mc,string msg1)
           {mac = mc;
            msg=msg1;
           }
};
void Recieve(destination dest,endDevice e1,Hub h,int n)
{cout<<"{"<<dest.msg<<"}is broadcasted to every station through Hub "<<h.num<<"\n";
for(int i=0;i<n;i++)
{
    if(h.e1[i].mac==dest.mac)
    {   cout<<h.e1[i].mac<<" received the packet.Thats the destination. {";
        cout<<dest.msg<<"} recieved by:"<<dest.mac<<"\n";
        if(dest.msg!="ACK")
        cout<<"\nAck sent to:"<<e1.mac<<" by "<<dest.mac<<"\n";

    }
    else if(h.e1[i].mac!=e1.mac)
    {
        cout<<h.e1[i].mac<<" received the packet.Not the destination,packet dropped\n";
    }
}
}
void RecieveF(destination d,endDevice e1,Hub h,Hub h1,Switch s)
{
    cout<<"Switch will check table to which port it should send{"<<d.msg<<"}\n";
    if(s.vec.size()==0)
    {
        cout<<"Table is empty!\n Switch will broadcast {"<<d.msg<<"}to port 1 and port 2\n";
        Recieve(d,e1,h,3);
        Recieve(d,e1,h1,3);
    }
    else
    {for(int i=0;i<s.vec.size();i++)
    {
        if(s.vec[i].second==d.mac)
        {
            cout<<"so port:"<<s.vec[i].first<<" have desired end device\n";
            if(s.vec[i].first==1)
                Recieve(d,e1,h,3);
            else
                Recieve(d,e1,h1,3);
        }
    }}
}
void send(Hub h,Switch s,Hub h1,int n)
{
    cout<<h.e1[2].mac<<"wants to send message {Hello,there!} to"<<h.e1[0].mac<<"\n";
    destination d1(h.e1[0].mac,"Hello,there!");
    Recieve(d1,h.e1[2],h,n);
    cout<<"{"<<d1.msg<<"} forwarded to switch\n";
    RecieveF(d1,h.e1[2],h,h1,s);
    create_table(s.vec,h,h1,n);
    cout<<"Table created!\n";
    cout<<"Ack transmission:\n";
    d1.msg="ACK";
    d1.mac=h.e1[2].mac;
    Recieve(d1,h.e1[0],h,n);
    cout<<"{"<<d1.msg<<"} forwarded to switch\n";
    RecieveF(d1,h.e1[0],h,h1,s);
    cout<<h.e1[2].mac<<"wants to send message {1001010} to"<<h1.e1[2].mac<<"\n";
    destination d2(h1.e1[2].mac,"1001010");
    Recieve(d2,h.e1[2],h,n);
    cout<<"{"<<d2.msg<<"} forwarded to switch\n";
    RecieveF(d2,h.e1[2],h,h1,s);
    cout<<"Ack transmission:\n";
    d2.msg="ACK";
    d2.mac=h.e1[2].mac;
    Recieve(d2,h1.e1[2],h1,n);
    cout<<"{"<<d2.msg<<"} forwarded to switch\n";
    RecieveF(d2,h1.e1[2],h,h1,s);
}
void dedicatedLink()
{   cout<<"Dedicated link communication:\n";
    endDevice e11,e12;
    e11.add="EndDev1";
    e12.add="EndDev2";
    cout<<e11.add<<" is connected to "<<e12.add<<" via dedicated link\n";
    cout<<"Message sent on dedicated link by "<<e11.add<<" and received by "<<e12.add<<"\n";
    //cout<<"Ack sent on dedicated link by "<<e12.add<<" and recieved by "<<e11.add<<"\n";
}
void hub()
{cout<<"Single HUB communication:\n";
Hub h3(1);
h3.getData(5);
destination d1(h3.e1[0].mac,"1001");
cout<<h3.e1[1].mac<<" wants to send {"<<d1.msg<<"} to "<<h3.e1[0].mac<<"\n";
Recieve(d1,h3.e1[1],h3,5);
d1.msg="ACK";
d1.mac=h3.e1[1].mac;
cout<<"Ack transmission:\n";
Recieve(d1,h3.e1[0],h3,5);
}
void RecieveB(destination dest,endDevice e1,Bridge h,int n)
{cout<<"{"<<dest.msg<<"}is broadcasted to every station through Hub "<<h.num<<"\n";
for(int i=0;i<n;i++)
{
    if(h.e1[i].mac==dest.mac)
    {   cout<<h.e1[i].mac<<" received the packet.Thats the destination. {";
        cout<<dest.msg<<"} recieved by:"<<dest.mac<<"\n";
        if(dest.msg!="ACK")
        cout<<"\nAck sent to:"<<e1.mac<<" by "<<dest.mac<<"\n";

    }
    else if(h.e1[i].mac!=e1.mac)
    {
        cout<<h.e1[i].mac<<" received the packet.Not the destination,packet dropped\n";
    }
}
}
void bridge()
{cout<<"Single BRIDGE communication:\n";
Bridge h3(1);
h3.getData(2);
destination d1(h3.e1[0].mac,"1001");
cout<<h3.e1[1].mac<<" wants to send {"<<d1.msg<<"} to "<<h3.e1[0].mac<<"\n";
RecieveB(d1,h3.e1[1],h3,2);
d1.msg="ACK";
d1.mac=h3.e1[1].mac;
cout<<"Ack transmission:\n";
RecieveB(d1,h3.e1[0],h3,2);
}
void SendM(destination d,endDevice e1,Switch s)
{
    for(int i=0;i<5;i++)
{
    if(s.e1[i].mac==d.mac)
    {   cout<<s.e1[i].mac<<" received the packet.Thats the destination. {";
        cout<<d.msg<<"} recieved by:"<<d.mac<<"\n";
        if(d.msg!="ACK")
        cout<<"\nAck sent to:"<<e1.mac<<" by "<<d.mac<<"\n";

    }
    else if(s.e1[i].mac!=e1.mac)
    {
        cout<<s.e1[i].mac<<" received the packet.Not the destination,packet dropped\n";
    }
}
}
void RecieveSOnly(destination d,endDevice e,Switch s)
{
    if(s.vec.size()==0)
    {
        cout<<"Table is empty!Message broadcasted to all end devices\n";
        SendM(d,e,s);

    }
    else
    {
        for(int i=0;i<5;i++)
        {
            if(s.vec[i].second==d.mac)
            {
                cout<<"So,the destination port is "<<s.vec[i].first<<"\n";
                cout<<"{"<<d.msg<<"} recieved by "<<d.mac<<"\n";
                if(d.msg!="Ack")
                {
                    cout<<"Ack sent back to:"<<e.mac<<"\n";
                }
            }
        }
    }
}
void SwitchA()
{    cout<<"Switch with 5 end devices\n";
    Switch s(5);
    s.getInput();
    destination d(s.e1[0].mac,"100101");
    cout<<s.e1[3].mac<<" wants to send {"<<d.msg<<"}to "<<s.e1[0].mac<<"\n";
    RecieveSOnly(d,s.e1[3],s);
    create_table(s.vec,s);
        cout<<"Table created!\n";
    d.msg="ACK";
    d.mac=s.e1[3].mac;
    RecieveSOnly(d,s.e1[0],s);
    cout<<"Collision domain:5\nBroadcast Domain:1\n";
}
void FirstFunc()
{ cout<<"Switch with two hubs each connected to 3 end devices:\n";
    Switch s1(2);
  Hub h1(1),h2(2);
  h1.getData(3);
  h2.getData(3);
  send(h1,s1,h2,3);
}
void lastFunc()
{  cout<<"Switch with two hubs each connected to 5 end devices:\n";
    Switch s(2);
    Hub h1(1),h2(2);
    h1.getData(5);
    h2.getData(5);
    send(h1,s,h2,5);
    cout<<"Collision domain:4\n Broadcast Domain:3\n";
}
void demoAccess()
{
    Switch s1(2);
    char ch;
    cout<<"WHAT YOU WANT US TO DEMONSTRATE 1.STOP N WAIT 2.GO BACK N:";
    cin>>ch;
    if(ch=='1')
         s1.StopNWait();
    else if(ch=='2')
         s1.GoBackN();
    else
         cout<<"Wrong choice!";
}

struct station{
    string data;
    int dest;
    int st_no;
};
map<int,vector<int> >mp;
void slotted_aloha()
{  cout<<"     ==========Slotted ALOHA============      \n";
station s[6];
char ch;
vector<int>visited(6,0);
int t[6]={0};
    for(int i=1;i<=5;i++)
    {int time_;

        cout<<"Station "<<i<<" wants to send data?y:n   |";
        cin>>ch;
        if(ch=='y')
        {

            cout<<"Enter data:";
            cin>>s[i].data;
            cout<<"Enter destination station id [1,5]:";
            cin>>s[i].dest;
            cout<<"At what time interval beginning?Interval is of 5 seconds:";
            cin>>time_;
            mp[time_].push_back(i);
            s[i].st_no=i;
        }
        else
            visited[i]=1;
    }
    int j=0;
    srand(time(NULL));
    for(int i=5;;i+=5)
    {
        if(mp[i].size()!=0)
        {
            if(mp[i].size()>1)
            {
                cout<<"-------------Collision occurred at "<<i<<"th interval\nResend after some time\n";
                for(int k=0;k<mp[i].size();k++)
                {   if(t[mp[i][k]]>5)
                    {cout<<"Reached kmax!drop "<<mp[i][k]<<"th message!\n";
                    visited[mp[i][k]]=1;
                    continue;}
                    else
                    t[mp[i][k]]++;
                    int u=5+rand()%10;
                    if(u%5!=0)
                         u=u-(u%5);
                    mp[u+i].push_back(mp[i][k]);
                }
            }
            else
            {
                cout<<s[mp[i][0]].data<<"received successfully by "<<s[mp[i][0]].dest<<" at "<<i<<"th interval"<<"\n";
                visited[mp[i][0]]=1;
            }
        }
      if(count(visited.begin(),visited.end(),1)==5)
        break;
    }

}
int main()
{
    bridge();
  dedicatedLink();
  hub();
  FirstFunc();
  SwitchA();
  lastFunc();
  demoAccess();
  slotted_aloha();
}
