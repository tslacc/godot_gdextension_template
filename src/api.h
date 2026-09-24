#pragma once

/*
This file works as a collection of helpers to call the GDExtension API
in a less verbose way, as well as a cache for methods from the discovery API,
just so we don't have to keep loading the same methods again.
*/

#include "gdextension_interface.h"

#include "defs.h"

extern GDExtensionClassLibraryPtr class_library;

// API methods.

extern struct Constructors
{
    GDExtensionInterfaceStringNameNewWithLatin1Chars string_name_new_with_latin1_chars;
    GDExtensionVariantFromTypeConstructorFunc variant_from_float_constructor;
    GDExtensionTypeFromVariantConstructorFunc float_from_variant_constructor;
    GDExtensionInterfaceStringNewWithUtf8Chars string_new_with_utf8_chars;
    
} constructors;

extern struct Destructors
{
    GDExtensionPtrDestructor string_name_destructor;
    GDExtensionPtrDestructor string_destructor;
} destructors;

extern struct Operators
{
    GDExtensionPtrOperatorEvaluator string_name_equal;
} operators;

extern struct API
{
    GDExtensionInterfaceClassdbRegisterExtensionClass2 classdb_register_extension_class2;
    GDExtensionInterfaceClassdbRegisterExtensionClassMethod classdb_register_extension_class_method;
    GDExtensionInterfaceClassdbRegisterExtensionClassProperty classdb_register_extension_class_property;
    GDExtensionInterfaceClassdbRegisterExtensionClassSignal classdb_register_extension_class_signal;
	
	GDExtensionInterfaceClassdbUnregisterExtensionClass classdb_unregister_extension_class;
    
    GDExtensionInterfaceClassdbConstructObject classdb_construct_object;
    
    GDExtensionInterfaceObjectSetInstance object_set_instance;
    GDExtensionInterfaceObjectSetInstanceBinding object_set_instance_binding;
    
    GDExtensionInterfaceGetVariantFromTypeConstructor get_variant_from_type_constructor;
    GDExtensionInterfaceGetVariantToTypeConstructor get_variant_to_type_constructor;
    GDExtensionInterfaceVariantGetType variant_get_type;
    
    GDExtensionInterfaceMemAlloc mem_alloc;
    GDExtensionInterfaceMemFree mem_free;
} api;

void load_api(GDExtensionInterfaceGetProcAddress p_get_proc_address);

// Create a PropertyInfo struct.
GDExtensionPropertyInfo make_property(GDExtensionVariantType type, const char *name);
GDExtensionPropertyInfo make_property_full(GDExtensionVariantType type, const char *name, uint32_t hint, const char *hint_string, const char *class_name, uint32_t usage_flags);

void bind_property(const char *class_name, const char *name, GDExtensionVariantType type, const char *getter, const char *setter);
void destruct_property(GDExtensionPropertyInfo *info);
void bind_signal_1(const char *class_name, const char *signal_name, const char *arg1_name, GDExtensionVariantType arg1_type);

// This is what Godot uses when the types of the values are known to be exact, which avoids using Variant
void ptrcall_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);
void ptrcall_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);

void call_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);
void call_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);

bool is_string_name_equal(GDExtensionConstStringNamePtr p_a, const char *p_b);

// Version for 0 arguments, with return.
void bind_method_0_r(const char *class_name, const char *method_name, void *function, GDExtensionVariantType return_type);

// Version for 1 argument, no return.
void bind_method_1(const char *class_name, const char *method_name, void *function, const char *arg1_name, GDExtensionVariantType arg1_type);
