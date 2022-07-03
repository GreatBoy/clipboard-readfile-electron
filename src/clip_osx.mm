#include "clip_osx.h"
#include <node_api.h>

napi_value get_file_names(napi_env env) {
  napi_value fileNames, value;
  napi_status status;
  
  status = napi_create_array(env, &fileNames);
  if (status != napi_ok) return nullptr;

  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];  
  NSArray* tempArray = [pasteboard pasteboardItems];
  int count = 0;
  for(NSPasteboardItem *tmpItem in tempArray){ 
    NSString *pathString = [tmpItem stringForType:@"public.file-url"];
    const char* str = [pathString UTF8String];
    if (str) {
      status = napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, &value);
      if (status != napi_ok) return nullptr;
      status = napi_set_element(env, fileNames, count, value);
      if (status != napi_ok) return nullptr;
      count++;
    }
  }
  return fileNames;
}
