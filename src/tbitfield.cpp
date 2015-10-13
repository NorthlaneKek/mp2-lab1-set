// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen=len;
	MemLen=(BitLen/(sizeof(TELEM)*8));
	pMem=new TELEM[MemLen];
	for (int i=0; i<MemLen; i++)
		pMem[i]=0;
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
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int Pos = n%32;
	TELEM tmp = 1;
	tmp = tmp<<Pos;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int Ind = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[Ind] = pMem[Ind]|mask;
}


void TBitField::ClrBit(const int n) // очистить бит
{
	int Ind = GetMemIndex(n);
	TELEM mask =~GetMemMask(n);
	pMem[Ind] = pMem[Ind]&mask;
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	return pMem[GetMemIndex(n)]&GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = bf.pMem[i];
	return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int tmp = 0;
	if ((BitLen == bf.BitLen) & (MemLen == bf.MemLen))
	
		for (int i; i < MemLen; i++)
		{
			if ((pMem[i] == bf.pMem[i]))
				tmp = tmp + i;
			else tmp = 0;
		}
	else tmp = 0;
	tmp = tmp / MemLen;
  return tmp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int tmp = 0;
	if ((BitLen != bf.BitLen) & (MemLen != bf.BitLen))
	
		for (int i; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				tmp = tmp + i;
			else 
			{
				tmp = 0;
			    break;
			}
		}
	else tmp = 0;
	tmp = tmp / MemLen;
	return tmp;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=pMem[i]|bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=~pMem[i];
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
