/*
 * RingBuffer.h
 *
 *  Created on: Feb 18, 2016
 *      Author: ntut
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <iostream>
using namespace std;

template <class T>
class RingBuffer {

private:
	T *mBuffer;
	int mBufferLength;
	int mReadIndex;
	int mWriteIndex;

	int nextIndex(int nowIndex) {
		nowIndex ++;
		nowIndex %= mBufferLength;
		return nowIndex;
	} // nextIndex

public:

	RingBuffer(int length) {
		mBufferLength = length + 1;
		mBuffer = new T[mBufferLength];
		mReadIndex = 0;
		mWriteIndex = 0;
	} // RingBuffer(int length)

	virtual ~RingBuffer() {
		delete[] mBuffer;
	} // virtual ~RingBuffer()

	int write(T *in, int length) {
		int writeCount;
		for(writeCount = 0; writeCount < length; writeCount++) {
			if(isFull())
				break;
			mBuffer[mWriteIndex] = in[writeCount];
			mWriteIndex = nextIndex(mWriteIndex);
		}
		return writeCount;
	} // int write(T *in, int length)

	int read(T *out, int length) {
		int readCount;
		for(readCount = 0; readCount < length; readCount++) {
			if(isEmpty())
				break;
			out[readCount] = mBuffer[mReadIndex];
			mReadIndex = nextIndex(mReadIndex);
		}
		return readCount;
	} // int read(T *out, int length)

	bool isFull() {
		int nextWriteIndex = nextIndex(mWriteIndex);
		return nextWriteIndex == mReadIndex;
	}

	bool isEmpty() {
		return mWriteIndex == mReadIndex;
	}

	int getRemainingLength() {
		int dataLength = mWriteIndex - mReadIndex;
		if(dataLength < 0)
			dataLength += mBufferLength;
		return (mBufferLength-1) - getDataLength();
	}

	int getDataLength() {
		int dataLength = mWriteIndex - mReadIndex;
		if(dataLength < 0)
			dataLength += mBufferLength;
		return dataLength;
	}
}; // class RingBuffer

#endif /* RINGBUFFER_H_ */
