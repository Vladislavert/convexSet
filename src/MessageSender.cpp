#include "MessageSender.hpp"

MessageSender::MessageSender()
{   
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// sock = socket(AF_INET, SOCK_DGRAM, 0);
	// Заполняем структуру для адресации при отправке пакетов
	memset((char *) &address, 0, sizeof(address));
	address.sin_family = AF_INET;
	//ставим номер порта
	address.sin_port = htons(PORT);

	slen=sizeof(address);
	//debug
	std::cout << "sim init" << std::endl;

}

// void Simulator::sendMessage(const double &simulationTime, const VectorXd_t &stateVector,const VectorXd_t &motorSpeed)
void MessageSender::send(const Point* initialPoints, const Point* resultsPoints,
						 const uint_t& sizeInitialPoints, const uint_t& sizeResultPoints)
{
	int	index;

	index = 0;
	for (unsigned int i = 0; i < sizeInitialPoints; i++)
	{
		memcpy(&message[index], &initialPoints[i], sizeof(Point));
		index += sizeof(initialPoints[i]);
	}
	for (unsigned int i = 0; i < sizeResultPoints; i++)
	{
		memcpy(&message[index], &resultsPoints[i], sizeof(Point));
		index += sizeof(resultsPoints[i]);
	}

	if (sendto(sock, message, sizeof(message) , 0 , (struct sockaddr *) &address, slen) == -1)
	{
		// выводим ошибку в терминал
		perror("sendto()");
		// завершаем выполнение программы
		exit(1);
	}
}

MessageSender::~MessageSender()
{

}