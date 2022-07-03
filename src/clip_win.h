#include <windows.h>
#include <node.h>
#include <shlobj.h>
#include <vector>
#include <string>
#include <iostream>

#include <node_api.h>
using namespace std;

napi_value get_file_names(napi_env env);
