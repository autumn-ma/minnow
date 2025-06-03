#include "byte_stream.hh"
#include <iostream>

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), popped_ {}, pushed_ {}, buffer_ {}, is_closed_ { false }
{}

void Writer::push( string data )
{
  if ( !is_closed() && available_capacity() > 0 ) {
    data = data.substr( 0, available_capacity() );
    buffer_ = buffer_ + data;
    pushed_ = pushed_ + data.length();
  };
}

void Writer::close()
{
  is_closed_ = true;
}

bool Writer::is_closed() const
{
  return is_closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.length();
}

uint64_t Writer::bytes_pushed() const
{
  return pushed_;
}

string_view Reader::peek() const
{
  return buffer_;
}

void Reader::pop( uint64_t len )
{
  buffer_.erase( 0, len );
  popped_ = popped_ + len;
}

bool Reader::is_finished() const
{
  return is_closed_ && buffer_.length() == 0;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.length();
}

uint64_t Reader::bytes_popped() const
{
  return popped_ ;
}
