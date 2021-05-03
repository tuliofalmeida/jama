#include <iostream>
//#include <string.h>
//#include <stdlib.h>
#include <Windows.h>
#include "SistemasdeControle/headers/communicationLibs/serial/comunicacao.h"
//#include <math.h>


Serial::Serial()
{

}

void Serial::setIdCom(const char *namedoor)
{
    WCHAR    str3[5];
    MultiByteToWideChar( 0,0, namedoor, 5, str3, 5);
    IdCom = str3;
}

Serial::Serial(const char *namedoor)
{
    this->setIdCom(namedoor);
	this->dcbPortaSerialparams = {0};
	this->timeouts = {0};
    this->PortaSerial = CreateFile(this->IdCom,
        GENERIC_READ|GENERIC_WRITE,     //para leitura e escrita
	  	0,							//outra abertura n�o ser� permitida
	   	NULL,						//atributo de seguranca(null)padr�o
	    OPEN_EXISTING, 				//cria��o ou abertura
		FILE_ATTRIBUTE_NORMAL, 		//ouverlapped
		NULL );
	
this->dcbPortaSerialparams.DCBlength = sizeof(this->dcbPortaSerialparams); 
    if (GetCommState(this->PortaSerial, &this->dcbPortaSerialparams) == 0)
    {
        fprintf(stderr, "Error de estado de dispositivo\n");
        CloseHandle(this->PortaSerial);
    }
     
    this->dcbPortaSerialparams.BaudRate = CBR_4800;		   //velocidade
    this->dcbPortaSerialparams.ByteSize = 8;			   //tamanho do dado
    this->dcbPortaSerialparams.StopBits = ONESTOPBIT;	   //bits de parada
    this->dcbPortaSerialparams.Parity =  NOPARITY;		   //paridde
    this->dcbPortaSerialparams.fDtrControl = DTR_CONTROL_DISABLE;
    if(SetCommState(this->PortaSerial, &this->dcbPortaSerialparams) == 0)
    {
        fprintf(stderr, "Parametro de dispositivo errado\n");
        CloseHandle(this->PortaSerial);
    }
    this->timeouts.ReadIntervalTimeout = 50;
    this->timeouts.ReadTotalTimeoutConstant = 50;
    this->timeouts.ReadTotalTimeoutMultiplier = 10;
    this->timeouts.WriteTotalTimeoutConstant = 50;
    this->timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(this->PortaSerial, &this->timeouts) == 0)
    {
        fprintf(stderr, "timeout configurado errado\n");
        CloseHandle(this->PortaSerial);
    }
}

void Serial::Close()
{
	fprintf(stderr, "\nFechando porta serial...");
    if (CloseHandle(this->PortaSerial) == 0)
    {
        fprintf(stderr, "Error\n");        
    }
    fprintf(stderr, "OK\n");
}

void Serial::Write(const char *teste)
{ 	
    int  i = 0, m = 0; //n =0;
	 m = strlen(teste);
	
	 for (i=0 ; i != m ; i++)
	  {
	      bytes_pra_envio[i]=teste[i];
      }
   int tamanho = m;

    DWORD bytes_written;//, total_bytes_written = 0;
   // fprintf(stderr, "Enviando bytes...");
    if(!WriteFile(this->PortaSerial,		//identificador da porta serial
				  this->bytes_pra_envio,	//buffer onde ser� depositado para serem enviados a porta serial
				  tamanho,					//tamanho do buffer de dados
				  &bytes_written,	        //ponteiro onde armazena a quantidade exata de bytes escritos
				  NULL))				    //ponteiro para overlapped
    {
        fprintf(stderr, "Error\n");
        CloseHandle(this->PortaSerial);        
    }   
   
 }

char Serial::Read()
{
	while (PortaSerial != INVALID_HANDLE_VALUE){
	
    DWORD bytes_lidos;// , total_bytes_lidos = 0;
    //fprintf(stderr, "Recebendo bytes....");
    
    if (!ReadFile(this->PortaSerial,		//identificador da porta serial
				this->bytes_para_receber,	//buffer, local tempor�rio onde os dados lidos ser�o armazenados 
				1,					        //tamanho do buffer
				&bytes_lidos,		        //ponteiro onde armazenar� a quantidade exata de bytes lidos
				NULL))				        //ponteiro para overlapped
	{
		fprintf(stderr, "Erro\n");


       CloseHandle(this->PortaSerial);
	} 
	else 
	{
            if (bytes_lidos > 0)
                return this->bytes_para_receber[0];
	}
  }		
  return '0';
}

