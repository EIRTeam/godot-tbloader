#include "tbloader_editor_plugin.h"
#include "scene/gui/button.h"

void TBLoaderEditorPlugin::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            Button *map_build_button = memnew(Button);
            map_build_button->set_text("Build Meshes");
            map_build_button->set_flat(true);
            map_build_button->connect("pressed", callable_mp(this, &TBLoaderEditorPlugin::build_meshes));
            
            map_build_control = memnew(HBoxContainer);
            map_build_control->add_child(map_build_button);
            map_build_control->hide();

            add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, map_build_control);
        } break;
        case NOTIFICATION_EXIT_TREE: {
            remove_control_from_container(CONTAINER_SPATIAL_EDITOR_MENU, map_build_control);
            map_build_control->queue_free();
            map_build_control = nullptr;
        } break;
    };
}

bool TBLoaderEditorPlugin::handles(Object *p_object) const {
    return p_object->is_class("TBLoader");
}

void TBLoaderEditorPlugin::edit(Object *p_object) {
    editing_loader = Object::cast_to<TBLoader>(p_object);
}

void TBLoaderEditorPlugin::make_visible(bool p_visible) {
    map_build_control->set_visible(p_visible);
}

void TBLoaderEditorPlugin::build_meshes() {
    if (editing_loader) {
        editing_loader->build_meshes();
    }
}

