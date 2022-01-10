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
    tcp::acceptor  acceptot_server(service, tcp::endpoint(tcp::v4(),9999));

    // Creating socket object
    tcp::socket server_socket(service);

    // Waiting for connection
    acceptot_server.accept(server_socket);

    // Reading username
    string u_name = get_data(server_socket);

    // Removing "\n" from the username
    u_name.pop_back();

    // Replaying with default message to initiate chat
    string response, reply;
    reply = "Hello " + u_name + "!";
    cout << "Server: " << reply << "\n";

    send_data(server_socket,reply);

    while (true){
        // Featching response
        response = get_data(server_socket);

        // Popping last character "\n"
        response.pop_back();

        // Validating if the connection has to be closed
        if(response == "exit"){
            cout << u_name << " left!\n";
            break;
        }

        cout << u_name << ": " << response << "\n";

        // Reading new message from input stream
        cout << "Server: ";
        getline(cin, reply);
        send_data(server_socket, reply);


        if(reply == "exit"){
            break;
        }
    }

    return 0;
}
