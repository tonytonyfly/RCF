/*
发布，可发布多个主题，唯一要求是，订阅方能发起网络连接，发布方从不与订阅方发起连接
RcfServer::createPublisher<>();
*/

#include <iostream>
using namespace std;

#include <RCF/RCF.hpp>

RCF_BEGIN(I_HelloWorld, "I_HelloWorld")
	RCF_METHOD_R1(int, Print, const string &)
RCF_END(I_HelloWorld)

//class HelloWorld
//{
//public:
//	int Print(const string &s)
//	{
//		cout << s << endl;
//		return s.size();
//	}
//};

int main()
{
	RCF::init();
	try
	{
		RCF::RcfServer pubServer(RCF::TcpEndpoint(50001));
		pubServer.start();
		typedef boost::shared_ptr<RCF::Publisher<I_HelloWorld> > HelloWorldPubPtr;
		// 创建默认名称的Publisher(运行时标示"I_HelloWorld"
		HelloWorldPubPtr pubPtr = pubServer.createPublisher<I_HelloWorld>();
		// 手动设置主题名
		RCF::PublisherParms pubParms;
		pubParms.setTopicName("HelloWorld_Topic_1");
		HelloWorldPubPtr pub1Ptr = pubServer.createPublisher<I_HelloWorld>(pubParms);

		while (true)
		{
			RCF::sleepMs(1000);
			pubPtr->publish().Print("HelloWorld"); // OneWay方式
		}
		// 关闭
		pub1Ptr->close();
		pubPtr->close();
	}
	catch (RCF::Exception &e)
	{
		cout << e.getErrorString() << endl;
	}

	cout << "任意键退出..." << endl;
	cin.get();



	return 0;
}