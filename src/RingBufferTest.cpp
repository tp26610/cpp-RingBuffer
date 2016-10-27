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

test(overRead) {
	const int bufferLength = 10;
	RingBuffer<short> buffer(bufferLength);

	const int writeLength = 5;
	short writeBuffer[writeLength];
	for(int i = 0; i < writeLength; i++) {
		writeBuffer[i] = i;
	}
	int writeCount = buffer.write(writeBuffer, writeLength);

	ASSERT_EQ(writeLength, writeCount);

	const int readLength = 10;
	short readBuffer[readLength] = {};
	int readCount = buffer.read(readBuffer, readLength);

	ASSERT_EQ(5, readCount);

	// assert elements in buffer.
	for(int i = 0; i < writeLength; i++) {
		ASSERT_EQ(i, readBuffer[i]) << "assert elements wrong. i=" << i;
	}

	ASSERT_TRUE(buffer.isEmpty());
}

test(recursive) {
	const int bufferLength = 6;
	RingBuffer<short> buffer(bufferLength);

	const int writeLength = 3;
	short writeBuffer1[] = {0, 1, 2};
	short writeBuffer2[] = {3, 4, 5};
	short writeBuffer3[] = {6, 7, 8};

	short readBuffer[200] = {};

	// write elements
	int writeCount = buffer.write(writeBuffer1, writeLength);
	ASSERT_EQ(3, writeCount);

	// now elements in buffer -> [ 0 1 2 ]

	// read elements
	int readCount = buffer.read(readBuffer, 1);
	ASSERT_EQ(1, readCount);
	ASSERT_EQ(0, readBuffer[0]);

	// now elements in buffer -> [ 1 2 ]

	// write elements
	writeCount = buffer.write(writeBuffer2, writeLength);
	ASSERT_EQ(3, writeCount);

	// now elements in buffer -> [ 1 2 3 4 5 ]

	// read elements
	readCount = buffer.read(readBuffer, 4);
	ASSERT_EQ(4, readCount);
	ASSERT_EQ(1, readBuffer[0]);
	ASSERT_EQ(2, readBuffer[1]);
	ASSERT_EQ(3, readBuffer[2]);
	ASSERT_EQ(4, readBuffer[3]);

	// now elements in buffer -> [ 5 ]

	// write elements
	writeCount = buffer.write(writeBuffer3, writeLength);
	ASSERT_EQ(3, writeCount);

	// now elements in buffer -> [ 5 6 7 8]

	// read elements
	readCount = buffer.read(readBuffer, 4);
	ASSERT_EQ(4, readCount);
	ASSERT_EQ(5, readBuffer[0]);
	ASSERT_EQ(6, readBuffer[1]);
	ASSERT_EQ(7, readBuffer[2]);
	ASSERT_EQ(8, readBuffer[3]);

}
