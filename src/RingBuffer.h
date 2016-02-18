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

	int nextIndex(int nowIndex);
public:
	RingBuffer(int length);
	virtual ~RingBuffer();
	int write(T *in, int length);
	int read(T *out, int length);
	bool isFull();
	bool isEmpty();
	int getRemainingLength();
	int getDataLength();
};

#endif /* RINGBUFFER_H_ */
