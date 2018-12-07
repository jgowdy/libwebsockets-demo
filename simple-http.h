#ifndef LIBWEBSOCKETS_DEMO_SIMPLE_HTTP_H
#define LIBWEBSOCKETS_DEMO_SIMPLE_HTTP_H

int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                  void *user, void *in, size_t len);

#endif