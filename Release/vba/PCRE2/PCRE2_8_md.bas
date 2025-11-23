Attribute VB_Name = "PCRE2_8_md"
Option Explicit

DefLngPtr H, P
'Declare PtrSafe Sub CoTaskMemFree Lib "ole32.dll" (ByVal hMem As LongPtr)
'Private Declare PtrSafe Function GlobalSize Lib "kernel32.dll" (ByVal hMem As LongPtr) As LongPtr
Private Declare PtrSafe Sub SafeArrayAllocDescriptorEx Lib "oleaut32.dll" ( _
                  ByVal vt As VbVarType, _
                  ByVal cDims As Long, _
                        saOut() As Any)

Public Const NullPtr As LongPtr = 0
Public Const PCRE_ERROR_NOMATCH& = -1
' PCRE2 error codes
Public Const PCRE2_ERROR_NOMATCH As Long = -1
Public Const PCRE2_ERROR_NULL As Long = -2
Public Const PCRE2_ERROR_BADOPTION As Long = -3
Public Const PCRE2_ERROR_NOMEMORY As Long = -5

' PCRE2 options
Public Const PCRE2_ZERO_TERMINATED As Long = -1
Public Const PCRE2_NOTBOL As Long = &H1
Public Const PCRE2_NOTEOL As Long = &H2
Public Const PCRE2_JIT_COMPLETE& = &H1&

Public Const VT_I8& = 20
Public Const FADF_AUTO      As Integer = &H1
Public Const FADF_FIXEDSIZE As Integer = &H10

Public Type MatchPos
    bpos As Long
    epos As Long
End Type
Public hPCRE2_8
Public pfn_pcre2_compile_8
Public pfn_pcre2_match_data_create_from_pattern_8
Public pfn_pcre2_match_8
Public pfn_pcre2_get_ovector_pointer_8
Public pfn_pcre2_match_data_free_8
Public pfn_pcre2_code_free_8
Public pfn_pcre2_get_error_message_8
Public pfn_pcre2_jit_compile_8
Public pfn_pcre2_get_ovector_count_8
Public PCRE2IsInit As Boolean

Sub PCRE2_8_Init()
    If PCRE2IsInit = False Then Else Exit Sub
    hPCRE2_8 = LoadLibrary(ThisWorkbook.Path & "\pcre2-8.dll")
    If hPCRE2_8 = 0 Then
        Debug.Print "Ошибка загрузки pcre2-8.dll"
        Exit Sub
    End If
    pfn_pcre2_compile_8 = GetProcAddress(hPCRE2_8, "pcre2_compile_8")
    pfn_pcre2_match_data_create_from_pattern_8 = GetProcAddress(hPCRE2_8, "pcre2_match_data_create_from_pattern_8")
    pfn_pcre2_match_8 = GetProcAddress(hPCRE2_8, "pcre2_match_8")
    pfn_pcre2_get_ovector_pointer_8 = GetProcAddress(hPCRE2_8, "pcre2_get_ovector_pointer_8")
    pfn_pcre2_match_data_free_8 = GetProcAddress(hPCRE2_8, "pcre2_match_data_free_8")
    pfn_pcre2_code_free_8 = GetProcAddress(hPCRE2_8, "pcre2_code_free_8")
    pfn_pcre2_get_error_message_8 = GetProcAddress(hPCRE2_8, "pcre2_get_error_message_8")
    pfn_pcre2_jit_compile_8 = GetProcAddress(hPCRE2_8, "pcre2_jit_compile_8")
    pfn_pcre2_get_ovector_count_8 = GetProcAddress(hPCRE2_8, "pcre2_get_ovector_count_8")
    PCRE2IsInit = True
End Sub

Private Sub TestPCRE2_8_obj()
    Dim pcreObj As New PCRE2_8_obj
    Dim Pattern As String: Pattern = toA("(\w+) (\w+) (\w+) (\w+)") 'toA("\b\w+\b") 'toA("(?=\d+)\w+(?=\d+)") 'toA("(\d{2})-(\d{2})-(\d{4})")
    Dim subject As String: subject = toA("Hello world from PCRE2") 'toA("3223oiuppoou342423") 'toA("Дата: 25-12-2023, время: 10:30")
    Dim matches() As MatchPos
    
    pcreObj.JIT = True
    pcreObj.Pattern = Pattern
    matches = pcreObj.Execute(subject)
    
    Dim matchNum&, tempNum&
    For matchNum = 0 To UBound(matches, 2)
        Debug.Print "Совпадение №" & matchNum + 1
        For tempNum = 0 To UBound(matches)
            With matches(tempNum, matchNum)
              Debug.Print fmA(MidB$(subject, .bpos + 1, .epos - .bpos))
            End With
        Next
    Next
End Sub

