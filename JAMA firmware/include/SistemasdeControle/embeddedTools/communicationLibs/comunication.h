#ifndef COMUNICATION_H
#define COMUNICATION_H
#include <string>

class Comunication
{
public:
    Comunication(ComunicationConfiguration *config);
    virtual void open();
    virtual void sendData();
    virtual void receiveData();
    virtual void close();
    std::string print();

protected:
    ComunicationConfiguration *config;
};

template<typename Type> // ok
std::ostream& operator<< (std::ostream& output, Comunication controller);
template<typename Type> //ok
std::string& operator<< (std::string& output, const Comunication &controller);
#endif // COMUNICATION_H
