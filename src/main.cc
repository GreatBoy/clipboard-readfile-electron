// hello.cc using Node-API
#include <node_api.h>
#ifdef __WIN32__
#include "clip_win.h"
#elif __APPLE__
#include "clip_osx.h"
#endif

namespace demo {

napi_value readFiles(napi_env env, napi_callback_info args) {
  napi_value greeting;
  napi_status status;
 
  greeting = get_file_names(env);
  return greeting;
}

napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, nullptr, 0, readFiles, nullptr, &fn);
  if (status != napi_ok) return nullptr;

  status = napi_set_named_property(env, exports, "readFiles", fn);
  if (status != napi_ok) return nullptr;
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace demo