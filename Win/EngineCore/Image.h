#pragma once

class UImage
{
public:
	UImage();
	~UImage();

	UImage(const UImage& _Other) = delete;
	UImage(UImage&& _Other) noexcept = delete;
	UImage& operator=(const UImage& _Other) = delete;
	UImage& operator=(UImage&& _Other) noexcept = delete;

protected:

private:

};