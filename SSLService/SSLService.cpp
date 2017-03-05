#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <io.h>
#include <fcntl.h>

void connect_handler(const boost::system::error_code &ec);
void timeout_handler(const boost::system::error_code &ec);
void run_service();

boost::asio::io_service service;

int main()
{
	setlocale(LC_ALL, "rus");
	//_setmode(_fileno(stdout), _O_U16TEXT);


	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("95.84.192.66"), 80);
	boost::asio::ip::tcp::socket sock(service);

	sock.async_connect(ep, connect_handler);

	boost::asio::deadline_timer t(service, boost::posix_time::seconds(5));
	t.async_wait(timeout_handler);

	for (int i = 0; i < 5; ++i)
		boost::thread(run_service);

	service.run();
    return 0;
}

void run_service()
{
	std::cout << "run " << std::endl;
	service.run();
}

void timeout_handler(const boost::system::error_code &ec)
{
	std::cout << "timeout!" << std::endl;
}

void connect_handler(const boost::system::error_code &ec)
{
	std::cout << "connect_handler " << ec << std::endl;
	// here we know we connected successfully
	// if ec indicates success 
}