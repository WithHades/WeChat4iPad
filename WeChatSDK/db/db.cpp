#include "stdafx.h"
#include "db.h"


static CStringA Utc2BeijingTime(DWORD dwUtc)
{
	CStringA strTime;

	time_t utc = dwUtc;
	struct tm *tmdate = localtime(&utc);

	strTime.Format("%d-%02d-%02d %02d:%02d:%02d",
		tmdate->tm_year + 1900, tmdate->tm_mon + 1, tmdate->tm_mday, tmdate->tm_hour, tmdate->tm_min, tmdate->tm_sec);

	return strTime;
}


CMicroChatDB *CMicroChatDB::m_Instance = NULL;
CMicroChatDB * CMicroChatDB::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = new CMicroChatDB;
	}

	return m_Instance;
}


int CMicroChatDB::CreateTable()
{
	int ret = SQLITE_OK;

	//同步key表
	CStringA str = "create table synckey(key varchar(4096));";

	ret = ExecSQL(str);
	if (SQLITE_OK != ret)
	{
		printf("[CSynckeyDB::CreateTable]synckey建表失败!");
	}

	//好友列表
	str = "create table contact(wxid varchar(1024),nickname varchar(1024),headicon varchar(1024),v1_name varchar(1024));";

	ret = ExecSQL(str);
	if (SQLITE_OK != ret)
	{
		printf("[CSynckeyDB::CreateTable]contact建表失败!");
	}

	//历史消息记录表
	str = "create table msg(svrid bigint,utc integer,createtime varchar(1024),fromWxid varchar(1024),toWxid varchar(1024),type integer,content text(65535));";

	ret = ExecSQL(str);
	if (SQLITE_OK != ret)
	{
		printf("[CSynckeyDB::CreateTable]msg建表失败!");
	}

	return SQLITE_OK;
}

void CMicroChatDB::ClearDB()
{
	CStringA strSql;
	strSql.Format("delete from msg;");
	ExecSQL(strSql,NULL,NULL);

	strSql.Format("delete from contact;");
	ExecSQL(strSql, NULL, NULL);

	strSql.Format("delete from synckey;");
	ExecSQL(strSql, NULL, NULL);
}

string CMicroChatDB::GetSyncKey()
{
	char szSyncKey[4096] = { 0 };

	CString strSql;
	strSql.Format(L"select * from synckey;");
	ExecSQL(CW2UTF8(strSql), &CMicroChatDB::GetSyncKeyCallBack, szSyncKey);

	return string(szSyncKey,strlen(szSyncKey));
}

void CMicroChatDB::UpdateSyncKey(string strSyncKey)
{
	//清空表
	CString strSql;
	strSql.Format(L"delete from synckey;");
	ExecSQL(CW2UTF8(strSql), NULL, NULL);

	//插入记录
	strSql.Format(L"insert into synckey(key) values('%s');", CA2W(strSyncKey.c_str()).m_psz);
	ExecSQL(CW2UTF8(strSql), NULL, NULL);
}



int CMicroChatDB::GetSyncKeyCallBack(void *lpUserArg, int argc, char **argv, char **lpszValue)
{
	//字段数量不符,放弃解析该任务
	if (DB_INDEX_RECORD_CNT != argc)		return SQLITE_OK;
	
	//TODO:没做异常处理
	strcpy((char *)lpUserArg, argv[DB_INDEX_SYNCKEY_KEY]);

	return 0;
}

