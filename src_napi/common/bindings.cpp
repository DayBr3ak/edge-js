#include "napi_edge_common.h"

BOOL debugMode = 1;

int CoreClrInit(char* source, size_t sourceLen);

#ifdef EDGE_PLATFORM_WINDOWS
#pragma unmanaged
#endif
napi_value MyFunction(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  return argv[0];
}

#ifdef EDGE_PLATFORM_WINDOWS
#pragma unmanaged
#endif
napi_value InitializeClrFunc(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  size_t sourceLen;
  status = napi_get_value_string_utf8(env, argv[0], NULL, 0, &sourceLen);

  char* source = new char[sourceLen + 1];
  status = napi_get_value_string_utf8(env, argv[0], source, sourceLen + 1, &sourceLen);
  CoreClrInit(source, sourceLen + 1);
  delete source;
  return nullptr;
}

#ifdef EDGE_PLATFORM_WINDOWS
#pragma unmanaged
#endif
napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  DBG("Init Module");

  #ifdef _DEBUG
    status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Unable to wrap native function");
    }

    status = napi_set_named_property(env, exports, "myFunction", fn);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Unable to populate exports");
    }
  #endif

  status = napi_create_function(env, NULL, 0, InitializeClrFunc, NULL, &fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }

  status = napi_set_named_property(env, exports, "initializeClrFunc", fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
