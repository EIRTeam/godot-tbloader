#ifndef TB_LOADER_SINGLETON_H
#define TB_LOADER_SINGLETON_H

#include "core/object/ref_counted.h"
#include "scene/3d/physics/collision_shape_3d.h"
#include "scene/3d/node_3d.h"
#include "tb_loader.h"

struct TBLoaderEntityBuildInfo {
	CollisionShape3D *collision_shape = nullptr;
	String class_name;
};

struct TBLoaderBuildInfo {
	Vector<TBLoaderEntityBuildInfo> entities;
	Vector<CollisionShape3D*> worldspawn_collision_shapes;
};

class TBLoaderEntity {
public:
    struct EntityCompileInfo {
        Vector<StringName> parents;
        Vector<StringName> children;
        Node3D* node;
        TBLoaderEntity* entity;
    };
    virtual void _editor_build(const EntityCompileInfo &p_info, const HashMap<StringName, EntityCompileInfo> &p_entities) {};
    virtual ~TBLoaderEntity() = default;
};

class TBLoaderHook : public Resource {
    GDCLASS(TBLoaderHook, Resource);
public:
    virtual void post_compile_hook(TBLoader *p_loader, TBLoaderBuildInfo *p_build_info) { };
};

class TBLoaderSingleton : public RefCounted {
    GDCLASS(TBLoaderSingleton, RefCounted);
    struct EntityType {
        StringName entity_name;
        StringName class_name;
    };
public:
    static HashMap<StringName, EntityType> entity_types;
    static Vector<Ref<TBLoaderHook>> compile_hooks;
    static void register_compile_hook(Ref<TBLoaderHook> p_hook) {
        compile_hooks.push_back(p_hook);
    }
    template <class T>
    static void register_entity_type() {
        EntityType type;
        type.entity_name = T::get_entity_name();
        type.class_name = T::get_class_static();
        ERR_FAIL_COND_MSG(!ClassDB::is_parent_class(type.class_name, "Node3D"), "Entity classes must inherit Node3D");
        entity_types.insert(type.entity_name, type);
    }
    static Node3D *create_entity(StringName p_entity_name) {
        EntityType *type_info = entity_types.getptr(p_entity_name);
        ERR_FAIL_COND_V_MSG(type_info == nullptr, nullptr, vformat("Entity not found: %s", p_entity_name));
        return Object::cast_to<Node3D>(ClassDB::instantiate(type_info->class_name));
    }
};

#endif // TB_LOADER_SINGLETON_H
