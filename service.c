#include <libwebsockets.h>
#include <pthread.h>

#include "service.h"
#include "simple-http.h"
#include "websocket.h"

typedef struct {
  struct lws_context *context;
  pthread_t lws_service_thread;
  volatile int shutdown_flag;
} service_state;

// First protocol must be http handler
struct lws_protocols protocols[] = {
    {"http-only", callback_http, 0, 0, 0, NULL},
    //{"freeswitch-events", callback_freeswitch, 0, 0, 0, NULL},
    {NULL, NULL, 0, 0, 0, NULL}};


void *lws_service_thread_proc(void *data) {
  service_state *service = (service_state*)data;

  struct lws_context_creation_info info = {0};
  info.protocols = &protocols[0];

  info.options = LWS_SERVER_OPTION_LIBUV;

#ifndef USE_SSL
  info.port = 8080;
#else
  info.port = 4430;
  info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT | LWS_SERVER_OPTION_REDIRECT_HTTP_TO_HTTPS;
  info.ssl_cert_filepath = "";
  info.ssl_private_key_filepath = "";
  info.ssl_ca_filepath = "";
  info.ssl_cipher_list = "";
  info.ssl_private_key_password = NULL;
#endif

  struct lws_context *context = lws_create_context(&info);
  if (context==NULL) {
    lwsl_err("Failed to create websocket context\n");
    abort();
  }

  while (!service->shutdown_flag) {
    lws_service(context, 150);
  }

  lwsl_notice("Websocket service thread exiting\n");
  lws_context_destroy(context);
  return 0;
}

service_state_handle start_service() {
  service_state *state = calloc(1, sizeof(service_state));

  // Spawn the thread that services the websocket
  int result = pthread_create(&state->lws_service_thread, NULL,
                              lws_service_thread_proc, state);

  if (result!=0) {
    lwsl_err("Failed to create pthread for websocket service\n");
    return NULL;
  }

  return state;
}