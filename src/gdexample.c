#include "gdexample.h"

#include "api.h"

const GDExtensionInstanceBindingCallbacks gdexample_class_binding_callbacks = {
    .create_callback = NULL,
    .free_callback = NULL,
    .reference_callback = NULL,
};

void *gdexample_class_get_virtual_with_data(void *p_class_userdata, GDExtensionConstStringNamePtr p_name){
    // If it is the "_process" method, return a pointer to the gdexample_class_process function.
    if (is_string_name_equal(p_name, "_process"))
    {
        return (void *)gdexample_class_process;
    }
    // Otherwise, return NULL.
    return NULL;
}

void gdexample_class_call_virtual_with_data(GDExtensionClassInstancePtr p_instance, GDExtensionConstStringNamePtr p_name, void *p_virtual_call_userdata, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret){
    // If it is the "_process" method, call it with a helper.
    if (p_virtual_call_userdata == &gdexample_class_process)
    {
        ptrcall_1_float_arg_no_ret(p_virtual_call_userdata, p_instance, p_args, r_ret);
    }
}

GDExtensionObjectPtr gdexample_class_create_instance(void *p_class_userdata){
	printf("gdexample_class_create_instance: create parent (Sprite2D)\n");
    // Create native Godot object;
    StringName class_name;
    constructors.string_name_new_with_latin1_chars(&class_name, "Sprite2D", false);
    GDExtensionObjectPtr object = api.classdb_construct_object(&class_name);
    destructors.string_name_destructor(&class_name);

	printf("gdexample_class_create_instance: create instance of GDExample\n");
    // Create extension object.
    GDExample *self = (GDExample *)api.mem_alloc(sizeof(GDExample));
    gdexample_class_constructor(self);
    self->object = object;

	printf("gdexample_class_create_instance: set instance of self inside Sprite2D\n");
    // Set the extension instance in the native Godot object.
    constructors.string_name_new_with_latin1_chars(&class_name, "GDExample", false);
    api.object_set_instance(object, &class_name, self);
    api.object_set_instance_binding(object, class_library, self, &gdexample_class_binding_callbacks);
    destructors.string_name_destructor(&class_name);

    return object;
}

void gdexample_class_free_instance(void *p_class_userdata, GDExtensionClassInstancePtr p_instance){
	printf("gdexample_class_free_instance\n");
    if (p_instance == NULL)
        return;
    GDExample *self = (GDExample *)p_instance;
    printf("gdexample_class_free_instance: gdexample_class_destructor\n");
    gdexample_class_destructor(self);
    api.mem_free(self);
}

void gdexample_class_constructor(GDExample *self){
    self->time_passed = 0.0;
    self->amplitude = 10.0;
    self->speed = 1.0;
    self->time_emit = 0.0;
    
    constructors.string_name_new_with_latin1_chars(&self->position_changed, "position_changed", false);
}

void gdexample_class_destructor(GDExample *self){
	printf("gdexample_class_destructor\n");
    // Destruct the StringName for the signal.
    destructors.string_name_destructor(&self->position_changed);
}

void gdexample_class_bind_methods(){
	bind_method_0_r("GDExample", "get_amplitude", gdexample_class_get_amplitude, GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_method_1("GDExample", "set_amplitude", gdexample_class_set_amplitude, "amplitude", GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_property("GDExample", "amplitude", GDEXTENSION_VARIANT_TYPE_FLOAT, "get_amplitude", "set_amplitude");
    
    bind_method_0_r("GDExample", "get_speed", gdexample_class_get_speed, GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_method_1("GDExample", "set_speed", gdexample_class_set_speed, "speed", GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_property("GDExample", "speed", GDEXTENSION_VARIANT_TYPE_FLOAT, "get_speed", "set_speed");
    
    bind_signal_1("GDExample", "position_changed", "new_position", GDEXTENSION_VARIANT_TYPE_VECTOR2);
}

void gdexample_class_set_amplitude(GDExample *self, double amplitude){
    self->amplitude = amplitude;
}

double gdexample_class_get_amplitude(const GDExample *self){
    return self->amplitude;
}

void gdexample_class_set_speed(GDExample *self, double speed){
    self->speed = speed;
}

double gdexample_class_get_speed(const GDExample *self){
    return self->speed;
}

void gdexample_class_process(GDExample *self, double delta){
    self->time_passed += self->speed * delta;
}
