/**
* @file		PcmCallback.cpp
* @brief	�R�[���o�b�N�p�N���X
* @author	yshimada
* @data		20190818
*/

#include "stdafx.h"
#include "PcmCallback.h"

CPcmCallback::CPcmCallback()
{
	m_hBufferEndEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CPcmCallback::~CPcmCallback()
{
	CloseHandle(m_hBufferEndEvent);
}