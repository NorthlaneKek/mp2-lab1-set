// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen / (sizeof(TELEM)* 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	for (int i=0; i<MemLen; i++)
		pMem[i] = bf.pMem[i]; 
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	return mask << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else throw n;
}


void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int Ind = GetMemIndex(n);
		TELEM mask = ~GetMemMask(n);
		pMem[Ind] &=  mask;
	}
	else throw n;
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
	else throw n;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
 	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen))
	{
		int flag = 1;
		for (int i = 0; i < MemLen; i++)
		{

			if (pMem[i] == bf.pMem[i])
			{
				flag = 1;
			}
			else
			{
				flag = 0;
				break;
			}
			return flag;
		}
		}
	else
	{
		return 0;
	}
	}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((BitLen == bf.BitLen) && (MemLen == bf.BitLen))
	{
		int flag = 0;
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] == bf.pMem[i])
			{
				flag = 0;
			}
			else
			{
				flag = 1;
				break;
			}
			return flag;
		}
	}
	else
	{
		return 1;
	}
}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int TmpSize = BitLen;
	if (BitLen < bf.BitLen)
		 TmpSize = bf.BitLen;
	TBitField tmp(TmpSize);
	for (int i=0; i<tmp.MemLen; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int TmpSize = BitLen;
	if (BitLen < bf.BitLen)
		TmpSize = bf.BitLen;
	TBitField tmp(TmpSize);
	for (int i=0; i<tmp.MemLen; i++)
		tmp.pMem[i]=pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=~pMem[i];
	for (int i = sizeof(TELEM)* 8 - ((MemLen)*sizeof(TELEM)* 8 - BitLen); i < sizeof(TELEM)*8; i++)
		tmp.pMem[MemLen - 1] &= (~(1 << i));
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char ch;
	do {istr>>ch;} while (ch!=' ');
	while (1)
	{
		istr>>ch;
		if (ch=='0')
			bf.ClrBit(i++);
		else if (ch=='1')
			bf.SetBit(i++);
		else break;
}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0;i<bf.BitLen; i++)
		if (bf.GetBit(i)) ostr<<1;
		else ostr<<0;
			return ostr;
}
