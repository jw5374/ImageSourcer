#include <string>
#include <windows.h>

using namespace std;

void setRegKey(HKEY handle, wstring path) {
	const wstring strManPath = L"C:\\Users\\tlbot\\Desktop\\projects\\ImageSourcer\\ImageSourcerHost\\manifest.json\0"; // Path should be changed to whereever the host manifest.json is
	HKEY key;
	RegCreateKeyExW(handle, path.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueExW(key, NULL, 0, REG_SZ, (LPBYTE)(strManPath.c_str()), (strManPath.size() + 1) * sizeof(wchar_t));
}

int main() {
	const HKEY regHandle = HKEY_LOCAL_MACHINE;

	// This is the path for registry key, only the last section should be changed
	// If changed, this should be also changed within the port connection in the background.js script
	const wstring regPath = L"SOFTWARE\\Google\\Chrome\\NativeMessagingHosts\\com.toothbrush.imsrc";
	setRegKey(HKEY_LOCAL_MACHINE, regPath);
	return 0;
}

