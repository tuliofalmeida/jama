#include "SistemasdeControle/headers/communicationLibs/opc/OPCClient.h"

OPCClient::OPCClient()
{
	StartCOM();
}

OPCClient::~OPCClient()
{
	AbortCOM();
}

void OPCClient::StartCOM()
{
	CoInitialize(0);
}

void OPCClient::AbortCOM()
{
	CoUninitialize();
}

void OPCClient::GetCLSID()
{
	CLSIDFromProgID(this->ServerName, &this->CLSIDServer);
}

void OPCClient::CreateInstance()
{
	CoCreateInstance(this->CLSIDServer, NULL, CLSCTX_LOCAL_SERVER, IID_IOPCServer, (void**) &this->ServerConnected);
}

void OPCClient::OPCConnect(_bstr_t ServerName)
{
	this->ServerName = ServerName;
	GetCLSID();
	CreateInstance();
	StartGroup();
}

void OPCClient::StartGroup()
{
	OPCHANDLE clientHandle = 1;
	DWORD DefaultUpdTime = 5000, RevisedUpdTime, LanguageCode = 0x416;
	IOPCItemMgt *Item = NULL;
	OPCHANDLE GroupHandle = NULL;
	
	this->ServerConnected->AddGroup(L"",
						  FALSE,
						  DefaultUpdTime,
						  clientHandle,
						  NULL,
						  NULL,
						  LanguageCode,
						  &this->OPCGroup,
						  &RevisedUpdTime,
						  IID_IOPCItemMgt,
						  (LPUNKNOWN*) &this->TypeReadItem);
	this->TypeReadItem->QueryInterface(IID_IOPCSyncIO, (void**)&this->TypeReadSync);
}

void OPCClient::InsertItens(_bstr_t tags[], int QtdTags)
{
	OPCITEMDEF *TagDef = new OPCITEMDEF[QtdTags];
	OPCITEMRESULT *AddResult = NULL;
	HRESULT *Errors = NULL;

	this->QtdTags = QtdTags;
	this->TagValues = new _variant_t[QtdTags];
	this->TagNames = new _bstr_t[QtdTags];
	
	for(int i = 0; i < this->QtdTags; i++)
		this->TagNames[i] = tags[i];

	for (int i = 0; i < this->QtdTags; i++)
	{
		TagDef[i].szAccessPath = _bstr_t("");
		TagDef[i].szItemID = tags[i];
		TagDef[i].bActive = FALSE;
		TagDef[i].hClient = 1;
		TagDef[i].dwBlobSize = 0;
		TagDef[i].pBlob = NULL;
		TagDef[i].vtRequestedDataType = 0;
	}
	this->TypeReadItem->AddItems(this->QtdTags, TagDef, &AddResult, &Errors);
	this->OPCGroupTag = new OPCHANDLE[this->QtdTags];
	for (int i = 0; i < this->QtdTags; i++)
		this->OPCGroupTag[i] = AddResult[i].hServer;

	if(Errors != NULL)
		CoTaskMemFree(Errors);
	if(TagDef != NULL)
		delete [] TagDef;
}

_variant_t *OPCClient::ReadItens()
{	
	HRESULT *Errors = NULL;
	OPCITEMSTATE *Values = NULL;	

	this->TypeReadSync->Read(OPC_DS_DEVICE, this->QtdTags, this->OPCGroupTag, &Values, &Errors);
	for (int i = 0; i < this->QtdTags; i++)
		this->TagValues[i] = Values[i].vDataValue;
	for (int i = 0; i < this->QtdTags; i++)
		VariantClear(&Values[i].vDataValue);
	if (Values != NULL)
		CoTaskMemFree(Values);
	if (Errors != NULL)
		CoTaskMemFree(Errors);
	
	return this->TagValues;
}

void OPCClient::WriteItens(int TagIndex[], _variant_t Values[], int QtdValues)
{
	using namespace std;
		
	HRESULT *Errors = NULL;
	OPCHANDLE *Items = new OPCHANDLE[QtdValues];	

	for (int i = 0; i < QtdValues; i++)
		Items[i] = this->OPCGroupTag[TagIndex[i]];
	this->TypeReadSync->Write(QtdValues, Items, Values, &Errors);
		
	if (Errors != NULL)
		CoTaskMemFree(Errors);
	if (Items != NULL)
		delete [] Items;
}

void OPCClient::Show(int ShowTime)
{
	using namespace std;

		for(int i=0;i < ShowTime;i++)
		{
			ReadItens();
			cout<<"##################\n";
			for(int i = 0; i < this->QtdTags; i++)
				{			
					cout<<"# "<<this->TagNames[i]<<"| ";
					printf("%6.0f", this->TagValues[i].dblVal);
					cout<<" #\n";
				}
			cout<<"##################\n";
			cout<<"\n";
			Sleep(1000);
		}	
}

