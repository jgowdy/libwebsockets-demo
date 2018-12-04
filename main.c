#include <libwebsockets.h>
#include <pthread/pthread.h>

static struct
{
  struct lws_context *context;
  struct lws_protocols *freeswitch_protocol;
  pthread_t websocket_service_thread;
  volatile int shutdown_flag;
} globals = {0};

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                         void *user, void *in, size_t len)
{
  switch (reason)
  {
  case LWS_CALLBACK_PROTOCOL_INIT:
    break;
  case LWS_CALLBACK_ESTABLISHED:
    break;
  case LWS_CALLBACK_CLOSED:
    break;
  case LWS_CALLBACK_SERVER_WRITEABLE:
    break;
  case LWS_CALLBACK_RECEIVE:
    break;
  default:
    break;
  }

  return 0;
}

static int callback_freeswitch(struct lws *wsi,
                               enum lws_callback_reasons reason, void *user,
                               void *in, size_t len)
{
  switch (reason)
  {
  case LWS_CALLBACK_PROTOCOL_INIT:
    break;
  case LWS_CALLBACK_ESTABLISHED:
    break;
  case LWS_CALLBACK_CLOSED:
    break;
  case LWS_CALLBACK_SERVER_WRITEABLE:
    break;
  case LWS_CALLBACK_RECEIVE:
    break;
  default:
    break;
  }

  return 0;
}

// First protocol must be http handler
struct lws_protocols protocols[] = {
    {"http-only", callback_http, 0, 0, 0, NULL, 0},
    {"freeswitch-events", callback_freeswitch, 0, 0, 0, NULL, 0},
    {NULL, NULL, 0, 0, 0, NULL, 0}};

void *websocket_service_thread_proc(void *data)
{
  struct lws_context *context = (struct lws_context *)data;

  while (!globals.shutdown_flag)
  {
    lws_service(context, 150);
  }

  printf("Websocket service thread exiting\n");
  lws_context_destroy(context);
  return NULL;
}

int main(int argc, char *argv[])
{
  struct lws_context_creation_info info = {0};
  info.port = 80;
  info.protocols = &protocols[0];

  struct lws_context *context = lws_create_context(&info);
  if (context == NULL)
  {
    printf("Failed to create websocket context\n");
    return -1;
  }

  // Spawn the thread that services the websocket
  int result = pthread_create(&globals.websocket_service_thread, NULL,
                              websocket_service_thread_proc, context);

  if (result != 0)
  {
    printf("Failed to create pthread for websocket service\n");
    lws_context_destroy(context);
    return -1;
  }
}
