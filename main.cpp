#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

// Receiving data from buffer
string get_data(tcp::socket& socket){
    boost::asio::streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

// Send data
void send_data(tcp::socket& socket, const string& message){
    write(socket, buffer(message + "\n"));
}

int main() {

    io_service service;

    // Listening for any new incoming connection at port 9999 with IPv4 protocol
    

    return 0;
}
