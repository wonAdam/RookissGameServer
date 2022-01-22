#pragma once
class RefCountable
{
public:
	RefCountable() : _refCount(0) {}
	virtual ~RefCountable() {}

	uint32 GetRefCount() { return _refCount; }

	uint32 AddRef() { return ++_refCount; }

	int32 ReleaseRef() 
	{  
		int32 refCount = --_refCount;
		if (refCount == 0)
		{
			delete this;
		}
		return refCount;
	}

protected:
	uint32 _refCount;

};


template <typename T>
class TSharedPtr
{
public:
	TSharedPtr() {}
	TSharedPtr(T* ptr) { Set(ptr); }

	// 복사
	TSharedPtr(const TSharedPtr& rhs) { Set(rhs._ptr); }

	// 이동
	TSharedPtr(TSharedPtr&& rhs) { _ptr = rhs._ptr; rhs._ptr = nullptr; }

	// 상속 관계 복사
	template<typename U>
	TSharedPtr(const TSharedPtr<U>& rhs) { Set(static_cast<T*>(rhs._ptr)); }

	~TSharedPtr() { Release(); }

public:
	// 복사 연산자
	TSharedPtr& operator=(const TSharedPtr& rhs)
	{
		if (rhs._ptr != _ptr)
		{
			Release();
			Set(rhs._ptr);
		}

		return *this;
	}

	// 이동 연산자
	TSharedPtr& operator=(TSharedPtr&& rhs)
	{
		Release();
		Set(rhs._ptr);

		rhs.Release();

		return *this;
	}

	bool operator==(const TSharedPtr& rhs) const { return _ptr == rhs._ptr; }
	bool operator==(const T* ptr) const { return _ptr == ptr; }
	bool operator!=(const TSharedPtr& rhs) const { return _ptr != rhs._ptr; }
	bool operator!=(const T* ptr) const { return _ptr != ptr; }
	bool operator<(const TSharedPtr& rhs) { return _ptr < rhs._ptr; }
	T& operator*() { return *_ptr; }
	operator T* () const { return _ptr; }
	T* operator->() { return _ptr; }
	const T* operator->() const { return _ptr; }

	bool IsNull() { return _ptr == nullptr; }

private:
	inline void Set(T* ptr)
	{
		if (!ptr && _ptr)
			Release();

		_ptr = ptr;

		if (ptr)
			ptr->AddRef();

	}

	inline void Release()
	{
		if (_ptr != nullptr)
		{
			_ptr->ReleaseRef();
			_ptr = nullptr;
		}
	}

private:
	T* _ptr = nullptr;
};