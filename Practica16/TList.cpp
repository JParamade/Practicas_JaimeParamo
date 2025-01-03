#include "TList.h"
#include "IComparable.h"
#include <string>

TList::TList()
	: m_pIterator(nullptr)
	, m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_uSize(0)
{}

TList::TList(const TList& _rOther)
	: m_pIterator(nullptr) 
	, m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_uSize(0)
{
	TListNode* pTempNode = _rOther.m_pHead;

	while (pTempNode) {
		Push(*(pTempNode->m_pData));
		pTempNode = pTempNode->m_pNext;
	}
}

TList::~TList() { Reset(); }

TList::TListNode::TListNode(const IComparable& _rData)
	: m_pData(_rData.Clone())
	, m_pNext(nullptr)
{}

TList::TListNode::~TListNode() { delete m_pData; }

int TList::Size() const { return m_uSize; }

int TList::Push(const IComparable& _rData) {
	TListNode* pNewNode = new TListNode(_rData);

	if (!m_pHead) m_pHead = m_pTail = pNewNode;
	else {
		m_pTail->m_pNext = pNewNode;
		m_pTail = pNewNode;
	}

	m_pIterator = m_pHead;
	m_uSize++;
	return m_uSize;
}

IComparable* TList::First() {
	if (m_pHead) {
		m_pIterator = m_pHead;

		return m_pHead->m_pData;
	}
	else return nullptr;
}

IComparable* TList::Next() {
	if (m_pIterator && m_pIterator->m_pNext) {
		m_pIterator = m_pIterator->m_pNext;

		return m_pIterator->m_pData;
	}
	else return nullptr;
}

IComparable*TList::Pop() {
	if (!m_pHead) return nullptr;

	TListNode* pTempNode = m_pHead;

	IComparable* pTempData = pTempNode->m_pData->Clone();

	m_pHead = m_pHead->m_pNext;

	delete pTempNode;

	m_uSize--;
	return pTempData;
}

void TList::Reset() {
	while (m_pHead) Pop();
	m_pTail = m_pIterator = nullptr;
}

TList TList::GetReverseList() const {
	TList lTempList;

	TListNode* pCurrentNode = m_pHead;

	while (pCurrentNode) {
		TListNode* pNewNode = new TListNode(*(pCurrentNode->m_pData));

		pNewNode->m_pNext = lTempList.m_pHead;
		lTempList.m_pHead = pNewNode;

		if (!lTempList.m_pTail) lTempList.m_pTail = pNewNode;

		lTempList.m_uSize++;
		pCurrentNode = pCurrentNode->m_pNext;
	}

	return lTempList;
}