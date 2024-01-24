#pragma once
#include <string>

class UNameObject
{
public:
	UNameObject();
	~UNameObject();

	UNameObject(const UNameObject& _Other) = delete;
	UNameObject(UNameObject&& _Other) noexcept = delete;
	UNameObject& operator=(const UNameObject& _Other) = delete;
	UNameObject& operator=(UNameObject&& _Other) noexcept = delete;

	std::string GetName()
	{
		return Name;
	}

	void SetName(std::string_view _View)
	{
		Name = _View;
	}

protected:

private:
	std::string Name;
};
