/*
	Code taken from
	http://www.codeguru.com/cpp/g-m/gdi/capturingimages/article.php/c11231/Capturing-Windows-Regardless-of-Their-ZOrder.htm

	According to Codeguru:
	As you know, this site is a valuable resource for the developer community. 
	Please note, however, that to avoid legal complications, 
	we need to obtain your permission to use any computer code and any related materials ("resources") that you are providing to us. 
	Accordingly, by submitting any such resource to CodeGuru via email or the site, you grant to QuinStreet a worldwide, 
	nonexclusive, transferable, sublicensable (through multiple tiers), royalty-free, perpetual, irrevocable right and license, 
	without compensation to you; to use, reproduce, distribute, adapt (including without limitation edit, modify, translate, and reformat), 
	create derivative works of, transmit, publicly display, publicly perform, and sublicense the submitted resource (in both object 
	and source code formats, as well as on and off the Web), and you acknowledge that you have the authority to grant such rights to 
	QuinStreet. We request this waiver to help ensure that we have all the rights we may need to provide the Services available through this site.

	By submitting the resource, you also grant your article's readers the permission to use any source code in the resource for commercial 
	or noncommercial software. Please note that you retain ownership of any copyright in any resources submitted!

	ALSO, IN MAKING THE RESOURCE AVAILABLE TO OTHER SITE VISITORS FOR DOWNLOADING, QUINSTREET WILL INFORM SUCH OTHER VISITORS THAT, ALTHOUGH 
	THEY MAY DOWNLOAD ANY RESOURCES FOR COMMERCIAL OR NONCOMMERCIAL USES, THEY MAY NOT REPUBLISH THE SOURCE CODE SO THAT IT IS ACCESSIBLE 
	TO THE PUBLIC WITHOUT FIRST OBTAINING THE COPYRIGHT OWNER'S PERMISSION.

	We (CodeGuru and QuinStreet) have no control over, and shall have no liability for, any damages resulting from the use (including without 
	limitation republication) or misuse by any third party of information voluntarily made public through any other part of the site. IF YOU 
	CHOOSE TO MAKE ANY OF YOUR PERSONALLY IDENTIFIABLE FOR OTHER INFORMATION PUBLICLY AVAILABLE IN A SUBMISSION, YOU DO SO AT YOUR OWN RISK.
*/

#include "BlueFramework/ImageProcessing/captureScreen.h"

#include <Windows.h>
#include <stdio.h>

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

namespace Internal {
	void saveBmpToFile(const char *filename, int W, int H, int Bpp, int *lpBits) {
		BITMAPINFO Bmi = {0};
		Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		Bmi.bmiHeader.biWidth = W;
		Bmi.bmiHeader.biHeight = H;
		Bmi.bmiHeader.biPlanes = 1;
		Bmi.bmiHeader.biBitCount = Bpp;
		Bmi.bmiHeader.biCompression = BI_RGB;
		Bmi.bmiHeader.biSizeImage = W * H * Bpp / 8;

		FILE *fp = fopen(filename, "wb");
		if (fp == 0)
			return;
		int h = Bmi.bmiHeader.biHeight;
		int w = Bmi.bmiHeader.biWidth;
		Bmi.bmiHeader.biHeight = -h;
		Bmi.bmiHeader.biWidth = w;

		BITMAPFILEHEADER bfh = {0};
		bfh.bfType = ('M' << 8) + 'B';
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bfh.bfSize = Bmi.bmiHeader.biSizeImage + bfh.bfOffBits;

		fwrite(&bfh, sizeof(bfh), 1, fp);
		fwrite(&Bmi.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(lpBits, Bmi.bmiHeader.biSizeImage, 1, fp);
		fclose(fp);
	}

	void get24BitBmp(const int &nWidth, const int &nHeight, const HBITMAP &hBitmap, BYTE *lpDesBits) {
		HDC hDC = ::GetDC(0);

		HDC memDC1 = ::CreateCompatibleDC(hDC);
		HDC memDC2 = ::CreateCompatibleDC(hDC);

		BYTE *lpBits = NULL;

		BITMAPINFO bmi;
		::ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = nWidth;
		bmi.bmiHeader.biHeight = nHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;

		HBITMAP hDIBMemBM = ::CreateDIBSection(0, &bmi, DIB_RGB_COLORS, (void **)&lpBits, NULL, NULL);

		HBITMAP hOldBmp1 = (HBITMAP)::SelectObject(memDC1, hDIBMemBM);

		HBITMAP hOldBmp2 = (HBITMAP)::SelectObject(memDC2, hBitmap);

		::BitBlt(memDC1, 0, 0, nWidth, nHeight, memDC2, 0, 0, SRCCOPY);

		for (int i = 0; i < nHeight; i++)
			::CopyMemory(&lpDesBits[i * 3 * nWidth], &lpBits[nWidth * 3 * (nHeight - 1 - i)], nWidth * 3);

		// clean up
		::SelectObject(memDC1, hOldBmp1);
		::SelectObject(memDC2, hOldBmp2);
		::ReleaseDC(0, hDC);
		::DeleteObject(hDIBMemBM);
		::DeleteObject(hOldBmp1);
		::DeleteObject(hOldBmp2);
		::DeleteDC(memDC1);
		::DeleteDC(memDC2);
	}

	void captureScreen(const char *filename) {
		RECT rc;
		HWND hWnd = ::GetDesktopWindow();
		::GetWindowRect(hWnd, &rc);

		int Width = rc.right - rc.left;
		int Height = rc.bottom - rc.top;

		HDC hDC = ::GetDC(0);
		HDC memDC = ::CreateCompatibleDC(hDC);
		HBITMAP memBM = ::CreateCompatibleBitmap(hDC, Width, Height);
		HBITMAP OldBM = (HBITMAP)::SelectObject(memDC, memBM);
		::BitBlt(memDC, 0, 0, Width, Height, hDC, rc.left, rc.top, SRCCOPY);

		int Bpp = ::GetDeviceCaps(hDC, BITSPIXEL);
		int size = Bpp / 8 * (Width * Height);
		BYTE *lpBits1 = new BYTE[size];
		::GetBitmapBits(memBM, size, lpBits1);

		HBITMAP hBmp = ::CreateBitmap(Width, Height, 1, Bpp, lpBits1);

		BYTE *lpBits2 = new BYTE[Width * Height * 3];

		get24BitBmp(Width, Height, hBmp, lpBits2);

		saveBmpToFile(filename, Width, Height, 24, (int *)lpBits2);

		delete[] lpBits1;
		delete[] lpBits2;
		::SelectObject(hDC, OldBM);
		::DeleteObject(memBM);
		::DeleteObject(hBmp);
		::DeleteDC(memDC);
		::ReleaseDC(0, hDC);
	}
} // namespace Internal

void captureScreen(const char *filename) {
	Internal::captureScreen(filename);
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END