#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  TCPSocket tcp_soc;
  const Address endpoint( host, "http" );
  tcp_soc.connect( endpoint );

  const string get_cmd = "GET " + path + " HTTP/1.1\r\n";
  const string host_cmd = "Host: " + host + "\r\n";

  tcp_soc.write( get_cmd );
  tcp_soc.write( host_cmd );
  tcp_soc.write( "Connection: close \r\n" );
  tcp_soc.write( "\r\n" );

  string buff;
  while ( not tcp_soc.eof() ) {
    tcp_soc.read( buff );
    std::cout << buff;
  }
  tcp_soc.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
