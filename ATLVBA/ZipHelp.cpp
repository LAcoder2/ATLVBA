#include <shlobj.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <comdef.h>
#include <string>
#include <fstream>

void WriteBytesToZipFile(BSTR psFilePath, BSTR psZipPath, SAFEARRAY** ppsaBytes) {
	CoInitialize(NULL);

	do {
		// Проверяем входные параметры
		if (!psFilePath || !psZipPath || !ppsaBytes || !*ppsaBytes) {
			MessageBox(NULL, L"Ошибка: Неверные параметры функции", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Получаем информацию о SAFEARRAY
		SAFEARRAY* psa = *ppsaBytes;
		if (SafeArrayGetDim(psa) != 1) {
			MessageBox(NULL, L"Ошибка: SAFEARRAY должен быть одномерным", L"Ошибка", MB_ICONERROR);
			break;
		}

		VARTYPE vt;
		if (FAILED(SafeArrayGetVartype(psa, &vt)) || vt != VT_UI1) {
			MessageBox(NULL, L"Ошибка: SAFEARRAY должен содержать байты (VT_UI1)", L"Ошибка", MB_ICONERROR);
			break;
		}

		long lLowerBound, lUpperBound;
		if (FAILED(SafeArrayGetLBound(psa, 1, &lLowerBound)) ||
			FAILED(SafeArrayGetUBound(psa, 1, &lUpperBound))) {
			MessageBox(NULL, L"Ошибка: Не удалось получить границы SAFEARRAY", L"Ошибка", MB_ICONERROR);
			break;
		}

		long elementCount = lUpperBound - lLowerBound + 1;
		if (elementCount <= 0) {
			MessageBox(NULL, L"Ошибка: SAFEARRAY пустой", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Получаем указатель на данные
		LPVOID pData = NULL;
		HRESULT hr = SafeArrayAccessData(psa, &pData);
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить доступ к данным SAFEARRAY", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Создаем временный файл с уникальным именем
		WCHAR tempPath[MAX_PATH];
		WCHAR tempFile[MAX_PATH];

		if (!GetTempPath(MAX_PATH, tempPath)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить путь к временной директории", L"Ошибка", MB_ICONERROR);
			SafeArrayUnaccessData(psa);
			break;
		}

		// Извлекаем имя файла из psZipPath для временного файла
		std::wstring zipPath(psZipPath);
		size_t lastSlash = zipPath.find_last_of(L"/\\");
		std::wstring fileName = (lastSlash != std::wstring::npos) ?
			zipPath.substr(lastSlash + 1) : zipPath;

		if (fileName.empty()) {
			MessageBox(NULL, L"Ошибка: Неверное имя файла в архиве", L"Ошибка", MB_ICONERROR);
			SafeArrayUnaccessData(psa);
			break;
		}

		// Создаем временный файл с правильным расширением
		if (!GetTempFileName(tempPath, L"ZIP", 0, tempFile)) {
			MessageBox(NULL, L"Ошибка: Не удалось создать временный файл", L"Ошибка", MB_ICONERROR);
			SafeArrayUnaccessData(psa);
			break;
		}

		// Переименовываем временный файл чтобы иметь правильное расширение
		std::wstring finalTempFile = tempFile;
		finalTempFile += L"_" + fileName;

		if (!MoveFile(tempFile, finalTempFile.c_str())) {
			MessageBox(NULL, L"Ошибка: Не удалось переименовать временный файл", L"Ошибка", MB_ICONERROR);
			DeleteFile(tempFile);
			SafeArrayUnaccessData(psa);
			break;
		}

		// Записываем данные во временный файл
		std::ofstream file(finalTempFile, std::ios::binary);
		if (!file.is_open()) {
			MessageBox(NULL, L"Ошибка: Не удалось открыть временный файл для записи", L"Ошибка", MB_ICONERROR);
			SafeArrayUnaccessData(psa);
			DeleteFile(finalTempFile.c_str());
			break;
		}

		if (!file.write(static_cast<const char*>(pData), elementCount)) {
			MessageBox(NULL, L"Ошибка: Не удалось записать данные во временный файл", L"Ошибка", MB_ICONERROR);
			file.close();
			SafeArrayUnaccessData(psa);
			DeleteFile(finalTempFile.c_str());
			break;
		}

		file.close();
		SafeArrayUnaccessData(psa);

		// Используем IShellDispatch для копирования файла в архив
		IShellDispatch* pShell = NULL;
		Folder* pDestFolder = NULL;
		VARIANT vDir, vFile, vOpt;

		hr = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (void**)&pShell);
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось создать экземпляр IShellDispatch", L"Ошибка", MB_ICONERROR);
			DeleteFile(finalTempFile.c_str());
			break;
		}

		// Открываем ZIP-архив как папку
		vDir.vt = VT_BSTR;
		vDir.bstrVal = SysAllocString(psFilePath);
		hr = pShell->NameSpace(vDir, &pDestFolder);
		if (FAILED(hr)) {
			std::wstring errorMsg = L"Ошибка: Не удалось открыть ZIP архив: ";
			errorMsg += psFilePath;
			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
			VariantClear(&vDir);
			pShell->Release();
			DeleteFile(finalTempFile.c_str());
			break;
		}

		// Копируем временный файл в архив
		vFile.vt = VT_BSTR;
		vFile.bstrVal = SysAllocString(finalTempFile.c_str());
		vOpt.vt = VT_I4;
		vOpt.lVal = 16; // FOF_NO_UI - не показывать диалоги прогресса и ошибок

		// Выполняем копирование
		pDestFolder->CopyHere(vFile, vOpt);

		// Ожидаем завершения операции (важно дать время на обработку)
		Sleep(3000);

		// Проверяем, был ли файл добавлен в архив
		// Можно добавить дополнительную проверку здесь

		// Освобождаем ресурсы
		pDestFolder->Release();
		pShell->Release();
		VariantClear(&vDir);
		VariantClear(&vFile);
		VariantClear(&vOpt);

		// Удаляем временный файл
		if (!DeleteFile(finalTempFile.c_str())) {
			MessageBox(NULL, L"Предупреждение: Не удалось удалить временный файл", L"Предупреждение", MB_ICONWARNING);
		}

		std::wstring successMsg = L"Данные успешно записаны в архив. Размер: ";
		successMsg += std::to_wstring(elementCount);
		successMsg += L" байт";
		MessageBox(NULL, successMsg.c_str(), L"Успех", MB_ICONINFORMATION);

	} while (false);

	CoUninitialize();
}

//void WriteBytesToZipFile(BSTR psFilePath, BSTR psZipPath, SAFEARRAY** ppsaBytes) {
//	CoInitialize(NULL);
//	IStream* pStream = NULL;
//	LPVOID pData = NULL;
//	LARGE_INTEGER liZero = { 0 };
//	ULARGE_INTEGER uliSize = { 0 };
//	ULONG cbWritten = 0;
//
//	do {
//		// Проверяем входные параметры
//		if (!psFilePath || !psZipPath || !ppsaBytes || !*ppsaBytes) {
//			MessageBox(NULL, L"Ошибка: Неверные параметры функции", L"Ошибка", MB_ICONERROR);
//			break;
//		}
//		
//		// Получаем информацию о SAFEARRAY
//		SAFEARRAY* psa = *ppsaBytes;
//		//if (SafeArrayGetDim(psa) != 1) {
//		if (psa->cDims!=1){
//			std::wstring errorMsg = L"Ошибка: SAFEARRAY должен быть одномерным";
//			errorMsg += std::to_wstring(psa->cDims);
//			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
//			break;
//		}
//
//		//VARTYPE vt;
//		//if (FAILED(SafeArrayGetVartype(psa, &vt)) || vt != VT_UI1) {
//		/*if (psa->cbElements!=1){
//			MessageBox(NULL, L"Ошибка: SAFEARRAY должен содержать байты (VT_UI1)", L"Ошибка", MB_ICONERROR);
//			break;
//		}*/
//
//		/*long lLowerBound, lUpperBound;
//		if (FAILED(SafeArrayGetLBound(psa, 1, &lLowerBound)) ||
//			FAILED(SafeArrayGetUBound(psa, 1, &lUpperBound))) {
//			MessageBox(NULL, L"Ошибка: Не удалось получить границы SAFEARRAY", L"Ошибка", MB_ICONERROR);
//			break;
//		}*/
//
//		long elementCount = psa->rgsabound[0].cElements; //lUpperBound - lLowerBound + 1;
//		/*if (elementCount) {
//		} else {
//			MessageBox(NULL, L"Ошибка: SAFEARRAY пустой", L"Ошибка", MB_ICONERROR);
//			break;
//		}*/
//
//		// Создаем объект ZIP-папки
//		CLSID clsidZipFolder;
//		HRESULT hr = CLSIDFromString(L"{E88DCCE0-B7B3-11d1-A9F0-00AA0060FA31}", &clsidZipFolder);
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось получить CLSID для ZIP папки", L"Ошибка", MB_ICONERROR);
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		IShellFolder* pZipFolder;
//		hr = CoCreateInstance(clsidZipFolder, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pZipFolder));
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось создать экземпляр ZIP папки", L"Ошибка", MB_ICONERROR);
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		// Инициализируем ZIP-папку путем к архиву
//		IPersistFolder* pPersistFolder;
//		hr = pZipFolder->QueryInterface(IID_PPV_ARGS(&pPersistFolder));
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось получить интерфейс IPersistFolder", L"Ошибка", MB_ICONERROR);
//			pZipFolder->Release();
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		// Создаем PIDL для ZIP-архива
//		LPITEMIDLIST pidlArchive;
//		hr = SHParseDisplayName(psFilePath, NULL, &pidlArchive, 0, NULL);
//		if (FAILED(hr)) {
//			std::wstring errorMsg = L"Ошибка: Не удалось разобрать путь к архиву: ";
//			errorMsg += psFilePath;
//			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
//			pPersistFolder->Release();
//			pZipFolder->Release();
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		hr = pPersistFolder->Initialize(pidlArchive);
//		ILFree(pidlArchive);
//		pPersistFolder->Release();
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось инициализировать ZIP папку", L"Ошибка", MB_ICONERROR);
//			pZipFolder->Release();
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		// Создаем поток для записи файла в архив
//		hr = pZipFolder->BindToStorage(NULL, NULL, IID_PPV_ARGS(&pStream));
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось создать поток для записи", L"Ошибка", MB_ICONERROR);
//			pZipFolder->Release();
//			//SafeArrayUnaccessData(psa);
//			break;
//		}
//
//		// Создаем структуру STGMEDIUM для передачи данных
//		STGMEDIUM stgMedium = { 0 };
//		stgMedium.tymed = TYMED_ISTREAM;
//		stgMedium.pstm = pStream;
//
//		// Создаем структуру FORMATETC для описания формата
//		FORMATETC formatEtc = { 0 };
//		formatEtc.cfFormat = CF_UNICODETEXT; // Можно изменить на нужный формат
//		formatEtc.ptd = NULL;
//		formatEtc.dwAspect = DVASPECT_CONTENT;
//		formatEtc.lindex = -1;
//		formatEtc.tymed = TYMED_ISTREAM;
//
//		// Получаем указатель на данные
//		hr = SafeArrayAccessData(psa, &pData);
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось получить доступ к данным SAFEARRAY", L"Ошибка", MB_ICONERROR);
//			break;
//		}
//
//		// Записываем данные в поток
//		ULONG ulBytesToWrite = elementCount;
//		hr = pStream->Write(pData, ulBytesToWrite, &cbWritten);
//
//		SafeArrayUnaccessData(psa);
//
//		if (FAILED(hr)) {
//			MessageBox(NULL, L"Ошибка: Не удалось записать данные в поток", L"Ошибка", MB_ICONERROR);
//		}
//		else if (cbWritten != ulBytesToWrite) {
//			std::wstring errorMsg = L"Ошибка: Записано не все данные. Ожидалось: ";
//			errorMsg += std::to_wstring(ulBytesToWrite);
//			errorMsg += L", записано: ";
//			errorMsg += std::to_wstring(cbWritten);
//			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
//		}
//		else {
//			// Фиксируем изменения в потоке
//			hr = pStream->Commit(STGC_DEFAULT);
//			if (FAILED(hr)) {
//				MessageBox(NULL, L"Ошибка: Не удалось зафиксировать изменения в потоке", L"Ошибка", MB_ICONERROR);
//			}
//			else {
//				std::wstring successMsg = L"Данные успешно записаны в архив. Размер: ";
//				successMsg += std::to_wstring(cbWritten);
//				successMsg += L" байт";
//				MessageBox(NULL, successMsg.c_str(), L"Успех", MB_ICONINFORMATION);
//			}
//		}
//
//		pZipFolder->Release();
//
//	} while (false);
//
//	// Освобождаем ресурсы
//	if (pStream) {
//		pStream->Release();
//	}
//
//	CoUninitialize();
//}

SAFEARRAY* UnzipFileToBytes(BSTR psFilePath, BSTR psZipPath) {
	CoInitialize(NULL);
	SAFEARRAY* pSafeArray = NULL;
	IStream* pStream = NULL;
	LPVOID pZipData = NULL;
	ULONG cbRead = 0;

	do {
		// Создаем объект ZIP-папки
		CLSID clsidZipFolder;
		HRESULT hr = CLSIDFromString(L"{E88DCCE0-B7B3-11d1-A9F0-00AA0060FA31}", &clsidZipFolder);
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить CLSID для ZIP папки", L"Ошибка", MB_ICONERROR);
			break;
		}

		IShellFolder* pZipFolder;
		hr = CoCreateInstance(clsidZipFolder, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pZipFolder));
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось создать экземпляр ZIP папки", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Инициализируем ZIP-папку путем к архиву
		IPersistFolder* pPersistFolder;
		hr = pZipFolder->QueryInterface(IID_PPV_ARGS(&pPersistFolder));
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить интерфейс IPersistFolder", L"Ошибка", MB_ICONERROR);
			pZipFolder->Release();
			break;
		}

		// Создаем PIDL для ZIP-архива
		LPITEMIDLIST pidlArchive;
		hr = SHParseDisplayName(psFilePath, NULL, &pidlArchive, 0, NULL);
		if (FAILED(hr)) {
			std::wstring errorMsg = L"Ошибка: Не удалось разобрать путь к архиву: ";
			errorMsg += psFilePath;
			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
			pPersistFolder->Release();
			pZipFolder->Release();
			break;
		}

		hr = pPersistFolder->Initialize(pidlArchive);
		ILFree(pidlArchive);
		pPersistFolder->Release();
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось инициализировать ZIP папку", L"Ошибка", MB_ICONERROR);
			pZipFolder->Release();
			break;
		}

		// Получаем PIDL для внутреннего файла в архиве
		LPITEMIDLIST pidlFile;
		ULONG chEaten = 0;
		ULONG dwAttributes = 0;
		hr = pZipFolder->ParseDisplayName(NULL, NULL, psZipPath, &chEaten, &pidlFile, &dwAttributes);
		if (FAILED(hr)) {
			std::wstring errorMsg = L"Ошибка: Не удалось найти файл в архиве: ";
			errorMsg += psZipPath;
			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
			pZipFolder->Release();
			break;
		}

		// Получаем интерфейс IStream для файла
		hr = pZipFolder->BindToStorage(pidlFile, NULL, IID_PPV_ARGS(&pStream));
		ILFree(pidlFile);
		pZipFolder->Release();
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить поток данных для файла", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Определяем размер файла через STATSTG
		STATSTG stat;
		hr = pStream->Stat(&stat, STATFLAG_NONAME);
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось определить размер файла", L"Ошибка", MB_ICONERROR);
			break;
		}

		ULARGE_INTEGER fileSize;
		fileSize.QuadPart = stat.cbSize.QuadPart;
		if (fileSize.HighPart > 0 || fileSize.LowPart > LONG_MAX) {
			std::wstring errorMsg = L"Ошибка: Файл слишком большой. Размер: ";
			errorMsg += std::to_wstring(fileSize.QuadPart);
			errorMsg += L" байт";
			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
			break;
		}

		if (fileSize.LowPart == 0) {
			MessageBox(NULL, L"Предупреждение: Файл пустой", L"Предупреждение", MB_ICONWARNING);
		}

		// Создаем SAFEARRAY для хранения данных
		pSafeArray = SafeArrayCreateVector(VT_UI1, 0, fileSize.LowPart);
		if (!pSafeArray) {
			MessageBox( NULL, L"Ошибка: Не удалось создать SAFEARRAY", L"Ошибка", MB_ICONERROR);
			break;
		}

		// Читаем данные из потока непосредственно в SAFEARRAY		
		hr = SafeArrayAccessData(pSafeArray, &pZipData);
		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось получить доступ к данным SAFEARRAY", L"Ошибка", MB_ICONERROR);
			SafeArrayDestroy(pSafeArray);
			pSafeArray = NULL;
			break;
		}
		hr = pStream->Read(pZipData, fileSize.LowPart, &cbRead);
		SafeArrayUnaccessData(pSafeArray);

		if (FAILED(hr)) {
			MessageBox(NULL, L"Ошибка: Не удалось прочитать данные из потока", L"Ошибка", MB_ICONERROR);
			SafeArrayDestroy(pSafeArray);
			pSafeArray = NULL;
		}
		else if (cbRead != fileSize.LowPart) {
			std::wstring errorMsg = L"Ошибка: Прочитано не все данные. Ожидалось: ";
			errorMsg += std::to_wstring(fileSize.LowPart);
			errorMsg += L", прочитано: ";
			errorMsg += std::to_wstring(cbRead);
			MessageBox(NULL, errorMsg.c_str(), L"Ошибка", MB_ICONERROR);
			SafeArrayDestroy(pSafeArray);
			pSafeArray = NULL;
		}
		/*else {
			std::wstring successMsg = L"Файл успешно извлечен. Размер: ";
			successMsg += std::to_wstring(cbRead);
			successMsg += L" байт";
			MessageBox(NULL, successMsg.c_str(), L"Успех", MB_ICONINFORMATION);
		}*/

	} while (false);

	// Освобождаем ресурсы
	if (pStream) pStream->Release();

	CoUninitialize();

	/*if (pSafeArray == NULL) {
		MessageBox(NULL, L"Ошибка: Не удалось извлечь файл из архива", L"Итоговая ошибка", MB_ICONERROR);
	}*/

	return pSafeArray; // Возвращает NULL в случае ошибки
}