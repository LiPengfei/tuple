#pragma once

#include <iostream>
using namespace std;

// 普适类型
template<typename... TList>
class Tuple;

// 为空时 特化
template<> class Tuple<> {};
using EmptyTupe = Tuple<>;

// 为一个元素时 特化
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

// 递归定义 特化
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...>{
public:
	// 模板参数包 展开 构造了 一个 函数参数包（只能有一个，并且为最后一个， 模板参数包 则没有这个要求）
	Tuple(const Head &val, Tail... preArgs)
		: Tuple<Tail...>(preArgs...),         // 函数参数包 展开
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
