#include <ace/os_include/os_netdb.h>
#include <ace/OS_NS_errno.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>
#include <ace/Time_Value.h>

/*
 * EXTRA_CMDS=pkg-config --cflags --libs ACE
 */

/*
 *      Example of simple single threaded ace socket server.
 *      Notice the hanlding of interruption
 */
int ACE_TMAIN(int, ACE_TCHAR **) {
	// lets open the port...
	ACE_INET_Addr port_to_listen(50000);

	//ACE_INET_Addr port_to_listen("HAStatus");
	ACE_SOCK_Acceptor acceptor;

	if (acceptor.open(port_to_listen, 1) == -1) {
		ACE_ERROR_RETURN((LM_ERROR,
		                  ACE_TEXT("%p\n"),
		                  ACE_TEXT("acceptor.open")),
		                 100);
	}
	// lets print our own connect address...
	ACE_TCHAR my_name[MAXHOSTNAMELEN];
	port_to_listen.addr_to_string(my_name, MAXHOSTNAMELEN);
	ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) Listening on %s\n"), my_name));
	// lets go into the main loop...
	ACE_DEBUG((LM_DEBUG, ACE_TEXT("Server going into main loop\n")));
	while (true) {
		ACE_SOCK_Stream peer;
		ACE_INET_Addr peer_addr;
		ACE_Time_Value timeout(10, 0);

		if (acceptor.accept(peer, &peer_addr, &timeout, 1) == -1) {
			//if(acceptor.accept(peer) == -1) {
			if (ACE_OS::last_error() == EINTR) {
				ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) Interrupted while waiting for connection")));
			} else if (ACE_OS::last_error() == ETIMEDOUT) {
				ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) Timeout while waiting for connection")));
			}
		} else {
			// print the address where the connection is from...
			ACE_TCHAR peer_name[MAXHOSTNAMELEN];
			peer_addr.addr_to_string(peer_name, MAXHOSTNAMELEN);
			ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) Connection from %s\n"), peer_name));
			char buffer[4096];
			ssize_t bytes_received = peer.recv(buffer, sizeof(buffer));
			// IMPORTANT NOTICE: do not allow 0 here since it is the end
			// of file...
			while (bytes_received > 0) {
				if (peer.send(buffer, bytes_received) == -1) {
					ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) error in send")));
				}
				bytes_received = peer.recv(buffer, sizeof(buffer));
			}
			// lets show a nice message if we are interrupted while reading...
			if (bytes_received == -1) {
				if (ACE_OS::last_error() == EINTR) {
					ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) Interrupted while reading")));
				}
			}
			peer.close();
			ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) connection from %s has closed...\n"), peer_name));
		}
	}
	ACE_NOTREACHED(return 0);
}