
// FFmpegGDIDlg.h : ͷ�ļ�
//

#pragma once
#include "Decoder.h"


// CFFmpegGDIDlg �Ի���
class CFFmpegGDIDlg : public CDialog
{
// ����
public:
	CFFmpegGDIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FFMPEGGDI_DIALOG };

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

	void OnPresent(BYTE* data);


	CDecoder* m_decoder = NULL;

	SIZE m_videoSize;
	CImage m_dc;
	CCriticalSection m_dcLock;
};
