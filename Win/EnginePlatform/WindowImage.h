#pragma once
#include <Windows.h>

#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <EngineBase\PathObject.h>

enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class ImageInfo
{
public:
	HDC ImageDC = nullptr;
	HBITMAP hBitMap;
	FTransform CuttingTrans;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
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

	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

	FVector GetScale();

	bool Load(UWindowImage* _Image);
	bool LoadFolder(UWindowImage* _Image);

	bool Create(UWindowImage* _Image, const FVector& _Scale);
	void Cutting(int _X, int _Y);

	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);
	void AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);

protected:

private:
	HDC ImageDC = 0;
	HBITMAP hBitMap = 0;
	BITMAP BitMapInfo = BITMAP();
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	std::vector<ImageInfo> Infos;

	bool Create(HDC _MainDC);
};