#include "tb_loader_singleton.h"

HashMap<StringName, TBLoaderSingleton::EntityType> TBLoaderSingleton::entity_types;
Vector<Ref<TBLoaderHook>> TBLoaderSingleton::compile_hooks;