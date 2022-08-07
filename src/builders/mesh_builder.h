#pragma once

#include <builder.h>

#include <godot_cpp/classes/mesh_instance3d.hpp>

class MeshBuilder : public Builder
{
public:
	MeshBuilder(TBLoader* loader);
	virtual ~MeshBuilder();

	virtual void build_worldspawn(int idx, LMEntity& ent, LMEntityGeometry& geo) override;

protected:
	virtual void build_entity_mesh(int idx, LMEntity& ent, Node3D* parent, bool build_collision) override;
};
