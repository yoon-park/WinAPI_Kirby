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
	bool Create(UWindowImage* _Image, const FVector& _Scale);
	bool Load(UWindowImage* _Image);

	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _CopyTrans, const FTransform& _ImageTrans, Color8Bit _Color = Color8Bit::Black);

protected:

private:
	HDC ImageDC = 0;
	HBITMAP hBitMap = 0;
	BITMAP BitMapInfo = BITMAP();
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	bool Create(HDC _MainDC);
};