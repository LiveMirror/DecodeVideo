
// RenderFilterGDIDlg.h : ͷ�ļ�
//

#pragma once
#include "Decoder.h"


// CRenderFilterGDIDlg �Ի���
class CRenderFilterGDIDlg : public CDialog
{
// ����
public:
	CRenderFilterGDIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RENDERFILTERGDI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	void OnPresent(IMediaSample* mediaSample);


	CDecoder* m_decoder = NULL;

	SIZE m_videoSize;
	CImage m_dc;
	CCriticalSection m_dcLock;
};
