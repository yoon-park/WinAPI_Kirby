#pragma once

class AFire
{
public:
	AFire();
	~AFire();

	AFire(const AFire& _Other) = delete;
	AFire(AFire&& _Other) noexcept = delete;
	AFire& operator=(const AFire& _Other) = delete;
	AFire& operator=(AFire&& _Other) noexcept = delete;

protected:

private:

};