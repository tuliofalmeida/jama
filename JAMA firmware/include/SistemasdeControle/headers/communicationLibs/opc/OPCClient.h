#ifndef OPCCLIENT_H
#define OPCCLIENT_H

#include "Opcda.h"
#include "opccomn.h"
#include "OpcEnum.h"
#include <comdef.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>


class OPCClient
{
private:
	_bstr_t ServerName, *TagNames;
	CLSID CLSIDServer;
	IOPCServer *ServerConnected;
	OPCHANDLE OPCGroup, *OPCGroupTag;
	IOPCItemMgt *TypeReadItem;
	IOPCSyncIO *TypeReadSync;
	_variant_t *TagValues;
	
	int QtdTags;

	void StartCOM(); //inicia a com
	void AbortCOM(); // fecha com
	void CreateInstance();//acesso o especo de memoria reservado para o servidor 
	void GetCLSID(); // pega o id do servidor no registro
	void StartGroup();
	
public:
	OPCClient();
	OPCClient(_bstr_t ServerName);
	~OPCClient();

	void OPCConnect(_bstr_t ServerName);
	void InsertItens(_bstr_t tags[], int QtdTags);
	void WriteItens(int TagIndex[], _variant_t Values[], int QtdValues);
	void Show(int ShowTime);
	
	
	_variant_t *ReadItens();

};

#endif //OPCCLIENT_H