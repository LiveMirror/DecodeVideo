
// FFmpegGDIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFmpegGDI.h"
#include "FFmpegGDIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFmpegGDIDlg �Ի���



CFFmpegGDIDlg::CFFmpegGDIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFFmpegGDIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFFmpegGDIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFFmpegGDIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CFFmpegGDIDlg ��Ϣ�������

BOOL CFFmpegGDIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	av_register_all();

	m_decoder = new CDecoder("E:\\pump it.avi");
	m_decoder->SetOnPresent(std::bind(&CFFmpegGDIDlg::OnPresent, this, std::placeholders::_1));

	m_decoder->GetVideoSize(m_videoSize);
	m_dc.Create(m_videoSize.cx, m_videoSize.cy, 32);

	m_decoder->Run();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFFmpegGDIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialog::OnPaint();

		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		m_dcLock.Lock();
		m_dc.StretchBlt(dc, rect);
		m_dcLock.Unlock();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFFmpegGDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFFmpegGDIDlg::OnDestroy()
{
	CDialog::OnDestroy();

	delete m_decoder;
}

void CFFmpegGDIDlg::OnPresent(BYTE* data)
{
	m_dcLock.Lock();
	// RGBλͼ���Ǵ��µ��ϴ���ģ�data����
	for (int y = 0; y < m_videoSize.cy; y++)
	{
		memcpy(m_dc.GetPixelAddress(0, y), data, m_videoSize.cx * 4);
		data += m_videoSize.cx * 4;
	}
	m_dcLock.Unlock();

	Invalidate(FALSE);
}
