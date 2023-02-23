# Gap Buffer

## Summary

Small `.h`and `.cpp` files to implement a custom GapBuffer. This gap buffer has a dynamic memory increase.

Default size is 10, but you can change it to whatever you want. Increase is done multiplying by 2 the size.

The implemented methods are:

	- void Insert(char c);
	- void Insert(const char* s);
	- void Left(size_t position = 1);
	- void Right(size_t position = 1);
	- void DeleteBeforeGap(size_t size = 1);
	- void DeleteAfterGap(size_t size = 1);
	- void DebugPrint() const;
	- void Print() const;
	- char* SetBuffer(char* buffer);

A quick example on how to implement and use the GapBuffer class:

```
#include "GapBuffer.h"

int main()
{
	GapBuffer* gapBuffer = new GapBuffer;

	gapBuffer->Insert("Hello World!");
	gapBuffer->Print();

	return 0;
}
```