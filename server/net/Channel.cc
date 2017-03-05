#include <server/net/Channel.h>

#include <poll.h>
#include <cstdio>

using namespace server;
using namespace server::net;

const int Channel::kReadEvent = POLLIN;

Channel::Channel(EventLoop *loop, int fd)
	: loop_(loop),
	  fd_(fd),
	  events_(0),
	  revents_(0),
	  index_(-1)
{

}

Channel::~Channel()
{

}

void Channel::handle_event()
{
	if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
	{

	}

	if (revents_ & POLLNVAL)
	{
		perror("Channel::handle_event() POLLNVAL");
	}

	if (revents_ & (POLLERR | POLLNVAL))
	{
		if (errorCallback_)
		{
			errorCallback_();
		}
	}
	if (revents_ & (POLLIN | POLLPRI | POLLHUP))
	{
		if (readCallback_)
		{
			readCallback_();
		}
	}
	if (revents_ & (POLLOUT))
	{
		if (writeCallback_)
		{
			writeCallback_();
		}
	}

}