VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "PCRE2_8_obj"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

DefLngPtr H, P

Private sPattern As String
Private pCode
Private pMatchData
Private ovector() As MatchPos, saOvector As SAFEARRAY1D, ovecCount&
Private JitComp As Boolean
Private errorBuffer(255) As Byte

Private Sub Class_Initialize()
    If PCRE2IsInit Then Else PCRE2_8_Init
    With saOvector
      .cbElements = 8
      .cDims = 1
      .cLocks = 1
      .fFeatures = FADF_AUTO Or FADF_FIXEDSIZE
    End With
End Sub
Private Sub Class_Terminate()
'    Debug.Print "Class_Terminate"
    CleanUp
End Sub

Friend Property Get Pattern() As String
    Pattern = sPattern
End Property
Friend Property Let Pattern(sNewPattern$)
    Compile sNewPattern, JitComp
End Property
Friend Sub Compile(sNewPattern$, Optional ByVal JitOn As Boolean)
    Dim error_number&, error_offset&
    If sNewPattern <> sPattern Or JitOn <> JitComp Then Else CleanUp
    
    ' pcre2_code *pcre2_compile(PCRE2_SPTR pattern, PCRE2_SIZE length, uint32_t options, int *errorcode, PCRE2_SIZE *erroroffset, pcre2_compile_context *ccontext);
    CCall6 pfn_pcre2_compile_8, pCode, ptrSz, _
            ByVal sNewPattern, _
            ByVal StrLenB(sNewPattern), _
            ByVal 0&, _
                  error_number, _
                  error_offset, _
            ByVal NullPtr
    If pCode Then
    Else
        ' void pcre2_get_error_message_8(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
        CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
                ByVal error_number, errorBuffer(0), ByVal CLngPtr(256)
'        CleanUp
        Err.Raise error_number, , "Ошибка компиляции: " & Replace$(fmA(errorBuffer), vbNullChar, vbNullString)
    End If
    
    If JitOn Then
        Dim jit_result&
        ' int pcre2_jit_compile_8(pcre2_code_8 *code, uint32_t options);
        CCall2 pfn_pcre2_jit_compile_8, jit_result, 4, _
                ByVal pCode, ByVal PCRE2_JIT_COMPLETE
        If jit_result Then Debug.Print "Паттерн: " & sNewPattern & vbCr & "JIT-компиляция не удалась."
    End If
    
    ' pcre2_match_data *pcre2_match_data_create_from_pattern_8(const pcre2_code_8 *code, pcre2_general_context *gcontext);
    CCall2 pfn_pcre2_match_data_create_from_pattern_8, pMatchData, ptrSz, _
            ByVal pCode, ByVal NullPtr
    If pMatchData Then
    Else
'        CleanUp
        Err.Raise 0, , "Ошибка создания match_data"
    End If
    
    Dim povector
    CCall1 pfn_pcre2_get_ovector_pointer_8, povector, ptrSz, _
            ByVal pMatchData
    If povector Then
    Else
'        CleanUp
        Err.Raise 0, , "Ошибка получения ovector"
    End If
    
    'uint32_t pcre2_get_ovector_count(pcre2_match_data *match_data);
    CCall1 pfn_pcre2_get_ovector_count_8, ovecCount, 4, ByVal pMatchData
    With saOvector
      .pvData = povector
      .Bounds.cCount = ovecCount
    End With
    SAPtr(ovector) = vp(saOvector)
    
    JitComp = JitOn
    sPattern = sNewPattern
End Sub
Friend Property Get JIT() As Boolean
    JIT = JitComp
End Property
Friend Property Let JIT(ByVal JitOn As Boolean)
    If JitComp <> JitOn Then
        Compile sPattern, JitComp
    End If
End Property

Friend Function Execute(sSubject$) As MatchPos()
    Dim subjLen&: subjLen = StrLenB(sSubject)
    Dim startOffset&
    Dim matchCount&
    Dim rc&
    Dim mpArOut() As MatchPos
    
    Dim Ub1&: Ub1 = ovecCount - 1
    ReDim mpArOut(Ub1, 0)
    Dim maxCount&: maxCount = 1
    Do While startOffset < subjLen
        ' int pcre2_match_8(const pcre2_code_8 *code, PCRE2_SPTR subject, PCRE2_SIZE length, PCRE2_SIZE startoffset, uint32_t options, pcre2_match_data_8 *match_data, pcre2_match_context_8 *mcontext);
        CCall7 pfn_pcre2_match_8, rc, 4, _
                ByVal pCode, _
                ByVal sSubject, _
                ByVal subjLen, _
                ByVal startOffset, _
                ByVal 0&, _
                ByVal pMatchData, _
                ByVal NullPtr
        
        If rc < 0 Then
            If rc = PCRE2_ERROR_NOMATCH Then
                Exit Do
            Else
                ' int pcre2_get_error_message(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
                CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
                        ByVal pCode, _
                              errorBuffer(0), _
                        ByVal CLngPtr(256) 'приведение к LongPtr, поскольку PCRE2_SIZE это алиас size_t, что соответствует LongPtr
                Debug.Print "Ошибка выполнения: " & Replace$(fmA(errorBuffer), vbNullChar, vbNullString)
                Exit Do
            End If
        End If
                
        matchCount = matchCount + 1
        If maxCount < matchCount Then
            maxCount = maxCount * 2 'maxCount = maxCount + stepIncr
            ReDim Preserve mpArOut(Ub1, maxCount - 1)
        End If
        memCpy mpArOut(0, matchCount - 1), ovector(0), ovecCount * 8
        
        startOffset = ovector(0).epos ' Перемещаемся за текущее совпадение
    Loop
    If matchCount Then
        ReDim Preserve mpArOut(Ub1, matchCount - 1)
        
        Execute = mpArOut
    End If
End Function

Private Sub CleanUp()
    If pMatchData Then
        ' void pcre2_match_data_free_8(pcre2_match_data_8 *match_data);
        CCall1 pfn_pcre2_match_data_free_8, ByVal NullPtr, 0, _
                ByVal pMatchData
    End If
    If pCode Then
        ' void pcre2_code_free_8(pcre2_code_8 *code);
        CCall1 pfn_pcre2_code_free_8, ByVal NullPtr, 0, _
                ByVal pCode
    End If
    SAPtr(ovector) = 0
End Sub

'Private Sub TestPCRE2()
'    Dim Pattern As String: Pattern = toA("(?=\d+)\w+(?=\d+)") 'toA("(\d{2})-(\d{2})-(\d{4})")         'toA("\b\w+\b")
'    Dim subject As String: subject = toA("3223oiuppoou342423") 'toA("Дата: 25-12-2023, время: 10:30")  'toA("Hello world from PCRE2")
'
'    Dim re As LongPtr         ' pcre2_code_8*
'    Dim match_data As LongPtr ' pcre2_match_data_8*
'    Dim error_number&
'    Dim error_offset&
'
'    ' pcre2_code *pcre2_compile(PCRE2_SPTR pattern, PCRE2_SIZE length, uint32_t options, int *errorcode, PCRE2_SIZE *erroroffset, pcre2_compile_context *ccontext);
'    CCall6 pfn_pcre2_compile_8, re, ptrSz, _
'            ByVal Pattern, _
'            ByVal PCRE2_ZERO_TERMINATED, _
'            ByVal 0&, _
'                  error_number, _
'                  error_offset, _
'            ByVal NullPtr
'    If re = 0 Then
'        ' void pcre2_get_error_message_8(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
'        CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
'                ByVal error_number, errorBuffer(0), ByVal 256&
'        GoSub CleanUp
'        Err.Raise error_number, , "Ошибка компиляции: " & Replace$(fmA(errorBuffer), vbNullChar, vbNullString)
'    End If
'
'    Dim jit_result&
'    ' int pcre2_jit_compile_8(pcre2_code_8 *code, uint32_t options);
'    CCall2 pfn_pcre2_jit_compile_8, jit_result, 4, _
'            ByVal re, ByVal PCRE2_JIT_COMPLETE
''    If jit_result <> 0 Then Debug.Print "JIT-компиляция не удалась, но это не критично"
'
'    ' pcre2_match_data *pcre2_match_data_create_from_pattern_8(const pcre2_code_8 *code, pcre2_general_context *gcontext);
'    CCall2 pfn_pcre2_match_data_create_from_pattern_8, match_data, ptrSz, _
'            ByVal re, ByVal NullPtr
'    If match_data = 0 Then
'        Debug.Print "Ошибка создания match_data"
'        GoTo EndSub
'    End If
'
'    ' PCRE2_SIZE *pcre2_get_ovector_pointer_8(pcre2_match_data_8 *match_data);
'    Dim povector
'    CCall1 pfn_pcre2_get_ovector_pointer_8, povector, ptrSz, _
'            ByVal match_data
'    If povector Then
'    Else
'        Debug.Print "Ошибка получения ovector"
'        GoTo EndSub
'    End If
'
'    Dim ovecCount&
'    'uint32_t pcre2_get_ovector_count(pcre2_match_data *match_data);
'    CCall1 pfn_pcre2_get_ovector_count_8, ovecCount, 4, ByVal match_data
'    Dim ovector() As MatchPos
'    ReDim ovector(ovecCount - 1)
'
''    GoTo EndSub
'
'    Dim subject_length&: subject_length = StrLenB(subject)
'    Dim start_offset&
'    Dim match_count&
'    Dim rc&
'
'    ' Поиск всех совпадений
'    While start_offset < subject_length
'        ' int pcre2_match_8(const pcre2_code_8 *code, PCRE2_SPTR subject, PCRE2_SIZE length, PCRE2_SIZE startoffset, uint32_t options, pcre2_match_data_8 *match_data, pcre2_match_context_8 *mcontext);
'        CCall7 pfn_pcre2_match_8, rc, LenB(rc), _
'                ByVal re, _
'                ByVal subject, _
'                ByVal subject_length, _
'                ByVal start_offset, _
'                ByVal 0&, _
'                ByVal match_data, _
'                ByVal NullPtr
'
'        If rc < 0 Then
'            If rc = PCRE2_ERROR_NOMATCH Then
'                GoTo ExitWhile
'            Else
'                ' int pcre2_get_error_message(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
'                CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
'                        ByVal rc, _
'                              errorBuffer(0), _
'                        ByVal CLngPtr(256) 'приведение к LongPtr потому, что PCRE2_SIZE это алиас size_t, что соответствует LongPtr
'                Debug.Print "Ошибка выполнения: " & fmA(errorBuffer)
'                GoTo ExitWhile
'            End If
'        End If
'
'        ' Читаем вектор совпадений
'
'        memCpy ovector(0), ByVal povector, ovecCount * 8 ' 2 * 4 bytes
'
'        match_count = match_count + 1
'        Dim i&
'        For i = 0 To ovecCount - 1
'            Debug.Print fmA(MidB$(subject, ovector(i).bpos + 1, ovector(i).epos - ovector(i).bpos))
'        Next
'        Debug.Print
'
'        start_offset = ovector(0).epos ' Перемещаемся за текущее совпадение
'    Wend
'ExitWhile:
'
'    Debug.Print "Всего совпадений: " & match_count
'
'EndSub:
'    GoSub CleanUp
'Exit Sub
'CleanUp:
'    ' Освобождаем ресурсы
'    If match_data <> 0 Then
'        ' void pcre2_match_data_free_8(pcre2_match_data_8 *match_data);
'        CCall1 pfn_pcre2_match_data_free_8, ByVal NullPtr, 0, _
'                ByVal match_data
'    End If
'
'    If re <> 0 Then
'        ' void pcre2_code_free_8(pcre2_code_8 *code);
'        CCall1 pfn_pcre2_code_free_8, ByVal NullPtr, 0, _
'                ByVal re
'    End If
'
'    ' Выгружаем библиотеку
'    If hPCRE2_8 <> 0 Then
'        FreeLib hPCRE2_8
'    End If
'Return
'End Sub

'Function Compile8(sNewPattern$, Optional JitOn As Boolean) As LongPtr
'    Dim re As LongPtr
'    ' pcre2_code *pcre2_compile(PCRE2_SPTR pattern, PCRE2_SIZE length, uint32_t options, int *errorcode, PCRE2_SIZE *erroroffset, pcre2_compile_context *ccontext);
'    CCall6 pfn_pcre2_compile_8, re, ptrSz, _
'            ByVal sNewPattern, _
'            ByVal StrLen(sNewPattern), _
'            ByVal 0&, _
'                  error_number, _
'                  error_offset, _
'            ByVal NullPtr
'    If Compile8 = 0 Then
'        ' void pcre2_get_error_message_8(int errorcode, PCRE2_UCHAR *buffer, PCRE2_SIZE bufflen);
'        CCall3 pfn_pcre2_get_error_message_8, ByVal NullPtr, 0, _
'                ByVal error_number, errorBuffer(0), ByVal CLngPtr(256)
'        Err.Raise error_number, , "Ошибка компиляции: " & Replace$(fmA(errorBuffer), vbNullChar, vbNullString)
'    End If
'    If JitOn Then
'        Dim jit_result&
'        ' int pcre2_jit_compile_8(pcre2_code_8 *code, uint32_t options);
'        CCall2 pfn_pcre2_jit_compile_8, jit_result, 4, _
'                ByVal re, ByVal PCRE2_JIT_COMPLETE
'        If jit_result Then Debug.Print "Паттерн: " & sNewPattern & vbCr & "JIT-компиляция не удалась."
'    End If
'    copmpile3 = re
'End Function
'Function CreateMatchData8(ByVal re As LongPtr)
'    Dim match_data As LongPtr
'    ' pcre2_match_data *pcre2_match_data_create_from_pattern_8(const pcre2_code_8 *code, pcre2_general_context *gcontext);
'    CCall2 pfn_pcre2_match_data_create_from_pattern_8, match_data, ptrSz, _
'            ByVal re, ByVal NullPtr
'    If match_data Then
'    Else
'        Err.Raise 0, , "Ошибка создания match_data"
'    End If
'    CreateMatchData8 = match_data
'End Function
'Function GetOvector8(ByVal match_data As LongPtr, saDesk As SAFEARRAY1D) As MatchPos()
'    ' PCRE2_SIZE *pcre2_get_ovector_pointer_8(pcre2_match_data_8 *match_data);
'    Dim povector
'    CCall1 pfn_pcre2_get_ovector_pointer_8, povector, ptrSz, _
'            ByVal match_data
'    If povector Then
'    Else
'        Err.Raise 0, , "Ошибка получения ovector"
'    End If
'    Dim ovecCount&
'    'uint32_t pcre2_get_ovector_count(pcre2_match_data *match_data);
'    CCall1 pfn_pcre2_get_ovector_count_8, ovecCount, 4, ByVal match_data
'
'    With saDesk
'        .cbElements = 8
'        .cDims = 1
'        .cLocks = 1
'        .fFeatures = FADF_AUTO Or FADF_FIXEDSIZE
'        .pvData = povector
'        .Bounds.cCount = ovecCount
'    End With
'End Function
