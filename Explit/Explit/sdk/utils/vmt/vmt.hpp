#pragma once
#include"../../sdk.hpp"

class vmt {
public:
	vmt(void* ppClass)
	{
		this->ppbase = static_cast<std::uintptr_t**>(ppClass);
		while (static_cast<std::uintptr_t*>(*this->ppbase)[this->indexCount])
			++this->indexCount;
		const std::size_t kSizeTable = this->indexCount * sizeof(std::uintptr_t);
		this->porginal = *this->ppbase;
		this->pnew = std::make_unique<std::uintptr_t[]>(this->indexCount);
		std::memcpy(this->pnew.get(), this->porginal, kSizeTable);
		*this->ppbase = this->pnew.get();
	};
	~vmt() {
		*this->ppbase = this->porginal;
	};

	template<class Type>
	Type getorginal(const std::size_t index)
	{
		return reinterpret_cast<Type>(this->porginal[index]);
	};

	template<typename T>
	T getmethod(size_t nIndex)
	{
		return (T)OriginalTable[nIndex];
	}

	HRESULT hook(const std::size_t index, void* fnnew)
	{
		if (index > this->indexCount)
			return E_INVALIDARG;
		this->pnew[index] = reinterpret_cast<std::uintptr_t>(fnnew);
		return S_OK;
	};

	HRESULT unhook(const std::size_t index)
	{
		if (index > this->indexCount)
			return E_INVALIDARG;
		this->pnew[index] = this->porginal[index];
		return S_OK;
	}
private:
	std::unique_ptr<std::uintptr_t[]> pnew = nullptr;
	std::uintptr_t**                  ppbase = nullptr;
	std::uintptr_t*                   porginal = nullptr;
	std::size_t                       indexCount = 0;
};