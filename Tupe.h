#pragma once

#include <iostream>
using namespace std;

// ��������
template<typename... TList>
class Tuple;

// Ϊ��ʱ �ػ�
template<> class Tuple<> {};
using EmptyTupe = Tuple<>;

// Ϊһ��Ԫ��ʱ �ػ�
template<typename Head>
class Tuple<Head> : EmptyTupe{
public:
	Tuple(const Head &val) : m_head(val) {}

	void SetVal(const Head &val) {
		m_head = val;
	}

	Head GetHead() {
		return m_head;
	}

private:
	Head m_head;
};

// �ݹ鶨�� �ػ�
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...>{
public:
	// ģ������� չ�� ������ һ�� ������������ֻ����һ��������Ϊ���һ���� ģ������� ��û�����Ҫ��
	Tuple(const Head &val, Tail... preArgs)
		: Tuple<Tail...>(preArgs...),         // ���������� չ��
		m_head(val) {}

	void SetVal(const Head &val) {
		m_head = val;
	}

	Head GetHead() {
		return m_head;
	}
private:
	Head m_head;
};

template<typename... TList>
Tuple<TList...> MakeTuple(TList...);

template<>
Tuple<> MakeTuple() {
	return EmptyTupe();
}

template<typename Head, typename... Tail>
Tuple<Head, Tail...> MakeTuple(const Head &head, const Tail&... tail) {
	return Tuple<Head, Tail... >(head, tail...);
}

template<unsigned int N, typename... TList>
struct TupleAt;

template<unsigned int N, typename Head, typename... Tail>
struct TupleAt <N, Tuple<Head, Tail...>> {
	using ValType = typename TupleAt<N - 1, Tuple<Tail...>>::ValType;
	using TupleType = typename TupleAt<N - 1, Tuple<Tail...>>::TupleType;
};

template<typename Head, typename... Tail>
struct TupleAt <0, Tuple<Head, Tail...>> {
	using ValType = Head;
	using TupleType = Tuple<Head, Tail...>;
};

template <unsigned int N>
struct TupleAt<N, EmptyTupe> {
	using ValType = EmptyTupe;
	using TupleType = EmptyTupe;
};

template<unsigned int N, typename... TList>
typename TupleAt<N, Tuple<TList...>>::ValType
TupleGet(Tuple<TList...> tp) {
	return static_cast<typename TupleAt<N, Tuple<TList...>> ::TupleType>(tp).GetHead();
}
