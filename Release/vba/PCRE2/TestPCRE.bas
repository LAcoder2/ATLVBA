Attribute VB_Name = "TestPCRE"
Option Explicit
DefLngPtr H, P
Declare PtrSafe Sub CoTaskMemFree Lib "ole32.dll" (ByVal hMem As LongPtr)
'Private Declare PtrSafe Function GlobalSize Lib "kernel32.dll" (ByVal hMem As LongPtr) As LongPtr
Private Declare PtrSafe Sub SafeArrayAllocDescriptorEx Lib "oleaut32.dll" ( _
                  ByVal vt As VbVarType, _
                  ByVal cDims As Long, _
                        saOut() As Any)

Public Const NullPtr As LongPtr = 0
Const PCRE_ERROR_NOMATCH& = -1
' PCRE2 error codes
Private Const PCRE2_ERROR_NOMATCH As Long = -1
Private Const PCRE2_ERROR_NULL As Long = -2
Private Const PCRE2_ERROR_BADOPTION As Long = -3
Private Const PCRE2_ERROR_NOMEMORY As Long = -5

' PCRE2 options
Private Const PCRE2_ZERO_TERMINATED As Long = -1
Private Const PCRE2_NOTBOL As Long = &H1
Private Const PCRE2_NOTEOL As Long = &H2
Private Const PCRE2_JIT_COMPLETE = &H1&
Private Sub Auto_Open()
    Stop
End Sub
Private Sub TestPCRE2()
    Dim hLib
    Dim pfn_pcre2_compile_8
    Dim pfn_pcre2_match_data_create_from_pattern_8
    Dim pfn_pcre2_match_8
    Dim pfn_pcre2_get_ovector_pointer_8
    Dim pfn_pcre2_match_data_free_8
    Dim pfn_pcre2_code_free_8
    Dim pfn_pcre2_get_error_message_8
    Dim pfn_pcre2_jit_compile_8
    Dim pfn_pcre2_get_ovector_count_8
    ' Загружаем библиотеку
    hLib = LoadLibrary(ThisWorkbook.Path & "\pcre2-8.dll")
    If hLib = 0 Then
        Debug.Print "Ошибка загрузки pcre2-8.dll"
        Exit Sub
    End If
    
    ' Получаем адреса функций
    pfn_pcre2_compile_8 = GetProcAddress(hLib, "pcre2_compile_8")
    pfn_pcre2_match_data_create_from_pattern_8 = GetProcAddress(hLib, "pcre2_match_data_create_from_pattern_8")
    pfn_pcre2_match_8 = GetProcAddress(hLib, "pcre2_match_8")
    pfn_pcre2_get_ovector_pointer_8 = GetProcAddress(hLib, "pcre2_get_ovector_pointer_8")
    pfn_pcre2_match_data_free_8 = GetProcAddress(hLib, "pcre2_match_data_free_8")
    pfn_pcre2_code_free_8 = GetProcAddress(hLib, "pcre2_code_free_8")
    pfn_pcre2_get_error_message_8 = GetProcAddress(hLib, "pcre2_get_error_message_8")
    pfn_pcre2_jit_compile_8 = GetProcAddress(hLib, "pcre2_jit_compile_8")
    pfn_pcre2_get_ovector_count_8 = GetProcAddress(hLib, "pcre2_get_ovector_count_8")
    
    Dim pattern As String: pattern = toA("(\d{2})-(\d{2})-(\d{4})")         'toA("\b\w+\b")
    Dim subject As String: subject = toA("Дата: 25-12-2023, время: 10:30")  'toA("Hello world from PCRE2")
    
    Dim re As LongPtr         ' pcre2_code_8*
    Dim match_data As LongPtr ' pcre2_match_data_8*
    Dim error_number&
    Dim error_offset&
    Dim error_buffer(255) As Byte
    
    ' pcre2_code *pcre2_compile(PCRE2_SPTR pattern, PCRE2_SIZE length, uint32_t options, int *errorcode, PCRE2_SIZE *erroroffset, pcre2_compile_context *ccontext);
    CCall6 pfn_pcre2_compile_8, re, ptrSz, _
            ByVal pattern, _
            ByVal PCRE2_ZERO_TERMINATED, _
            ByVal 0&, _
                  error_number, _
                  error_offset, _
            ByVal NullPtr
    If re = 0 Then
        ' void pcre2_get_error_message_8(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
        CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
                ByVal error_number, error_buffer(0), ByVal 256&
        GoSub Cleanup
        Err.Raise error_number, , "Ошибка компиляции: " & Replace$(fmA(error_buffer), vbNullChar, vbNullString)
    End If
    Dim jit_result&
    ' int pcre2_jit_compile_8(pcre2_code_8 *code, uint32_t options);
    CCall2 pfn_pcre2_jit_compile_8, jit_result, 4, _
            ByVal re, ByVal PCRE2_JIT_COMPLETE
'    If jit_result <> 0 Then Debug.Print "JIT-компиляция не удалась, но это не критично"
    
    ' pcre2_match_data *pcre2_match_data_create_from_pattern_8(const pcre2_code_8 *code, pcre2_general_context *gcontext);
    CCall2 pfn_pcre2_match_data_create_from_pattern_8, match_data, ptrSz, _
            ByVal re, ByVal NullPtr
    If match_data = 0 Then
        Debug.Print "Ошибка создания match_data"
        GoTo EndSub
    End If
    
    ' PCRE2_SIZE *pcre2_get_ovector_pointer_8(pcre2_match_data_8 *match_data);
    Dim povector
    CCall1 pfn_pcre2_get_ovector_pointer_8, povector, ptrSz, _
            ByVal match_data
    If povector Then
    Else
        Debug.Print "Ошибка получения ovector"
        GoTo EndSub
    End If
    Dim ovec_count&
    'uint32_t pcre2_get_ovector_count(pcre2_match_data *match_data);
    CCall1 pfn_pcre2_get_ovector_count_8, ovec_count, 4, ByVal match_data
    
    GoTo EndSub
    
    Dim subject_length&: subject_length = StrLenB(subject)
    Dim start_offset&: start_offset = 0
    Dim match_count&: match_count = 0
    Dim rc&
    
    ' Поиск всех совпадений
    While start_offset < subject_length
        ' int pcre2_match_8(const pcre2_code_8 *code, PCRE2_SPTR subject, PCRE2_SIZE length, PCRE2_SIZE startoffset, uint32_t options, pcre2_match_data_8 *match_data, pcre2_match_context_8 *mcontext);
        CCall7 pfn_pcre2_match_8, rc, LenB(rc), _
                ByVal re, _
                ByVal subject, _
                ByVal subject_length, _
                ByVal start_offset, _
                ByVal 0&, _
                ByVal match_data, _
                ByVal NullPtr
        
        If rc < 0 Then
            If rc = PCRE2_ERROR_NOMATCH Then
                GoTo ExitWhile
            Else
                ' int pcre2_get_error_message(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
                CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
                        ByVal rc, _
                              error_buffer(0), _
                        ByVal CLngPtr(256) 'приведение к LongPtr потому, что PCRE2_SIZE это алиас size_t, что соответствует LongPtr
                Debug.Print "Ошибка выполнения: " & fmA(error_buffer)
                GoTo ExitWhile
            End If
        End If
        
        ' Читаем вектор совпадений
        Dim ovector&(1) ' Только первое совпадение (0 - полное, 1 - первая группа)
        memCpy ovector(0), ByVal povector, 8 ' 2 * 4 bytes
        
        match_count = match_count + 1
        Dim match_start&: match_start = ovector(0) + 1
        Dim match_length&: match_length = ovector(1) - ovector(0)
        
        Debug.Print "Совпадение " & match_count & ": " & fmA(MidB$(subject, match_start, match_length))
        
        start_offset = ovector(1) + 1 ' Перемещаемся за текущее совпадение
    Wend
ExitWhile:
    
    Debug.Print "Всего совпадений: " & match_count

EndSub:
    GoSub Cleanup
Exit Sub
Cleanup:
    ' Освобождаем ресурсы
    If match_data <> 0 Then
        ' void pcre2_match_data_free_8(pcre2_match_data_8 *match_data);
        CCall1 pfn_pcre2_match_data_free_8, ByVal NullPtr, 0, _
                ByVal match_data
    End If
    
    If re <> 0 Then
        ' void pcre2_code_free_8(pcre2_code_8 *code);
        CCall1 pfn_pcre2_code_free_8, ByVal NullPtr, 0, _
                ByVal re
    End If
    
    ' Выгружаем библиотеку
    If hLib <> 0 Then
        FreeLib hLib
    End If
Return
End Sub


Private Sub TestPCRE()
    Dim psError
    Dim erroffset&
    Dim ovector(31) As Long
    Dim pPcRe
    
    Dim hLib: hLib = LoadLibrary(ThisWorkbook.Path & "\pcre.dll")
    Dim pfn_pcre_compile: pfn_pcre_compile = GetProcAddress(hLib, "pcre_compile")  'GetProcAddrByNum(hLib, 3)
    Dim pfn_pcre_exec: pfn_pcre_exec = GetProcAddress(hLib, "pcre_exec")
    Dim pfn_pcre_free: pfn_pcre_free = GetProcAddress(hLib, "pcre_free") 'GetProcAddrByNum(hLib, 10)
'    Dim pfn_pcre_free_study: pfn_pcre_free_study = GetProcAddress(hLib, "pcre_free_study")
    
    Dim sPattern$: sPattern = toA("(\d{2})-(\d{2})-(\d{4})")          'toA("\b\w+\b")
    Dim sSubject$: sSubject = toA("Дата: 25-12-2023, время: 10:30")   'toA("Hello world from PCRE")
    
    'pcre *pcre_compile(const char*, int, const char**, int*, const unsigned char*);
    'pcre *re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    CCall5 pfn_pcre_compile, pPcRe, ptrSz, _
                        ByVal sPattern, ByVal 0&, psError, erroffset, ByVal NullPtr
    If pPcRe = 0 Then
        Debug.Print "Ошибка компилляции выражения"
        Exit Sub
    End If
    
    Dim lenSubj&: lenSubj = StrLenB(sSubject)
    Dim startOffset&, options&, matchCount&
    
    Do While startOffset < lenSubj
        'int pcre_exec(const pcre *code, const pcre_extra *extra, const char *subject, int length, int startoffset, int options, int *ovector, int ovecsize);
        'int rc = pcre_exec(re, NULL, subject, lenSubj, startOffset, options, ovector(0), 30);
        Dim rc&: Call CCall8(pfn_pcre_exec, rc, LenB(rc), _
                           ByVal pPcRe, ByVal NullPtr, ByVal sSubject, ByVal lenSubj, ByVal startOffset, ByVal options, ovector(0), ByVal 32&)
        If rc < 0 Then
            If (rc = PCRE_ERROR_NOMATCH) Then
                Exit Do
            Else
                Debug.Print "Ошибка выполнения!!"
                Exit Sub
            End If
        End If
        matchCount = matchCount + 1
        Dim pos&: pos = ovector(0) + 1
        Dim matchlen&: matchlen = ovector(1) - ovector(0)
        
        Debug.Print fmA(MidB$(sSubject, pos, matchlen))
        
        startOffset = ovector(1)
    Loop
    
    'pcre_free(re);
    CCall1 pfn_pcre_free, ByVal NullPtr, 0, ByVal pPcRe  'это почему-то вызывает сбой
'    CoTaskMemFree pPcRe                                  'зато работает это
End Sub

Private Sub Test_SafeArrayAllocDescriptorEx()
    Dim lAr&(), SA As SAFEARRAY1D
    Dim bAr() As Byte: bAr = vbNullString
'    SafeArrayAllocDescriptorEx vbLong, 1, lAr
    memCpy SA, ByVal SAPtr(bAr), LenB(SA)
End Sub
