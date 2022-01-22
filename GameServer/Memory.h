#pragma once
#include "Allocator.h"

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	// memory allocation
	Type* memory = static_cast<Type*>(BaseAllocator::Alloc(sizeof(Type)));

	// constructor
	new(memory)Type(args);
	
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	BaseAllocator::Release(obj);
}