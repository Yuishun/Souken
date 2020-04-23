#pragma once
#define __IGAMEOBJECT_H__

struct ID2D1RenderTarget;

class IGameObject
{
public:
	virtual ~IGameObject() = 0;
	virtual bool move() = 0;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) = 0;

	//	当たり判定関連
	virtual bool collide(float x, float y, float w, float h) {
		return false;
	}
	virtual bool collide(float x, float y, float w, float h, int id) {	//	ブロックとの判定用
		return false;
	}
	virtual bool collide(IGameObject *pObj) {
		return false;
	}

	virtual void damage(float amount) {};

	virtual float GetX() const { return 0.f; }
	virtual float GetY() const { return 0.f; }
	virtual float GetWidth() const { return 0.f; }
	virtual float GetHeight() const { return 0.f; }
	virtual void SetX(float x) {};
	virtual void SetY(float y) {};
	virtual void SetJumpFlag() {};
	virtual void ResetGravityFlag() {};

	virtual int GetID() const { return -1; }
};

//  マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }

#define GRAVITY 1.f

//	重力フラグ
#define GFLG_DOWN	0x0000	//	重力下向き = ブロックの上
#define GFLG_UP		0x0001	//	重力上向き = ブロックの下
#define GFLG_LEFT	0x0002	//	重力左向き = ブロックの右
#define GFLG_RIGHT	0x0003	//	重力右向き = ブロックの左
//	状態フラグ
#define SFLG_JUMP	0x0020	//	空中
#define SFLG_GROUND	0x0040	//	接地