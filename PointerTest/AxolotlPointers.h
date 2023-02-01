#pragma once

#include <memory>
#include <vector>

namespace AxoPtr
{
	template<typename T>
	class lent_ptr
	{
	public:
		lent_ptr() : rawPointer(nullptr)
		{
		}

		lent_ptr(T* rawPointer) : rawPointer(rawPointer)
		{
		}

		lent_ptr(const std::unique_ptr<T>& uniquePointer) : lent_ptr(uniquePointer.get())
		{
		}

		inline T* operator ->() const
		{
			return rawPointer;
		}

		inline T& operator *() const
		{
			return *rawPointer;
		}

		inline operator bool() const
		{
			return rawPointer != nullptr;
		}

		inline bool operator !() const
		{
			return rawPointer == nullptr;
		}

		inline T* operator =(nullptr_t) noexcept
		{
			return rawPointer = nullptr;
		}

		inline T* operator =(const std::unique_ptr<T>& uniquePtr) noexcept
		{
			return rawPointer = uniquePtr.get();
		}

		inline friend bool operator ==(const lent_ptr<T>& lent1, const lent_ptr<T>& lent2)
		{
			return lent1.rawPointer == lent2.rawPointer;
		}

		inline friend bool operator ==(const lent_ptr<T>& lent1, T* rawPointer)
		{
			return lent1.rawPointer == rawPointer;
		}

		inline friend bool operator ==(const lent_ptr<T>& lent, const std::unique_ptr<T>& unique)
		{
			return lent.rawPointer == unique.get();
		}

	private:
		T* rawPointer;
	};

	template<typename T>
	static std::vector<lent_ptr<T> > uniqueVectorToLent(const std::vector<std::unique_ptr<T> >& originalVector)
	{
		return std::vector<lent_ptr<T> >(std::begin(originalVector), std::end(originalVector));
	}
}
