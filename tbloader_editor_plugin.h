#ifndef TBLOADER_EDITOR_PLUGIN_H
#define TBLOADER_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "src/tb_loader.h"
#include "scene/gui/box_container.h"

class TBLoaderEditorPlugin : public EditorPlugin {
    GDCLASS(TBLoaderEditorPlugin, EditorPlugin);
    TBLoader *editing_loader = nullptr;
    HBoxContainer *map_build_control = nullptr;

protected:
    void _notification(int p_what);
    virtual bool handles(Object *p_object) const override;
    virtual void edit(Object *p_object) override;
    virtual void make_visible(bool p_visible) override;
private:
    void build_meshes();
};

#endif // TBLOADER_EDITOR_PLUGIN_H
