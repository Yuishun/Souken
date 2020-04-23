/**
* @file		PcmCallback.cpp
* @brief	コールバック用クラス
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