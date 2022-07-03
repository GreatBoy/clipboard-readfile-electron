#include "clip_win.h"

char *GBK2Utf8(const char *strGBK)
{
	WCHAR *str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK, -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	delete[] str1;
	str1 = NULL;
	return str2;
}

napi_value get_file_names(napi_env env)
{
  napi_value fileNames, value;
  napi_status status;
  
  status = napi_create_array(env, &fileNames);
  if (status != napi_ok) return nullptr;

	if (OpenClipboard(NULL)) // open clipboard
	{
		HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP)); // get the file path hwnd of clipboard
		if (hDrop != NULL)
		{
			char szFilePathName[MAX_PATH + 1] = { 0 };
			UINT nNumOfFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); // get the count of files
			for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex)
			{
				memset(szFilePathName, 0, MAX_PATH + 1);
				DragQueryFile(hDrop, nIndex, szFilePathName, MAX_PATH); // get file name

                status = napi_create_string_utf8(env, GBK2Utf8(szFilePathName), NAPI_AUTO_LENGTH, &value);
                if (status != napi_ok) return nullptr;
                status = napi_set_element(env, fileNames, nIndex, value);
                if (status != napi_ok) return nullptr;
			}
		}
		CloseClipboard(); // close clipboard	
	}
	return fileNames;
}
