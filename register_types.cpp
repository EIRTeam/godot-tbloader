#include "register_types.h"

#ifdef TOOLS_ENABLED

#include "editor/editor_node.h"
#endif
#include "src/tb_loader.h"
#include "tbloader_editor_plugin.h"

#ifdef TOOLS_ENABLED
static void _editor_init() {
    TBLoaderEditorPlugin *plugin = memnew(TBLoaderEditorPlugin);
    EditorNode::get_singleton()->add_editor_plugin(plugin);
}
#endif

void initialize_tbloader_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        ClassDB::register_class<TBLoader>();
#ifdef TOOLS_ENABLED
		EditorNode::add_init_callback(_editor_init);
#endif
    }
}

void uninitialize_tbloader_module(ModuleInitializationLevel p_level) {
    
}
