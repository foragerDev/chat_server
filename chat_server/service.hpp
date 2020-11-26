#pragma once

#include <iostream>
#include "core_header.hpp"
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <unordered_map>
#include <thread>
#include <memory>
#include <mutex>

unsigned int Service::id_counter = 0;

class Service {
public:
	Service(std::shared_ptr<net::ip::tcp::socket> sock)
		: m_socket(sock) {

	}
	void StartServer() {
		std::string message = "Hi! Get register yourself. Please enter Your user name.";
		net::async_write(*m_socket.get(), net::buffer(message), [this](sys::error_code& ec, std::size_t bytes_transfered) {
			get_user_name(ec, bytes_transfered);
			});
	}

	void get_user_name(sys::error_code& ec, std::size_t bytes_transfered) {
		std::string message = "Enter your username:";
		net::async_write(*m_socket.get(), net::buffer(message), [this](sys::error_code& ec, std::size_t bytes_transfered) {
			if (ec) {
				std::cout << " Failed to get user name " << ec.value() << " " << ec.message() << std::endl;
			}
			process_user_name(ec, bytes_transfered);
			});
	}

	void process_user_name(sys::error_code& ec, std::size_t bytes_transfered) {
		net::streambuf stream; //stream is non copyable
		net::async_read(*m_socket.get(), stream, [this, &stream](sys::error_code& ec, std::size_t bytes_transfered) {
			if (ec) {
				std::cout << "Sorry I could not get the user name" << ec.value() << " " << ec.message() << std::endl;
			}
			save_user_name(stream);
			});
	}

	void save_user_name(net::streambuf& buf) {

	}
private:
	std::mutex mut;
	std::unordered_map <std::string , std::string > users;
	std::shared_ptr<net::ip::tcp::socket> m_socket;
	static unsigned int id_counter;
};

