#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<iostream>
#include	<string>
#include	<cstring>

#include "DataTypes.hpp"
#include    "Point.hpp"

// адрес сервера на который мы будем отправлять пакеты
#define SERVER "127.0.0.1"
#define BUFLEN 136	//размер сообщения в байтах
#define PORT 3001	//Порт на который мы будем отправлять данные

class MessageSender
{
private:
    std::string     	server;
    int             	buflen;
    int             	port;
    int 	        	sock;
    int 	        	slen;
    struct 	sockaddr_in	address;
	char				message[BUFLEN];
	
public:
	MessageSender();

	// void sendMessage(const double &simulationTime, const VectorXd_t &stateVector,const VectorXd_t &motorSpeed);
	void send(const Point* initialPoints, const Point* resultsPoints,
					 const uint_t& sizeInitialPoints, const uint_t& sizeResultPoints);

	~MessageSender();
};

#endif 
