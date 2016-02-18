#

#include <gtest/gtest.h>

#define CLASS_NAME RingBuffer
#define test(caseName) TEST(CLASS_NAME, caseName)

#include "RingBuffer.h"



test(writeAndReadOneElement) {

	RingBuffer<short> buffer(1000);

	short writeBuffer[] = {123};
	int writeCount = buffer.write(writeBuffer, 1);
	ASSERT_EQ(1, writeCount);

	short readBuffer[1] = {};
	int readCount = buffer.read(readBuffer, 1);
	ASSERT_EQ(1, readCount);

	ASSERT_EQ(123, readBuffer[0]) << "read value is wrong.";
}

test(isFull) {
	const int bufferLength = 1000;
	RingBuffer<short> buffer(bufferLength);

	short writeBuffer[bufferLength] = {};
	for(int i = 0; i < bufferLength; i++) {
		writeBuffer[i] = i;
	}
	buffer.write(writeBuffer, bufferLength);

	ASSERT_TRUE(buffer.isFull());

	// assert value in the buffer
	short readBuffer[bufferLength] = {};
	buffer.read(readBuffer, bufferLength);
	for(int i = 0; i < bufferLength; i++) {
		ASSERT_EQ(i, readBuffer[i]) << "assert elements wrong. i=" << i;
	}
}

test(isEmpty) {
	RingBuffer<short> buffer(1024);
	ASSERT_TRUE(buffer.isEmpty());
}

test(getRemainingLength) {
	const int bufferLength = 1000;
	RingBuffer<short> buffer(bufferLength);

	const int writeLength = 302;
	short writeBuffer[writeLength];
	buffer.write(writeBuffer, writeLength);

	ASSERT_EQ(698, buffer.getRemainingLength());
}

test(getDataLength) {
	const int bufferLength = 1000;
	RingBuffer<short> buffer(bufferLength);

	const int writeLength = 302;
	short writeBuffer[writeLength];
	buffer.write(writeBuffer, writeLength);

	ASSERT_EQ(302, buffer.getDataLength());
}

test(overWrite) {
	const int bufferLength = 10;
	RingBuffer<short> buffer(bufferLength);

	const int writeLength = 11;
	short writeBuffer[writeLength];
	for(int i = 0; i < writeLength; i++) {
		writeBuffer[i] = i;
	}
	int writeCount = buffer.write(writeBuffer, writeLength);

	ASSERT_EQ(bufferLength, writeCount) << "bufferLength=" << bufferLength << " writeCount=" << writeCount;
	ASSERT_EQ(bufferLength, buffer.getDataLength());

	// assert elements in buffer.
	short readBuffer[bufferLength] = {};
	buffer.read(readBuffer, bufferLength);
	for(int i = 0; i < buffer.getDataLength(); i++) {
		ASSERT_EQ(i, readBuffer[i]) << "assert elements wrong. i=" << i;
	}
}
