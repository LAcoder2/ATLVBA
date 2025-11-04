# ATLVBA
ATL/com is a library (DLL) that implements various functions in C/C++ that complement VBA functionality.
The library can be included in references using the standard method, but the functions can also be accessed using the "Delcare" import. When using the library, it must be located in the system directory or in the VBA project directory. In the latter case, the code must be written in an automacro. The automacro module must not use functions from atlvba.dll, otherwise the automacro code may fail to compile and generate an error.
'''vba
Private Declare PtrSafe Function LoadLibrary Lib "kernel32.dll" Alias "LoadLibraryA" (ByVal lpLibFileName As String) As LongPtr

Private Sub Workbook_Open()
    LoadLibrary ThisWorkbook.Path & "\ATLVBA.dll"
'    Debug.Print "Workbook_Open"
'    ChDir ThisWorkbook.Path
End Sub
'''
