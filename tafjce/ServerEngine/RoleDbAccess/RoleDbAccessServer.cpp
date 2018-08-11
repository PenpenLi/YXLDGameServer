#include "RoleDbAccessServer.h"
#include "RoleDbAccessImp.h"
#include "DalRole.h"

using namespace ServerEngine;

RoleDbAccessServer g_app;

void RoleDbAccessServer::initialize()
{
    //��ʼ��servant
	addServant<RoleDbAccessImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DbAccessObj");

    //��ʼ��DB pool
    TC_Config conf;
	//conf.parseFile(ServerConfig::BasePath + ServerConfig::ServerName + ".conf");
	conf.parseFile(ServerConfig::ServerName + ".conf");
	DbPool<DefaultRoleDb>::getInstance()->init(conf);
    
    //�ϱ���ʼ���¼�
    TAF_NOTIFY_NORMAL("initialize");
    RLOG << "Server::initialize ok" << endl;
}

void RoleDbAccessServer::destroyApp()
{
	// nothing
}


int
main(int argc, char* argv[])
{
	try
	{
		g_app.main(argc, argv);
		g_app.waitForShutdown();
	}
	catch (std::exception& e)
	{
		cerr << "std::exception:" << e.what() << std::endl;
	}
	catch (...)
	{
		cerr << "unknown exception." << std::endl;
	}
	return -1;
}
