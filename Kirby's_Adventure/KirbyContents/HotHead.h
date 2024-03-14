#pragma once

class AHotHead
{
public:
	AHotHead();
	~AHotHead();

	AHotHead(const AHotHead& _Other) = delete;
	AHotHead(AHotHead&& _Other) noexcept = delete;
	AHotHead& operator=(const AHotHead& _Other) = delete;
	AHotHead& operator=(AHotHead&& _Other) noexcept = delete;

protected:

private:

};