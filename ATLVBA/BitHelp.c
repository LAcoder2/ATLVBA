#include <windows.h>
#include <intrin.h>
// ==================== 32-битные функции ====================

//VARIANT_BOOL GetBit(int num, unsigned char pos){
//	if (pos > 31) return VARIANT_FALSE;
//	return (num >> pos) & 1 ? VARIANT_TRUE : VARIANT_FALSE;
//}
VARIANT_BOOL GetBit(int num, unsigned char pos) {
	if (pos > 31) return VARIANT_FALSE;
	return (VARIANT_BOOL)((num >> pos) & 1);
}

int SetBit(int num, unsigned char pos){
	if (pos > 31) return num;
	return num | (1 << pos);
}

int ClearBit(int num, unsigned char pos){
	if (pos > 31) return num;
	return num & ~(1 << pos);
}

int LeftBitShift(int num, unsigned char shift){
	return (shift >= 32) ? 0 : num << shift;
}

int RightBitShift(int num, unsigned char shift){
	return (shift >= 32) ? 0 : num >> shift;
}

int BitRotateLeft(int num, unsigned char shift){
	shift %= 32;
	return (num << shift) | (num >> (32 - shift));
}

int BitRotateRight(int num, unsigned char shift){
	shift %= 32;
	return (num >> shift) | (num << (32 - shift));
}

unsigned char BitCount(int num){
	// Быстрый алгоритм подсчета битов (Kernighan's algorithm)
	unsigned char count = 0;
	unsigned int n = (unsigned int)num;

	while (n) {
		n &= (n - 1);
		count++;
	}
	return count;
}

// ==================== 64-битные функции ====================

//VARIANT_BOOL GetBit64(__int64 num, unsigned char pos){
//	if (pos > 63) return VARIANT_FALSE;
//	return (num >> pos) & 1 ? VARIANT_TRUE : VARIANT_FALSE;
//}
VARIANT_BOOL GetBit64(__int64 num, unsigned char pos) {
	if (pos > 63) return VARIANT_FALSE;
	return (VARIANT_BOOL)(num >> pos) & 1;
}

__int64 SetBit64(__int64 num, unsigned char pos){
	if (pos > 63) return num;
	return num | (1LL << pos);
}

__int64 ClearBit64(__int64 num, unsigned char pos){
	if (pos > 63) return num;
	return num & ~(1LL << pos);
}

__int64 LeftBitShift64(__int64 num, unsigned char shift){
	return (shift >= 64) ? 0 : num << shift;
}

__int64 RightBitShift64(__int64 num, unsigned char shift){
	return (shift >= 64) ? 0 : num >> shift;
}

__int64 BitRotateLeft64(__int64 num, unsigned char shift){
	shift %= 64;
	return (num << shift) | (num >> (64 - shift));
}

__int64 BitRotateRight64(__int64 num, unsigned char shift){
	shift %= 64;
	return (num >> shift) | (num << (64 - shift));
}

unsigned char BitCount64(__int64 num){
	unsigned char count = 0;
	unsigned __int64 n = (unsigned __int64)num;

	while (n) {
		n &= (n - 1);
		count++;
	}
	return count;
}

//Проверка чётности (Parity check)
BOOL IsEven(int n) { return !(n & 1); }        // Чётное
BOOL IsOdd(int n) { return n & 1; }           // Нечётное

//Проверка выравнивания адреса
BOOL IsAligned(void* ptr, size_t alignment) {
	return !((uintptr_t)ptr & (alignment - 1));
}
// alignment должно быть степенью двойки

//Проверка, является ли число степенью двойки
BOOL IsPowerOfTwo(unsigned int n) {
	return n && !(n & (n - 1));  // 0 вернёт 0, степени двойки - 1
}

//Поиск самого младшего установленного бита
int LowestSetBit(int n) {
	return n & -n;  // Выделяет младший единичный бит
	// Пример: 12 (1100) & -12 (0100) = 4 (0100)
}
// поиск самого старшего установленного бита
// only MSVC (Visual Studio)
int HighestSetBit_msvc(unsigned int n) {
	unsigned long index;
	if (_BitScanReverse(&index, n)) {
		return (int)index;
	}
	return -1;  // n == 0
}
//Изоляция группы битов (bit field extraction)
// Извлечь биты с позиции 'start' длиной 'length'
unsigned int ExtractBits(unsigned int n, unsigned char start, unsigned char length) {
	unsigned int mask = (1u << length) - 1;  // Создаём маску из length единиц
	return (n >> start) & mask;
}
// Пример: ExtractBits(0xABCD, 4, 8) → извлечёт 0xBC
unsigned __int64 ExtractBits64(unsigned __int64 n, unsigned char start, unsigned char length) {
	unsigned __int64 mask = (1u << length) - 1;  // Создаём маску из length единиц
	return (n >> start) & mask;
}
// Установить биты с позиции 'start' длиной 'length' в значение 'value'
unsigned int SetBits(unsigned int n, unsigned char start, unsigned char length, unsigned int value) {
	unsigned int mask = ((1u << length) - 1) << start;
	return (n & ~mask) | ((value << start) & mask);
}
unsigned __int64 SetBits64(unsigned __int64 n, unsigned char start, unsigned char length, unsigned __int64 value) {
	unsigned __int64 mask = ((1u << length) - 1) << start;
	return (n & ~mask) | ((value << start) & mask);
}

//Переключение бита
int BitToggle(int num, unsigned char pos) {
	if (pos > 31) return num; // Проверка границ
	return num ^ (1 << pos); // Ключевая операция XOR
}
__int64 BitToggle64(__int64 num, unsigned char pos) {
	if (pos > 63) return num; 
	return num ^ (1LL << pos); // 1LL - long long константа
}