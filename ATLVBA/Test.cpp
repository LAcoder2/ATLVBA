#include "ATLVBA_i.h"
#include <windows.h>
//#include <oleauto.h> // SAFEARRAY, BSTR
#include <regex>
#include <string>

struct MatchPosition {
	LONG position;
	LONG length;
};

std::regex* CreateStdRegexA(BSTR bstrPattern){
	//std::wstring wPattern(bstrPattern, SysStringLen(bstrPattern));
	//std::string sPattern(wPattern.begin(), wPattern.end());
	//std::regex* ret = new std::regex((LPSTR)bstrPattern, *((long*)bstrPattern - 1));
	if (bstrPattern != nullptr)
		return new std::regex((LPSTR)bstrPattern, *((long*)bstrPattern - 1));
}

void DestroyStdRegex(std::regex* regex){
	if (regex != nullptr) delete regex; // освобождает объект, если он был выделен через new
}

SAFEARRAY* StdRE_ExtractPositionsA(const std::regex* rxPattern, BSTR bstrInp) {
	if (rxPattern != nullptr && bstrInp != nullptr) {} else return nullptr;
	const char* lastChar = (const char*)bstrInp + *((long*)bstrInp - 1) - 1;
	std::cregex_iterator iter((const char*)bstrInp, lastChar, *rxPattern);
	std::cregex_iterator iter_end;

	LONG match_count = 0;
	for (auto i = iter; i != iter_end; i++) {
		match_count++;
	}
	//std::cmatch match;
	//std::regex_search((const char*)input, match, *rxPattern);
	//int match_count = match.length;
	if (match_count) {} else return NULL; //возвращаем нулль, если ни чего не найдено

	SAFEARRAY* psaMatches = SafeArrayCreateVector(VT_UI8, 0, match_count);
	if (!psaMatches) return NULL;

	// Получить указатель на данные SAFEARRAY для прямой записи
	MatchPosition* matchPositions = NULL;	
	HRESULT hr = SafeArrayAccessData(psaMatches, (void**)&matchPositions);
	if (FAILED(hr)) {
		SafeArrayDestroy(psaMatches);
		return NULL;
	}
	long index = 0;
	for (auto pmatch = iter; pmatch !=iter_end; pmatch++, index++) {
		const std::cmatch& match = *pmatch;
		matchPositions[index].position = (long)match.position(0) + 1;
		matchPositions[index].length = (long)match.length(0);
	}
	SafeArrayUnaccessData(psaMatches);

	return psaMatches;
}
void TestSub(std::string* str) {
	*str = "some string";
}
void DeleteStdString(std::string* str) {
	delete str;
}

BSTR RegexReplaceA(const std::regex& pattern, BSTR bstrInput, BSTR bstrReplacement){
	if (!bstrInput || !bstrReplacement)
		return NULL;

	// Получаем длины BSTR (ANSI)
	int lenInput = *((long*)bstrInput - 1);
	int lenReplace = *((long*)bstrReplacement - 1);

	// Преобразуем BSTR ANSI в std::string (без копирования организационно не обойтись)
	//const char* pInput = (const char*)bstrInput;
	//const char* pReplace = (const char*)bstrReplacement;

	std::string inputStr((const char*)bstrInput, lenInput);
	std::string replaceStr((const char*)bstrReplacement, lenReplace);

	// Выполняем замену по паттерну
	std::string result = std::regex_replace(inputStr, pattern, replaceStr);
	
	// Создаем BSTR результат (длина в wchar_t)
	size_t szRet = (int)result.size();
	BSTR bstrResult = SysAllocStringByteLen(NULL, szRet);

	if (!bstrResult)
		return NULL;

	memcpy(bstrResult, result.data(), szRet);

	return bstrResult;
}