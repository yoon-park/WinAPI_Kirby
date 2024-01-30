#pragma once
#include <Windows.h>

#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <EngineBase\PathObject.h>

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UEngineWindow;

class UWindowImage : public UPathObject
{
	friend UEngineWindow;

public:
	UWindowImage();
	~UWindowImage();

	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	FVector GetScale();
	bool Load(UWindowImage* _Image);
	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);

protected:

private:
	HDC ImageDC = 0;
	HBITMAP hBitMap = 0;
	BITMAP BitMapInfo = BITMAP();
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	bool Create(HDC _MainDC);
};