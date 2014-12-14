#pragma once

#include <gl/glut.h>
#include "Vector3D.h"

class Camera
{
private:
	Point3D world_pos;
	Point3D view_point;
	Vector3D view_vector;
	Vector3D up_vector;

public:
	Camera()
	{
		setPosition(Point3D(0.0f, 0.0f, 0.0f));
		view_vector.Set(0.0f, 0.0f, 1.0f);
		up_vector.Set(0.0f, 1.0f, 0.0f);
	}

	~Camera()
	{

	}

	const Point3D getPosition(void)
	{
		return world_pos;
	}

	void setPosition(const Point3D& pos)
	{
		world_pos = pos;
	}

	void look(void)
	{
		gluLookAt(
			world_pos.x, world_pos.y, world_pos.z,
			view_vector.x, view_vector.y, view_vector.z,
			up_vector.x, up_vector.y, up_vector.z
			);
	}

};

