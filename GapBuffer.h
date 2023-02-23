/**
 * @file GapBuffer.h
 *
 * @brief This file defines the interface for a
 * dynamic Gap Buffer. This gap buffer initialise
 * by default with a size of 10, and each time it
 * is needed to increase the size, it doubles this
 * size.
 *
 * @author Enrique Reina Gutierrez
 *
 */

#pragma once

#include <iostream>
#include <stdio.h>

class GapBuffer
{
public:

	GapBuffer(size_t size = 10);
	~GapBuffer();

	void Insert(char c);
	void Insert(const char* s);
	void Left(size_t position = 1);
	void Right(size_t position = 1);
	void DeleteBeforeGap(size_t size = 1);
	void DeleteAfterGap(size_t size = 1);
	void DebugPrint() const;
	void Print() const;

private:

	void Expand();

private:
	size_t m_size = 0;
	char* m_buffer;
	size_t m_gap_start;
	size_t m_gap_end;
};
