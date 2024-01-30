#include "WindowImage.h"

#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage()
{
}

UWindowImage::~UWindowImage()
{
	DeleteObject(hBitMap);
	DeleteDC(ImageDC);
}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (ImageDC == nullptr)
	{
		return false;
	}

	return true;
}

bool UWindowImage::Load(UWindowImage* _Image)
{
	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (UpperExt == ".BMP")
	{
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	else if (UpperExt == ".PNG")
	{
		ULONG_PTR gdiplusToken = 0;
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);

		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);

		if (stat != Gdiplus::Status::Ok)
		{
			MsgBoxAssert("Png ���� ���ҽ� �ε忡 �����߽��ϴ�.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	ImageDC = CreateCompatibleDC(_Image->ImageDC);
	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, FTransform _Trans)
{
	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->ImageDC;

	BitBlt(
		hdc, 						
		_Trans.iLeft(),
		_Trans.iTop(),
		_Trans.GetScale().iX(),
		_Trans.GetScale().iY(),
		hdcSrc,
		0,
		0,
		SRCCOPY
	);
}