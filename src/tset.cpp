// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower=s.MaxPower;
	BitField=s.BitField;
	return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp(MaxPower);
	tmp = BitField|s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TBitField tmp(MaxPower);
	tmp = BitField;
	tmp.SetBit(Elem);
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField tmp(MaxPower);
	tmp = BitField;
	tmp.ClrBit(Elem);
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp(MaxPower);
	tmp=BitField & s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator~(void) // дополнение
{
	TBitField tmp(MaxPower);
	tmp = ~tmp;
	TSet _s(tmp);
	return _s;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	istr>>i;
	while ((i>=0) && (i<s.MaxPower))
	{
		s.InsElem(i);
		istr>>i;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i))
			if (i!=s.MaxPower)
			ostr<<' , ';
		else ostr<<0;
		return ostr;
}
