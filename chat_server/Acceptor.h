#pragma once
#include "core_header.hpp"


#include <memory>
#include <atomic>

#include <boost/asio/io_service.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>


class Acceptor
{
public:
	Acceptor(net::io_service& io, unsigned short port) :
		Io_Service(io),
		my_acceptor(io, net::ip::tcp::endpoint(
			net::ip::address_v4::any(), port)),
		stop(false) {
	}

private:

	net::io_service& Io_Service;
	net::ip::tcp::acceptor my_acceptor;
	std::atomic_bool stop;

	void start_acceptor() {
	std::shared_ptr < net::ip::tcp::socket> sock(new net::ip::tcp::socket(Io_Service));
	my_acceptor.async_accept(
		*sock.get(), [this, sock](sys::error_code& ec) {
			if (ec) {
				std::cout << "Error Occured" << std::endl;
			}
			do_accept();
		}
	);
}

	void do_accept(std::shared_ptr<net::ip::tcp::socket>& sock, sys::error_category& ec) {
		my_acceptor.
	}

};
