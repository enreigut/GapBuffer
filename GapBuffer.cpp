#include "GapBuffer.h"

/**
* Gap Buffer constructor. It initializes all the required
* pointer. By default, a size of 10 is given if none is
* specified in the constructor. We allocate size + 1, to
* introduce the '\0'at the end of the gap buffer
* 
* @param size is the size you want the gap buffer start
* with.
*/

GapBuffer::GapBuffer(size_t size)
	: m_size(size + 1)
{
	m_buffer = (char*)malloc(m_size);
	if (m_buffer)
		m_buffer[m_size - 1] = '\0';
	else
		exit(-1);

	m_gap_start = 0;
	m_gap_end = size - 1;
}

/**
* Destructor of the GapBuffer. It just dealloactes and
* frees the memory used by the GapBuffer.
*/
GapBuffer::~GapBuffer()
{
	free(m_buffer);
}

/**
* Inserts a character in the first allowed position of
* the gap buffer
* 
* @param c is the character you want to introduce into
* the gap buffer.
*/
void GapBuffer::Insert(char c)
{
	if (m_gap_start - 1 == m_gap_end)
		Expand();

	m_buffer[m_gap_start++] = c;
}

/**
* Inserts a string (group of chars) in the allowed
* positions of the gap buffer. Instead of iterting
* over each char and call Insert(char c)  we allocate
* enough space for the string and the move the memmory
*
* @param s is the string you want to introduce into
* the gap buffer.
*/
void GapBuffer::Insert(const char* s)
{
	size_t s_length = strlen(s);

	while (s_length > (m_gap_end - (m_gap_start - 1)))
		Expand();

	std::memmove(m_buffer + m_gap_start, s, s_length);
	m_gap_start += s_length;
}


/**
* Moves the gap buffer to the left.
*
* @param position is the amount of chars or positions
* we want to move to the left. Defaults is 1.
*/
void GapBuffer::Left(size_t position)
{
	int new_position = m_gap_start - position;

	if (new_position >= 0)
	{
		std::memmove(m_buffer + (m_gap_end - position + 1), m_buffer + m_gap_start - position, position);
		m_gap_start -= position;
		m_gap_end -= position;
	}
	else
	{
		position -= 1;
		Left(position);
	}
}


/**
* Moves the gap buffer to the right.
*
* @param position is the amount of chars or positions
* we want to move to the right. Defaults is 1.
*/
void GapBuffer::Right(size_t position)
{
	size_t new_position = m_gap_end + position;

	if (new_position < m_size - 1)
	{
		std::memmove(m_buffer + m_gap_start, m_buffer + m_gap_end + 1, position);
		m_gap_start += position;
		m_gap_end += position;
	}
	else
	{
		position -= 1;
		Right(position);
	}
}

/**
* Deletes the chars before the gap. Behaves like a delete.
*
* @param size is the amount of chars we want to delete. 
* Default is 1.
*/
void GapBuffer::DeleteBeforeGap(size_t size)
{
	size_t gap_size = m_gap_end - m_gap_start;
	if (m_gap_start > 0 && gap_size != m_size - 1)
	{
		if ((int)(m_gap_start - size) >= 0)
			m_gap_start -= size;
		else
		{
			size -= 1;
			DeleteBeforeGap(size);
		}
	}
}


/**
* Deletes the chars after the gap. Behaves like a SUPR.
*
* @param size is the amount of chars we want to delete.
* Default is 1.
*/
void GapBuffer::DeleteAfterGap(size_t size)
{
	size_t gap_size = m_gap_end - m_gap_start;
	if (m_gap_end < m_size - 2 && gap_size != m_size - 1)
	{
		if ((int)(m_gap_end + size) < m_size - 1)
			m_gap_end += size;
		else
		{
			size -= 1;
			DeleteAfterGap(size);
		}
	}
}

/**
* Method to print the buffer showing the gap buffer.
*/
void GapBuffer::DebugPrint() const
{
	for (size_t i = 0; i < m_gap_start; i++)
		std::printf("%c", m_buffer[i]);

	for (size_t i = m_gap_start; i <= m_gap_end; i++)
		std::printf(" _ ");

	for (size_t i = m_gap_end + 1; i < m_size - 1; i++)
		std::printf("%c", m_buffer[i]);

	std::printf("\n");
}


/**
* Method to print the buffer as a normal string without
* the gap buffer.
*/
void GapBuffer::Print() const
{
	for (size_t i = 0; i < m_gap_start; i++)
		std::printf("%c", m_buffer[i]);

	for (size_t i = m_gap_end + 1; i < m_size - 1; i++)
		std::printf("%c", m_buffer[i]);

	std::printf("\n");
}

/**
* Method to expand the gap buffer. This is done automatically.
* This method is called when we do not have enought space in
* the gap buffer to insert chars.
*/
void GapBuffer::Expand()
{
	size_t new_size = m_size * 2 - 1;
	char* new_buffer = (char*)malloc(new_size);

	if (new_buffer)
		new_buffer[new_size - 1] = '\0';
	else
		exit(-1);

	std::memmove(new_buffer, m_buffer, m_gap_start);
	std::memmove(new_buffer + (new_size - (m_size - 1 - m_gap_end)), m_buffer + m_gap_end + 1, m_size - 1 - m_gap_end);
	m_gap_end = new_size - 1 - (m_size - 1 - m_gap_end);
	m_size = new_size;
	free(m_buffer);
	m_buffer = new_buffer;
}
