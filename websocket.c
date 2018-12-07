#include <libwebsockets.h>

int callback_freeswitch(struct lws *wsi,
                               enum lws_callback_reasons reason, void *user,
                               void *in, size_t len) {
  switch (reason) {
  case LWS_CALLBACK_PROTOCOL_INIT: {
    //One time initializer for callback_freeswitch
    break;
  }
  case LWS_CALLBACK_ESTABLISHED: {
    lwsl_debug("callback_freeswitch established\n");
    break;
  }
  case LWS_CALLBACK_CLOSED: {
    lwsl_debug("callback_freeswitch closed\n");
    break;
  }
  case LWS_CALLBACK_SERVER_WRITEABLE: {
    lwsl_debug("callback_freeswitch server writeable\n");
    break;
  }
  case LWS_CALLBACK_RECEIVE: {
    lwsl_debug("callback_freeswitch receive\n");
    break;
  }
  default:break;
  }

  return 0;
}