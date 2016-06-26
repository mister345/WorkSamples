#pragma once
#include <array>
#include "PolyClosed.h"
#include "Camera.h"
#include "CollidableCircle.h"
#include "Vertex.h"

class Ship : public CollidableCircle
{
public:
	class Drawable : public ::Drawable
	{
	public:
		Drawable( const Ship& parent )
			:
			parent( parent )
		{
			Transform( Mat3::Translation( parent.pos ) * Mat3::Rotation( parent.angle ) );
		}
		virtual void Rasterize( D3DGraphics& gfx ) const override
		{
            std::array<Vertex, 4> quadTrans;
            for (int i = 0; i < 4; i++)
            {
                quadTrans[i].t = parent.quad[i].t;
                quadTrans[i].v = trans * parent.quad[i].v;
            }

            gfx.DrawTriangleTex(
                quadTrans[0], quadTrans[1], quadTrans[3],
                clip, parent.shipTexture);
            gfx.DrawTriangleTex(
                quadTrans[1], quadTrans[2], quadTrans[3],
                clip, parent.shipTexture);

			const Vec2 shieldCenter = trans * Vec2 { 0.0f,0.0f };
			gfx.DrawCircle( shieldCenter,parent.shieldRadius,parent.shieldColor );
		}
	private:
		const Ship& parent;
	};
public:
	Ship( std::string filename,Vec2 pos = {0.0f,0.0f} )
		:
		pos( pos ),
shipTexture(Surface::FromFile(L"Ship.png"))
    {
        //quad[0].v = { -80.0f, -135.0f };
        //quad[0].t = { 0.0f, 0.0f };
        //quad[1].v = { 79.0f, -135.0f };
        //quad[1].t = { 159.0f, 0.0f };
        //quad[2].v = { 79.0f, 134.0f };
        //quad[2].t = { 159.0f, 269.0f };
        //quad[3].v = { -80.0f, 134.0f };
        //quad[3].t = { 0.0f, 269.0f };

// Load image file with specified dimensions (half size)
        quad[0].v = { -40.0f, -67.0f };
        quad[0].t = { 0.0f, 0.0f };
        quad[1].v = { 39.0f, -67.0f };
        quad[1].t = { 79.0f, 0.0f };
        quad[2].v = { 39.0f, 67.0f };
        quad[2].t = { 79.0f, 134.0f };
        quad[3].v = { -40.0f, 67.0f };
        quad[3].t = { 0.0f, 134.0f };
    }
	Drawable GetDrawable() const
	{
		return Drawable( *this );
	}
	void Update( float dt )
	{
		// angular (1st order then 0th order)
		if( angAccelDir == 0.0f )
		{
			if( abs( angVel ) <= angAccel * dt )
			{
				angVel = 0.0f;
			}
			else
			{
				angVel -= copysign( angAccel,angVel ) * dt;
			}
		}
		angVel += angAccel * angAccelDir * dt;
		angle += angVel * dt;
		// clamp angle to within 2pi
		angle = fmodf( angle,2.0f * PI );

		// linear (1st order then 0th order)
		vel += Vec2 { 0.0f,-1.0f }.Rotation( angle ) * accel * thrust * dt;
		pos += vel * dt;
	}
	void FocusOn( Camera& cam ) const
	{
		cam.MoveTo( pos );
	}
	// control functions
	void Thrust()
	{
		thrust = 1.0f;
	}
	void StopThrusting()
	{
		thrust = 0.0f;
	}
	void Spin( float dir )
	{
		angAccelDir = dir;
	}
	void StopSpinning( float dir )
	{
		if( angAccelDir == dir )
		{
			angAccelDir = 0.0f;
		}
	}
	// collidable interface
	virtual RectF GetAABB() const override
	{
		return RectF( pos.y - shieldRadius,pos.y + shieldRadius,
			pos.x - shieldRadius,pos.x + shieldRadius );
	}
	virtual Vec2 GetCenter() const override
	{
		return pos;
	}
	virtual float GetRadius() const override
	{
		return (float)shieldRadius;
	}
	virtual Vec2 GetVel() const override
	{
		return vel;
	}
	virtual void Rebound( Vec2 normal ) override
	{
		vel -= normal * ( vel * normal ) * 2.0f;
	}


private:
	// structural
    Surface shipTexture;
    std::array<Vertex, 4> quad;
	const int shieldRadius = 80;
	const Color shieldColor = GREEN;

	// linear
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	const float accel = 0.2f * 60.0f * 60.0f;
	float thrust = 0.0f;

	// angular
	float angle = 0.0f;
	float angVel = 0.0f;
	const float angAccel = 0.002f * 60.0f * 60.0f;
	float angAccelDir = 0.0f;
};