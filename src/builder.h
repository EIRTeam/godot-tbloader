#pragma once

#include "core/io/file_access.h"
#include "scene/resources/texture.h"
#include "scene/resources/material.h"
#include "scene/resources/mesh.h"
#include "scene/3d/node_3d.h"
#include "scene/3d/area_3d.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/3d/physics_body_3d.h"

#include <map_parser.h>
#include <geo_generator.h>
#include <surface_gatherer.h>

class TBLoader;

enum class ColliderType
{
	// Does not create any collider
	None,

	// Creates a collider from a Mesh (can create a single "merged" convex shape)
	Mesh,

	// Creates a static collider from a MeshInstance3D (can decompose into multiple convex shapes)
	Static,
};

enum class ColliderShape
{
	Convex,
	Concave,
};

class Builder
{
public:
	TBLoader* m_loader;
	std::shared_ptr<LMMapData> m_map;
	Dictionary m_loaded_map_textures; // Texture Name(const char*) - Ref<Texture2D>

public:
	Builder(TBLoader* loader);
	~Builder();

	void load_map(const String& path);
	void build_map();

	void build_worldspawn(int idx, LMEntity& ent);
	void build_brush(int idx, Node3D* node, LMEntity& ent);

	void build_entity(int idx, LMEntity& ent, const String& classname);
	void build_entity_custom(int idx, LMEntity& ent, LMEntityGeometry& geo, const String& classname);
	void build_entity_light(int idx, LMEntity& ent);
	void build_entity_area(int idx, LMEntity& ent);

	void set_entity_node_common(Node3D* node, LMEntity& ent);
	void set_entity_brush_common(int idx, Node3D* node, LMEntity& ent);

protected:
	Vector3 lm_transform(const vec3& v);

	void add_collider_from_mesh(Node3D* area, Ref<ArrayMesh>& mesh, ColliderShape colshape);
	void add_surface_to_mesh(Ref<ArrayMesh>& mesh, LMSurface& surf);
	MeshInstance3D* build_entity_mesh(int idx, LMEntity& ent, Node3D* parent, ColliderType coltype, ColliderShape colshape);

protected:
	void load_and_cache_map_textures();

	String texture_path(const char* name, const char* extension);
	String material_path(const char* name);
	Ref<Texture2D> texture_from_name(const char* name);
	Ref<Material> material_from_name(const char* name);
};
