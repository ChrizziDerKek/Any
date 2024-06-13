#pragma once
#include <sstream>

#pragma warning(push)
#pragma warning(disable: 4018)
#pragma warning(disable: 4244)
#pragma warning(disable: 4302)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4804)
#pragma warning(disable: 4805)

enum class eType
{
	Null,
	Long,
	ULong,
	Int,
	UInt,
	Short,
	UShort,
	SByte,
	Byte,
	Double,
	Float,
	PVoid,
	Bool,
	String,
	Char,
	WString,
	WChar,
	Function,
};

using Any = std::shared_ptr<class IGeneric>;

template <class T, class... TArgs>
Any construct(TArgs... args) {
	return std::make_shared<T>(args...);
}

template <class T>
void destruct(std::shared_ptr<T> ptr) {
	ptr.reset();
}

class IGeneric
{
protected:
	IGeneric() = default;
	virtual void* Serialize() = 0;

	virtual Any Add(Any that) { throw; } //+
	virtual Any Sub(Any that) { throw; } //-
	virtual Any Mul(Any that) { throw; } //*
	virtual Any Div(Any that) { throw; } ///
	virtual Any Mod(Any that) { throw; } //%

	virtual Any Xor(Any that) { throw; } //^
	virtual Any And(Any that) { throw; } //&
	virtual Any Or(Any that) { throw; } //|
	virtual Any Neg() { throw; } //~
	virtual Any Not() { throw; } //!

	virtual Any Inc(bool prefix) { throw; } //++
	virtual Any Dec(bool prefix) { throw; } //--

	virtual Any EAdd(Any that) { throw; } //+=
	virtual Any ESub(Any that) { throw; } //-=
	virtual Any EMul(Any that) { throw; } //*=
	virtual Any EDiv(Any that) { throw; } ///=
	virtual Any EMod(Any that) { throw; } //%=

	virtual Any EXor(Any that) { throw; } //^=
	virtual Any EAnd(Any that) { throw; } //&=
	virtual Any EOr(Any that) { throw; } //|=

	virtual int Compare(Any that) { throw; } //<, >, <=, >=, ==, !=

	virtual Any UAdd() { throw; } //+
	virtual Any USub() { throw; } //-

public:
	auto GetLong() { return (long long)Serialize(); }
	auto GetULong() { return (unsigned long long)Serialize(); }
	auto GetInt() { return (int)Serialize(); }
	auto GetUInt() { return (unsigned)Serialize(); }
	auto GetShort() { return (short)Serialize(); }
	auto GetUShort() { return (unsigned short)Serialize(); }
	auto GetSByte() { return (signed char)Serialize(); }
	auto GetByte() { return (unsigned char)Serialize(); }
	auto GetDouble() { auto tmp = Serialize(); return *(double*)&tmp; }
	auto GetFloat() { auto tmp = Serialize(); return *(float*)&tmp; }
	auto GetPVoid() { return Serialize(); }
	auto GetBool() { return (bool)Serialize(); }
	auto GetString() { return std::string((char*)Serialize()); }
	auto GetChar() { return (char)Serialize(); }
	auto GetWString() { return std::wstring((wchar_t*)Serialize()); }
	auto GetWChar() { return (wchar_t)Serialize(); }
	auto GetFunc() { return (void*(*)(void*))Serialize(); }

	virtual eType GetType() = 0;
	virtual std::string ToString() { throw; }
	virtual void* Call(void* arg) { throw; }
	virtual Any Clone() { throw; }

	friend Any operator +(Any a, Any b);
	friend Any operator -(Any a, Any b);
	friend Any operator *(Any a, Any b);
	friend Any operator /(Any a, Any b);
	friend Any operator %(Any a, Any b);
	friend Any operator -(Any a);
	friend Any operator +(Any a);
	friend Any operator ^(Any a, Any b);
	friend Any operator &(Any a, Any b);
	friend Any operator |(Any a, Any b);
	friend bool operator <(Any a, Any b);
	friend bool operator >(Any a, Any b);
	friend bool operator >=(Any a, Any b);
	friend bool operator <=(Any a, Any b);
	friend bool operator ==(Any a, Any b);
	friend bool operator !=(Any a, Any b);
	friend Any operator ++(Any a);
	friend Any operator ++(Any a, int);
	friend Any operator --(Any a);
	friend Any operator --(Any a, int);
	friend Any operator ~(Any a);
	friend Any operator !(Any a);
	friend Any operator +=(Any a, Any b);
	friend Any operator -=(Any a, Any b);
	friend Any operator *=(Any a, Any b);
	friend Any operator /=(Any a, Any b);
	friend Any operator %=(Any a, Any b);
	friend Any operator ^=(Any a, Any b);
	friend Any operator &=(Any a, Any b);
	friend Any operator |=(Any a, Any b);
};

Any operator +(Any a, Any b) { return a->Add(b); }
Any operator -(Any a, Any b) { return a->Sub(b); }
Any operator *(Any a, Any b) { return a->Mul(b); }
Any operator /(Any a, Any b) { return a->Div(b); }
Any operator %(Any a, Any b) { return a->Mod(b); }
Any operator -(Any a) { return a->USub(); }
Any operator +(Any a) { return a->UAdd(); }
Any operator ^(Any a, Any b) { return a->Xor(b); }
Any operator &(Any a, Any b) { return a->And(b); }
Any operator |(Any a, Any b) { return a->Or(b); }
bool operator <(Any a, Any b) { return a->Compare(b) < 0; }
bool operator >(Any a, Any b) { return a->Compare(b) > 0; }
bool operator >=(Any a, Any b) { return a->Compare(b) >= 0; }
bool operator <=(Any a, Any b) { return a->Compare(b) <= 0; }
bool operator ==(Any a, Any b) { return a->Compare(b) == 0; }
bool operator !=(Any a, Any b) { return a->Compare(b) != 0; }
Any operator ++(Any a) { return a->Inc(false); }
Any operator ++(Any a, int) { return a->Inc(true); }
Any operator --(Any a) { return a->Dec(false); }
Any operator --(Any a, int) { return a->Dec(true); }
Any operator ~(Any a) { return a->Neg(); }
Any operator !(Any a) { return a->Not(); }
Any operator +=(Any a, Any b) { return a->EAdd(b); }
Any operator -=(Any a, Any b) { return a->ESub(b); }
Any operator *=(Any a, Any b) { return a->EMul(b); }
Any operator /=(Any a, Any b) { return a->EDiv(b); }
Any operator %=(Any a, Any b) { return a->EMod(b); }
Any operator ^=(Any a, Any b) { return a->EXor(b); }
Any operator &=(Any a, Any b) { return a->EAnd(b); }
Any operator |=(Any a, Any b) { return a->EOr(b); }

class Long;
class ULong;
class Int;
class UInt;
class Short;
class UShort;
class SByte;
class Byte;
class Double;
class Float;
class PVoid;
class Bool;
class String;
class Char;
class WString;
class WChar;
class Function;

//Numeric Types

#pragma region Long
class Long : public IGeneric
{
protected:
	long long m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Long; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Long>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<Long>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<Long>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Long>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<Long>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<Long>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Long>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Long>(+m_Value);
	}
	Any USub() override {
		return construct<Long>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Long>(m_Value);
	}

public:
	Long() = default;
	Long(long long val) : m_Value(val) { }
};
#pragma endregion
#pragma region ULong
class ULong : public IGeneric
{
protected:
	unsigned long long m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::ULong; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<ULong>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<ULong>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<ULong>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<ULong>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<ULong>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<ULong>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<ULong>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<ULong>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<ULong>(+m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<ULong>(m_Value);
	}

public:
	ULong() = default;
	ULong(unsigned long long val) : m_Value(val) { }
};
#pragma endregion
#pragma region Int
class Int : public IGeneric
{
protected:
	int m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Int; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Int>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Int>(+m_Value);
	}
	Any USub() override {
		return construct<Int>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Int>(m_Value);
	}

public:
	Int() = default;
	Int(int val) : m_Value(val) { }
};
#pragma endregion
#pragma region UInt
class UInt : public IGeneric
{
protected:
	unsigned m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::UInt; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<UInt>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<UInt>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<UInt>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<UInt>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<UInt>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<UInt>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<UInt>(+m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<UInt>(m_Value);
	}

public:
	UInt() = default;
	UInt(unsigned val) : m_Value(val) { }
};
#pragma endregion
#pragma region Short
class Short : public IGeneric
{
protected:
	short m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Short; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<Short>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<Short>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<Short>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Int>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Int>(+m_Value);
	}
	Any USub() override {
		return construct<Int>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Short>(m_Value);
	}

public:
	Short() = default;
	Short(short val) : m_Value(val) { }
};
#pragma endregion
#pragma region UShort
class UShort : public IGeneric
{
protected:
	unsigned short m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::UShort; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<UShort>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<UShort>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<UShort>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Int>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Int>(+m_Value);
	}
	Any USub() override {
		return construct<Int>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<UShort>(m_Value);
	}

public:
	UShort() = default;
	UShort(unsigned short val) : m_Value(val) { }
};
#pragma endregion
#pragma region SByte
class SByte : public IGeneric
{
protected:
	signed char m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::SByte; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Int>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Int>(+m_Value);
	}
	Any USub() override {
		return construct<Int>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<SByte>(m_Value);
	}

public:
	SByte() = default;
	SByte(signed char val) : m_Value(val) { }
};
#pragma endregion
#pragma region Byte
class Byte : public IGeneric
{
protected:
	unsigned char m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Byte; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Mod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value % that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value % that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value % that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value % that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value % that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value % that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value % that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value % that->GetByte());
		}
		throw;
	}
	Any Xor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value ^ that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value ^ that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value ^ that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value ^ that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value ^ that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value ^ that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value ^ that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value ^ that->GetByte());
		}
		throw;
	}
	Any And(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value & that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value & that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value & that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value & that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value & that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value & that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value & that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value & that->GetByte());
		}
		throw;
	}
	Any Or(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Long>(m_Value | that->GetLong());
		case eType::ULong:
			return construct<ULong>(m_Value | that->GetULong());
		case eType::Int:
			return construct<Int>(m_Value | that->GetInt());
		case eType::UInt:
			return construct<UInt>(m_Value | that->GetUInt());
		case eType::Short:
			return construct<Int>(m_Value | that->GetShort());
		case eType::UShort:
			return construct<Int>(m_Value | that->GetUShort());
		case eType::SByte:
			return construct<Int>(m_Value | that->GetSByte());
		case eType::Byte:
			return construct<Int>(m_Value | that->GetByte());
		}
		throw;
	}
	Any Neg() override {
		return construct<Int>(~m_Value);
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMod(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value %= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value %= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value %= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value %= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value %= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value %= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value %= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value %= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EXor(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value ^= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value ^= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value ^= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value ^= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value ^= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value ^= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value ^= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value ^= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EAnd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value &= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value &= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value &= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value &= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value &= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value &= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value &= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value &= that->GetByte();
			return Clone();
		}
		throw;
	}
	Any EOr(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value |= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value |= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value |= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value |= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value |= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value |= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value |= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value |= that->GetByte();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Int>(+m_Value);
	}
	Any USub() override {
		return construct<Int>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Byte>(m_Value);
	}

public:
	Byte() = default;
	Byte(unsigned char val) : m_Value(val) { }
};
#pragma endregion

//Floating Types

#pragma region Double
class Double : public IGeneric
{
protected:
	double m_Value;

	void* Serialize() override { return (void*)*(long long*)&m_Value; }
	eType GetType() override { return eType::Double; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Double>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<Double>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Double>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<Double>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Double>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Double>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Double>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Double>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Double>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Double>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<Double>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Double>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<Double>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Double>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Double>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Double>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Double>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Double>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Double>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<Double>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Double>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<Double>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Double>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Double>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Double>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Double>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Double>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Double>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<Double>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Double>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<Double>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Double>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Double>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Double>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Double>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Double>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Double>(+m_Value);
	}
	Any USub() override {
		return construct<Double>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Double>(m_Value);
	}

public:
	Double() = default;
	Double(double val) : m_Value(val) { }
};
#pragma endregion
#pragma region Float
class Float : public IGeneric
{
protected:
	float m_Value;

	void* Serialize() override { return (void*)*(int*)&m_Value; }
	eType GetType() override { return eType::Float; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Float>(m_Value + that->GetLong());
		case eType::ULong:
			return construct<Float>(m_Value + that->GetULong());
		case eType::Int:
			return construct<Float>(m_Value + that->GetInt());
		case eType::UInt:
			return construct<Float>(m_Value + that->GetUInt());
		case eType::Short:
			return construct<Float>(m_Value + that->GetShort());
		case eType::UShort:
			return construct<Float>(m_Value + that->GetUShort());
		case eType::SByte:
			return construct<Float>(m_Value + that->GetSByte());
		case eType::Byte:
			return construct<Float>(m_Value + that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value + that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value + that->GetFloat());
		}
		throw;
	}
	Any Sub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Float>(m_Value - that->GetLong());
		case eType::ULong:
			return construct<Float>(m_Value - that->GetULong());
		case eType::Int:
			return construct<Float>(m_Value - that->GetInt());
		case eType::UInt:
			return construct<Float>(m_Value - that->GetUInt());
		case eType::Short:
			return construct<Float>(m_Value - that->GetShort());
		case eType::UShort:
			return construct<Float>(m_Value - that->GetUShort());
		case eType::SByte:
			return construct<Float>(m_Value - that->GetSByte());
		case eType::Byte:
			return construct<Float>(m_Value - that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value - that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value - that->GetFloat());
		}
		throw;
	}
	Any Mul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Float>(m_Value * that->GetLong());
		case eType::ULong:
			return construct<Float>(m_Value * that->GetULong());
		case eType::Int:
			return construct<Float>(m_Value * that->GetInt());
		case eType::UInt:
			return construct<Float>(m_Value * that->GetUInt());
		case eType::Short:
			return construct<Float>(m_Value * that->GetShort());
		case eType::UShort:
			return construct<Float>(m_Value * that->GetUShort());
		case eType::SByte:
			return construct<Float>(m_Value * that->GetSByte());
		case eType::Byte:
			return construct<Float>(m_Value * that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value * that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value * that->GetFloat());
		}
		throw;
	}
	Any Div(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<Float>(m_Value / that->GetLong());
		case eType::ULong:
			return construct<Float>(m_Value / that->GetULong());
		case eType::Int:
			return construct<Float>(m_Value / that->GetInt());
		case eType::UInt:
			return construct<Float>(m_Value / that->GetUInt());
		case eType::Short:
			return construct<Float>(m_Value / that->GetShort());
		case eType::UShort:
			return construct<Float>(m_Value / that->GetUShort());
		case eType::SByte:
			return construct<Float>(m_Value / that->GetSByte());
		case eType::Byte:
			return construct<Float>(m_Value / that->GetByte());
		case eType::Double:
			return construct<Double>(m_Value / that->GetDouble());
		case eType::Float:
			return construct<Float>(m_Value / that->GetFloat());
		}
		throw;
	}
	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	Any Inc(bool prefix) override {
		if (prefix) {
			m_Value++;
			return Clone();
		}
		Any clone = Clone();
		m_Value++;
		return clone;
	}
	Any Dec(bool prefix) override {
		if (prefix) {
			m_Value--;
			return Clone();
		}
		Any clone = Clone();
		m_Value--;
		return clone;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value += that->GetULong();
			return Clone();
		case eType::Int:
			m_Value += that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value += that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value += that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value += that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value += that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value += that->GetByte();
			return Clone();
		case eType::Double:
			m_Value += that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value += that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any ESub(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value -= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value -= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value -= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value -= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value -= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value -= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value -= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value -= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value -= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value -= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EMul(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value *= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value *= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value *= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value *= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value *= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value *= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value *= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value *= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value *= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value *= that->GetFloat();
			return Clone();
		}
		throw;
	}
	Any EDiv(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value /= that->GetLong();
			return Clone();
		case eType::ULong:
			m_Value /= that->GetULong();
			return Clone();
		case eType::Int:
			m_Value /= that->GetInt();
			return Clone();
		case eType::UInt:
			m_Value /= that->GetUInt();
			return Clone();
		case eType::Short:
			m_Value /= that->GetShort();
			return Clone();
		case eType::UShort:
			m_Value /= that->GetUShort();
			return Clone();
		case eType::SByte:
			m_Value /= that->GetSByte();
			return Clone();
		case eType::Byte:
			m_Value /= that->GetByte();
			return Clone();
		case eType::Double:
			m_Value /= that->GetDouble();
			return Clone();
		case eType::Float:
			m_Value /= that->GetFloat();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	Any UAdd() override {
		return construct<Float>(+m_Value);
	}
	Any USub() override {
		return construct<Float>(-m_Value);
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Float>(m_Value);
	}

public:
	Float() = default;
	Float(float val) : m_Value(val) { }
};
#pragma endregion

//Specific Types

#pragma region Bool
class Bool : public IGeneric
{
protected:
	bool m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Bool; }

	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return m_Value == that->GetLong() ? 0 : m_Value < that->GetLong() ? -1 : 1;
		case eType::ULong:
			return m_Value == that->GetULong() ? 0 : m_Value < that->GetULong() ? -1 : 1;
		case eType::Int:
			return m_Value == that->GetInt() ? 0 : m_Value < that->GetInt() ? -1 : 1;
		case eType::UInt:
			return m_Value == that->GetUInt() ? 0 : m_Value < that->GetUInt() ? -1 : 1;
		case eType::Short:
			return m_Value == that->GetShort() ? 0 : m_Value < that->GetShort() ? -1 : 1;
		case eType::UShort:
			return m_Value == that->GetUShort() ? 0 : m_Value < that->GetUShort() ? -1 : 1;
		case eType::SByte:
			return m_Value == that->GetSByte() ? 0 : m_Value < that->GetSByte() ? -1 : 1;
		case eType::Byte:
			return m_Value == that->GetByte() ? 0 : m_Value < that->GetByte() ? -1 : 1;
		case eType::Double:
			return m_Value == that->GetDouble() ? 0 : m_Value < that->GetDouble() ? -1 : 1;
		case eType::Float:
			return m_Value == that->GetFloat() ? 0 : m_Value < that->GetFloat() ? -1 : 1;
		}
		throw;
	}
	std::string ToString() override {
		return std::to_string(m_Value);
	}
	Any Clone() override {
		return construct<Bool>(m_Value);
	}

public:
	Bool() = default;
	Bool(bool val) : m_Value(val) { }
};
#pragma endregion
#pragma region PVoid
class PVoid : public IGeneric
{
protected:
	void* m_Value;

	void* Serialize() override { return m_Value; }
	eType GetType() override { return eType::PVoid; }

	Any Not() override {
		return construct<Bool>(!m_Value);
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::PVoid:
		case eType::Function:
			return m_Value == that->GetPVoid() ? 0 : 1;
		}
		throw;
	}
	std::string ToString() override {
		std::stringstream stream;
		stream << m_Value;
		return stream.str();
	}
	Any Clone() override {
		return construct<PVoid>(m_Value);
	}

public:
	PVoid() = default;
	PVoid(void* val) : m_Value(val) { }
};
#pragma endregion
#pragma region Function
class Function : public IGeneric
{
protected:
	void* (*m_Value)(void*);

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Function; }

	int Compare(Any that) {
		switch (that->GetType()) {
		case eType::PVoid:
		case eType::Function:
			return GetPVoid() == that->GetPVoid() ? 0 : 1;
		}
		throw;
	}
	std::string ToString() override {
		std::stringstream stream;
		stream << m_Value;
		return stream.str();
	}
	Any Clone() override {
		return construct<Function>(m_Value);
	}
	void* Call(void* arg) override {
		return m_Value(arg);
	}

public:
	Function() = default;
	Function(void* (*val)(void*)) : m_Value(val) { }
};
#pragma endregion

//String Types

#pragma region String
class String : public IGeneric
{
protected:
	std::string m_Value;

	void* Serialize() override { return (void*)m_Value.c_str(); }
	eType GetType() override { return eType::String; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<String>(m_Value + std::to_string(that->GetLong()));
		case eType::ULong:
			return construct<String>(m_Value + std::to_string(that->GetULong()));
		case eType::Int:
			return construct<String>(m_Value + std::to_string(that->GetInt()));
		case eType::UInt:
			return construct<String>(m_Value + std::to_string(that->GetUInt()));
		case eType::Short:
			return construct<String>(m_Value + std::to_string(that->GetShort()));
		case eType::UShort:
			return construct<String>(m_Value + std::to_string(that->GetUShort()));
		case eType::SByte:
			return construct<String>(m_Value + std::to_string(that->GetSByte()));
		case eType::Byte:
			return construct<String>(m_Value + std::to_string(that->GetByte()));
		case eType::Double:
			return construct<String>(m_Value + std::to_string(that->GetDouble()));
		case eType::Float:
			return construct<String>(m_Value + std::to_string(that->GetFloat()));
		case eType::String:
			return construct<String>(m_Value + that->GetString());
		case eType::Char:
			return construct<String>(m_Value + that->GetChar());
		}
		throw;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += std::to_string(that->GetLong());
			return Clone();
		case eType::ULong:
			m_Value += std::to_string(that->GetULong());
			return Clone();
		case eType::Int:
			m_Value += std::to_string(that->GetInt());
			return Clone();
		case eType::UInt:
			m_Value += std::to_string(that->GetUInt());
			return Clone();
		case eType::Short:
			m_Value += std::to_string(that->GetShort());
			return Clone();
		case eType::UShort:
			m_Value += std::to_string(that->GetUShort());
			return Clone();
		case eType::SByte:
			m_Value += std::to_string(that->GetSByte());
			return Clone();
		case eType::Byte:
			m_Value += std::to_string(that->GetByte());
			return Clone();
		case eType::Double:
			m_Value += std::to_string(that->GetDouble());
			return Clone();
		case eType::Float:
			m_Value += std::to_string(that->GetFloat());
			return Clone();
		case eType::String:
			m_Value += that->GetString();
			return Clone();
		case eType::Char:
			m_Value += that->GetChar();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::String:
			return m_Value == that->GetString() ? 0 : 1;
		}
		throw;
	}
	std::string ToString() override {
		return m_Value;
	}
	Any Clone() override {
		return construct<String>(m_Value);
	}

public:
	String() = default;
	String(std::string val) : m_Value(val) { }
	String(const char* val) : m_Value(val) { }
	String(char* val) : m_Value(val) { }
};
#pragma endregion
#pragma region Char
class Char : public IGeneric
{
protected:
	char m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::Char; }

	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::Char:
			return m_Value == that->GetChar() ? 0 : 1;
		}
		throw;
	}
	std::string ToString() override {
		return m_Value + "";
	}
	Any Clone() override {
		return construct<Char>(m_Value);
	}

public:
	Char() = default;
	Char(char val) : m_Value(val) { }
};
#pragma endregion
#pragma region WString
class WString : public IGeneric
{
protected:
	std::wstring m_Value;

	void* Serialize() override { return (void*)m_Value.c_str(); }
	eType GetType() override { return eType::WString; }

	Any Add(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			return construct<WString>(m_Value + std::to_wstring(that->GetLong()));
		case eType::ULong:
			return construct<WString>(m_Value + std::to_wstring(that->GetULong()));
		case eType::Int:
			return construct<WString>(m_Value + std::to_wstring(that->GetInt()));
		case eType::UInt:
			return construct<WString>(m_Value + std::to_wstring(that->GetUInt()));
		case eType::Short:
			return construct<WString>(m_Value + std::to_wstring(that->GetShort()));
		case eType::UShort:
			return construct<WString>(m_Value + std::to_wstring(that->GetUShort()));
		case eType::SByte:
			return construct<WString>(m_Value + std::to_wstring(that->GetSByte()));
		case eType::Byte:
			return construct<WString>(m_Value + std::to_wstring(that->GetByte()));
		case eType::Double:
			return construct<WString>(m_Value + std::to_wstring(that->GetDouble()));
		case eType::Float:
			return construct<WString>(m_Value + std::to_wstring(that->GetFloat()));
		case eType::String:
			return construct<WString>(m_Value + that->GetWString());
		case eType::Char:
			return construct<WString>(m_Value + that->GetWChar());
		}
		throw;
	}
	Any EAdd(Any that) override {
		switch (that->GetType()) {
		case eType::Long:
			m_Value += std::to_wstring(that->GetLong());
			return Clone();
		case eType::ULong:
			m_Value += std::to_wstring(that->GetULong());
			return Clone();
		case eType::Int:
			m_Value += std::to_wstring(that->GetInt());
			return Clone();
		case eType::UInt:
			m_Value += std::to_wstring(that->GetUInt());
			return Clone();
		case eType::Short:
			m_Value += std::to_wstring(that->GetShort());
			return Clone();
		case eType::UShort:
			m_Value += std::to_wstring(that->GetUShort());
			return Clone();
		case eType::SByte:
			m_Value += std::to_wstring(that->GetSByte());
			return Clone();
		case eType::Byte:
			m_Value += std::to_wstring(that->GetByte());
			return Clone();
		case eType::Double:
			m_Value += std::to_wstring(that->GetDouble());
			return Clone();
		case eType::Float:
			m_Value += std::to_wstring(that->GetFloat());
			return Clone();
		case eType::String:
			m_Value += that->GetWString();
			return Clone();
		case eType::Char:
			m_Value += that->GetWChar();
			return Clone();
		}
		throw;
	}
	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::WString:
			return m_Value == that->GetWString() ? 0 : 1;
		}
		throw;
	}
	Any Clone() override {
		return construct<WString>(m_Value);
	}

public:
	WString() = default;
	WString(std::wstring val) : m_Value(val) { }
	WString(const wchar_t* val) : m_Value(val) { }
	WString(wchar_t* val) : m_Value(val) { }
};
#pragma endregion
#pragma region WChar
class WChar : public IGeneric
{
protected:
	wchar_t m_Value;

	void* Serialize() override { return (void*)m_Value; }
	eType GetType() override { return eType::WChar; }

	int Compare(Any that) override {
		switch (that->GetType()) {
		case eType::WChar:
			return m_Value == that->GetWChar() ? 0 : 1;
		}
		throw;
	}
	std::string ToString() override {
		return (char)m_Value + "";
	}
	Any Clone() override {
		return construct<WChar>(m_Value);
	}

public:
	WChar() = default;
	WChar(wchar_t val) : m_Value(val) { }
};
#pragma endregion

#pragma warning(pop)