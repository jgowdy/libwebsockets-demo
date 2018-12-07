#ifndef LIBWEBSOCKETS_DEMO_WEBSOCKET_H
#define LIBWEBSOCKETS_DEMO_WEBSOCKET_H

int callback_freeswitch(struct lws *wsi,
                        enum lws_callback_reasons reason, void *user,
                        void *in, size_t len);

#endif