#pragma once
#include "Allocator.h"

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	// memory allocation
	Type* memory = static_cast<Type*>(xalloc(sizeof(Type)));

	// constructor
	new(memory)Type(std::forward<Args>(args)...);
	
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	xrelease(obj);
}