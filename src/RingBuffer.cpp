/*
 * RingBuffer.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: ntut
 */

#include "RingBuffer.h"



template <class T>
RingBuffer<T>::RingBuffer(int length) {
	mBufferLength = length + 1;
	mBuffer = new T[mBufferLength];
	mReadIndex = 0;
	mWriteIndex = 0;
}

template <class T>
RingBuffer<T>::~RingBuffer() {
	delete[] mBuffer;
}

template <class T>
int RingBuffer<T>::write(T *in, int length) {
	int writeCount;
	for(writeCount = 0; writeCount < length; writeCount++) {
		if(isFull())
			break;
		mBuffer[mWriteIndex] = in[writeCount];
		mWriteIndex = getNextIndex(mWriteIndex);
	}
	return writeCount;
}

template <class T>
int RingBuffer<T>::read(T *out, int length) {
	int readCount;
	for(readCount = 0; readCount < length; readCount++) {
		out[readCount] = mBuffer[mReadIndex];
		mReadIndex = getNextIndex(mReadIndex);
	}
	return readCount;
}

template <class T>
int RingBuffer<T>::getNextIndex(int nowIndex) {
	nowIndex ++;
	nowIndex %= mBufferLength;
	return nowIndex;
}

template <class T>
bool RingBuffer<T>::isFull() {
	int nextWriteIndex = getNextIndex(mWriteIndex);
	return nextWriteIndex == mReadIndex;
}

template <class T>
bool RingBuffer<T>::isEmpty() {
	return mWriteIndex == mReadIndex;
}

template <class T>
int RingBuffer<T>::getRemainingLength() {
	int dataLength = mWriteIndex - mReadIndex;
	if(dataLength < 0)
		dataLength += mBufferLength;
	return (mBufferLength-1) - getDataLength();
}

template <class T>
int RingBuffer<T>::getDataLength() {
	int dataLength = mWriteIndex - mReadIndex;
	if(dataLength < 0)
		dataLength += mBufferLength;
	return dataLength;
}

template class RingBuffer<short>;



