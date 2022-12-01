Example for Suggested Usage
While the usage of epoll when employed like a Level Triggered interface does have the same semantics of poll(2), an Edge Triggered usage requires more clarifiction to avoid stalls in the application event loop. In this example, listener is a non-blocking socket on which listen(2) has been called. The function do_use_fd() uses the new ready file descriptor until EAGAIN is returned by either read(2) or write(2). An event driven state machine application should, after having received EAGAIN, record its current state so that at the next call to do_use_fd() it will continue to read(2) or write(2) from where it stopped before. 

struct epoll_event ev, *events;
for(;;) {
    nfds = epoll_wait(kdpfd, events, maxevents, -1);
    for(n = 0; n < nfds; ++n) {
        if(events[n].data.fd == listener) {
            client = accept(listener, (struct sockaddr *) &local,
                            &addrlen);
            if(client < 0){
                perror("accept");
                continue;
            }
            setnonblocking(client);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = client;
            if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, client, &ev) < 0) {
                fprintf(stderr, "epoll set insertion error: fd=%d0,
                        client);
                return -1;
            }
        }
        else
            do_use_fd(events[n].data.fd);
    }
}
