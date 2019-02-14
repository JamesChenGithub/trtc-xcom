//
//  xcom_var.cpp
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var.h"

namespace xcom {
#ifdef __cplusplus
    extern "C" {
#endif
        xcom_var::xcom_var_func::xcom_var_func()
        {
            func = nullptr;
            funcpar = nullptr;
        }
        xcom_var::xcom_var_func::xcom_var_func(const xcom_var_func &vf)
        {
            func = vf.func;
            funcpar = vf.funcpar;
        }
        xcom_var::xcom_var_func::xcom_var_func(xcom_var_func &&vf)
        {
            func = vf.func;
            xcom_var_ptr vptr(new xcom_var(std::move(vf.funcpar)));
            funcpar = vptr;
            
            vf.func = nullptr;
            vf.funcpar = nullptr;
        }
        xcom_var::xcom_var_func::xcom_var_func(xcom_var_callback callback, const xcom_var &par)
        {
            func = callback;
            xcom_var_ptr vptr(new xcom_var(par));
            funcpar = vptr;
        }
        xcom_var::xcom_var_func::xcom_var_func(xcom_var_callback callback, xcom_var &&par)
        {
            func = callback;
            funcpar = std::move(par);
        }
        xcom_var::xcom_var_func::~xcom_var_func()
        {
            func = nullptr;
            funcpar.reset();
            funcpar = nullptr;
        }
        
        xcom_var::xcom_var_func &xcom_var::xcom_var_func::operator =(const xcom_var_func &vf)
        {
            func = vf.func;
            funcpar = vf.funcpar;
            return *this;
        }
        xcom_var::xcom_var_func &xcom_var::xcom_var_func::operator =(xcom_var_func &&vf)
        {
            func = vf.func;
            funcpar = std::move(vf.funcpar);
            
            vf.func = nullptr;
            vf.funcpar = nullptr;
            return *this;
        }
        
        xcom_var::xcom_var_func::operator xcom_var() const
        {
            if (func) {
               return func(funcpar);
            }
            return xcom_var();
        }
        const char *xcom_var::xcom_var_func::to_var_json() const
        {
            char buf[128];
            sprintf(buf, "%p", func);
            std::ostringstream ostr;
            ostr << "{ \"func\" : ";
            ostr << (func == nullptr ? "NULL" : buf);
            ostr << ", \"param\" : \"";
            ostr << (funcpar == nullptr ? "void" : funcpar->to_var_json());
            ostr << "}";
            std::string str = ostr.str();
            return str.c_str();
        }
        
        const char *xcom_var::xcom_var_func::to_json() const
        {
            char buf[128];
            sprintf(buf, "%p", func);
            std::ostringstream ostr;
            ostr << "{ \"func\" : ";
            ostr << (func == nullptr ? "NULL" : buf);
            ostr << ", \"param\" : \"";
            ostr << (funcpar == nullptr ? "void" : funcpar->to_json());
            ostr << "}";
            std::string str = ostr.str();
            return str.c_str();
        }
        //==============================
        xcom_var::xcom_var_value::xcom_var_value()
        {
            memset(this, 0, sizeof(xcom_var_value));
            
        }
        xcom_var::xcom_var_value::~xcom_var_value()
        {
            
        }
        
        //==============================
        
        xcom_var::~xcom_var()
        {
            reset();
        }
        #define kDefault_Xcom_Var_Value = {.int32_val{0}}
        xcom_var::xcom_var()
        {
            this->type = xcom_vtype_null;
        }
        
        void xcom_var::reset()
        {
            
            switch(this->type)
            {
                case xcom_vtype_array:
                {
                    if (this->obj.array_val != nullptr)
                    {
                        delete this->obj.array_val;
                        this->obj.array_val = nullptr;
                    }
                    
                    break;
                }
                case xcom_vtype_dict:
                {
                    if (this->obj.dict_val != nullptr)
                    {
                        delete this->obj.dict_val;
                        this->obj.dict_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_bytes:
                {
                    if (this->obj.buf_val != nullptr)
                    {
                        delete this->obj.buf_val;
                        this->obj.buf_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_vptr:
                {
                    xcom_var_ptr ptr = this->obj.vptr_val;
                    if (ptr != nullptr) {
                        ptr->reset();
                    }
                    break;
                }
                case xcom_vtype_func:
                {
                    if (this->obj.func_val != nullptr)
                    {
                        delete this->obj.func_val;
                        this->obj.func_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_null:
                case xcom_vtype_bool:
                case xcom_vtype_int8:
                case xcom_vtype_uint8:
                case xcom_vtype_int16:
                case xcom_vtype_uint16:
                case xcom_vtype_int32:
                case xcom_vtype_uint32:
                case xcom_vtype_int64:
                case xcom_vtype_uint64:
                case xcom_vtype_float:
                case xcom_vtype_double:
                case xcom_vtype_string:
                case xcom_vtype_ref:
               
                default:
                    break;
            }
            memset(&(this->obj), 0, sizeof(xcom_var_value));
            this->type = xcom_vtype_null;
            
        }
    
        void xcom_var::reset(const xcom_var &var)
        {
            this->reset();
            this->type = var.type;
            switch(var.type)
            {
                case xcom_vtype_array:
                {
                    if (var.obj.array_val)
                    {
                        this->obj.array_val = new xcom_var_array;
                        auto it = var.obj.array_val->begin();
                        while (it != var.obj.array_val->end()) {
                            this->obj.array_val->emplace_back(*it);
                            it++;
                        }
                    }
                    
                    break;
                }
                case xcom_vtype_dict:
                {
                    if (var.obj.dict_val)
                    {
                        this->obj.dict_val = new xcom_var_dict;
                        auto it = var.obj.dict_val->begin();
                        while (it != var.obj.dict_val->end()) {
                            this->obj.dict_val->push_back(std::make_pair(it->first, it->second));
                            it++;
                        }
                    }
                    break;
                }
                    
                case xcom_vtype_bytes:
                {
                    if (var.obj.buf_val)
                    {
                        this->obj.buf_val = new xcom_var_buf(var.obj.buf_val->buf, var.obj.buf_val->len);
                    }
                    break;
                }
                case xcom_vtype_vptr:
                {
                    if (var.obj.vptr_val)
                    {
                        this->obj.vptr_val = var.obj.vptr_val;
                    }
                    break;
                }
                    
                case xcom_vtype_null:  break;
                case xcom_vtype_bool: { this->obj.bool_val = var.obj.bool_val; break; }
                case xcom_vtype_int8: { this->obj.int8_val = var.obj.int8_val; break; }
                case xcom_vtype_uint8: { this->obj.uint8_val = var.obj.uint8_val; break; }
                case xcom_vtype_int16: { this->obj.int16_val = var.obj.int16_val; break; }
                case xcom_vtype_uint16: { this->obj.uint16_val = var.obj.uint16_val; break; }
                case xcom_vtype_int32: { this->obj.int32_val = var.obj.int32_val; break; }
                case xcom_vtype_uint32: { this->obj.uint32_val = var.obj.uint32_val; break; }
                case xcom_vtype_int64: { this->obj.int64_val = var.obj.int64_val; break; }
                case xcom_vtype_uint64: { this->obj.uint64_val = var.obj.uint64_val; break; }
                case xcom_vtype_float: { this->obj.float_val = var.obj.float_val; break; }
                case xcom_vtype_double: { this->obj.double_val = var.obj.double_val; break; }
                case xcom_vtype_string: { this->obj.string_val = var.obj.string_val; break; }
                case xcom_vtype_ref: { this->obj.ref_val = var.obj.ref_val; break; }
                case xcom_vtype_func: { this->obj.func_val = var.obj.func_val; break; }
                    
                default:
                {
                    break;
                }
            }
            
            
            
        }
        
        void xcom_var::reset(xcom_var &&var)
        {
            this->reset();
            this->type = var.type;
            switch(var.type)
            {
                case xcom_vtype_array:
                {
                    if (var.obj.array_val)
                    {
                        this->obj.array_val = var.obj.array_val;
                        var.obj.array_val = nullptr;
                    }
                    
                    break;
                }
                case xcom_vtype_dict:
                {
                    if (var.obj.dict_val)
                    {
                        this->obj.dict_val = var.obj.dict_val;
                        var.obj.dict_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_vptr:
                {
                    if (var.obj.vptr_val) {
                        this->obj.vptr_val = var.obj.vptr_val;
                        var.obj.vptr_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_bytes:
                {
                    if (var.obj.buf_val)
                    {
                        this->obj.buf_val = var.obj.buf_val;
                        var.obj.buf_val = nullptr;
                    }
                    break;
                }
                    
                case xcom_vtype_null:  break;
                case xcom_vtype_bool: { this->obj.bool_val = var.obj.bool_val; break; }
                case xcom_vtype_int8: { this->obj.int8_val = var.obj.int8_val; break; }
                case xcom_vtype_uint8: { this->obj.uint8_val = var.obj.uint8_val; break; }
                case xcom_vtype_int16: { this->obj.int16_val = var.obj.int16_val; break; }
                case xcom_vtype_uint16: { this->obj.uint16_val = var.obj.uint16_val; break; }
                case xcom_vtype_int32: { this->obj.int32_val = var.obj.int32_val; break; }
                case xcom_vtype_uint32: { this->obj.uint32_val = var.obj.uint32_val; break; }
                case xcom_vtype_int64: { this->obj.int64_val = var.obj.int64_val; break; }
                case xcom_vtype_uint64: { this->obj.uint64_val = var.obj.uint64_val; break; }
                case xcom_vtype_float: { this->obj.float_val = var.obj.float_val; break; }
                case xcom_vtype_double: { this->obj.double_val = var.obj.double_val; break; }
                case xcom_vtype_string: { this->obj.string_val = var.obj.string_val; var.obj.string_val = ""; break; }
                case xcom_vtype_ref: { this->obj.ref_val = var.obj.ref_val; var.obj.ref_val = nullptr; break; }
                case xcom_vtype_func: { this->obj.func_val = var.obj.func_val; var.obj.func_val = nullptr; break; }
                    
                default:
                {
                    break;
                }
            }
            
            var.reset();
        }


        //================
        const char *xcom_var::to_var_json() const
        {
            std::string typestr = xcom_var_type_string(this->type);
            std::string valstr = "" ;
            switch(this->type)
            {
                case xcom_vtype_null: { valstr = "null"; break; };
                case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; break; };
                case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); break;};
                case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); break;};
                case xcom_vtype_int16: { valstr = std::to_string(this->int8_val()); break;};
                case xcom_vtype_uint16: { valstr = std::to_string(this->int16_val()); break;};
                case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); break;};
                case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); break;};
                case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); break;};
                case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); break;};
                case xcom_vtype_float: { valstr = std::to_string(this->float_val()); break;};
                case xcom_vtype_double: { valstr = std::to_string(this->double_val()); break;};
                case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; break;};
                case xcom_vtype_bytes: {
                    valstr = this->obj.buf_val->to_var_json();
                    break;
                };
                case xcom_vtype_array:
                {
                    std::ostringstream ostr;
                    ostr << "[";
                    auto it = this->obj.array_val->begin();
                    auto end = this->obj.array_val->end();
                    while(it != end){
                        std::string json = (*it)->to_var_json();
                        ostr << json;
                        it++;
                        if (it != end)
                        {
                            ostr << ",";
                        }
                    }
                    ostr << "]";
                    std::string str = ostr.str();
                    return str.c_str();
                };
                case xcom_vtype_dict: {
                    std::ostringstream ostr;
                    ostr << "{";
                    auto it = this->obj.dict_val->begin();
                    auto end = this->obj.dict_val->end();
                    while(it != end){
                        std::string json = it->second->to_var_json();
                        ostr << "\""<<it->first << "\":" << json;
                        it++;
                        if (it != end)
                        {
                            ostr << ",";
                        }
                    }
                    ostr << "}";
                    std::string str = ostr.str();
                    return str.c_str();
                    break;
                };
                case xcom_vtype_vptr:
                {
                    if (this->obj.vptr_val)
                    {
                        std::string str = this->obj.vptr_val->to_var_json();
                        return str.c_str();
                    }
                };
                case xcom_vtype_ref: {
                    char buf[32];
                    sprintf(buf, "%p", this->obj.ref_val);
                    valstr = buf;
                    break;
                };
                case xcom_vtype_func: {
                    if (this->obj.func_val)
                    {
                        std::string str = this->obj.func_val->to_var_json();
                        return str.c_str();
                    } else {
                        valstr = "NULL";
                    }
                    
                    break;
                };
            }

            std::string str = "{ \"" + typestr + "\" : " + valstr + " }";
            return str.c_str();
        }

        const char *xcom_var::to_json() const
        {
            std::string typestr = xcom_var_type_string(this->type);
            std::string valstr = "" ;
            switch(this->type)
            {
                case xcom_vtype_null: { valstr = "null"; std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str(); };
                case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str(); };
                case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();};
                case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();};
                case xcom_vtype_int16: { valstr = std::to_string(this->int16_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_uint16: { valstr = std::to_string(this->uint16_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_float: { valstr = std::to_string(this->float_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_double: { valstr = std::to_string(this->double_val()); std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();}
                case xcom_vtype_bytes: {
                    valstr = this->obj.buf_val->to_var_json();
                    std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();
                    break;
                };
                case xcom_vtype_ref: {
                    char buf[32];
                    sprintf(buf, "%p", this->obj.ref_val);
                    valstr = buf;
                    std::string str = "{ \"" + typestr + "\" : " + valstr + " }"; return str.c_str();
                    break;
                };
                case xcom_vtype_func: {
                    if (this->obj.func_val)
                    {
                        std::string str = this->obj.func_val->to_json();
                        return str.c_str();
                    } else {
                        valstr = "NULL";
                    }
                    
                    break;
                };
                case xcom_vtype_array:
                {
                    std::ostringstream ostr;
                    ostr << "[";
                    auto it = this->obj.array_val->begin();
                    auto end = this->obj.array_val->end();
                    while(it != end){
                        std::string json = (*it)->to_json();
                        ostr << json;
                        it++;
                        if (it != end)
                        {
                            ostr << ",";
                        }
                    }
                    ostr << "]";
                    std::string str = ostr.str();
                    return str.c_str();

                };
                case xcom_vtype_dict: {
                    std::ostringstream ostr;
                    ostr << "{";
                    auto it = this->obj.dict_val->begin();
                    auto end = this->obj.dict_val->end();
                    while(it != end) {
                        xcom_var_ptr ptr = it->second;
                        std::string json = "";
                        if (ptr->type == xcom_vtype_dict || ptr->type == xcom_vtype_array)
                        {
                            json = it->second->to_json();
                            ostr << "\"" << it->first << "\" : " << json ;
                        }
                        else
                        {
                            json = it->second->to_json(it->first.c_str());
                            ostr << json;
                        }


                        it++;
                        if (it != end)
                        {
                            ostr << ",";
                        }
                    }
                    ostr << "}";
                    std::string str = ostr.str();
                    return str.c_str();
                    break;
                }
                case xcom_vtype_vptr:
                {
                    if (this->obj.vptr_val.get())
                    {
                        std::string str = this->obj.vptr_val->to_json();
                        return str.c_str();
                    }
                    return "";
                }
                default:
                    return "";

            }
            return "";
        }

        const char *xcom_var::to_json(const char *key) const
        {
            if (key == nullptr) {
                return "";
            }

            std::string typestr = std::string(key);
            std::string valstr = "" ;
            switch(this->type)
            {
                case xcom_vtype_null: { valstr = "null"; std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); };
                case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); };
                case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_int16: { valstr = std::to_string(this->int16_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_uint16: { valstr = std::to_string(this->uint16_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_float: { valstr = std::to_string(this->float_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_double: { valstr = std::to_string(this->double_val()); std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str(); }
                case xcom_vtype_bytes: {
                    valstr = this->obj.buf_val->to_var_json();
                    std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str();
                    break;
                }
                case xcom_vtype_ref: {
                    char buf[32];
                    sprintf(buf, "%p", this->obj.ref_val);
                    valstr = buf;
                    std::string str = "\"" + typestr + "\" : " + valstr; return str.c_str();
                    break;
                }
                default:
                    return "";

            }
            return "";
        }

        //=====================
        //string
        // string
        xcom_var::xcom_var(const std::string &str): xcom_var() {
            this->type = xcom_vtype_string;
            this->obj.string_val = str;
        }
        xcom_var::xcom_var(const char *cstr) : xcom_var() {
            this->type = xcom_vtype_string;
            this->obj.string_val = cstr ? cstr : "";
        }

        xcom_var::operator const char *() const {
            return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
        }
        xcom_var::operator std::string () const {
            return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : std::string("");
        }

        const char *xcom_var::cstr_val() const  {
            return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
        }
        std::string xcom_var::string_val() const {
            return this->type == xcom_vtype_string ? this->obj.string_val : std::string("");
        }

        xcom_var & xcom_var::operator= (const char *cstr) {
            if (this->type == xcom_vtype_vptr) {
                xcom_var_ptr ptr = this->vptr_val();
                *ptr = (cstr == nullptr ? "" : cstr);
            } else {
                this->reset();
                this->type = xcom_vtype_string;
                this->obj.string_val = (cstr == nullptr ? "" : cstr);
            }
            return *this;
        }
        xcom_var & xcom_var::operator= (const std::string &str) {
            if (this->type == xcom_vtype_vptr) {
                xcom_var_ptr ptr = this->vptr_val();
                *ptr = str;
            } else {
                this->reset();
                this->type = xcom_vtype_string;
                this->obj.string_val = str;
            }
            return *this;
        }

        bool xcom_var::operator == (const char *cstr) const {
            return this->type != xcom_vtype_string || cstr == nullptr ?  false : this->obj.string_val == std::string(cstr);
        }
        bool xcom_var::operator == (const std::string str) const {
            return this->type != xcom_vtype_string || str.length() == 0 ?  false : this->obj.string_val == str;
        }
        //=====================
        /* array */
        xcom_var_ptr xcom_var::operator[](uint32_t index) {
            if (this->type != xcom_vtype_array)
                return nullptr;

            return at(index);
        }

        /* 'index' based array methods */
        void xcom_var::append(xcom_var data)
        {
            if (data.type == xcom_vtype_null)
                return;

            init_varray();
            if (this->type == xcom_vtype_array)
            {
                xcom_var *ptr = new xcom_var(data);
                xcom_var_ptr var_ptr(ptr);
                this->obj.array_val->emplace_back(ptr);
            }
        }


        bool xcom_var::erase(uint32_t index)
        {
            if (this->type == xcom_vtype_array)
            {
                if(index >=0 && index < this->obj.array_val->size())
                {

                    this->obj.array_val->erase(this->obj.array_val->begin() + index);
                    return true;
                }
            }
            return false;
        }


        /* 'index' based array methods */
        xcom_var_ptr xcom_var::at(uint32_t index) {

            if(index >=0 && index < this->obj.array_val->size())
            {
                return (*this->obj.array_val)[index];
            }

            return nullptr;
        }

        void xcom_var::init_varray()
        {
            if (this->type != xcom_vtype_array)
            {
                this->type = xcom_vtype_array;
                this->reset();
                this->obj.array_val = new xcom_var_array;
            }
        }
        //=====================
        /* dict */
        xcom_var_ptr xcom_var::operator[](const char *key) {
            if (!key || !*key)
                return nullptr;

            if (this->type != xcom_vtype_dict)
                init_vdict();

            if (!this->contains(key))
            {
                //            printf("\ntest put \n");
                xcom_var&& var = xcom_var(false);
                this->put(key, std::move(var));
            }
            //        printf("test put done\n");
            xcom_var_ptr ptr = get(key);
            //        printf("get ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
            return ptr;
        }
        bool xcom_var::contains(const char *key)
        {
            if (this->type != xcom_vtype_dict)
                return false;

            // bool succ = this->obj.dict_val->find(key) != this->obj.dict_val->end();
            // return succ;
            for (auto it = this->obj.dict_val->begin(); it != this->obj.dict_val->end(); it++) {
                if (it->first == key ) {
                    return true;
                }
            }
            return false;
        }

        bool xcom_var::erase(const char *key) {
            if (this->type != xcom_vtype_dict)
                return false;

            //            auto it = this->obj.dict_val->find(key);
            //            if (it != this->obj.dict_val->end())
            //            {
            //                it->second.reset();
            //                this->obj.dict_val->erase(it);
            //                return true;
            //            }
            //            return false;

            for (auto it = this->obj.dict_val->begin(); it != this->obj.dict_val->end(); it++) {
                if (it->first == key ) {
                    this->obj.dict_val->erase(it);
                    return true;
                }
            }
            return false;
        }

        void xcom_var::init_vdict()
        {
            if (this->type != xcom_vtype_dict)
            {
                this->type = xcom_vtype_dict;
                this->reset();
                this->obj.dict_val = new xcom_var_dict;
            }
        }

        /* 'key-value' dictionary methods */
        void xcom_var::put(const char *key,  xcom_var&& data) {
            init_vdict();
            xcom_var *ptr = new xcom_var(std::move(data));
            xcom_var_ptr var_ptr(ptr);
            this->obj.dict_val->push_back(std::make_pair(key, var_ptr));
        }

        xcom_var_ptr xcom_var::get(const char *key) {
            auto it = this->obj.dict_val->begin();
            while (it != this->obj.dict_val->end()) {
                if (it->first == key) {
                    return it->second;
                }
                it++;
            }
            return nullptr;
        }
        //=====================
        /* buffer */
        void xcom_var::set_buffer(const void *data, uint32_t len) {
            if (data != nullptr && len > 0) {
                this->reset();
                this->type = xcom_vtype_bytes;
                this->obj.buf_val = new xcom_var_buf(data, len);
            }
        }
        //================
        bool xcom_var::empty()
        {
            if (this->type == xcom_vtype_array )
            {
                return this->obj.array_val->empty();
            }
            else if (this->type == xcom_vtype_dict)
            {
                return this->obj.dict_val->empty();
            }
            else if (this->type == xcom_vtype_vptr) {
                if (this->obj.vptr_val) {
                    return this->obj.vptr_val->empty();
                }
                return false;
            }
            else
            {
                return true;
            }
        }
        uint32_t xcom_var::size()
        {
            if (this->type == xcom_vtype_array )
            {
                return (uint32_t)this->obj.array_val->size();
            }
            else if (this->type == xcom_vtype_dict)
            {
                return (uint32_t)this->obj.dict_val->size();
            }
            else if (this->type == xcom_vtype_vptr) {
                if (this->obj.vptr_val) {
                   return this->obj.vptr_val->size();
                }
                return 0;
            }
            else
            {
                return 1;
            }
        }
#ifdef __cplusplus
    }
#endif
}
