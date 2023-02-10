#pragma once
class ClientDataListener
{
public:
	virtual void onData(unsigned char* data, int lnt) {};
	virtual void onCommandData(unsigned char* data, int lnt) {};
};