#include <libwebsockets.h>

int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                         void *user, void *in, size_t len) {
  switch (reason) {
  case LWS_CALLBACK_PROTOCOL_INIT: {
    //One time initializer call for callback_http
    return 0;
  }
/*
  case LWS_CALLBACK_HTTP: {
    char *requested_uri = (char *) in;
    lwsl_debug("requested URI: %s\n", requested_uri);
    lws_return_http_status(wsi, 200, "OK");
    return 0;
  }*/
/*
  case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: {
    lwsl_debug("callback_http SERVER_NEW_CLIENT_INSTANTIATED\n");
    break;
  }
  */
  default:break;
  }

  return 0;
}