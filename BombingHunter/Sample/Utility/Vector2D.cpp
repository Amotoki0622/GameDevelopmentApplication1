#include "Vector2D.h"
#include <math.h>

//コンストラクタ(生成時に呼び出される)
Vector2D::Vector2D() : x(0.0f), y(0.0f)			//初期子リスト
{

}

Vector2D::Vector2D(float scalar) : x(scalar), y(scalar)
{

}

Vector2D::Vector2D(float mx, float my) : x(mx), y(my)
{

}

//デストラクタ(解体時に呼び出される)
Vector2D::~Vector2D()
{

}

//代入処理を演算子にオーバーロードしています。
Vector2D& Vector2D::operator= (const Vector2D& location)
{
	//自身のメンバ関数xに引数の値を代入する
	this->x = location.x;
	//自身のメンバ関数yに引数の値を代入する
	this->y = location.y;

	//自分自身を返す
	return *this;
}

//加算処理
const Vector2D Vector2D::operator+(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x + location.x;
	result.y = this->y + location.y;

	return result;
}

//自己代入(加算)
Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	//加算代入する
	this->x += location.x;
	this->y += location.y;

	//自分自身を返す
	return *this;
}

const Vector2D Vector2D::operator-(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

Vector2D& Vector2D::operator-=(const Vector2D& location)
{
	this->x -= location.x;
	this->y -= location.y;

	return *this;
}

const Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

const Vector2D Vector2D::operator*(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
	this->x *= scalar;
	this->y *= scalar;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& location)
{
	this->x *= location.x;
	this->y *= location.y;

	return *this;
}

const Vector2D Vector2D::operator/(const float& scalar) const
{
	if (fabsf(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / scalar, this->y / scalar);
}

const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / location.x, this->y / location.y);
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	if (fabsf(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= scalar;
		this->y /= scalar;
	}

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	if ((fabs(location.x) < 1e-6f) || (fabs(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}

	return *this;
}

void Vector2D::ToInt(int* x, int* y) const
{
	*x = static_cast<int> (this->x);
	*y = static_cast<int> (this->y);
}