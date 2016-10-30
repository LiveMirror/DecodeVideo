
// RenderFilterGDIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderFilterGDI.h"
#include "RenderFilterGDIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRenderFilterGDIDlg �Ի���



CRenderFilterGDIDlg::CRenderFilterGDIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenderFilterGDIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderFilterGDIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRenderFilterGDIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRenderFilterGDIDlg ��Ϣ�������

BOOL CRenderFilterGDIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	HRESULT hr;
	m_decoder = new CDecoder(L"E:\\pump it.avi", &hr);
	m_decoder->SetOnPresent(std::bind(&CRenderFilterGDIDlg::OnPresent, this, std::placeholders::_1));

	m_decoder->GetVideoSize(m_videoSize);
	m_dc.Create(m_videoSize.cx, m_videoSize.cy, 32);

	m_decoder->RunVideo();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRenderFilterGDIDlg::OnPaint()
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
HCURSOR CRenderFilterGDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRenderFilterGDIDlg::OnDestroy()
{
	CDialog::OnDestroy();

	delete m_decoder;

	CoUninitialize();
}

void CRenderFilterGDIDlg::OnPresent(IMediaSample* mediaSample)
{
	BYTE* sampleBuf = NULL;
	if (FAILED(mediaSample->GetPointer(&sampleBuf)))
		return;
	
	// ����ÿ��֮��û�ж�����ֽ�
	ASSERT(mediaSample->GetActualDataLength() == m_videoSize.cx * m_videoSize.cy * 4);
	m_dcLock.Lock();
	// RGBλͼ���Ǵ��µ��ϴ����
	memcpy(m_dc.GetPixelAddress(0, m_videoSize.cy - 1), sampleBuf, m_videoSize.cx * m_videoSize.cy * 4);
	m_dcLock.Unlock();

	Invalidate(FALSE);
}
